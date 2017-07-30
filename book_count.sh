#!/bin/sh
#openings=`grep "book\[\"1" src/book.cpp  | wc -l | sed "s/ //g"`
openings=`grep "book\[\"1" src/book.cpp  | wc -l | sed "s/ //g"`
let openings=openings+1
echo "Number of book moves: $openings."
