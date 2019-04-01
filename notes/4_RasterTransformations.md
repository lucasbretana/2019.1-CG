### Raster Pipeline Overview
![Open 4.5 Core Profile](notes/res/image-open4.5-core-profile.png)
- OpenGL-4.5 Core Profile

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

```C++
  void Test()
  {
    glm::vec4 Pos = glm::vec4(glm::vec3(0.0f), 1.0f);
    glm::mat4 Model = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f));
    glm::vec4 Tranformed = Model * Pos;
  }
```
```C++
  void GlmToOpenGL()
  {
    glm::vec4 v(0.0f);
    glm::mat4 m(1.0f);
    ....
    glVertex3fv(&v[0]); // OpenGL interface
    glLoadMatrix(&m[0][0]);
  }
```


#### Shading language
- graphic programming language, runs in the GPU
  * data structures: color, normal, etc ..
  * operation: dot, cross product, etc ..
  * GLSL, HLSL, Cg <- _usually highly parallel_
  * usually C++ like

- programmer -> OpenGL interface -> OpenGL implementation -> frame buffer
                * CPU memory        * GPU memory

##### GLSL
- is a C++ like language

- input: geometric primitives
  * GL_POINTS, GL_TRIANGLE, GL_LINE_STRIP, SGL_LINES, ...

![OpenGL-pipeline](notes/res/image-current-pipeline.png)
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

###### Vertex Shader
- responsible for the vertex processing
  * one thread per vertex
  * usually there are _less_ vertexes than pixels

- sample code: Vertex Shader
  * simply gets the input
  * the output is a point
```C++
  in vec3 vPos;
  in vec4 vCol;
  out vec4 color;
  void main() 
  {
    color = vColor;
    gl_Position = vertex;
  }
```
- __NOTE:__ gl\_Position: is a built-in variable for output on the vertex shader

###### Fragment Shader
- responsible for pixel panting
  * one thread per pixel
  * usually there a _lot more_ pixel than vertexes

- sample code: Fragment Shader
  * the output is a painted pixel
```C++
  in vec4 color;
  void main()
  {
    gl_FragColor = color;
  }
```
- __NOTE:__ gl\_FragColor: is a built-in variable for output on the fragment shader
- __NOTE:__ in this step we make stuff like interpolation
