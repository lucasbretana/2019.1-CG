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
  * 6) Near and Far Clipping Planes

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

##### 4) Aspect ratio
- ...

##### 5) View angle
- ...

##### 6) Near and Far Clipping Planes
- we want to see an image, for that we project the objects in the scene to the **near clip plane**
  * too close: occupies the entire scene
  * too far: we won't see thing that are too close

- the **far clipping plane** serves two purposes:
  * to avoid unnecessary computation
  * precision, we cannot represent with full precision an arbitrary length of space
    + map 100 cm to 0 -> 1 may be easy
    + map 10M km to 0 -> 1 might not be to easy

- the computer has an fixed precision, but let's say it goes from [0.0 -> 1.0]
  * if we want to map 100 cm to this machine, every step (0.1) is equivalent to 10 cm
  * if we want to map 10M km to this machine, every step (0.1) is equivalent to 1M km
    + everything in between two steps will be "truncated" to a small/bigger one (like using floor of ceiling functions)

##### Projection: 3D to 2D
- basically how to draw the shadow of an object
  * this is using the _rasterization_ technique

- there is two ways of doing this:
  * one for the **perpective** view: which have a "pyramid" view volume
  * one for the **parallel** view: which have a "cubic" view volume (actually a parallelepiped)

##### Parallel View Volume
- NOTE: out model has limitations, but is good enough to get us the intuition
  * we use only the  ..

- so, to make the 2D view from the 3D world we need to "smash the scene to **near plane**"
  * there is no descretization in this process, we only loose the 3D information part
  * everything is still vectors and points, only in the 2D world

- NOTE: every frame the unused information (3D stuff) is discarded and redraw in 2D form

##### Parallel Projection
- **so far we**: translate objects to origin and rotate the axis

- **now we need to**: normalize everything to a common base (between 0 and 1) and convert the 3D information to a 2D view
  * this make it easy for computing
  * like defining what goes inside/outside of the clipping area
  * normalize things make it possible to create dedicated HW for that
  * we can compute stuff without thinking about resolution

- **Canonical Parallel View Volume**
  * near plane is at 0
  * far plane if at 1
  * look vector (0, 0, -1)
  * up vector (0, 1, 0)
**NOTE**: this does not exists, is represented inside of the matrix that we shall define now
  * it just defines what goes inside/outside the view volume

- when we multiply the objects, that are in the world scale, we transfer them to the normalized view
  * x' = 2\*x / width
  * y' = 2\*y / height
  * z' = z / far

- we can now put those formulas into a matrix (as its principal diagonal)
  * and every point multiplied by this matrix is the same thing as calculate the x, y, x separately
  * the idea is to use a matrix so we can combine all of them into a single one

- now we also need to drop the 3D axis information so we can project it in a 2D screen, for instance
  * this only works because we put everything into the view of the camera
  * otherwise everything else would project to the world view, and vanish in some point

- and at least, in a matrix form, we just use a 0 to loose the **z** information of the objects

**NOTE:** _WE DO NOT ACCTUALLY PROGRAM THIS PART, THIS ALWAYS THE SAME, SO IT'S DONE IN THE CODE_

**NOTE:** for the perspective view thing are not that easy, since we cannot just loose the **Z** information
  * that is because we have an angle with the near plane

## Camera, the overview
- we have many object that comes from a scanner

- those object don't have a world, they are in their own coordinate system

- now every object is put in a common world coordinate system
  * so they're not in the same position

- once that's done we put them in the camera coordinate system

- and now we finally put them in the same normalized coordinate system
