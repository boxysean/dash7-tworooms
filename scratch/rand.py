from random import randint


last = -1

a = []

for i in range(100):
    x = randint(0, 3)
    while x == last:
      x = randint(0, 3)
    a.append(str(x))
    last = x

print ",".join(a)
