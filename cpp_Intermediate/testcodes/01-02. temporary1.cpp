#include <iostream>

class Point
{
    int x, y;
public:
    Point(int x, int y) : x(x), y(y)    { std::cout << "Point(int, int)" << std::endl; }
    ~Point() { std::cout << "~Point()" << std::endl; }    
};

int main()
{
    // named object
    Point pt(1, 2); // 로컬변수이므로 생성자 호출, 밑줄, 소멸자 호출이 순서대로 이루어짐

    // unnamed object
    // 이를 temporary object라 부름
    // Point(1, 2); // 만들어지고 줄을 벗어나는 순간 파괴되므로, 생성자 호출, 소멸자 호출, 밑줄이 출력됨    

    std::cout << "-----------" << std::endl;

    return 0;
}