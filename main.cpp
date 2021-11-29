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

    std::cout << "size of custom deleter 'del': " << sizeof(del) << std::endl;

    auto data = std::unique_ptr<Data<int>, decltype(del)>(new Data<int>(10), del);
}