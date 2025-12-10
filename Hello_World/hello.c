/*
 *--------------------------------------------------------------------------
 *  hello.c   - hello world for KC85/4 (/3 or /5) with SDCC
 *
 *  Copyright (c) 2024 boert, CC BY-SA 2.0 de
 *--------------------------------------------------------------------------
 */

#include <stdio.h>  // printf
#include "caos.h"   // crt


// Hauptprogramm
void main( void)
{
    crt( CLS);
    printf( "Hello User of KC85...\n");
}
