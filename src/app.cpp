#include "app.hpp"
#include "debug.hpp"
#include "engine.hpp"
#include "input.hpp"
#include "utils.hpp"

void App::init() {
    /*camera.transform.position = glm::vec3(0, 0, 4);*/
    /*rect.transform.position.x = 1;*/
    /*rect.transform.rotation.yaw = 90;*/

    grid.create_cells(ncells);
    grid.add_to_scene();
    camera.transform.position.z = 1.3;
    camera.lock();

    target_cell = grid.cells[50];
    start_cell = grid.cells[5];

    start_cell->set_fill(true);
    target_cell->set_fill(true);
    start_cell->material.color = Color(0, 0, 255);
    target_cell->material.color = Color(0, 255, 0);

    path.trace(start_cell, target_cell, grid);
}

void App::update() {
    if (engine::cursor_enabled) {
        if (utils::imgui_rect("boundary", grid.boundary)
         || ImGui::DragInt("ncells", (int*)&ncells, 1, 0)) {
            grid.create_cells(ncells);
            grid.add_to_scene();
        }
        if (!grid.cells.empty()) {
            utils::imgui_rect("cell1", *grid.cells.front());
        }
        auto mp = input::get_mouse_pos();
        ImGui::Text("mouse pos (%f, %f)", mp.x, mp.y);

        // left click to highlight, right click to remove
        if (input::mouse_button_down(MouseButton::ANY)) {
            for (auto cell : grid.cells) {
                if (utils::mouse_in_rect(*cell)) {
                    if (input::mouse_button_down(MouseButton::LEFT)) {
                        clear_path_cells();
                        target_cell->set_fill(false);
                        target_cell->material.color = Color(255);
                        target_cell = cell;
                        start_cell->set_fill(true);

                        path.trace(start_cell, target_cell, grid);
                        cell->set_fill(true);
                        cell->material.color = Color(0, 255, 0);
                    }
                    else if (input::mouse_button_down(MouseButton::RIGHT)) {
                        clear_path_cells();
                        cell->traversable = !cell->traversable; 
                        path.trace(start_cell, target_cell, grid);
                        cell->set_fill(!cell->traversable);
                    }
                }
            }
        }
    }
}

void App::cleanup() {
}

void App::clear_path_cells() {
    for (auto cell : grid.cells) {
        if (cell->material.color == Color(255, 0, 0)) {
            cell->material.color = Color(255);
            cell->set_fill(false);
        }
    }
}

