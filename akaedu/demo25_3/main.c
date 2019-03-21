#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define strtok_func my_strtok_r

static bool contains(const char* str, char c)
{
    while(*str != '\0')
    {
        if(*str == c)
        {
            return true;
        }
        ++str;
    }
    return false;
}

char* my_strtok_r(char* src, const char* sep, char** lasts) 
{
    if(src == NULL && **lasts == '\0')
    {
        return NULL;
    }

    char* pbegin = src;
    if(pbegin == NULL)
    {
        pbegin = *lasts;
    }

    //跳过前导字符
    while(contains(sep, *pbegin))
    {
        pbegin++;
    }
    *lasts = pbegin;

    for(; **lasts != '\0'; (*lasts)++)
    {
        if(contains(sep, **lasts))
        {
            **lasts = '\0';
            *lasts = *lasts + 1;
            break;
        }
    }
    return pbegin;
}

int main(int argc, char* argv[])
{
    if(argc != 4)
    {
        fprintf(stderr, "Usage: %s string delim subdelim\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int j = 1;
    char* str1 = argv[1];
    char* token = NULL;
    char* saveptr1 = NULL;

    char* subtoken = NULL;
    char* substr = NULL;
    char* subsaveptr = NULL;
    while((token = strtok_func(str1, argv[2], &saveptr1)))
    {
        str1 = NULL;
        printf("%d: %s\n", j++, token);
        while((subtoken = strtok_func(token, argv[3], &subsaveptr)))
        {
            token = NULL;
            printf(" --> %s\n", subtoken);
        }
    }

    return 0;
}