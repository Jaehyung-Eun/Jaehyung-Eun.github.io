#include <iostream>

class Counter
{
    int count{0};
public:
    // 연속적으로 사용하기 위해 자기 자신을 반환함
    // 하지만 값으로 반환하는 경우 임시 객체를 반환함
    // 임시객체가 증가한 후 파괴되고 원래 객체에 접근하면 값이 바뀌지 않음
    // 이런 문제를 해결하려면 call by reference를 사용해야 함
    // Counter increment()
    Counter &increment()
    {
        ++count;
        
        return *this;
    }
    int get() const { return count; }
};

int main()
{
    Counter c;
    c.increment().increment().increment();
    std::cout << c.get() << std::endl;
    return 0;
}