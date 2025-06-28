# read 2 integers and print them out to console.

.text
.globl main

main:

li $v0,5 # read integer
syscall
move $a0,$v0 

li $v0,1 # print integer
syscall

li $v0,10 # exit
syscall

