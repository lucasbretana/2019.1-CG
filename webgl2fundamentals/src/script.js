// WebGL2 - Fundamentals
// from https://webgl2fundamentals.org/webgl/webgl-fundamentals.html


  "use strict";


// what goes in this string will be discussed later
var vertexShaderSource = `#version 300 es

// an attribute is an input (in) to a vertex shader.
// It will receive data from a buffer
in vec4 a_position;

// all shaders have a main function
void main() {

  // gl_Position is a special variable a vertex shader
  // is responsible for setting
  gl_Position = a_position;
}
`;

var fragmentShaderSource = `#version 300 es

// fragment shaders don't have a default precision so we need
// to pick one. mediump is a good default. It means "medium precision"
precision mediump float;

// we need to declare an output for the fragment shader
out vec4 outColor;

void main() {
  // Just set the output to a constant redish-purple
  outColor = vec4(1, 0, 0.5, 1);
}
`;

function createShader(gl, type, source) {
  var shader = gl.createShader(type);
  gl.shaderSource(shader, source);
  gl.compileShader(shader);
  var success = gl.getShaderParameter(shader, gl.COMPILE_STATUS);
  if (success) {
    return shader;
  }

  console.log(gl.getShaderInfoLog(shader));  // eslint-disable-line
  gl.deleteShader(shader);
  return undefined;
}

function createProgram(gl, vertexShader, fragmentShader) {
  var program = gl.createProgram();
  gl.attachShader(program, vertexShader);
  gl.attachShader(program, fragmentShader);
  gl.linkProgram(program);
  var success = gl.getProgramParameter(program, gl.LINK_STATUS);
  if (success) {
    return program;
  }

  console.log(gl.getProgramInfoLog(program));  // eslint-disable-line
  gl.deleteProgram(program);
  return undefined;
}

function main() {
  // Get A WebGL context
  // draw over the main canvas from the html
  var canvas = document.getElementById("main-canvas");
  // now we interelate the canvas with an object that will be used to draw w/ WebGL
  var gl = canvas.getContext("webgl2");
  if (!gl) {
    return;
  }

  // create GLSL shaders, upload the GLSL source, compile the shaders
  var vertexShader = createShader(gl, gl.VERTEX_SHADER, vertexShaderSource);
  var fragmentShader = createShader(gl, gl.FRAGMENT_SHADER, fragmentShaderSource);

  // Link the two shaders into a program
  var program = createProgram(gl, vertexShader, fragmentShader);

  // look up where the vertex data needs to go.
  var positionAttributeLocation = gl.getAttribLocation(program, "a_position");

  // Create a buffer and put three 2d clip space points in it
  var positionBuffer = gl.createBuffer(); // from now on, every ARRAY_BUFFER operation to the positionBuffer, (think of it as ARRAY_BUFFER = positionBuffer)

  // Bind it to ARRAY_BUFFER (again, think of it as ARRAY_BUFFER = positionBuffer)
  gl.bindBuffer(gl.ARRAY_BUFFER, positionBuffer);

  // triangle cordinates
  var positions = [
    0, 0,
    0, .5,
    .5, 0,
  ];
  // that  is basically a memcopy
  // except we don't need to say the destination buffer channel (because of the previous bind)
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(positions), gl.STATIC_DRAW);
  // context's buffer/origin buffer/context's type of draw (ignore for now)

  // Create a vertex array object (attribute state)
  var vao = gl.createVertexArray();

  // and make it the one we're currently working with
  gl.bindVertexArray(vao);
  // that is the description of the data sent to the buffer
  // after all we just sent a bunch of 0's and 1's

  // Turn on the attribute
  gl.enableVertexAttribArray(positionAttributeLocation);
  // Q: what is that?

  // Tell the attribute how to get data out of positionBuffer (ARRAY_BUFFER)
  // that is basically a struct definition
  var size = 2;          // 2 components per iteration
  var type = gl.FLOAT;   // the data is 32bit floats
  var normalize = false; // don't normalize the data
  var stride = 0;        // 0 = move forward size * sizeof(type) each iteration to get the next position
  var offset = 0;        // start at the beginning of the buffer
  gl.vertexAttribPointer(
      positionAttributeLocation, size, type, normalize, stride, offset);
  // Q: what is that?

  // that is only used to accept resising of the window
  webglUtils.resizeCanvasToDisplaySize(gl.canvas);

  // Tell WebGL how to convert from clip space to pixels
  gl.viewport(0, 0, gl.canvas.width, gl.canvas.height);
  // ocupies the entire canvas

  // Clear the canvas
  gl.clearColor(0, 0, 0, 0); // background is white
  gl.clear(gl.COLOR_BUFFER_BIT); // Q: what is that?
 
  // Tell it to use our program (pair of shaders)
  gl.useProgram(program);
  // tells the engine to use the program with our shaders from before

  // Bind the attribute/buffer set we want.
  gl.bindVertexArray(vao);
  // Q: bind the attributes array to where?
  
  // draw, only that anything will be actually draw
  var primitiveType = gl.TRIANGLES;
  var offset = 0;
  var count = 3;
  gl.drawArrays(primitiveType, offset, count);
  // draw triangle, from the start of the buffer and draw COUNT of them
  console.log("one");
}

main();
