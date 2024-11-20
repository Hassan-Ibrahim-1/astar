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

Fix stuff with index 0. might be something added with it already?
Look at the commented out code in delete_game_object
Don't crash when something doesn't go right in Scene
Look at the stuff in the add_ functions with the game index checking against -1
all that is bugged

Make it so that the grid can be customized at runtime.
Add mouse clicking on rects to highlight cells (walls).
Implement A*
Lock the camera to make it look 2D?



