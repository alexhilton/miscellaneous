#!/usr/bin/perl -w

$in = @ARGV[0];
unless (defined $in) {
    die "usage: $0 filename";
}

$out = $in;
$out =~ s/(\.\w+)?$/\.out/;

unless (open IN, "<$in") {
    die "cannot opne $in, $!";
}

unless (open OUT, ">$out") {
    die "cannot write to $out, $!";
}

while (<IN>) {
    s/fred/larry/gi;
    print OUT $_;
}
