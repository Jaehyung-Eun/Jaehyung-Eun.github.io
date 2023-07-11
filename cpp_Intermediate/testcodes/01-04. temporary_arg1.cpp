// temporary와 함수 인자

#include <iostream>

class Point
{
    int x, y;
public:
    Point(int x, int y) : x(x), y(y) { std::cout << "Point(int, int)" << std::endl; }
    ~Point() { std::cout << "~Point()" << std::endl; }
};

void foo(const Point &pt) { std::cout << "foo" << std::endl; }

int main(){
    // pt를 foo 호출을 위해서만 사용한다고 가정해보자.
    // pt는 foo 이후로는 사용할 필요가 없지만 로컬변수이므로 함수가 종료될 때까지 살아남는다.
    // Point pt(1, 2);
    // foo(pt);

    // 함수 인자로만 사용하려면 임시객체를 만들어 사용하는 것이 좋음
    // 이를 위해 foo의 인자는 const Point & 타입이어야 함
    // 실행해보면 소멸자가 호출되는 시점이 달라지는 것을 확인할 수 있음
    foo(Point(1, 2)); 
    // C++11부터는 중괄호를 사용할 수도 있음 foo(Point{1,2})
    // 또는 foo({1, 2})로 표현할 수도 있음

    std::cout << "-----" << std::endl;
    return 0;
}