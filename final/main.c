#include "run/include/enc_dec.h"
#include "run/include/algo.h"
#include "run/include/utils.h"
#include "main.h"      // For HexWord, HexByte, and any custom types

#include "modes/include/enc/cfb_enc.h"    // For OfbEnc function
#include "modes/include/dec/cfb_dec.h"    // For OfbDec function (if decryption is also needed)
#include "modes/include/enc/ofb_enc.h"    // For OfbEnc function
#include "modes/include/dec/ofb_dec.h"    // For OfbDec function (if decryption is also needed)
#include "modes/include/enc/cbc_enc.h"    // For CbcEnc function
#include "modes/include/dec/cbc_dec.h"    // For CbcDec function (if decryption is also needed)
#include "modes/include/enc/ecb_enc.h"    // For EcbEnc function
#include "modes/include/dec/ecb_dec.h"    // For EcbDec function (if decryption is also needed)

int main() {
    HexWord IV[4], input_2[4];
    
    FILE *iFile, *oFile;
    
    //  char *key = "d4bf5d30e0b452aeb84111f11e2798e5";    // Example KEY
    //  char *key = "3243f6a8885a308d313198a2e0370734";    // Example KEY
    //  char *key = "2b7e151628aed2a6abf7158809cf4f3c";    // Example KEY
    
    // string "YELLOW SUBMARINE"
    char *key = "59454c4c4f57205355424d4152494e45"; // Example KEY
    
    unsigned char keyLen = 32;
    unsigned char inLen = 32;
    unsigned char keyCount = keyLen / 8; // Not Needed as of now
    unsigned char inCount = inLen / 8;   // Not Needed as of now
    
    HexWord rowKeyArray[keyCount];            // Array to store all Initial Keys
    HexWord keyScheduling[44];                // Array to store all Round Keys
    
    rowParseHexWords(key, rowKeyArray, keyLen);    // Parse the hex string and store it into Array
    keyExpansion(rowKeyArray, keyScheduling, 4);    // Run the Key Scheduling Algorithm and store it inside the
    // KeyScheduling DONE !
    // The Keys being stored in Array keyScheduling[]
    
    unsigned char temp_iv[16];                // 16-byte IV
    arc4random_buf(temp_iv, sizeof(temp_iv)); // Generate random IV

    // Now Store that IV in HexWord Format
    IV[0].bytes[0].nibbles.low = temp_iv[0];
    IV[0].bytes[0].nibbles.high = temp_iv[0] >> 4;
    IV[0].bytes[1].nibbles.low = temp_iv[1];
    IV[0].bytes[1].nibbles.high = temp_iv[1] >> 4;
    IV[0].bytes[2].nibbles.low = temp_iv[2];
    IV[0].bytes[2].nibbles.high = temp_iv[2] >> 4;
    IV[0].bytes[3].nibbles.low = temp_iv[3];
    IV[0].bytes[3].nibbles.high = temp_iv[3] >> 4;
    
    IV[1].bytes[0].nibbles.low = temp_iv[4];
    IV[1].bytes[0].nibbles.high = temp_iv[4] >> 4;
    IV[1].bytes[1].nibbles.low = temp_iv[5];
    IV[1].bytes[1].nibbles.high = temp_iv[5] >> 4;
    IV[1].bytes[2].nibbles.low = temp_iv[6];
    IV[1].bytes[2].nibbles.high = temp_iv[6] >> 4;
    IV[1].bytes[3].nibbles.low = temp_iv[7];
    IV[1].bytes[3].nibbles.high = temp_iv[7] >> 4;
    
    IV[2].bytes[0].nibbles.low = temp_iv[8];
    IV[2].bytes[0].nibbles.high = temp_iv[8] >> 4;
    IV[2].bytes[1].nibbles.low = temp_iv[9];
    IV[2].bytes[1].nibbles.high = temp_iv[9] >> 4;
    IV[2].bytes[2].nibbles.low = temp_iv[10];
    IV[2].bytes[2].nibbles.high = temp_iv[10] >> 4;
    IV[2].bytes[3].nibbles.low = temp_iv[11];
    IV[2].bytes[3].nibbles.high = temp_iv[11] >> 4;
    
    IV[3].bytes[0].nibbles.low = temp_iv[12];
    IV[3].bytes[0].nibbles.high = temp_iv[12] >> 4;
    IV[3].bytes[1].nibbles.low = temp_iv[13];
    IV[3].bytes[1].nibbles.high = temp_iv[13] >> 4;
    IV[3].bytes[2].nibbles.low = temp_iv[14];
    IV[3].bytes[2].nibbles.high = temp_iv[14] >> 4;
    IV[3].bytes[3].nibbles.low = temp_iv[15];
    IV[3].bytes[3].nibbles.high = temp_iv[15] >> 4;
    
    input_2[0] = IV[0];
    input_2[1] = IV[1];
    input_2[2] = IV[2];
    input_2[3] = IV[3];

    iFile = fopen("hi.txt", "rb");
    oFile = fopen("encrypt.bin", "wb");

    if (iFile == NULL || oFile == NULL) {
        printf("File Couldn't be opened !!");
    return 1; } 
    
    EcbEnc(keyScheduling, iFile, oFile);
    // CbcEnc(input_2, keyScheduling, iFile, oFile);
    // OfbEnc(input_2, keyScheduling, iFile, oFile);
    // CfbEnc(input_2, keyScheduling, iFile, oFile);
    
    fclose(iFile);
    fclose(oFile);
    printf("ENCRYPTED !!!\n");

    input_2[0] = IV[0];
    input_2[1] = IV[1];
    input_2[2] = IV[2];
    input_2[3] = IV[3];
    
    iFile = fopen("encrypt.bin", "rb");
    oFile = fopen("decrypt.bin", "wb");

    if (iFile == NULL || oFile == NULL) {
        printf("File Couldn't be opened !!");
    return 1; } 

    EcbDec(keyScheduling, iFile, oFile);
    // CbcDec(input_2, keyScheduling, iFile, oFile);
    // OfbDec(input_2, keyScheduling, iFile, oFile);
    // CfbDec(input_2, keyScheduling, iFile, oFile);
    
    fclose(iFile);
    fclose(oFile);
    printf("DECRYPTED !!!\n");

    return 0;
}