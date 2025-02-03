#ifndef LIST_HPP
#define LIST_HPP

int stringListSize(char** List) {
    int Result = 0;

    while (List[Result] != NULL) {
        Result++;
    }

    return Result;
}

int stringListCapacity(char** List) {
    int Result = 0;

    while (List[Result] != NULL) Result++;
    while(List[Result] == NULL) Result++;

    return Result;
}

void stringListInit(char*** List) {
    *List = (char**) malloc(4 * sizeof(char*));
    for(int I = 0; I < 4; I++) {
        (*List)[I] = NULL;
    }
}

void stringListDestroy(char*** List) {
    int Size = stringListSize(*List);

    for(int I = 0; I < Size; I++) {
        free((*List)[I]);
    }

    free(*List);
    *List = NULL;
}

void stringListAdd(char ***List, char *Str) {
    int Capacity = stringListCapacity(*List);
    int Size = stringListSize(*List);

    (*List)[Size] = Str;

    if (Size == Capacity - 1) {
        *List = (char **) realloc(*List, (2 * Capacity) * sizeof(char *));
        for (int I = Capacity; I < 2 * Capacity; I++) {
            (*List)[I] = NULL;
        }
    }

    (*List)[Size] = strdup(Str);
    (*List)[Size + 1] = NULL;
}

int stringListIndexOf(char** List, char* Str) {
    int Size = stringListSize(List);

    for(int I = 0; I < Size; I++) {
        if(List[I] == NULL) continue;

        if(strstr(List[I], Str)) return I;
    }
    return -1;
}

void stringListRemove(char** List, char* Str) {
    int Size = stringListSize(List);

    int Shift = 0;

    for (int I = 0; I < Size; I++) {
        if (List[I] == NULL) continue;

        if (strcmp(List[I], Str) != 0) {
            List[Shift] = List[I];
            Shift++;
        }
    }

    for (int I = Shift; I < Size; I++) {
        List[I] = NULL;
    }
}

void stringListRemoveDuplicates(char** List) {
    int Size = stringListSize(List);

    for (int I = 0; I < Size; I++) {
        if (List[I] == NULL) continue;

        for (int J = I + 1; J < Size; J++) {
            if (List[J] != NULL && strcmp(List[I], List[J]) == 0) {
                stringListRemove(List, List[J]);
                J--;
            }
        }
    }
}

void stringListReplaceInStrings(char** List, char* Before, char* After) {
    int Size = stringListSize(List);

    if((Before || After) == NULL) return;

    for (int I = 0; I < Size; I++) {
        if (List[I] == NULL) continue;

        char* Sub = strstr(List[I], Before);
        if(Sub != NULL) {
            int Index = Sub - List[I];

            char* NewStr = (char*)malloc(strlen(List[I]) - strlen(Before) + strlen(After) + 1);
            if (NewStr == NULL) {
                continue;
            }
            strncpy(NewStr, List[I], Index);
            strcpy(NewStr + Index, After);
            strcpy(NewStr + Index + strlen(After), List[I] + Index + strlen(Before));

            List[I] = NewStr;
        }
    }
}

int comparator(const void* A, const void* B) {
    char* Fir = *(char**)A;
    char* Sec = *(char**)B;
    if (Fir == NULL && Sec == NULL) return 0;
    return (Fir == NULL ? 1 : (Sec == NULL ? -1 : *Fir - *Sec));
}

void stringListSort(char** List) {
    int Size = stringListSize(List);
    qsort(List, Size, sizeof(char*), comparator);
}

void printList(char** List) {
    int Size = stringListSize(List);

    for(int I = 0; I < Size; I++) {
        std::cout << List[I] << std::endl;
    }
}

#endif //LIST_HPP
