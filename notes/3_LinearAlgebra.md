### Base change
#### Motivation
- objects in OpenGL have different coordinate systems (or base)
  * usually the center of the object is the origin

- modeling
  * place an object
  * size
  * view it from different angles

- animation

- each basis has a purpose
  * model -> world -> camera -> projection

- changing the base from __model__ to __world__ makes the object motion relative to the scene

#### Transformation
- transformations 2D & 3D
  * translation
  * rotation

- a transformation __maps__ points to other points and/or vectors to other vectors
  * v = T(u)


##### Pipeline Implementation (include pic. _Current GPU Graphics Pipeline_)
- on the pipeline transformation all the transformation are done previous from the rasterizer
  * .... -> transformation -> rasterizer -> .... -> frame buffer

- u -> transformation -> T(u) -> rasterizer -> frame buffer
          |
          T (from application)

- the pipeline is made of parts that are fixed and some are programmable
  * the fixes: everybody uses them as they are, and are used by different application (e.g. medic and graphic)
  * the programmable: can be changed by every application

- besides that, some parts are not _mandatory_ to be used, e.g.
  * tessellation
  * geometry

###### Simplification of the pipeline process
- everything start with the vertexes (e.g. from blender)
  * known as ...

- then they're transformed using some function (e.g. T(x))

- rasterization connect the dots and creates the polygons

- the fragment program is responsible to paint the objects

##### Translation: vertex
- a transformation that moves the object needs:
  * the variation rate (distance between the points)
  * the direction of the movement

__NOTE__: a point plus a vector equals to move the point in the direction of the vector and the distance equals the vector size
  * vector + vector = vector
  * point  + vector = point
  _ point  - point  = vector

##### Translation: mesh
- once we have the transformation matrix we can apply that same transformation to a full mesh

- properties:
  * angles are preserved
  * edge length is preserved

##### Scale
- the scale an object is simply a multiplication for the scale itself
  * to make a proportional scale multiply per a scalar
  * to changed differently uses a vector with different scales

- properties:
  * angles are preserved only if is proportional
  * the edge lengths is not preserved

##### Rotation
- uses trigonometric functions to rotate the object __in a fixed axis__
  * the matrix for the transformation is different for each fixed axis

- properties:
  * angles are preserved
  * edge length is preserved

##### Inverses
- used to invert the operation
  * Translation: T'(x,y,z) = T(-x,-y,-z)
  * Rotation: T'(teta) = T(-teta)
  * Scale: T'(x,y,z) = T(-x,-y,-z)

##### Transformations properties
- affine: preserve ratio of ares
  * translation, rotation, non-uniform/uniform scaling, shearing
- conformal: preserve angles
  * translation, rotation, uniform scaling
- isometric: preserve length
  * transformation, rotation

##### Concatenation
- we can simplify the process by multiplying the matrices, 
  * resulting in a single matrix that makes all the transformation at once

- do __note__ the order of the operation is important
  * A . B != B . A    (where A n' B are matrices)

##### Normal Transformation
- on the normal vector is applied a different transformation
  * e.g. in a scale, if we apply the same transformation on the normal vector it will stop being normal

