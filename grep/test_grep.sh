#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
RES=""
FFLAG=f

FILE="s21_grep.c"
for v1 in e i v c l n h s f o
do
    if [[ $v1 == "f" ]]
    then
        v1="$v1 file.txt"
    else
        v1="$v1 for"
    fi

    ./s21_grep -$v1 $FILE > log1.log
    grep -$v1 $FILE > log2.log


    (( COUNTER++ ))
    RES=$(diff -s log1.log log2.log)
    if [ "$RES" == "Files log1.log and log2.log are identical" ]
    then
        (( SUCCESS++ ))
        echo "SUCCESS \ grep -$v1 $FILE"
    else
        (( FAIL++ ))
        echo "FAIL \ grep -$v1 $FILE"
    fi
    rm -rf log1.log log2.log
done

FILE="testcopy.txt test.txt"
for v1 in i v c l n h s o
do
    for v2 in e i v c l n h s f o
    do
        if [ $v2 == "f" ]
        then
            v2="$v2 file.txt"
        else
            v2="$v2 grep"
        fi

        ./s21_grep -$v1$v2 $FILE > log1.log
        grep -$v1$v2 $FILE > log2.log


        (( COUNTER++ ))
        RES=$(diff -s log1.log log2.log)
        if [ "$RES" == "Files log1.log and log2.log are identical" ]
        then
            (( SUCCESS++ ))
            echo "SUCCESS \ grep -$v1$v2 $FILE"
        else
            (( FAIL++ ))
            echo "FAIL \ grep -$v1$v2 $FILE"
        fi
        rm -rf log1.log log2.log
    done
done


RESULT=$(( 100*$SUCCESS/$COUNTER ))
echo "--------------------------------------------------"
echo "SUMMARY:$COUNTER -- SUCCESS:$SUCCESS \ FAIL:$FAIL"
echo "$RESULT% SUCCESSED"
echo "--------------------------------------------------"