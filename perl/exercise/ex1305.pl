#!/usr/bin/perl -w
use File::Basename;
use File::Spec;

my( $from, $to ) = @ARGV;
die "usage ex1303.pl from to\n" unless defined($from) and defined($to);
die "cannot find file $from" unless -e $from;

if ( -e -f $to ) {
    die "cannot move $from to $to because $to is an existing file\n";
} elsif ( -e $to ) {
    # moving
    my $file = basename $from;
    open FILE, "<", $from or die "cannot move $from to $to:$!";
    open OUT, ">", File::Spec->catfile($to, $file) or warn "cannot move $from to $to: $!";
    while (<FILE>) {
        print OUT;
    }
    close OUT;
    unlink $from or warn "failed to remove $file: $!";
} else {
    # renaming
    rename $from, $to or warn "cannot rename $from to $to: $!";
}
