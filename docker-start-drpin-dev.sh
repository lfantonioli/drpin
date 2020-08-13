#!/bin/bash

mkdir -p /tmp/tmpdrpin

docker image build -t drpin_image:latest ./drpin/

docker run -u $(id -u):$(id -g) --rm -it --name drpin_container  --mount type=bind,source="$(pwd)",target=/app -v /tmp/tmpdrpin:/tmp drpin_image:latest
