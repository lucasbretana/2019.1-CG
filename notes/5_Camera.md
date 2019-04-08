## Cameras
- from where on the scene we're observing
  + the idea is to transform a 3D scene into a 2D representation

- two main methods to draw:
  + rasterisation,
  + ray tracing	

- plan view: said to be _parallel_, in which the proportion is maintained, 
  + this is **not** how we see stuff, tho
  + another way of saying is that the center of projection is at infinite

- _perpective_ is how we see the reality
  + determined by center of projection, usually the eye

__NOTE:__ there are a lot of others types of projections, basically they're all subsets of the two main ones

### Multi View Orthographic
- used for: engineer drawing of machines, architectural drawings, ...
  + software usually use more than one view

- pros: accurate measurements, all view at same scale, 
- cons: not a realistic view or sense of 3D

- usually need multiple view to get a 3D feeling for the object

### Perspective
- used for: human visual systems

- pros: gives a realistic 3D view
- cons: doesn't preserve shapes or scale

__NOTE:__ there are many different perspectives, we maintain at the single point of vanishing

## Camera: Frustum
- view frustum: aka, view volume
  + a set of information about the scene

- view plane: 

- view point: 

### Camera positioning
- important info given at projection time: 
  + camera position and orientation, 
  + and projection (transforms a 3D scene to a 2D image)
    * depends on the methods used as well
__note:__ uses transformation

- we use the camera as a basis
  + so the offset (x,y,z) of the objects are now in relation to the camera itself
  + it's a basis change

## World-2-Camera Transform
- aka: World-2-Eye transform

- the idea is to create a matrix such that we make the camera
  + 1) the to the origin of the World Coordinate (__canonical basis__)
  + 2) rotate to align, becoming the canonical basis

- the canonical basis is centered at (0,0,0) and have perpendicular axis

- transformation matrix: a mapping between the coordination systems

### Construction of the View Volume
- __Position__ of the camera: where the camera is located with respect to the origin
  + we use the _right handed_ coordinate system

- __Look__ vector: direction
  + specifies the direction we're looking towards
  + this can be given by a __point in space__ (Look At point), or a look vector
  + __FIX__ we need to make it unitary

- __Up__ vector: no ambiguity between the camera orientation
  + cannot be parallel to the look vector
  + but it doesn't need to be perpendicular
  + __FIX__ we need to make it perpendicular

- __Aspect ration__: relation between weight and width
- __View angle__: how wide the frustum will be
- __Clipping planes__: limits and extends of the camera's view


### Camera Basis (u,v,w)
#### Finding u,v,w
- given the two parameters lookV and upV

```
- finding W = -lookV/|lookV|

- finding U = upV x W/|upV x W|
```
