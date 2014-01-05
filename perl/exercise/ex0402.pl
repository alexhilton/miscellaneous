#!/usr/bin/perl -w
use strict;

sub total {
    my $sum = shift @_;
    foreach (@_) {
        $sum += $_;
    }
    return $sum;
}

my $t = &total(1..1000);
print "sum of (1..1000) is $t\n";
