#pragma once

#include "common.hpp"
#include "scene.hpp"

struct Cell : public Rect {
    bool empty = true;

    Cell() {}
};

struct Grid {
    Rect boundary;
    std::vector<Cell> cells;

    Grid(uint ncells) {
        create_cells(ncells);
    }

    void create_cells(uint ncells);
    void add_to_scene(Scene& scene);
};

