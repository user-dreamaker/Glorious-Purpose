#include "global.h"
#include "random.h"

// The number 1103515245 comes from the example implementation
// of rand and srand in the ISO C standard.

u32 gRngValue;
u32 gRng2Value;

u16 Random(void)
{
    gRngValue = ISO_RANDOMIZE1(gRngValue);
    return gRngValue >> 16;
}

void SeedRng(u16 seed)
{
    gRngValue = seed;
}

u16 Random2(void)
{
    gRng2Value = ISO_RANDOMIZE1(gRng2Value);
    return gRng2Value >> 16;
}

void SeedRng2(u16 seed)
{
    gRng2Value = seed;
}