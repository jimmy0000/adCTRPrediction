
f = open('advertiseridadid.txt', 'rU')
fw = open('adidstodiscard.txt', 'w')
fwinc = open('advertiseridadidstoinclude.txt', 'w')
adIdsToDiscard = []
for line in f:
  vec = line.split()
  advertiserid = int(vec[0])
  adid = int(vec[1])
  clicks = int(vec[2])
  impressions = int(vec[3])
  instances = int(vec[4])
  if impressions >= 50: fwinc.write(line)
  else: fw.write(line)
    
fwinc.close()
fw.close()
f.close()
