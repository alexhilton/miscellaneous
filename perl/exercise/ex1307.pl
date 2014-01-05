#!/usr/bin/perl -w
die "usage ex1307 [-s] file link\n" if @ARGV < 2;

my $option;
if (@ARGV == 3) {
    $option = shift @ARGV;
    die "usage ex1307 [-s] file link\n" unless $option =~ /^-s$/;
} else {
    $option = "";
}
my($file, $link) = @ARGV;
die "$file not exists\n" unless -e $file;
die "$link already exists\n" if -e $link;
if ($option =~ /^-s$/) {
    symlink $file, $link or die "cannot create symbol link  $link to $file: $!";
} else {
    link $file, $link or die "cannot create hard link $link to $file: $!";
}
