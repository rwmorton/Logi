.GB filename 9
#.GB gvar1 5
#.GB gvar2 7
#.GB gvar3 3

#LQI $R1 9 # allocate 9 bytes for global storage
#SUB $SP $SP $R1

#LAI $R1 $TOP filename

###
#LBI $R24 1

#LAD $R1 150         # set start position
#LBI $R2 116
#SB $R2 $R1
#SUB $R1 $R1 $R24

#LBI $R2 101
#SB $R2 $R1
#SUB $R1 $R1 $R24

LBI $R1 116
PUSHB $R1

LBI $R1 101
PUSHB $R1

LBI $R1 115
PUSHB $R1

LBI $R1 116
PUSHB $R1

LBI $R1 46
PUSHB $R1

LBI $R1 65
PUSHB $R1

LBI $R1 83
PUSHB $R1

LBI $R1 77
PUSHB $R1

LBI $R1 0
PUSHB $R1

###
# 116,101,115,116,46,65,83,77,0

EI

# open file
#LBI $R1 0
#INT 0

# flush the file buffer
#LBI $R1 2
#INT 0

# close file
#LBI $R1 1
#INT 0

NOP
HALT
