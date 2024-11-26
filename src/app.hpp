#include "engine.hpp"
#include "path.hpp"
#include "grid.hpp"

class App : public Application {
public:
    void init() override;
    void update() override;
    void cleanup() override;

    uint ncells = 675;
    Grid grid;
    Path path;
    Cell* target_cell = nullptr;
    Cell* start_cell = nullptr;

    PointLight& light = *new PointLight;
    Model capsule_model;
    GameObject& capsule = *new GameObject;
    Cube& cube = *new Cube;
    Cube& end_point = *new Cube;

    Rect& rect = *new Rect;

    // TODO: get rid of this later. super hacky
    void clear_path_cells();
};

