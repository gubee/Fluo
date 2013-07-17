#!/bin/bash

########################################################################
# Set dirrectory path and name
########################################################################
mainDir=~/Documents/Library/Fluo

toolChainPath=${mainDir}/Toolchains
emscriptenDir=Emscripten
flasccDir=FlasCC
mingwDir=MinGW-W64
androidNDKDir=Android-NDK
androidSDKDir=Android-SDK

javaScriptEnginePath=${mainDir}/JavaScriptEngines
v8Dir=V8
spiderMonkeyDir=SpiderMonkey
javaScriptCoreDir=JavaScriptCore

linkToolChainDir=${mainDir}/ToolChains/Links

########################################################################
# Install Homebrew
########################################################################
ruby -e "$(curl -fsSkL raw.github.com/mxcl/homebrew/go)"

########################################################################
# Install node.js, closure-compiler, yuicompressor, llvm, mercurial
########################################################################
brew install node 
brew install closure-compiler
brew install yuicompressor
brew install llvm --with-clang
brew install mercurial

########################################################################
# Download Toolchains
########################################################################
mkdir -p $linkToolChainDir
mkdir -p $toolChainPath

#-----------------------------------------------------------------------
echo "###### wget minGW ######"
#-----------------------------------------------------------------------
if [ ! -d $toolChainPath/$mingwDir ]
then
	downloadMingwVer=mingw-w64-bin_i686-darwin_20130622 # download version file name on sourceforge.net
	mkdir -p $toolChainPath/$mingwDir
	cd $toolChainPath/$mingwDir
	wget http://sourceforge.net/projects/mingw-w64/files/${downloadMingwVer}.tar.bz2
	tar -xvf ${downloadMingwVer}.tar.bz2
	rm -r ${downloadMingwVer}.tar.bz2
else
	echo "minGW arleady installed"
fi

if [ ! -d $linkToolChainDir/$mingwDir ]
then
	ln -s $toolChainPath/$mingwDir $linkToolChainDir/$mingwDir
fi
	
#-----------------------------------------------------------------------
echo "###### wget androidNDK ######"
#-----------------------------------------------------------------------
if [ ! -d $toolChainPath/$androidNDKDir ]
then
	downloadAndroidNDKVerName=android-ndk-r8e
	downloadAndroidNDKVer=android-ndk-r8e-darwin-x86_64.tar.bz2
	cd $toolChainPath
	wget http://dl.google.com/android/ndk/${downloadAndroidNDKVer}.tar.bz2
	tar -xvf ${downloadAndroidNDKVer}.tar.bz2
	rm -r ${downloadAndroidNDKVer}.tar.bz2
	mv $toolChainPath/$downloadAndroidNDKVerName $toolChainPath/$androidNDKDir
else
	echo "androidNDK arleady installed"
fi

if [ ! -d $linkToolChainDir/$androidNDKDir ]
then
	ln -s $toolChainPath/$androidNDKDir $linkToolChainDir/$androidNDKDir
fi

#-----------------------------------------------------------------------
echo "###### git emscripten ######"
#-----------------------------------------------------------------------
if [ -d $toolChainPath/$emscriptenDir/.git ]
then
	cd $toolChainPath/$emscriptenDir
	git pull
else
	cd $toolChainPath
	git clone --depth 1 git://github.com/kripken/emscripten.git $emscriptenDir
fi

if [ ! -d $linkToolChainDir/$emscriptenDir ]
then
	ln -sf $toolChainPath/$emscriptenDir $linkToolChainDir/$emscriptenDir
fi

#-----------------------------------------------------------------------
echo "###### git flascc ######"
#-----------------------------------------------------------------------
if [ -d $toolChainPath/$flasccDir/.git ]
then
	cd $toolChainPath/$flasccDir
	git pull
else
	cd $toolChainPath
	git clone --depth 1 git://github.com/adobe-flash/crossbridge.git $flasccDir
fi

if [ ! -d $linkToolChainDir/$flasccDir ]
then
	ln -sf $toolChainPath/$flasccDir $linkToolChainDir/$flasccDir
fi

########################################################################
# Download JavaScripteEngines
########################################################################
mkdir -p $javaScriptEnginePath
cd $javaScriptEnginePath

echo "###### git v8 ######"
if [ -d $javaScriptEnginePath/$v8Dir/.git ]
then
	cd $javaScriptEnginePath/$v8Dir
	git pull
else
	git clone --depth 1 git://github.com/v8/v8.git $v8Dir
fi

echo "###### git spidermonkey ######"
if [ -d $javaScriptEnginePath/$spiderMonkeyDir/.git ]
then
	cd $javaScriptEnginePath/$spiderMonkeyDir
	git pull
else
	git clone --depth 1 https://github.com/mozilla/mozilla-central.git $spiderMonkeyDir
fi

echo "###### git webkit ######"
if [ -d $javaScriptEnginePath/$javaScriptCoreDir/.git ]
then
	cd $javaScriptEnginePath/$javaScriptCoreDir
	git pull
else
	git clone --depth 1 https://github.com/WebKit/webkit.git $javaScriptCoreDir
fi

########################################################################
# Download Others
########################################################################

#-----------------------------------------------------------------------
echo "###### wget androidSDK ######"
#-----------------------------------------------------------------------
if [ ! -d $mainDir/$androidSDKDir ]
then
	downloadAndroidSDKVer=adt-bundle-mac-x86_64-20130522
	cd $mainDir
	wget http://dl.google.com/android/adt/${downloadAndroidSDKVer}.zip
	tar -xvf ${downloadAndroidSDKVer}.zip
	rm -r ${downloadAndroidSDKVer}.zip
	downloadAndroidSDKVerName=$(echo "adt-*")
	echo $downloadAndroidSDKVerName
	if [ -d $mainDir/$downloadAndroidSDKVerName ]; then
		mv $mainDir/$downloadAndroidSDKVerName $mainDir/$androidSDKDir
	fi
else
	echo "androidSDK arleady installed"
fi


echo "Download is finished, type the following in terminal"
echo "export FLUO_TOOLCHAINS=$linkToolChainDir > ~/.profile"
#export FLUO_TOOLCHAINS=$linkToolChainDir > ~/.profile
