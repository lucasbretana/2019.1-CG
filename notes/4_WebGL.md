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
