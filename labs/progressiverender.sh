#!/bin/sh
make final-project smash # compile
rm -f output.xwd
# Xvfb :30 -ac -screen 0 900x900x24 # start framebuffer # FUCK YOU X11
# sleep 2
# echo "done with xvfb stuff"

for i in {0..20}; do
	bin/final-project $i $i & 				#render the image
	RENDER=$!
	wait $RENDER
	bin/smash $i $i 								#HULK SMASH
	kill $SHOW
	xwud -in output.xwd & #show the temp result
	SHOW=$!
done