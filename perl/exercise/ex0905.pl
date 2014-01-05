#!/usr/bin/perl -w

# each file can only have one copyright, so we must examine each file
# and for the file does not have copyright add it.

my %to_do;
foreach (@ARGV) {
    $to_do{$_} = 1;
}

while (<>) {
    if (/^## Copyright/) {
        delete $to_do{$ARGV};
    }
}

@ARGV = sort keys %to_do;
$^I = ".bak";
while (<>) {
    if (/^#!/) {
        $_ .= "## Copyright (C) 2012 by Alex Hilton\n";
    }
    print;
}
