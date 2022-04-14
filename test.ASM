.GB cin_str 256

.PB globalproc

    # manually allocate
    # space for cin
    LQI $R1 256
    SUB $SP $SP $R1
    
    # read bytes from std::cin
    LQI $R2 256
    LAI $R3 $TOP cin_str
    LBI $R1 13
    INT 0

    # hello world!

    INT 3 # put debug back on to see mem dump
    NOP

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
