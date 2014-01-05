#!/usr/bin/perl -w
use 5.010;

open FILE, "<", "sample_text.txt" or die "cannot open file 'sample_text.txt: $!";
my @lines = <FILE>;
while (1) {
    print "input your pattern:";
    chomp(my $pattern = <STDIN>);
    last if $pattern =~ /^\s*$/;
    # TODO: check the validation of the pattern
    my @matched_lines = grep /$pattern/, @lines;
    print "@matched_lines\n";
}
