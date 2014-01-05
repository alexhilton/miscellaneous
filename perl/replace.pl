#!/usr/bin/perl -w
use strict;
my $debug = 1;
sub usage {
    die "usage: replace.pl pattern1 replace1 [pattern2 replace2] - file1 [file2] [file3]\n";
}

if (@ARGV < 4) {
    &usage;
}
my @pairs;
foreach (@ARGV) {
    if ($_ eq "-") {
        last;
    }
    push @pairs, $_;
}
print "patterns is '@pairs'\n" if $debug;
printf "%s %s\n", @pairs == @ARGV, @pairs / 2;
if (@pairs + 1 == @ARGV || @pairs == @ARGV || @pairs % 2 != 0) {
    &usage;
}
my @patterns;
my @replaces;
foreach (my $i = 0; $i <= @pairs/2; $i+=2) {
    push @patterns, shift @ARGV;
    push @replaces, shift @ARGV;
}
print "pattern is '@patterns'\n" if $debug;
print "replaces is '@replaces'\n" if $debug;
shift @ARGV;
$^I = ".bak";
while (<>) {
    for(my $p = 0; $p < @patterns; $p++) {
        s/$patterns[$p]/$replaces[$p]/g;
    }
    print;
}
