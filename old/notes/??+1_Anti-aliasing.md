## Anti-aliasing
- after the render algorithms () there are algorithms that can improve the performance
	+ dimming the number of calculations

- what is and what generates the aliasing?

## Supersampling
- the aliasing problems comes from the 'ray per pixel' problem
  + using the 'pixel view' of the scene with a single point (in the center) may not represent decently the region color
  + one of the solutions would be use more points per pixel, e.g. 5 pts (corners and center)

- we can supersampling when we take more samples from the scene than the monitor resolution can support

## Aliasing
- the signal is analogic, so we make an aproximation of it
  + a discretization

- we use a finite number of samples of the signal and recreate the signal by making interpolation on those points
  + using different interpolations may have better results (linear, bilinear, quadratic ..)
  + also using more sample can make a better discretization

- Fourier
  + any function can be written as a combination of simple wiggles

- draw a polygon perfectly is impossible, so we use a discretization
  + this may result a bad view
  + single sample problems

## Single Sample Problem
- thin primitive
  + e.g. for a thin line the discretizaion may not show anything at all
  + that's why thin and in angle objects have more aliasing

- temporal aliasing
  + from a moment to the other a pixel may/may not show with color
  + the "blinking" effect bothers too much in the image
  + the quick changes in the image make it so ugly

- estimate the fragments coverage
  + instead of setting the color on/off we can make an estimative of a color
  + e.g. 45% is black (background) and 55% is the green object color

- rendering into a higher resolution
  + with central sampling
  + a higher resolution than the monitor can use
  + box filtering
    * having stored more resolution than we can use in the final image
  + downsampling
    * we make an average from the pixel in high resolution to the resolution that we can represent
    * but this technique is __too expensive__

## Anti-aliasing
- Super Sampling Anti-aliasing (SSAA)
- Multi Sampling Anti-aliasing (MSAA) <- very used, the mother of those techniques
- Fast Sampling Anti-aliasing (FSAA)
- Coverage Sampling Anti-aliasing (CSAA)
- ...

- MSAA, does that
- since the biggest concern about using super sampling is the light calculation for each ray
  + we can _not make_ the calculation for each sample, only detecting the color on each pixel
  + then we _calculate the light_ only for the central ray, and assume the light is equal in every point
  + now we have a decent color approximation and a not so complex light calculation
