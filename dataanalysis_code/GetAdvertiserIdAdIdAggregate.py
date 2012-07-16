dict = {}

f = open('data\\training.txt', 'rU')
for line in f:
  vec = line.split()
  clicks = int(vec[0])
  impressions = int(vec[1])
  adid = int(vec[3])
  advertiserid = int(vec[4])
  
  if advertiserid in dict:
    if adid in dict[advertiserid]:
      (oldclicks, oldimpressions, oldinstances) = dict[advertiserid][adid] 
      dict[advertiserid][adid] = (oldclicks + clicks, oldimpressions + impressions, oldinstances + 1)
    else:
      dict[advertiserid][adid] = (clicks, impressions, 1)
  else:
    dict[advertiserid] = {}
    dict[advertiserid][adid] = (clicks, impressions, 1)
    
f.close()

f = open('advertiseridadid.txt', 'w')
for advertiserid in sorted(dict.keys()):
  for adid in sorted(dict[advertiserid].keys()):
    (clicks, impressions, instances) = dict[advertiserid][adid]
    ctr = 0.0
    if impressions != 0: ctr = float(clicks) / float(impressions)
    text = '%d %d %d %d %d %.16f\n'%(advertiserid, adid, clicks, impressions, instances, ctr)
    f.write(text)
f.close()

