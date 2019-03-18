## Computer Graphics
### Graphic Pipeline
- lets build up the ground rules  
- the final ideia is to build to an __image__ 

- the pipeline is a path to be followed by pixels
- an algorithm with data will reveal an image
  * scene description -> algorithm -> image
    + a scene is basically a bunch of arrays

- this discipline is to study:
  * how to describe the image
  * the algorithms to

#### Render Overview
- choose the color for each pixel
  * and changed accordingly to the light (by the algorithm)

- __how to describe a scene?__
  * lots of data: all the objects, the camera position, the light source, the image position, shadows .....

##### Common ways to describe an object
__NOTE__: it's not always necessary to describe the insides of an object
- _Triangle Mesh_: uses triangles... __surface only__
- _Quad Mesh_: ...__surface only__

- _Volume_: used to describe the whole object
  * e.g. a cat scan, physics simulations..

- many other ways to do it...

##### Triangle Mesh 2D
- __how to describe a circle?__
- discretization
- connection

__NOTE__: _Riemann touch_, when an algorithm gets better with more precision

- the circle can be divied into N (8) parts, and have a somewhat good aproximation
  * Riemann touch

- __why triangles?__
  * the polygon with less vertex and area
  * always planar
  * can represent any other polygon

- can be used to 3D representations as well

#### Resolution
- to make the conversion from a real image to its representation we can use a digital scanner
- those scanner uses the highest resolution possible

- LOD: Level Of Details, how accurate the representation will be
  * differents LODs can be used to distant objects
- distant objects use coarse LODs

- there is a Error x Size correlation with the resolution of the objects

- a few techniquies to change the image resolution can be used
  * when creating/deleting a vertex the other can slowly converge to fill that or do it instantly

##### Vertex Removal
- doing the smooth transition is computer heavy
- is it better to use the original? <- __a important question__

- overview
  * 1. select a vertex to remove (priority queue)
  * 2. remove it
  * 3. re-triangulate the hole, it can be done smoothly or abruptly

- using the right order to insert the points makes it quickly to "understamd" what is on the image
- __what is the right/best order to insert the vertex?__
- not removing vertex on a curve, or on the borders ....

- lodbook.com

#### The Origin
- the description of each vertex is its coordinates
- those coordinates indicates the distance on each axis from a reference point, the __Origin__

#### Tranformations
- are bassically modification on the object description
- such as moving the object is just changing its distance from the origin

#### Surface vs Light vs Color
- from the surface description, we apply the light and the apply the color
- many differents algorithms are used to do it
