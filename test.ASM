.GB gb1
.GW gw1
.GD gd1
.GQ gq1

.PB myproc
.PR retval 5
.PA arg1 3
.PA arg2 2
.PV loc1 1
.PV loc2 -5
.PE

.PB stackproc

# manually place word on stackproc
LWI $R2 6570
LBI $R3 2
SUB $SP $SP $R3
SW $R2 $SP

# pop word into $R2 then print
POPW $R2
LAD $R10 stackproc_L1
LAD $R1 printNumber
JMP $R1

.PL stackproc_L1

# push a quad word on to stack
LQI $R2 -1234567890
PUSHQ $R2

# manually retrieve quad word and print
LQ $R2 $SP
LQI $R3 8
SUB $SP $SP $R3
LAD $R10 stackproc_end
LAD $R4 printNumber
JMP $R4

.PL stackproc_end
HALT

.PE

# print value in $R2
# return to position in $R10
.PB printNumber

LBI $R1 20
INT 0

LQI $R2 10
LQI $R1 16
INT 0

LQI $R2 13
LQI $R1 16
INT 0

JMP $R10

.PE
