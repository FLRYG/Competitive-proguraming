#!/bin/sh

declare str_a='in/input'
declare str_b='.txt'
declare -i i
for (( i=0; $i < 50 ; ++i )); do
    declare num=$i
    declare path=$str_a$num$str_b
    python3 generator.py $i > $path
done

# python3 generator.py 0 > in/input0.txt
