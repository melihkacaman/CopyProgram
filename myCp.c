#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 4096

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        printf("Invalid number of parameters.");
        return 0;
    }

    FILE *source, *dest;
    source = fopen(argv[1], "rb");
    if (source == NULL)
    {
        printf("Unable to open file, make sure that file exists.\n");
        return 0;
    }
    dest = fopen(argv[2], "wb");
    if (dest == NULL)
    {
        printf("Unable to create file, make sure that you have permission to write.\n");
        return 0;
    }

    char *buffer = (char *)malloc(sizeof(char) * BLOCK_SIZE);
    if (buffer == NULL)
    {
        printf("Unable to allocate buffer memory for copying... \n");
        return 0;
    }

    fseek(source, 0l, SEEK_END);
    long rem_size = ftell(source);
    fseek(source, 0l, SEEK_SET);

    while (rem_size > 0)
    {
        long read_bytes = 0;
        if (rem_size < BLOCK_SIZE)
        {
            read_bytes = fread((void *)buffer, sizeof(char), rem_size, source);
        }
        else
        {
            read_bytes = fread((void *)buffer, sizeof(char), BLOCK_SIZE, source);
        }
        fwrite((void *)buffer, sizeof(char), read_bytes, dest);
        rem_size -= read_bytes;
    }

    fclose(source);
    fclose(dest);

    printf("File has been copied successfully...\n");
    return 0;
}
