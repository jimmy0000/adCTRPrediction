mindepth = 100000
maxdepth = -1
minpos = 100000
maxpos = -1

f = open('training.txt')
for line in f:
  vec = line.strip().split()
  depth = int(vec[5])
  pos = int(vec[6])
  if depth < mindepth: mindepth = depth
  if pos < minpos: minpos = pos
  if depth > maxdepth: maxdepth = depth
  if pos > maxpos: maxpos = pos
f.close()

print mindepth, maxdepth
print minpos, maxpos