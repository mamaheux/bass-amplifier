#ifndef INTERRUPT_LOCK_H
#define INTERRUPT_LOCK_H

#include <Arduino.h>

class InterruptLock
{
    IRQ_NUMBER_t m_irqNumber;
public:
    InterruptLock(IRQ_NUMBER_t irqNumber);
    ~InterruptLock();
};

#endif
