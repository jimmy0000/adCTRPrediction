import random
import exceptions

totalValidationInstances = 0
totalTestInstances = 0
tenpercentcutoff = 14600000
instanceValueToSkip = 500000

dict = {}
advertiserid2instancesmap = {}

f=open('advertiseridaggregate_adidstoinclude.txt', 'rU')
for line in f:
  vec = line.split()
  advertiserid = int(vec[0])
  totalads = int(vec[1])
  totalclicks = int(vec[2])
  totalimpressions = int(vec[3])
  totalinstances = int(vec[4])
  totalctr = float(vec[5])
  
  if totalinstances >= instanceValueToSkip: continue
  elif advertiserid not in dict:
    dict[advertiserid] = line
    advertiserid2instancesmap[advertiserid] = totalinstances
  else: raise 'AdvertiserId already present in dictionary'
    
f.close()

f = open('validationadvertiserids.txt', 'w')
iteration = 0
while totalValidationInstances < tenpercentcutoff:
  advertiseridvec = dict.keys()
  flag = False
  for advertiserid in advertiseridvec:
    if (random.random() > 0.5 or iteration >= 10000) and totalValidationInstances + advertiserid2instancesmap[advertiserid] < tenpercentcutoff:
      totalValidationInstances += advertiserid2instancesmap[advertiserid]
      f.write(dict[advertiserid])
      del dict[advertiserid]
      del advertiserid2instancesmap[advertiserid]
      flag = True
  iteration += 1
  if iteration >= 10000 and flag == False: break
    
f.close()

f = open('testadvertiserids.txt', 'w')
iteration = 0
while totalTestInstances < tenpercentcutoff:
  advertiseridvec = dict.keys()
  flag = False
  for advertiserid in advertiseridvec:
    if (random.random() > 0.5 or iteration >= 10000) and totalTestInstances + advertiserid2instancesmap[advertiserid] < tenpercentcutoff:
      totalTestInstances += advertiserid2instancesmap[advertiserid]
      f.write(dict[advertiserid])
      del dict[advertiserid]
      del advertiserid2instancesmap[advertiserid]
      flag = True
  iteration += 1
  if iteration >= 10000 and flag == False: break
    
f.close()

print 'totalValidationInstances: %d totalTestInstances: %d'%(totalValidationInstances, totalTestInstances)