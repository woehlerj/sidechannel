# change to ubuntu 22.04 to make it compatible with compiled binary
FROM ubuntu:22.04

RUN adduser --disabled-password --gecos '' ctf

# install libc
RUN apt update && apt install -y libc6 libstdc++6

# install packages
RUN apt install -y xinetd

# copy flag files
COPY flag /flag
COPY target /target
COPY welcome-message.txt /welcome-message.txt

# make the flag readonly
RUN chmod a-w flag

# run target
CMD ["/target"]
