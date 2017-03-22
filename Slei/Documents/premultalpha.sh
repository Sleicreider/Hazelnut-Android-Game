
#!/bin/bash

mkdir premult
for a in *.png; do convert "$a" \( +clone -alpha Extract \) -channel RGB -compose Multiply -composite premult/"$a"; done
