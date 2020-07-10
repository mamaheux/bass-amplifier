#ifndef DSP_COMMUNICATION_H
#define DSP_COMMUNICATION_H

#include <EffectDesign.h>

class DspCommunication
{
    EffectDesigner** m_effectDesigners;

public:
    DspCommunication(EffectDesigner* effectDesigners[]);
    void begin();

    void update();

private:
    void sendData(EffectDesigner* effectDesigner);
};

#endif
