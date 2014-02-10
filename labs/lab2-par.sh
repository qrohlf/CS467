#!/bin/sh

make lab2

for i in {0..30};
    do 
    echo $i
    bin/lab2 prefix $i $i &
done