#!/bin/bash

xhost +local:root

docker run -ti \
       -e DISPLAY=$DISPLAY \
       -v /tmp/.X11-unix:/tmp/.X11-unix \
       -v "`pwd`":/root \
       slacker sh -c 'cd /root && export LD_PATH=$LD_LIBRARY_PATH:.:./libraries && ./platform'

