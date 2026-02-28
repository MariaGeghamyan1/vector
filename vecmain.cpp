#include <iostream>
#include "vector.cpp"

int main() {
    // ----------------------------
    // 1. Constructors
    // ----------------------------
    MyVector v1;              // default
    MyVector v2(5);           // size constructor
    MyVector v3(5, 10);       // size + value
    MyVector v4(v3);          // copy constructor
    MyVector v5{1, 2, 3, 4};  // initializer list

    std::cout << "v3: ";
    for (size_t i = 0; i < v3.getSize(); ++i) std::cout << v3[i] << " ";
    std::cout << "\nv5: ";
    for (size_t i = 0; i < v5.getSize(); ++i) std::cout << v5[i] << " ";
    std::cout << "\n\n";

    // ----------------------------
    // 2. Copy Assignment
    // ----------------------------
    v1 = v3;
    std::cout << "v1 after copy assignment from v3: ";
    for (size_t i = 0; i < v1.getSize(); ++i) std::cout << v1[i] << " ";
    std::cout << "\n\n";

    // ----------------------------
    // 3. Move Constructor
    // ----------------------------
    MyVector v6(std::move(v5));
    std::cout << "v6 (moved from v5): ";
    for (size_t i = 0; i < v6.getSize(); ++i) std::cout << v6[i] << " ";
    std::cout << "\nv5 size after move: " << v5.getSize() << "\n\n";

    // ----------------------------
    // 4. Move Assignment
    // ----------------------------
    MyVector v7;
    v7 = std::move(v4);
    std::cout << "v7 (moved from v4): ";
    for (size_t i = 0; i < v7.getSize(); ++i) std::cout << v7[i] << " ";
    std::cout << "\nv4 size after move: " << v4.getSize() << "\n\n";

    // ----------------------------
    // 5. push_back & pop_back
    // ----------------------------
    v1.push_back(42);
    v1.push_back(99);
    std::cout << "v1 after push_back: ";
    for (size_t i = 0; i < v1.getSize(); ++i) std::cout << v1[i] << " ";
    std::cout << "\n";

    v1.pop_back();
    std::cout << "v1 after pop_back: ";
    for (size_t i = 0; i < v1.getSize(); ++i) std::cout << v1[i] << " ";
    std::cout << "\n\n";

    // ----------------------------
    // 6. resize
    // ----------------------------
    v1.resize(5, 7);
    std::cout << "v1 after resize(5,7): ";
    for (size_t i = 0; i < v1.getSize(); ++i) std::cout << v1[i] << " ";
    std::cout << "\n\n";

    // ----------------------------
    // 7. insert
    // ----------------------------
    v1.insert(1, 99);            // single
    v1.insert(2, 3, 8);          // multiple
    v1.insert(0, {5,6,7});       // initializer list
    std::cout << "v1 after inserts: ";
    for (size_t i = 0; i < v1.getSize(); ++i) std::cout << v1[i] << " ";
    std::cout << "\n\n";

    // ----------------------------
    // 8. erase
    // ----------------------------
    v1.erase(0);                  // single
    v1.erase(1,3);                // range
    std::cout << "v1 after erases: ";
    for (size_t i = 0; i < v1.getSize(); ++i) std::cout << v1[i] << " ";
    std::cout << "\n\n";

    // ----------------------------
    // 9. clear
    // ----------------------------
    v1.clear();
    std::cout << "v1 size after clear: " << v1.getSize() << "\n\n";

    // ----------------------------
    // 10. swap
    // ----------------------------
    MyVector a{1,2,3};
    MyVector b{9,8,7,6};
    a.swap(b);
    std::cout << "a after swap: ";
    for (size_t i = 0; i < a.getSize(); ++i) std::cout << a[i] << " ";
    std::cout << "\nb after swap: ";
    for (size_t i = 0; i < b.getSize(); ++i) std::cout << b[i] << " ";
    std::cout << "\n";

    return 0;
}
