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

extern sp<IIndicatorManager> gINDICATORHandle;
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

    std::vector<android::String16> indicator_states;
    uint32_t repeat = 0;
    uint32_t delay = 0;

    UT_status_t status = vts_indicator_parse_SetStates_config(
                            VTS_INDICATOR_TEST_CONFIG_PATH,
                            gModuleName,
                            gTestGroup,
                            testName,
                            indicator_states,
                            &repeat,
                            &delay);

    UT_ASSERT_EQUAL_FATAL(status, UT_STATUS_OK);

    // STEP 1: Manager → Get IDs
    android::sp<com::rdk::hal::indicator::IIndicatorManager> manager = gINDICATORHandle;
    std::vector<com::rdk::hal::indicator::IIndicator::Id> ids;
    INDICATOR_GET_INDICATORIDS(manager, ids);
    UT_ASSERT_TRUE(ids.size() > 0);

    // Loop through each instance
    for (const auto& id : ids)
    {
        android::sp<com::rdk::hal::indicator::IIndicator> indicatorObj = nullptr;

        // STEP 2: Get Indicator instance
        INDICATOR_GET_INDICATOR(manager, id, indicatorObj);
        UT_ASSERT_TRUE(indicatorObj != nullptr);

        // STEP 3: Get Capabilities
        com::rdk::hal::indicator::Capabilities caps;
        INDICATOR_GET_CAPS(indicatorObj, caps);

        UT_ASSERT_TRUE(caps.supportedStates.size() > 0);
        UT_LOG_INFO("Indicator supports %zu state(s)", caps.supportedStates.size());

        for (uint32_t repeatIndex = 0; repeatIndex < repeat; repeatIndex++)
        {
            for (auto &state : indicator_states)
            {
                // Only test states that instance supports
                if (std::find(caps.supportedStates.begin(),
                              caps.supportedStates.end(),
                              state) == caps.supportedStates.end())
                {
                    UT_LOG_INFO("State not supported for ID=%d", id.value);
                    continue;
                }

                // STEP 4: SET
                INDICATOR_SET_STATE_POS(indicatorObj, state);

                this_thread::sleep_for(chrono::milliseconds(delay));

                // STEP 5: GET verify
                android::String16 getState;
                INDICATOR_GET_STATE_POS(indicatorObj, getState);

                UT_ASSERT_EQUAL(getState, state);
            }
        }
    }
}



/** @} */ // End of INDICATOR_HALTEST L3 File
/** @} */ // End of INDICATOR_HALTEST
/** @} */ // End of INDICATOR Module
/** @} */ // End of HPK