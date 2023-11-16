#!/usr/bin/env bash

# usage: ./test.sh <number of tests> <universe size> <number of operations>

if [ $# -lt 3 ]; then
  echo "usage: ./test.sh <number of tests> <universe size> <number of operations>"
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

make 
make tests

TESTS_PATH=tests
BIN_GEN=gen
IN_DIR=in
SOL_DIR=sol
OUT_DIR=out

BIN_VEB=veb

QT_TESTS=$1
IN_U=$2
IN_N=$3

# create directories
mkdir -p ${TESTS_PATH}/${IN_DIR}
rm -r ${TESTS_PATH}/${IN_DIR}/*
mkdir -p ${TESTS_PATH}/${SOL_DIR}
rm -r ${TESTS_PATH}/${SOL_DIR}/*
mkdir -p ${TESTS_PATH}/${OUT_DIR}
rm -r ${TESTS_PATH}/${OUT_DIR}/*

# loop $1 times
for (( i=0; i<${QT_TESTS}; i++ ))
do
  IN_FILE=${IN_DIR}/veb_${i}_${IN_U}_${IN_N}.in
  SOL_FILE=${SOL_DIR}/veb_${i}_${IN_U}_${IN_N}.sol
  OUT_FILE=${OUT_DIR}/veb_${i}_${IN_U}_${IN_N}.out

  echo ${IN_FILE} ${SOL_FILE} ${OUT_FILE}

  # generate test case
  (cd ${TESTS_PATH} && ./${BIN_GEN} ${IN_U} ${IN_N} ${IN_FILE} ${SOL_FILE}) 

   # run testcase and save output
  ./${BIN_VEB} < ${TESTS_PATH}/${IN_FILE} &> ${TESTS_PATH}/${OUT_FILE}

  if cmp -s ${TESTS_PATH}/${OUT_FILE} ${TESTS_PATH}/${SOL_FILE}; then
    echo "Test case ${i} passed"
  else
    echo "TEST CASE ${i} FAILED"
    exit 5
  fi
done