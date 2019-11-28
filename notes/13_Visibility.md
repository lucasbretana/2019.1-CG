## Visibility

### Culling

**Q**: How do we identify the surface of outside the view area?
**A**:
> First, we define the _view frustrum_
> There are two types of "not visible" object
> 1) Outside the _view frustrum_
> > Uses the __.__ algorithm
> 2) _Occluded_ objects
> > Uses the __.__ algorithm

> For every frame test every triangle if it is inside the _frustrum_
> **How?** Well, the _frustrum_ has 4 triangles faces (up, left, down, right)
> So we calculate the angle between the inside normal of those faces and __.__
> for every point in the triangle, if any is inside, then draw it

That's the intuitive idea, but this is too much expensive
We can create a **bouding box** around the model, and test its extremities
> Do note that a _box_ may not be the best bounding polygon
> And, the test can give _false positives_, but never a _false negative_
> > negative: not inside the _view frustrum_
> We could also use an _hierarchy_ **bouding box**, i.e., many polygon different
> for different parts of the object

Another good idea is to divide the scene into **sectors** and before going object
by object checking the boundaries, we check by sector, this is still _hierachy_
> If a section is in the scene, check object by object
> > It's also a good idea to check the neighbor sectors
> If it isn't then don't bother going object by object
This idea is typically implemented using a **Quadtree** data structure
A even more convoluted technique is the use of **Octree**,
that uses the 3 space dimensions


### Clipping

This is done in the `screen space`, i.e., in a 2D space

### Line Clipping

The points is easy,
```
  if ( Xmin < X < Xmax ) && ( Ymin < Y < Ymax ) print (X, Y)
```

But lines have many alternatives
- X and Y inside the screen area
- only X (or Y) inside the screen
- neither X or Y inside, the line passes thought inside the scene
- neither X or Y inside, line completely outside the area

_Parametric Line Formulation for Clipping_ 
Using: 0 <= t <= 1
- X = X0 + t(X1 - X0)
- Y = Y0 + t(Y1 - Y0)
- P(t) = P0 + t(P0 - P1)

The **Cohen-Sutherland Line Clipping in 2D** is an algorithm for making scene clipping
- divide the plane into 9 regions
- compute the sign bit of 4 comparisons between a vertex and a _clip edge_
