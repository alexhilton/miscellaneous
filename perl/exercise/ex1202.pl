#!/usr/bin/perl -w
my $modified = -99999;
my $file = undef;
foreach (@ARGV) {
    if ($modified < -M $_) {
        $file = $_;
    }
}
print "$file is oldest\n" if defined($file);
