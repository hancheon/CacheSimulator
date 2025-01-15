#include <iostream>
#include <string>
#include "CacheSimulator.h"

// 32bit 8-way 64-line Architecture
// |----------20bit(Tag)----------|------6bit(Index)------|------6bit(Offset)------|

CACHE_LINE cacheLines[CACHE_LINE_SIZE];

#undef CacheSimulate
void CacheSimulate(const char* tag, void* ptr, int line)
{
	unsigned int address = (unsigned int)ptr;
	unsigned int cacheTag;
	unsigned char cacheIndex;

	cacheTag = (unsigned int)(address >> 12);
	cacheIndex = (unsigned char)(address >> 6) & 0x3f;

	bool cacheHit = false;
	for (int i = 0; i < WAY; i++)
	{
		// Cache Hit
		if (cacheLines[cacheIndex].ways[i] == cacheTag)
		{
			for (int j = 0; j < WAY; j++)
			{
				if (j != i)
				{
					cacheLines[cacheIndex].LRU_priority[j]--;
				}
				else
				{
					cacheLines[cacheIndex].LRU_priority[j] = 7;
				}
			}

			cacheHit = true;
			break;
		}
	}

	// Cache Miss
	if (!cacheHit)
	{
		printf("[Cache Miss] line: %d, tag: %s\n", line, tag);

		for (int j = 0; j < WAY; j++)
		{
			if (cacheLines[cacheIndex].LRU_priority[j] > 0)
			{
				cacheLines[cacheIndex].LRU_priority[j]--;
			}
			else
			{
				cacheLines[cacheIndex].ways[j] = cacheTag;
				cacheLines[cacheIndex].LRU_priority[j] = 7;
			}
		}
	}
}
#define CacheSimulate(X, Y) CacheSimulate(X, Y, __LINE__)