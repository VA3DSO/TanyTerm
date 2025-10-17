/*****************************************************************************/
/*                                                                           */
/*                                  tt.c                                     */
/*                                                                           */
/*                   Commodore VIC-20 Minimalist Terminal                    */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/* (C) 1982-2025, Rick Towns                                                 */
/*                Sudbury, Ontario                                           */
/*                CANADA                                                     */
/* EMail:         sysop@deepskies.com                                        */
/*                                                                           */
/* Acknowledgments:                                                          */
/*   Special thanks to Francesco Sblendorio (github.com/sblendorio) for his  */
/*   excellent victerm300 which inspired the writing of this program. Some   */
/*   of the functions here are based on some functions in victerm300.        */
/*                                                                           */
/*   Specifically: print, cursor_on, cursor_off and beep                     */
/*                                                                           */
/* This software is provided 'as-is', without any expressed or implied       */
/* warranty.  In no event will the authors be held liable for any damages    */
/* arising from the use of this software.                                    */
/*                                                                           */
/* Permission is granted to anyone to use this software for any purpose,     */
/* including commercial applications, and to alter it and redistribute it    */
/* freely, subject to the following restrictions:                            */
/*                                                                           */
/* 1. The origin of this software must not be misrepresented; you must not   */
/*    claim that you wrote the original software. If you use this software   */
/*    in a product, an acknowledgment in the product documentation would be  */
/*    appreciated but is not required.                                       */
/* 2. Altered source versions must be plainly marked as such, and must not   */
/*    be misrepresented as being the original software.                      */
/* 3. This notice may not be removed or altered from any source              */
/*    distribution.                                                          */
/*                                                                           */
/*****************************************************************************/
#include <cbm.h>
#include <peekpoke.h>

#pragma charmap(147, 147)
#pragma charmap(17, 17)

#define TRUE 1
#define FALSE 0
#define SUCCESS 0
#define ERROR 1
#define OFF 0
#define ON 1

/* local functions */
void print(char*);
void cursor_on(void);
void cursor_off(void);
void beep(void);

/* global variables */
static char CS;

char main(void) {

    char exiting = FALSE;
    char ch;
    char *p = "x";

    p[0] = 8;

    CS = OFF;

    POKE(36879UL,8);

    print("\223\005\010\016\022TANY\222TERM\n\n");

    cursor_on();
    cbm_open(5,2,3,p);
    POKE(169,192);

    do {

        /* XLOCAL */

        ch = cbm_k_getin();
        if (ch == 136) {
            cursor_off();
            exiting = TRUE;
            break;
        } else if (ch != 0) {
            cbm_k_ckout(5);
            cbm_k_bsout(ch);
            cbm_k_clrch();
        }

        /* XREMOTE */
        cbm_k_chkin(5);
        ch = cbm_k_getin();
        cbm_k_clrch();
        if (ch != 0) {
            cursor_off();
            cbm_k_bsout(ch);
            if (ch == 7) {
                beep();
            }
            cursor_on();
        }

    } while(exiting == FALSE);

    cbm_close(5);

    return(SUCCESS);

}

void print(char *str) {
    while (*str) {
        __A__ = *str++;
        asm("jsr $ffd2");
    }
}

void cursor_on(void) {

    if (CS == OFF) {
        POKE(212, 0);
        POKE(216, 0);

        if (PEEK(204) != 0) {
            asm("ldy #$00");
            asm("sty $cc");
            CS = ON;
        }

    }

}

void cursor_off(void) {
    if (CS == ON) {
        asm("ldy $cc");
        asm("bne %g", exitloop);
        asm("ldy #$01");
        asm("sty $cd");
        loop:
        asm("ldy $cf");
        asm("bne %g", loop);
        exitloop:
        asm("ldy #$ff");
        asm("sty $cc");
        CS = OFF;
    }
}

void beep(void) {

    static unsigned long j;

    /* VIC 20 BEEP */
    POKE(0x900E, 15);
    POKE(0x900D, 0);
    POKE(0x900C, 230);
    for (j=0; j<1000; ++j) asm("nop");
    POKE(0x900E, 0);

}
