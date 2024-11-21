#include "grid.hpp"

struct Path {
    Cell* start;
    Cell* end;
    // Includes the end node.
    std::vector<Cell*> nodes;
};

