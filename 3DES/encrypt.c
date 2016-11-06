#include "DES.c"

int main(void) {
    char* m = malloc(8);
    strcpy(m, "problem1");

    char* key1 = malloc(8);
    strcpy(key1, "joshkey1");
    char* key2 = malloc(8);
    strcpy(key2, "secondk1");

    char* step1 = encryptDES(m, key1);
    char* step2 = decryptDES(step1, key2);
    char* encrypted = encryptDES(step2, key1);


    step1 = decryptDES(encrypted, key1);
    step2 = encryptDES(step1, key2);
    char* decrypted = decryptDES(step2, key1);
    printf("Result of decryption = %s\n", decrypted);
}

/*
printf("Result of encryption = ");
for(int i = 0; i < 8; i++)
    printf("%02x", encrypted[i] & 0xff);
printf("\n");
*/