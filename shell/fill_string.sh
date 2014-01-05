#!/bin/sh

WORKSPACE=$PWD
APP_DIR=packages/apps
APP_CALENDAR=$APP_DIR/Calendar
APP_MMS=$APP_DIR/Mms
# collect strings
STRING_FILE=calendar_string
cd $APP_CALENDAR/res
grep -r "app_label" ./values* > $STRING_FILE
mv $STRING_FILE $WORKSPACE/$APP_MMS/res

cd $WORKSPACE/$APP_MMS/res
TMP_FILE=tempfile_temp.file
sed "s/app_label/attach_vcalendar/g" $STRING_FILE > $TMP_FILE
rm $STRING_FILE
mv $TMP_FILE $STRING_FILE
IFS=:
while read filename line;
do
    #echo $filename;
    #echo $line;
    # append the line after the line matching 'file_attachment_vcard_name'
    sed "/file_attachment_vcard_name/a $line" $filename > $TMP_FILE;
    rm $filename;
    mv $TMP_FILE $filename;
    # add leading four spaces to newly added line
    sed "/<string name=\"attach_vcalendar\"/s/^/    /" $filename > $TMP_FILE;
    rm $filename;
    mv $TMP_FILE $filename;
done < $STRING_FILE;
rm $STRING_FILE;
