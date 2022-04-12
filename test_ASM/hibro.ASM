.GB hello 8

### "hi bro!" is made up of the following bytes (including line end)
# 104 105 32 98 114 111 33 0 # big-endian

LBI $R1 104
PUSHB $R1

LBI $R1 105
PUSHB $R1

LBI $R1 32
PUSHB $R1

LBI $R1 98
PUSHB $R1

LBI $R1 114
PUSHB $R1

LBI $R1 111
PUSHB $R1

LBI $R1 33
PUSHB $R1

LBI $R1 0
PUSHB $R1

#

NOP
NOP

EI

# print string
LBI $R1 14
INT 0

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
