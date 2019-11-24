l1=[]
l1.append(12)
l1.insert(1,34)
#warning
l1.append("sample")

l2 = []
l2.append("this")
#warning
l2.append(34)
#warning
l4 = l1+l2
#error
l3 = l1*l2
