#!/bin/bash
set -e
clear

# for unxpanded VIC-20:
cl65 -t vic20 --config vic20.cfg -Cl -O -o tt.prg tt.c

# for 35K expanded VIC-20 (uncomment line below, and comment line above):
# cl65 -t vic20 --config tt-35k.cfg -Cl -O -o tt.prg tt.c

c1541 /home/rick/Sync/Computers/Commodore/Disks/VIC-20.dhd < inst.txt
