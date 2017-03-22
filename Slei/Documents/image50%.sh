
#!/bin/bash

mkdir resized
for a in *.png; do convert "$a" -resize 50% resized/"$a"; done
