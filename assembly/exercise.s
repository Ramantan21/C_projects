# Load from address

.text
.globl __start

__start:

    lbu $t0, b1 # load the byte from label "b1" as unsigned, in $t0
    lhu $t1, b1 # load the half word (2 bytes) from label "b1" as unsigned, in $t1









.data

b1: .byte 0x01, 0x02, 0x03, 0x04, 0x81, 0x82, 0x83, 0x84
w1: .word 0x12345678, 0x87654321
