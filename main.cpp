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

auto del_fn(Data<int>* p_data) {
    std::cout << "calling custom deleter function" << std::endl;
    delete p_data;
}

int main() {
    auto del = [](Data<int>* p_data) {
        std::cout << "calling custom deleter lambda" << std::endl;
        delete p_data;
    };

    const std::string astr{ "hey  this is going to be a large string. considering small buffer optimization, we had to do this.   " };
    std::cout << "size of a string: " << sizeof(astr) << std::endl;

    const short shint{ 100 };

    auto del_with_ref_capture = [&](Data<int>* p_data) {
        std::cout << "accessing ref-captures: " << astr << ", short: " << shint << std::endl;
        std::cout << "calling custom deleter lambda" << std::endl;
        delete p_data;
    };

    auto del_with_val_capture = [=](Data<int>* p_data) {
        std::cout << "accessing val-captures: " << astr << ", short: " << shint << std::endl;
        std::cout << "calling custom deleter lambda" << std::endl;
        delete p_data;
    };

    std::cout << "size of custom deleter lambda 'del': " << sizeof(del) << std::endl;
    std::cout << "size of custom deleter lambda with capture 'del_with_ref_capture': " << sizeof(del_with_ref_capture) << std::endl;
    std::cout << "size of custom deleter lambda with capture 'del_with_val_capture': " << sizeof(del_with_val_capture) << std::endl;
    std::cout << "size of custom deleter function pointer 'del_fn': " << sizeof(&del_fn) << std::endl;

    const auto data = std::unique_ptr<Data<int>, decltype(del)>(new Data<int>(10), del);
    const auto data_ref_capturing_lam = std::unique_ptr<Data<int>, decltype(del_with_ref_capture)>(new Data<int>(10), del_with_ref_capture);
    const auto data_val_capturing_lam = std::unique_ptr<Data<int>, decltype(del_with_val_capture)>(new Data<int>(10), del_with_val_capture);
    const auto data_fp = std::unique_ptr<Data<int>, void(*)(Data<int> *)>(new Data<int>(20), &del_fn);

    std::cout << "size of unique_ptr with lambda custom-deleter: " << sizeof(data) << std::endl;
    std::cout << "size of unique_ptr with lambda (ref-capture) custom-deleter: " << sizeof(data_ref_capturing_lam) << std::endl;
    std::cout << "size of unique_ptr with lambda (val-capture) custom-deleter: " << sizeof(data_val_capturing_lam) << std::endl;
    std::cout << "size of unique_ptr with function-ptr custom-deleter: " << sizeof(data_fp) << std::endl;
}
