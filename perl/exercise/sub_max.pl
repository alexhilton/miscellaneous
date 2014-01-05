#!/bin/perl

sub max {
    my ($m, $n) = @_;
    if ($m > $n) {
        $m;
    } else {
        $n;
    }
}

print &max(5, 4);
