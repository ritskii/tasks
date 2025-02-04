#include "gtest/gtest.h"
#include "List.hpp"

TEST(StringList, SizeDefault) {
    char **List = NULL;
    stringListInit(&List);

    stringListAdd(&List, "string1");
    stringListAdd(&List, "string2");

    EXPECT_EQ(stringListSize(List), 2);
    stringListDestroy(&List);
}

TEST(StringList, SizeRealloc) {
    char **List = NULL;
    stringListInit(&List);
    stringListAdd(&List, "string1");
    stringListAdd(&List, "string2");
    stringListAdd(&List, "string1");
    stringListAdd(&List, "string2");
    stringListAdd(&List, "string1");
    stringListAdd(&List, "string2");
    stringListAdd(&List, "string1");
    stringListAdd(&List, "string2");
    stringListAdd(&List, "string1");
    stringListAdd(&List, "string2");
    stringListAdd(&List, "string1");
    stringListAdd(&List, "string2");
    EXPECT_STREQ(List[11], "string2");
    stringListDestroy(&List);
}

TEST(StringList, SizeEmpty) {
    char **List = NULL;
    stringListInit(&List);

    EXPECT_EQ(stringListSize(List), 0);
    stringListDestroy(&List);
}

TEST(StringList, IndexDefault) {
    char **List = NULL;
    stringListInit(&List);

    stringListAdd(&List, "string1");
    stringListAdd(&List, "string2");
    stringListAdd(&List, "string3");

    EXPECT_EQ(stringListIndexOf(List, "string3"), 2);
    stringListDestroy(&List);
}

TEST(StringList, IndexEmpty) {
    char **List = NULL;
    stringListInit(&List);

    stringListAdd(&List, "string1");
    stringListAdd(&List, "string2");
    stringListAdd(&List, "string3");

    EXPECT_EQ(stringListIndexOf(List, " "), -1);
    stringListDestroy(&List);
}

TEST(StringList, RemoveEmpty) {
    char **List = NULL;
    stringListInit(&List);

    stringListAdd(&List, "string1");
    stringListAdd(&List, "string2");
    stringListRemove(List, "");
    EXPECT_EQ(stringListSize(List), 2);
    stringListDestroy(&List);
}

TEST(StringList, RemoveDefault) {
    char **List = NULL;
    stringListInit(&List);

    stringListAdd(&List, "string1");
    stringListAdd(&List, "string2");
    stringListRemove(List, "string1");
    EXPECT_EQ(stringListSize(List), 1);
    EXPECT_STREQ(List[0], "string2");
    stringListDestroy(&List);
}

TEST(StringList, DuplicateEmpty) {
    char **List = NULL;
    stringListInit(&List);

    stringListAdd(&List, "string1");
    stringListAdd(&List, "string2");
    stringListAdd(&List, "string3");

    stringListRemoveDuplicates(List);
    EXPECT_EQ(stringListSize(List), 3);

    stringListDestroy(&List);
}

TEST(StringList, DuplicateDefault) {
    char **List = NULL;
    stringListInit(&List);

    stringListAdd(&List, "string1");
    stringListAdd(&List, "string2");
    stringListAdd(&List, "string2");

    stringListRemoveDuplicates(List);
    EXPECT_EQ(stringListSize(List), 1);

    stringListDestroy(&List);
}

TEST(StringList, DuplicateClear) {
    char **List = NULL;
    stringListInit(&List);

    stringListAdd(&List, "string2");
    stringListAdd(&List, "string2");
    stringListAdd(&List, "string2");

    stringListRemoveDuplicates(List);
    EXPECT_EQ(stringListSize(List), 0);

    stringListDestroy(&List);
}

TEST(StringList, DuplicateRealloc) {
    char **List = NULL;
    stringListInit(&List);

    stringListAdd(&List, "string2");
    stringListAdd(&List, "string2");
    stringListAdd(&List, "string3");
    stringListAdd(&List, "string2");


    stringListRemoveDuplicates(List);
    EXPECT_EQ(stringListSize(List), 1);
    EXPECT_STREQ(List[0], "string3");

    stringListDestroy(&List);
}

TEST(StringList, DuplicateDouble) {
    char **List = NULL;
    stringListInit(&List);

    stringListAdd(&List, "string2");
    stringListAdd(&List, "string2");
    stringListAdd(&List, "string3");
    stringListAdd(&List, "string3");

    stringListRemoveDuplicates(List);
    EXPECT_EQ(stringListSize(List), 0);

    stringListDestroy(&List);
}

TEST(StringList, ReplaceIn) {
    char **List = NULL;
    stringListInit(&List);

    stringListAdd(&List, "string2");
    stringListAdd(&List, "string2");
    stringListAdd(&List, "string3");

    stringListReplaceInStrings(List, "string", "s");

    EXPECT_STREQ(List[0], "s2");

    stringListDestroy(&List);
}

TEST(StringList, Sort) {
    char **List = NULL;
    stringListInit(&List);

    stringListAdd(&List, "3");
    stringListAdd(&List, "2");
    stringListAdd(&List, "1");

    stringListSort(List);

    EXPECT_STREQ(List[0], "1");
    EXPECT_STREQ(List[1], "2");
    EXPECT_STREQ(List[2], "3");

    stringListDestroy(&List);
}