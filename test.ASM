#
# globals
#
.GB gvar1
.GW gvar2
.GD gvar3 10    # array with 10 elements
.GD gvar4 15    # array with 15 elements

.GQ gvar5
.GQ gvar6 10

#
# myproc1 begin
#
.PB myproc1
    .PR retval 6
    .PA arg1 4
    .PA arg2 3
    .PA arg3 1
    .PV var1 -6
    .PV var2 -11
    .PV var3 -18

LBI $R1, -23
LWI $R2, 280
LDI $R3, -70000
LQI $R4, 1234567890123 ### SOME COMMENT ####
LF1I $F1, -2.3e-4
LF2I $D1, 100e2
### LAD $R5, myproc2
#
# CHECK!!!
#
### LAI $R6, $TOP, gvar4        # balh balh balh
#
LWI $R7, 600
SB $R1, $R7
LB $R8, $R7
SW $R2, $R7
LW $R9, $R7
SD $R3, $R7
LD $R10, $R7
SQ $R4, $R7
LQ $R11, $R7        #   SOME OTHER DCOMMENT ####
SF1 $F1, $R7
LF1 $F2, $R7
SF2 $D1, $R7
LF2 $D2, $R7
PUSHB $R4
PUSHW $R4
PUSHD $R4
PUSHQ $R4
PUSHF1 $F1
PUSHF2 $D1
.PL proc1label1
POPB $R4
POPW $R4
POPD $R4
POPQ $R4
POPF1 $F3
POPF2 $D3
.PE
HALT
