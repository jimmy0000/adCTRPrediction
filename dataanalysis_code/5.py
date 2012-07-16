import time
import numpy as np

querycounts = np.zeros(27000000, dtype = int)
dict = {}

f = open('analysis_training_queryid.txt')
for line in f:
  vec = line.strip().split()
  queryid = int(vec[0])
  count = int(vec[1])
  querycounts[queryid] = count
f.close()


f = open('queryid_tokensid.txt')
lineno = 0
start_clock = time.clock()
for line in f:
  vec = line.strip().split()
  queryid = int(vec[0])
  count =  querycounts[queryid]
  delimitedtokens = vec[1]
  tokens = delimitedtokens.split('|')
  for tokenstr in tokens:
    tokenid = int(tokenstr)
    if tokenid not in dict: dict[tokenid] = 0
    dict[tokenid] += count
    
  lineno += 1
  if lineno % 1000000 == 0: print lineno, 'lines processed in ', time.clock() - start_clock, 'seconds'
  if lineno < 5: print queryid, tokens
f.close()

fw = open('analysis_training_querytokensid.txt', 'w')
for tokenid in sorted(dict.keys()):
  fw.write(str(tokenid) + '\t'  + str(dict[tokenid]) + '\n')
fw.close()


  