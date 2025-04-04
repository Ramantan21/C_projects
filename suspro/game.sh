#!/bin/bash 

echo -n "Enter a Number:"; 
read BASE;

myNumber=$(( ((`date +%N` / 1000) % ${BASE}) +1 ))

# echo $myNumber

guess=-1

while [ "$guess" != "$myNumber" ]; 
        do
	echo -n "I am thinking of a number between 1 and "${BASE}". Enter your guess:"
	read guess
	if [ "$guess" = "" ]; then
		echo "Please enter a number."
	elif [ "$guess" = "$myNumber" ]; then
		echo -e "\a Yes! $guess is the correct answer!"
	elif [ "$myNumber" -gt "$guess" ]; then
		echo "Sought number is larger than your guess. Try once more."
	else
		echo "Sought number is smaller than your guess. Try once more."
	fi
	done

