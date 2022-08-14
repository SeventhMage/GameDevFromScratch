#include <stdlib.h>
#include <stdio.h>

#include "gmemory.h"

//内存块
typedef struct memblock_s
{
    int size;                       //包含头大小的当前内存块尺寸
    int tag;                        //当前内存块是否被使用标记
    struct memblock_s *next, *prev; //链连接的上一和下一空闲块
} memblock_t;

//放在内存末尾用于找到内存头信息
typedef struct
{
    int size;
} memfooter_t;

//内存区首地址
typedef struct
{
    int size;               //总内存大小
    int used;               //当前使用的内存大小
    memblock_t *freeblock;  //第一块空闲内存块
} memzone_t;

void *CreateMemoryZone(int size)
{
    memzone_t *zone;
    memblock_t *block;
    zone = (memzone_t *)calloc(size, 1);
    if (!zone)
    {
        printf("InitMemory failed : %d", size);
        return 0;
    }
    zone->size = size;
    zone->used = 0;
    block = (memblock_t *)((char *)zone + sizeof(memzone_t));
    block->next = block->prev = block;
    block->size = size - sizeof(memzone_t);
    block->tag = 0;
    zone->freeblock = block;

    return zone;
}

void DestroyMemoryZone(void *ptr)
{
    if (ptr)
        free(ptr);
}

memblock_t *FindFreeMemory(memzone_t *zone, int size)
{
    memblock_t *base = 0, *worker = 0;
    int minMeetSize = -1;

    if (size > zone->size - sizeof(memzone_t) - sizeof(memblock_t) - zone->used)
        return 0;

    worker = zone->freeblock;
    if (!worker)
        return 0;
    do
    {
        if (worker->size >= size && (worker->size < minMeetSize || minMeetSize == -1))
        {
            base = worker;
            minMeetSize = worker->size;
        }
    } while (worker != zone->freeblock);

    return base;
}

void *Malloc(void *fromPtr, int size)
{
    int allocSize, extra;
    memblock_t *base, *new;
    memfooter_t *footer;
    memzone_t *zone = (memzone_t *)fromPtr;

    allocSize = size;
    size += sizeof(memblock_t) + sizeof(memfooter_t);
    size = (size + 3) & ~3; //4字节对齐

    base = FindFreeMemory(zone, size);
    if (!base)
    {
        printf("Malloc failed, memory not enough:%d\n", size);
        return 0;
    }

    extra = base->size - size;
    if (extra > sizeof(memblock_t) + sizeof(memfooter_t)) //找到的内存剩余部分可以分割为另一个block
    {
        new = (memblock_t *)((char *)base + size);
        if (base->next == base) //唯一空闲块
            new->next = new->prev = new;
        else
        {
            new->next = base->next;
            new->prev = base->prev;
        }
        new->size = extra;
        zone->freeblock = new;
    }
    else
    {
        if (base->next == base) //唯一内存被分配
            zone->freeblock = 0;
        else
            zone->freeblock = base->next;
    }

    base->size = size;

    footer = (memfooter_t *)((char *)base + size - sizeof(memfooter_t));
    footer->size = size;

    base->tag = 1;
    zone->used += size;

    return (void *)((char *)base + sizeof(memblock_t));
}

void Free(void *fromPtr, void *ptr)
{
    memblock_t *base, *other, *first, *last;
    memfooter_t *baseFooter, *prevAdjacentFooter, *lastFooter;
    memzone_t *zone = (memzone_t *)fromPtr;
    int freeSize;
    int isMerged = 0;

    base = (memblock_t *)((char *)ptr - sizeof(memblock_t));
    base->tag = 0;
    freeSize = base->size;

    first = (memblock_t *)((char *)fromPtr + sizeof(memzone_t));
    lastFooter = (memfooter_t *)((char *)fromPtr + zone->size - sizeof(memfooter_t));
    last = (memblock_t *)((char *)fromPtr + zone->size - lastFooter->size);

    if (!zone->freeblock)
    {
        zone->freeblock = base->next = base->prev = base;
        return;
    }

    //检查相邻内存空闲则合并
    if (base > first)
    {
        prevAdjacentFooter = (memfooter_t *)((char *)base - sizeof(memfooter_t));
        other = (memblock_t *)((char *)base - prevAdjacentFooter->size);
        if (other->tag == 0)
        {
            base = other;
            base->size += freeSize;
            isMerged = 1;
        }
    }

    if (base < last)
    {
        other = (memblock_t *)((char *)base + base->size);
        if (other->tag == 0)
        {
            base->size += other->size;
            base->next = other->next;
            base->prev = other->prev;
            base->prev->next = base;
            base->next->prev = base;
            if (other == zone->freeblock)
            {
                zone->freeblock = base;
            }
            isMerged = 1;
        }
    }

    baseFooter = (memfooter_t *)((char *)base + base->size - sizeof(memfooter_t));
    baseFooter->size = base->size;

    zone->used -= freeSize;

    if (!isMerged)
    {
        base->next = zone->freeblock->next;
        base->prev = zone->freeblock;
        zone->freeblock->next = base;
        if (zone->freeblock->prev == zone->freeblock)
            zone->freeblock->prev = base;
    }
}

void DebugPrint(void *ptr, const char *message)
{
    memzone_t *zone = (memzone_t *)ptr;
    memblock_t *block;
    printf("==========================================\n");
    printf("%s\n", message);
    printf("Zone Info(%p):\nSize: %d\nUsed:%d\n", zone, zone->size, zone->used);
    block = zone->freeblock;
    while (block)
    {
        printf("Free addr:%p, size:%d\n", block, block->size);
        block = block->next;
        if (block == zone->freeblock)
            break;
    }
    printf("==========================================\n");

    printf("\n\r");
}
