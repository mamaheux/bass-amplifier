#include <unity.h>

#include <EffectDesign.h>

#include "UtilsTests.h"
#include "EffectDesignerTests.h"
#include "ContourDesignerTests.h"
#include "PresenceDesignerTests.h"
#include "EqDesignerTests.h"
#include "CompressorDesignerTests.h"
#include "OctaverDesignerTests.h"
#include "DelayDesignerTests.h"
#include "ReverbDesignerTests.h"
#include "OverdriveDesignerTests.h"

int main()
{
    UNITY_BEGIN();

    runUtilsTests();
    runEffectDesignerTests();
    runContourDesignerTests();
    runPresenceDesignerTests();
    runEqDesignerTests();
    runCompressorDesignerTests();
    runOctaverDesignerTests();
    runDelayDesignerTests();
    runReverbDesignerTests();
    runOverdriveDesignerTests();

    UNITY_END();
}
