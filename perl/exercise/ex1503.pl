#!/usr/bin/perl -w
use 5.010;

foreach (@ARGV) {
    when (-r -w -x $_) {
        print "readable, writable and executable\n";
    }
    when (-r -w $_) {
        print "readable, writable\n";
    }
    when (-r -x $_) {
        print "readable and executable\n";
    }
    when (-x -w $_) {
        print "executable and writable\n";
    }
    when (-r $_) {
        print "readable\n";
    }
    when (-w $_) {
        print "writable\n";
    }
    when (-x $_) {
        print "executable\n";
    }
}

# again better solution
foreach (@ARGV) {
    if (-r $_) {
        print "readable ";
    }
    if (-w _) {
        print "writable ";
    }
    if (-x _) {
        print "executable";
    }
    print "\n";
}

# again better solution by given-when
foreach (@ARGV) {
    when ( not -e ) {
        print "Not existing\n";
        next;
    }
    when ( -r _ ) {
        print " readable ";
        continue
    }
    when ( -x ) {
        print " executable ";
        continue
    }
    when ( -w ) {
        print " writable ";
        continue
    }
    default {
        print "\n";
    }
}
