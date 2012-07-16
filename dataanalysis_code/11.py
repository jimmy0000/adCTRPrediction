clicksdict = {}
impressionsdict = {}
uniqueusersdict = {}
meanctrdict = {}

f = open('displayurl_clicks_impressions_uniqueusers.txt')
for line in f:
  vec = line.strip().split()
  clicks = int(vec[1])
  impressions = int(vec[2])
  uniqueusers = int(vec[3])
  
  if clicks not in clicksdict: clicksdict[clicks] = 0
  clicksdict[clicks] += 1
  
  if impressions not in impressionsdict: impressionsdict[impressions] = 0
  impressionsdict[impressions] += 1
  
  if uniqueusers not in uniqueusersdict: uniqueusersdict[uniqueusers] = 0
  uniqueusersdict[uniqueusers] += 1
  
  ctr = 0.0
  if impressions > 0: ctr = clicks / float(impressions)
  if ctr not in meanctrdict: meanctrdict[ctr] = 0
  meanctrdict[ctr] += 1
f.close()

fw = open('displayurl_clicks_count.txt', 'w')
for clicks in sorted(clicksdict.keys()):
  fw.write( str(clicks) + ' ' + str(clicksdict[clicks]) + '\n')
fw.close()

fw = open('displayurl_impressions_count.txt', 'w')
for impressions in sorted(impressionsdict.keys()):
  fw.write( str(impressions) + ' ' + str(impressionsdict[impressions]) + '\n')
fw.close()

fw = open('displayurl_uniqueusers_count.txt', 'w')
for uniqueusers in sorted(uniqueusersdict.keys()):
  fw.write( str(uniqueusers) + ' ' + str(uniqueusersdict[uniqueusers]) + '\n')
fw.close()

fw = open('displayurl_ctr_count.txt', 'w')
for ctr in sorted(meanctrdict.keys()):
  fw.write( str(ctr) + ' ' + str(meanctrdict[ctr]) + '\n')
fw.close()