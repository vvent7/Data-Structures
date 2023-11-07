#!/usr/bin/env bash

if [ -z "$1" ]; then
  echo "Usage: $0 <number of tests>"
  exit 1
elif [ "$1" -le 0 ]; then
  echo "Number of tests must be positive"
  exit 2
fi

make 
make test-gen

BIN_GEN=./gen
BIN_VEB=./veb
IN_FILE=in
SOL_FILE=sol
OUT_FILE=out

IN_U=256
IN_N=10000
# loop $1 times
for (( i=0; i<$1; i++ ))
do
  $BIN_GEN $IN_U $IN_N
  $BIN_VEB < $IN_FILE > $OUT_FILE
  if cmp -s $OUT_FILE $SOL_FILE; then
    echo "Test case passed"
  else
    echo "Test case failed"
    exit 3
  fi
done
