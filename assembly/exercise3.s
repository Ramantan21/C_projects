.data
buffer: .space 21 # pilot said to read up to 20 chars
newl: .asciiz "\n"


.text
.globl main

main:

li $v0,8 # read string
la $a0,21 # specify lenght to read
la $a0,buffer # store read string in buffer
syscall

la $a0,buffer
li $v0,4
syscall

la $a0,newl
li $v0,4
syscall

sb $zero,buffer + 5 # add null byte after 5th chars

la $a0,buffer
li $v0,4
syscall

la $a0,newl
li $v0,4
syscall

li $v0,10
syscall
