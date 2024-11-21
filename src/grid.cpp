#include "grid.hpp"

void Grid::create_cells(uint ncells) {
    delete_cells();

    uint f1 = static_cast<uint>(glm::sqrt(ncells));
    while (ncells % f1 != 0) {
        f1--;
    }
    // f2 > f1
    uint f2 = ncells / f1; // along the width

    _rows = 0;
    _cols = 0;

    update_direction_offsets();

    // put the larger factor amount of cells on the larger side
    if (boundary.transform.scale.x > boundary.transform.scale.y) {
        _rows = f1 - 1;
        _cols = f2 - 1;
    }
    else {
        _rows = f2 - 1;
        _cols = f1 - 1;
    }

    Transform cell_t = Transform();
    cell_t.scale.x = boundary.transform.scale.x / _cols;
    cell_t.scale.y = boundary.transform.scale.y / _rows;

    // make cell go to the upper left corner
    cell_t.position.x = (-0.5 * boundary.transform.scale.x) + boundary.transform.position.x;
    // + here to make the cell go to the right
    cell_t.position.x += (cell_t.scale.x / 2);

    // - here to make the cell go downwards - opposite of vao coordinate
    cell_t.position.y = (0.5 * boundary.transform.scale.y) + boundary.transform.position.y;
    cell_t.position.y -= (cell_t.scale.y / 2);

    float original_xpos = cell_t.position.x;

    for (uint i = 0; i < _rows; i++) {
        for (uint j = 0; j < _cols; j++) {
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

void Grid::update_direction_offsets() {
    _direction_offsets[NORTH] = -_cols;
    _direction_offsets[SOUTH] = _cols;
    _direction_offsets[NORTH_EAST] = -_cols + 1;
    _direction_offsets[NORTH_WEST] = -_cols - 1;
    _direction_offsets[SOUTH_EAST] = _cols + 1;
    _direction_offsets[SOUTH_WEST] = _cols - 1;
}

/*uint Grid::n_cell_neighbours(uint cell_index) {*/
/*    uint count = 0;*/
/*    if (cell_north(cell_index) != -1) {*/
/*        if (cells[cell_north(cell_index)].fill) {*/
/*            count++;*/
/*        }*/
/*    }*/
/*    if (cell_south(cell_index) != -1) {*/
/*        if (cells[cell_south(cell_index)].fill) {*/
/*            count++;*/
/*        }*/
/*    }*/
/*    if (cell_east(cell_index) != -1) {*/
/*        if (cells[cell_east(cell_index)].fill) {*/
/*            count++;*/
/*        }*/
/*    }*/
/*    if (cell_west(cell_index) != -1) {*/
/*        if (cells[cell_west(cell_index)].fill) {*/
/*            count++;*/
/*        }*/
/*    }*/
/*    if (cell_north_east(cell_index) != -1) {*/
/*        if (cells[cell_north_east(cell_index)].fill) {*/
/*            count++;*/
/*        }*/
/*    }*/
/*    if (cell_north_west(cell_index) != -1) {*/
/*        if (cells[cell_north_west(cell_index)].fill) {*/
/*            count++;*/
/*        }*/
/*    }*/
/*    if (cell_south_east(cell_index) != -1) {*/
/*        if (cells[cell_south_east(cell_index)].fill) {*/
/*            count++;*/
/*        }*/
/*    }*/
/*    if (cell_south_west(cell_index) != -1) {*/
/*        if (cells[cell_south_west(cell_index)].fill) {*/
/*            count++;*/
/*        }*/
/*    }*/
/**/
/*    return count;*/
/*}*/

int Grid::cell_north(uint cell_index) {
    uint index = cell_index + _direction_offsets[NORTH];
    if (index < 0 || index >= cells.size()) {
        return -1;
    }
    return index;
}
int Grid::cell_south(uint cell_index) {
    uint index = cell_index + _direction_offsets[SOUTH];
    if (index < 0 || index >= cells.size()) {
        return -1;
    }
    return index;
}
int Grid::cell_east(uint cell_index) {
    uint index = cell_index + _direction_offsets[EAST];
    if (index < 0 || index >= cells.size()) {
        return -1;
    }
    return index;
}
int Grid::cell_west(uint cell_index) {
    uint index = cell_index + _direction_offsets[WEST];
    if (index < 0 || index >= cells.size()) {
        return -1;
    }
    return index;
}

int Grid::cell_north_east(uint cell_index) {
    uint index = cell_index + _direction_offsets[NORTH_EAST];
    if (index < 0 || index >= cells.size()) {
        return -1;
    }
    return index;
}
int Grid::cell_north_west(uint cell_index) {
    uint index = cell_index + _direction_offsets[NORTH_WEST];
    if (index < 0 || index >= cells.size()) {
        return -1;
    }
    return index;
}
int Grid::cell_south_east(uint cell_index) {
    uint index = cell_index + _direction_offsets[SOUTH_EAST];
    if (index < 0 || index >= cells.size()) {
        return -1;
    }
    return index;
}
int Grid::cell_south_west(uint cell_index) {
    uint index = cell_index + _direction_offsets[SOUTH_WEST];
    if (index < 0 || index >= cells.size()) {
        return -1;
    }
    return index;
}

