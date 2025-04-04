#!/usr/bin/bash

#Compile the C program
gcc -o leet3 leet3.c

#check if compilation was successfull
if [ $? -eq 0 ] ; then
    echo "Compilation successful. Running tasks in the background..."

    #run the program in the background
    ./leet3 &

    #continue with other tasks in the script
    echo "Bash script is doing other things while the c program runs in the background..."
    sleep 5 #Simulate other work in the script

    #wait for the background process to finish
    wait

    echo "Bash script is done!"
else
    echo " Compilation failed. Please check the c Code."

fi


