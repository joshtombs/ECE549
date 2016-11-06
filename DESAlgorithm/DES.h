#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char* encryptDES(char*, char*);
char* decryptDES(char*, char*);
char* performSixteenRounds(char*, char*, char);
char* roundFunction(int, char*, char*, char*, char*, char*);
char* getPC1(char*);
char* getC0(char*);
char* getD0(char*);
char* shiftLeft(char* , int);
int getRoundShift(int);
char* getPC2(char* , char* );
char* getSubKey(char* );
char* getLO(char* );
char* getRO(char* );
int getBitInPosition(char* , int, int);
char* createETable(char* );
char* getSubKeyInSixBits(char* );
char* putThroughSBox(char* );
char* putThroughPermutation(char* );
char* getLToFourBits(char* );
char* splitMessage(char* , int);
char* getCipherText(char* );
char* getMessageFromLR(char* , char* );