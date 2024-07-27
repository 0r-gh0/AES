#include <stdio.h>

// Byte Containing 2 Hexadecimal Characters
typedef union {                     // Union allocates one common storage space for all its members
    unsigned char byte;             // Store 2 hexadecimal characters (1 byte)
    struct {                        // Structure declaration
        unsigned char high : 4;     // High nibble (4 bits)
        unsigned char low : 4;      // Low nibble (4 bits)
    } nibbles;
} HexByte;

// Word Containing 4 Bytes or 8 Hexadecimal Characters
typedef struct {                    // "typedef" provides existing data types with a new name
    HexByte bytes[4];               // Array of 4 HexBytes to form a word (8 hex characters)
} HexWord;

unsigned char hexCharToByte(char hex) {
    if (hex >= '0' && hex <= '9') {
        return hex - '0';
    } else if (hex >= 'A' && hex <= 'F') {
        return hex - 'A' + 10;
    } else if (hex >= 'a' && hex <= 'f') {
        return hex - 'a' + 10;
    } else {
        return 0; // Invalid character
    }
}

void printHexWord(HexWord word) {
    for (int i = 0; i < 4; i++) {
        printf("%X%X", word.bytes[i].nibbles.high, word.bytes[i].nibbles.low);
    }
    printf("\n");
}

void parseHexWords(const char *hexString, HexWord *wordArray, unsigned char *wordCount, unsigned char len) {
    *wordCount = len / 8;

    for (int i = 0; i < *wordCount; i++) {
        for (int j = 0; j < 4; j++) {
            char lowNibble = hexString[i * 8 + j * 2];
            char highNibble = hexString[i * 8 + j * 2 + 1];
            wordArray[i].bytes[j].byte = (hexCharToByte(highNibble) << 4) | hexCharToByte(lowNibble);
        }
    }
}

int main(){

    unsigned char wordCount = 0;

    unsigned char Nk = 4;
    const char *key = "2b7e151628aed2a6abf7158809cf4f3c"; // Example input string
    unsigned char key_len = 32;
    
    HexWord key_Array[key_len/8];
    
    // Parse the hex string into words
    parseHexWords(key, key_Array, &wordCount, key_len);

    HexWord word;
    // Initialize the word with hexadecimal values (example: 0x1A2B3C4D)
    word.bytes[0].byte = 0x1A;
    word.bytes[1].byte = 0x2B;
    word.bytes[2].byte = 0x3C;
    word.bytes[3].byte = 0x4D;

    // Print the hexadecimal word
    printHexWord(word);

    // Print the parsed words
    for (int i = 0; i < wordCount; i++) {
        printHexWord(key_Array[i]);
    }

    return 0;
}