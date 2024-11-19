#include "engine.hpp"
#include "game_object.hpp"

class App : public Application {
public:
    void init() override;
    void update() override;
    void cleanup() override;

    GameObject* obj = new GameObject;
    Rect& rect = *new Rect;
};

