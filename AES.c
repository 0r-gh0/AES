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

// Convert each parsed Character to HEX
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

// Print the Hexadecimal Word
void printHexWord(HexWord word) {
    for (unsigned char i = 0; i < 4; i++) {
        printf("%X%X", word.bytes[i].nibbles.high, word.bytes[i].nibbles.low);
    }
    printf("\n");
}

void parseHexWords(const char *hexString, HexWord *wordArray, unsigned char len) {
    unsigned char wordCount = len / 8;

    for (unsigned char i = 0; i < wordCount; i++) {
        for (unsigned char j = 0; j < 4; j++) {
            unsigned char lowNibble = hexString[i * 8 + j * 2];
            unsigned char highNibble = hexString[i * 8 + j * 2 + 1];
            wordArray[i].bytes[j].byte = (hexCharToByte(highNibble) << 4) | hexCharToByte(lowNibble);
        }
    }
}

int main(){

    // const char *key = "2b7e151628aed2a6abf7158809cf4f3c"; // Example input string
    // unsigned char keyLen = 32;

    // const char *key = "8e73b0f7da0e6452c810f32b809079e562f8ead2522c6b7b"; // Example input string
    // unsigned char keyLen = 48;

    const char *key = "603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4"; // Example input string
    unsigned char keyLen = 64;

    unsigned char keyCount = keyLen/8;
    HexWord keyArray[keyCount];
    
    // Parse the hex string into words
    parseHexWords(key, keyArray, keyLen);

    // Print the parsed words
    for (unsigned char i = 0; i < keyCount; i++) {
        printHexWord(keyArray[i]);
    }

    return 0;
}