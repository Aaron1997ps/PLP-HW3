#function program
import math

def f1(x,y,z):
    return x+y*z
#error
f1("how","you","doing")
#error
f1(1,2,"a")
f1(3,4,5)

def f2(a,b):
    l1=[]
    l2=[]
    l1.append(a)
    l2.append(b)
    return l1+l2

f2("the","sun")
var = f2(2,3)
#warning
var = "moon"
#warning
f2(2,"hi")
