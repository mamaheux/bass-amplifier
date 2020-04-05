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

#define UNLOOP_1(code) WRAP_CODE(code)
#define UNLOOP_2(code) WRAP_CODE(code); WRAP_CODE(code)
#define UNLOOP_4(code) UNLOOP_2(code); UNLOOP_2(code)
#define UNLOOP_8(code) UNLOOP_4(code); UNLOOP_4(code)

#define WRAP_CODE(code) do { code } while(false)

#endif
