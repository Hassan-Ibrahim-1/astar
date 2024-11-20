#include "engine.hpp"
#include "grid.hpp"

class App : public Application {
public:
    void init() override;
    void update() override;
    void cleanup() override;

    /*GameObject* obj = new GameObject;*/

    /*Rect& rect = *new Rect;*/
    Rect boundary;
    uint ncells = 100;
    Grid grid;
};

