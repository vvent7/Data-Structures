#!/usr/bin/env bash

make clean
make
. set_enviroment.sh
path="out"
./"$path"/run_dataset.sh > "$path"/in
g++ "$path"/process.cpp -o "$path"/pcs
./"$path"/pcs < "$path"/in > "$path"/out.csv

rm "$path"/in
rm "$path"/pcs