#!/usr/bin/perl
## Copyright (C) 2012 by Alex Hilton
$^I = ".bak";
while (<>) {
    if (/^#!/) {
        $_ .= "## Copyright (C) 2012 by Alex Hilton\n";
    }
    print;
}
