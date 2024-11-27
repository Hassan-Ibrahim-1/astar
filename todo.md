# TODO
basic level
ability to load and save state
draw a path -> generate vertices to make the path look smooth
first test using a basic grid

-- figure out how to deal with deleting rects
-- just clear all of them out?

-- add a delete game object function in Scene figure out if this frees
-- or not? it does free

-- Ability to fill and unfill rects

now that there are ids. can check if something with that id has been added
before to prevent multiples of the exact same game object

Lights currently don't have ids

Kind of fixed. hacky way in engine.cpp
 -- Front is always set to 1, 0, 0
 -- camera is rotated at 0,0 probably some recent change that broke this.
 -- x and z are flipped?

# 2D demo

-- Fix stuff with index 0. might be something added with it already?
-- Look at the commented out code in delete_game_object
-- Don't crash when something doesn't go right in Scene
-- Look at the stuff in the add_ functions with the game index checking against -1
-- all that is bugged

-- Make it so that the grid can be customized at runtime.
-- Lock the camera to make it look 2D?
-- Add mouse clicking on rects to highlight cells (walls).

Make it so that cells can be stored using x and y
Maybe just store cols and rows?
 - might not have to if i just use position data

Implement A*

f(n) = g(n) + h(n)

n is the current node
g(n) is the cost of getting to the current node from the start node
    calculate this by adding all previous g(n) values
h(n) is the estimated cost of getting to the destination node from the 
current node.
    maybe calculate this by just getting the distance to destination
    from the current node? won't account for walls though

Choose the path with the lowest f(n)

-- Find neighbouring cells

Ideas on how to store path:
    just a simple vector of Cell* nodes
    Path class that stores a vector of Cell* nodes. stores a start and end node as well


# TODO NEXT
Fix the bug where clicking too far from start just crashses everything

-- Boundary checking doesn't seem to be working. Try drawing a horizontal
-- line blocking the start and target cells. there's still a path that's possible
-- Probably something to do with diagonals

-- Do at least on demo of the algorithm. render each step.
-- Use a time step maybe? do one bit at a time. click based?
-- Make an animation with the paths joining up as well

3d movement. a capsule moving around on ground that can handle obstacles as well.
start and end points
figure out how to automatically detect a cube in the way for example.
    - vector of cubes passes into a function. read their x and z coordinates and map
      them to their grid cell.

ignore the y component;

-- create a grid using the size of the ground.


The way obstacles are handled is dumb. if the target moves over them they disappear but are still
not traversable. 


# THIS NEXT 
If the capsule is moved out of the grid, it still keeps moving
even though theres a check that sets velocity to 0 when its supposed to 
be out of the grid. find_cells seems to be returning something even
when it isn't supposed to. might be point_in_rect. have to check

find_cell does not work returns cells that are closer to the center

# DO THIS LATER
FIX ROTATION - use x,y,z instead of yaw pitch and roll

