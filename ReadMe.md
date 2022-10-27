Very major WIP for a game engine, right now it is just a poopy renderer.

/lib contains glad, glfw, and glm

/src/core is where most of the code is, and contains general purpose code for both the player and the engine

/src/editor contains code specific to the editor

/src/player contains code specific to the player

/src/util contains util code for games, such as PerlinNoise, which is a nice to have in the engine APIs, but not required for engine functionality.

/src/editor.cpp compiles into the SHOGUN_EDITOR application

/src/player.cpp compiles into the SHOGUN_PLAYER application
