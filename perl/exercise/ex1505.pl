#!/usr/bin/perl -w
use 5.010;

sub divisors {
    my $number = shift;
    my @divisors = ();
    foreach my $divisor (2 .. $number/2) {
        push @divisors, $divisor unless $_ % $divisor;
    }
    return @divisors;
}

my $favorite = 5;
my @empty = ();
foreach (@ARGV) {
    if ($_ ~~ /[\D]+/i) {
        print "invalid argument '$_', number is required\n";
        next;
    }
    my @divisors = &divisors($_);
    if (@divisors ~~ @empty) {
        print "Prime\n";
        next;
    }
    # todo: what the hell? the following smart match does not match
    when (@divisors ~~ 2) {
        print ":even:";
        continue
    }
    if (@divisors ~~ 2) {
        print ":Even: ";
    } 
    unless (@divisors ~~ 2) {
        print ":Odd: ";
    }
    if (@divisors ~~ $favorite) {
        print ": Divisible by $favorite: ";
    } 
    unless (@divisors ~~ $favorite) {
        print ": indivisible by $favorite: ";
    }
    print "@divisors\n";
}
