## Projections
__NOTE:__ this matrix doesn't exists on the _ray tracing_ methods, only on the _rasterization_

- (4.) Aspect Ratio
  + how wide the camera see

- (5.) View Angle	
  + distortion
  + specific for the perspective
    * since in the parallel projection this angle is always parallel

- (6.) Near/Far Clipping Panes
  + how far the camera sees
  + in the parallel projection the object is always seen
**NOTE:** putting an object far so it wont be render is hard
  + the near pane is important so the objects wont converge to a single point
    * thus limiting the whole view to a single color
    * the objects get more distortion when closer

### Projection: 3D to 2D
#### Parallel View Volume
- we have focused on perspective transform
  + but the same concepts apply to parallel view volume

- the parallel view has no _view angle_
  + instead of aspect ratio + view angle
  + we need width + height

**NOTE:** this model have limitations, works only for non-oblique perspective
  + the general model uses a "windows view"

- the technique is to project the vertex into the 2D view
  + since we don't see points, we need lines
  + we use the information of the edges to connect the dots

#### 
- first thing we need to do is to normalize the view volume to canonical one

##### The Normalization Transformation
- one of the reasons is to make optimization in a default volume
  + made in hardware
  + independent from resolution

- the conversion to the canonical volume is considering half of a block
  + 1 > x|y > -1
  +  1 > z > 0
    * near plane Z = 0
    * far plane Z = -1

- [FIX] add matrix notes
