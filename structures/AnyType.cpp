#include "AnyType.hpp"

AnyType::TypeID AnyType::getTypeID() const {
    if (Type == typeid(void)) return VOID;
    if (Type == typeid(int)) return INT;
    if (Type == typeid(double)) return DOUBLE;
    if (Type == typeid(char)) return CHAR;
    if (Type == typeid(bool)) return BOOL;
}

AnyType::AnyType(int Input) : Type(typeid(int)) {
    Value = new int(Input);
}

AnyType::AnyType(double Input) : Type(typeid(double)) {
    Value = new double(Input);
}

AnyType::AnyType(char Input) : Type(typeid(char)) {
    Value = new char(Input);
}

AnyType::AnyType(bool Input) : Type(typeid(bool)) {
    Value = new bool(Input);
}

AnyType::AnyType(AnyType&& Oth) : Type(Oth.Type) {
    switch (Oth.getTypeID()) {
        case INT:
            Value = new int(*(static_cast<int*>(Oth.Value)));
        break;
        case DOUBLE:
            Value = new double(*(static_cast<double*>(Oth.Value)));
        break;
        case CHAR:
            Value = new char(*(static_cast<char*>(Oth.Value)));
        break;
        case BOOL:
            Value = new bool(*(static_cast<bool*>(Oth.Value)));
        break;
    }
    Oth.destroy();
}

AnyType::AnyType(const AnyType& Oth) : Type(Oth.Type) {
    switch (Oth.getTypeID()) {
        case INT:
            Value = new int(*(static_cast<int*>(Oth.Value)));
            break;
        case DOUBLE:
            Value = new double(*(static_cast<double*>(Oth.Value)));
            break;
        case CHAR:
            Value = new char(*(static_cast<char*>(Oth.Value)));
            break;
        case BOOL:
            Value = new bool(*(static_cast<bool*>(Oth.Value)));
            break;
    }
}

AnyType& AnyType::operator=(const AnyType& Oth) {
    if (this != &Oth) {
        destroy();
        Type = Oth.Type;
        switch (Oth.getTypeID()) {
            case INT:
                Value = new int(*(static_cast<int*>(Oth.Value)));
                break;
            case DOUBLE:
                Value = new double(*(static_cast<double*>(Oth.Value)));
                break;
            case CHAR:
                Value = new char(*(static_cast<char*>(Oth.Value)));
                break;
            case BOOL:
                Value = new bool(*(static_cast<bool*>(Oth.Value)));
                break;
        }
    }
    return *this;
}

AnyType& AnyType::operator=(AnyType&& Oth) {
    if (this != &Oth) {
        destroy();
        Type = Oth.Type;
        Oth.Type = typeid(void);
        std::swap(Value, Oth.Value);
    }
    return *this;
}

void AnyType::swap(AnyType& Oth) {
    std::swap(Value, Oth.Value);
    std::swap(Type, Oth.Type);
}

void AnyType::destroy() {
    switch (getTypeID()) {
        case INT:
            delete static_cast<int*>(Value);
            break;
        case DOUBLE:
            delete static_cast<double*>(Value);
            break;
        case CHAR:
            delete static_cast<char*>(Value);
            break;
        case BOOL:
            delete static_cast<bool*>(Value);
            break;
        default:
            break;
    }
    Value = nullptr;
    Type = typeid(void);
}

int AnyType::toInt() {
    if (Type != typeid(int)) throw std::bad_cast();
    return *(static_cast<int*>(Value));
}

double AnyType::toDouble() {
    if (Type != typeid(double)) throw std::bad_cast();
    return *(static_cast<double*>(Value));
}

char AnyType::toChar() {
    if (Type != typeid(char)) throw std::bad_cast();
    return *(static_cast<char*>(Value));
}

bool AnyType::toBool() {
    if (Type != typeid(bool)) throw std::bad_cast();
    return *(static_cast<bool*>(Value));
}

AnyType::~AnyType() {
    destroy();
}
