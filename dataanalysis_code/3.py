import time

f = open('training_original.txt')
fwdispurl = open('training_original_displayurl.txt', 'w')
fwadvertiser = open('training_original_advertiser.txt', 'w')
lineno = 0
start_clock = time.clock()
for line in f:
  vec = line.strip().split()
  fwdispurl.write(vec[2] + ' ' + vec[11] + ' ' + vec[0] + ' ' + vec[1] + '\n')
  fwadvertiser.write(vec[4] + ' ' + vec[3] + ' ' + vec[0] + ' ' + vec[1] + '\n')
  
  lineno += 1
  if lineno % 1000000 == 0: print lineno, 'lines processed in ', time.clock() - start_clock, 'seconds'
  if lineno < 5: print vec[:5], vec[11]
fwadvertiser.close()  
fwdispurl.close()
f.close()