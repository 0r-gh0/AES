#ifndef MAIN_H
#define MAIN_H

// Include necessary standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>  // For uint8_t, uint32_t, etc.

// Byte Containing 2 Hexadecimal Characters
typedef union { // Union allocates one common storage space for all its members
    unsigned char byte;       // Store 2 hexadecimal characters (1 byte)
    struct {                  // Structure declaration
        unsigned char high : 4; // High nibble (4 bits)
        unsigned char low : 4;  // Low nibble (4 bits)
    } nibbles;
} HexByte;

// Word Containing 4 Bytes or 8 Hexadecimal Characters
typedef struct {    // "typedef" provides existing data types with a new name
    HexByte bytes[4]; // Array of 4 HexBytes to form a word (8 hex characters)
} HexWord;

// Function Declaration Needed before usage
int ftruncate(int oFile, off_t newSize);

#endif // MAIN_H
