/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
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
#include "ut_log.h"
#include "com/rdk/hal/indicator/State.h"

extern sp<IIndicator> gINDICATORHandle;

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
 * @brief Test for set() and get() functions of IIndicator interface for General states
 *
 * This test verifies that the set() and get() methods of the IIndicator interface
 * can set and get the general indicator states: ACTIVE, STANDBY, OFF, DEEP_SLEEP.
 *
 * **Test Group ID:** 02@n
 * **Test Case ID:** 001@n
 *
 * **Test Procedure:**
 * Refer to Indicator specification documentation [indicator_L2_Low-Level_TestSpecification](../docs/pages/)
 */
UT_ADD_TEST(VTS_L2_INDICATOR, test_l2_setgetGeneralStates)
{
    com::rdk::hal::indicator::Capabilities caps;
    com::rdk::hal::indicator::State getState;
    bool result = false;
    
    INDICATOR_GET_CAPABILITIES(gINDICATORHandle, caps);

    std::vector<com::rdk::hal::indicator::State> generalStates = {
        com::rdk::hal::indicator::State::ACTIVE,
        com::rdk::hal::indicator::State::STANDBY,
        com::rdk::hal::indicator::State::OFF,
        com::rdk::hal::indicator::State::DEEP_SLEEP
    };
    
    for (const auto& general_state : generalStates) 
    {
        if (!(std::find(caps.supportedStates.begin(), caps.supportedStates.end(), general_state) != caps.supportedStates.end())) 
        {
                UT_LOG_INFO("%s state is not supported", toString(general_state).c_str());
                continue;
        }
        INDICATOR_SET(gINDICATORHandle, general_state, result);
        UT_ASSERT_TRUE(result);
        INDICATOR_GET(gINDICATORHandle, getState);
        UT_ASSERT_EQUAL(getState, general_state);
    }
    
    return;
}

/**
 * @brief Test for set() and get() functions of IIndicator interface for WPS states
 *
 * This test verifies that the set() and get() methods of the IIndicator interface
 * can set and get the WPS indicator states: WPS_CONNECTING, WPS_CONNECTED, WPS_ERROR, WPS_SES_OVERLAP.
 *
 * **Test Group ID:** 02@n
 * **Test Case ID:** 002@n
 *
 * **Test Procedure:**
 * Refer to Indicator specification documentation [indicator_L2_Low-Level_TestSpecification](../docs/pages/)
 */
UT_ADD_TEST(VTS_L2_INDICATOR, test_l2_setgetWpsStates)
{
    com::rdk::hal::indicator::Capabilities caps;
    com::rdk::hal::indicator::State getState;
    bool result = false;
    
    INDICATOR_GET_CAPABILITIES(gINDICATORHandle, caps);

    std::vector<com::rdk::hal::indicator::State> wpsStates = {
        com::rdk::hal::indicator::State::WPS_CONNECTING,
        com::rdk::hal::indicator::State::WPS_CONNECTED,
        com::rdk::hal::indicator::State::WPS_ERROR,
        com::rdk::hal::indicator::State::WPS_SES_OVERLAP
    };

    for (const auto& wps_state : wpsStates) 
    {
        if (!(std::find(caps.supportedStates.begin(), caps.supportedStates.end(), wps_state) != caps.supportedStates.end())) 
        {
                UT_LOG_INFO("%s state is not supported", toString(wps_state).c_str());
                continue;
        }
        INDICATOR_SET(gINDICATORHandle, wps_state, result);
        UT_ASSERT_TRUE(result);
        INDICATOR_GET(gINDICATORHandle, getState);
        UT_ASSERT_EQUAL(getState, wps_state);
    }

    return;
}

/**
 * @brief Test for set() and get() functions of IIndicator interface for Network states
 *
 * This test verifies that the set() and get() methods of the IIndicator interface
 * can set and get the Network indicator states: WIFI_ERROR, IP_ACQUIRED, NO_IP.
 *
 * **Test Group ID:** 02@n
 * **Test Case ID:** 003@n
 *
 * **Test Procedure:**
 * Refer to Indicator specification documentation [indicator_L2_Low-Level_TestSpecification](../docs/pages/)
 */
UT_ADD_TEST(VTS_L2_INDICATOR, test_l2_setgetNetworkStates)
{
    com::rdk::hal::indicator::Capabilities caps;
    com::rdk::hal::indicator::State getState;
    bool result = false;
    
    INDICATOR_GET_CAPABILITIES(gINDICATORHandle, caps);

    std::vector<com::rdk::hal::indicator::State> networkStates = {
        com::rdk::hal::indicator::State::WIFI_ERROR,
        com::rdk::hal::indicator::State::IP_ACQUIRED,
        com::rdk::hal::indicator::State::NO_IP
    };

    for (const auto& network_state : networkStates) 
    {
        if (!(std::find(caps.supportedStates.begin(), caps.supportedStates.end(), network_state) != caps.supportedStates.end())) 
        {
                UT_LOG_INFO("%s state is not supported", toString(network_state).c_str());
                continue;
        }
        INDICATOR_SET(gINDICATORHandle, network_state, result);
        UT_ASSERT_TRUE(result);
        INDICATOR_GET(gINDICATORHandle, getState);
        UT_ASSERT_EQUAL(getState, network_state);
    }

    return;
}

/**
 * @brief Test for set() and get() functions of IIndicator interface for System Maintenance states
 *
 * This test verifies that the set() and get() methods of the IIndicator interface
 * can set and get the Maintenance indicator states: FULL_SYSTEM_RESET, USB_UPGRADE, SOFTWARE_DOWNLOAD_ERROR, PSU_FAILURE.
 *
 * **Test Group ID:** 02@n
 * **Test Case ID:** 004@n
 *
 * **Test Procedure:**
 * Refer to Indicator specification documentation [indicator_L2_Low-Level_TestSpecification](../docs/pages/)
 */
UT_ADD_TEST(VTS_L2_INDICATOR, test_l2_setgetMaintenanceStates)
{
    com::rdk::hal::indicator::Capabilities caps;
    com::rdk::hal::indicator::State getState;
    bool result = false;
    
    INDICATOR_GET_CAPABILITIES(gINDICATORHandle, caps);

    std::vector<com::rdk::hal::indicator::State> maintenanceStates = {
        com::rdk::hal::indicator::State::FULL_SYSTEM_RESET,
        com::rdk::hal::indicator::State::USB_UPGRADE,
        com::rdk::hal::indicator::State::SOFTWARE_DOWNLOAD_ERROR,
        com::rdk::hal::indicator::State::PSU_FAILURE
    };
    for (const auto& system_state : maintenanceStates) 
    {
        if (!(std::find(caps.supportedStates.begin(), caps.supportedStates.end(), system_state) != caps.supportedStates.end())) 
        {
                UT_LOG_INFO("%s state is not supported", toString(system_state).c_str());
                continue;
        }
        INDICATOR_SET(gINDICATORHandle, system_state, result);
        UT_ASSERT_TRUE(result);
        INDICATOR_GET(gINDICATORHandle, getState);
        UT_ASSERT_EQUAL(getState, system_state);
    }
    
    return;
}

/**
* @} // End of INDICATOR_HALTEST_CLASS
* @} // End of INDICATOR_HALTEST
* @} // End of INDICATOR
* @} // End of HPK
*/
/* End of vts_indicator_l2_tests.cpp */