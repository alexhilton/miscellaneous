#!/usr/bin/env python

from subprocess import *;
import re;
from time import sleep;
from time import time;

pkg_name = "com.tencent.mtt";
activity = "com.tencent.mtt.SplashActivity";

def start():
    check_output("adb shell am start -n " + pkg_name + "/" + activity, shell = True);

def get_mem():
    try:
        output = check_output("adb shell dumpsys meminfo " + pkg_name, shell = True);
        m = re.search("\(Pss\):\s+\d+\s+\d+\s+\d+\s+(\d+)", output);
        if m is not None:
            print m.group(1);
        else:
            print "nothing match";
    except CalledProcessError as e:
        print e;

def something():
    start();
    duration = 20;
    freq = 0.1;
    time = 0;
    while time < duration:
        get_mem();
        sleep(freq);
        time += freq;

def cap_mem():
    comp = pkg_name + "/" + activity;
    seq = ' '.join([str(i) for i in range(100)]);
    start = time();
    output = check_output("adb shell 'am start -n " + comp + ";for i in " + seq + "\ndo\ndumpsys meminfo " + pkg_name + "\ndone'",
            shell = True, universal_newlines = True);
    m = re.findall("\(Pss\):\s+\d+\s+\d+\s+\d+\s+(\d+)", output);
    print m;
    print "length of m is ", len(m);
    end = time();
    print "loop 100 for mem takes %r" % (end - start);

if __name__ == "__main__":
    cap_mem();
