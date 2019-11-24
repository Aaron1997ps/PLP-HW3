# functions
def f(x,y,z):
  return x+y+z

f(1,0,0)
f("how ","are ","you")
# error
f(1,"abc",1)
# error
f("xyz","abc",1)
# error
f(1,2,"xyz")


def g(x,y,z):
  l=[]
  l.append(x)
  l.append(y)
  l.append(z)
  return l

g("how ","are ","you")
# warning
g(1,2,"abc")
somenumber=1
# warning
somenumber=g("how ","are ","you")
