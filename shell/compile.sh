#!/bin/sh

PROJECT=OMADRMImageCDTest
JAR=com.mtk.automation.app.omadrmimagecdtest.jar
WORKSPACE=~/workspace/$PROJECT/
CTS=$WORKSPACE/cts
echo "clearing old stuff in '$CTS'";
find $WORKSPACE -name "*~" -print | xargs rm
rm $CTS/$JAR
rm $CTS/com.mtk.automation.app.omadrmimage*test.apk
rm -fr $CTS/push_to_pc
HOST=out/host/linux-x86/framework
APK=out/target/product/eagle75v1_2/system/app
echo "clearing old stuff in '$APK'";
rm $HOST/$JAR
rm $APK/com.mtk.automation.app.omadrmimage*test.apk

echo "compiling apks";
APP_DIR=cts/apps
if [ -d $APP_DIR/$PROJECT ]
then
    rm -fr $APP_DIR/$PROJECT
fi
cp -r $HOME/workspace/$PROJECT $APP_DIR
makeMtk mm $APP_DIR/$PROJECT

echo "copying compiled apks from '$APK' to '$CTS'";
cp $HOST/$JAR $CTS
cp $APK/com.mtk.automation.app.omadrmimage*test.apk $CTS

cp -r $WORKSPACE/push_to_pc $CTS

# copying apks in FL test to cts
#cp ~/workspace/OMADRMImageFLTest/cts/com.mtk.automation.app.omadrmimage*test.apk $CTS
