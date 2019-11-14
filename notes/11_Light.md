## Light

### Models

- **Physical Model**
  * complex, uses many variables

- **Non-Physical Model**
  * simpler, doesn't use a good part of the information

### Illumination models
- **Point Light**
  * like candle

- **8Spot Light**
  * typical

- **Directional Light**
  * for far away light, e.g. the sun

There are also other classes of illumination models
- **Global Light**: will it illuminate other objects on the scene
  * much used because reflects in many other good things, e.g. shadows
  * consider all the light and reflection surfaces
  * need to be calculated for every single point in the screen, i.e., for each pixel (think about a 4K screen..)

- **Local Light**
  * to calculate the light in a point only uses the coordination and the light vector
  * in this model cannot calculate shadows, since there is no information about other objects
  * _much more quickly, and efficient_

### Light Components
Note: those components are for local illumination, i.e., won't have shadow and such
  * also ..

#### Ambient Light Contribution

It's used to **simulate** indirect lighting
- for everything we add a little bit of light, otherwise thing that are covered would be completely dark

Ambient component
- **Independent** of
  * object's position
  * viewer's position
  * light source's position

- **Dependent** of
  * a constant factor calculated by the ambient

#### Diffuse Light Component

**DIffuse Light** is the illumination that a surface receives from a light source that reflects equally on every surface

To calculate the light reflected in each object we must consider a set of factor, following `Lambert's Law`
- `Kd * I * cos(angle)`
  * diffuse light constant, comes from the material of the object
  * light intensity
  * the angle between the surface normal and the light vector (product between the two vectors)

#### Specular Light Contribution

**Specular Light** is the light reflection from a shiny surface (metal, mirror, etc)

Colors depends on the material and how it scatters light
  * depends on both _light source_ and _angle_
  * this light depends highly on the angle between the surface and the light vector, is decays in a exponential velocity

## Shading

Now we use the light calculation to actually determinate the shading in the object
- we can calculate the shading for the polygons of the object, we can use a middle point of the polygons, or every vertex..
  * more work shall give us a better reality view

**Phong** model, the idea is to calculate for every `fragment` in the scene
- closer to the object, more fragments -> better quality
- far from the object, less fragments -> less computing wasting
