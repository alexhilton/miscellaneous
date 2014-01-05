#!/usr/bin/perl -w
@files = <*>;
print "@files\n";
foreach (@files) {
    printf "$_ --> %s\n", readlink $_ if -l $_;
}
