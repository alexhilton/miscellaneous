#!/usr/bin/perl -w
my @lines;
chomp(@lines = <STDIN>);
my $width = shift @lines;
my $format = "%${width}s\n" x @lines;
my $ruler;
if ($width % 10 == 0) {
    $ruler = "1234567890" x ($width / 10);
} else {
    my $rem = $width % 10;
    $width /= 10;
    $ruler = "1234567890" x $width;
    foreach (1..${rem}) {
        $ruler .= $_;
    }
}

print "$ruler\n";
printf $format, @lines;
