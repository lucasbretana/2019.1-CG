## WebGL - WebGL2 2d Translation
- now that we now how to display stuff,
	* we will move things around in the screen

### Drawing on the screen
- in JS we draw as it was from (0,0)
	* top left -> bottom right

- in the OpenGL system the coordinates are from (-1,-1) to (+1,+1)
	* inside the vertex shader we convert it by
	* from bottom left -> top right
		+ getting the position / resolution
		+ multuply it by 2 (0,1) -> (0,2), subtract 1 (0,2) -> (-1,+1)

- the vertex shader is the first to run
	* it runs once for every vertex in the triangle
	* for our rectangle sample we run it six times (even if some are the same)

### GLSL
- language used to write the vertex shaders
	* have many types and functions to deal with colors ans vectors

- vertex shader have mandatory input and output memory
	* output: ```gl_Position```
	* input:  (no sure what is the mandatory one)


### Homework
- do all the 2d Translation part of the tutorial

**NOTE**: last class was about the previous part of the tutorial
