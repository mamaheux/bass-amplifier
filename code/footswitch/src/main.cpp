#include "config.h"
#include "StatusLed.h"
#include "EffectControls.h"

#include <Communication.h>
#include <Ticker.h>

ControllerFootswitchCommunication<decltype(CONTROLLER_SERIAL)> controllerCommunication(CONTROLLER_SERIAL);

StatusLed statusLed;
EffectControls effectControls(controllerCommunication);

void setupControllerCommunication();

void updateControllerCommunication();
void updateStatusLed();
void updateEffectControls();

void controllerClippingNotificationHandler();
void controllerEffectActiveStatesHandler(bool compressorActiveState,
    bool octaverActiveState,
    bool delayActiveState,
    bool reverbActiveState,
    bool overrideActiveState,
    bool muteActiveState);

Ticker updateControllerCommunicationTicker(updateControllerCommunication,
    CONTROLLER_COMMUNICATION_UPDATE_INTERVAL_US, MICROS);
Ticker updateStatusLedTicker(updateStatusLed, STATUS_LED_UPDATE_INTERVAL_US, MICROS);
Ticker updateEffectControlsTicker(updateEffectControls, EFFECT_CONTROLS_UPDATE_INTERVAL_US, MICROS);

void setup() 
{
    setupControllerCommunication();
    statusLed.begin();
    effectControls.begin();

    updateStatusLedTicker.start();
    updateControllerCommunicationTicker.start();
    updateEffectControlsTicker.start();
}

void setupControllerCommunication()
{
    controllerCommunication.begin(CONTROLLER_SERIAL_BAUD_RATE);
    controllerCommunication.registerClippingNotificationHandler(controllerClippingNotificationHandler);
    controllerCommunication.registerEffectActiveStatesHandler(controllerEffectActiveStatesHandler);
}

void loop()
{
    updateControllerCommunicationTicker.update();
    updateStatusLedTicker.update();
    updateEffectControlsTicker.update();
}

void updateControllerCommunication()
{
    while (controllerCommunication.receive());
}

void updateStatusLed()
{
    statusLed.update();
}

void updateEffectControls()
{
    effectControls.update();
}

void controllerClippingNotificationHandler()
{
    statusLed.notifyClipping();
}

void controllerEffectActiveStatesHandler(bool compressorActiveState,
    bool octaverActiveState,
    bool delayActiveState,
    bool reverbActiveState,
    bool overrideActiveState,
    bool muteActiveState)
{
    statusLed.setCompressorLed(compressorActiveState);
    statusLed.setOctaverLed(octaverActiveState);
    statusLed.setDelayLed(delayActiveState);
    statusLed.setReverbLed(reverbActiveState);
    statusLed.setOverdriveLed(overrideActiveState);
    statusLed.setMuteLed(muteActiveState);
}