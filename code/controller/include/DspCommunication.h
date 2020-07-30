#ifndef DSP_COMMUNICATION_H
#define DSP_COMMUNICATION_H

#include <EffectDesign.h>

class DspCommunication
{
public:
    typedef void (*ClippingNotificationHandler)();

private:
    EffectDesigner** m_effectDesigners;
    ClippingNotificationHandler m_clippingNotificationHandler;

public:
    DspCommunication(EffectDesigner* effectDesigners[]);
    void begin(ClippingNotificationHandler clippingNotificationHandler);

    void update();

private:
    void sendData(EffectDesigner* effectDesigner);
    void readNotification();
};

#endif
