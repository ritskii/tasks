#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "List.hpp"

void printList(char** List) {
    int Size = stringListSize(List);

    for(int I = 0; I < Size; I++) {
        std::cout << List[I] << std::endl;
    }
}

int main() {
    char **List = NULL;
    stringListInit(&List);

    stringListAdd(&List, "string2");
    stringListAdd(&List, "string2");
    stringListAdd(&List, "string3");
    stringListAdd(&List, "string3");
    stringListAdd(&List, "string3");

    stringListReplaceInStrings(List, "string", "str");

    printList(List);

    stringListDestroy(&List);
    return 0;
}