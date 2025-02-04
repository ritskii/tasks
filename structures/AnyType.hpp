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

    AnyType() : Type(typeid(void)) {};
    AnyType(void* Input) = delete;
    AnyType(std::nullptr_t Input) = delete;

    AnyType(int Input);
    AnyType(double Input);
    AnyType(char Input);
    AnyType(bool Input);

    AnyType(const AnyType& Oth);
    AnyType(AnyType&& Oth);
    AnyType& operator=(const AnyType& Oth);
    AnyType& operator=(AnyType&& Oth);

    void swap(AnyType& Oth);
    void destroy();

    int toInt();
    double toDouble();
    char toChar();
    bool toBool();

    ~AnyType();

    void print() {
        switch (getTypeID()) {
            case VOID:
                std::cout << Type.name() << "\n";
            break;
            case INT:
                std::cout << Type.name()  << " " << *(static_cast<int*>(Value)) << std::endl;
            break;
            case DOUBLE:
                std::cout << Type.name() << " " << *(static_cast<double*>(Value)) << std::endl;
            break;
            case CHAR:
                std::cout << Type.name() << " " << *(static_cast<char*>(Value)) << std::endl;
            break;
            case BOOL:
                std::cout << Type.name() << " " << (*(static_cast<bool*>(Value)) ? "true" : "false") << std::endl;
            break;
        }
    }
};

#endif // ANYTYPE_HPP
