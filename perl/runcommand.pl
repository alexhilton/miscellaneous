$source = "D:\\softs\\grub4dos-0.4.4.zip";
$target = substr $source, (rindex($source, "\\")+1);
$target = substr $target, 0, ($target-4);
print "target of $source is $target\n";
$target = "D:\\" . $target;
#make sure WinRAR is in environment path
$winrar = "WinRAR.exe x -y $source $target";
print "The winrar program path is $winrar\n";
print "source file to extract is $source\n";
print "target fold is $target\n";
#mkdir $target, 0755;
#system $winrar; 
# copy directory
$to = "D:\\softs";
#system "xcopy /s /y $target $to";
# an alternative
#$copy = "xcopy";
#system "$copy /s /y $target $to";
$tmpfile = "filenames.txt";
system "dir /b /od > $tmpfile";
open FILE, "<", $tmpfile or die "Cannot open file $tmpfile, $!";
chomp(@lines = <FILE>);
close FILE;
#@lines = reverse @lines;
#print "the files are '$lines[0]'\n";
print "The files are @lines\n";
unlink $tmpfile or warn "Cannot remove file $tmpfile, $!";
print "get files by readdir\n";

$dir = "D:\\work\\perl";
opendir DIR, $dir or die "Cannot open dir $dir, $!\n";
#the order of entries in a directory is not date ascentant
@lines = readdir DIR;
closedir DIR;
print "From readdir is @lines\n";
