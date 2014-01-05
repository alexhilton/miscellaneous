#!/usr/bin/perl -w
## Copyright (C) 2012 by Alex Hilton

while (<>) {
    chomp;
    if (/($what){3}/) {
        print "matched:|$`<$&>$'|\n";
    } else {
        print "no match:|$`<$&>$'|\n";
    }
}
