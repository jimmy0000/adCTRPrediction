import time

prevdisplayurl = 0
prevclicks = 0
previmpressions = 0
prevuniqueusers = 0
prevuserid = 0
f = open('training_original_displayurl_sorted.txt')
fw = open('displayurl_clicks_impressions_uniqueusers.txt', 'w')
lineno = 0
start_clock = time.clock()
for line in f:
  vec = line.strip().split()
  displayurl = long(vec[0])
  userid = int(vec[1])
  clicks = int(vec[2])
  impressions = int(vec[3])
  
  if prevdisplayurl != 0 and prevdisplayurl != displayurl:
    fw.write(str(prevdisplayurl) + ' ' + str(prevclicks) + ' ' + str(previmpressions) + ' ' + str(prevuniqueusers) + '\n')
    
    prevdisplayurl = 0
    prevclicks = 0
    previmpressions = 0
    prevuniqueusers = 0
    prevuserid = 0

  
  if userid == 0 or prevuserid != userid: prevuniqueusers += 1
  prevdisplayurl = displayurl
  prevclicks += clicks
  previmpressions += impressions
  prevuserid = userid

  lineno += 1
  if lineno % 1000000 == 0: print lineno, 'lines processed in ', time.clock() - start_clock, 'seconds'
  if lineno < 5: print displayurl, userid, clicks, impressions
  
fw.write(str(prevdisplayurl) + ' ' + str(prevclicks) + ' ' + str(previmpressions) + ' ' + str(prevuniqueusers) + '\n')

fw.close()
f.close()
