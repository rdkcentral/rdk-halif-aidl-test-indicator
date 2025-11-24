/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2016 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

/**
 * @addtogroup HPK Hardware Porting Kit
 * @{
 *
 */

/**
 * @addtogroup INDICATOR INDICATOR Module
 * @{
 *
 */

/**
 * @defgroup INDICATOR_HALTEST INDICATOR
 *
 */

/**
 * @defgroup INDICATOR_HALTEST_L3 INDICATOR HAL Tests L3 File
 * @{
 * @parblock
 *
 * ### L3 Test Cases for INDICATOR HAL :
 *
 * This module includes Level 3 functional tests (success and failure scenarios).
 * This is to ensure that the API meets the operational requirements of the module across all vendors.
 *
 * **Pre-Conditions:** @n
 * **Dependencies:** None@n
 *
 * @endparblock
 *
 */

/**
 * @file vts_indicator_l3_tests.cpp
 *
 */
//#include "vts_indicator_parse_hfp.h"
#include "vts_indicator.h"
#include "vts_indicator_parse_testconfig.h"

extern sp<IIndicator> gINDICATORHandle;
static const char *gModuleName = "Indicator";
static const char *gTestGroup = "L3";

/* Test class registration with UT_Core */
UT_ADD_TEST_TO_GROUP(VTS_L3_INDICATOR, UT_TESTS_L3)

class VTS_L3_INDICATOR : public UTCore
{
public:
    VTS_L3_INDICATOR() : UTCore() {}

    ~VTS_L3_INDICATOR() override = default;

    void SetUp() override
    {
        android::ProcessState::self()->startThreadPool();
    }

    void TearDown() override
    {
    }
};

/**
 * @brief Test Case to validate functionality of Set and Get Indicator States
 *
 *
 * **Test Group ID:** Basic: 03@n
 * **Test Case ID:** 001@n
 * **Priority:** High@n
 *
 * **Pre-Conditions:**
 *
 * **Dependencies:**
 * - A valid gINDICATORHandle must be available
 *
 * **User Interaction:** None@n
 *
 * **Test Procedure:**@n
 * Refer to UT specification documentation [indicator_High-Level_TestSpecification.md](../docs/pages/indicator_High-Level_TestSpecification.md)
 *
 */
UT_ADD_TEST(VTS_L3_INDICATOR, SetStates)
{
    const char *testName = "SetStates";
    
    std::vector<com::rdk::hal::indicator::State> indicator_state;
    com::rdk::hal::indicator::State getState;
    bool result = false;
    uint32_t repeat = 0;
    uint32_t delay = 0;

    UT_status_t status = UT_STATUS_OK;

    status = vts_indicator_parse_SetStates_config(VTS_INDICATOR_TEST_CONFIG_PATH, gModuleName, gTestGroup, testName,
                                                  indicator_state, &repeat, &delay);

    UT_ASSERT_EQUAL_FATAL(status, UT_STATUS_OK);

    for(uint32_t repeatIndex = 0; repeatIndex < repeat; repeatIndex++)
    {
        for(auto &states : indicator_state)
        {
            INDICATOR_SET(gINDICATORHandle, states, result);
            UT_ASSERT_TRUE(result);

            this_thread::sleep_for(chrono::milliseconds(delay));

            INDICATOR_GET(gINDICATORHandle, getState);
            UT_ASSERT_EQUAL(getState, states);
        }
    }
    
    return;
}



/** @} */ // End of INDICATOR_HALTEST L3 File
/** @} */ // End of INDICATOR_HALTEST
/** @} */ // End of INDICATOR Module
/** @} */ // End of HPK
