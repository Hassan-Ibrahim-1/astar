# TODO
basic level
ability to load and save state
draw a path -> generate vertices to make the path look smooth
first test using a basic grid

figure out how to deal with deleting rects
just clear all of them out?

assign a uuid to a game object on creation
scene assigns the uuid when calling create or add

use that to find the game object in Scene::game_objects
then just delete that game object from the list. free it? idk

now that there are ids. can check if something with that id has been added
before to prevent multiples of the exact same game object

Lights currently don't have ids

