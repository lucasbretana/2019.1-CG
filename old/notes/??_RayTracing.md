## Ray Tracing
- one ray of light for each pixel
  +  
	
### Recursive Ray-Tracing
- _so far_ the camera sends a ray of light for each pixel
  + using the lights (direct, reflect, inside light) and the material of the object we can give it color

- for each ray that collides with a point there is a sphere of light reflection
  + this __explodes__ computationally, so we minimize the number of reflection light rays

#### Shadows
- each light contributes to the object color (if it reaches the object)
  + could be occluded by others objects in the scene
  + self-occluding

- the shadow of object can be _hard_ of _soft_
  + if the point to where we are calculating the light is behind another object -> light is 0 __HARD__
  + otherwise calculate normally

- we can also use ambience light to make if a bit better (not so dark in the shadow)
