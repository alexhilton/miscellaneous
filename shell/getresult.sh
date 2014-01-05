#!/bin/sh
PROJECT=OMADRMImageFLTest
WORKSPACE=~/workspace/$PROJECT/
CTS=$WORKSPACE/cts
HOST=out/host/linux-x86/framework
APK=out/target/product/eagle75v1_2/system/app
echo "copying compiled apks from '$APK' to '$CTS'";
cp $HOST/com.mtk.automation.app.omadrmimagefltest.jar $CTS
#cp $APK/com.mtk.automation.app.omadrmimage01oktest.apk $CTS
#cp $APK/com.mtk.automation.app.omadrmimageopenwifitest.apk $CTS
#cp $APK/com.mtk.automation.app.omadrmimagecanceltest.apk $CTS
#cp $APK/com.mtk.automation.app.omadrmimagedeletetest.apk $CTS
#cp $APK/com.mtk.automation.app.omadrmimagedownloadtest.apk $CTS
#cp $APK/com.mtk.automation.app.omadrmimagestatusbartest.apk $CTS
cp $APK/com.mtk.automation.app.omadrmimage*test.apk $CTS

cp -r $WORKSPACE/push_to_pc $CTS
