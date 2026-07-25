// scenes/protopirate_scene_car_capture.c — Select car → auto-config → capture
#include "../protopirate_app_i.h"
#include "../car_presets.h"

#define TAG "CarCapture"
#define MAX_MODELS 12

typedef enum {
    CarStepBrand,
    CarStepModel,
} CarStep;

static void car_capture_callback(void* context, uint32_t index) {
    ProtoPirateApp* app = context;
    uint32_t step = scene_manager_get_scene_state(app->scene_manager,
        ProtoPirateSceneCarCapture) & 0xFFFF;
    uint32_t brand_idx = (scene_manager_get_scene_state(app->scene_manager,
        ProtoPirateSceneCarCapture) >> 16) & 0xFF;

    if(step == CarStepBrand) {
        // Show models for this brand
        const char* brand = CAR_BRANDS[index];
        const CarPreset* models[MAX_MODELS];
        uint8_t count = car_presets_by_brand(brand, models, MAX_MODELS);

        scene_manager_set_scene_state(app->scene_manager, ProtoPirateSceneCarCapture,
            (CarStepModel << 16) | (index & 0xFFFF));

        submenu_reset(app->submenu);
        submenu_set_header(app->submenu, brand);
        char label[64];
        for(uint8_t i = 0; i < count; i++) {
            snprintf(label, sizeof(label), "%s (%d-%d)",
                models[i]->model, models[i]->year_start, models[i]->year_end);
            submenu_add_item(app->submenu, label, i, car_capture_callback, app);
        }
        view_dispatcher_switch_to_view(app->view_dispatcher, ProtoPirateViewSubmenu);
    } else {
        // Model selected → configure and go to receiver
        const char* brand = CAR_BRANDS[brand_idx];
        const CarPreset* models[MAX_MODELS];
        uint8_t count = car_presets_by_brand(brand, models, MAX_MODELS);

        if(index < count && models[index]) {
            const CarPreset* p = models[index];
            app->auto_save = true;
            if(app->txrx && app->txrx->preset) {
                furi_string_set_str(app->txrx->preset->name, p->mod);
                app->txrx->preset->frequency = p->frequency;
            }
            scene_manager_next_scene(app->scene_manager, ProtoPirateSceneReceiver);
        }
    }
}

void protopirate_scene_car_capture_on_enter(void* context) {
    ProtoPirateApp* app = context;
    uint32_t step = scene_manager_get_scene_state(app->scene_manager,
        ProtoPirateSceneCarCapture);
    uint32_t display_step = step & 0xFFFF;

    if(display_step != CarStepModel) {
        // Show brand list
        submenu_reset(app->submenu);
        submenu_set_header(app->submenu, "Marque");
        for(uint8_t i = 0; CAR_BRANDS[i] && i < 24; i++) {
            if(CAR_BRANDS[i][0] == '-') continue; // Skip separators
            submenu_add_item(app->submenu, CAR_BRANDS[i], i, car_capture_callback, app);
        }
        scene_manager_set_scene_state(app->scene_manager, ProtoPirateSceneCarCapture, CarStepBrand);
        view_dispatcher_switch_to_view(app->view_dispatcher, ProtoPirateViewSubmenu);
    }
}

bool protopirate_scene_car_capture_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    return false;
}

void protopirate_scene_car_capture_on_exit(void* context) {
    ProtoPirateApp* app = context;
    submenu_reset(app->submenu);
}
