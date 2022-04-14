.GQ gvar1
.GB gvar2 4

.PB globalproc

    # manually allocate
    # space for global
    # variables
    LQI $R3 12
    SUB $SP $SP $R3

    # load values into
    # variables
    LAI $R1 $TOP gvar1
    LQI $R2 -320
    SQ $R2 $R1

    LAI $R1 $TOP gvar2
    LQI $R2 25
    SD $R2 $R1

    LAI $R1 $TOP gvar1
    LQ $R2 $R1
    LAD $R10 globalproc_L1
    LAD $R4 printNumber
    JMP $R4

    .PL globalproc_L1

    LAI $R1 $TOP gvar2
    LD $R2 $R1
    LAD $R10 globalproc_end
    LAD $R4 printNumber
    JMP $R4

    .PL globalproc_end
    HALT
.PE

# print value in $R2
# return to pos in $R10
.PB printNumber
    LBI $R1 20
    INT 0
    LBI $R2 10
    LBI $R1 16
    INT 0
    LBI $R2 13
    LBI $R1 16
    INT 0
    JMP $R10
.PE
