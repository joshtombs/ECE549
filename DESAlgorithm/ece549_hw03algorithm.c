#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PRINTTABLES

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

char getHexScheme(char );
char getAsciiFromHex(char);
char* createStringFromCipher(char* );
char* getPC1(char*);
char* getC1(char*);
char* getD1(char*);
char* getPC2(char* , char* );
char* getSubKey(char* );
char* getMessageInBinary(char* );
char* getLO(char* );
char* getRO(char* );
int getBitInPosition(char* , int);
int getBitInPositionSix(char* , int);
int getBitInPositionFour(char* , int);
char* createETable(char* );
char* getSubKeyInSixBits(char* );
char* putThroughSBox(char* );
char* putThroughPermutation(char* );
char* getLToFourBits(char* );
char* getCipherText(char* , char* );

void printPhaseOne(char* , char* , char* , char* , char* );
void printPhaseTwo(char* , char* , char* );
void printPhaseThree(char* , char* , char* , char* , char* );
void printPhaseFour(char* , char* , char* );
void printPhaseFive(char* , char* , char* );

int main(void) {
    char* m = malloc(17);
    strcpy(m, "codebreakproblem");
    //strcpy(m, "hphaanbaplmkapbi"); //Encrypted text of 'codebreakproblem'
    printf("Original Message = %s\n", m);
    
    char* bMessage = getMessageInBinary(m);
    
    printf("Message in Hex   = ");
    for(int i = 0; i < 8; i++)
        printf("%02x", bMessage[i] & 0xff);
    printf("\n");

    
    //Phase 1
    char* key = malloc(8);
    key[0] = 0x01; key[1] = 0x23; key[2] = 0x45; key[3] = 0x67; key[4] = 0x89; key[5] = 0xab; key[6] = 0xcd; key[7] = 0xef;

    char* PCOne = getPC1(key);

    char* C = getC1(PCOne);
    char* D = getD1(PCOne);

    char* PCTwo = getPC2(C, D);

    char* k1;
    k1 = getSubKey(PCTwo);

#ifdef PRINTTABLES
    printPhaseOne(key, PCOne, C, D, PCTwo);
#endif

    //Phase 2
    char* LO = getLO(bMessage);
    char* RO = getRO(bMessage);

#ifdef PRINTTABLES
    printPhaseTwo(bMessage, LO, RO);
#endif

    //Phase 3
    char* eTable = createETable(RO);
    char* sixBitsKey = getSubKeyInSixBits(k1);
    
    char* A = malloc(8);
    for(int i = 0; i < 8; i++) {
        A[i] = eTable[i] ^ sixBitsKey[i];
    }

    char* B = putThroughSBox(A);
    char* PB = putThroughPermutation(B);

#ifdef PRINTTABLES
    printPhaseThree(RO, eTable, A, B, PB);
#endif

    //Phase 4
    char* L = getLToFourBits(LO);
    char* R = malloc(8);

    for(int i = 0; i < 8; i++) {
        R[i] = L[i] ^ PB[i];
    }

    char* Rtwo = getLToFourBits(RO);

#ifdef PRINTTABLES
    printPhaseFour(PB, L, R);
#endif

    char* cipherText = getCipherText(Rtwo, R);

#ifdef PRINTTABLES
    printPhaseFive(Rtwo, R, cipherText);
#endif
    
    printf("CipherText = ");
    for(int i = 0; i < 8; i++)
        printf("%02x", cipherText[i] & 0xff);
    printf("\n");

    char* encryptedAscii = createStringFromCipher(cipherText);
    printf("Message decoded with hex scheme = %s\n", encryptedAscii);

    return 0;
}

char getHexScheme(char c) {
    if(c == 'a')
        return 0;
    else if(c == 'b')
        return 1;
    else if(c == 'c')
        return 2;
    else if(c == 'd')
        return 3;
    else if(c == 'e')
        return 4;
    else if(c == 'f')
        return 5;
    else if(c == 'g')
        return 6;
    else if(c == 'h')
        return 7;
    else if(c == 'i')
        return 8;
    else if(c == 'j' || c == 'r')
        return 9;
    else if(c == 'k')
        return 10;
    else if(c == 'l')
        return 11;
    else if(c == 'm')
        return 12;
    else if(c == 'n')
        return 13;
    else if(c == 'o')
        return 14;
    else if(c == 'p')
        return 15;
    else 
        return -1;
}

char getAsciiFromHex(char hex) {
    if(hex == 0x00)
        return 'a';
    else if(hex == 0x01)
        return 'b';
    else if(hex == 0x02)
        return 'c';
    else if(hex == 0x03)
        return 'd';
    else if(hex == 0x04)
        return 'e';
    else if(hex == 0x05)
        return 'f';
    else if(hex == 0x06)
        return 'g';
    else if(hex == 0x07)
        return 'h';
    else if(hex == 0x08)
        return 'i';
    else if(hex == 0x09)
        return 'r';
        //return 'j';
    else if(hex == 0x0A)
        return 'k';
    else if(hex == 0x0B)
        return 'l';
    else if(hex == 0x0C)
        return 'm';
    else if(hex == 0x0D)
        return 'n';
    else if(hex == 0x0E)
        return 'o';
    else if(hex == 0x0F)
        return 'p';
    else 
        return -1;
}

char* createStringFromCipher(char* cipher) {
    char* a = malloc(17);
    for(int i = 0; i < 8; i++){
        a[2*i + 1] = getAsciiFromHex(cipher[i] & 0x0f);
        a[2*i] = getAsciiFromHex((cipher[i]>>4) & 0x0f);
        //printf("a[%d] = ")
    }

    a[16] = '\0';
    return a;
}

char* getPC1(char* k) {
    char* PC = malloc(7);
    char tmp;
    for(int i = 0; i < 7; i++) {
        tmp = 0;
        for(int j = 0; j < 8; j++) {
            tmp |= (getBitInPosition(k, PC1[i][j])<<(7-j));
        }
        PC[i] = tmp;
    }

    return PC;
}

char* getC1(char* PCOne) {
    char* C1 = malloc(7);
    char tmp;
    for(int i = 0; i < 7; i++) {
        tmp = 0;
        for(int j = 0; j < 4; j++) {
            tmp |= getBitInPosition(PCOne, i*4 + j + 1)<<(3-j);
        }
        C1[i] = tmp;
    }

    int bit1 = getBitInPositionFour(C1, 1);
    for(int i = 0; i < 7; i++) {
        tmp = 0;
        for(int j = 0; j < 4; j++) {
            if(i == 6 && j == 3)
                tmp |= bit1;
            else
                tmp |= getBitInPositionFour(C1, i*4 + j + 1 +1)<<(3-j);
        }
        C1[i] = tmp;
    }

    return C1;
}

char* getD1(char* PCOne) {
    char* D1 = malloc(7);
    char tmp;
    for(int i = 0; i < 7; i++) {
        tmp = 0;
        for(int j = 0; j < 4; j++) {
            tmp |= getBitInPosition(PCOne, 28 + i*4 + j + 1)<<(3-j);
        }
        D1[i] = tmp;
    }

    int bit1 = getBitInPositionFour(D1, 1);
    for(int i = 0; i < 7; i++) {
        tmp = 0;
        for(int j = 0; j < 4; j++) {
            if(i == 6 && j == 3)
                tmp |= bit1;
            else
                tmp |= getBitInPositionFour(D1, i*4 + j + 1 +1)<<(3-j);
        }
        D1[i] = tmp;
    }

    return D1;
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
                tmp |= getBitInPositionFour(C1, index)<<(7-j);
            else
                tmp |= getBitInPositionFour(D1, index-28)<<(7-j);
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
            temp |= getBitInPosition(pcTwo, i*8 + j + 1)<<(7-j);
        }
        subKey[i] = temp;
    }
    /*
    printf("\nSubkey = ");
    for(int i = 0; i < 6; i++)
        printf("%02x", subKey[i] & 0xff);
    printf("\n");
    */
    
    return subKey;
}

char* getMessageInBinary(char* message) {
    char* m = malloc(8);
    char temp;
    for(int i = 0; i < 8; i++) {
        temp = 0;
        temp |= getHexScheme(message[2*i])<<4;
        temp |= getHexScheme(message[2*i+1]);
        m[i] = temp;
    }
    return m;
}

char* getLO(char* m) {
    char* LO = malloc(4);
    char tmp;
    for(int i = 0; i < 4; i++) {
        tmp = 0;
        for(int j = 0; j < 8; j++) {
            tmp |= (getBitInPosition(m, initialPermutation[i][j])<<(7-j));
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
            tmp |= (getBitInPosition(m, initialPermutation[i][j])<<(7-j));
        }
        RO[i-4] = tmp;
    }
    return RO;
}

int getBitInPosition(char* m, int pos) {
    pos -= 1;
    int bytePos = pos / 8;
    int bitPos;

    if(bytePos > 0)
        bitPos = pos % 8  + 1;
    else
        bitPos = (pos+1) % 9;

    return ((m[bytePos]>>(8-bitPos)) & 1);
}

int getBitInPositionSix(char* m, int pos) {
    pos -= 1;
    int bytePos = pos / 6;
    int bitPos;

    if(bytePos > 0)
        bitPos = pos % 6  + 1;
    else
        bitPos = (pos+1) % 7;

    return ((m[bytePos]>>(6-bitPos)) & 1);
}

int getBitInPositionFour(char* m, int pos) {
    pos -= 1;
    int bytePos = pos / 4;
    int bitPos;

    if(bytePos > 0)
        bitPos = pos % 4  + 1;
    else
        bitPos = (pos+1) % 5;

    return ((m[bytePos]>>(4-bitPos)) & 1);
}

char* createETable(char* R) {
    char* e = malloc(8);
    char tmp;
    for(int i = 0; i < 8; i++) {
        tmp = 0;
        for(int j = 0; j < 6; j++) {
            tmp |= (getBitInPosition(R, eTableValues[i][j])<<(5-j));
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
            tmp |= (getBitInPosition(k, keyCount)<<(5-j));
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
        row = getBitInPositionSix(a, 1 + 6*i)<<1 | getBitInPositionSix(a, 6 + 6*i);
        for( int j = 0; j < 4; j++) {
            col |= getBitInPositionSix(a, 2+j + 6*i)<<(3-j);
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
            tmp |= (getBitInPositionFour(b, permutationOrder[4*i + j]))<<(3-j);
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

char* getCipherText(char* L1, char* R1) {
    char* ct = malloc(8);
    char temp;
    int index = 0;
    /*
    printf("Result of Rounds     = ");
    for(int i = 0; i < 8; i++)
        printf("%x", R1[i] & 0xff);
    for(int i = 0; i < 8; i++)
        printf("%x", L1[i] & 0xff);
    printf("\n");
    */
    for(int i = 0; i < 8; i++) {
        temp = 0;
        for(int j = 0; j < 8; j++){
            index = finalPermutation[i][j];
            if(index < 33)
                temp |= getBitInPositionFour(R1, index)<<(7-j);
            else
                temp |= getBitInPositionFour(L1, index-32)<<(7-j);
        }
        ct[i] = temp;
    }

    return ct;
}

void printPhaseOne(char* key, char* PCOne, char* C1, char* D1, char* PCTwo) {
    printf("Phase 1\n");
    //Print Key in Binary
    printf("        |");
    for(int i = 1; i < 33; i++) {
        printf("%3d|", i);
    }
    printf("\n");

    printf(" 64-bit |");
    for(int i = 1; i < 33; i++){
        printf("%3d|", getBitInPosition(key, i));
    }
    printf("\n");

    printf("   key  |");
    for(int i = 33; i < 65; i++) {
        printf("%3d|", i);
    }
    printf("\n");
    printf("        |");
    for(int i = 33; i < 65; i++){
        printf("%3d|", getBitInPosition(key, i));
    }

    printf("\n\n");

    //Print PC1
    printf("        |");
    for(int i = 0; i < 28; i++)
        printf("%3d|", PC1[i/8][i%8]);
    printf("\n");

    printf("  PC-1  |");
    for(int i = 1; i < 29; i++)
        printf("%3d|", getBitInPosition(PCOne, i));
    printf("\n");

    printf("        |");
    for(int i = 28; i < 56; i++)
        printf("%3d|", PC1[i/8][i%8]);
    printf("\n");

    printf("        |");
    for(int i = 29; i < 57; i++)
        printf("%3d|", getBitInPosition(PCOne, i));

    printf("\n\n");

    //Print C1
    printf("        |");
    for(int i = 1; i < 15; i++)
        printf("%3d|", i);
    printf("\n");

    printf("   C1   |");
    for(int i = 1; i < 15; i++)
        printf("%3d|", getBitInPositionFour(C1, i));
    printf("\n");

    printf("        |");
    for(int i = 15; i < 29; i++)
        printf("%3d|", i);
    printf("\n");

    printf("        |");
    for(int i = 15; i < 29; i++)
        printf("%3d|", getBitInPositionFour(C1, i));

    printf("\n\n");    

    //Print D1
    printf("        |");
    for(int i = 29; i < 43; i++)
        printf("%3d|", i);
    printf("\n");

    printf("   D1   |");
    for(int i = 1; i < 15; i++)
        printf("%3d|", getBitInPositionFour(D1, i));
    printf("\n");

    printf("        |");
    for(int i = 43; i < 57; i++)
        printf("%3d|", i);
    printf("\n");

    printf("        |");
    for(int i = 15; i < 29; i++)
        printf("%3d|", getBitInPositionFour(D1, i));

    printf("\n\n");    

    //Print PC-2
    printf("        |");
    for(int i = 0; i < 24; i++)
        printf("%3d|", PC2[i/8][i%8]);
    printf("\n");

    printf("  PC-2  |");
    for(int i = 1; i < 25; i++)
        printf("%3d|", getBitInPosition(PCTwo, i));
    printf("\n");

    printf("        |");
    for(int i = 24; i < 48; i++)
        printf("%3d|", PC2[i/8][i%8]);
    printf("\n");

    printf("        |");
    for(int i = 25; i < 49; i++)
        printf("%3d|", getBitInPosition(PCTwo, i));

    printf("\n\n");    
}

void printPhaseTwo(char* bm, char* LO, char* RO) {
    printf("Phase 2\n");

    //Print Binary Message
    printf("        |");
    for(int i = 1; i < 33; i++)
        printf("%3d|",i);

    printf("\n 64-bit |");

    for(int i = 1; i < 33; i++)
        printf("%3d|", getBitInPosition(bm, i));


    printf("\n    m   |");
    for(int i = 33; i < 65; i++)
        printf("%3d|",i);

    printf("\n        |");

    for(int i = 33; i < 65; i++)
        printf("%3d|", getBitInPosition(bm, i));

    printf("\n\n");

    //Print LO
    printf("        |");
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 8; j++)
            printf("%3d|", initialPermutation[i][j]);

    printf("\n   L0   |");
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 8; j++)
            printf("%3d|", getBitInPosition(LO, 8*i + j + 1));

    printf("\n        |");
    for(int i = 2; i < 4; i++)
        for(int j = 0; j < 8; j++)
            printf("%3d|", initialPermutation[i][j]);
    
    printf("\n        |");
    for(int i = 2; i < 4; i++)
        for(int j = 0; j < 8; j++)
            printf("%3d|", getBitInPosition(LO, 8*i + j + 1));

    printf("\n\n");

    //Print RO
    printf("        |");
    for(int i = 4; i < 6; i++)
        for(int j = 0; j < 8; j++)
            printf("%3d|", initialPermutation[i][j]);

    printf("\n   R0   |");
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 8; j++)
            printf("%3d|", getBitInPosition(RO, 8*i + j + 1));

    printf("\n        |");
    for(int i = 6; i < 8; i++)
        for(int j = 0; j < 8; j++)
            printf("%3d|", initialPermutation[i][j]);
    
    printf("\n        |");
    for(int i = 2; i < 4; i++)
        for(int j = 0; j < 8; j++)
            printf("%3d|", getBitInPosition(RO, 8*i + j + 1));

    printf("\n\n");
}

void printPhaseThree(char* RO, char* E, char* A, char* B, char* PB) {
    printf("Phase 3\n");

    printf("Step 1.\n");
    //Print RO
    printf("        |");
    for(int i = 1; i < 17; i++)
            printf("%3d|", i);

    printf("\n   R0   |");
    for(int i = 1; i < 17; i++)
            printf("%3d|", getBitInPosition(RO, i));

    printf("\n        |");
    for(int i = 17; i < 33; i++)
            printf("%3d|", i);
    
    printf("\n        |");
    for(int i = 17; i < 33; i++)
            printf("%3d|", getBitInPosition(RO, i));

    printf("\n\n");

    //Print E Table
    printf("\n        | 32|");
    for(int i = 1; i < 6; i++)
        printf("%3d|", i);
    printf("\n        |");
    
    for(int i = 1; i < 7; i++)
        printf("%3d|", getBitInPositionSix(E, i));

    printf("\n        |");
    for(int i = 4; i < 10; i++)
        printf("%3d|", i);
    printf("\n        |");
        
    for(int i = 7; i < 13; i++)
        printf("%3d|", getBitInPositionSix(E, i));

    printf("\n        |");
    for(int i = 8; i < 14; i++)
        printf("%3d|", i);
    printf("\n        |");
        
    for(int i = 13; i < 19; i++)
        printf("%3d|", getBitInPositionSix(E, i));

    printf("\n        |");
    for(int i = 12; i < 18; i++)
        printf("%3d|", i);
    printf("\n E Table|");
        
    for(int i = 19; i < 25; i++)
        printf("%3d|", getBitInPositionSix(E, i));

    printf("\n        |");
    for(int i = 16; i < 22; i++)
        printf("%3d|", i);
    printf("\n        |");
        
    for(int i = 25; i < 31; i++)
        printf("%3d|", getBitInPositionSix(E, i));

    printf("\n        |");
    for(int i = 20; i < 26; i++)
        printf("%3d|", i);
    printf("\n        |");
        
    for(int i = 31; i < 37; i++)
        printf("%3d|", getBitInPositionSix(E, i));

    printf("\n        |");
    for(int i = 24; i < 30; i++)
        printf("%3d|", i);
    printf("\n        |");
        
    for(int i = 37; i < 43; i++)
        printf("%3d|", getBitInPositionSix(E, i));

    printf("\n        |");
    for(int i = 28; i < 33; i++)
        printf("%3d|", i);
    printf("%3d|",1);
    printf("\n        |");
        
    for(int i = 43; i < 49; i++)
        printf("%3d|", getBitInPositionSix(E, i));

    printf("\n\n");

    printf("Step 2.\n");

    printf("Result: A = ");
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 6; j++) {
            printf("%d",getBitInPositionSix(A,6*i + j + 1));
        }
        printf("  ");
    }

    printf("\n\n");

    printf("Step 3.\n");

    printf("6-bit from A |             |              |  In base 2\n");
    char row, col;
    for(int i = 0; i < 8; i++) {
        printf("   ");
        for(int j = 0; j < 6; j++)
            printf("%d", getBitInPositionSix(A, 6*i + j + 1));
        printf("    |");

        printf(" S%d(%d%d,", i, getBitInPositionSix(A, 6*i +1), getBitInPositionSix(A, 6*i +6));
        for(int j = 1; j < 5; j++)
            printf("%d", getBitInPositionSix(A, 6*i + j + 1));
        printf(") |");
        
        row = ((getBitInPositionSix(A, 6*i +1))<<1) | (getBitInPositionSix(A, 6*i +6));
        col = 0;
        for(int j = 1; j < 5; j++)
            col |= (getBitInPositionSix(A, 6*i + j + 1))<<(3-(j-1));

        printf(" S%d(%x,%x) = %2d |", i, row, col, SBox[i][row][col]);

        printf("   ");
        for(int j = 1; j < 5; j++)
            printf("%d", getBitInPositionFour(B, 4*i + j));

        printf("\n");
    }
    printf("\n\n");

    printf("Step 4.\n");

    printf("Result: B = ");
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 4; j++) {
            printf("%d",getBitInPositionFour(B,4*i + j + 1));
        }
        printf("  ");
    }    
    printf("\n\n");

    printf("Step 5.\n");
    printf("\n        |");
    for(int i = 1; i < 9; i++)
        printf("%3d|",i);
    
    printf("\n        |");
    for(int i = 1; i < 9; i++)
        printf("%3d|", getBitInPositionFour(B, i));
    
    printf("\n        |");
    for(int i = 9; i < 17; i++)
        printf("%3d|",i);
    
    printf("\n   B    |");
    for(int i = 9; i < 17; i++)
        printf("%3d|", getBitInPositionFour(B, i));
    
    printf("\n        |");
    for(int i = 17; i < 25; i++)
        printf("%3d|",i);
    
    printf("\n        |");
    for(int i = 17; i < 25; i++)
        printf("%3d|", getBitInPositionFour(B, i));
    
    printf("\n        |");
    for(int i = 25; i < 33; i++)
        printf("%3d|",i);
    
    printf("\n        |");
    for(int i = 25; i < 33; i++)
        printf("%3d|", getBitInPositionFour(B, i));
    
    printf("\n\n");

    printf("\n        |");
    for(int i = 1; i < 9; i++)
        printf("%3d|",permutationOrder[i-1]);
    
    printf("\n        |");
    for(int i = 1; i < 9; i++)
        printf("%3d|", getBitInPositionFour(B, permutationOrder[i-1]));
    
    printf("\n        |");
    for(int i = 9; i < 17; i++)
        printf("%3d|",permutationOrder[i-1]);
    
    printf("\n P(B)   |");
    for(int i = 9; i < 17; i++)
        printf("%3d|", getBitInPositionFour(B, permutationOrder[i-1]));
    
    printf("\n        |");
    for(int i = 17; i < 25; i++)
        printf("%3d|",permutationOrder[i-1]);
    
    printf("\n        |");
    for(int i = 17; i < 25; i++)
        printf("%3d|", getBitInPositionFour(B, permutationOrder[i-1]));
    
    printf("\n        |");
    for(int i = 25; i < 33; i++)
        printf("%3d|",permutationOrder[i-1]);
    
    printf("\n        |");
    for(int i = 25; i < 33; i++)
        printf("%3d|", getBitInPositionFour(B, permutationOrder[i-1]));
    
    printf("\n\n");

    printf("Result: P(B) = ");
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 4; j++) {
            printf("%d",getBitInPositionFour(PB,4*i + j + 1));
        }
        printf("  ");
    }    
    printf("\n\n");
}

void printPhaseFour(char* PB, char* L, char* R) {
    printf("Phase 4\n");
    printf("LO = \n");
    printf("|  R(B)  |       |    L0   |       |   R1    |\n");
    for(int i = 0; i < 8; i++){
        printf("|  ");
        for(int j = 0; j < 4; j++)
            printf("%d", getBitInPositionFour(PB, 4*i + j + 1));
        printf("  |%s|   ", (i != 3)?"       ":"  XOR  ");
        for(int j = 0; j < 4; j++)
            printf("%d", getBitInPositionFour(L, 4*i + j + 1));
        printf("  |%s|  ", (i != 3)?"       ":"   =   ");
        for(int j = 0; j < 4; j++)
            printf("%d", getBitInPositionFour(R, 4*i + j + 1));
        printf("   |\n");
    }
    printf("\n\n");
}

void printPhaseFive(char* L1, char* R1, char* C) {
    printf("Phase 5\n");

    printf("        |");
    for(int i = 1; i < 17; i++)
            printf("%3d|", i);

    printf("\n   R1   |");
    for(int i = 1; i < 17; i++)
        printf("%3d|", getBitInPositionFour(R1, i));

    printf("\n        |");
    for(int i = 17; i < 33; i++)
            printf("%3d|", i);
    
    printf("\n        |");
    for(int i = 17; i < 33; i++)
            printf("%3d|", getBitInPositionFour(R1, i));

    printf("\n\n");    

    //Print L1
    printf("        |");
    for(int i = 33; i < 49; i++)
            printf("%3d|", i);

    printf("\n   L1   |");
    for(int i = 1; i < 17; i++)
        printf("%3d|", getBitInPositionFour(L1, i));

    printf("\n        |");
    for(int i = 49; i < 65; i++)
            printf("%3d|", i);
    
    printf("\n        |");
    for(int i = 17; i < 33; i++)
            printf("%3d|", getBitInPositionFour(L1, i));

    printf("\n\n");

    //Print CipherText
    printf("        |");
    for(int i = 0; i < 32; i++)
            printf("%3d|", finalPermutation[i/8][i%8]);

    printf("\n   CT   |");
    for(int i = 1; i < 33; i++)
        printf("%3d|", getBitInPosition(C, i));

    printf("\n        |");
    for(int i = 32; i < 64; i++)
            printf("%3d|", finalPermutation[i/8][i%8]);
    
    printf("\n        |");
    for(int i = 33; i < 65; i++)
            printf("%3d|", getBitInPosition(C, i));

    printf("\n\n");
}