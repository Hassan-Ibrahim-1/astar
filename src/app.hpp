#include "engine.hpp"
#include "path.hpp"
#include "grid.hpp"

class App : public Application {
public:
    void init() override;
    void update() override;
    void cleanup() override;

    Rect boundary;
    uint ncells = 675;
    Grid grid;
    Path path;

    Cell* target_cell = nullptr;
    Cell* start_cell = nullptr;

    Model capsule_model;
    GameObject& capsule = *new GameObject;

    PointLight& light = *new PointLight;

    // TODO: get rid of this later. super hacky
    void clear_path_cells();
};

