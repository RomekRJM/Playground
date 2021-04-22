#!/bin/bash

JAVA_HOME=/usr/lib/jvm/java-8-openjdk-armhf
WORKDIR=/opt
JAVA_OPTIONS=" -Xms64m -Xmx128m -server "
APP_OPTIONS=""

cd $WORKDIR
"${JAVA_HOME}/bin/java" $JAVA_OPTIONS -jar /opt/finance.jar $APP_OPTIONS
