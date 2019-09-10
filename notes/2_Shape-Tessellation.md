## Computer Graphics
### Review Shape
- so to represent an object in the computer we store samples of the object
	* we store the coordinates of the samples
	* interpolating different points of the model we create lines of connection
	* the connection, thus form a polygon to represent the surface of the object

- when the object is "squared" we can use simple lines to connect the samples
	* we lose no information since the model is "squared"
	* but when talking a more "vivid" object the lines will **lose information**
		+ we should connect the vertexes using curves

- the interpolation of the point is **mandatory** cause otherwise there would be a surface to look at
	* we could use **more and more** points, but is too much memory usage

__NOTE:__ using lines if computational more complex than using lines
	* we can also represent a sphere using just lines, just use **MORE** sampling

### So, again.. after sampling
- to connect samples we can use: __lines__ or __curves__
	* we use lines, is more simple

- witch ones do we connect? (to fulfill the gaps w/ low computational cost)
	* lets say we shall connect only the close ones (within a maximum distance) 
	* we use lines to form an area, so it fills the gaps
		+ lets use a polygon (so there is area), the simplest one __triangle__

- why triangles?
	* simplest polygon
	* we can draw any polygon using triangles
	* has area

- now that everything is connect we only need to ad more samples

__NOTE:__ a sketch of a model with only triangles is called __wireframe__

- wireframe if much used so we can have a 3D perspective of the model

### Curves
- the use of curves is still used to:
	* make stuff that doesn't make much sense to scan from a physic model
	* like a sphere, or would you like to make a sphere vertex by vertex
	* define paths for animation
	* vector graphics, it's much easier to work with curves (control points, but we got the point)
	* change resolution [?]

- so when it will be displayed by the graphic card it's made a conversion to use lines
	* this will be done using a certain LOD for the object

### LOD (Level Of Detail)
- those algorithms are used to minimize computational resources usage
	* they work using a parameter for how well the object is seen for a given camera
	* like, stuff closer it's better represented than far away stuff
	* why not everything at max resolution? too much computer processing

### Homework
- how to determinate which LOD to be used for a given perspective
	* either search for an algorithm of create a rule for that

- check links for the books: both math and intuition
	* Mathematics for 3D Game Programming and Computer Graphics (skeleton one)
	* Fundamentals of Computer Graphics (tiger one)

- check Khan Academy links about how Pixar does something called "subdivision surfaces"

### Defining the LOD
- how to determinate the LOD to use for a given object on the scene?
	* one way, that was very used, is to manually determine it
	* and then make the LOD smaller as the object gets far away from the camera

- but that is impractical as models became larger and more complex
	* also, think about the number of objects in a scene!

- apparently there are three main approaches to manage the LOD
	* discrete: generate a number of objects with different LOD and use them as necessary
		+ closer to camera = higher LOD
		+ those models are generated offline, so no extra cost at runtime
		+ is the _most widely used approach_
	* contiguous: a data structure with a continuous LOD is created
		+ the right LOD is extracted at runtime freeing unneeded polygons
		+ this data structure is generated offline
	* view dependant: the simplification is done by regions of high/low importance
		+ silhouettes and closer to the camera regions are of high importance
		+ the problem is that the cost of simplification if higher than the gain in polygon efficiency


