# Makefile for TanyTerm

SRC = tt.c
TANY = tt.prg

all: tany

tany:
	cl65 -t vic20 --config vic20.cfg -Cl -O -o $(TANY) $(SRC)
	c1541 /home/rick/Sync/Computers/Commodore/Disks/VIC-20.d64 < inst.txt
	c1541 tt.d64 < inst.txt

clean:
	rm -f *.o *.prg