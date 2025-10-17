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
 * @addtogroup indicator indicator Module
 * @{
 */

/**
 * @addtogroup indicator_HALTEST indicator HAL Tests
 * @{
 */

/**
 * @defgroup indicator_HALTEST_CLASS indicator HAL Tests L1 Test Cases
 * @{
 * @parblock
 *
 * ### Common functions/macros required for the indicator module :
 *
 * Common functions/macros required for the indicator module .
 *
 * **Pre-Conditions:**  None @n
 * **Dependencies:** None @n
 *
 * @endparblock
 *
 */

/**
 * @file vts_indicator_l1_tests.cpp
 *
 */

 #include "vts_indicator.h"
 #include "com/rdk/hal/indicator/IIndicator.h"
 #include "ut_log.h"
 
 extern sp<IIndicator> gINDICATORHandle;
 
 /* Test class registration with UT_Core */
 UT_ADD_TEST_TO_GROUP(VTS_L1_INDICATOR, UT_TESTS_L1)
 
 class VTS_L1_INDICATOR : public UTCore
 {
    public:
        VTS_L1_INDICATOR() : UTCore() {}
    
        ~VTS_L1_INDICATOR() override = default;
    
        void SetUp() override
        {
            android::ProcessState::self()->startThreadPool();
        }
    
        void TearDown() override
        {
        }
 };
 
 /**
 * @brief Validates that the Indicator HAL getCapabilities() API returns all supported states
 *
 * This test ensures that:
 * - The getCapabilities() API correctly returns the Capabilities object.
 * - All supported states defined in the KVP profile (IIndicator.supportedStates) 
 *   are present in the returned Capabilities object.
 *
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 001@n
 * **Priority:** High@n
 *
 * **Pre-Conditions:**@n
 * - Indicator HAL must be initialized and gINDICATORHandle must be valid@n
 * - The supported states must be correctly configured in the profile@n
 *
 * **Dependencies:**@n
 * - gINDICATORHandle must be valid@n
 *
 * **User Interaction:** None@n
 *
 * **Test Procedure:**@n
 * | Step | Action | Input | Expected Result | Remarks |
 * |01|Call getCapabilities() API|N/A|Returns a Capabilities object|Mandatory step|
 * |02|Verify that the number of supported states matches the profile count|IIndicator.supportedStates|caps.supportedStates.size() == profile count|Ensures all configured states are returned|
 * |03|Verify each supported state from profile is present in caps.supportedStates|Profile entry string -> enum (stringToState)|All profile states exist in caps.supportedStates|Logs a mismatch if any state is missing|
 */
UT_ADD_TEST(VTS_L1_INDICATOR, getCapablities_pos)
{
    com::rdk::hal::indicator::Capabilities caps;
    bool result = true;
    INDICATOR_GET_CAPABILITIES(gINDICATORHandle, caps);

    size_t supportedCount = UT_KVP_PROFILE_GET_LIST_COUNT("IIndicator.supportedStates");
    UT_ASSERT_EQUAL(caps.supportedStates.size(), supportedCount);

    for (size_t i = 0; i < supportedCount; i++) 
    {
        std::string key_string = "IIndicator.supportedStates." + std::to_string(i);
        char states[256] = {0};
        UT_KVP_PROFILE_GET_STRING(key_string.c_str(), states);
        if (states[0] != '\0') 
        {
            com::rdk::hal::indicator::State stateEnum = stringToState(states);
            if (!(std::find(caps.supportedStates.begin(), caps.supportedStates.end(), stateEnum) != caps.supportedStates.end())) 
            {
                UT_LOG_INFO("State %s mismatch in supported list\n", states);
                result = false;
                break;
            }
        }
    }
    UT_ASSERT_TRUE(result);
    return;
}

/**
 * @brief L1 Positive Test for the Indicator HAL get() API
 *
 * This test verifies that the HAL correctly returns the current indicator state.
 *
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 002@n
 * **Priority:** High@n
 *
 * **Pre-Conditions:**@n
 * - Indicator HAL must be initialized and gINDICATORHandle must be valid@n
 *
 * **Dependencies:**@n
 * - gINDICATORHandle must be valid@n
 *
 * **User Interaction:** None@n
 *
 * **Test Procedure:**@n
 * |Step|Description|Test Data|Expected Result|Notes|
 * |----|-----------|---------|---------------|-----|
 * |01  |Call get() API|N/A|Returns the current indicator state|Mandatory step|
 * |02  |Verify returned state|getState|Should be ERROR_UNKNOWN|Default initial state|
 */
UT_ADD_TEST(VTS_L1_INDICATOR, get_pos)
{
    com::rdk::hal::indicator::State getState;
    
    INDICATOR_GET(gINDICATORHandle, getState);
    UT_ASSERT_EQUAL(getState, com::rdk::hal::indicator::State::ERROR_UNKNOWN);
    return;
}

/**
 * @brief L1 Positive Test for the Indicator HAL set() API
 *
 * This test verifies that the HAL correctly sets all supported indicator states.
 *
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 003@n
 * **Priority:** High@n
 *
 * **Pre-Conditions:**@n
 * - Indicator HAL must be initialized and gINDICATORHandle must be valid@n
 * - Capabilities must be retrieved successfully via getCapabilities() API@n
 *
 * **Dependencies:**@n
 * - gINDICATORHandle must be valid@n
 *
 * **User Interaction:** None@n
 *
 * **Test Procedure:**@n
 * |Step|Description|Test Data|Expected Result|Notes|@n
 * |----|-----------|---------|---------------|-----|@n
 * |01  |Retrieve capabilities|N/A|Caps object returned with supported states|Mandatory step|@n
 * |02  |Loop through supported states and call set()|caps.supportedStates|All set() calls succeed|Skips index 0 if initial state is ERROR_UNKNOWN|@n
 */
UT_ADD_TEST(VTS_L1_INDICATOR, set_pos)
{
    bool result = false;
    
    com::rdk::hal::indicator::Capabilities caps;
    INDICATOR_GET_CAPABILITIES(gINDICATORHandle, caps);

    for(size_t i = 1; i < caps.supportedStates.size(); i++) 
    {
        INDICATOR_SET(gINDICATORHandle, caps.supportedStates[i], result);
        UT_ASSERT_TRUE(result);
    }
    return;
}

/**
 * @brief L1 Negative Test for the Indicator HAL set() API
 *
 * This test verifies that the HAL correctly rejects unsupported or invalid states.
 *
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 004@n
 * **Priority:** High@n
 *
 * **Pre-Conditions:**@n
 * - Indicator HAL must be initialized and gINDICATORHandle must be valid@n
 *
 * **Dependencies:**@n
 * - gINDICATORHandle must be valid@n
 *
 * **User Interaction:** None@n
 *
 * **Test Procedure:**@n
 * |Step|Description|Test Data|Expected Result|Notes|@n
 * |----|-----------|---------|---------------|-----|@n
 * |01  |Attempt to set BOOT state|State::BOOT|set() returns false|BOOT state is not allowed|@n
 * |02  |Attempt to set ERROR_UNKNOWN state|State::ERROR_UNKNOWN|set() returns false|ERROR_UNKNOWN state is not allowed|@n
 * |03  |Attempt to set an invalid state outside enum|static_cast<State>(400)|set() returns false|Invalid enum value rejected|@n
 */
 UT_ADD_TEST(VTS_L1_INDICATOR, set_neg)
{
    bool result = false;
 
    INDICATOR_SET(gINDICATORHandle, com::rdk::hal::indicator::State::BOOT, result);
    UT_ASSERT_FALSE(result);

    INDICATOR_SET(gINDICATORHandle, com::rdk::hal::indicator::State::ERROR_UNKNOWN, result);
    UT_ASSERT_FALSE(result);

    INDICATOR_SET(gINDICATORHandle, static_cast<com::rdk::hal::indicator::State>(400), result);
    UT_ASSERT_FALSE(result);
    
    return;
}
 
 
 /**
 * @} // End of indicator_HALTEST_CLASS
 * @} // End of indicator_HALTEST
 * @} // End of indicator
 * @} // End of HPK
 */
 /* End of vts_indicator_l1_tests.cpp */