FROM ubuntu:22.04

RUN adduser --disabled-password --gecos '' ctf

# enable 32-bit support
RUN dpkg --add-architecture i386
RUN apt update && apt install -y libc6:i386 libstdc++6:i386

# install packages
RUN apt install -y xinetd

# copy service/flag files
COPY service.conf /service.conf
COPY flag /flag
COPY target /target

# make the flag readonly
RUN chmod a-w flag

# run xinetd
CMD ["/usr/sbin/xinetd", "-dontfork", "-f", "/service.conf"]
