import time
dict = {}

f = open('queryid_tokensid.txt')
lineno = 0
start_clock = time.clock()
for line in f:
  delimitedtokens = line.strip().split()[-1]
  tokens = delimitedtokens.split('|')
  for tokenstr in tokens:
    tokenid = int(tokenstr)
    if tokenid not in dict: dict[tokenid] = 0
    dict[tokenid] += 1
    
  lineno += 1
  if lineno % 1000000 == 0: print lineno, 'lines processed in ', time.clock() - start_clock, 'seconds'
  if lineno < 5: print line.strip().split()[0], tokens
f.close()

fw = open('analysis_queryid_tokensid.txt', 'w')
for tokenid in sorted(dict.keys()):
  fw.write(str(tokenid) + '\t'  + str(dict[tokenid]) + '\n')
fw.close()


  