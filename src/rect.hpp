#pragma once

#include "game_object.hpp"
#include "material.hpp"
#include "transform.hpp"

struct Rect : GameObject {
    static constexpr DrawCommand rect_draw_command = {
        DrawCommandType::DRAW_ELEMENTS,
        DrawCommandMode::TRIANGLES,
        6 // 6 indices
    };
    // NOTE: ignore scale.z it does nothing
    // Maybe add a transform2D class for this?

    /*Transform transform = Transform();*/
    /*Material material;*/
    /*bool hidden = false;*/

    Rect() {
        Mesh& mesh = create_mesh();
        mesh.draw_command = rect_draw_command;
    }
    Rect(Transform transform, Material material = Material())
        : GameObject(transform, material) {
        Mesh& mesh = create_mesh();
        mesh.draw_command = rect_draw_command;
    }
    Rect(glm::vec3 position, Material material = Material())
        : GameObject(Transform(position), material) {
        Mesh& mesh = create_mesh();
        mesh.draw_command = rect_draw_command;
    }
};

