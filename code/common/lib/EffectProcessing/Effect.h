#ifndef EFFECT_PROCESSING_EFFECT_H
#define EFFECT_PROCESSING_EFFECT_H

#include <stdint.h>

template<uint32_t BLOCK_SIZE>
class Effect
{
public:
    Effect();
};

template<uint32_t BLOCK_SIZE>
Effect<BLOCK_SIZE>::Effect()
{
    static_assert(BLOCK_SIZE > 0, "BLOCK_SIZE must be greater than 0.");
}


#endif
