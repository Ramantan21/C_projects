# Load from address

.text
.globl main

main:

    lbu $t0, b1 + 10 # load the byte label "b1" as unsigned, in $t0
    lbu $t1, b1 + 11 # load the half word(2 bytes) from label "b1" as unsigned, in $t1
    lbu $t2, b1 + 12 # load the word (4 bytes) from label "b1". in $t2

    lbu $t3, b1 + 4 # load the byte from adress of label "b1 + 4" as unsigned, in $t3
    ulh $t4, b1 + 4 # load the half word( 2 bytes) from the adress of label "b1" + 4 as unsigned,in $t4
    lw $t5, b1 + 4 # load the word(4 bytes) from the adress of label "b1" + 4, in $t5

    lb $t0, b1 # load the byte from label "b1" as signed, in $t0
    lh $t1, b1 # load the half word(2 bytes) from "b1" as signed
    ulw $t2, b1 # load the word(4 bytes) from label "b1" as signed

    lb $t3, b1 + 4 # load the byte from adress of label "b1" + 4 as signed, in $t3
    lh $t4, b1 + 4 # load the half word(2 bytes) from label "b1" + 4 as signed, in $t4
    ulw $t5, b1 + 4 # load the word(4 bytes) from label "b1" , in $t5

    lb $t6, b1 + 4

    sb $t6, b1 + 16 # store the byte that is stored in $t6, in adress of label "b1" + 16


    lw $t0,w1 
    li $v0, 10 # exit
    syscall

.data
.aling 0

b1: .byte 0x01, 0x02, 0x03, 0x04, 0x05, 0x81, 0x82, 0x83, 0x84
h1: .half 0x6677
w1: .word 0x12345678, 0x87654321