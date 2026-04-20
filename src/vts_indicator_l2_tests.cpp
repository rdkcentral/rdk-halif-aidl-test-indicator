/**
*  If not stated otherwise in this file or this component's LICENSE
*  file the following copyright and licenses apply:
*
*  Copyright 2026 RDK Management
*
*  Licensed under the Apache License, Version 2.0 (the License);
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*  http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an AS IS BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*/

/**
 * @addtogroup HPK Hardware Porting Kit
 * @{
 * @par The Hardware Porting Kit
 * HPK is the next evolution of the well-defined Hardware Abstraction Layer
 * (HAL), but augmented with more comprehensive documentation and test suites
 * that OEM or SOC vendors can use to self-certify their ports before taking
 * them to RDKM for validation or to an operator for final integration and
 * deployment. The Hardware Porting Kit effectively enables an OEM and/or SOC
 * vendor to self-certify their own Video Accelerator devices, with minimal RDKM
 * assistance.
 *
 */

/**
 * @addtogroup INDICATOR INDICATOR Module
 * @{
 */

/**
 * @addtogroup INDICATOR_HALTEST INDICATOR HAL Tests
 * @{
 */

/**
 * @defgroup INDICATOR_HALTEST_CLASS INDICATOR HAL Tests L2 Test Cases
 * @{
 * @parblock
 *
 * ### Common functions/macros required for the INDICATOR module :
 *
 * Common functions/macros required for the INDICATOR module .
 *
 * **Pre-Conditions:**  None @n
 * **Dependencies:** None @n
 *
 * @endparblock
 *
 */

/**
 * @file vts_indicator_l2_tests.cpp
 *
 */

#include "vts_indicator.h"
#include "com/rdk/hal/indicator/IIndicator.h"
#include "com/rdk/hal/indicator/IIndicatorManager.h"
#include "ut_log.h"

extern sp<IIndicatorManager> gINDICATORHandle;

/* Test class registration with UT_Core */
UT_ADD_TEST_TO_GROUP(VTS_L2_INDICATOR, UT_TESTS_L2)

class VTS_L2_INDICATOR : public UTCore
{
public:
    VTS_L2_INDICATOR() : UTCore() {}

    ~VTS_L2_INDICATOR() override = default;

    void SetUp() override
    {
        android::ProcessState::self()->startThreadPool();
    }

    void TearDown() override
    {
    }
};

/**
 * @brief Validates set() and get() for General indicator states.
 *
 * This test ensures that:
 * - All General states (ACTIVE, STANDBY, OFF, DEEP_SLEEP) can be set and retrieved.
 * - Only supported states defined in the capabilities are tested.
 *
 * **Test Group ID:** 02@n
 * **Test Case ID:** 001@n
 * **Priority:** High@n
 *
 * **Pre-Conditions:**@n
 * - Indicator HAL must be initialized and gINDICATORHandle must be valid@n
 * - Supported states must be configured in the profile@n
 *
 * **Dependencies:**@n
 * - getIndicatorIds() and getIndicator() must work correctly@n
 *
 * **User Interaction:** None@n
 *
 * **Test Procedure:**@n
 * | Step | Action | Input | Expected Result | Remarks |
 * |01|Call getIndicatorIds()|N/A|Returns list of IDs|Mandatory step|
 * |02|Retrieve each indicator instance|ID from step 1|Non-null IIndicator object|Mandatory step|
 * |03|Call getCapabilities()|Indicator object|Obtain supported states|Mandatory step|
 * |04|For each General state|Supported state|Call set() and get()|Set and verify state only if supported|
 * |05|Assert returned state matches set state|get() result|Equal to set state|Logs unsupported states|
 */

UT_ADD_TEST(VTS_L2_INDICATOR, test_l2_setgetGeneralStates)
{
    std::vector<com::rdk::hal::indicator::IIndicator::Id> ids;
    INDICATOR_GET_INDICATORIDS(gINDICATORHandle, ids);

    std::vector<android::String16> generalStates = {
        android::String16("ACTIVE"),
        android::String16("STANDBY"),
        android::String16("OFF"),
        android::String16("DEEP_SLEEP")
    };

    for (const auto& id : ids)
    {
        android::sp<com::rdk::hal::indicator::IIndicator> indicator;
        INDICATOR_GET_INDICATOR(gINDICATORHandle, id, indicator);

        com::rdk::hal::indicator::Capabilities caps;
        INDICATOR_GET_CAPS(indicator, caps);

        for (const auto& state : generalStates)
        {
            if (std::find(caps.supportedStates.begin(), caps.supportedStates.end(), state) == caps.supportedStates.end())
            {
                UT_LOG_INFO("%s state not supported for ID=%d", android::String8(state).string(), id.value);
                continue;
            }

            // Set state POS
            INDICATOR_SET_STATE_POS(indicator, state);

            // Get state POS
            android::String16 getState;
            INDICATOR_GET_STATE_POS(indicator, getState);

            UT_ASSERT_EQUAL(getState, state);
        }
    }
}

/**
 * @brief Validates set() and get() for WPS indicator states.
 *
 * This test ensures that:
 * - WPS states (WPS_CONNECTING, WPS_CONNECTED, WPS_ERROR, WPS_SES_OVERLAP) can be set and retrieved.
 * - Only supported states defined in capabilities are tested.
 *
 * **Test Group ID:** 02@n
 * **Test Case ID:** 002@n
 * **Priority:** High@n
 *
 * **Pre-Conditions:**@n
 * - Indicator HAL must be initialized and gINDICATORHandle must be valid@n
 * - Supported states must be configured in the profile@n
 *
 * **Dependencies:**@n
 * - getIndicatorIds() and getIndicator() must work correctly@n
 *
 * **User Interaction:** None@n
 *
 * **Test Procedure:**@n
 * | Step | Action | Input | Expected Result | Remarks |
 * |01|Call getIndicatorIds()|N/A|Returns list of IDs|Mandatory step|
 * |02|Retrieve each indicator instance|ID from step 1|Non-null IIndicator object|Mandatory step|
 * |03|Call getCapabilities()|Indicator object|Obtain supported states|Mandatory step|
 * |04|For each WPS state|Supported state|Call set() and get()|Set and verify state only if supported|
 * |05|Assert returned state matches set state|get() result|Equal to set state|Logs unsupported states|
 */

UT_ADD_TEST(VTS_L2_INDICATOR, test_l2_setgetWpsStates)
{
    std::vector<com::rdk::hal::indicator::IIndicator::Id> ids;
    INDICATOR_GET_INDICATORIDS(gINDICATORHandle, ids);

    std::vector<android::String16> wpsStates = {
        android::String16("WPS_CONNECTING"),
        android::String16("WPS_CONNECTED"),
        android::String16("WPS_ERROR"),
        android::String16("WPS_SES_OVERLAP")
    };

    for (const auto& id : ids)
    {
        android::sp<com::rdk::hal::indicator::IIndicator> indicator;
        INDICATOR_GET_INDICATOR(gINDICATORHandle, id, indicator);

        com::rdk::hal::indicator::Capabilities caps;
        INDICATOR_GET_CAPS(indicator, caps);

        for (const auto& state : wpsStates)
        {
            if (std::find(caps.supportedStates.begin(), caps.supportedStates.end(), state) == caps.supportedStates.end())
            {
                UT_LOG_INFO("%s state not supported for ID=%d", android::String8(state).string(), id.value);
                continue;
            }

            INDICATOR_SET_STATE_POS(indicator, state);

            android::String16 getState;
            INDICATOR_GET_STATE_POS(indicator, getState);

            UT_ASSERT_EQUAL(getState, state);
        }
    }
}

/**
 * @brief Validates set() and get() for Network indicator states.
 *
 * This test ensures that:
 * - Network states (WIFI_ERROR, IP_ACQUIRED, NO_IP) can be set and retrieved.
 * - Only supported states defined in capabilities are tested.
 *
 * **Test Group ID:** 02@n
 * **Test Case ID:** 003@n
 * **Priority:** High@n
 *
 * **Pre-Conditions:**@n
 * - Indicator HAL must be initialized and gINDICATORHandle must be valid@n
 * - Supported states must be configured in the profile@n
 *
 * **Dependencies:**@n
 * - getIndicatorIds() and getIndicator() must work correctly@n
 *
 * **User Interaction:** None@n
 *
 * **Test Procedure:**@n
 * | Step | Action | Input | Expected Result | Remarks |
 * |01|Call getIndicatorIds()|N/A|Returns list of IDs|Mandatory step|
 * |02|Retrieve each indicator instance|ID from step 1|Non-null IIndicator object|Mandatory step|
 * |03|Call getCapabilities()|Indicator object|Obtain supported states|Mandatory step|
 * |04|For each Network state|Supported state|Call set() and get()|Set and verify state only if supported|
 * |05|Assert returned state matches set state|get() result|Equal to set state|Logs unsupported states|
 */

UT_ADD_TEST(VTS_L2_INDICATOR, test_l2_setgetNetworkStates)
{
    std::vector<com::rdk::hal::indicator::IIndicator::Id> ids;
    INDICATOR_GET_INDICATORIDS(gINDICATORHandle, ids);

    std::vector<android::String16> networkStates = {
        android::String16("WIFI_ERROR"),
        android::String16("IP_ACQUIRED"),
        android::String16("NO_IP")
    };

    for (const auto& id : ids)
    {
        android::sp<com::rdk::hal::indicator::IIndicator> indicator;
        INDICATOR_GET_INDICATOR(gINDICATORHandle, id, indicator);

        com::rdk::hal::indicator::Capabilities caps;
        INDICATOR_GET_CAPS(indicator, caps);

        for (const auto& state : networkStates)
        {
            if (std::find(caps.supportedStates.begin(), caps.supportedStates.end(), state) == caps.supportedStates.end())
            {
                UT_LOG_INFO("%s state not supported for ID=%d", android::String8(state).string(), id.value);
                continue;
            }

            INDICATOR_SET_STATE_POS(indicator, state);

            android::String16 getState;
            INDICATOR_GET_STATE_POS(indicator, getState);

            UT_ASSERT_EQUAL(getState, state);
        }
    }
}

/**
 * @brief Validates set() and get() for System Maintenance indicator states.
 *
 * This test ensures that:
 * - Maintenance states (FULL_SYSTEM_RESET, USB_UPGRADE, SOFTWARE_DOWNLOAD_ERROR, PSU_FAILURE) can be set and retrieved.
 * - Only supported states defined in capabilities are tested.
 *
 * **Test Group ID:** 02@n
 * **Test Case ID:** 004@n
 * **Priority:** High@n
 *
 * **Pre-Conditions:**@n
 * - Indicator HAL must be initialized and gINDICATORHandle must be valid@n
 * - Supported states must be configured in the profile@n
 *
 * **Dependencies:**@n
 * - getIndicatorIds() and getIndicator() must work correctly@n
 *
 * **User Interaction:** None@n
 *
 * **Test Procedure:**@n
 * | Step | Action | Input | Expected Result | Remarks |
 * |01|Call getIndicatorIds()|N/A|Returns list of IDs|Mandatory step|
 * |02|Retrieve each indicator instance|ID from step 1|Non-null IIndicator object|Mandatory step|
 * |03|Call getCapabilities()|Indicator object|Obtain supported states|Mandatory step|
 * |04|For each Maintenance state|Supported state|Call set() and get()|Set and verify state only if supported|
 * |05|Assert returned state matches set state|get() result|Equal to set state|Logs unsupported states|
 */
UT_ADD_TEST(VTS_L2_INDICATOR, test_l2_setgetMaintenanceStates)
{
    std::vector<com::rdk::hal::indicator::IIndicator::Id> ids;
    INDICATOR_GET_INDICATORIDS(gINDICATORHandle, ids);

    std::vector<android::String16> maintenanceStates = {
        android::String16("FULL_SYSTEM_RESET"),
        android::String16("USB_UPGRADE"),
        android::String16("SOFTWARE_DOWNLOAD_ERROR"),
        android::String16("PSU_FAILURE")
    };

    for (const auto& id : ids)
    {
        android::sp<com::rdk::hal::indicator::IIndicator> indicator;
        INDICATOR_GET_INDICATOR(gINDICATORHandle, id, indicator);

        com::rdk::hal::indicator::Capabilities caps;
        INDICATOR_GET_CAPS(indicator, caps);

        for (const auto& state : maintenanceStates)
        {
            if (std::find(caps.supportedStates.begin(), caps.supportedStates.end(), state) == caps.supportedStates.end())
            {
                UT_LOG_INFO("%s state not supported for ID=%d", android::String8(state).string(), id.value);
                continue;
            }

            INDICATOR_SET_STATE_POS(indicator, state);

            android::String16 getState;
            INDICATOR_GET_STATE_POS(indicator, getState);

            UT_ASSERT_EQUAL(getState, state);
        }
    }
}


/**
* @} // End of INDICATOR_HALTEST_CLASS
* @} // End of INDICATOR_HALTEST
* @} // End of INDICATOR
* @} // End of HPK
*/
/* End of vts_indicator_l2_tests.cpp */
