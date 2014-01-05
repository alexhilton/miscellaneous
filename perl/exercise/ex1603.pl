#!/usr/bin/perl -w
use 5.010;

my @weekday = (1, 2, 3, 4, 5);
my @weekend = (6, 7);
my $date = `date +%u`;
print "$date";
print "get to work\n" if @weekday ~~ $date;
print "get to work\n" if $date < 6;
print "go to play\n" if $date >= 6;
