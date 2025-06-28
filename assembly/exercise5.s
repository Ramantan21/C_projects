# print 2 integers then print the sum and the difference

.text
.globl main

main:

li $v0,5 # read int
syscall
move $t0,$v0 # save int

move $a0,$v0 # print int
li $v0,1
syscall
jal print_endl

# now read the other int and save it
li $v0,5
# save it
move $t1,$v0

# and print it
move $a0,$v0
li $v0,1
syscall
jal print_endl

add $s0,$t0,$t1
sub $s1,$t0,$t1

# now we want to print add and sub

move $a0,$s0
li $v0,1
syscall
jal print_endl

move $a0,$s1
li $v0,1
syscall
jal print_endl

li $v0,10
syscall



print_endl:
    li $a0,10
    li $v0,11
    syscall
    jr $ra




