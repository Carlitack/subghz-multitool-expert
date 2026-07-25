// scenes/protopirate_scene_start.c — Pandora-style simplified menu
#include "../protopirate_app_i.h"

#include "subghz_mt_expert_icons.h"

#define TAG "ProtoPirateSceneStart"

typedef enum {
    MenuCar = 0,
    MenuEmulate,
    MenuTools,
    MenuGuide,
} MenuItem;

static void start_cb(void* context, uint32_t index) {
    ProtoPirateApp* app = context;
    view_dispatcher_send_custom_event(app->view_dispatcher, index);
}

void protopirate_scene_start_on_enter(void* context) {
    ProtoPirateApp* app = context;
    protopirate_release_shared_radio_state(app);

    submenu_set_header(app->submenu, "SubGhz MT Expert");
    submenu_add_item(app->submenu, "Voiture", MenuCar, start_cb, app);
    submenu_add_item(app->submenu, "Emulation", MenuEmulate, start_cb, app);
    submenu_add_item(app->submenu, "Outils", MenuTools, start_cb, app);
    submenu_add_item(app->submenu, "Guide", MenuGuide, start_cb, app);
    view_dispatcher_switch_to_view(app->view_dispatcher, ProtoPirateViewSubmenu);
}

bool protopirate_scene_start_on_event(void* context, SceneManagerEvent event) {
    ProtoPirateApp* app = context;
    if(event.type == SceneManagerEventTypeCustom) {
        switch(event.event) {
        case MenuCar:
            scene_manager_next_scene(app->scene_manager, ProtoPirateSceneCarCapture);
            return true;
        case MenuEmulate:
            scene_manager_next_scene(app->scene_manager, ProtoPirateSceneSaved);
            return true;
        case MenuTools:
            scene_manager_next_scene(app->scene_manager, ProtoPirateSceneTools);
            return true;
        case MenuGuide:
            scene_manager_next_scene(app->scene_manager, ProtoPirateSceneProtocolHelp);
            return true;
        }
    }
    return false;
}

void protopirate_scene_start_on_exit(void* context) {
    ProtoPirateApp* app = context;
    submenu_reset(app->submenu);
}
