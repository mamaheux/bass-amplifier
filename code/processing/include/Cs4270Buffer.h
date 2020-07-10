#ifndef CS4270_BUFFER_H
#define CS4270_BUFFER_H

#include <stdint.h>
#include <string.h>

template<uint32_t BLOCK_SIZE>
class Cs4270Buffer
{
    static constexpr uint32_t BUFFER_SIZE = 2 * BLOCK_SIZE;

    int32_t m_buffer[BUFFER_SIZE];
    
    volatile uint32_t m_readIndex;
    volatile uint32_t m_writeIndex;

    volatile uint32_t m_readAvailable;
    volatile uint32_t m_writeAvailable;

public:
    Cs4270Buffer();
    
    bool read(int32_t& v);
    bool write(int32_t v);

    uint32_t readAvailable();
    uint32_t writeAvailable();
};

template<uint32_t BLOCK_SIZE>
Cs4270Buffer<BLOCK_SIZE>::Cs4270Buffer()
{
    memset(m_buffer, 0, BUFFER_SIZE * sizeof(int32_t));
    m_readIndex = 0;
    m_writeIndex = 0;

    m_readAvailable = 0;
    m_writeAvailable = BUFFER_SIZE;
}
    
template<uint32_t BLOCK_SIZE>
bool Cs4270Buffer<BLOCK_SIZE>::read(int32_t& v)
{
    if (m_readAvailable == 0)
    {
        return false;
    }
    v = m_buffer[m_readIndex];

    m_readAvailable -= 1;
    m_writeAvailable += 1;
    
    m_readIndex++;
    if (m_readIndex >= BUFFER_SIZE)
    {
        m_readIndex = 0;
    }
    return true;
}

template<uint32_t BLOCK_SIZE>
bool Cs4270Buffer<BLOCK_SIZE>::write(int32_t v)
{
    if (m_writeAvailable == 0)
    {
        return false;
    }

    m_buffer[m_writeIndex] = v;

    m_readAvailable += 1;
    m_writeAvailable -= 1;
    
    m_writeIndex++;
    if (m_writeIndex >= BUFFER_SIZE)
    {
        m_writeIndex = 0;
    }
    return true;
}

template<uint32_t BLOCK_SIZE>
uint32_t Cs4270Buffer<BLOCK_SIZE>::readAvailable()
{
    return m_readAvailable;
}

template<uint32_t BLOCK_SIZE>
uint32_t Cs4270Buffer<BLOCK_SIZE>::writeAvailable()
{
    return m_writeAvailable;
}

#endif
