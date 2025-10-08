# Shogun Engine
A basic rendering / game engine I made while bored in class during sophmore year of highschool.

## Features:
- 2D and 3D rendering
- Support for using framebuffers on textures
- OBJ file loading
- Ability to sereialize and load serialized scenes
- Support for weird gimmicks such as multiple windows



/lib contains glad, glfw, glm, and freetype

/src/core is where most of the code is, and contains general purpose code for both the player and the engine

/src/editor contains code specific to the editor

/src/player contains code specific to the player

/src/util contains util code for games, such as PerlinNoise, which is a nice to have in the engine APIs, but not required for engine functionality.

/src/editor.cpp compiles into the SHOGUN_EDITOR application

/src/player.cpp compiles into the SHOGUN_PLAYER application
