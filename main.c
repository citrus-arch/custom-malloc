#include <unistd.h>
#include "mymemory.h"


int main(void)
{
    int *a = mymalloc(sizeof(int));
    int *b = mymalloc(sizeof(int));

    if (a == NULL || b == NULL)
    {
        return 1;
    }

    *a = 42;
    *b = 100;
    
    if (*a != 42 || *b != 100)
    {
        return 1;
    }

    myfree(a);
    myfree(b);

    write(STDOUT_FILENO, "allocation and free successful\n", 31);

    return 0;
}