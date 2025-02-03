#include "gtest/gtest.h"
#include "AnyType.hpp"

TEST(Constructor, Empty) {
    AnyType A;

    EXPECT_EQ(A.Value, nullptr);
}

TEST(Constructor, Default) {
    AnyType I = 2;
    AnyType D = 2.5;
    AnyType C = 'C';

    int Integer = I.toInt();
    double Double = D.toDouble();
    char Character = C.toChar();

    EXPECT_EQ(Integer, 2);
    EXPECT_EQ(Double, 2.5);
    EXPECT_EQ(Character, 'C');
}

TEST(Constructor, Move) {
    AnyType I = 2;
    AnyType A = std::move(I);

    EXPECT_EQ(A.toInt(), 2);
    EXPECT_THROW({
        I.toInt();
    }, std::bad_cast);
}

TEST(Constructor, Copy) {
    AnyType I = 2;
    AnyType A = I;

    EXPECT_EQ(A.toInt(), I.toInt());
    EXPECT_NE(A.Value, I.Value);
}

TEST(Operator, Copy) {
    AnyType I = 2;
    AnyType D = 3.5;
    I = D;

    EXPECT_NE(I.Value, D.Value);
    EXPECT_EQ(I.toDouble(), 3.5);
    EXPECT_EQ(I.Type, typeid(double));
}

TEST(Operator, Move) {
    AnyType D = 2.5;
    AnyType I = 2;
    I = std::move('C');
    D = std::move(I);

    EXPECT_EQ(D.toChar(), 'C');
    EXPECT_EQ(I.Type, typeid(void));
    EXPECT_EQ(D.Type, typeid(char));
}

TEST(Method, Swap) {
    AnyType D = 2.5;
    AnyType I = 2;
    D.swap(I);

    EXPECT_EQ(D.toInt(), 2);
    EXPECT_EQ(I.toDouble(), 2.5);
}

TEST(Method, Int) {
    AnyType D = 2.5;

    EXPECT_THROW({
        D.toInt();
    }, std::bad_cast);
}

TEST(Method, Char) {
    AnyType C = 'A';

    int Character = C.toChar();

    EXPECT_EQ(Character, 65);
}