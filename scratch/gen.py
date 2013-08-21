a = []

x = range(0, 128, 4)
x.reverse()

for i in x:
  a.append(str(127-i))

print ",".join(a)

print len(a)
