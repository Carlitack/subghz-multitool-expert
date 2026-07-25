// scenes/protopirate_scene_jam.c — Simple 433 MHz jammer (fixed)
#include "../protopirate_app_i.h"
#include <lib/subghz/devices/devices.h>
#include <lib/subghz/transmitter.h>

#define TAG "Jammer"

typedef struct {
    SubGhzTransmitter* transmitter;
    bool active;
} JamContext;

static JamContext* jam_ctx = NULL;

void protopirate_scene_jam_on_enter(void* context) {
    ProtoPirateApp* app = context;
    
    // Clean up any previous instance (prevents leak on re-entry)
    if(jam_ctx) {
        if(jam_ctx->transmitter) {
            subghz_transmitter_stop(jam_ctx->transmitter);
            subghz_transmitter_free(jam_ctx->transmitter);
        }
        free(jam_ctx);
    }

    jam_ctx = malloc(sizeof(JamContext));
    jam_ctx->active = false;
    jam_ctx->transmitter = NULL;

    if(!protopirate_radio_init(app)) {
        notification_message(app->notifications, &sequence_error);
        scene_manager_previous_scene(app->scene_manager);
        return;
    }

    jam_ctx->active = true;
    widget_reset(app->widget);
    widget_add_text_scroll_element(app->widget, 0, 0, 128, 64,
        "JAMMING 433 MHz\n\nActive - blocking signals\nPress BACK to stop\n\nTip: use before capturing\nto prevent original keyfob\nfrom reaching the car");
    view_dispatcher_switch_to_view(app->view_dispatcher, ProtoPirateViewWidget);
}

bool protopirate_scene_jam_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    return false;
}

void protopirate_scene_jam_on_exit(void* context) {
    ProtoPirateApp* app = context;
    UNUSED(app);
    if(jam_ctx) {
        jam_ctx->active = false;
        if(jam_ctx->transmitter) {
            subghz_transmitter_stop(jam_ctx->transmitter);
            subghz_transmitter_free(jam_ctx->transmitter);
            jam_ctx->transmitter = NULL;
        }
        free(jam_ctx);
        jam_ctx = NULL;
    }
}
