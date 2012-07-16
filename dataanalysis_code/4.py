import time
dict = {}

f = open('training.txt')
lineno = 0
start_clock = time.clock()
for line in f:
  vec = line.strip().split()
  
  adid = int(vec[3])
  dispurl = int(vec[2])
  titleid = int(vec[9])
  descriptionid = int(vec[10])
  dict[adid] = (titleid, descriptionid, dispurl)
  
  lineno += 1
  if lineno % 1000000 == 0: print lineno, 'lines processed in ', time.clock() - start_clock, 'seconds'
  if lineno < 5: print adid, dispurl, titleid, descriptionid
f.close()

fw = open('adid_title_desc_dispurl.txt', 'w')
for adid in sorted(dict.keys()):
  tuple = dict[adid]
  fw.write(str(adid) + ' ' + str(tuple[0]) + ' ' + str(tuple[1]) + ' ' + str(tuple[2]) + '\n')
fw.close()

