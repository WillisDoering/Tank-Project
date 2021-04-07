xhost +local:root

docker run -ti \
	-v "`pwd`":/home/dev/platform \
	-v /tmp/.X11-unix:/tmp/.X11-unix \
	-e DISPLAY=$DISPLAY \
	slackers sh -c 'cd /home/dev/platform && bash'
