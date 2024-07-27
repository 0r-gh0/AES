#include <stdio.h>

typedef union {                     // Union allocates one common storage space for all its members
    unsigned char byte;             // Store 2 hexadecimal characters (1 byte)
    struct {                        // Structure declaration
        unsigned char high : 4;     // High nibble (4 bits)
        unsigned char low : 4;      // Low nibble (4 bits)
    } nibbles;
} HexByte;

typedef struct {                    // "typedef" provides existing data types with a new name
    HexByte bytes[4];               // Array of 4 HexBytes to form a word (8 hex characters)
} HexWord;

void printHexWord(HexWord word) {
    for (int i = 0; i < 4; i++) {
        printf("%X%X", word.bytes[i].nibbles.high, word.bytes[i].nibbles.low);
    }
    printf("\n");
}

int main(){
    
    HexWord word;
    
    // Initialize the word with hexadecimal values (example: 0x1A2B3C4D)
    word.bytes[0].byte = 0x1A;
    word.bytes[1].byte = 0x2B;
    word.bytes[2].byte = 0x3C;
    word.bytes[3].byte = 0x4D;

    // Print the hexadecimal word
    printHexWord(word);

    return 0;
}