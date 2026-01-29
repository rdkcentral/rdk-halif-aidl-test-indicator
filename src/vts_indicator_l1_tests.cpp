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
  
UT_ADD_TEST(VTS_L1_INDICATOR, getIndicatorIds_pos)
{
    bool result = false;
    
    std::vector<com::rdk::hal::indicator::IIndicator::Id> indicatorIds;
    INDICATOR_GET_INDICATORIDS(gINDICATORHandle, indicatorIds);

    size_t supportedCount = UT_KVP_PROFILE_GET_LIST_COUNT("indicator.instances");
    UT_ASSERT_EQUAL(indicatorIds.size(), supportedCount);

    return;
}

UT_ADD_TEST(VTS_L1_INDICATOR, getIndicator_pos)
{
    std::vector<com::rdk::hal::indicator::IIndicator::Id> indicatorIds;

    // Step 1: Discover instances
    INDICATOR_GET_INDICATORIDS(gINDICATORHandle, indicatorIds);

    UT_ASSERT_TRUE(indicatorIds.size() > 0);

    // Step 2: Fetch first valid indicator
    android::sp<com::rdk::hal::indicator::IIndicator> indicatorObj = nullptr;

    INDICATOR_GET_INDICATOR(gINDICATORHandle, indicatorIds[0], indicatorObj);

    UT_LOG_DEBUG("getIndicator positive test passed");
}

UT_ADD_TEST(VTS_L1_INDICATOR, get_capabilities)
{
    android::sp<com::rdk::hal::indicator::IIndicatorManager> manager = gINDICATORHandle;
    std::vector<com::rdk::hal::indicator::IIndicator::Id> ids;
    INDICATOR_GET_INDICATORIDS(manager, ids);
    UT_ASSERT_TRUE(ids.size() > 0);

    android::sp<com::rdk::hal::indicator::IIndicator> indicatorObj = nullptr;
    INDICATOR_GET_INDICATOR(manager, ids[0], indicatorObj);
    UT_ASSERT_TRUE(indicatorObj != nullptr);

    com::rdk::hal::indicator::Capabilities caps;
    INDICATOR_GET_CAPS(indicatorObj, caps);

    UT_ASSERT_TRUE(caps.supportedStates.size() > 0);
    UT_LOG_INFO("Indicator supports %zu state(s)", caps.supportedStates.size());
}

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

        UT_ASSERT_EQUAL(state, caps.supportedStates[0]);

    }
}

UT_ADD_TEST(VTS_L1_INDICATOR, set_state_pos)
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

UT_ADD_TEST(VTS_L1_INDICATOR, setState_neg)
{
    android::sp<com::rdk::hal::indicator::IIndicatorManager> manager = gINDICATORHandle;
    std::vector<com::rdk::hal::indicator::IIndicator::Id> ids;
    INDICATOR_GET_INDICATORIDS(manager, ids);

    android::sp<com::rdk::hal::indicator::IIndicator> indicatorObj = nullptr;
    INDICATOR_GET_INDICATOR(manager, ids[0], indicatorObj);

    android::String16 invalidState("INVALID_STATE");
    INDICATOR_SET_STATE_NEG(indicatorObj, invalidState);
}
 
 /**
 * @} // End of indicator_HALTEST_CLASS
 * @} // End of indicator_HALTEST
 * @} // End of indicator
 * @} // End of HPK
 */
 /* End of vts_indicator_l1_tests.cpp */
