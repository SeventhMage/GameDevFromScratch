#ifndef G_MEMORY_H_

void *CreateMemoryZone(int size);
void DestroyMemoryZone(void *ptr);
void *Malloc(void *fromPtr, int size);
void Free(void *fromPtr, void *ptr);
void DebugPrint(void *ptr, const char *message);

#endif
