## Rasterization
- **NOTE:** so far we have the vertex in a 2D space, still being vectorial
  + can be mapped to any screen resolution easily

- the screen is discrete, a grid of pixels
  + a pixel is set on/off only
  + __no color__ yet

- rasterization = selecting the pixels
  + will be done frequently, so must be fast
    * integer arithmetics, additions instead of multiplication

### Interpolation
- each vertex have a bunch of attributes
  + position, color, normal, ....

- between two vertex attributes, from the same object, we make interpolation
  + this is used to fill the space between the points
  + the vertex have connection and the space left if filled with the interpolation values
    * **note:** this is easy to see if we think about color interpolation
TODO: add triangle image of the color interpolation

**NOTE**: using the right interpolation for the right object can spare the use of vertex, therefore being easier to process 

#### Bresenham's algorithm
- real quick algorithm to simply draw a line

- pre-conditions:
  + delX > delY
  + X0 < X1
  + Y0 <= Y1
  + -1 < slope < 0

- if those conditions are not true, we make some swap that grant those conditions

- **NOTE:** we call those pixels _fragment_, because they may be draw on the screen
  + they may not be draw because another fragment may be in its front

- _bilinear_ interpolation is used to fill the interior of an object
  + it uses the same Bresenham algorithm

- TODO generalizing
