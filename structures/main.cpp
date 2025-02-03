#include "AnyType.hpp"

int main() {
    AnyType A(1);
    AnyType B(1.5);
    AnyType C(false);

    A = std::move(C);

    A.print();
    B.print();
    C.print();

    return 0;
}
