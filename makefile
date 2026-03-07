# Makefile for TanyTerm

SRC = tt.c
OUT_UNEXPANDED = tt.prg
OUT_35K = ttx.prg

all: unexpanded

unexpanded:
	cl65 -t vic20 --config vic20.cfg -Cl -O -o $(OUT_UNEXPANDED) $(SRC)
	c1541 /home/rick/Sync/Computers/Commodore/Disks/VIC-20.dhd < inst.txt

35k:
	cl65 -t vic20 --config tt-35k.cfg -Cl -O -o $(OUT_35K) $(SRC)
	c1541 /home/rick/Sync/Computers/Commodore/Disks/VIC-20.dhd < instx.txt

clean:
	rm -f *.o *.prg