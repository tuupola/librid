#include <stdio.h>

#include "rid/version.h"

int
main(void)
{
    printf("Library version: %s\n", rid_version_to_string());

    return 0;
}
