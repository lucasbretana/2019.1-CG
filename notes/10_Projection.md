## Computer graphics
### Projection
- now we shall talk about camera perspective

- the early techniques were very crud and follow no algorithm
  * there was a method that didn't use a point of view
    + called __parallel perspective__

### Two classes of planar geometric projections
- **perspective**: determined by center of projection (eye or COP)
  * in this class we experience distortion when showing a 3D model
  * that all depends on how the object is positioned, of course
    + think about the size a finger in various position in to a screen

- **parallel**: determined by the direction of projection (DOP)
  * projectors are parallel, do not converge to the "eye"
  * alternatively the _COP is at the infinite_
  * the parallel was the first the humanity discover
    + it's much more easier

- NOTE: but both of those have many subdivisions

### Overview of Parallel Projection
- in some cases we can lose information in other we may not
  * multiview orthographic> very used for CAD software
    + but usually uses more than one view
  * axonometric
  * oblique

### Overview of Perspective Projection
- publish first in the XV century

- it's used for human visual system
  * gives a realistic view and feeling for a 3D form of object
  * but do not preserve the shape of objects, or its scale

- vanishing point
  * the point where the camera shall stay
  * everything vanishes here, like a black hole

### Camera
#### Defining the Volume Frustrum
- **clipping**: it's the method of cutting out objects that aren't relevant to the scene
  * such as thing that stays in the back of the camera, therefore aren't seen

- for now we shall not talk much about it

#### Positioning
- **first**: positioning and orientation of the camera

- **next**: we will see projection
  * this step can be done with different algorithms

- NOTE: both of those uses the transformation we have seen before

- the camera is like another model in the scene
  * think of that like moving the camera to the right is
  * basically the same as moving all model to the left
    + so model transform and view transform are inverse of each other
  * in OpenGL we move the world and the camera still

#### Camera as a basis
- we need to position everything in relation to the camera
  * otherwise every model would stay one stacked upon each other

- model -> world -> camera -> projection
  * that's the workflow of transformation of objects positioning
  * model -> world: we already did, to position the object in the scene
