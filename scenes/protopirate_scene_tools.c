// scenes/protopirate_scene_tools.c — Outils: Jam, Timing Tuner, Sub Decode
#include "../protopirate_app_i.h"

typedef enum { ToolJam, ToolTiming, ToolSubDecode } ToolItem;

static void tools_cb(void* context, uint32_t index) {
    ProtoPirateApp* app = context;
    view_dispatcher_send_custom_event(app->view_dispatcher, index);
}

void protopirate_scene_tools_on_enter(void* context) {
    ProtoPirateApp* app = context;
    submenu_reset(app->submenu);
    submenu_set_header(app->submenu, "Outils");
    submenu_add_item(app->submenu, "Jam 433 MHz", ToolJam, tools_cb, app);
    submenu_add_item(app->submenu, "Timing Tuner", ToolTiming, tools_cb, app);
    submenu_add_item(app->submenu, "Sub Decode", ToolSubDecode, tools_cb, app);
    view_dispatcher_switch_to_view(app->view_dispatcher, ProtoPirateViewSubmenu);
}

bool protopirate_scene_tools_on_event(void* context, SceneManagerEvent event) {
    ProtoPirateApp* app = context;
    if(event.type == SceneManagerEventTypeCustom) {
        switch(event.event) {
        case ToolJam:
            scene_manager_next_scene(app->scene_manager, ProtoPirateSceneJam);
            return true;
        case ToolTiming:
            scene_manager_next_scene(app->scene_manager, ProtoPirateSceneTimingTuner);
            return true;
        case ToolSubDecode:
            scene_manager_next_scene(app->scene_manager, ProtoPirateSceneSubDecode);
            return true;
        }
    }
    return false;
}

void protopirate_scene_tools_on_exit(void* context) {
    ProtoPirateApp* app = context;
    submenu_reset(app->submenu);
}
