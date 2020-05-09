FROM archlinux:latest

USER gitpod

RUN sudo pacman -Syu && sudo pacman -S sudo
RUN sudo useradd -m sdocker && \
	echo "sdocker:docker" | sudo chpasswd && \
	sudo adduser sdocker sudo

# Install custom tools, runtime, etc. using apt-get
# For example, the command below would install "bastet" - a command line tetris clone:
#
# RUN sudo apt-get -q update && \
#     sudo apt-get install -yq bastet && \
#     sudo rm -rf /var/lib/apt/lists/*
#
# More information: https://www.gitpod.io/docs/config-docker/
