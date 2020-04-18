#!/bin/bash

for filename in inputs/*.in; do
    echo "$filename"
    bin/NTU_sort "$1" "$filename" "outputs/$(basename "$filename" .in)$i.out"
    utility/PA1_Result_Checker "$filename" "outputs/$(basename "$filename" .in)$i.out"
done
