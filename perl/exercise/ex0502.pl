#!/usr/bin/perl -w
my @lines;
chomp(@lines = <STDIN>);
print "1234567890" x 6, "\n";
my $format = "%20s\n" x @lines;
printf $format, @lines;
