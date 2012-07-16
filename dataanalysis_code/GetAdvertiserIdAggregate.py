dict = {}

f = open('advertiseridadid.txt', 'rU')
#f = open('advertiseridadidstoinclude.txt', 'rU')
for line in f:
  vec = line.split()
  advertiserid = int(vec[0])
  adid = int(vec[1])
  clicks = int(vec[2])
  impressions = int(vec[3])
  instances = int(vec[4])
  ctr = float(vec[5])
  
  if advertiserid in dict:
    if adid in dict[advertiserid]:
      raise Exception('adid %d is already present in advertiserid %d'%(adid, advertiserid))
    else:
      dict[advertiserid][adid] = (clicks, impressions, instances, ctr)
  else:
    dict[advertiserid] = {}
    dict[advertiserid][adid] = (clicks, impressions, instances, ctr)
    
f.close()

f = open('advertiseridaggregate.txt', 'w')
#f = open('advertiseridaggregate_adidstoinclude.txt', 'w')
for advertiserid in sorted(dict.keys()):
  totalads = len(dict[advertiserid])
  totalclicks = 0
  totalimpressions = 0
  totalinstances = 0
  for adid in dict[advertiserid].keys():
    (clicks, impressions, instances, ctr) = dict[advertiserid][adid]
    totalclicks += clicks
    totalimpressions += impressions
    totalinstances += instances
  totalctr = 0.0
  if totalimpressions != 0: totalctr = float(totalclicks) / float(totalimpressions)
  
  text = '%d %d %d %d %d %.16f\n'%(advertiserid, totalads, totalclicks, totalimpressions, totalinstances, totalctr)
  f.write(text)
f.close()

