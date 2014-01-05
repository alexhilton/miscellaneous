#!/usr/bin/perl -w

sub divisors {
    my $number = shift;
    my @divisors = ();
    foreach my $divisor (2 .. $number/2) {
        push @divisors, $divisor unless $_ % $divisor;
    }
    return @divisors;
}

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
    print "@divisors\n";
}
