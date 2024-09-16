#include <stdio.h>

// Print the Hexadecimal Word
void printHexWord(HexWord word) {
    for (unsigned char i = 0; i < 4; i++) {
        printf("%X%X", word.bytes[i].nibbles.high, word.bytes[i].nibbles.low);
    }printf("\n");
}

// Defining XOR Organically
HexWord XOR(const HexWord A, const HexWord B) {
    HexWord temp;
    temp.bytes[0].byte = A.bytes[0].byte ^ B.bytes[0].byte;
    temp.bytes[1].byte = A.bytes[1].byte ^ B.bytes[1].byte;
    temp.bytes[2].byte = A.bytes[2].byte ^ B.bytes[2].byte;
    temp.bytes[3].byte = A.bytes[3].byte ^ B.bytes[3].byte;
    return temp;
}

// Right Rotate Once a HexWord
HexWord Rotate(const HexWord A) {
    HexWord temp;
    temp.bytes[3].byte = A.bytes[0].byte;
    temp.bytes[0].byte = A.bytes[1].byte;
    temp.bytes[1].byte = A.bytes[2].byte;
    temp.bytes[2].byte = A.bytes[3].byte;
    return temp;
}

// Swapping the First 4 Bits with the Last 4 Bits of a Byte because of
// To handle Little-Endienness
unsigned char swapNibbles(unsigned char byte) {
    return ((byte & 0x0F) << 4) | ((byte & 0xF0) >> 4);
}

// To Perform Substitution
HexWord SubWord(const HexWord A) {
    HexWord temp; // Check this about Little-Endienness
    temp.bytes[0].byte = swapNibbles(sBox[((int)A.bytes[0].nibbles.high) * 16 + ((int)A.bytes[0].nibbles.low)]);
    temp.bytes[1].byte = swapNibbles(sBox[((int)A.bytes[1].nibbles.high) * 16 + ((int)A.bytes[1].nibbles.low)]);
    temp.bytes[2].byte = swapNibbles(sBox[((int)A.bytes[2].nibbles.high) * 16 + ((int)A.bytes[2].nibbles.low)]);
    temp.bytes[3].byte = swapNibbles(sBox[((int)A.bytes[3].nibbles.high) * 16 + ((int)A.bytes[3].nibbles.low)]);
    return temp;
}

HexWord Rcon(unsigned char k) {
    unsigned char RCONST[11] = {0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36};
    HexWord temp;
    temp.bytes[0].byte = swapNibbles(RCONST[k]); // Little-Endienness
    temp.bytes[1].byte = 0x00;
    temp.bytes[2].byte = 0x00;
    temp.bytes[3].byte = 0x00;
    return temp;
}

// Left Shift a byte till k (k<8) Bits
HexByte leftShift(HexByte A, unsigned char i) {
    HexByte temp;
    for (unsigned char j = 1; j <= i; j++) {
        // Check : A.nibbles.Low's MSB is 1 => Shift that bit to LSB of
        // A.nibbles.High
        if (!((A.nibbles.low & 0x8) ^ 0x8)) { // '&' with 0x8 To Check if it's MSB is 1
            // '^' with 0x8 to Check LHS = RHS => 0! = 1 and Enters the If Block
            temp.nibbles.high = (A.nibbles.high << 1) ^ 0x1; } // '^' with 1 to add the removed Bit from low's MSB
        else { // low's MSB is NOT 1 so addition is not needed
            temp.nibbles.high = (A.nibbles.high << 1);}
        temp.nibbles.low = A.nibbles.low << 1;
        A.nibbles.low = temp.nibbles.low;
        A.nibbles.high = temp.nibbles.high; }
    return temp;
}

// Right Shift a byte till k (k<8) Bits
HexByte rightShift(HexByte A, unsigned char i) {
    HexByte temp;
    for (unsigned char j = 1; j <= i; j++) {
        // Check : A.nibbles.High's LSB is 1 => Shift that bit to MSB of
        // A.nibbles.Low
        if (!((A.nibbles.high & 0x1) ^ 0x1)) { // '&' with 0x1 To Check if it's MSB is 1
            // '^' with 0x1 to Check LHS = RHS => 0! = 1 and Enters the If Block
            temp.nibbles.low = (A.nibbles.low >> 1) ^ 0x8; } // '^' with 1 to add the removed Bit from low's MSB
        else { // High's LSB is NOT 1 so addition is not needed
            temp.nibbles.low = (A.nibbles.low >> 1); }
        temp.nibbles.high = A.nibbles.high >> 1;
        A.nibbles.low = temp.nibbles.low;
        A.nibbles.high = temp.nibbles.high; }
    return temp;
}

// Convert each parsed Character to Byte
unsigned char hexCharToByte(char hex) {
    if (hex >= '0' && hex <= '9') {
        return hex - '0'; }
    else if (hex >= 'A' && hex <= 'F') {
        return hex - 'A' + 10; }
    else if (hex >= 'a' && hex <= 'f') {
        return hex - 'a' + 10; }
    else { return 0; } // Invalid character
}

// To Parse the Key String and copy it into the Hex Word
void rowParseHexWords(const char *hexString, HexWord *wordArray, unsigned char len) {
    unsigned char wordCount = len / 8;
    for (unsigned char i = 0; i < wordCount; i++) {
        for (unsigned char j = 0; j < 4; j++) {
            unsigned char highNibble = hexString[i * 8 + j * 2];    // MSB
            unsigned char lowNibble = hexString[i * 8 + j * 2 + 1]; // LSB
            wordArray[i].bytes[j].byte = (hexCharToByte(lowNibble) << 4) | hexCharToByte(highNibble); // Little-Endian
        }
    }
}