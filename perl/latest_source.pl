use File::Copy;

$tmpfile = "filenames.txt";
$source_path = '\\\\10.15.11.230\\public1\\ALPS_source\\ALPS.ICS.MP\\';

#find the folder which contains the latest source
system "dir $source_path /b /od > $tmpfile";
open FILE, "<", $tmpfile or die "Cannot open file $tmpfile, $!";
chomp(@lines = <FILE>);
@lines = reverse @lines;
print "target folder is $lines[0]\n";
$source_path = $source_path . $lines[0];
print "source path is $source_path\n";
opendir SOURCES, $source_path or die "Cannot open $source_path, $!\n";
foreach (readdir SOURCES) {
   if (/eagle75v1_2_/) {
       $source = $_;
   }
}
closedir SOURCES;
print "the source is $source\n";
$target_path = 'z:\\source\\';
$target_path = $target_path . $source;
print "target path is $target_path\n";
$target_folder = substr $target_path, 0, ($target_path-4);
print "target folder is $target_folder\n";
die "source $source already exists\n" if -e $target_folder;
$load_file = $source_path . "\\" . $source;
print "the file to copy is $load_file\n";
print "the target path is $target_path\n";
print "Copying the source package, please wait...\n";
copy($load_file, $target_path);

#after copying extract the file
# make sure WinRAR is in envrironment path
print "Extracting the source package...\n";
mkdir $target_folder, 0755 or die "Cannot make directory $target_folder, $!";
system "WinRAR.exe x -y $target_path $target_folder";
print "Deleting file $target_path...\n";
unlink $target_path or warn "Cannot delete file $target_path, $!";
print "get source done";
