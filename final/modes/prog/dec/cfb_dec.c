#include "cfb_dec.h"
#include "enc_dec.h"
#include "algo.h"
#include "utils.h"
#include "main.h"

void CfbDec(HexWord* input_2, HexWord* keyScheduling, FILE *iFile, FILE *oFile) { 
    unsigned char byteRead, buff[16], out_buff[16];
    HexWord in[4], output[4];
    int pad_counter = 0;

    while ((byteRead = fread(buff, 1, 16, iFile)) == 16) {
    
        in[0].bytes[0].nibbles.low = buff[0];
        in[0].bytes[0].nibbles.high = buff[0] >> 4;
        in[0].bytes[1].nibbles.low = buff[1];
        in[0].bytes[1].nibbles.high = buff[1] >> 4;
        in[0].bytes[2].nibbles.low = buff[2];
        in[0].bytes[2].nibbles.high = buff[2] >> 4;
        in[0].bytes[3].nibbles.low = buff[3];
        in[0].bytes[3].nibbles.high = buff[3] >> 4;
    
        in[1].bytes[0].nibbles.low = buff[4];
        in[1].bytes[0].nibbles.high = buff[4] >> 4;
        in[1].bytes[1].nibbles.low = buff[5];
        in[1].bytes[1].nibbles.high = buff[5] >> 4;
        in[1].bytes[2].nibbles.low = buff[6];
        in[1].bytes[2].nibbles.high = buff[6] >> 4;
        in[1].bytes[3].nibbles.low = buff[7];
        in[1].bytes[3].nibbles.high = buff[7] >> 4;
    
        in[2].bytes[0].nibbles.low = buff[8];
        in[2].bytes[0].nibbles.high = buff[8] >> 4;
        in[2].bytes[1].nibbles.low = buff[9];
        in[2].bytes[1].nibbles.high = buff[9] >> 4;
        in[2].bytes[2].nibbles.low = buff[10];
        in[2].bytes[2].nibbles.high = buff[10] >> 4;
        in[2].bytes[3].nibbles.low = buff[11];
        in[2].bytes[3].nibbles.high = buff[11] >> 4;
    
        in[3].bytes[0].nibbles.low = buff[12];
        in[3].bytes[0].nibbles.high = buff[12] >> 4;
        in[3].bytes[1].nibbles.low = buff[13];
        in[3].bytes[1].nibbles.high = buff[13] >> 4;
        in[3].bytes[2].nibbles.low = buff[14];
        in[3].bytes[2].nibbles.high = buff[14] >> 4;
        in[3].bytes[3].nibbles.low = buff[15];
        in[3].bytes[3].nibbles.high = buff[15] >> 4;
    
        Encrypt(input_2, keyScheduling, output);
    
        input_2[0] = in[0];
        input_2[1] = in[1];
        input_2[2] = in[2];
        input_2[3] = in[3];
    
        output[0].bytes[0].byte = output[0].bytes[0].byte ^ in[0].bytes[0].byte;
        output[0].bytes[1].byte = output[0].bytes[1].byte ^ in[0].bytes[1].byte;
        output[0].bytes[2].byte = output[0].bytes[2].byte ^ in[0].bytes[2].byte;
        output[0].bytes[3].byte = output[0].bytes[3].byte ^ in[0].bytes[3].byte;
    
        output[1].bytes[0].byte = output[1].bytes[0].byte ^ in[1].bytes[0].byte;
        output[1].bytes[1].byte = output[1].bytes[1].byte ^ in[1].bytes[1].byte;
        output[1].bytes[2].byte = output[1].bytes[2].byte ^ in[1].bytes[2].byte;
        output[1].bytes[3].byte = output[1].bytes[3].byte ^ in[1].bytes[3].byte;
    
        output[2].bytes[0].byte = output[2].bytes[0].byte ^ in[2].bytes[0].byte;
        output[2].bytes[1].byte = output[2].bytes[1].byte ^ in[2].bytes[1].byte;
        output[2].bytes[2].byte = output[2].bytes[2].byte ^ in[2].bytes[2].byte;
        output[2].bytes[3].byte = output[2].bytes[3].byte ^ in[2].bytes[3].byte;
    
        output[3].bytes[0].byte = output[3].bytes[0].byte ^ in[3].bytes[0].byte;
        output[3].bytes[1].byte = output[3].bytes[1].byte ^ in[3].bytes[1].byte;
        output[3].bytes[2].byte = output[3].bytes[2].byte ^ in[3].bytes[2].byte;
        output[3].bytes[3].byte = output[3].bytes[3].byte ^ in[3].bytes[3].byte;
    
        for (unsigned char i = 0; i < 4; i++) {
            printHexWord(output[i]);
        }
    
        out_buff[0] = output[0].bytes[0].nibbles.high << 4 | output[0].bytes[0].nibbles.low;
        out_buff[1] = output[0].bytes[1].nibbles.high << 4 | output[0].bytes[1].nibbles.low;
        out_buff[2] = output[0].bytes[2].nibbles.high << 4 | output[0].bytes[2].nibbles.low;
        out_buff[3] = output[0].bytes[3].nibbles.high << 4 | output[0].bytes[3].nibbles.low;
    
        out_buff[4] = output[1].bytes[0].nibbles.high << 4 | output[1].bytes[0].nibbles.low;
        out_buff[5] = output[1].bytes[1].nibbles.high << 4 | output[1].bytes[1].nibbles.low;
        out_buff[6] = output[1].bytes[2].nibbles.high << 4 | output[1].bytes[2].nibbles.low;
        out_buff[7] = output[1].bytes[3].nibbles.high << 4 | output[1].bytes[3].nibbles.low;
    
        out_buff[8] = output[2].bytes[0].nibbles.high << 4 | output[2].bytes[0].nibbles.low;
        out_buff[9] = output[2].bytes[1].nibbles.high << 4 | output[2].bytes[1].nibbles.low;
        out_buff[10] = output[2].bytes[2].nibbles.high << 4 | output[2].bytes[2].nibbles.low;
        out_buff[11] = output[2].bytes[3].nibbles.high << 4 | output[2].bytes[3].nibbles.low;
    
        out_buff[12] = output[3].bytes[0].nibbles.high << 4 | output[3].bytes[0].nibbles.low;
        out_buff[13] = output[3].bytes[1].nibbles.high << 4 | output[3].bytes[1].nibbles.low;
        out_buff[14] = output[3].bytes[2].nibbles.high << 4 | output[3].bytes[2].nibbles.low;
        out_buff[15] = output[3].bytes[3].nibbles.high << 4 | output[3].bytes[3].nibbles.low;
    
        fwrite(out_buff, 1, 16, oFile);
    }
    
    for (int i = 14; i >= 0; i--) {
        if ((int)out_buff[i] == (int)out_buff[15]) {
            pad_counter++;
        }
    }
    
    if (pad_counter + 1 == (int)out_buff[15]) {
        fseek(oFile, 0, SEEK_END);       // Seek to the End of the file
        long currentSize = ftell(oFile); // Determine the new File Size
        long newSize = currentSize - (int)out_buff[15];
        ftruncate(fileno(oFile), newSize); // Truncate the File
    }
}