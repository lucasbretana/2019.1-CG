## WebGL
- we're using WebGL v 2.0, that is nearly 100% backward compatible with v 1.0

- WebGL is simply a __rasterization engine__ capable of drawing points, line and triangles
  * the part of WebGL that runs on the GPU are the __shaders__
    + written in `GLSM` (a C++ like)
    + there are two shaders: vertex and fragment

- _vertex shader_: compute vertex position
  * upon the position the engine can rasterize points, lines and triangles

- _fragment shader_: computes the color for each pixel

- the API is almost completely about setting up the state of the OpenGL machine
  * `gl.drawArrays` and `gl.drawElements` are responsible for calling the shaders
  * the setting up is basically about how to provide data to the GPU

### Receive data in the shaders
- there are 4 ways shaders can receive data

#### 1. Attributes, Buffers and Vertex Arrays
- **BUFFERS** are arrays of binary data you sent to the GPU
  * contains: positions, normals, textures coordinates, vertex color..

- _NOTE_: this data is NOT randomly accessed
  * for each iteration of the shader it normally access a fixed number
  * of the data in the buffer

- **ATTRIBUTES** are used to specify _how to pull data from the buffer_
  * number of parameters
  * size of each parameter (e.g. 32bits floats)
  * start of the buffer, offset
  * the state of the attributes, which buffer and how use the data is store in the `VAO`
    + **VAO**: vertex array object

#### 2. Uniforms
- basically global variables set before the execution of the shader

#### 3. Textures
- arrays of data that can be accessed randomly
  * most commonly used to store texture as image data

#### 4. Varying
- communication between vertex and fragment shaders
  * depending on what is being render (points, lines, triangles)
  * the value stored in the varying by the vertex shader will
    + interpolated in the fragment shader
