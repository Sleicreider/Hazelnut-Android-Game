#!/bin/bash

mkdir compressed
for a in *.png; do etc1tool "$a" --encode -o compressed/${a%.*}.pkm; done
