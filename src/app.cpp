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

    /*grid.boundary.transform.rotation = {*/
    /*    -82,*/
    /*    90,*/
    /*    -124*/
    /*};*/
    /**/
    /*grid.boundary.transform.scale = { */
    /*    8.2,*/
    /*    1,*/
    /*    8.6*/
    /*};*/

    camera.velocity = 20;
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
    scene.add_point_light(&light);

    capsule_model.load("models/capsule/capsule.obj");
    capsule.load_mesh_data(capsule_model);
    capsule.material.color = Color(255, 141, 141);
    scene.add_game_object(&capsule);
    /*capsule.hidden = true;*/

    cube.transform.scale = glm::vec3(50, 1, 50);
    cube.transform.position.y = -2.6;
    scene.add_primitive(&cube);

    end_point.material.color = Color(0, 255, 0);
    end_point.transform.position = glm::vec3(17, -0.8, 0);
    scene.add_primitive(&end_point);

    grid.boundary.transform = cube.transform;
    grid.boundary.transform.position.y += cube.transform.scale.y;
    // HACK: adding one to z fixes the misalignment between 
    // the grid and the cube. idk why its misaligned in the first
    // place tho
    grid.boundary.transform.position.z += 1;
    grid.boundary.transform.rotation.pitch = 90;
    grid.create_cells(ncells);
    grid.add_to_scene();
    grid.boundary.set_fill(false);

    create_path();
}

void App::update() {
    /*grid.boundary.transform.rotation.pitch += sin(glfwGetTime());*/
    /*grid.boundary.transform.rotation.yaw += sin(glfwGetTime());*/
    /*grid.boundary.transform.rotation.roll += cos(glfwGetTime());*/
    /*grid.create_cells(ncells);*/
    /*grid.add_to_scene();*/

    update_capsule_path();
    update_capsule_pos();

    if (engine::cursor_enabled) {
        if (utils::imgui_game_object("capsule", capsule)) {
            clear_path_cells();
            LOG("recreating path");
            create_path();
            /*grid.add_to_scene();*/
            /*grid.create_cells(ncells);*/
        }
        ImGui::Spacing();

        /*if (utils::imgui_rect("boundary", grid.boundary)*/
        /* || ImGui::DragInt("ncells", (int*)&ncells, 1, 0)) {*/
        /*    grid.create_cells(ncells);*/
        /*    grid.add_to_scene();*/
        /*}*/

        auto mp = input::get_mouse_pos();
        ImGui::Text("mouse pos (%f, %f)", mp.x, mp.y);

        utils::imgui_point_light("light", light);
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

void App::create_path() {
    if (start_cell && target_cell) {
        start_cell->set_fill(false);
        target_cell->set_fill(false);
        start_cell->material.color = Color(255);
        target_cell->material.color = Color(255);
    }

    start_cell = grid.find_cell(capsule.transform.position).value_or(nullptr);
    if (start_cell == nullptr) {
        LOG("no cell found for capsule");
        return;
    }
    /*ASSERT(start_cell, "no cell found for capsule");*/

    target_cell = grid.find_cell(end_point.transform.position).value_or(nullptr);
    if (target_cell == nullptr) {
        LOG("no cell found for end point");
        return;
    }
    /*ASSERT(target_cell, "no cell found for end point");*/

    start_cell->set_fill(true);
    start_cell->material.color = Color(0, 0, 255);
    target_cell->set_fill(true);
    target_cell->material.color = Color(0, 255, 0);

    auto tmp = path.trace(start_cell, target_cell, grid);
    ASSERT(tmp.has_value(), "no path found");
    cells = tmp.value();
    current_cell = 0;
    capsule_velocity = {0, 0, 0};
}

void App::clear_path_cells() {
    for (auto cell : grid.cells) {
        if (cell->material.color == Color(255, 0, 0)) {
            cell->material.color = Color(255);
            cell->set_fill(false);
        }
    }
}

void App::update_capsule_path() {
    auto actual_cell = grid.find_cell(capsule.transform.position).value_or(nullptr);
    if (actual_cell == nullptr) {
        capsule_velocity = {0, 0, 0};
        return;
    }
    else if (actual_cell != cells[current_cell]) {
        // What
        current_cell = current_cell++;
    }
    Cell& cell = *cells[current_cell];
    auto cell_pos = cell.transform.position;
    cell_pos.y = 0;
    glm::vec3 dir = glm::normalize(
        cell_pos - capsule.transform.position
    );
    capsule_velocity = 4.0f * dir;
    capsule_velocity.y = 0;
}

void App::update_capsule_pos() {
    // d = vt
    capsule.transform.position += capsule_velocity * delta_time;
}

