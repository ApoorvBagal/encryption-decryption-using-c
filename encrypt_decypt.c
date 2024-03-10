#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX 10000
#define S 100
#define LSIZ 1280
#define RSIZ 100

char ciphertext[2000000], enc[100], dec[100];
int strint[1000000];
int c = 0;
int i, j, len;
char encc[S];
FILE *fPtr;
char datafile[100];

void append(char *s, char c)
{
    int len = strlen(s);
    s[len] = c;
    s[len + 1] = '\0';
}

void caesarenc(char plt[])
{
    char ch;
    int i, key;
    printf("Enter key: (Number) \n");
    scanf("%d", &key);

    for (i = 0; plt[i] != '\0'; ++i)
    {
        ch = plt[i];
        if (isalpha(plt[i]))
        {
            if (ch >= 'a' && ch <= 'z')
            {
                ch = ch + key;

                if (ch > 'z')
                {
                    ch = ch - 'z' + 'a' - 1;
                }
                enc[i] = ch;
            }
            else if (ch >= 'A' && ch <= 'Z')
            {
                ch = ch + key;

                if (ch > 'Z')
                {
                    ch = ch - 'Z' + 'A' - 1;
                }
                enc[i] = ch;
            }
        }
        else
        {
            enc[i] = plt[i];
        }
    }
    enc[i + 1] = '\0';
    fPtr = fopen(datafile, "w");
    fprintf(fPtr, "%s", enc);
    fclose(fPtr);
    printf("Encrypted message: %s", enc);
}

void caesar_de(char encc[])
{
    char ch;
    int i, key;
    printf("\nEnter the key to decrypt\n");
    scanf("%d", &key);

    for (i = 0; encc[i] != '\0'; ++i)
    {
        ch = encc[i];
        if (isalpha(encc[i]))
        {
            if (ch >= 'a' && ch <= 'z')
            {
                ch = ch - key;

                if (ch < 'a')
                {
                    ch = ch + 'z' - 'a' + 1;
                }

                dec[i] = ch;
            }
            else if (ch >= 'A' && ch <= 'Z')
            {
                ch = ch - key;

                if (ch < 'A')
                {
                    ch = ch + 'Z' - 'A' + 1;
                }

                dec[i] = ch;
            }
        }
        else
        {
            dec[i] = encc[i];
        }
    }
    enc[i + 1] = '\0';
    fPtr = fopen(datafile, "w");
    fprintf(fPtr, "%s", dec);
    fclose(fPtr);
    printf("\nDecrypted message: %s\n", dec);
}

int main()
{
    int ch;
    char line[RSIZ][LSIZ];
    int i = 0, tot = 0;

    for (;;)
    {
        printf("Enter :\n1 to Encrypt\n2 to Decrypt\n3 to Exit\n");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
        {
            printf("Enter the filename:\n");
            scanf("%s", datafile);

            // Encryption
            fPtr = fopen(datafile, "r");

            while (fgets(line[i], LSIZ, fPtr))
            {
                line[i][strlen(line[i])] = '\0';
                i++;
            }
            tot = i;

            printf("\nThe content of the file %s is:\n", datafile);
            for (i = 0; i <= tot; ++i)
            {
                printf(" %s", line[i]);
            }
            printf("\n");
            caesarenc(*line);
            fclose(fPtr);
            break;
        }

        case 2:
        {
            // Decryption
            fPtr = fopen(datafile, "r");

            fflush(stdin);
            while (fgets(encc, sizeof(encc), fPtr) != NULL);
            caesar_de(encc);
            fclose(fPtr);
            break;
        }

        case 3:
        {
            exit(0);
            break;
        }
        }
    }

    return 0;
}
