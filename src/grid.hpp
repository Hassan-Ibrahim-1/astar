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
};

