#include <iostream>

class Point {    
public:
    int x, y;
    Point(int x, int y): x(x), y(y) {}
    void set(int a, int b) { 
        x = a;
        y = b;
    }
};

int main()
{
    Point pt(1, 2);
    pt.x = 10;
    // temporary는 rvalue이다. 즉, 등호의 왼쪽에 놓을 수 없다.
    // Point(1, 2).x = 10; 
    // 멤버 함수를 호출할 수 있으므로 상수는아니다.
    Point(1, 2).set(10, 20);

    Point* p1 = &pt;
    // temporary는 라인이 끝나고 파괴되므로 주소 연산자로 주소를 구할 수 없다.
    // 단, 객체 안에서 this 연산자를 이용해 주소를 사용할 수는 있다.
    // Point* p2 = &Point(1, 2);

    Point &r1 = pt;
    // temporary는 라인이 끝나고 파괴되므로 참조 연산자로 가리킬 수도 없다.
    // Point &r2 = Point(1, 2);
    // temporary는 상수 참조로는 가리킬 수 있다.
    // 이 경우 temporary에 r3라는 이름을 붙인 것이므로 수명이 r3에 의해 결정된다.
    const Point &r3 = Point(1, 2);

    // C++11부터 상수성 없이 temporary를 가리키는 문법이 등장함
    // 이를 rvalue reference라 부름
    Point &&r = Point(1, 2);

    return 0;
}