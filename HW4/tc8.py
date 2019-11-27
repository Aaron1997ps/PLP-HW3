t=0
a=1 if t>0 else 1
l1=[a]

b=2 if a>1 else 3
l2=[b]

l3=l1+l2+[2]+[3]+[4]

print(l3[1:])
#[3,2,3,4]