x="ABC"
y="XYZ"
x+y
z=x+y
x=1
# error
z=x+y


A=1
B="string1 "
C="string2"
# warning
A=B+C
A

# constants
x1="["+"123"+"456"+"]"
x2=123+456+789
#error
x3=123+"456"
#warning
x2=x1

# longer expression
s= "string1"+"string2"+"string3"
#error
b=1+2*3+(4+5)+s


#lists
l=[]
l.append("a")
l.append("b")
# warning
l.append(3)
# warning
l[1]=2

list2=[]
list2.append(1)
list2.append(2)
list2.append(3)
# warning
list2.append("4")
# warning
list2.insert(0,10)

from math import *
# if
a=3
b=2
if a>b:
  prob= 1/(2*pi)*exp(-1/(1.5)**2)
#undefined
  x=w
#error
  mixed="s1"+1+"s3"
else:
  x="s2"
# warning
  x1=a
  x2=x+a

