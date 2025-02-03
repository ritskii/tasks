#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "List.hpp"

int main() {
    char **List = NULL;
    stringListInit(&List);



    printList(List);

    stringListDestroy(&List);
    return 0;
}