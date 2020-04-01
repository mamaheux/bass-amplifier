#include <unity.h>

#include <EffectDesign.h>

#include "UtilsTests.h"
#include "EffectDesignerTests.h"
#include "ContourDesignerTests.h"
#include "PresenceDesignerTests.h"
#include "EqDesignerTests.h"

int main()
{
    UNITY_BEGIN();

    runUtilsTests();
    runEffectDesignerTests();
    runContourDesignerTests();
    runPresenceDesignerTests();
    runEqDesignerTests();

    UNITY_END();
}
