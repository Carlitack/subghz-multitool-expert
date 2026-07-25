// scenes/protopirate_scene_radar.c — Radar animation screen
#include "../protopirate_app_i.h"

void protopirate_scene_radar_on_enter(void* context) {
    ProtoPirateApp* app = context;
    widget_reset(app->widget);
    widget_add_text_scroll_element(app->widget, 0, 0, 128, 64,
        "RADAR SCAN\n\n"
        "Frequency: 433.92 MHz\n"
        "Modulation: AM+FM Auto\n\n"
        "Sweeping...\n"
        "Press BACK to stop\n\n"
        "Tip: point Flipper at\n"
        "receiver, not the keyfob");
    view_dispatcher_switch_to_view(app->view_dispatcher, ProtoPirateViewWidget);
}

bool protopirate_scene_radar_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context); UNUSED(event);
    return false;
}

void protopirate_scene_radar_on_exit(void* context) {
    ProtoPirateApp* app = context;
    widget_reset(app->widget);
}
