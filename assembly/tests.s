.text
.globl main

main:

li $v0,5 # read an integer
syscall
move $t0,$v0

move $a0,$v0

#now print it
li $v0,1
syscall
jal print_newl

# now let's read the second integer

li $v0,5 # print fun
syscall
move $t1,$v0

move $a0,$v0
li $v0,1
syscall
jal print_newl

# lets add some spice

add $s0,$t0,$t1
sub $s1,$t0,$t1

# let's now print $s0, $s1

move $a0,$s0

li $v0,1
syscall
jal print_newl

move $a0,$s1
li $v0,1
syscall
jal print_newl

li $v0,10
syscall




# sick!


print_newl:
    li $a0,10
    li $v0,11
    syscall
    jal $ra