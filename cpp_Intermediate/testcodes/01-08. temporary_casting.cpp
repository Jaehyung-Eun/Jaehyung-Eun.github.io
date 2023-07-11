// temporary와 캐스팅

#include <iostream>

struct Base
{
    // C++11부터 구조체에서 초기화 가능
    int value = 10;
    Base() = default;
    Base(const Base &b) : value(b.value)
    {
        std::cout << "Base copy" << std::endl;
    }
};

struct Derived: public Base
{
    // 기반 클래스와 동일한 변수를 생성하는 것이 가능함
    // 이때 기존 변수를 덮어 쓰는 것이 아니라, 동일한 이름의 변수가 두 개 존재하게 됨
    int value = 20;
};

int main()
{
    Derived d;
    std::cout << d.value << std::endl; // 자신의 value인 20을 출력함
    // static cast를 이용하면 base 클래스의 값에 접근할 수 있음
    // d를 Base처럼 생각하고 value에 접근하므로 10을 출력함
    std::cout << static_cast<Base &>(d).value << std::endl;

    // 만일 참조가 아니라 값으로 캐스팅하면 Base타입의 임시객체를 생성함
    // Base 타임의 temporary를 만들고 그 temporary의 value에 접근하게 됨
    // 따라서 d와 달리 value를 하나만 가짐
    std::cout << static_cast<Base>(d).value << std::endl;

    // 참조 casting은 원본을 반환하므로 대입할 수 있음
    static_cast<Base &>(d).value = 100;
    // 값 casting은 임시 객체를 반환하며, 임시 객체는 rvalue이므로 값을 대입할 수 없음
    // static_cast<Base>(d).value = 100;
    return 0;
}