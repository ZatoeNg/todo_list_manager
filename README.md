# CRTP 特性:是一种通过模板继承实现的静态多态技术，其核心思想是基类将派生类作为模板参数，从而在编译时实现多态行为.
```cpp
template <typename Derived>
class Base {
public:
    void interface() {
        // 将 this 转换为派生类指针，调用派生类方法
        static_cast<Derived*>(this)->implementation();
    }
};

class Derived : public Base<Derived> {
public:
    void implementation() {
        std::cout << "Derived::implementation()" << std::endl;
    }
};

int main() {
    Derived d;
    d.interface(); // 输出：Derived::implementation()
}
```
# RAII:资源获取即初始化.
