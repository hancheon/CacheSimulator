#include <iostream>
#include "CacheSimulator.h"

struct TEST
{
	int a;
	char buf[60];
	int b;
};

void Test()
{
	int a = 0;
	CacheSimulate("a", &a);
	int b = 0;
	CacheSimulate("b", &b);
	printf("a 林家: 0x%p\n", &a);
	printf("b 林家: 0x%p\n", &b);
}

int main()
{
	int a = 0;
	CacheSimulate("a", &a);
	printf("a 林家: 0x%p\n", &a);
	int b = 0;
	CacheSimulate("b", &b);
	printf("b 林家: 0x%p\n", &b);
	TEST t1;
	t1.a = 3;
	CacheSimulate("t1.a", &a);
	printf("t1.a 林家: 0x%p\n", &t1.a);
	memset(t1.buf, 2, sizeof(t1.buf));
	CacheSimulate("t1.buf", t1.buf);
	printf("t1.buf 林家: 0x%p\n", &t1.buf);
	t1.b = 1;
	CacheSimulate("t1.b", &t1.b);
	printf("t1.b 林家: 0x%p\n", &b);
	Test();
	CacheSimulate("a", &a);
	printf("a 林家: 0x%p\n", &a);
}