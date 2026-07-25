// scenes/protopirate_scene_start.c — Pandora-style simplified menu
#include "../protopirate_app_i.h"

#include "subghz_mt_expert_icons.h"

#define TAG "ProtoPirateSceneStart"

typedef enum {
    SubmenuIndexProtoPirateCar,
    SubmenuIndexProtoPirateEmulate,
    SubmenuIndexProtoPirateTools,
    SubmenuIndexProtoPirateGuide,
} SubmenuIndexSimplified;

static void protopirate_scene_start_submenu_callback(void* context, uint32_t index) {
    furi_check(context);
    ProtoPirateApp* app = context;
    view_dispatcher_send_custom_event(app->view_dispatcher, index);
}

void protopirate_scene_start_on_enter(void* context) {
    furi_check(context);
    ProtoPirateApp* app = context;

    protopirate_release_shared_radio_state(app);

    submenu_set_header(app->submenu, "SubGhz MT Expert");
    submenu_add_item(app->submenu, "Voiture", SubmenuIndexProtoPirateCar,
        protopirate_scene_start_submenu_callback, app);
    submenu_add_item(app->submenu, "Emulation", SubmenuIndexProtoPirateEmulate,
        protopirate_scene_start_submenu_callback, app);
    submenu_add_item(app->submenu, "Outils", SubmenuIndexProtoPirateTools,
        protopirate_scene_start_submenu_callback, app);
    submenu_add_item(app->submenu, "Guide", SubmenuIndexProtoPirateGuide,
        protopirate_scene_start_submenu_callback, app);

    submenu_set_selected_item(
        app->submenu, scene_manager_get_scene_state(app->scene_manager, ProtoPirateSceneStart));

    view_dispatcher_switch_to_view(app->view_dispatcher, ProtoPirateViewSubmenu);
}

bool protopirate_scene_start_on_event(void* context, SceneManagerEvent event) {
    furi_check(context);
    ProtoPirateApp* app = context;

    if(event.type == SceneManagerEventTypeCustom) {
        if(event.event == SubmenuIndexProtoPirateCar) {
            app->auto_save = true;
            scene_manager_next_scene(app->scene_manager, ProtoPirateSceneReceiverConfig);
        } else if(event.event == SubmenuIndexProtoPirateEmulate) {
            scene_manager_next_scene(app->scene_manager, ProtoPirateSceneSaved);
        } else if(event.event == SubmenuIndexProtoPirateTools) {
            scene_manager_next_scene(app->scene_manager, ProtoPirateSceneTimingTuner);
        } else if(event.event == SubmenuIndexProtoPirateGuide) {
            scene_manager_next_scene(app->scene_manager, ProtoPirateSceneProtocolHelp);
        }
    } else if(event.type == SceneManagerEventTypeBack) {
        scene_manager_set_scene_state(
            app->scene_manager, ProtoPirateSceneStart, 0);
    }
    return false;
}

void protopirate_scene_start_on_exit(void* context) {
    furi_check(context);
    ProtoPirateApp* app = context;
    submenu_reset(app->submenu);
}
