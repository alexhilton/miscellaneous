#!/bin/sh
SOURCE=OMADRMImageCDTest/test-app/
APP_DIR=packages/apps
PKG=OMADRMImageCDFileManagerOpenTest
echo "compiling $PKG";
if [ -d $APP_DIR/$PKG ]
then
    rm -fr $APP_DIR/$PKG
fi
cp -r $HOME/workspace/$SOURCE/$PKG $APP_DIR
makeMtk mm $APP_DIR/$PKG
