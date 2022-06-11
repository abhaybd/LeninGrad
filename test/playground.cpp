#include <type_traits>
#include <iostream>
#include <complex>

int main() {
    std::cout << "double: " << std::is_floating_point<double>::value;
    std::cout << "complex: " << std::is_floating_point<std::complex<double>>::value;
}