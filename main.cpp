#include <iostream>
#include <memory>

template<typename T>
class Data {
public:
    Data(T v) {
        std::cout << "constructed" << std::endl;
    }

    ~Data() {
        std::cout << "destructor" << std::endl;
    }
};

int main() {
    auto del = [](Data<int>* p_data) {
        std::cout << "calling custom deleter" << std::endl;
        delete p_data;
    };

    auto d = std::unique_ptr<int, decltype(del)>(10, del);
}