#!/bin/sh
PROJECT=OMADRMImageFLTest
WORKSPACE=~/workspace/$PROJECT/
CTS=$WORKSPACE/cts
echo "clearing old stuff in '$CTS'";
find $WORKSPACE -name "*~" -print | xargs rm
rm $CTS/com.mtk.automation.app.omadrmimagefltest.jar
rm $CTS/com.mtk.automation.app.omadrmimage*test.apk
rm -fr $CTS/push_to_pc
HOST=out/host/linux-x86/framework
APK=out/target/product/eagle75v1_2/system/app
echo "clearing old stuff in '$APK'";
rm $HOST/com.mtk.automation.app.omadrmimagefltest.jar
rm $APK/com.mtk.automation.app.omadrmimage*test.apk
