import sys

f = open('adidstodiscard.txt', 'rU')
adIdsToDiscard = {}
for line in f:
  vec = line.split()
#  advertiserid = int(vec[0])
  adid = int(vec[1])
  # clicks = int(vec[2])
  # impressions = int(vec[3])
  # instances = int(vec[4])
  if adid not in adIdsToDiscard: adIdsToDiscard[adid] = True
f.close()
print 'done loading adIdsToDiscard'
sys.stdout.flush()

validationAdvertiserIds = []
f = open('validationadvertiserids.txt', 'rU')
for line in f:
  advertiserid = int(line.split()[0])
  validationAdvertiserIds.append(advertiserid)
f.close()
print 'done loading validationAdvertiserIds'
sys.stdout.flush()

testAdvertiserIds = []
f = open('testadvertiserids.txt', 'rU')
for line in f:
  advertiserid = int(line.split()[0])
  testAdvertiserIds.append(advertiserid)
f.close()
print 'done loading testAdvertiserIds'
sys.stdout.flush()

f = open('data\\training.txt', 'rU')
ftrain = open('F:\\training.txt', 'w')
fvalid = open('F:\\validation.txt', 'w')
ftest = open('F:\\testing.txt', 'w')
totalInstancesSkipped = 0
lineno = 0
for line in f:
  vec = line.split()
  adid = vec[3]
  advertiserid = int(vec[4])
  if adid not in adIdsToDiscard: 
    if advertiserid in validationAdvertiserIds: fvalid.write(line)
    elif advertiserid in testAdvertiserIds: ftest.write(line)
    else: ftrain.write(line)
  else: totalInstancesSkipped += 1
  
  lineno += 1
  if lineno % 500000 == 0: 
    print 'processed line:%d'%(lineno)
    sys.stdout.flush()
  
ftrain.close()
fvalid.close()
ftest.close()
f.close()

print 'totalInstancesSkipped:%d'%(totalInstancesSkipped)