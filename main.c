#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_LENGTH 255

typedef struct {
    char *str;
    char num;
} lookup;

lookup lookup_table[9] = {
    {"one", 1},
    {"two", 2},
    {"three", 3},
    {"four", 4},
    {"five", 5},
    {"six", 6},
    {"seven", 7},
    {"eight", 8},
    {"nine", 9},
};

int match(char *slice)
{
    for (int i = 0; i < 9; i++)
    {
        int slen1 = strlen(slice);
        int slen2 = strlen(lookup_table[i].str);
        int len = (slen1 < slen2) ? slen1 : slen2;
        int result = strncmp(slice, lookup_table[i].str, len);
        if (result != 0) continue;
        return lookup_table[i].num;
    }

    return -1;
}

void substr(const char* str, char* result, size_t start)
{
    int len = strlen(str) - start;
    strncpy(result, str + start, len);
    result[len] = '\0';
}

int main(int argc, char **argv)
{
    FILE *f = fopen("./stuff.txt", "r");
    char line[BUFFER_LENGTH];
    
    int sum = 0;
    while (fgets(line, BUFFER_LENGTH, f))
    {
        int len = strlen(line);
        int left = -1;
        int right = -1;
        for (int i = 0; i < len; i++)
        {
            if (isdigit(line[i]))
            {
                if (left == -1)
                {
                    left = line[i] - 0x30;
                    right = line[i] - 0x30;
                }
                else
                {
                    right = line[i] - 0x30;
                }
            }
            else
            {
                char test[BUFFER_LENGTH];
                substr(line, test, i);
                int result = match(test);
                if (result != -1)
                {
                    printf("%s", line);
                    printf("Str Match: %s with %d\n", test, result);
                    if (left == -1)
                    {
                        left = result;
                        right = result;
                    }
                    else
                    {
                        right = result;
                    }
                }
            }
        }
        sum += left * 10 + right;
    }

    printf("The sum of the calibration values is: %d\n", sum);
    fclose(f);
    return 0;
}