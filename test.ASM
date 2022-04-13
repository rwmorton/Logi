.GQ gvar1
.GB gvar2 3
.GD gvar3

# the above variables require
# 15 bytes so allocate 15 bytes
LQI $R1 15
SUB $SP $SP $R1

LAI $R1 $TOP gvar1
LAI $R1 $TOP gvar2
LAI $R1 $TOP gvar3

NOP
NOP
HALT
