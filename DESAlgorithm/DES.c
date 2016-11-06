#include "DES.h"

int PC1[7][8] = {{57, 49, 41, 33, 25, 17,  9,  1},
                 {58, 50, 42, 34, 26, 18, 10,  2}, 
                 {59, 51, 43, 35, 27, 19, 11,  3},
                 {60, 52, 44, 36, 63, 55, 47, 39},
                 {31, 23, 15,  7, 62, 54, 46, 38},
                 {30, 22, 14,  6, 61, 53, 45, 37},
                 {29, 21, 13,  5, 28, 20, 12,  4}
               };

int PC2[6][8] = {{14, 17, 11, 24,  1,  5,  3, 28},
                 {15,  6, 21, 10, 23, 19, 12,  4},
                 {26,  8, 16,  7, 27, 20, 13,  2},
                 {41, 52, 31, 37, 47, 55, 30, 40},
                 {51, 45, 33, 48, 44, 49, 39, 56},
                 {34, 53, 46, 42, 50, 36, 29, 32}
                };

int initialPermutation[8][8] = {{58, 50, 42, 34, 26, 18, 10, 2} ,
                                {60, 52, 44, 36, 28, 20, 12, 4}, 
                                {62, 54, 46, 38, 30, 22, 14, 6}, 
                                {64, 56, 48, 40, 32, 24, 16, 8}, 
                                {57, 49, 41, 33, 25, 17,  9, 1}, 
                                {59, 51, 43, 35, 27, 19, 11, 3}, 
                                {61, 53, 45, 37, 29, 21, 13, 5}, 
                                {63, 55, 47, 39, 31, 23, 15, 7}};

int finalPermutation[8][8] = {{40,  8, 48, 16, 56, 24, 64, 32},
                              {39,  7, 47, 15, 55, 23, 63, 31},
                              {38,  6, 46, 14, 54, 22, 62, 30},
                              {37,  5, 45, 13, 53, 21, 61, 29},
                              {36,  4, 44, 12, 52, 20, 60, 28},
                              {35,  3, 43, 11, 51, 19, 59, 27},
                              {34,  2, 42, 10, 50, 18, 58, 26},
                              {33,  1, 41,  9, 49, 17, 57, 25}};

int eTableValues[8][6] = {  {32,  1,  2,  3,  4,  5},
                            { 4,  5,  6,  7,  8,  9},
                            { 8,  9, 10, 11, 12, 13},
                            {12, 13, 14, 15, 16, 17},
                            {16, 17, 18, 19, 20, 21},
                            {20, 21, 22, 23, 24, 25},
                            {24, 25, 26, 27, 28, 29},
                            {28, 29, 30, 31, 32,  1}};

int SBox[8][4][16] = {  {   {14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},
                            { 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},
                            { 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0},
                            {15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13}},

                        {   {15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10},
                            { 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5},
                            { 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15},
                            {13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9}},

                        {   {10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8},
                            {13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1},
                            {13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7},
                            { 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12}},

                        {   { 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15},
                            {13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9},
                            {10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4},
                            { 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14}},

                        {   { 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9},
                            {14, 11,  2, 13,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6},
                            { 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14},
                            {11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3}},

                        {   {12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11},
                            {10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8},
                            { 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6},
                            { 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13}},

                        {   { 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1},
                            {13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6},
                            { 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2},
                            { 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12}},

                        {   {13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7},
                            { 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2},
                            { 7, 11,  4,  1,  9, 12, 14,  2,  0 , 6, 10, 13, 15,  3,  5,  8},
                            { 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11}}
                     };

int permutationOrder[32] = {16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10, 2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25};

char* encryptDES(char* m, char* key) {
    char* result = performSixteenRounds(key, m, 'E');
    char* cipherText = getCipherText(result);    
    return cipherText;
}

char* decryptDES(char* m, char* key) {
    char* result = performSixteenRounds(key, m, 'D');
    char* cipherText = getCipherText(result);
    return cipherText;
}

char* performSixteenRounds(char* key, char* binaryMessage, char direction) {
    char* PCOne = getPC1(key);
    char* C0 = getC0(PCOne);
    char* D0 = getD0(PCOne);
    char* message = binaryMessage;

    char* L0 = getLO(message);
    char* R0 = getRO(message);

    if( direction == 'e' || direction == 'E'){
        for(int i = 1; i <= 16; i++) {
            message = roundFunction(i, C0, D0, message, L0, R0);
            L0 = splitMessage(message, 1);
            R0 = splitMessage(message, 2);;
        }
    } else if( direction == 'd' || direction == 'D'){
        for(int i = 16; i >= 1; i--) {
            message = roundFunction(i, C0, D0, message, L0, R0);
            L0 = splitMessage(message, 1);
            R0 = splitMessage(message, 2);;
        }
    } else {
        exit(1);
    }
    
    return message;
}

char* roundFunction(int round, char* C0, char* D0, char* bMessage, char* LO, char* RO) {
    char* C = shiftLeft(C0, getRoundShift(round));
    char* D = shiftLeft(D0, getRoundShift(round));
    char* PCTwo = getPC2(C, D);
    char* subKey = getSubKey(PCTwo);

    char* eTable = createETable(RO);
    char* sixBitsKey = getSubKeyInSixBits(subKey);
    
    char* A = malloc(8);
    for(int i = 0; i < 8; i++) {
        A[i] = eTable[i] ^ sixBitsKey[i];
    }

    char* B = putThroughSBox(A);
    char* PB = putThroughPermutation(B);

    char* L = getLToFourBits(LO);
    char* R = malloc(8);

    for(int i = 0; i < 8; i++) {
        R[i] = L[i] ^ PB[i];
    }

    char* Rtwo = getLToFourBits(RO);
    char* message = getMessageFromLR(Rtwo, R);

    return message;
}

char* getPC1(char* k) {
    char* PC = malloc(7);
    char tmp;
    for(int i = 0; i < 7; i++) {
        tmp = 0;
        for(int j = 0; j < 8; j++) {
            tmp |= (getBitInPosition(k, PC1[i][j], 8)<<(7-j));
        }
        PC[i] = tmp;
    }

    return PC;
}

char* getC0(char* PCOne) {
    char* C0 = malloc(7);
    char tmp;
    for(int i = 0; i < 7; i++) {
        tmp = 0;
        for(int j = 0; j < 4; j++) {
            tmp |= getBitInPosition(PCOne, i*4 + j + 1, 8)<<(3-j);
        }
        C0[i] = tmp;
    }

    return C0;
}

char* getD0(char* PCOne) {
    char* D0 = malloc(7);
    char tmp;
    for(int i = 0; i < 7; i++) {
        tmp = 0;
        for(int j = 0; j < 4; j++) {
            tmp |= getBitInPosition(PCOne, 28 + i*4 + j + 1, 8)<<(3-j);
        }
        D0[i] = tmp;
    }

    return D0;
}

char* shiftLeft(char* a, int n) {
    char* CN = malloc(7);
    char* ref = a;
    int bit1;
    char tmp;

    for(int k = 0; k < n; k++){
        bit1 = getBitInPosition(ref, 1, 4);
        for(int i = 0; i < 7; i++) {
            tmp = 0;
            for(int j = 0; j < 4; j++) {
                if(i == 6 && j == 3)
                    tmp |= bit1;
                else
                    tmp |= getBitInPosition(ref, i*4 + j + 1 + 1, 4)<<(3-j);
            }
            CN[i] = tmp;
        }
        ref = CN;
    }

    return CN;
}

int getRoundShift(int round) {
    int shifts[16] = {1, 2, 4, 6, 8, 10, 12, 14, 15, 17, 19, 21, 23, 25, 27, 28};
    return shifts[round-1];
}

char* getPC2(char* C1, char* D1) {
    char* PCTwo = malloc(6);
    char tmp;
    int index = 0;
    for(int i = 0; i < 6; i++) {
        tmp = 0;
        for(int j = 0; j < 8; j++) {
            index = PC2[i][j];
            if(index < 29)
                tmp |= getBitInPosition(C1, index, 4)<<(7-j);
            else
                tmp |= getBitInPosition(D1, index-28, 4)<<(7-j);
        }
        PCTwo[i] = tmp;
    }

    return PCTwo;
}

char* getSubKey(char* pcTwo) {
    char* subKey = malloc(6);
    char temp;
    for(int i = 0; i < 6; i++) {
        temp = 0;
        for(int j = 0; j < 8; j++){
            temp |= getBitInPosition(pcTwo, i*8 + j + 1, 8)<<(7-j);
        }
        subKey[i] = temp;
    }
    return subKey;
}

char* getLO(char* m) {
    char* LO = malloc(4);
    char tmp;
    for(int i = 0; i < 4; i++) {
        tmp = 0;
        for(int j = 0; j < 8; j++) {
            tmp |= (getBitInPosition(m, initialPermutation[i][j], 8)<<(7-j));
        }
        LO[i] = tmp;
    }
    return LO;
}

char* getRO(char* m) {
    char* RO = malloc(4);
    char tmp;
    for(int i = 4; i < 8; i++) {
        tmp = 0;
        for(int j = 0; j < 8; j++) {
            tmp |= (getBitInPosition(m, initialPermutation[i][j], 8)<<(7-j));
        }
        RO[i-4] = tmp;
    }
    return RO;
}

int getBitInPosition(char* m, int pos, int length) {
    pos -= 1;
    int bytePos = pos / length;
    int bitPos;

    if(bytePos > 0)
        bitPos = pos % length  + 1;
    else
        bitPos = (pos+1) % (length+1);

    return ((m[bytePos]>>(length-bitPos)) & 1);
}

char* createETable(char* R) {
    char* e = malloc(8);
    char tmp;
    for(int i = 0; i < 8; i++) {
        tmp = 0;
        for(int j = 0; j < 6; j++) {
            tmp |= (getBitInPosition(R, eTableValues[i][j], 8)<<(5-j));
        }
        e[i] = tmp;
    }
    return e;
}

char* getSubKeyInSixBits(char* k) {
    char* s = malloc(8);
    char tmp;
    int keyCount = 1;
    for(int i = 0; i < 8; i++) {
        tmp = 0;
        for(int j = 0; j < 6; j++) {
            tmp |= (getBitInPosition(k, keyCount, 8)<<(5-j));
            keyCount++;
        }
        s[i] = tmp;
    }
    return s;
}

char* putThroughSBox(char* a) {
    char* b = malloc(8);
    char row, col;

    for(int i = 0; i < 8; i++) {
        row = 0; col = 0;
        row = getBitInPosition(a, 1 + 6*i, 6)<<1 | getBitInPosition(a, 6 + 6*i, 6);
        for( int j = 0; j < 4; j++) {
            col |= getBitInPosition(a, 2+j + 6*i, 6)<<(3-j);
        }

        b[i] = SBox[i][row][col];
    }

    return b;
}

char* putThroughPermutation(char* b) {
    char* p = malloc(8);
    char tmp;

    for(int i = 0; i < 8; i++) {
        tmp = 0;
        for(int j = 0; j < 4; j++) {
            tmp |= (getBitInPosition(b, permutationOrder[4*i + j], 4))<<(3-j);
        }
        p[i] = tmp;
    }

    return p;
}

char* getLToFourBits(char* l) {
    char* f = malloc(8);

    for(int i = 0; i < 8; ) {
        f[i] = ((l[(int)floor((float)i/2)])>>4) & 0x0f;
        i++;
        f[i] = (l[(int)floor((float)i/2)]) & 0x0f;
        i++;
    }

    return f;
}

char* getMessageFromLR(char* L1, char* R1) {
    char* m = malloc(8);
    char temp;
    int index = 0;

    for(int i = 0; i < 8; i++) {
        temp = 0;
        for(int j = 0; j < 8; j++){
            index = 8*i + j + 1;
            if(index < 33)
                temp |= getBitInPosition(L1, index, 4)<<(7-j);
            else
                temp |= getBitInPosition(R1, index-32, 4)<<(7-j);
        }
        m[i] = temp;
    }  

    return m;
}

char* splitMessage(char* message, int half) {
    int n, index = 0;
    char* split = malloc(4);
    char tmp;

    if(half == 1)
        n = 0;
    else if(half == 2)
        n = 4;
    else
        exit(1);

    for(int i = n; i < n+4; i++) {
        tmp = 0;
        for(int j = 0; j < 8; j++) {
            tmp |= getBitInPosition(message, i*8 + j + 1, 8)<<(7-j);
        }
        split[index] = tmp;
        index++;
    }

    return split;
}

char* getCipherText(char* m) {
    char* reverseM = malloc(8);
    char* ct = malloc(8);
    char temp;
    int index = 0;

    for(int i = 0; i < 4; i++) {
        reverseM[i] = m[i+4];
    }
    for(int i = 4; i < 8; i++) {
        reverseM[i] = m[i-4];
    }

    for(int i = 0; i < 8; i++) {
        temp = 0;
        for(int j = 0; j < 8; j++){
            index = finalPermutation[i][j];
            temp |= getBitInPosition(reverseM, index, 8)<<(7-j);
        }
        ct[i] = temp;
    }

    return ct;
}