## OpenGL
- it's an API that makes the middle term between a high level code and the driver of the graphic card

- __todo__: download and compile both opengl and cg projects

- OpenGL v3.3> uses a new approach, allowing developers to use more internal functionalities
  * this allows to more complex control of how OpenGL operates
  * this also makes it more complex to learn

### Extensions
- an easier way to add functionalities to old versions

### State Machine
- the OpenGL works as a state machine, with some variables that define that state
  * the current state is usually called __context__

- every drawning function uses the current context to know how to draw
  * for instance, if it should draw lines or triangles
  * some functions alter the state machine, others just use it to draw correctly

### Objects
- objects are used to represent a sub-set of OpenGL internal state

- OpenGL internally is a C-library, so there is an abstraction for __OpenGL Objects__
  * e.g. an object to control the window drawning could be seen as

'''C
  struct object-name {
    float   opt1;
    int     opt2;
    char[]  name;
  };
'''

- one big reason to use objects it to able to set many objects, 
  * and changed the context option accordingly to what is being draw

### Getting started
- to draw anything we need a __context__ and a __window__

#### Drawning a window
- it's OS specific, therefore we use some librarie to make it easy
  * e.g.: GLUT, SDL, SFML, GLFW

##### GLFW
- is a framework used to simplify the construction of contexts and window

- it's not really necessary, but the process of creating window is OS dependent

##### GLAD
- used to manage function pointers, it's also no required but makes lifes much easier

##### Viewport
- where openGL will render
