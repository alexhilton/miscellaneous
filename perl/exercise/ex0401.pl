#!/usr/bin/perl -w
use strict;

sub total {
    my $sum = shift @_;
    foreach (@_) {
        $sum += $_;
    }
    return $sum;
}

my @fred = qw{ 1 3 5 7 9};
my $fred_total = &total(@fred);
print "The total of \@fred is $fred_total.\n";
print "Enter some numbers on separate lines.:";
my $user_total = &total(<STDIN>);
print "the total of thoose numbers is $user_total.\n";
