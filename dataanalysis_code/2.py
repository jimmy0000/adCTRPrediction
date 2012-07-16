import time
querydict = {}
keyworddict = {}

f = open('training.txt')
lineno = 0
start_clock = time.clock()
for line in f:
  vec = line.strip().split()
  queryid = int(vec[7])
  keywordid = int(vec[8])
  
  if queryid not in querydict: querydict[queryid] = 0
  querydict[queryid] += 1
  
  if keywordid not in keyworddict: keyworddict[keywordid] = 0
  keyworddict[keywordid] += 1
  
  lineno += 1
  if lineno % 1000000 == 0: print lineno, 'lines processed in ', time.clock() - start_clock, 'seconds'
  if lineno < 5: print queryid, keywordid
f.close()

fw = open('analysis_training_queryid.txt', 'w')
for queryid in sorted(querydict.keys()):
  fw.write(str(queryid) + '\t'  + str(querydict[queryid]) + '\n')
fw.close()

fw = open('analysis_training_keywordid.txt', 'w')
for keywordid in sorted(keyworddict.keys()):
  fw.write(str(keywordid) + '\t'  + str(keyworddict[keywordid]) + '\n')
fw.close()

  