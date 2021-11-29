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

const auto del_fn(Data<int>* p_data) {
    std::cout << "calling custom deleter function" << std::endl;
    delete p_data;
}

int main() {
    const auto del = [](Data<int>* p_data) {
        std::cout << "calling custom deleter lambda" << std::endl;
        delete p_data;
    };

    std::cout << "size of custom deleter lambda 'del': " << sizeof(del) << std::endl;
    std::cout << "size of custom deleter function pointer 'del_fn': " << sizeof(&del_fn) << std::endl;

    const auto data = std::unique_ptr<Data<int>, decltype(del)>(new Data<int>(10), del);
    const auto data_fp = std::unique_ptr<Data<int>, void(*)(Data<int> *)>(new Data<int>(20), &del_fn);

    std::cout << "size of unique_ptr with lambda custom-deleter: " << sizeof(data) << std::endl;
    std::cout << "size of unique_ptr with function-ptr custom-deleter: " << sizeof(data_fp) << std::endl;
}
