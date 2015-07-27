
#!/bin/bash

mkdir premult
for a in *.png; do convert "$a" \( +clone -alpha Extract \) -channel RGB -compose Multiply -composite premult/"$a"; done

cd premult/

for a in *.png; do convert "$a" -channel A -separate ${a%.*}_alpha.png; done

mkdir ../compressed
for a in *.png; do etc1tool "$a" --encode -o ../compressed/${a%.*}.pkm; echo "$a"; done