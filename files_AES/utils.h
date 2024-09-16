#ifndef UTILS_H
#define UTILS_H

#include "main.h"  // Include for HexWord and HexByte types, and standard libraries

// External declaration for the global sBox array
extern unsigned char sBox[256];
extern unsigned char InvSBox[256];

// Function declarations
// Function to print a HexWord in hexadecimal format
void printHexWord(HexWord word);

// Function to XOR two HexWord values and return the result
HexWord XOR(HexWord A, HexWord B);

// Function to rotate the bytes of a HexWord
HexWord Rotate( HexWord A);

// Function to swap the nibbles (4-bit parts) of a byte
unsigned char swapNibbles(unsigned char byte);

// Function to substitute the bytes of a HexWord using the sBox (SubWord operation)
HexWord SubWord( HexWord A);

// Function to compute the round constant (Rcon) for AES key expansion
HexWord Rcon(unsigned char k);

// Function to left shift a HexByte by a certain number of bits
HexByte leftShift(HexByte A, unsigned char i);

// Function to right shift a HexByte by a certain number of bits
HexByte rightShift(HexByte A, unsigned char i);

// Function to Convert a hex Character to byte
unsigned char hexCharToByte(char hex);

// Function to parse HexWords from a given String
void rowParseHexWords( char *hexString, HexWord *wordArray, unsigned char len);

#endif // UTILS_H