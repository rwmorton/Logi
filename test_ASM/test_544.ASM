.PB loopproc

    # storage
    .PL loopproc_i
    NOP

    # set i to 0
    LAD $R4 loopproc_i
    LBI $R3 0
    SB $R3 $R4

    # check to se if i < 10
    .PL loopproc_L1
    LQI $R3 10
    LB $R2 $R4
    SLT $R1 $R2 $R3
    LQI $R4 0
    LAD $R5 loopproc_end
    JE $R1 $R4 $R5

    # print out i
    LAD $R4 loopproc_i
    LB $R2 $R4
    LAD $R10 loopproc_L2
    LAD $R1 printNumber
    JMP $R1

    # increment i
    .PL loopproc_L2
    LBI $R3 1
    LAD $R4 loopproc_i
    LB $R2 $R4
    ADD $R1 $R2 $R3
    SB $R1 $R4
    LAD $R1 loopproc_L1
    JMP $R1

    .PL loopproc_end
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
