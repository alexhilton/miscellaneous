$tmpfile = "filenames.txt";
$load_path = '\\\\10.15.11.230\\public1\\ALPS_load\\ALPS.ICS.MP\\';
# find the folder which contains latest load
system "dir $load_path /b /od > $tmpfile";
open FILE, "<", $tmpfile or die "Cannot open file $tmpfile, $!";
chomp(@lines = <FILE>);
@lines = reverse @lines;
close FILE;
print "target folder is $lines[0]\n";
unlink $tmpfile or warn "Cannot delete file $tmpfile, $!";
$load_path = $load_path . $lines[0];
print "load path is $load_path\n";

# find the correct load
opendir LOADS, $load_path or die "Cannot open $load_path, $!\n";
foreach (readdir LOADS) {
   if (/eagle75v1_2_/) {
       $load = $_;
   }
}
closedir LOADS;

$target_path = 'z:\\alps_load\\';

# check whether already have the load
print "the load is $load\n";
$target_path = $target_path . $load;
print "target path is $target_path\n";
die "load $load already exists\n" if -e $target_path;
mkdir $target_path, 0755 or die "Cannot create directory $target_path, $!";
# copy load into our folder
$load_file = $load_path . "\\" . $load;
print "the file to copy is $load_file\n";
print "the target path is $target_path\n";
system "xcopy /s /y $load_file $target_path";
print "get load done!\n";
