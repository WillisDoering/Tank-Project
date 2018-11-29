
FROM ubuntu:16.04

RUN apt update && apt install sudo

#create a user (dev), add it to wheel, and set up sudo to allow wheel without password.
#dev's password is dev if it is ever needed.
RUN export user=dev ROS_DISTRO=ardent && \
    mkdir -p /home/${user} && \
    mkdir -p /home/${user}/shr && \
    useradd ${user} && \
    groupadd wheel && \
    usermod -a -G wheel ${user} && \
    echo "%wheel ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers && \
    echo "${user}:${user}" | chpasswd && \
    chown -R dev /home/dev

#set the user and home in Docker
USER dev

ENV HOME /home/dev

#set the command for docker run to bash
CMD /bin/bash


# apt-get and install tools
RUN sudo apt-get update
RUN sudo apt-get install -y make gcc g++ lcov freeglut3-dev git

# remove apt files after installs
RUN sudo rm -rf /var/lib/apt/lists/*

COPY .gitconfig /home/dev/.gitconfig