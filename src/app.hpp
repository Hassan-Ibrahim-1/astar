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

    // Path traversal related stuff
    uint current_cell = 0;
    glm::vec3 capsule_velocity = {};
    std::vector<Cell*> cells;

    // TODO: get rid of this later. super hacky
    void clear_path_cells();
    void update_capsule_path();
    void update_capsule_pos();
};

