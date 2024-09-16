
// To perform the Encryption
void Encrypt(const HexWord *in, const HexWord *key, HexWord *out) { 
    HexWord state[4], word_key[4];
    unsigned char Nr = 10;
    
    word_key[0] = key[0];
    word_key[1] = key[1];
    word_key[2] = key[2];
    word_key[3] = key[3];
    
    wordXOR(in, word_key, state);
    
    for (unsigned char i = 1; i < Nr; i++) {
        subBytes(state, out);
        shiftRows(out, state);
        MixColumns(state, out);
        
        word_key[0] = key[4 * i];
        word_key[1] = key[4 * i + 1];
        word_key[2] = key[4 * i + 2];
        word_key[3] = key[4 * i + 3];
        
        wordXOR(out, word_key, state); } 
    
    subBytes(state, out);
    shiftRows(out, state);
    
    word_key[0] = key[40];
    word_key[1] = key[41];
    word_key[2] = key[42];
    word_key[3] = key[43];
    
    wordXOR(state, word_key, out);
}

// To perform the Decryption
void Decrypt(const HexWord *in, const HexWord *key, HexWord *out) {
    HexWord state[4], word_key[4];
    unsigned char Nr = 10;
    
    word_key[0] = key[40];
    word_key[1] = key[41];
    word_key[2] = key[42];
    word_key[3] = key[43];
    
    wordXOR(in, word_key, state);
    
    for (unsigned char i = Nr - 1; i > 0; i--) { 
        InvShiftRows(state, out);
        InvSubBytes(out, state);
        
        word_key[0] = key[4 * i];
        word_key[1] = key[4 * i + 1];
        word_key[2] = key[4 * i + 2];
        word_key[3] = key[4 * i + 3];
        
        wordXOR(state, word_key, out);
        InvMixColumns(out, state); } 
    
    InvShiftRows(state, out);
    InvSubBytes(out, state);
    
    word_key[0] = key[0];
    word_key[1] = key[1];
    word_key[2] = key[2];
    word_key[3] = key[3];
    
    wordXOR(state, word_key, out);
}