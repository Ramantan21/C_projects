# encode a 32bit number using grey encoding
# insert value at s0, manually from qtspim window
#before running the program result is stored at s1


.text
.globl main

main:

srl $t0,$s0,1

xor $s1,$s0,$t0

li $v0,10
syscall