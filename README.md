# TanyTerm
A minimalist terminal program for the Commodore VIC-20
![TanyTerm](https://github.com/user-attachments/assets/3011f4b6-2f55-4bc4-9f1e-c46dbc723bcb)

Based on victerm300 by Francesco Sblendorio (https://github.com/sblendorio/victerm300), this is a stripped down absolutely minimalist version of a terminal program for a VIC-20.

Compile it using the cc65 compiler and transfer the resulting .PRG file to a media that your VIC-20 can access.

By default, TanyTerm runs at 1200 baud using the VIC-20's Kernal routines to communicating with whatever modem device you have connected to the User Port. The device will have to be a "smart" device such as a modern WiFi Modem or a Smart Modem (ie: one that recognizes Hayes-style "AT" commands). 

To dial out, simply type something like:

    atdt bbs.deepskies.com:6400

and the terminal will connect. To hang up, type three plus signs (+++) quickly and then enter:

    ath0

to hang up. Finally, you can press F7 to exit the terminal program and go back to BASIC.

For compiling, something like this would work for an unexpanded VIC:

    cl65 -t vic20 --config vic20.cfg -Cl -O -o tt.prg tt.c

If you want to run at 300 baud instead of 1200, update line 67 from:

    p[0] = 8;

to:

    p[0] = 6;

and re-compile.
