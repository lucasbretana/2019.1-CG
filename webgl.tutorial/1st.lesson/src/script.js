"use strict";

var vertexShaderSource = "" +
  "   #version 300 es \n" +
  "   // an attribute is an input (in) to a vertex shader. \n" +
  "   // It will receive data from a buffer \n" +
  "   in vec2 a_position; \n" +
  "   in vec2 u_resolution; \n" +
  "    \n" +
  "   // all shaders have a main function \n" +
  "   void main() { \n" +
  "     // gl_Position is responsible for setting \n" +
  "     // fst: go from pixel position to a value between [0, 1] \n" +
  "     // snd: make this value from: [0, 2] \n" +
  "     // finally: make this value between [-1, +1] \n" +
  "     gl_Position = vec4((2.0 * (a_position / u_resolution)) - 1.0, 0.0, 1.0); \n" +
  "   } \n" +
"";

var fragmentShaderSource = ""+
  "   #version 300 es \n" +
  "   \n" +
  "   // fragment shaders don't have a default precision so we need \n" +
  "   // to pick one. mediump is a good default. It means \"medium precision\" \n" +
  "   precision mediump float; \n" +
  "   \n" +
  "   // we need to declare an output for the fragment shader \n" +
  "   out vec4 outColor; \n" +
  "   \n" +
  "   void main() { \n" +
  "     // Just set the output to a constant redish-purple \n" +
  "     outColor = vec4(1, 0, 0.5, 1); \n" +
  "   } \n" +
"";

/*
 * Create and compile a shder
 * @param gl: WebGL API object
 * @param type: kinda of shader { vertex, fragment }
 * @param source: code of the shader
 * @return shader: a compiled shader
 */
function createShader(gl, type, source) {
  var shader = gl.createShader(type);
  gl.shaderSource(shader, source);
  gl.compileShader(shader);
  var success = gl.getShaderParameter(shader, gl.COMPILE_STATUS);
  if (success) {
    return shader;
  }

  var err_msg = gl.getShaderInfoLog(shader);
  console.log("webgl: " + err_msg);  // eslint-disable-line
  gl.deleteShader(shader);
  throw Error("Could't compile the shader!\n" + err_msg);
}

/*
 * Links the shaders together into a "program"
 * @param gl: WebGL API object
 * @param vertexShader: the vertex shader :p
 * @param fragmnetShader: the fragmnet shader :p
 * @return program: shader linked
 */
function createProgram(gl, vertexShader, fragmentShader) {
  var program = gl.createProgram();
  gl.attachShader(program, vertexShader);
  gl.attachShader(program, fragmentShader);
  gl.linkProgram(program);
  var success = gl.getProgramParameter(program, gl.LINK_STATUS);
  if (success) {
    return program;
  }

  var err_msg = gl.getProgramInfoLog(program);
  console.log(err_msg);  // eslint-disable-line
  gl.deleteProgram(program);
  throw Error("Could't compile the shader!\n" + err_msg);
}

function main() {
  // Get A WebGL context
  var canvas = document.getElementById("webgl-canvas");
  if (!canvas) {
    window.alert("Could't find the canvas..");
    return;
  }
  var gl = canvas.getContext("webgl2");
  if (!gl) {
    window.alert("Could't get the context..");
    return;
  }

  // create GLSL shaders, upload the GLSL source, compile the shaders
  var vertexShader = createShader(gl, gl.VERTEX_SHADER, vertexShaderSource);
  var fragmentShader = createShader(gl, gl.FRAGMENT_SHADER, fragmentShaderSource);

  // Link the two shaders into a program
  var program = createProgram(gl, vertexShader, fragmentShader);

  // look up where the vertex data needs to go.
  var posAttrLoc = gl.getAttribLocation(program, "a_position");
  var clipUnifLoc = gl.getUniformLocation(program, "u_resolution");

  // Create a buffer and put three 2d clip space points in it
  var bufPos = gl.createBuffer();

  // Bind it to ARRAY_BUFFER (think of it as ARRAY_BUFFER = bufPos)
  gl.bindBuffer(gl.ARRAY_BUFFER, bufPos);

  var positions = [
    10.0, 200.0,
    80.0, 200.0,
    10.0, 300.0,
  ];
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(positions), gl.STATIC_DRAW);

  // Create a vertex array object (attribute state)
  var vao = gl.createVertexArray();

  // and make it the one we're currently working with
  gl.bindVertexArray(vao);

  // Turn on the attribute
  gl.enableVertexAttribArray(posAttrLoc);

  // Tell the attribute how to get data out of bufPos (ARRAY_BUFFER)
  var size = 2;          // 2 components per iteration
  var type = gl.FLOAT;   // the data is 32bit floats
  var normalize = false; // don't normalize the data
  var stride = 0;        // 0 = move forward size * sizeof(type) each iteration to get the next position
  var offset = 0;        // start at the beginning of the buffer
  gl.vertexAttribPointer( posAttrLoc, size, type, normalize, stride, offset );

  webglUtils.resizeCanvasToDisplaySize(gl.canvas);

  // Tell WebGL how to convert from clip space to pixels
  gl.viewport(0, 0, gl.canvas.width, gl.canvas.height);

  // Clear the canvas
  gl.clearColor(0, 0, 0, 0);
  gl.clear(gl.COLOR_BUFFER_BIT);

  // Tell it to use our program (pair of shaders)
  gl.useProgram(program);

  // 
  gl.uniform2f(clipUnifLoc, gl.canvas.width, gl.canvas.height);

  // Bind the attribute/buffer set we want.
  gl.bindVertexArray(vao);

  // draw
  var primitiveType = gl.TRIANGLES;
  var offset = 0;
  var count = 3;
  gl.drawArrays(primitiveType, offset, count);
}

main();

