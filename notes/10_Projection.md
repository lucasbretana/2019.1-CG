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

#### World-to-camera transformation
- we first move the camera (and everything else in the world) to the (0,0,0)
  * also we need to set the axis to be over the world axis

- the first part is easy is just the position of the camera minus the (0,0,0)
  * position of the camera uses the axis (u,v,w)
  * the canonical basis is (x,y,z)

#### Construction the View Volume
 - we need 6 things
  * 1) Position
  * 2) Look
  * 3) Up Vector
  * 4) Aspect ratio
  * 5) View angle
  * 6)

##### 1) Position
- where is the camera located with respect to the origin?

- we could use right-hand rule or the left-hand rule
  * WebGL/OpenGL uses right-hand rule
  * _the **z** axis gets bigger coming from the image to the screen_

##### 2) Look & 3) Up Vector

- **Look Vector** where the camera is looking is specified by either
  * a 3D point in space that you're looking at (the **LookAt** point)
  * or, a direction in which you're looking towards (the **look at** vector)
  * the look point is to the wrong direction since we use the right-hand rule

- the camera could be "upside down", so we need an **Up Vector**
  * determines how to camera is rotated around _look vector_
  * note that the Up Vector is not necessarily perpendicular to the _look vector_
    + so we do a small fix for that
  
###### Camera Coordinate System
 - the camera equivalent axis of (x,y,x) are unit vectors (u,v,w)
  * spin in **u** is called _Roll_
  * spin in **v** is called _Yaw_
  * spin in **w** is called _Pitch_

- so to find the (u,v,w) we use two parameters **lookV** and **upV**

- finding **w** is the easy one, since **w** is defined as the opposite of the _look vector_
  * `w = -lookV / |lookV|`
    + we use the minus sign so it points to the right direction
    + and divided by its size so it is unitary

- finding **u**, must be perpendicular to both **v** and **w**
  * but we don't have **v** yet, just the **upV** .. (good enough)
  * so the cross product works `u = upV x w / |upV x w|`
    + note that the order of the operation defines the direction of the resulting vector

- now finding **v** is trivial by using the **w** and **u**
  * `v = u x w / |u x w|`

- now we have the matrix that defines the camera
  * with its position
  * and the its coordinate system

##### First: translation
- using only the camera matrix with its position
  * we can move all the objects in the scene to the camera coordinate system
    + but the are kept not rotate yet

##### Second: rotation
- we can retrieve the position of a matrix by multiplying it by the vector of an axis
  * `M * [1,0,0]` (matrix * x vector)
  * this will get the 

- lets define the `Rxyz2uvw` as the matrix that transfers from (x,y,z) to the (u,v,w)
  * the inverse of this matrix, only because of a set of properties, is its _transpost_
  * so it's very easy to calculate it
    + `transpost(Rxyz2uvw) = Ruvw2xyz`

##### Final Viewing Matrix (aka Camera)
- `V = Rxyz2uvw * T`
  * this matrix can transfer all objects in the scene to the coordinate system of the camera

- next step is to go to the **Projection** coordinate system
  * this one is the monitor/screen system, _is 2D_

**NOTE:** _WE DO NOT ACCTUALLY PROGRAM THIS PART, THIS ALWAYS THE SAME, SO IT'S DONE IN THE CODE_
