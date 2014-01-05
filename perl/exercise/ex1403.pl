#!/usr/bin/perl -w
my ($string, $pattern) = @ARGV;
die "usage ex1403 string pattern\n" unless defined($string) and defined($pattern);
my $start = 0;
my @occurence;
while ((my $stop = index $string, $pattern, $start) != -1) {
    push @occurence, $stop;
    $start = $stop + length $pattern;
}
print "@occurence\n";
