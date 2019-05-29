## Light simulation
- the kitchen scene

- importance to calculate the light
  + all light sources
  + the reflection of others objects
  + light from other side (like through a glass)

- based on physics
- not based in physics

- local and non-local light
  + __local__ considers the light only on the given point, ignores the rest of the world (except the light source) __O(n)__
    * shadows have to be calculated separately
    * takes only direct lighting information
    * involves the use of an "ambient" term to simulate indirect lighting

  + __global__ much more complex, but also includes the shadows __O(n^n)__
    * direct illumination: object that receive light without another object blocking it
    * objects in the shadow can still receive light from light rays bouncing off others objects (indirect illumination)

- figures (one of them has an error)
  + the local model shouldn't have a shadow on the foot of the objects, they are directly exposed to the light source

### Local Illumination (Phong)
- reduce light model to 3 components
  + ambient
  + diffuse
  + specular

- we will have a equation that give the exact light at a given point
- later we shall see how to use this equation __without infinite points__ (shading)

- even knowing that we calculate the light for just a point we need to simplify it and dis considers some things

- to make the calculation we need the light source info and the material reflection behavior

#### Ambient light contribution
- ambient light = background light
  + it's used to simulate indirect lighting

- irl the light stop reflecting once there is no more wave to be propagated
  + in CG we stop calculating once it gets to hard for the computer :p

- since we cannot calculate the real l

- ambient component
  + independent of
    * object's position
    * viewer's position
    * light source's position

  + dependent of
    * a constant factor (in each RGB channels)

#### Diffuse light contribution
- depends on the light's position and the surface property of reflection

- but it is independent of the viewer's position

- solution if based on __Lambert's Law__
  + diffuse = K * I * cos(@)
    * K: material's reflection property
    * I: light intensity
    * @: angle between the point normal vector and light vector

#### Diffuse + Ambient
- we basically sum the diffuse light with the remains of the light of the ambient

#### Specular light contribution
- light reflection from shinny surfaces
  + e.g. metal

- it highly depends of the viewer's position

- the vector with most specular light is exact reflection of the light vector

- specular = K * I * cos(@)^f
  + K: specular reflection constant
  + I: light intensity
  + @: angle between light vector and reflection vector
  + f: specular variation

#### Shading vs Lighting
- we define a normal at each polygon
  + not at each vertex

- we don't want to calculate all the points (infinite!)

##### Shading Models: Flat
- lighting: evaluate the lighting equation at center of each polygon using the associate normal

- shading: each sample point on the polygon is given the interpolated lighting value at the vertices (i.e. a total hack)

##### Shading Models: Gouraud
- we define a normal vector at each vertex

- lighting: evaluate the lighting equation at each vertex using the associated normal vector

- shading: each sample point's color on the polygon is interpolated from the color values at the polygon's vertices

##### Shading Models: Phong
- each vertex has an associated normal vector

- lighting: evaluate the lighting equation at each vertex using the associated normal vector

- shading: for every sample point on the polygon we interpolate the normals at vertices of the polygon and compute the color using lighting equation with the interpolated normal at each interior pixel
