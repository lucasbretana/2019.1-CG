## Computer Graphics
### Transformations
#### Animation
- all animation is a subset of the transformations

- always remember that what we see on the screen each frame is a picture
  * picture, after picture...

- _requestAnimationFrame(drawSceneFunction)_
  * sets a function to be called each iteration, on each frame

##### Frame update
- there is one big concern here
  * the frame rate, every frame probably did not take exactly the same as the previous (or next)
  * now think about it if we change machines (different clock speed)

- we need to think are animation to finish in a given time space
  * even if it's necessary to "jump" a few steps (in the animation)
  * that is better than changing how long each animation takes for each clock speed

- the simplest solution for that it to modify the animation step 
  * with the time passed since the last draw in the scene

## Homework
- make the task explained in the forum
