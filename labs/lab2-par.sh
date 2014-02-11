#!/bin/bash

for i in {0..30};
    do 
    echo "rendering frame $i"
    bin/lab2 lab2-mov $i $i &
done
wait
echo "Rendering complete"