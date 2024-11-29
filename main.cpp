#include "lib/OOP1.hpp"


int main() {
    BitArray d(32, 0b01010101010101010101010101010101);
    std::cout << d.to_string() << "\n";
    return 0;
}