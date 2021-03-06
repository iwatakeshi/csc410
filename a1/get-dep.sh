#! /bin/bash

function get_dep {
  if [ -d "master.zip" ]; then
    unzip master.zip && mv matrix.h-master/ matrix/
  else
    curl -LOk https://github.com/iwatakeshi/matrix.h/archive/master.zip && unzip master.zip && mv matrix.h-master/ matrix/
  fi
}

if [ -d "./matrix/" ]; then
	cp matrix/matrix.* . && rm -r -f matrix/ master.zip
else 
  get_dep && cp matrix/matrix.* . && rm -r -f matrix/ master.zip
fi
