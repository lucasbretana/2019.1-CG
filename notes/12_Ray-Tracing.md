## Ray Tracing

Is a method for defining the light of every point in the scene, like rasterization
In this approach we simulate how light actually works, by _path finding_ the trace of the light from the source til the camera
- in practice, we do the other way around:
  * camera ray >> objects.. >> source light
  * we do it like that so we won't calculate rays that don't shows up in the camera
	
The way the computer calculates those rays is using the GPU model, by calculating the path for many traces at once
- the _many cores_ or _massive parallel_ computing

### Ray Tracer

Is a mapping of rays from the camera through each pixel to the points in the actual scene 
**NOTE**: using ray trace with a single ray give us the same result as the rasterization technique

The three main parts to a **ray tracer**:
- Generating rays:
  * the rays must be generated for every frame

- Ray-Object intersection
  * how to determine if a ray hit something

- Calculate lighting:
  * for every ray hit the light must be calculated using either _local_ or _global_ illumination

**Q:** _how to determinate if the ray pass through the object?_
**A:** ..

### Generating rays

**Q:** _how to generate the rays?_
**A:** we have information about camera position, near plane, distance between them, direction...
Using that, we create _a line that_ comes from the camera, pass through the pixel of interest and goes all the way to infinity, hitting objects in its way, therefore giving us the colors to fulfill
Afterwards we modify it slightly so it goes from the same camera position, to a neighbor pixel and through the entire scene again

Now for every hit we have a **t**, i.e., _the distance from the camera to the hit point_
We then store only the ones of interest, i.e., the smaller ones, those are gonna actually be showed in the screen

### Recursive Ray Tracing

It's the same idea but in this case for every hit the ray keeps going and hits others objects in the scene, i.e., reflecting the light
This leaves us with an enormous amount of rays to calculate, so one good strategy it specify how many ray will reflect
A common method is to generate something like 3 rays
- one for each light source (consider a scenario where there are only 2)
- plus one for the closest neighbor object
