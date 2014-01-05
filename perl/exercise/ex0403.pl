#!/usr/bin/perl -w
use strict;

sub sum {
    my $sum = shift @_;
    foreach (@_) {
        $sum += $_;
    }
    return $sum;
}

sub mean {
    # $#_ is 9, but @_ is 10
    # should check whether @_ is 0
    if (@_ == 0) {
        return;
    }
    my $m = &sum(@_) / @_;
    return $m;
}

sub above_average {
    my $m = &mean(@_);
    my @am;
    foreach (@_) {
        if ($_ >= $m) {
            push(@am, $_);
        }
    }
    return @am;
}

my @fred = &above_average(1..10);
print "\@fred is @fred\n";
print "(should be 6 7 8 9 10)\n";
my @barney = &above_average(100, 1..10);
print "\@barney is @barney\n";
print "(should be just 100)\n";
