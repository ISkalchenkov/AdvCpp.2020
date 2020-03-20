//
// Created by antarctica on 20.03.2020.
//

#include <unistd.h>
#include <cstdio>

int main()
{
    char buffer[256];
    while (!feof(stdin))
    {
        size_t bytes = fread(buffer, 1, sizeof(buffer), stdin);
        fwrite(buffer, 1, bytes, stdout);
    }

    return 0;
}