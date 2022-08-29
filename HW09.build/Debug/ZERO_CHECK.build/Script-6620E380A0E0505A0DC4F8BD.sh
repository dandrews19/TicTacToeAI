#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/dylanandrews/Desktop/GitHub365/hw09-dandrews19
  make -f /Users/dylanandrews/Desktop/GitHub365/hw09-dandrews19/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/dylanandrews/Desktop/GitHub365/hw09-dandrews19
  make -f /Users/dylanandrews/Desktop/GitHub365/hw09-dandrews19/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/dylanandrews/Desktop/GitHub365/hw09-dandrews19
  make -f /Users/dylanandrews/Desktop/GitHub365/hw09-dandrews19/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/dylanandrews/Desktop/GitHub365/hw09-dandrews19
  make -f /Users/dylanandrews/Desktop/GitHub365/hw09-dandrews19/CMakeScripts/ReRunCMake.make
fi

