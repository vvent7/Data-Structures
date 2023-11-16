#!/usr/bin/env bash

if [ $# -lt 3 ]; then
  echo "usage: ./test.sh <number of tests> <universe size> <number of operations> [-h (stores test cases)]"
  exit 1
elif [ "$1" -le 0 ]; then
  echo "Number of tests must be positive"
  exit 2
elif [ "$2" -le 0 ]; then
  echo "Universe size must be positive"
  exit 3
elif [ "$3" -le 0 ]; then
  echo "Number of operations must be positive"
  exit 4
fi

# compile
make 
make tests

# paths and files
TESTS_PATH=tests
BIN_GEN=${TESTS_PATH}/gen
IN_DIR=${TESTS_PATH}/in
SOL_DIR=${TESTS_PATH}/sol
OUT_DIR=${TESTS_PATH}/out
BIN_VEB=veb

# ARGUMENTS
QT_TESTS=$1
IN_U=$2
IN_N=$3
HISTORY=false

if [ $# -eq 4 ] && [ "$4" == "-h" ]; then
  HISTORY=true
fi

# CREATE DIRECTORIES
mkdir -p ${IN_DIR}
rm -r ${IN_DIR}/*
mkdir -p ${SOL_DIR}
rm -r ${SOL_DIR}/*
mkdir -p ${OUT_DIR}
rm -r ${OUT_DIR}/*


IN_FILE=${IN_DIR}/veb.in
SOL_FILE=${SOL_DIR}/veb.sol
OUT_FILE=${OUT_DIR}/veb.out

# loop ${QT_TESTS} times
for (( i=1; i<=${QT_TESTS}; i++ ))
do
  if [ "$HISTORY" = true ]; then
    IN_FILE=${IN_DIR}/veb_${i}_${IN_U}_${IN_N}.in
    SOL_FILE=${SOL_DIR}/veb_${i}_${IN_U}_${IN_N}.sol
    OUT_FILE=${OUT_DIR}/veb_${i}_${IN_U}_${IN_N}.out
  fi

  # generate test case
  ./${BIN_GEN} ${IN_U} ${IN_N} ${IN_FILE} ${SOL_FILE}

   # run testcase and save output
  ./${BIN_VEB} < ${IN_FILE} &> ${OUT_FILE}

  if cmp -s ${OUT_FILE} ${SOL_FILE}; then
    echo "Test case ${i} passed"
  else
    echo "TEST CASE ${i} FAILED"
    exit 5
  fi
done