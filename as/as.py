#!/usr/bin/python

import sys

inputlines = []
outputlines = []

labels = {}

data_seg = 0

def analyze_inst(parts,offset):
    if not isinstance(parts,list):
        return str(parts)
    if parts[0] == "addi":
        return str((0x02<<26)|(int(parts[1][1])<<21)|(int(parts[2][1])<<16)|(int(parts[3])&0xffff))
    if parts[0] == "add":
        return str((0x01<<26)|(int(parts[1][1])<<21)|(int(parts[2][1])<<16)|(int(parts[3][1])<<11))
    if parts[0] == "slt":
        return str((0x11<<26)|(int(parts[1][1])<<21)|(int(parts[2][1])<<16)|(int(parts[3][1])<<11))
    if parts[0] == "lw":
        return str((0x03<<26)|(int(parts[1][1])<<21)|(int(parts[3][1])<<16)|(int(parts[2])&0xffff))
    if parts[0] == "sw":
        return str((0x04<<26)|(int(parts[1][1])<<21)|(int(parts[3][1])<<16)|(int(parts[2])&0xffff))
    if parts[0] == "beq":
        return str((0x12<<26)|(int(parts[1][1])<<21)|(int(parts[2][1])<<16)|(int(labels[parts[3]]-offset)&0xffff))
    if parts[0] == "bne":
        return str((0x13<<26)|(int(parts[1][1])<<21)|(int(parts[2][1])<<16)|(int(labels[parts[3]]-offset)&0xffff))
    if parts[0] == "swi":
        return str((0x3f<<26)|(int(parts[1])))
    return "!!FAIL"

def main():
    infile = open(sys.argv[1],"r")
    inputlines = infile.readlines()
    outputlines.append(0)
    outputlines.append(0)
    for line in inputlines:
        line = line.strip()
        if len(line) == 0:
            continue
        if line[0] == '#':
            continue
        if len(line)>=8 and line[0:8] == "DATA SEG":
            data_seg = 1
            continue
        if len(line)>=8 and line[0:8] == "DATA END":
            data_seg = 0
            continue
        if len(line)>=8 and line[0:8] == "CODE SEG":
            continue
        if len(line)>=8 and line[0:8] == "CODE END":
            continue
        if data_seg == 1:
            outputlines.append(int(line))
            labels["EP"] = len(outputlines)-2
            continue
        if len(line)>0 and line[-1] == ':':
            labels[line[0:-1]] = len(outputlines)-2
            continue
        outputlines.append(line.split())
    print "CONTENTS:"
    i = 0
    outputlines[0] = len(outputlines)-2
    outputlines[1] = (labels["EP"]<<2) +0x200
    outfile=open(sys.argv[2],"w")
    for line in outputlines:
        i+=1
        print str(i)+": "+str(line)
        outfile.write("%08x\n"%int(analyze_inst(line,i-2)))
    outfile.close()
    print "OVER"
    print labels

main()
