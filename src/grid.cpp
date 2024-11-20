#include "grid.hpp"

void Grid::create_cells(uint ncells) {
    delete_cells();

    uint f1 = static_cast<uint>(glm::sqrt(ncells));
    while (ncells % f1 != 0) {
        f1--;
    }
    // f2 > f1
    uint f2 = ncells / f1; // along the width

    uint n_rows = 0;
    uint n_cols = 0;

    // put the larger factor amount of cells on the larger side
    if (boundary.transform.scale.x > boundary.transform.scale.y) {
        n_rows = f1 - 1;
        n_cols = f2 - 1;
    }
    else {
        n_rows = f2 - 1;
        n_cols = f1 - 1;
    }

    Transform cell_t = Transform();
    cell_t.scale.x = boundary.transform.scale.x / n_cols;
    cell_t.scale.y = boundary.transform.scale.y / n_rows;

    // make cell go to the upper left corner
    cell_t.position.x = (-0.5 * boundary.transform.scale.x) + boundary.transform.position.x;
    // + here to make the cell go to the right
    cell_t.position.x += (cell_t.scale.x / 2);

    // - here to make the cell go downwards - opposite of vao coordinate
    cell_t.position.y = (0.5 * boundary.transform.scale.y) + boundary.transform.position.y;
    cell_t.position.y -= (cell_t.scale.y / 2);

    float original_xpos = cell_t.position.x;

    for (uint i = 0; i < n_rows; i++) {
        for (uint j = 0; j < n_cols; j++) {
            cells.push_back(new Cell(cell_t));
            cells.back()->set_fill(false);
            cell_t.position.x += cell_t.scale.x;
        }
        cell_t.position.x = original_xpos;
        cell_t.position.y -= cell_t.scale.y;
    }
}

void Grid::add_to_scene() {
    for (auto& cell : cells) {
        _scene.add_primitive(cell);
    }
}

void Grid::delete_cells() {
    for (uint i = 0; i < cells.size(); i++) {
        _scene.delete_game_object(cells[i]);
    }
    cells.clear();
}

