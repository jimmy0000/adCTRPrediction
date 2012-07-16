dict = {}

f = open('data\\training.txt', 'rU')

for line in f:
  vec = line.split()
  adid = int(vec[3])
  click = int(vec[0])
  impression = int(vec[1])
  
  if adid not in dict: dict[adid] = (click, impression, 1)
  else: 
    (oldclick, oldimpression, oldinstances) = dict[adid]
    dict[adid] = (oldclick + click, oldimpression + impression, oldinstances + 1)

f.close()


f = open('adctr2.txt', 'w')
for key in sorted(dict.keys()):
  ctr = 0.0
  (click, impression, instances) = dict[key]
  if impression > 0: ctr = float(click) / float(impression)
  text = '%d %d %d %d %.16f\n'%(key, click, impression, instances, ctr)
  f.write(text)
    
f.close()