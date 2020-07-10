#include "InterruptLock.h"

InterruptLock::InterruptLock(IRQ_NUMBER_t irqNumber) : m_irqNumber(irqNumber)
{
    NVIC_DISABLE_IRQ(m_irqNumber);
}

InterruptLock::~InterruptLock()
{
    NVIC_ENABLE_IRQ(m_irqNumber);
}