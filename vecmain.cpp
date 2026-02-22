#include <iostream>
#include "vector.cpp"

int main() {
    MyVector v1;       
    MyVector v2(5);    
    MyVector v3(5, 10);
    MyVector v4(v3);   
    MyVector v5{1, 2, 3, 4};  

    v1 = v3;                  

    std::cout << "v3 elem: ";
    for (size_t i = 0; i < v3.getSize(); ++i)
        std::cout << v3[i] << " ";
    std::cout << std::endl;

    std::cout << "v5 elem: ";
    for (size_t i = 0; i < v5.getSize(); ++i)
        std::cout << v5[i] << " ";
    std::cout << std::endl;

    std::cout << v3.front() << std::endl;
    std::cout << v3.back() << std::endl;
    std::cout << v4.empty() << std::endl;
    v3.reserve(6);
    std::cout << v3.getCapacity() << std::endl;
    v3.shrink_to_fit();
    std::cout << v3.getCapacity() << std::endl;


    return 0;
} 


