uniqueadsdict = {}
uniqueadsimpresseddict = {}
totalimpressionsdict = {}
uniqueadsclickeddict = {}
totalclicksdict = {}
meanctrdict = {}

f = open('advertiser_properties.txt')
for line in f:
  vec = line.strip().split()
  uniqueads = int(vec[1])
  uniqueadsimpressed = int(vec[2])
  totalimpressions = int(vec[3])
  uniqueadsclicked = int(vec[4])
  totalclicks = int(vec[5])
  
  if uniqueads not in uniqueadsdict: uniqueadsdict[uniqueads] = 0
  uniqueadsdict[uniqueads] += 1
  
  if uniqueadsimpressed not in uniqueadsimpresseddict: uniqueadsimpresseddict[uniqueadsimpressed] = 0
  uniqueadsimpresseddict[uniqueadsimpressed] += 1
  
  if totalimpressions not in totalimpressionsdict: totalimpressionsdict[totalimpressions] = 0
  totalimpressionsdict[totalimpressions] += 1
  
  if uniqueadsclicked not in uniqueadsclickeddict: uniqueadsclickeddict[uniqueadsclicked] = 0
  uniqueadsclickeddict[uniqueadsclicked] += 1
  
  if totalclicks not in totalclicksdict: totalclicksdict[totalclicks] = 0
  totalclicksdict[totalclicks] += 1
  
  ctr = 0.0
  if totalimpressions > 0: ctr = totalclicks / float(totalimpressions)
  if ctr not in meanctrdict: meanctrdict[ctr] = 0
  meanctrdict[ctr] += 1
f.close()

fw = open('advertiser_uniqueads_count.txt', 'w')
for uniqueads in sorted(uniqueadsdict.keys()):
  fw.write( str(uniqueads) + ' ' + str(uniqueadsdict[uniqueads]) + '\n')
fw.close()

fw = open('advertiser_uniqueadsimpressed_count.txt', 'w')
for uniqueadsimpressed in sorted(uniqueadsimpresseddict.keys()):
  fw.write( str(uniqueadsimpressed) + ' ' + str(uniqueadsimpresseddict[uniqueadsimpressed]) + '\n')
fw.close()

fw = open('advertiser_totalimpressions_count.txt', 'w')
for totalimpressions in sorted(totalimpressionsdict.keys()):
  fw.write( str(totalimpressions) + ' ' + str(totalimpressionsdict[totalimpressions]) + '\n')
fw.close()

fw = open('advertiser_uniqueadsclicked_count.txt', 'w')
for uniqueadsclicked in sorted(uniqueadsclickeddict.keys()):
  fw.write( str(uniqueadsclicked) + ' ' + str(uniqueadsclickeddict[uniqueadsclicked]) + '\n')
fw.close()

fw = open('advertiser_totalclicks_count.txt', 'w')
for totalclicks in sorted(totalclicksdict.keys()):
  fw.write( str(totalclicks) + ' ' + str(totalclicksdict[totalclicks]) + '\n')
fw.close()

fw = open('advertiser_ctr_count.txt', 'w')
for ctr in sorted(meanctrdict.keys()):
  fw.write( str(ctr) + ' ' + str(meanctrdict[ctr]) + '\n')
fw.close()