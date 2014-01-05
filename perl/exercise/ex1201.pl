#!/usr/bin/perl -w
sub test_file {
    my $file = $_[0];
    print "file: '$file':";
    if ( -r $file ) {
        print "\treadable";
    } else {
        print "\tunreadable";
    }
    if ( -w _ ) {
        print "\twritable";
    } else {
        print "\tunwritable";
    }
    if ( -x _ ) {
        print "\texecutable";
    } else {
        print "\tinexecutable";
    }
    # -e is better choice
    if ( -s _ ) {
        print "\texists\n";
    } else {
        print "\tnonexists\n";
    }
}

foreach (@ARGV) {
    &test_file($_);
}
