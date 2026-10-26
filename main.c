#include <unistd.h>
#include "mymemory.h"


int main(void)
{
    int *a = mymalloc(sizeof(int));

    if (a == NULL)
    {
        return 1;
    }

    *a = 42;
    
    if (*a != 42)
    {
        return 1;
    }

    write(STDOUT_FILENO, "allocation successful\n", 22);

    return 0;
}