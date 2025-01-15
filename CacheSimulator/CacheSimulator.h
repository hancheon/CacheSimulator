#pragma once

#define WAY 8
#define CACHE_LINE_SIZE 64

struct CACHE_LINE
{
	unsigned int ways[WAY];
	unsigned int LRU_priority[WAY];
};

#undef CacheSimulate
void CacheSimulate(const char*, void*, int line);
#define CacheSimulate(X, Y) CacheSimulate(X, Y, __LINE__)