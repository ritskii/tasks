#ifndef ANYTYPE_HPP
#define ANYTYPE_HPP

#include <iostream>
#include <typeindex>
#include <stdexcept>

struct AnyType {
    void* Value;
    std::type_index Type;

    enum TypeID { VOID, INT, DOUBLE, CHAR, BOOL };

    TypeID getTypeID() const;

    AnyType();

    template<typename T>
    AnyType(T Input) : Type(typeid(T)) {
        Value = new T(Input);
    }

    AnyType(const AnyType& Oth);
    AnyType(AnyType&& Oth);
    AnyType& operator=(const AnyType& Oth);
    AnyType& operator=(AnyType&& Oth);

    void swap(AnyType& Oth);
    void print();
    void destroy();

    int toInt();
    double toDouble();
    char toChar();
    bool toBool();

    ~AnyType();
};

#endif // ANYTYPE_HPP
