#include "app.hpp"
#include "debug.hpp"
#include "engine.hpp"
#include "imgui.h"
#include "input.hpp"
#include "utils.hpp"

void App::init() {
    /*camera.transform.position = glm::vec3(0, 0, 4);*/
    /*rect.transform.position.x = 1;*/
    /*rect.transform.rotation.yaw = 90;*/

    grid.boundary.transform.rotation = {
        -82,
        90,
        -124
    };

    grid.boundary.transform.scale = { 
        8.2,
        1,
        8.6
    };

    grid.boundary.transform.rotation.pitch = 90;
    grid.create_cells(ncells);
    grid.add_to_scene();
    grid.boundary.set_fill(false);

    camera.velocity = 14;
    camera.transform.position.x = -1.2;
    camera.transform.position.y = 4;
    camera.transform.position.z = 15;
    /*camera.lock();*/

    /*target_cell = grid.cells[50];*/
    /*start_cell = grid.cells[5];*/

    /*start_cell->set_fill(true);*/
    /*target_cell->set_fill(true);*/
    /*start_cell->material.color = Color(0, 0, 255);*/
    /*target_cell->material.color = Color(0, 255, 0);*/
    /**/
    /*path.trace(start_cell, target_cell, grid);*/

    light.position.y = 20;
    light.constant = 0.12;
    light.linear = 0.033;
    light.quadratic = 0.010;
    /*scene.add_point_light(&light);*/

    capsule_model.load("models/capsule/capsule.obj");
    capsule.load_mesh_data(capsule_model);
    capsule.material.color = Color(255, 141, 141);
    /*capsule.hidden = true;*/
    /*scene.add_game_object(&capsule);*/

    cube.transform.scale = glm::vec3(50, 1, 50);
    cube.transform.position.y = -2.6;
    /*scene.add_primitive(&cube);*/

    end_point.material.color = Color(0, 255, 0);
    end_point.transform.position = glm::vec3(17, -0.8, 0);
    /*scene.add_primitive(&end_point);*/
    

    /*scene.add_primitive(&rect);*/
}

void App::update() {

    grid.boundary.transform.rotation.pitch += sin(glfwGetTime());
    /*grid.boundary.transform.rotation.yaw += sin(glfwGetTime());*/
    /*grid.boundary.transform.rotation.roll += cos(glfwGetTime());*/
    grid.create_cells(ncells);
    grid.add_to_scene();

    if (engine::cursor_enabled) {
        if (utils::imgui_rect("boundary", grid.boundary)
         || ImGui::DragInt("ncells", (int*)&ncells, 1, 0)) {
            grid.create_cells(ncells);
            grid.add_to_scene();
        }

        auto mp = input::get_mouse_pos();
        ImGui::Text("mouse pos (%f, %f)", mp.x, mp.y);

        utils::imgui_point_light("light", light);
        ImGui::Spacing();
        utils::imgui_game_object("capsule", capsule);
        ImGui::Spacing();
        utils::imgui_cube("cube", cube);
        ImGui::Spacing();
        utils::imgui_cube("end", end_point);
        ImGui::Spacing();

        return;

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

