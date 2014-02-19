#!/bin/bash
INCREMENT=5

for ((i=0; i < $1 ; i=i+5))
do
    echo $i
    echo "########################"
    echo "# Rendering frames $i-$(($i+5))"
    echo "########################"
    for ((j=i; j<=i+5; j++));
    do
        bin/lab2.1 lab21-mov $j &
    done
    wait
done
echo "Rendering complete"