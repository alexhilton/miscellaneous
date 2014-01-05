#!/usr/bin/env python

from subprocess import check_output;
from subprocess import CalledProcessError;
from subprocess import STDOUT;
from time import time;
import re;

def get_mem():
    start = time();
    pkg_name = "com.tencent.mtt";
    output = check_output("adb shell 'am start -n com.tencent.mtt/com.tencent.mtt.SplashActivity; top -d 0.1 -n 100'",
            stderr = STDOUT, shell = True, universal_newlines = True);
    m = re.findall("\d+\s+(\d+)%.+?" + pkg_name + "\n", output);
    print m;
    print "lenth of m ", len(m);
    end = time();
    print "100 loops 0.1 per loop, takes %r" % (end - start);

if __name__ == "__main__":
    get_mem();
