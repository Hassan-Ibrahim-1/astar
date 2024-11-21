#pragma once

#include "common.hpp"
#include "engine.hpp"

struct Cell : public Rect {
    bool empty = true;

    Cell(Transform transform) : Rect(transform) {}
};

class Grid {
public:
    // NOTE: boundary is never rendered becase it doesn't have to be
    Rect boundary;
    // Probably doesn't have to be heap allocated
    std::vector<Cell*> cells;

    Grid() {}
    Grid(uint ncells) {
        create_cells(ncells);
    }
    ~Grid() {
    }

    void create_cells(uint ncells);
    void add_to_scene();
    void delete_cells();

private:
    // probably not the best way to do this
    Scene& _scene = engine::get_scene();

    uint _cols = 0;
    uint _rows = 0;

    enum Direction {
        NORTH = 0,
        SOUTH,
        EAST,
        WEST,
        NORTH_EAST,
        NORTH_WEST,
        SOUTH_EAST,
        SOUTH_WEST
    };

    std::array<int, 8> _direction_offsets;

    void update_direction_offsets();

    // return -1 if no cell exists
    int cell_north(uint cell_index);
    int cell_south(uint cell_index);
    int cell_east(uint cell_index);
    int cell_west(uint cell_index);
    int cell_north_east(uint cell_index);
    int cell_north_west(uint cell_index);
    int cell_south_east(uint cell_index);
    int cell_south_west(uint cell_index);
};

