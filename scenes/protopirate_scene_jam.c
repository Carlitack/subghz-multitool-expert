// scenes/protopirate_scene_jam.c — Jammer with frequency selection
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

static const uint32_t JAM_FREQS[] = {
    315000000, 390000000, 433920000, 434420000, 868000000,
};

void protopirate_scene_jam_on_enter(void* context) {
    ProtoPirateApp* app = context;
    
    if(jam_ctx) {
        if(jam_ctx->transmitter) {
            subghz_transmitter_stop(jam_ctx->transmitter);
            subghz_transmitter_free(jam_ctx->transmitter);
        }
        if(jam_ctx->ff) flipper_format_free(jam_ctx->ff);
        free(jam_ctx);
    }

    jam_ctx = malloc(sizeof(JamContext));
    memset(jam_ctx, 0, sizeof(JamContext));

    if(!protopirate_radio_init(app)) {
        notification_message(app->notifications, &sequence_error);
        free(jam_ctx); jam_ctx = NULL;
        scene_manager_previous_scene(app->scene_manager);
        return;
    }

    // Build long noise pattern (~30 sec TX)
    jam_ctx->ff = flipper_format_string_alloc();
    flipper_format_write_string_cstr(jam_ctx->ff, "Protocol", "RAW");
    
    FuriString* raw = furi_string_alloc();
    for(int i = 0; i < 200; i++) {
        furi_string_cat_printf(raw,
            "300 -300 600 -600 400 -400 500 -500 350 -350 550 -550 "
            "300 -300 700 -700 450 -450 650 -650 500 -500 400 -400 "
            "550 -550 350 -350 300 -300 600 -600 450 -450 700 -700 ");
    }
    flipper_format_write_string_cstr(jam_ctx->ff, "RAW_Data", furi_string_get_cstr(raw));
    furi_string_free(raw);

    // Default: 433.92 MHz
    jam_ctx->frequency = 433920000;
    jam_ctx->transmitter = subghz_transmitter_alloc_init(app->txrx->environment, "AM650");
    if(!jam_ctx->transmitter) goto fail;
    
    subghz_transmitter_deserialize(jam_ctx->transmitter, jam_ctx->ff);

    if(!subghz_devices_start_async_tx(app->txrx->radio_device,
        subghz_transmitter_yield, jam_ctx->transmitter)) goto fail;

    app->txrx->txrx_state = ProtoPirateTxRxStateTx;
    jam_ctx->active = true;

    widget_reset(app->widget);
    widget_add_text_scroll_element(app->widget, 0, 0, 128, 64,
        "JAMMING 433.92 MHz\n\nTX active - ~60 sec\nBlocking all signals\n\nPress BACK to stop\n\nWARNING: illegal on\npublic frequencies!");
    view_dispatcher_switch_to_view(app->view_dispatcher, ProtoPirateViewWidget);
    return;

fail:
    notification_message(app->notifications, &sequence_error);
    if(jam_ctx->transmitter) {
        subghz_transmitter_free(jam_ctx->transmitter);
    }
    if(jam_ctx->ff) flipper_format_free(jam_ctx->ff);
    free(jam_ctx); jam_ctx = NULL;
    scene_manager_previous_scene(app->scene_manager);
}

bool protopirate_scene_jam_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    return false;
}

void protopirate_scene_jam_on_exit(void* context) {
    ProtoPirateApp* app = context;
    if(jam_ctx) {
        jam_ctx->active = false;
        if(jam_ctx->transmitter) {
            subghz_transmitter_stop(jam_ctx->transmitter);
            subghz_transmitter_free(jam_ctx->transmitter);
        }
        if(jam_ctx->ff) flipper_format_free(jam_ctx->ff);
        free(jam_ctx);
        jam_ctx = NULL;
    }
    if(app && app->txrx) {
        app->txrx->txrx_state = ProtoPirateTxRxStateIDLE;
        subghz_devices_idle(app->txrx->radio_device);
    }
}
