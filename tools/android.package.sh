#!/bin/bash
# 
# Usages:
#		./android.package.sh {project-path} {application} {package}
#

LIBPATH=${PWD}
ENGINE=${PWD}/libfluo.so
INPUTPATH=$1
OUTPUTPATH=
APPLICATION=$2
PACKAGE=$3
KEYSTORE=${PWD}/android.debug.keystore
KEYSTOREPASS=android
KEYPASS=android
KEYNAME=androiddebugkey

if [ -z ${INPUTPATH} ] 
then
	echo -n "Project Path: "
	read INPUTPATH
fi

if [ -z ${APPLICATION} ] 
then
	echo -n "Application Name: "
	read APPLICATION
fi

if [ -z ${PACKAGE} ] 
then
	echo -n "Package Name: "
	read PACKAGE
fi

OUTPUTPATH=${INPUTPATH}.android.out

mkdir -p ${OUTPUTPATH}
mkdir -p ${OUTPUTPATH}/bin
mkdir -p ${OUTPUTPATH}/obj
mkdir -p ${OUTPUTPATH}/src
mkdir -p ${OUTPUTPATH}/res/values
mkdir -p ${OUTPUTPATH}/libs
mkdir -p ${OUTPUTPATH}/bin/lib/armeabi
cp -a ${INPUTPATH}/* ${OUTPUTPATH}/bin
cp ${ENGINE} ${OUTPUTPATH}/bin/lib/armeabi
sed -e "s/package=\"PackageName\"/package=\"${PACKAGE}\"/g" \
	${LIBPATH}/android.manifest.xml > ${OUTPUTPATH}/AndroidManifest.xml
sed -e "s/<string name=\"app_name\">ApplicationName<\/string>/<string name=\"app_name\">${APPLICATION}<\/string>/g" \
	${LIBPATH}/android.strings.xml > ${OUTPUTPATH}/res/values/strings.xml

echo '@ Generating Java Classes..'
aapt package -v -f -m \
	-S ${OUTPUTPATH}/res \
	-J ${OUTPUTPATH}/src \
	-M ${OUTPUTPATH}/AndroidManifest.xml \
	-I ${ANDROID_SDK}/platforms/android-17/android.jar
echo ' '

echo '@ Compiling Java Classes..'
javac -verbose \
	-d ${OUTPUTPATH}/obj \
    -classpath ${ANDROID_SDK}/platforms/android-17/android.jar:${OUTPUTPATH}/obj \
    -sourcepath ${OUTPUTPATH}/src \
    ${OUTPUTPATH}/src/${PACKAGE//./\//}/*.java
echo ' '

echo '@ Generating DEX..'
dx --dex --verbose \
	--output=${OUTPUTPATH}/bin/classes.dex \
    ${OUTPUTPATH}/obj \
    ${OUTPUTPATH}/libs
echo ' '
    
echo '@ Packaging Unsigned APK..'
aapt package -v -f \
	-M ${OUTPUTPATH}/AndroidManifest.xml \
    -S ${OUTPUTPATH}/res \
    -I ${ANDROID_SDK}/platforms/android-17/android.jar \
    -F ${OUTPUTPATH}/${APPLICATION}.unsigned.apk \
    ${OUTPUTPATH}/bin
echo ' '

echo '@ Signing APK..'
jarsigner -verbose \
    -keystore ${KEYSTORE} \
    -storepass ${KEYSTOREPASS} \
 	-keypass ${KEYPASS} \
	-signedjar ${OUTPUTPATH}/${APPLICATION}.signed.apk \
    ${OUTPUTPATH}/${APPLICATION}.unsigned.apk \
	${KEYNAME}
echo ' '

echo '@ Zip-Aligning APK..'
zipalign -v -f 4 \
	${OUTPUTPATH}/${APPLICATION}.signed.apk \
	${OUTPUTPATH}/${APPLICATION}.apk
echo ' '
