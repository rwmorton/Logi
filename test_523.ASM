.PB proc1

# print the address of a procedure
LAD $R4 proc2
MOV $R2 $R4
LBI $R1 20
INT 0

.PL proc1_L001
LQI $R2 10
LQI $R1 16
INT 0

LQI $R2 13
LQI $R1 16
INT 0

# print the address of a label
LAD $R4 proc1_L001
MOV $R2 $R4
LBI $R1 20
INT 0
LQI $R2 10
LQI $R1 16
INT 0
LQI $R2 13
LQI $R1 16
INT 0
HALT

.PE

.PB proc2
LQI $R1 23
MOV $R3 $R1
.PE
