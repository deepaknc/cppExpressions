### C++ Expression Evaluation

In this template / inheritance fun, we have a way of defining an expression in a format that looks natural and human readable, and yet can be passed around as a typed object. 

This is an implementation of prelude to [Arindam Mukherjee's excellent tutorial](http://shoddykid.blogspot.com/2008/07/expression-templates-demystified.html) on Expression Templates
The only difference is that instead of using an intrusive ref count the way he doesn, I'm using shared_ptr.

The beauty of this is that the expression is not evaluated until the () operator is called on the expression. This 'lazy' evaluation seems to be exploited in a lot of linear algebra libraries - where the Variable 'x' can be thought of as a vector of integers, and the operations are addition, and products (like cross product and dot product)
