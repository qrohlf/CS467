#!/bin/bash

for i in {0..3};
    do 
    echo "rendering frame $i"
    bin/lab2.1 lab21-mov $i &
done
wait
echo "Rendering complete"