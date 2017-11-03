#include <vector>
#include <iostream>

int solution(int A, int B) {
	const int size = 20;
	int a[size];
	int b[size];
	int ia = size;
	int ib = size;
	if( 0 == A)
		a[--ia] = 0;
	if( 0 == B)
		b[--ib] = 0;
	while (A || B) {
		a[ia -= ( 0 != A ) ] = A % 10;
		A /= 10;
		b[ib -= ( 0 != B ) ] = B % 10;
		B /= 10;
	}
	int r = 0;
	for (; ib != size || ia != size; ) {
		if (ia < size) {
			r *= 10;
			r += a[ia++];
		}
		if (ib < size) {
			r *= 10;
			r += b[ib++];
		}
	}
	return r;
}

int main()
{
	std::cout << solution(12, 56) << std::endl;
	std::cout << solution(12300, 56) << std::endl;
	std::cout << solution(12, 56300) << std::endl;
	std::cout << solution(0, 56300) << std::endl;
	std::cout << solution(12300, 0) << std::endl;
	return 0;
}

