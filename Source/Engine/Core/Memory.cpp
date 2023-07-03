#include "Memory.h"
#include <iostream>

using namespace std;
kiko::MemoryTracker kiko::g_memoryTracker;

void* operator new(size_t size)
{
	void* ptr = malloc(size);

	kiko::g_memoryTracker.Add(ptr, size);

	return ptr;
}

void operator delete (void* memory, size_t size)
{
	kiko::g_memoryTracker.Remove(memory, size);

	free(memory);
}

namespace kiko
{
	void MemoryTracker::Add(void* memory, size_t size)
	{
		m_bytesAllocated += size;
		m_numAllocated++;
	}
	void MemoryTracker::Remove(void* memory, size_t size)
	{
		m_bytesAllocated -= size;
		m_numAllocated--;
	}
	void MemoryTracker::DisplayInfo()
	{
		cout << "Current Byte Allocated: " << m_bytesAllocated << endl;
		cout << "Current Number Allocated: " << m_numAllocated << endl;
	}
}