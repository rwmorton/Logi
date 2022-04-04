# globals ####
.GB gvar1
.GW gvar2
.GD gvar3 10
.GD gvar4 15

### myproc1 begin ###
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
LDI $R3,        -70000
LQI $R4, 1234567890123
LF1I $F1,,       , -2.3e-4
LF2I $D1, 100e2
LAD $R5, myproc2
LAI $R6 ,       , , $TOP, gvar4
