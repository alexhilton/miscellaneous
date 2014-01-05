#!/usr/bin/perl -w
foreach (@ARGV) {
    print "$_ is your file, readable and writable\n" if -o -r -w $_;
}
