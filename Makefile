NAME := $(shell cat NAME)
PORT := $(shell cat PORT)

help:
	@echo "dist   : build the target and distribute to docker/release"
	@echo "build  : build the docker image"
	@echo "run    : run the docker container"
	@echo "exploit: launch the exploit"
	@echo "test   : test the docker/exploit"
	@echo "submit : zip for submission"

dist:
	(cd source/src; make)
	cp -f source/src/target docker/

build:
	(cd docker; docker build -t $(NAME) .)

run:
	docker run -p $(PORT):28014 --rm -i -t $(NAME)

submit:
	zip -r ../$(NAME).zip .
	@echo "Please submit ../$(NAME).zip"

exploit:
	PORT=$(PORT) REMOTE=1 source/exploit.py

test:
	@source/test.sh

.PHONY: dist build run submit exploit test help
