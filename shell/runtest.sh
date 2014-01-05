#!/bin/sh
if [ $# -lt 1 ]
then
    CTS_LOOP=1
else
    CTS_LOOP=$1
fi
WORKSPACE=$PWD
# make sure CTS_HOME points to right place in which cts tools are
CTS_HOME=/home/am/cts/Util
SDCARDCTS=/sdcard/cts
CTS=cts
rm -fr $CTS
if [ ! -d $CTS ]
then
    mkdir $CTS
fi
adb pull $SDCARDCTS ./$CTS
CTS_FRAMEWORK=$CTS_HOME/cts_framework/framework
CTS_TOOLS=$CTS_HOME/cts_framework/android-cts/tools
CTS_PLANS=$CTS_HOME/cts_framework/android-cts/repository/plans
CTS_TESTCASES=$CTS_HOME/cts_framework/android-cts/repository/testcases

# move *.apk, *.jar, *.xml into right destinations
mv $CTS/*.apk $CTS_TESTCASES
mv $CTS/*.jar $CTS_TESTCASES
mv $CTS/*.xml $CTS_TESTCASES
find $CTS_TOOLS -name "OMADRMImage*" -exec rm -rf {} ';'
mv -uf $CTS/push_to_pc/* $CTS_TOOLS

TMP_FILE=Plans.xml_bak
PLAN_FILE=$CTS_FRAMEWORK/Plans.xml
mv $CTS_FRAMEWORK/Plans.xml $TMP_FILE
cp $WORKSPACE/omadrm_image.xml $CTS_PLANS
cp $WORKSPACE/Plans.xml $CTS_FRAMEWORK

#start running
cd $CTS_FRAMEWORK
./letGo

cd $WORKSPACE
rm $PLAN_FILE
mv $TMP_FILE $PLAN_FILE
#sleep 5
CTS_RESULT=$CTS_HOME/cts_framework/android-cts/repository/results
cd $CTS_RESULT
#collect result
grep -hrin "test_omadrm_" *
#find . -name "testResult.xml" -exec firefox -browser {} ';'

# backup runtest.sh omadrm_image.xml and Plans.xml
cd $WORKSPACE
adb push runtest.sh /sdcard/ctstools
adb push omadrm_image.xml /sdcard/ctstools
adb push Plans.xml /sdcard/ctstools
adb push preparetest.sh /sdcard/ctstools
