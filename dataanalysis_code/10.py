dict = {}

f = open('queryid_tokensid.txt')
for line in f:
  delimitedtokens = line.strip().split()[-1]
  numtokens = len(delimitedtokens.split('|'))
  if numtokens not in dict: dict[numtokens] = 0
  dict[numtokens] += 1
f.close()

fw = open('analysis_queryid_numtokens.txt', 'w')
for numtokens in sorted(dict.keys()):
  fw.write( str(numtokens) + ' ' + str(dict[numtokens]) + '\n' )
fw.close()