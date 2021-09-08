#!/bin/sh

declare source_file='../A1.cpp'
declare in_a='in/input'
declare in_b='.txt'
declare output='../out.txt'
declare result='../result50.txt'
declare scr='scr.txt'
declare -i score=0    

cd tester/

g++ -O2 $source_file
g++ -o t.out tester50.cpp 

: > $result
: > $scr

declare -i i
for (( i=0; $i < 50 ; ++i )); do
    declare input=$in_a$i$in_b
    ../a.out < $input > $output 
    ./t.out $input $output $result $scr $i
    echo $i
done

for j in `cat $scr`
do
    score=`echo "$score + $j" | bc`   # bcコマンドによる足し算
done
echo $score                     # 結果を出力

exit 0