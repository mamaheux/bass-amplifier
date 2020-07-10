#ifndef EFFECT_PROCESSING_EFFECT_H
#define EFFECT_PROCESSING_EFFECT_H

#include <stdint.h>

template<uint32_t BLOCK_SIZE>
class Effect
{
    bool m_isEnabled;

public:
    Effect();

    bool isEnabled() const;
    void setIsEnabled(bool isEnabled);

    virtual void update(const uint8_t* data);
};

template<uint32_t BLOCK_SIZE>
Effect<BLOCK_SIZE>::Effect() : m_isEnabled(true)
{
    static_assert(BLOCK_SIZE > 0, "BLOCK_SIZE must be greater than 0.");
}

template<uint32_t BLOCK_SIZE>
inline bool Effect<BLOCK_SIZE>::isEnabled() const
{
    return m_isEnabled;
}

template<uint32_t BLOCK_SIZE>
inline void Effect<BLOCK_SIZE>::setIsEnabled(bool isEnabled)
{
    m_isEnabled = isEnabled;
}

template<uint32_t BLOCK_SIZE>
void Effect<BLOCK_SIZE>::update(const uint8_t* data)
{
}

#define UNROLL_1(code) WRAP_CODE(code)
#define UNROLL_2(code) WRAP_CODE(code); WRAP_CODE(code)
#define UNROLL_4(code) UNROLL_2(code); UNROLL_2(code)
#define UNROLL_8(code) UNROLL_4(code); UNROLL_4(code)

#define WRAP_CODE(code) do { code } while(false)

#endif
