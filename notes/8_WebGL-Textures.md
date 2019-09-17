## Computer Graphics
### Review
- so far: how to draw on the surface

### How to color the shapes?
- one method of coloring the objects

- to draw any form on the surface we need the info about:
  * the points
  * they connections (i.e. the interpolation between them)

- another information about the surface is the color in them
  * for each vertex we can associate a color
  * and use interpolation to fill the spaces between them

- how to interpolate?
  * rasterization and ray tracing give us more on that,
  * but for now lets just associate a color for each vertex

- how many vertex will the object need?
  * depends on the form of the object
  * and how colorful is the object (if we associate color with vertexes)

- it's not a common to associate the color with the vertex because of that
  * bc it's not efficiently since simple forms can be colorful

#### Textures
##### Color interpolation
- if we have a color for each vertex
  * we can interpolate those color to fill up the area of the triangle
  * the function to interpolate them will be seen later

- the function that interpolates basically says,
  * for each point in the area of the triangle the function returns a color

##### Wrapping a texture
- the idea is to storage the information of the color in a separated place
  * like a picture of the object surface
  * think it like wrapping a present with a gift paper

- the object and the texture must be compatible
  * we cannot wrap a ball with a box texture, not equally anyway..

- so as the interpolation function 
  * _for each coordinate in the mesh_
  * _we must have a corresponding position in the texture_

- that mapping between texture and mesh is called __texture mapping__
  * for that every point in the mesh must have a _texture coordinate_
  * the texture coordinate uses a different nomenclature
    + for those coordinates (s,t) or (u,v)

- using the _texture coordinates_ for the vertexes of the triangle
  * we use __bilinear interpolation__ for the points inside the triangle
  * Q: but how to define the _texture coordinates_ for the vertexes?

###### Unfolding and mapping
- we can map the 2D texture to the 3D object

- we could also map the 3D object to 2D so it can fit into the 2D texture
  * that is hard, but mathematically is the way to go

- both of those techniques involve __distortion__
  * because of the different dimension mapping

- NOTE: __Tilling__
- the texture can have a high resolution for detailed scenes
  * or could be real small and cyclic for few detailed scenes

- the technique of transforming the 3D mesh to a 2D coordinate system is called __folding__
  * this technique is used to map the 3D mesh into a 2D representation
  * the 2D representation is easy to be mapped into the texture
    + as a real simple technique to make this transformation
    + we could just lose one of the coordinates

- another technique is surround the object with the texture
  * and use the normal vector of each point to assert the color of that point

- NOTE: this surrounding can be as a cylinder or as a sphere

###### Texture Atlas
- is a manually transformation of the 3D object to a 2D representation
  * this is a very handful job and usually is started using another technique
  * this tech also give some distortion

- in many cases the 3D model is divided into pieces
  * so it's easier to create the 2D representation
  * cutting the model into smaller parts converges to a 2D model
    + but we cannot make entirely into 2D pieces
    + bc ... I didn't understand..

###### Encode
- now for each vertex in each triangle encode 2D coordinates (u,v)
- some vertex in different triangle may have different (u,v)

- so we have 3 different buffers:
  * one for the vertexes information
  * one for the association/connection between vertexes
  * one for the texture (do note that the connection in those are the same as before)
