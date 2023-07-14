// temporary와 함수 반환값
#include <iostream>

class Point
{
public:
    int x, y;

    Point(int x, int y) : x(x), y(y) { std::cout << "Point(int, int)" << std::endl; }
    ~Point() { std::cout << "~Point()" << std::endl; }
    void print() { std::cout << "x value: " << x << std::endl; }
};

//------------------------
// call by value이므로 복사본을 생성함
void f1(Point p1){}
// call by reference이므로 복사본을 생성하지 않음
void f2(Point& p2){}

// 전역 객체를 만들고 전역객체를 반환하는 함수를 만듬
Point pt(1,2);
// return by value이므로 복사본을 반환함
Point f3() { return pt; }
// return by reference이므로 객체를 그대로 반환함
// 단, local variable은 return by reference 할 수 없음
Point &f4() { return pt; }

int main(){
    //Point pt(1, 2);
    //f1(pt);
    //f2(pt);

    // 전역 객체를 반환하는 함수를 호출함
    // 반환된 복사본은 임시객체(temporary)이므로 rvaule가 될 수 없음
    // f3().x = 10;
    // 임시객체가 아니므로 rvalue가 될 수 있음
    f4().print();    
    f4().x = 10;
    f4().print();
    return 0;
}