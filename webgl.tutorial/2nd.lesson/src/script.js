// WebGL2 - Fundamentals

  "use strict";

var vertexShaderSource = `#version 300 es
  // an attribute is an input (in) to a vertex shader.
  // It will receive data from a buffer
  //in vec4 a_position;
  in vec2 a_position;

  uniform vec2 u_resolution;

  // all shaders have a main function
  void main() {
    // convert the position from pixel to 0.0 ~ 1.0
    vec2 zeroToOne = a_position / u_resolution;

    // convert from 0~1 to 0~2
    vec2 zeroToTwo = zeroToOne * 2.0;

    // convert from 0~2 to -1~+1 (clipspace)
    vec2 clipspace = zeroToTwo - 1.0;

    gl_Position = vec4(clipspace, 0.0, 1.0);
  }
`;

var fragmentShaderSource = `#version 300 es
  // fragment shaders don't have a default precision so we need
  // to pick one. mediump is a good default. It means "medium precision"
  precision mediump float;

  // we need to declare an output for the fragment shader
  out vec4 outColor;

  // get color from outside shader (i.e. paramter)
  uniform vec4 u_color;

  void main() {
    // Just set the output to a constant redish-purple
    //outColor = vec4(1, 0, 0.5, 1);
    outColor = u_color;
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
  var canvas = document.getElementById("main-canvas");
  var gl = canvas.getContext("webgl2");
  if (!gl) {
    console.error("Could not get a webgl context");
    return;
  }

  // create and link a program
  var vertexShader = createShader(gl, gl.VERTEX_SHADER, vertexShaderSource);
  var fragmentShader = createShader(gl, gl.FRAGMENT_SHADER, fragmentShaderSource);
  var program = createProgram(gl, vertexShader, fragmentShader);

  var positionAttributeLocation = gl.getAttribLocation(program, "a_position");
  var resolutionUniformLocation = gl.getUniformLocation(program, "u_resolution");
  var colorUniformLocation = gl.getUniformLocation(program, "u_color");

  // Create a buffer and put three 2d clip space points in it
  var positionBuffer = gl.createBuffer();

  // Create a vertex array object (attribute state)
  // that is what describes how data should be read/write to thte buffer itself
  var vao = gl.createVertexArray();

  // and make it the one we're currently working with
  gl.bindVertexArray(vao);

  // Turn on the attribute
  gl.enableVertexAttribArray(positionAttributeLocation);

  // bind it to ARRAY_BUFFER
  gl.bindBuffer(gl.ARRAY_BUFFER, positionBuffer);

  // Tell the attribute how to get data out of positionBuffer (ARRAY_BUFFER)
  // that is basically a struct definition
  var size      = 2;          // 2 components per iteration
  var type      = gl.FLOAT;   // the data is 32bit floats
  var normalize = false;      // don't normalize the data
  var stride    = 0;          // 0 = move forward size * sizeof(type) each iteration to get the next position
  var offset    = 0;          // start at the beginning of the buffer
  gl.vertexAttribPointer(
      positionAttributeLocation, size, type, normalize, stride, offset);

  webglUtils.resizeCanvasToDisplaySize(gl.canvas);

  // Tell WebGL how to convert from clip space to pixels
  gl.viewport(0, 0, gl.canvas.width, gl.canvas.height);

  // Clear the canvas
  gl.clearColor(0, 0, 0, 0);
  gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

  // Tell it to use our program (pair of shaders)
  gl.useProgram(program);

  // Bind the attribute/buffer set we want.
  gl.bindVertexArray(vao);

  // pass in the canvas resolution so we can convert from
  // pixels to clipspace in the shader (piece of shit IMO...)
  gl.uniform2f(resolutionUniformLocation, gl.canvas.width, gl.canvas.height);

  for (var ii=0; ii<50; ++ii) {
    // random size
    setRectangle(gl, randomInt(300), randomInt(300), randomInt(300), randomInt(300));

    // random color
    gl.uniform4f(colorUniformLocation, Math.random(), Math.random(), Math.random(), 1);

    var primitiveType = gl.TRIANGLES;
    var offset        = 0;
    var count         = 6; // 2 triangles <-> 1 square shape
    gl.drawArrays(primitiveType, offset, count);
  }
}

function randomInt(range) {
  return Math.floor(Math.random() * range);
}

function setRectangle(gl, x, y, width, height) {
  var x1 = x;
  var x2 = x + width;
  var y1 = y;
  var y2 = y + height;

  var position = new Float32Array([
    x1, y1,
    x2, y1,
    x1, y2,
    x1, y2,
    x2, y1,
    x2, y2
  ]);

  gl.bufferData(gl.ARRAY_BUFFER, position, gl.STATIC_DRAW);
}

main();
