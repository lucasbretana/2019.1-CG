## WebGL - WebGL2 fundamentals
- check out at __https://webgl2fundamentals.org/__
- we shall use JS to build up OpenGL stuff
- we call the JS from a minimalist HTML doc file

### HTML and JS
- HTML is the structure file that loads up the JS
  * also its CSS is used to position things around

- the HTML will simply defines an <canvas> element
  * this is a container to draw freely using scripting
  * has no drawing abilities, the script must actually draw the graphics

- the JS runs the actual code that uses the WebGL algorithms and data structures
  * usually the JS is used to re sketch the HTML
  * but we shall use it only to run the WebGL stuff
  * this script look like other stuff, defines function and runs commands

- the JS will run the commands in the script
  * usually the JS defines function, call the main one at the end
  * the function will probably attaches itself to something, so it is called repeatedly
  * e.g. keeps refreshing the images

- the JS will be draw over the HTML
  * only the HTML will be rendered!
  * e.g. the element to be drawn over is the main canvas

### Sharing information between JS and the OpenGL code (in the kernels)
- basically sharing date between CPU and GPU

- we can create communication channels using
  * _document.getElementById("id").getContext("webgl").getAttributeLocation(program, "id");_

- now that we have a channel, we can bind its use a specific buffer from the WebGL

```js
  // create a buffer and put three 2d clip space points in it
  // from now on, every ARRAY_BUFFER operation to the positionBuffer
  // this will be used for something like ARRAY_BUFFER = positionBuffer
  var positionBuffer = gl.createBuffer();

  // bind it to ARRAY_BUFFER
  // (again, think of it as ARRAY_BUFFER = positionBuffer)
  gl.bindBuffer(gl.ARRAY_BUFFER, positionBuffer);
```

#### Receive data in the shaders
- there are 4 ways shaders can receive data

##### 1. Attributes, Buffers and Vertex Arrays
- buffers are arrays of binary data you sent to the GPU
  * contains: positions, normals, textures coordinates, vertex color..

- **NOTE**: this data is NOT randomly accessed
  * for each iteration of the shader it normally access a fixed number
  * of the data in the buffer

- attributes are used to specify __how to pull data from the buffer__
  * number of parameters
  * size of each parameter (e.g. 32bits floats)
  * start of the buffer, offset
  * the state of the attributes, which buffer and how use the data is store in the VAO
    + VAO: vertex array object

##### 2. Uniforms
- basically global variables set before the execution of the shader

##### 3. Textures
- arrays of data that can be accessed randomly
  * most commonly used to store texture as image data

##### 4. Varying
- communication between vertex and fragment shaders
  * depending on what is being render (points, lines, triangles)
  * the value stored in the varying by the vertex shader will
    + interpolated in the fragment shader

