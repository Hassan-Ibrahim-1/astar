#pragma once

#include "common.hpp"
#include "engine.hpp"

struct Cell : public Rect {
    bool empty = true;

    Cell(Transform transform) : Rect(transform) {}
};

class Grid {
public:
    Rect& boundary = *new Rect;
    // Probably doesn't have to be heap allocated
    std::vector<Cell*> cells;

    Grid() {}
    Grid(uint ncells) {
        create_cells(ncells);
    }
    ~Grid() {
        // I think scene deletes this automatically
        /*delete_cells();*/
        /*if (_boundary_in_scene) {*/
        /*    _scene.delete_game_object(&boundary);*/
        /*}*/
    }

    void create_cells(uint ncells);
    void add_to_scene();
    void delete_cells();

private:
    // probably not the best way to do this
    Scene& _scene = engine::get_scene();
    bool _boundary_in_scene = false;
};

