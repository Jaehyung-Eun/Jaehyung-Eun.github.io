# qsort

* category: function
* library: cstdlib
* prototype:

```c
void qsort (void* base, size_t num, size_t size, int (*compar)(const void*,const void*));
```

## 배열의 요소를 정렬합니다

`base`가 가리키는 배열의 `num` 개 요소를 `compar` 함수를 사용하여 순서를 결정하여 정렬합니다.

이 함수에서 사용되는 정렬 알고리즘은 지정된 `compar` 함수를 인수로 사용하여 요소 쌍을 비교합니다.

이 함수는 값을 반환하지 않지만, `compar`에 의해 정의된 대로 배열의 내용을 수정하여 요소의 순서를 변경합니다.

동등한 요소의 순서는 정의되어 있지 않습니다.

## 파라미터

### base

정렬할 배열의 첫 번째 객체를 가리키는 포인터로, `void*`로 변환됩니다.

### num

`base`가 가리키는 배열의 요소 개수입니다.

`size_t`는 unsigned integral 타입입니다.

### size

배열의 각 요소의 크기(바이트 단위)입니다.

`size_t`는 unsigned integral 타입입니다.

### compar

두 요소를 비교하는 함수를 가리키는 포인터입니다.

이 함수는 `qsort`에 의해 반복적으로 호출되어 두 요소를 비교합니다.

다음과 같은 프로토타입을 따라야 합니다:

```c
int compar (const void* p1, const void* p2);
```

두 개의 포인터를 인수로 받습니다 (둘 다 `const void*`로 변환됩니다).

이 함수는 요소의 순서를 정의하기 위해 (안정적이고 추이성을 가지도록) 반환합니다:

|반환 값|의미|
|---|---|
|<0 |p1이 가리키는 요소는 p2가 가리키는 요소보다 앞에 위치합니다.|
|0|p1이 가리키는 요소는 p2가 가리키는 요소와 동등합니다.|
|>0|p1이 가리키는 요소는 p2가 가리키는 요소보다 뒤에 위치합니다.|

일반적인 관계 연산자를 사용하여 비교할 수 있는 유형에 대해서는 일반적인 `compar` 함수는 다음과 같을 수 있습니다:

```c
int compareMyType (const void * a, const void * b)
{
    if ( *(MyType*)a <  *(MyType*)b ) return -1;
    if ( *(MyType*)a == *(MyType*)b ) return 0;
    if ( *(MyType*)a >  *(MyType*)b ) return 1;
}
```

## 반환 값

없음

## 사용 예

```c
/* qsort example */
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* qsort */

int values[] = { 40, 10, 100, 90, 20, 25 };

int compare (const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );
}

int main ()
{
    int n;
    qsort (values, 6, sizeof(int), compare);
    for (n=0; n<6; n++)
        printf ("%d ",values[n]);
    return 0;
}
```

### 출력 값

```terminal
10 20 25 40 90 100
```

## 복잡도

구체적으로 언급되지 않았지만, 대체로 퀵소트는 평균적으로 $nlog_2n$번 정도 `compar` 함수를 호출하여 $n$에 대해 선형로그 시간 복잡도를 갖습니다.

## 데이터 경쟁(Data races)

이 함수는 `base`가 가리키는 배열의 `num` 개 요소에 접근하거나 수정합니다.

## 예외 (C++)

`compar`가 예외를 던지지 않는다면, 이 함수는 예외를 던지지 않습니다 (예외 없는 보장).

만약 `base`가 적어도 `num*size` 바이트 크기의 배열을 가리키지 않거나, `compar`가 위에서 설명한 대로 동작하지 않는 경우, 이는 정의되지 않은 동작을 일으킵니다.
