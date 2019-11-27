a=40
l1=["50"]
#error <-(print this in .out file)
l2=[a]+l1 
l3=l1+(["300"]+["21"])
print(l3)
#["50","300","21"]
#error <-(print this in .out file)
l4=l3+[a]