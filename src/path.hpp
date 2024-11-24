#pragma once

#include "grid.hpp"

class Path {
public:

    Cell* start;
    Cell* target;

    void trace(Cell* start, Cell* end, Grid& grid);

private:
    struct PathNode {
        int cell_index = -1;
        int parent_index = -1;
        // Cost from starting node to current node
        float g;
        // Estimated cost from current to destination
        float h;
        // Sum of g and h
        float f;

        PathNode() {}
    };

    std::vector<PathNode> _path_nodes;
    std::vector<PathNode*> _open;
    std::vector<PathNode*> _closed;
    /*std::unordered_map<> _closed;*/

    // TODO: figure out how to store the cost of getting to the start

    float calculate_distance_to_target(Cell* cell);
    float calculate_distance_from_start(PathNode& node, const Grid& grid);
    float cost(const Cell* current, const Cell* target);
    // TODO: change this to std::array<Cell*, 8>
    PathNode* lowest_cost_open_node();

    // _open and _closed helper functions
    bool node_in_open(PathNode& node);
    bool node_in_closed(PathNode& node);
    size_t open_node_index(PathNode& node);
    size_t closed_node_index(PathNode& node);
};

