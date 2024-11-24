#include "engine.hpp"
#include "path.hpp"
#include "grid.hpp"

class App : public Application {
public:
    void init() override;
    void update() override;
    void cleanup() override;

    /*GameObject* obj = new GameObject;*/

    /*Rect& rect = *new Rect;*/
    Rect boundary;
    uint ncells = 513;
    Grid grid;
    Path path;

    Cell* selected_cell = nullptr;
    Cell* start_cell = nullptr;

    // TODO: get rid of this later. super hacky
    void clear_path_cells();
};

