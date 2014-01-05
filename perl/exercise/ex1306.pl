#!/usr/bin/perl -w
my ($file, $link) = @ARGV;
die "usage link file\n" unless defined($link) and defined($file);
die "$link is an existing file\n" if -e $link;
die "$file is not existing\n" unless -e -f $file;
link $file, $link or die "cannot link $link to $file: $!\n";
