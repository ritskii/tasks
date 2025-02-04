#include "AnyType.cpp"
#include "gtest/gtest.h"

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
    AnyType I = 2.5;
    AnyType C = 'c';
    AnyType B = true;
    AnyType TC = std::move(C);
    EXPECT_EQ(TC.Type, typeid(char));
    AnyType TD = std::move(I);
    EXPECT_EQ(TD.Type, typeid(double));
    AnyType TB = std::move(B);
    EXPECT_EQ(TB.Type, typeid(bool));
}

TEST(Constructor, Copy) {
    AnyType D = 2.5;
    AnyType C = 'c';
    AnyType B = true;
    AnyType I = 2;
    AnyType A = I;

    EXPECT_EQ(A.toInt(), I.toInt());
    EXPECT_NE(A.Value, I.Value);
    AnyType TD = D;
    EXPECT_EQ(TD.Type, typeid(double));
    AnyType TB = B;
    EXPECT_EQ(TB.Type, typeid(bool));
    AnyType TC = C;
    EXPECT_EQ(TC.Type, typeid(char));
}

TEST(Operator, Copy) {
    AnyType I = 2;
    AnyType D = 3.5;
    I = D;
    AnyType B;
    B = true;

    EXPECT_NE(I.Value, D.Value);
    EXPECT_EQ(I.toDouble(), 3.5);
    EXPECT_EQ(I.Type, typeid(double));
    EXPECT_EQ(B.Type, typeid(bool));
}

TEST(Operator, CopyTypes) {
    AnyType I = 2;
    AnyType D = 2.5;
    AnyType B = true;
    AnyType C = 'c';
    I = D;

    EXPECT_EQ(I.Type, typeid(double));
    I = B;
    EXPECT_EQ(I.Type, typeid(bool));
    I = C;
    EXPECT_EQ(I.Type, typeid(char));
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

TEST(Operator, MoveTypes) {
    AnyType C = 'c';
    AnyType D = 2.5;
    AnyType I = 3;
    AnyType B = true;
    AnyType V;

    D = C;
    EXPECT_EQ(D.Type, typeid(char));
    D = I;
    EXPECT_EQ(D.Type, typeid(int));
    D = B;
    EXPECT_EQ(D.Type, typeid(bool));
    D = V;
    EXPECT_EQ(D.Type, typeid(void));
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

TEST(Method, Double) {
    AnyType D = 1;

    EXPECT_THROW({
        D.toDouble();
    }, std::bad_cast);
}

TEST(Method, Bool) {
    AnyType B = true;

    EXPECT_EQ(B.toBool(), true);
}

TEST(Method, Void) {
    AnyType V = 2;
    AnyType I = std::move(V);

    EXPECT_EQ(V.getTypeID(), V.TypeID::VOID);
}