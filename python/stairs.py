#!/usr/bin/env python

count = 0
nlist = range(101)
mlist = range(51)
for n in nlist:
    for m in mlist:
        if n+2*m == 100:
            count += 1
            print "%d, %d" % (n, m)
print "total %d" % count
