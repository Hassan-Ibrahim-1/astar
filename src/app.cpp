#include "app.hpp"
#include "debug.hpp"
#include "engine.hpp"
#include "utils.hpp"

void App::init() {
    /*camera.transform.position = glm::vec3(0, 0, 4);*/
    /*rect.transform.position.x = 1;*/
    /*rect.transform.rotation.yaw = 90;*/

    /*rect.set_fill(false);*/
    grid.create_cells(ncells);
    grid.add_to_scene();
}

void App::update() {
    if (engine::cursor_enabled) {
        utils::imgui_rect("boundary", grid.boundary);
        if (ImGui::DragInt("ncells", (int*)&ncells, 1, 0)) {
            grid.create_cells(ncells);
            // TODO: this fixes something
            // this is really buggy.
            // Fix memory stuff. Maybe automatically
            // add to scene
            grid.add_to_scene();
        }
    }
}

void App::cleanup() {
}
