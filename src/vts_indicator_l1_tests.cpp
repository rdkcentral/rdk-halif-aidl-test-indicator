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
 #include "com/rdk/hal/indicator/IIndicatorManager.h" 
 #include "ut_log.h"
 
 extern sp<IIndicatorManager> gINDICATORHandle;
 
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
 * @brief Validates that the Indicator HAL returns all configured indicator instance IDs.
 *
 * This test ensures that:
 * - getIndicatorIds() returns a non-empty list of IDs.
 * - Each returned ID matches the IDs defined in the KVP profile (indicator.instances).
 *
 * **Test Group ID:** 01@n
 * **Test Case ID:** 001@n
 * **Priority:** High@n
 *
 * **Pre-Conditions:**@n
 * - Indicator HAL must be initialized and gINDICATORHandle must be valid@n
 * - The indicator instance IDs must be correctly configured in the profile@n
 *
 * **Dependencies:**@n
 * - gINDICATORHandle must be valid@n
 *
 * **User Interaction:** None@n
 *
 * **Test Procedure:**@n
 * | Step | Action | Input | Expected Result | Remarks |
 * |01|Call getIndicatorIds() API|N/A|Returns a list of IDs|Mandatory step|
 * |02|Verify that number of IDs matches profile count|indicator.instances|Returned IDs count == profile count|Ensures all configured instances are discovered|
 * |03|Verify each returned ID matches the profile|Profile IDs|All IDs exist in returned list|Logs mismatch if any ID is missing|
 */

UT_ADD_TEST(VTS_L1_INDICATOR, getIndicatorIds_pos)
{   
    std::vector<com::rdk::hal::indicator::IIndicator::Id> indicatorIds;
    INDICATOR_GET_INDICATORIDS(gINDICATORHandle, indicatorIds);

    size_t supportedCount = UT_KVP_PROFILE_GET_LIST_COUNT("indicator.instances");
    UT_ASSERT_EQUAL(indicatorIds.size(), supportedCount);

    // Validate each ID against config
    for (size_t i = 0; i < supportedCount; ++i)
    {
        std::string idKey = "indicator.instances/" + std::to_string(i) + "/Id";
        int expectedId = UT_KVP_PROFILE_GET_UINT8(idKey.c_str());

        bool found = false;
        for (const auto& id : indicatorIds)
        {
            if (id.value == expectedId)
            {
                found = true;
                break;
            }
        }
        
        UT_ASSERT_TRUE(found);
    }

    return;
}


/**
 * @brief Validates that a valid indicator instance can be retrieved.
 *
 * This test ensures that:
 * - getIndicator() returns a non-null IIndicator object for a valid ID.
 *
 * **Test Group ID:** 01@n
 * **Test Case ID:** 002@n
 * **Priority:** High@n
 *
 * **Pre-Conditions:**@n
 * - Indicator HAL must be initialized and gINDICATORHandle must be valid@n
 * - At least one indicator instance must be configured@n
 *
 * **Dependencies:**@n
 * - gINDICATORHandle must be valid@n
 *
 * **User Interaction:** None@n
 *
 * **Test Procedure:**@n
 * | Step | Action | Input | Expected Result | Remarks |
 * |01|Call getIndicatorIds() API|N/A|Returns a list of IDs|Mandatory step|
 * |02|For each ID, call getIndicator()|Each ID|Returns non-null IIndicator object|Validates instance retrieval|
 * |03|Verify returned object is non-null|N/A|IIndicator object is valid|Ensures valid instance is returned|

 */
UT_ADD_TEST(VTS_L1_INDICATOR, getIndicator_pos)
{
    std::vector<com::rdk::hal::indicator::IIndicator::Id> indicatorIds;

    // Step 1: Discover instances
    INDICATOR_GET_INDICATORIDS(gINDICATORHandle, indicatorIds);

    UT_ASSERT_TRUE(indicatorIds.size() > 0);

    // Step 2: For each ID, fetch indicator handle
    for (const auto& id : indicatorIds)
    {
        android::sp<com::rdk::hal::indicator::IIndicator> indicatorObj = nullptr;

        INDICATOR_GET_INDICATOR(gINDICATORHandle, id, indicatorObj);

        UT_LOG_INFO("Validating indicator handle for ID=%d", id.value);

        // Each valid ID must return a valid binder object
        UT_ASSERT_TRUE(indicatorObj != nullptr);
    }
}

/**
 * @brief Validates that getIndicator() handles invalid IDs safely.
 *
 * This test ensures that:
 * - Passing an invalid ID returns null and does not crash.
 *
 * **Test Group ID:** 01@n
 * **Test Case ID:** 003@n
 * **Priority:** Medium@n
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
 * | Step | Action | Input | Expected Result | Remarks |
 * |01|Call getIndicatorIds() API|N/A|Returns a list of IDs|Mandatory step|
 * |02|Create invalid ID (max existing ID + 1)|List of IDs|Invalid ID created|Ensures ID is out of range|
 * |03|Call getIndicator() with invalid ID|Invalid ID|Returns null IIndicator object|Validates safe handling of invalid ID|
 * |04|Call getIndicator() with negative ID|-101|Returns null IIndicator object|Validates safe handling of negative ID| 
 */

UT_ADD_TEST(VTS_L1_INDICATOR, getIndicator_neg)
{
    std::vector<com::rdk::hal::indicator::IIndicator::Id> indicatorIds;
    INDICATOR_GET_INDICATORIDS(gINDICATORHandle, indicatorIds);
    UT_ASSERT_TRUE(indicatorIds.size() > 0);

    // Create invalid ID (not present in YAML instances) by taking max existing ID and adding 1
    com::rdk::hal::indicator::IIndicator::Id invalidId;
    android::sp<com::rdk::hal::indicator::IIndicator> indicatorObj = nullptr;

    auto maxIdValue = indicatorIds[0].value;
    for (const auto &id : indicatorIds)
    {
        if (id.value > maxIdValue)
        {
            maxIdValue = id.value;
        }
    }
    invalidId.value = maxIdValue + 1;

    // Test getIndicator with invalid ID
    INDICATOR_GET_INDICATOR_NEG(gINDICATORHandle, indicatorObj, invalidId);
    UT_ASSERT_TRUE(indicatorObj == nullptr);

    // Test getIndicator with with a negative ID
    invalidId.value = -101;
    INDICATOR_GET_INDICATOR_NEG(gINDICATORHandle, indicatorObj, invalidId);
    UT_ASSERT_TRUE(indicatorObj == nullptr);
}

/**
 * @brief Validates that getCapabilities() returns all configured supported states.
 *
 * This test ensures that:
 * - getCapabilities() returns a non-empty supportedStates list.
 * - All states defined in profile (indicator.supportedStates) exist in the returned Capabilities.
 *
 * **Test Group ID:** 01@n
 * **Test Case ID:** 004@n
 * **Priority:** High@n
 *
 * **Pre-Conditions:**@n
 * - Indicator HAL must be initialized and gINDICATORHandle must be valid@n
 * - At least one indicator instance must be configured@n
 *
 * **Dependencies:**@n
 * - gINDICATORHandle must be valid@n
 *
 * **User Interaction:** None@n
 *
 * **Test Procedure:**@n
 * | Step | Action | Input | Expected Result | Remarks |
 * |01|Call getIndicatorIds() API|N/A|Returns a list of IDs|Mandatory step|
 * |02|Retrieve each indicator instance|Each ID|Non-null IIndicator objects|Mandatory step|
 * |03|Call getCapabilities() for each instance|Indicator object|Returns Capabilities with supportedStates|Validates capabilities retrieval|
 * |04|Verify each supported state against profile|Profile states|All profile states exist in supportedStates|Ensures HAL reports all configured states|
  */
UT_ADD_TEST(VTS_L1_INDICATOR, getCapabilities_pos)
{
    android::sp<com::rdk::hal::indicator::IIndicatorManager> manager = gINDICATORHandle;
    std::vector<com::rdk::hal::indicator::IIndicator::Id> ids;
    INDICATOR_GET_INDICATORIDS(manager, ids);
    UT_ASSERT_TRUE(ids.size() > 0);

    for (const auto& id : ids)
    {
        android::sp<com::rdk::hal::indicator::IIndicator> indicatorObj = nullptr;
        INDICATOR_GET_INDICATOR(manager, id, indicatorObj);
        UT_ASSERT_TRUE(indicatorObj != nullptr);

        com::rdk::hal::indicator::Capabilities caps;
        INDICATOR_GET_CAPS(indicatorObj, caps);

        UT_ASSERT_TRUE(caps.supportedStates.size() > 0);
        UT_LOG_INFO("Indicator supports %zu state(s)", caps.supportedStates.size());

        size_t expectedCount = UT_KVP_PROFILE_GET_LIST_COUNT("indicator.supportedStates");
        UT_ASSERT_EQUAL(caps.supportedStates.size(), expectedCount);

        for (size_t i = 0; i < expectedCount; ++i)
        {
            std::string key = "indicator.supportedStates." + std::to_string(i);

            char stateBuf[UT_KVP_MAX_ELEMENT_SIZE] = {0};
            UT_KVP_PROFILE_GET_STRING(key.c_str(), stateBuf);

            android::String16 expectedState(stateBuf);

            bool found = false;
            for (const auto& state : caps.supportedStates)
            {
                if (state == expectedState)
                {
                    found = true;
                    break;
                }
            }
            
            UT_ASSERT_TRUE(found);
        }
    }
}

/**
 * @brief Validates that get() returns a valid current state.
 *
 * This test ensures that:
 * - get() returns a state string that exists in the indicator’s supported states.
 *
 * **Test Group ID:** 01@n
 * **Test Case ID:** 005@n
 * **Priority:** High@n
 *
 * **Pre-Conditions:**@n
 * - Indicator HAL must be initialized and gINDICATORHandle must be valid@n
 * - At least one indicator instance must be configured@n
 *
 * **Dependencies:**@n
 * - gINDICATORHandle must be valid@n
 *
 * **User Interaction:** None@n
 *
 * **Test Procedure:**@n
 * | Step | Action | Input | Expected Result | Remarks |
 * |01|Call getIndicatorIds() API|N/A|Returns list of IDs|Mandatory step|
 * |02|Retrieve each indicator instance|Each ID|Non-null IIndicator objects|Mandatory step|
 * |03|Call getCapabilities() for each instance|Indicator object|Obtain supported states|Mandatory step|
 * |04|Call get()|Indicator object|Returned state is in supportedStates|Ensures current state is valid|
 */

UT_ADD_TEST(VTS_L1_INDICATOR, getState_pos)
{
    android::sp<com::rdk::hal::indicator::IIndicatorManager> manager = gINDICATORHandle;
    android::String16 state;

    std::vector<com::rdk::hal::indicator::IIndicator::Id> ids;

    INDICATOR_GET_INDICATORIDS(manager, ids);
    UT_ASSERT_TRUE(ids.size() > 0);

    for (const auto& id : ids)
    {
        android::sp<com::rdk::hal::indicator::IIndicator> indicatorObj = nullptr;
        INDICATOR_GET_INDICATOR(manager, id, indicatorObj);
        UT_ASSERT_TRUE(indicatorObj != nullptr);

        com::rdk::hal::indicator::Capabilities caps;
        INDICATOR_GET_CAPS(indicatorObj, caps);
        UT_ASSERT_TRUE(caps.supportedStates.size() > 0);

        INDICATOR_GET_STATE_POS(indicatorObj, state);

        bool isSupported = false;

        for (const auto& supportedState : caps.supportedStates)
        {
            if (state == supportedState)
            {
                isSupported = true;
                break;
            }
        }
        UT_ASSERT_TRUE(isSupported);
    }
}

/**
 * @brief Validates that all supported states can be set successfully.
 *
 * This test ensures that:
 * - set() API can set each supported state returned by getCapabilities().
 * - No errors occur while setting supported states.
 *
 * **Test Group ID:** 01@n
 * **Test Case ID:** 006@n
 * **Priority:** High@n
 *
 * **Pre-Conditions:**@n
 * - Indicator HAL must be initialized and gINDICATORHandle must be valid@n
 * - At least one indicator instance must be configured@n
 *
 * **Dependencies:**@n
 * - gINDICATORHandle must be valid@n
 *
 * **User Interaction:** None@n
 *
 * **Test Procedure:**@n
 * | Step | Action | Input | Expected Result | Remarks |
 * |01|Call getIndicatorIds() API|N/A|Returns list of IDs|Mandatory step|
 * |02|Retrieve each indicator instance|Each ID|Non-null IIndicator objects|Mandatory step|
 * |03|Call getCapabilities()|Indicator object|Obtain supported states|Mandatory step|
 * |04|Call set() for each supported state|Supported state|Returns success|Validates HAL accepts all supported states|
 */
UT_ADD_TEST(VTS_L1_INDICATOR, setState_pos)
{
    android::sp<com::rdk::hal::indicator::IIndicatorManager> manager = gINDICATORHandle;
    std::vector<com::rdk::hal::indicator::IIndicator::Id> ids;

    INDICATOR_GET_INDICATORIDS(manager, ids);
    UT_ASSERT_TRUE(ids.size() > 0);

    for (const auto& id : ids)
    {
        android::sp<com::rdk::hal::indicator::IIndicator> indicatorObj = nullptr;
        INDICATOR_GET_INDICATOR(manager, id, indicatorObj);
        UT_ASSERT_TRUE(indicatorObj != nullptr);

        com::rdk::hal::indicator::Capabilities caps;
        INDICATOR_GET_CAPS(indicatorObj, caps);
        UT_ASSERT_TRUE(caps.supportedStates.size() > 0);

        // Just set each supported state — no get() here
        for (const auto& state : caps.supportedStates)
        {
            INDICATOR_SET_STATE_POS(indicatorObj, state);
            UT_LOG_INFO("Indicator ID=%d, set state=%s succeeded", id.value, android::String8(state).string());
        }
    }
}


/**
 * @brief Validates that set() rejects invalid state strings.
 *
 * This test ensures that:
 * - set() fails when given an empty or invalid state string.
 *
 * **Test Group ID:** 01@n
 * **Test Case ID:** 007@n
 * **Priority:** Medium@n
 *
 * **Pre-Conditions:**@n
 * - Indicator HAL must be initialized and gINDICATORHandle must be valid@n
 * - At least one indicator instance must be configured@n
 *
 * **Dependencies:**@n
 * - gINDICATORHandle must be valid@n
 *
 * **User Interaction:** None@n
 *
 * **Test Procedure:**@n
 * | Step | Action | Input | Expected Result | Remarks |
 * |01|Call getIndicatorIds() API|N/A|Returns list of IDs|Mandatory step|
 * |02|Retrieve each indicator instance|Each ID|Non-null IIndicator objects|Mandatory step|
 * |03|Call set() with invalid state|Invalid state string|Returns failure|Validates HAL rejects invalid states|
 * |04|Call set() with empty string|""|Returns failure|Validates HAL rejects empty states|
 */
UT_ADD_TEST(VTS_L1_INDICATOR, setState_neg)
{
    android::sp<com::rdk::hal::indicator::IIndicatorManager> manager = gINDICATORHandle;
    std::vector<com::rdk::hal::indicator::IIndicator::Id> ids;
    INDICATOR_GET_INDICATORIDS(manager, ids);
    UT_ASSERT_TRUE(ids.size() > 0);

    for (const auto& id : ids)
    {
        android::sp<com::rdk::hal::indicator::IIndicator> indicatorObj = nullptr;
        INDICATOR_GET_INDICATOR(manager, id, indicatorObj);
        UT_ASSERT_TRUE(indicatorObj != nullptr);

        // Validating with an invalid state
        android::String16 invalidState("INVALID_STATE");
        INDICATOR_SET_STATE_NEG(indicatorObj, invalidState);

        // Validating with empty string
        android::String16 emptyInvalidState("");
        INDICATOR_SET_STATE_NEG(indicatorObj, emptyInvalidState);
    }
}

 /**
 * @} // End of indicator_HALTEST_CLASS
 * @} // End of indicator_HALTEST
 * @} // End of indicator
 * @} // End of HPK
 */
 /* End of vts_indicator_l1_tests.cpp */
