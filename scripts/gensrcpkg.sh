#!/bin/bash

tar cfvvj nasutek-commander-5.0-src.tar.bz2 --exclude-from=.tarignore --exclude-vcs --transform 's,\./,nasutek-commander-5.0-src/,S' --show-transformed .
