#!/usr/bin/perl -w
foreach (@ARGV) {
    if ( -d $_ ) {
        print "$_ is a directory\n";
        next;
        # or remove the stuff in the sub directory first
    }
    unlink $_ or warn "failed to remove $_: $!";
}
