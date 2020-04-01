#include <unity.h>

#include <EffectDesign.h>

#include "UtilsTests.h"
#include "EffectDesignerTests.h"
#include "ContourDesignerTests.h"
#include "PresenceDesignerTests.h"
#include "EqDesignerTests.h"
#include "CompressorDesignerTests.h"

int main()
{
    UNITY_BEGIN();

    runUtilsTests();
    runEffectDesignerTests();
    runContourDesignerTests();
    runPresenceDesignerTests();
    runEqDesignerTests();
    runCompressorDesignerTests();

    UNITY_END();
}
