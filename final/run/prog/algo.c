#include "../include/algo.h"
#include "../include/utils.h"
#include "../../main.h"

void keyExpansion(HexWord *rowKeyArray, HexWord *keyScheduling, unsigned char sizeNK) { 
    HexWord temp;
    for (unsigned char i = 0; i < sizeNK; i++) { 
        keyScheduling[i] = rowKeyArray[i]; } 
    for (unsigned char i = 4; i < 44; i++) {
        temp = keyScheduling[i - 1];
        if (i % sizeNK == 0) { 
            temp = XOR(SubWord(Rotate(temp)), Rcon(i / sizeNK));
        } keyScheduling[i] = XOR(keyScheduling[i - sizeNK], temp);
    }
}

// Xoring 2 Words and then storing it in temp
void wordXOR(HexWord *A, HexWord *B, HexWord *temp) { 
    for (unsigned char i = 0; i < 4; i++) {
        for (unsigned char j = 0; j < 4; j++) {
            temp[i].bytes[j].byte = A[i].bytes[j].byte ^ B[i].bytes[j].byte;
        }
    }
}

// Performing SubWord and Storing it in temp
void subBytes(HexWord *A, HexWord *temp) { 
    for (unsigned char i = 0; i < 4; i++) { 
        for (unsigned char j = 0; j < 4; j++) { 
            temp[i].bytes[j].byte = swapNibbles(sBox[((int)A[i].bytes[j].nibbles.high) * 16 + ((int)A[i].bytes[j].nibbles.low)]);
        }
    }
}

// Performing Inverse of SubWord and Storing it in temp
void InvSubBytes(HexWord *A, HexWord *temp) {
    for (unsigned char i = 0; i < 4; i++) { 
        for (unsigned char j = 0; j < 4; j++) { 
            temp[i].bytes[j].byte = swapNibbles(InvSBox[((int)A[i].bytes[j].nibbles.high) * 16 + ((int)A[i].bytes[j].nibbles.low)]);
        }
    }
}

// Shifting Rowise and Storing it in temp
void shiftRows(HexWord *inWord, HexWord *temp) { 
    unsigned char tempHex1, tempHex2, tempHex3;

    temp[0].bytes[0].byte = inWord[0].bytes[0].byte;
    temp[1].bytes[0].byte = inWord[1].bytes[0].byte;
    temp[2].bytes[0].byte = inWord[2].bytes[0].byte;
    temp[3].bytes[0].byte = inWord[3].bytes[0].byte;
    
    tempHex1 = inWord[0].bytes[1].byte;
    temp[0].bytes[1].byte = (inWord[1].bytes[1].byte);
    temp[1].bytes[1].byte = (inWord[2].bytes[1].byte);
    temp[2].bytes[1].byte = (inWord[3].bytes[1].byte);
    temp[3].bytes[1].byte = (tempHex1);
    
    tempHex1 = inWord[0].bytes[2].byte;
    tempHex2 = inWord[1].bytes[2].byte;
    temp[0].bytes[2].byte = (inWord[2].bytes[2].byte);
    temp[1].bytes[2].byte = (inWord[3].bytes[2].byte);
    temp[2].bytes[2].byte = (tempHex1);
    temp[3].bytes[2].byte = (tempHex2);
    
    tempHex1 = inWord[0].bytes[3].byte;
    tempHex2 = inWord[1].bytes[3].byte;
    tempHex3 = inWord[2].bytes[3].byte;
    temp[0].bytes[3].byte = (inWord[3].bytes[3].byte);
    temp[1].bytes[3].byte = (tempHex1);
    temp[2].bytes[3].byte = (tempHex2);
    temp[3].bytes[3].byte = (tempHex3);
}

// Inverse Shifting Rowise and Storing it in temp
void InvShiftRows(HexWord *inWord, HexWord *temp) { 
    unsigned char tempHex1, tempHex2, tempHex3;
    
    temp[0].bytes[0].byte = inWord[0].bytes[0].byte;
    temp[1].bytes[0].byte = inWord[1].bytes[0].byte;
    temp[2].bytes[0].byte = inWord[2].bytes[0].byte;
    temp[3].bytes[0].byte = inWord[3].bytes[0].byte;
    
    tempHex1 = inWord[0].bytes[1].byte;
    tempHex2 = inWord[1].bytes[1].byte;
    tempHex3 = inWord[2].bytes[1].byte;
    temp[0].bytes[1].byte = (inWord[3].bytes[1].byte);
    temp[1].bytes[1].byte = (tempHex1);
    temp[2].bytes[1].byte = (tempHex2);
    temp[3].bytes[1].byte = (tempHex3);
    
    tempHex1 = inWord[0].bytes[2].byte;
    tempHex2 = inWord[1].bytes[2].byte;
    temp[0].bytes[2].byte = (inWord[2].bytes[2].byte);
    temp[1].bytes[2].byte = (inWord[3].bytes[2].byte);
    temp[2].bytes[2].byte = (tempHex1);
    temp[3].bytes[2].byte = (tempHex2);
    
    tempHex1 = inWord[0].bytes[3].byte;
    temp[0].bytes[3].byte = (inWord[1].bytes[3].byte);
    temp[1].bytes[3].byte = (inWord[2].bytes[3].byte);
    temp[2].bytes[3].byte = (inWord[3].bytes[3].byte);
    temp[3].bytes[3].byte = (tempHex1);
}

// To Perform the Galois Multiplication of 2^8
HexByte galoisMul(HexByte A, HexByte B) {
    HexByte p, temp_A = A, temp_B = B;
    p.nibbles.high = 0x0;
    p.nibbles.low = 0x0; // Accumulator for the product of the multiplication
    while ((temp_A.nibbles.low != 0x0 || temp_A.nibbles.high != 0x0) && (temp_B.nibbles.low != 0x0 || temp_B.nibbles.high != 0x0)) { // To Check Whether a != 0 && b != 0
        if (temp_B.nibbles.low & 0x1) { // if the polynomial for b has a constant
            // term, add the corresponding a to p
            p.nibbles.low ^= temp_A.nibbles.low; // addition in GF(2^m) is an XOR of
            // the polynomial coefficients
            p.nibbles.high ^= temp_A.nibbles.high;
        }
        if (temp_A.nibbles.high & 0x8) { // GF modulo: if a has a nonzero term x^7,
            // then must be reduced when it becomes x^8
            temp_A = leftShift(temp_A, 1);
            temp_A.nibbles.high = temp_A.nibbles.high ^ 0x1;
            temp_A.nibbles.low = temp_A.nibbles.low ^ 0xb;
        } // Subtract (XOR) the primitive polynomial x^8 + x^4 + x^3 + x + 1
          // (0b1_0001_1011) – you can change it but it must be irreducible
        else {
            temp_A = leftShift(temp_A, 1); // Equivalent to a*x
        }   temp_B = rightShift(temp_B, 1);
    } return p;
}

// To Perform MixColumns
void MixColumns(HexWord *A, HexWord *temp) { 
    HexByte temp_02, temp_03, temp_02_galoisMul, temp_03_galoisMul;
    temp_02.nibbles.high = 0x0; // Argument of type "int" is incompatible with
    // parameter of type "const HexByte"C
    temp_02.nibbles.low = 0x2;

    temp_03.nibbles.high = 0x0;
    temp_03.nibbles.low = 0x3;

    for (int i = 0; i < 4; i++) {
        temp_02_galoisMul = galoisMul(temp_02, A[i].bytes[0]);
        temp_03_galoisMul = galoisMul(temp_03, A[i].bytes[1]);
        
        temp[i].bytes[0].nibbles.low = (temp_02_galoisMul).nibbles.low ^ (temp_03_galoisMul).nibbles.low ^ A[i].bytes[2].nibbles.low ^ A[i].bytes[3].nibbles.low;
        temp[i].bytes[0].nibbles.high = (temp_02_galoisMul).nibbles.high ^ (temp_03_galoisMul).nibbles.high ^ A[i].bytes[2].nibbles.high ^ A[i].bytes[3].nibbles.high;
    
        temp_02_galoisMul = galoisMul(temp_02, A[i].bytes[1]);
        temp_03_galoisMul = galoisMul(temp_03, A[i].bytes[2]);
    
        temp[i].bytes[1].nibbles.low = A[i].bytes[0].nibbles.low ^ (temp_02_galoisMul).nibbles.low ^ (temp_03_galoisMul).nibbles.low ^ A[i].bytes[3].nibbles.low;
        temp[i].bytes[1].nibbles.high = A[i].bytes[0].nibbles.high ^ (temp_02_galoisMul).nibbles.high ^ (temp_03_galoisMul).nibbles.high ^ A[i].bytes[3].nibbles.high;
    
        temp_02_galoisMul = galoisMul(temp_02, A[i].bytes[2]);
        temp_03_galoisMul = galoisMul(temp_03, A[i].bytes[3]);
        
        temp[i].bytes[2].nibbles.low = A[i].bytes[0].nibbles.low ^ A[i].bytes[1].nibbles.low ^ (temp_02_galoisMul).nibbles.low ^ (temp_03_galoisMul).nibbles.low;
        temp[i].bytes[2].nibbles.high = A[i].bytes[0].nibbles.high ^ A[i].bytes[1].nibbles.high ^ (temp_02_galoisMul).nibbles.high ^ (temp_03_galoisMul).nibbles.high;
        
        temp_02_galoisMul = galoisMul(temp_02, A[i].bytes[3]);
        temp_03_galoisMul = galoisMul(temp_03, A[i].bytes[0]);
        
        temp[i].bytes[3].nibbles.low = (temp_03_galoisMul).nibbles.low ^ A[i].bytes[1].nibbles.low ^ A[i].bytes[2].nibbles.low ^ (temp_02_galoisMul).nibbles.low;
        temp[i].bytes[3].nibbles.high = (temp_03_galoisMul).nibbles.high ^ A[i].bytes[1].nibbles.high ^ A[i].bytes[2].nibbles.high ^ (temp_02_galoisMul).nibbles.high;
    }
}

// To Perform Inverse MixColumns
void InvMixColumns(HexWord *A, HexWord *temp) {
    HexByte temp_09, temp_0b, temp_0d, temp_0e, temp_09_galoisMul, temp_0b_galoisMul, temp_0d_galoisMul, temp_0e_galoisMul;
    
    temp_09.nibbles.high = 0x0; // Argument of type "int" is incompatible with
    // parameter of type "const HexByte"C
    temp_0b.nibbles.high = 0x0;
    temp_0d.nibbles.high = 0x0;
    temp_0e.nibbles.high = 0x0;
    
    temp_09.nibbles.low = 0x9;
    temp_0b.nibbles.low = 0xb;
    temp_0d.nibbles.low = 0xd;
    temp_0e.nibbles.low = 0xe;
    
    for (int i = 0; i < 4; i++) {
        temp_09_galoisMul = galoisMul(temp_09, A[i].bytes[3]);
        temp_0b_galoisMul = galoisMul(temp_0b, A[i].bytes[1]);
        temp_0d_galoisMul = galoisMul(temp_0d, A[i].bytes[2]);
        temp_0e_galoisMul = galoisMul(temp_0e, A[i].bytes[0]);
        
        temp[i].bytes[0].nibbles.low = temp_09_galoisMul.nibbles.low ^ temp_0b_galoisMul.nibbles.low ^ temp_0d_galoisMul.nibbles.low ^ temp_0e_galoisMul.nibbles.low;
        temp[i].bytes[0].nibbles.high = temp_09_galoisMul.nibbles.high ^ temp_0b_galoisMul.nibbles.high ^ temp_0d_galoisMul.nibbles.high ^ temp_0e_galoisMul.nibbles.high;
        
        temp_09_galoisMul = galoisMul(temp_09, A[i].bytes[0]);
        temp_0b_galoisMul = galoisMul(temp_0b, A[i].bytes[2]);
        temp_0d_galoisMul = galoisMul(temp_0d, A[i].bytes[3]);
        temp_0e_galoisMul = galoisMul(temp_0e, A[i].bytes[1]);
        
        temp[i].bytes[1].nibbles.low = temp_09_galoisMul.nibbles.low ^ temp_0b_galoisMul.nibbles.low ^ temp_0d_galoisMul.nibbles.low ^ temp_0e_galoisMul.nibbles.low;
        temp[i].bytes[1].nibbles.high = temp_09_galoisMul.nibbles.high ^ temp_0b_galoisMul.nibbles.high ^ temp_0d_galoisMul.nibbles.high ^ temp_0e_galoisMul.nibbles.high;
        
        temp_09_galoisMul = galoisMul(temp_09, A[i].bytes[1]);
        temp_0b_galoisMul = galoisMul(temp_0b, A[i].bytes[3]);
        temp_0d_galoisMul = galoisMul(temp_0d, A[i].bytes[0]);
        temp_0e_galoisMul = galoisMul(temp_0e, A[i].bytes[2]);
        
        temp[i].bytes[2].nibbles.low = temp_09_galoisMul.nibbles.low ^ temp_0b_galoisMul.nibbles.low ^ temp_0d_galoisMul.nibbles.low ^ temp_0e_galoisMul.nibbles.low;
        temp[i].bytes[2].nibbles.high = temp_09_galoisMul.nibbles.high ^ temp_0b_galoisMul.nibbles.high ^ temp_0d_galoisMul.nibbles.high ^ temp_0e_galoisMul.nibbles.high;
        
        temp_09_galoisMul = galoisMul(temp_09, A[i].bytes[2]);
        temp_0b_galoisMul = galoisMul(temp_0b, A[i].bytes[0]);
        temp_0d_galoisMul = galoisMul(temp_0d, A[i].bytes[1]);
        temp_0e_galoisMul = galoisMul(temp_0e, A[i].bytes[3]);
        
        temp[i].bytes[3].nibbles.low = temp_09_galoisMul.nibbles.low ^ temp_0b_galoisMul.nibbles.low ^ temp_0d_galoisMul.nibbles.low ^ temp_0e_galoisMul.nibbles.low;
        temp[i].bytes[3].nibbles.high = temp_09_galoisMul.nibbles.high ^ temp_0b_galoisMul.nibbles.high ^ temp_0d_galoisMul.nibbles.high ^ temp_0e_galoisMul.nibbles.high;
    }
}