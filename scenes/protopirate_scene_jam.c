// scenes/protopirate_scene_jam.c — 433 MHz jammer (working)
#include "../protopirate_app_i.h"
#include <lib/subghz/devices/devices.h>
#include <lib/subghz/transmitter.h>

#define TAG "Jammer"

typedef struct {
    SubGhzTransmitter* transmitter;
    FlipperFormat* ff;
    bool active;
} JamContext;

static JamContext* jam_ctx = NULL;

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

    jam_ctx->transmitter = subghz_transmitter_alloc_init(
        app->txrx->environment, "AM650");
    if(!jam_ctx->transmitter) {
        FURI_LOG_E(TAG, "Transmitter alloc failed");
        notification_message(app->notifications, &sequence_error);
        free(jam_ctx); jam_ctx = NULL;
        scene_manager_previous_scene(app->scene_manager);
        return;
    }

    // Load noise pattern
    jam_ctx->ff = flipper_format_string_alloc();
    flipper_format_write_string_cstr(jam_ctx->ff, "Protocol", "RAW");
    flipper_format_write_string_cstr(jam_ctx->ff, "RAW_Data", 
        "300 -300 600 -600 300 -300 600 -600 "
        "300 -300 600 -600 300 -300 600 -600");
    subghz_transmitter_deserialize(jam_ctx->transmitter, jam_ctx->ff);

    // Start TX using same API as emulate plugin
    if(!subghz_devices_start_async_tx(
        app->txrx->radio_device,
        subghz_transmitter_yield,
        jam_ctx->transmitter)) {
        FURI_LOG_E(TAG, "TX start failed");
        subghz_transmitter_free(jam_ctx->transmitter);
        flipper_format_free(jam_ctx->ff);
        free(jam_ctx); jam_ctx = NULL;
        notification_message(app->notifications, &sequence_error);
        scene_manager_previous_scene(app->scene_manager);
        return;
    }

    app->txrx->txrx_state = ProtoPirateTxRxStateTx;
    jam_ctx->active = true;
    FURI_LOG_I(TAG, "JAMMING ACTIVE 433.92 MHz");

    widget_reset(app->widget);
    widget_add_text_scroll_element(app->widget, 0, 0, 128, 64,
        "JAMMING 433.92 MHz\n\nACTIVE - TX noise\nBlocking all signals\n\nPress BACK to stop\n\nWARNING: illegal on\npublic frequencies!");
    view_dispatcher_switch_to_view(app->view_dispatcher, ProtoPirateViewWidget);
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
