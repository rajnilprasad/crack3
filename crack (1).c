#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

#if __has_include("fileutil.h")
#include "fileutil.h"
#endif

#define PASS_LEN 50     // Maximum length any password will be.
#define HASH_LEN 33     // Length of hash plus one for null.

int compareHashes(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}

int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        printf("Usage: %s hash_file dictionary_file\n", argv[0]);
        exit(1);
    }

    // TODO: Read the hashes file into an array.

    //   Use either a 2D array or an array of arrays.

    //   Use the loadFile function from fileutil.c
    //   Uncomment the appropriate statement.
    int hashCount;
    char (*hashes)[HASH_LEN] = loadFile(argv[1], &hashCount);
    
    // CHALLENGE1: Sort the hashes using qsort.   
        qsort(hashes, hashCount, HASH_LEN, compareHashes);
 
    
    // TODO
    // Open the password file for reading.
    FILE *passFile = fopen(argv[2], "r");

    if (!passFile) {
        perror("Error opening dictionary file");
        free(hashes);
        exit(1);
    }

    // TODO
    // For each password, hash it, then use the array search
    // function from fileutil.h to find the hash.

    char password[PASS_LEN];
    char hash[HASH_LEN];
    int foundCount = 0;

    while (fgets(password, PASS_LEN, passFile)) {
        password[strcspn(password, "\n")] = '\0';

        computeMD5(password, hash);

        // Search using binary search
        int index = binarySearch(hashes, hashCount, hash);

        if (index != -1) {
            printf("Password: %s, Hash: %s\n", password, hash);
            foundCount++;
        }
    }

    fclose(passFile);
    free(hashes);

    printf("Total hashes found: %d\n", foundCount);

    return 0;
}
