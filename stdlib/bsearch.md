# bsearch

* category: function
* library: cstdlib
* prototype:

```c
void* bsearch (const void* key, const void* base, size_t num, size_t size, int (*compar)(const void*,const void*));
```

## 배열에서 이진 탐색을 합니다

배열에서 주어진 키(`key`)를 찾아 일치하는 요소에 대한 `void*` 포인터를 반환합니다.

이때 `base`가 가리키는 배열은 `num` 개의 요소로 구성되며, 각 요소의 크기는 `size` 바이트입니다.

검색을 수행하기 위해 함수는 `key`를 첫 번째 인수로 하고 base가 가리키는 배열의 요소를 두 번째 인수로 하여 `compar`을 연속적으로 호출합니다.

이 함수는 비선형 검색 알고리즘(아마도 이진 검색)을 사용하여 최적화될 수 있으므로, `compar`을 사용하여 `key`보다 작은 요소는 동일한 값을 가진 요소보다 앞에 위치하고, 동일한 값을 가진 요소는 큰 값을 가진 요소보다 앞에 위치해야 합니다.

이 요구사항은 `compar`이 사용하는 동일한 기준으로 정렬된 배열(`qsort`로 정렬된 것과 동일한 기준)에 의해 충족됩니다.

## 파라미터

### key

검색에 사용되는 키(`key`)로서 `void`로 형변환된 객체를 가리키는 포인터입니다.

### base

검색이 수행되는 배열의 첫 번째 객체를 가리키는 포인터로서 `void`로 형변환된 객체를 가리킵니다.

### num

`base`가 가리키는 배열의 요소 개수입니다.
`size_t`는 부호 없는 정수형입니다.

### size

배열의 각 요소의 크기(바이트 단위)입니다.
`size_t`는 부호 없는 정수형입니다.

### compar

두 요소를 비교하는 함수를 가리키는 포인터입니다.

이 함수는 `bsearch`에 의해 반복적으로 호출되어 `key`를 `base`의 개별 요소와 비교합니다.

다음과 같은 프로토타입을 따라야 합니다:

```c
int compar (const void* pkey, const void* pelem);
```

두 개의 포인터를 인수로 받습니다.

첫 번째는 항상 `key`이고, 두 번째는 배열의 요소를 가리키는 포인터입니다 (둘 다 `const void*`로 형변환됩니다).

이 함수는 (안정적이고 추이성을 가지도록) 다음을 반환해야 합니다

|반환 값|의미|
|---|---|
|<0 |`pkey`가 가리키는 요소는 `pelem`이 가리키는 요소보다 앞에 위치합니다.|
|0|`pkey`가 가리키는 요소는 `pelem`이 가리키는 요소와 동등합니다.|
|>0|`pkey`가 가리키는 요소는 `pelem`이 가리키는 요소보다 뒤에 위치합니다.|

일반적인 관계 연산자를 사용하여 비교할 수 있는 유형에 대해서는 일반적인 `compar` 함수는 다음과 같을 수 있습니다:

```c
int compareMyType (const void * a, const void * b)
{
    if ( *(MyType*)a <  *(MyType*)b )
        return -1;
    if ( *(MyType*)a == *(MyType*)b )
        return 0;
    if ( *(MyType*)a >  *(MyType*)b )
        return 1;
}
```

## 반환 값

검색 키와 일치하는 배열의 항목을 가리키는 포인터입니다.

일치하는 요소가 하나 이상 있는 경우 (즉, `compar`이 `0`을 반환하는 요소), 이는 그 중 아무 것이나 가리킬 수 있습니다 (첫 번째 요소가 아니어도 됩니다).

키가 발견되지 않은 경우, `null` 포인터가 반환됩니다.

## 사용 예

```c
/* bsearch example */
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* qsort, bsearch, NULL */

int compareints (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

int values[] = { 50, 20, 60, 40, 10, 30 };

int main ()
{
  int * pItem;
  int key = 40;
  qsort (values, 6, sizeof (int), compareints);
  pItem = (int*) bsearch (&key, values, 6, sizeof (int), compareints);
  if (pItem!=NULL)
    printf ("%d is in the array.\n",*pItem);
  else
    printf ("%d is not in the array.\n",key);
  return 0;
}
```

예를 들어, `compareints` 함수는 두 매개변수가 가리키는 값을 `int` 값으로 비교하고, 그들이 같으면 결과로 `0`을 반환하며, `a`가 가리키는 값이 `b`가 가리키는 값보다 크면 양수 결과를, `b`가 가리키는 값이 `a`가 가리키는 값보다 크면 음수 결과를 반환합니다.

메인 함수에서는 `bsearch` 호출 전에 대상 배열이 `qsort`를 사용하여 정렬됩니다. 이후에는 값을 검색하기 위해 `bsearch`가 호출됩니다.

### 출력

```terminal
40 is in the array.
```

`C` 문자열의 경우, `strcmp` 함수를 `bsearch`의 비교 인수로 직접 사용할 수 있습니다.

```c
/* bsearch example with strings */
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* qsort, bsearch, NULL */
#include <string.h>     /* strcmp */

char strvalues[][20] = {"some","example","strings","here"};

int main ()
{
  char * pItem;
  char key[20] = "example";

  /* sort elements in array: */
  qsort (strvalues, 4, 20, (int(*)(const void*,const void*)) strcmp);

  /* search for the key: */
  pItem = (char*) bsearch (key, strvalues, 4, 20, (int(*)(const void*,const void*)) strcmp);

  if (pItem!=NULL)
    printf ("%s is in the array.\n",pItem);
  else
    printf ("%s is not in the array.\n",key);
  return 0;
}
```

### 출력 (C-string)

```terminal
example is in the array.
```

## 복잡도

구체적으로 언급되지 않았지만, 이진 검색은 대체로 평균적으로 $log_2(num)+2$번 정도 `compar` 함수를 호출하여 `num`에 대해 로그 시간 복잡도를 가집니다.

## 데이터 경쟁(Data races)

이 함수는 `key`가 가리키는 객체와 `base`가 가리키는 배열의 `num` 개 요소 중 임의의 수에 접근하지만, 이들을 수정하지는 않습니다.

## 예외 (C++)

`compar`가 예외를 던지지 않는다면, 이 함수는 예외를 던지지 않습니다 (예외 없는 보장).

만약 `key`가 `size` 바이트 길이의 객체를 가리키지 않거나, `base`가 적어도 `num` 개의 `size` 바이트 크기의 요소를 올바르게 정렬된 배열로 가리키지 않거나, `compar`가 위에서 설명한 대로 동작하지 않는 경우, 이는 정의되지 않은 동작을 일으킵니다.
