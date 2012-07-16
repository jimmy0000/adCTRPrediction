import time
import numpy as np

keywordcounts = np.zeros(1500000, dtype = int)
dict = {}

f = open('analysis_training_keywordid.txt')
for line in f:
  vec = line.strip().split()
  keywordid = int(vec[0])
  count = int(vec[1])
  keywordcounts[keywordid] = count
f.close()


f = open('purchasedkeywordid_tokensid.txt')
lineno = 0
start_clock = time.clock()
for line in f:
  vec = line.strip().split()
  keywordid = int(vec[0])
  count =  keywordcounts[keywordid]
  delimitedtokens = vec[1]
  tokens = delimitedtokens.split('|')
  for tokenstr in tokens:
    tokenid = int(tokenstr)
    if tokenid not in dict: dict[tokenid] = 0
    dict[tokenid] += count
    
  lineno += 1
  if lineno % 1000000 == 0: print lineno, 'lines processed in ', time.clock() - start_clock, 'seconds'
  if lineno < 5: print keywordid, tokens
f.close()

fw = open('analysis_training_keywordtokensid.txt', 'w')
for tokenid in sorted(dict.keys()):
  fw.write(str(tokenid) + '\t'  + str(dict[tokenid]) + '\n')
fw.close()


  