#!/bin/sh
make clean >/dev/null 2>/dev/null
files=`find src -type f`
fn=`find src -type f | wc -l | sed -e 's/^[ \t]*//'`
srccount=`for i in $files; do wc -l $i; done | awk '{ sum+=$1} END {print sum}'`
echo "Chess0 codebase:"
echo "Number of files: $fn"
echo "Number of lines: $srccount"
echo "(Please run 'make' again to build the application)"
