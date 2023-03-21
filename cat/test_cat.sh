#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
RES=""

FILE="main.c"
for v1 in b e n s t
do
    ./s21_cat -$v1 $FILE > log1.log
    cat -$v1 $FILE > log2.log
    (( COUNTER++ ))
    RES=$(diff -s log1.log log2.log)
    if [ "$RES" == "Files log1.log and log2.log are identical" ]
    then
        (( SUCCESS++ ))
        echo "SUCCESS \ cat -$v1 $FILE"
    else
        (( FAIL++ ))
        echo "FAIL \ cat -$v1 $FILE"
    fi
    rm -rf log1.log log2.log
done

FILE="test_3_cat.txt"
for v1 in b e n s t
do
    ./s21_cat -$v1 $FILE > log1.log
    cat -$v1 $FILE > log2.log
    (( COUNTER++ ))
    RES=$(diff -s log1.log log2.log)
    if [ "$RES" == "Files log1.log and log2.log are identical" ]
    then
        (( SUCCESS++ ))
        echo "SUCCESS \ cat -$v1 $FILE"
    else
        (( FAIL++ ))
        echo "FAIL \ cat -$v1 $FILE"
    fi
    rm -rf log1.log log2.log
done

FILE="cat.c test_3_cat.txt"
for v1 in b e n s t
do
    ./s21_cat -$v1 $FILE > log1.log
    cat -$v1 $FILE > log2.log
    (( COUNTER++ ))
    RES=$(diff -s log1.log log2.log)
    if [ "$RES" == "Files log1.log and log2.log are identical" ]
    then
        (( SUCCESS++ ))
        echo "SUCCESS \ cat -$v1 $FILE"
    else
        (( FAIL++ ))
        echo "FAIL \ cat -$v1 $FILE"
    fi
    rm -rf log1.log log2.log
done

RESULT=$(( 100*$SUCCESS/$COUNTER ))
echo "--------------------------------------------------"
echo "SUMMARY:$COUNTER -- SUCCESS:$SUCCESS \ FAIL:$FAIL"
echo "$RESULT% SUCCESSED"
echo "--------------------------------------------------"