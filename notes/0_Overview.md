## Computer Graphics
### Render
- the whole purpose of the class to **render** something
	* from a description of the object

- _render_: is the process to generate an image with a **description** and an **algorithm** to render it

NOTE: this class is different from computational vision and image processing

##### _Does it runs Crysis?_
- even 10 years later after its lunch, the game can still be used to test qualities

##### Overview of CG for no CC people
- different material will reflect light differently
- calculations are done to simulate that
- done by the shaders
	* have many information about the object light reflection

- GPU is better than CPU for that
- those calculations are done for every pixel (530M for 4K and 60fps)

- those objects that will be render are processed by dividing the object in triangles

##### Overview for CC people
###### GPU vs CPU
- so everything in CG is **a lot** of calculations!

- GPU are used to make lots of calculations in parallel
	* not much synchronization needed, ergo the use of GPUs
	* not that much synchronization because of its main objective, _simulate light_

- CPU has stop growing so quickly recently (lots of reason for that, physical, market, demand, etc)
	* also the CPU is made for complex calculation with lots of controls and synchronization

- but the GPU needs that speed growth, since the GPU is more generic in marketing demand
	* the GPU is used for **massive parallel** algorithms that don't require a lot of synchronization

- so basically while de _GPU calculates "every" pixel at once_ the _CPU would calculate "1-by-1"_ sequentially

- it's very important to remind that the important thing is to _use the right processor for the right task_
	* GPU really suck for sequential calculation and synchronization

```
        CPU model
==========================
|           || ALU | ALU |
|   ctrl    ||-----------|
|           || ALU | ALU |
==========================
|                        |
|         cache          |
|                        |
==========================

              GPU model
===========================================
|   | cache | ALU | ALU | ALU | ALU | ALU |
| c |-------------------------------------|
| o | cache | ALU | ALU | ALU | ALU | ALU |
| n |-------------------------------------|
| t | cache | ALU | ALU | ALU | ALU | ALU |
| r |-------------------------------------|
| o | cache | ALU | ALU | ALU | ALU | ALU |
| l |-------------------------------------|
|   | cache | ALU | ALU | ALU | ALU | ALU |
===========================================
```

###### Scenes can get a lot complex
- every scene should be described with all the details that are important for the scene
	* some scenes from the movie Avatar could take 1.5 days to be render, using GPU!
		+ the same scene take a week!

- so the scene have a different level of details in its description structure

- the GPU needs content to render
	* models
	* colors
	* movement
	* lights
	* ...
- the more information the more details to be calculated

###### How to build model for the objects?
- there are programs used for that
	* can be human made: blender
	* can be scanned from real world with specialized scanners

- so to create a scene everything should be placed and set (properties) using some program
	* this will create a description of that scene in a given structure and will be saved to later processing

- the creative process, although not very influencing for us,

###### Pipeline for a movie
- story: a vision for the movie (the same for everyone working on the movie)
- editorial: build a sequence of the sketches so there is a presentation for the directors and etc
- art: creates the visual of the movie
- **modeling**: build characters and environment that comes from a 2D sketches
	* creates the wireframe of characters and objects
- rigging: uses the modeling to create the movements of objects (place joints and stuff like that)
- **surfacing**: determines the surface of characters and objects on every scene
	* this will influence the light behavior later
- rough layer: create the movie start
- final layer: placing all the stuff created so far in moving scenes
- animation: draw all animation for characters (almost what the actors do)
- crowds: in charge of extras, when there is too much stuff to animate
- character fx: things that move around the characters (clothes, objects in the scene ...)
- matte painting: beyond assets, far mountains and stuff for scenarios
- image cleaning: clean weird stuff on scenes
- sound design: creates the sounds for the movie

###### Render techniques
- we need an algorithm to render the image using the model descriptions
	* rasterization
	* ray-tracing
	* map
	* ...

###### The steps we need to cover for **you** to do something like that
- first the content
	* shape: surface from a real object
	* scene
	* color
	* movement
	* collision

- next, the render
	* simulation of light
	* materials
	* acceleration structures
	* render effects
	* anti-aliasing
	* virtual reality
