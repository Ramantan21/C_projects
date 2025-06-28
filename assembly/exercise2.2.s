# little endian to big endian

.data
    w1: .word 0x12345678

.text
.globl main


main:
    # load word from memory
    lw $s0,w1

    # shift b1 to new position
    srl $s1,$s0,8
    andi $s1,$s1,0xff00 # mask to obtain b1
    andi $t0,$s0,0xff00 # mask to obtain b2

    sll $t0,$t0,8 # now shift b2 to new position
    or  #s1,$s1,$t0 # or b2 to new position

    srl $t0,$s0,24 # only byte 0 remains rest is 0
    sll $t1,$s0,24 # only byte 3 remains rest is 0

    or $s1,$s1,$t0
    or $s1,$s1,$t1

    li $v0,10
    syscall
