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
# LAD $R5, myproc2
# LAI $R6 ,       , , $TOP, gvar4
.PE

5 0 64 195 136 0 0 0 0 0
5 0 64 195 136 0 0 0 0 0

0 8 233
1 9 1 24
2 10 255 254 238 144
3 11 0 0 1 31 113 251 4 203
4 0 185 113 44 40

5 101 25 179 168 0 0 0 0 0 0 39 16
