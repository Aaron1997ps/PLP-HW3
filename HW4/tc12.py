x="a"
y="b"
z="z" if x==y else "c"
l1=[z]+["z"]

w="w" if x<y else "d"
l2=l1+[w]
print(l2)
#["c","z","w"]