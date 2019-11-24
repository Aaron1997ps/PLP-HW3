l1=[]
l2=[]
l3=[]
l1.append(23)
l2.append("23")
l3.append(340)
#warning
l1.insert(1,"seen")
#warning
ans1 = l2+l3
l2.insert(1,"before")
#error
ans2 = l2 * l3 + l1
l3.append(40)
#warning
l2 = l3
