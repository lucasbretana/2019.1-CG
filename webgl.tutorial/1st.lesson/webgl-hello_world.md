## WebGL
- WebGL only cares for: _Clipspace coordinates_ and _colors_
  * the programmers task is to provide it

- for that we define the shaders
  * vertex shader for clipspace coordinates
  * fragment shader for colors

### Clipspace coordinates
- goes from -1 to 1
  * we can adjust it in code to more comfortable configuration

#### Shaders
- a simple __vertex shader__ example
``` GLSL
  #version 300 es

  // an attribute is an input (in) to a vertex shader.
  // it will receive data from a buffer
  in vec4 a_position;

  // all shaders have a main function
  void main() {

    // gl_Position is a special variable a vertex shader
    // is responsible for setting
    gl_Position = a_position;
  }
```

- on a pseudo-js-code we could image that what happens is
  * it's very important to note that the loop is implicit in the OpenGL
    + that is because the vertex shader runs once per set of data
    + i.e. 3 vertex per set, a.k.a. one triangle
    + also note that the 4th value is 0 - a point, 1 - a vector

```javascript
  var positionBuffer = [
    0, 0, 0, 0,
    0, 0.5, 0, 0,
    0.7, 0, 0, 0,
  ];
  var attributes = {};
  var gl_Position;

  drawArrays(..., offset, count) {
    var stride = 4;
    var size = 4;
    for (var i = 0; i < count; ++i) {
      // copy the next 4 values from positionBuffer to the a_position attribute
      const start = offset + i * stride;
      attributes.a_position = positionBuffer.slice(start, start + size);
      runVertexShader();
      ...
        doSomethingWith_gl_Position();
    }
```

- now a __fragment shader__ overview

``` GLSL
  #version 300 es

  // fragment shaders don't have a default precision so we need
  // to pick one. mediump is a good default. It means "medium precision"
  precision mediump float;

  // we need to declare an output for the fragment shader
  out vec4 outColor;

  void main() {
    // Just set the output to a constant redish-purple
    outColor = vec4(1, 0, 0.5, 1);
  }
```
- the _outColor_ is the fragment output where the RGB color is set
  * RGB in WebGL foes from 0 to 1
  * the extra field if for the alpha channel

#### HTML canvas element
- the HTML is just a basic structure to be accessed into the JS code
  * check out the webgl.tutorial to see actual code

- **NOTE**: the _#version 300 es_ is mandatory for this tutorial
  * it defines that we are using the WebGL 2
  * must be the first line in the shader (no comment or blank line before)
