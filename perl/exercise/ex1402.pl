#!/usr/bin/perl -w
my %last_name = qw {
    fred flintstone Wilma Flintstone Barney Rubble
    betty rubble Bamm-Bamm Rubble PEBBLES FLINTSTONE
};
my @given_names = sort {"\L$last_name{$a}" cmp "\L$last_name{$b}" or
    "\L$a" cmp "\L$b"} keys %last_name;

foreach (@given_names) {
    print "$_ --> $last_name{$_}\n";
}
