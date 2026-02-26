#!/bin/bash
set -e
clear

cl65 -t vic20 --config vic20.cfg -Cl -O -o tt.prg tt.c
c1541 /home/rick/Sync/Computers/Commodore/Disks/VIC-20.dhd < inst.txt
