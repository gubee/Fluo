#!/bin/bash

PROJECTDIR=${PWD}

keytool -genkeypair -validity 10000 \
	-dname "CN=Android Debug,O=Android,C=US" \
	-keystore ${PROJECTDIR}/debug.keystore \
	-storepass android \
	-keypass android \
	-alias androiddebugkey \
	-keyalg RSA \
	-v