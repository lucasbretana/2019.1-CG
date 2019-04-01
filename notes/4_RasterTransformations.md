### Raster Pipeline Overview
<OpenGL-4.5_core-profile> FIX

#### OpenGL
- is a software interface that simplifies the programmer job to use graphics hardware
	* without that we would use assembly

- there are others: DirectX, Pixar's RenderMan

- app -> OpenGL -> Frame Buffer
  * change states (pipeline) and send primitives though the state machine (pipeline)
  * the pipeline format is defined by the current state machine
  * the output is the image itself

- __NOTE:__: to make input, draw window, etc we use others libraries
  * GLFW, GLADE....

__OpenGL Extensions__
- used to make experimental features

#### OpenGL Mathematics **GLM**
- easy to use with OpenGL

- __INSERT SAMPLE CODE__

#### Shading language
- graphic programming language, runs in the GPU
  * data structures: color, normal, etc ..
  * operation: dot, cross product, etc ..
  * GLSL, HLSL, Cg <- _usually highly parallel_

- programmer -> OpenGL interface -> OpenGL implementation -> frame buffer
                * CPU memory        * GPU memory

##### GLSL
- input: geometric primitives
  * GL_POINTS, GL_TRIANGLE, GL_LINE_STRIP, SGL_LINES, ...

- FIX current_pipeline_image
- the GLSL code runs in the Vertex Program of the pipeline
  * one thread for each vertex

- many common data types to simplify our life
  * vec2, ivec4, mat2, samples2D, ...

- common operations too
  * operators overload from C++
  * a\*b

- qualifiers: __in__, __out__, __inout__, __uniform__
  * can be used to define its behavior
  * in, out, inout are one for each thread
  * uniform makes the variable shared between all threads

- sample code: Vertex Shader
  * simply gets the input
  * the output is a point
```
  in vec3 vPos;
  in vec4 vCol;
  out vec4 color;
  void main() 
  {
    color = vColor;
    gl_Position = vertex;
  }
```

- sample code: Fragment Shader
  * the output is a painted pixel
```
  in vec4 color;
  void main()
  {
    gl_FragColor = ...;
  }
```
- __NOTE:__ in this step we make stuff like interpolation
