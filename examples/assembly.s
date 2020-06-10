.data
label4:
.word 1
label5:
.word 2

.text
label1:
add R1, R2, R3
label2:
addi R4, R2, 10
beq R6, R7, label3
add R1, R4, R2
subf R3, R4, R5
label3:
addi R6, R6, 9
and R7, R6, R4
or R8, R6, R4
xor R7, R6, R8
ld R2, 0(R10)
addi R2, R2, 1
std R2, 0(R10)
ld R9, 0(R10)