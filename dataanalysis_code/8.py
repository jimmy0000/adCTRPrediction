import time

prevadvertiserid = -1
prevclicks = 0
previmpressions = 0
prevadid = -1
prevuniqueads = 0
prevadidimpressed = -1
prevuniqueadsimpressed = 0
prevadidclicked = -1
prevuniqueadsclicked = 0

f = open('training_original_advertiser_sorted.txt')
fw = open('advertiser_properties.txt', 'w')
lineno = 0
start_clock = time.clock()
for line in f:
  vec = line.strip().split()
  advertiserid = int(vec[0])
  adid = int(vec[1])
  clicks = int(vec[2])
  impressions = int(vec[3])
  
  if prevadvertiserid != 0 and prevadvertiserid != advertiserid:
    fw.write(str(prevadvertiserid) + ' ' + str(prevuniqueads) + ' ' + str(prevuniqueadsimpressed) + ' ' + \
    str(previmpressions) + ' ' + str(prevuniqueadsclicked) + ' ' + str(prevclicks) + '\n')
    
    prevadvertiserid = -1
    prevclicks = 0
    previmpressions = 0
    prevadid = -1
    prevuniqueads = 0
    prevadidimpressed = -1
    prevuniqueadsimpressed = 0
    prevadidclicked = -1
    prevuniqueadsclicked = 0

  
  if prevadid != adid: prevuniqueads += 1
  if impressions > 0:
    if prevadidimpressed != adid: prevuniqueadsimpressed += 1
    prevadidimpressed = adid
  if clicks > 0:
    if prevadidclicked != adid: prevuniqueadsclicked += 1
    prevadidclicked = adid
    
  prevadvertiserid = advertiserid
  prevclicks += clicks
  previmpressions += impressions
  prevadid = adid

  lineno += 1
  if lineno % 1000000 == 0: print lineno, 'lines processed in ', time.clock() - start_clock, 'seconds'
  if lineno < 5: print advertiserid, adid, clicks, impressions
  
fw.write(str(prevadvertiserid) + ' ' + str(prevuniqueads) + ' ' + str(prevuniqueadsimpressed) + ' ' + \
str(previmpressions) + ' ' + str(prevuniqueadsclicked) + ' ' + str(prevclicks) + '\n')

fw.close()
f.close()
