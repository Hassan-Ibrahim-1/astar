#include "app.hpp"
#include "debug.hpp"
#include "engine.hpp"
#include "utils.hpp"

void App::init() {
    /*camera.transform.position = glm::vec3(0, 0, 4);*/
    /*rect.transform.position.x = 1;*/
    /*rect.transform.rotation.yaw = 90;*/

    /*rect.set_fill(false);*/
    scene.add_primitive(&rect);
    scene.add_game_object(obj);
}

void App::update() {
    if (engine::cursor_enabled) {
        utils::imgui_rect("rect", rect);
    }
}

void App::cleanup() {

}

/*void create_grid() {*/
/*    _cells.clear();*/
/**/
/*    // Find the closest factors*/
/*    uint f1 = (uint) glm::sqrt(_ncells);*/
/*    while (_ncells % f1 != 0) {*/
/*        f1--;*/
/*    }*/
/*    // f2 > f1*/
/*    uint f2 = _ncells / f1; // along the width*/
/**/
/*    uint n_rows = 0;*/
/*    uint n_cols = 0;*/
/**/
/*    // put the larger factor amount of cells on the larger side*/
/*    if (_rect.transform.scale.x > _rect.transform.scale.y) {*/
/*        n_rows = f1 - 1;*/
/*        n_cols = f2 - 1;*/
/*    }*/
/*    else {*/
/*        n_rows = f2 - 1;*/
/*        n_cols = f1 - 1;*/
/*    }*/
/**/
/*    _cols = n_cols;*/
/*    _rows = n_rows;*/
/**/
/*    update_direction_offsets();*/
/**/
/*    Transform cell_t = Transform();*/
/*    cell_t.scale.x = _rect.transform.scale.x / n_cols;*/
/*    cell_t.scale.y = _rect.transform.scale.y / n_rows;*/
/**/
/*    // make cell go to the upper left corner*/
/*    cell_t.position.x = (-0.5 * _rect.transform.scale.x) + _rect.transform.position.x;*/
/*    // + here to make the cell go to the right*/
/*    cell_t.position.x += (cell_t.scale.x / 2);*/
/**/
/*    // - here to make the cell go downwards - opposite of vao coordinate*/
/*    cell_t.position.y = (0.5 * _rect.transform.scale.y) + _rect.transform.position.y;*/
/*    cell_t.position.y -= (cell_t.scale.y / 2);*/
/**/
/*    float original_xpos = cell_t.position.x;*/
/**/
/*    // render all cells*/
/*    for (uint i = 0; i < n_rows; i++) {*/
/*        for (uint j = 0; j < n_cols; j++) {*/
/*            _cells.push_back(Cell(cell_t, glm::vec4(1)));*/
/*            cell_t.position.x += cell_t.scale.x;*/
/*        }*/
/*        cell_t.position.x = original_xpos;*/
/*        cell_t.position.y -= cell_t.scale.y;*/
/*    }*/
/*    _cell_fills.resize(_cells.size());*/
/*}*/
/**/
