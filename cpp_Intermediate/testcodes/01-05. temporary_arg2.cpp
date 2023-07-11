// temporary와 문자열 함수 인자

#include <string>
#include <string_view>

// 문자열의 복사본을 힙에 생성하고 string 생성자를 이용해 임시객체를 만든다.
// 따라서 상수 메모리와 별도로 힙 메모리를 추가로 사용한다.
// 단 짧은 문자열의 경우 SSO 기술을 사용한다.
void foo(const std::string& s){}

// string_view는 문자열의 주소와 길이로 구성되어 있다.
// string_view는 문자열의 복사본을 생성하지 않고 상수 메모리에 존재하는 문자열을 가리킨다.
// 따라서 읽기 전용 문자열을 함수 인자로 받는 경우 "const std::string&" 보다 "std::string_view"가 좋다.
void goo (std::string_view s){}

int main()
{
    foo("Practice make perfect");
    goo("Practice make perfect");
}
