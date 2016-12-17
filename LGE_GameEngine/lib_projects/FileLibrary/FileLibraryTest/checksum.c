//===================================================== file = checksum.c =====
//=  Program to compute 16-bit Internet checksum                              =
//=============================================================================
//=  Notes: 1) Based on the C-code given in RFC 1071 (Computing the Internet  =
//=            Checksum by R. Braden, D. Borman, and C. Partridge, 1988).     =
//=         2) Streamlined for 32-bit machines.  All overflows are added-in   =
//=            after the summing loop and not within the summing loop on a    =
//=            an overflow-by-overflow basis.                                 =
//=---------------------------------------------------------------------------=
//=  Build:  bcc32 checksum.c, gcc checksum.c                                 =
//=---------------------------------------------------------------------------=
//=  History:  KJC (8/25/00) - Genesis                                        =
//=============================================================================
//----- Include files ---------------------------------------------------------
#include <stdio.h>                  // Needed for printf()
#include <stdlib.h>                 // Needed for rand()

//----- Type defines ----------------------------------------------------------
typedef unsigned char      byte;    // Byte is a char
typedef unsigned short int word16;  // 16-bit word is a short int
typedef unsigned int       word32;  // 32-bit word is an int

//----- Defines ---------------------------------------------------------------
#define BUFFER_LEN        4096      // Length of buffer

//----- Prototypes ------------------------------------------------------------
word16 checksum(byte *addr, word32 count);

//===== Main program ==========================================================
void main(void)
{
  byte        buff[BUFFER_LEN]; // Buffer of packet bytes
  word16      check;            // 16-bit checksum value
  word32      i;                // Loop counter

  // Load buffer with BUFFER_LEN random bytes
  for (i=0; i<BUFFER_LEN; i++)
    buff[i] = (byte) rand();

  // Compute the 16-bit checksum
  check = checksum(buff, BUFFER_LEN);

  // Output the checksum
  printf("checksum = %04X \n", check);
}

//=============================================================================
//=  Compute Internet Checksum for count bytes beginning at location addr     =
//=============================================================================
word16 checksum(byte *addr, word32 count)
{
  register word32 sum = 0;

  // Main summing loop
  while(count > 1)
  {
    sum = sum + *((word16 *) addr)++;
    count = count - 2;
  }

  // Add left-over byte, if any
  if (count > 0)
    sum = sum + *((byte *) addr);

  // Fold 32-bit sum to 16 bits
  while (sum>>16)
    sum = (sum & 0xFFFF) + (sum >> 16);

  return(~sum);
}
