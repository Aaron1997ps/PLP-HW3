

We created our own array function called AArray. It starts with a static size and can not change without the "resize" function.
It has its own tracker for how many elements are currently stored. Adding a new element with the "addElement" function
does not technically change the size of the array, but the class pretends to increase in size. This makes it not have mutations in it

Example:
variable = AArray(5) //Creates a new array with max size 5 [None, None, None, None, None], pretends to be size 0
print(variable.size) //Returns 0
variable.addElement(10) // [10, None, None, None, None]
print(variable.size) //Returns 1 