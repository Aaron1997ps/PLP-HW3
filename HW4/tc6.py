l1= ["st1"]
l2= l1 + ["st2"] + ["st3"] + ["ab"] + ["bc"]
print(l2)
#["st1", "st2","st3","ab","bc"]
print(l2[1:])
#["st2", "st3", "ab", "bc"]

l3=["ef"]
l4=["de"]
l5=l2 + l3 + l4
print(l5)
#["st1", "st2","st3","ab","bc","ef", "de"]