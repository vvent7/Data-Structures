#!/usr/bin/env bash


path="datasets"
curdir=$(pwd)
datasets="${curdir}/datasets"
queries="${curdir}/queries"

find "$path" -type f -print | sort | while read -r arquivo;
    do
        echo "$(basename $arquivo)"
        > "config"
        printf "dataset=${datasets}/$(basename $arquivo)\nquery=${queries}/$(basename $arquivo)\ntype=main_time" > "config"
            ./build/bin/dijkstra
            ./build/bin/rdijkstra
            ./build/bin/rdijkstra-v2
            ./build/bin/rauction
            ./build/bin/rauction-v2
    done

