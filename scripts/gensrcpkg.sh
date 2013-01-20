#!/bin/bash

tar cfvvj NasuTek-Commander-5.0-src.tar.bz2 --exclude-from=.tarignore --exclude-vcs --transform 's,\./,NasuTek-Commander-5.0-src/,S' --show-transformed .
