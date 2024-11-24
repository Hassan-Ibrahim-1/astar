#include "path.hpp"

void Path::trace(Cell* start_cell, Cell* target_cell, Grid& grid) {
    this->start = start_cell;
    this->target = target_cell;

    // Create path nodes with h costs already calculated
    uint start_index = -1;
    uint target_index = -1;
    for (size_t i = 0; i < grid.cell_count(); i++) {
        if (grid.cells[i] == start) {
            start_index = i;
        }
        if (grid.cells[i] == target) {
            target_index = i;
        }
        PathNode node;
        node.cell_index = i;
        node.h = cost(grid.cells[node.cell_index], target);
        _path_nodes.emplace_back(node);
    }

    PathNode& start_node = _path_nodes[start_index];
    start_node.g = 0;
    start_node.h = calculate_distance_to_target(grid.cells[start_node.cell_index]);
    start_node.f = start_node.g + start_node.h;
    _open.emplace_back(&start_node);

    PathNode* current = nullptr;
    while (!_open.empty()) {
        current = lowest_cost_open_node();
        _open.erase(_open.begin() + open_node_index(*current));
        _closed.emplace_back(current);

        if (current->cell_index == target_index) {
            break;
        }

        auto neighbours = grid.get_neighbours(current->cell_index);
        for (uint neighbour : neighbours) {
            PathNode& node = _path_nodes[neighbour];
            // NOTE: Check if traversable here
            if (node_in_closed(node)) {
                continue;
            }
            auto tmp_parent = node.parent_index;
            node.parent_index = current->cell_index;
            float new_g = calculate_distance_from_start(node, grid);
            node.parent_index = tmp_parent;
            float new_f = node.h + new_g;

            // if not in open - add it there and remove from closed
            if (new_f < node.f || !(node_in_open(node))) {
                node.g = new_g;
                node.f = new_f;
                node.parent_index = current->cell_index;
                if (node_in_closed(node)) {
                    _closed.erase(_closed.begin() + closed_node_index(node));
                }
                if (!node_in_open(node)) {
                    _open.emplace_back(&node);
                }
            }
        }
    }
    int index = _path_nodes[target_index].parent_index;
    while (index != start_index) {
        PathNode& node = _path_nodes[index];
        grid.cells[node.cell_index]->set_fill(true);
        grid.cells[node.cell_index]->material.color = Color(255, 0, 0);
        index = node.parent_index;
    }
}

float Path::calculate_distance_to_target(Cell* cell) {
    return cost(cell, target);
}

float Path::calculate_distance_from_start(PathNode& node, const Grid& grid) {
    // if start node. i think?
    if (node.parent_index == -1) {
        LOG("no parent");
        return 0;
    }

    float dist_to_parent = glm::distance(
        grid.cells[node.cell_index]->transform.position,
        grid.cells[node.parent_index]->transform.position
    );
    return abs(dist_to_parent) + _path_nodes[node.parent_index].g;
}

float Path::cost(const Cell* current, const Cell* target) {
    return abs(
        glm::distance(target->transform.position, current->transform.position)
    );
}

Path::PathNode* Path::lowest_cost_open_node() {
    ASSERT(!_open.empty(), "open is empty");
    if (_open.empty()) return nullptr;
    PathNode* lowest_cost_node = _open.front();
    for (auto node : _open) {
        // least f cost or least h cost if equal f costs
        if (node->f < lowest_cost_node->f
         || (node->f == lowest_cost_node->f && node->h < lowest_cost_node->h)) {
            lowest_cost_node = node;
        }
    }
    return lowest_cost_node;
}

bool Path::node_in_open(PathNode& node) {
    return std::find(_open.begin(), _open.end(), &node) != _open.end();
}

bool Path::node_in_closed(PathNode& node) {
    return std::find(_closed.begin(), _closed.end(), &node) != _closed.end();
}

size_t Path::open_node_index(PathNode& node) {
    return std::find(_open.begin(), _open.end(), &node) - _open.begin();
}
size_t Path::closed_node_index(PathNode& node) {
    return std::find(_closed.begin(), _closed.end(), &node) - _closed.begin();
}

