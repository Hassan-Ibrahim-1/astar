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
    uint ncells = 1014;
    Grid grid;
    Path path;

    Cell* target_cell = nullptr;
    Cell* start_cell = nullptr;

    float current_time = 0;
    float start_time = 0;
    float time_threshold = 0.02;

    // TODO: get rid of this later. super hacky
    void clear_path_cells();
};

