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
            // android::ProcessState::self()->startThreadPool();
        }
    
        void TearDown() override
        {
        }
 };
 
 // Test case for getCapabilities, set, and get positive scenarios
 UT_ADD_TEST(VTS_L1_INDICATOR, l1_getCaps_pos)
 {
    com::rdk::hal::indicator::Capabilities caps;
    INDICATOR_GET_CAPABILITIES(gINDICATORHandle, caps);
    UT_ASSERT_EQUAL(caps.supportedStates.size(), 
                    UT_KVP_PROFILE_GET_LIST_COUNT("IIndicator.supportedStates"));
    return;
}

UT_ADD_TEST(VTS_L1_INDICATOR, l1_set_pos)
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

UT_ADD_TEST(VTS_L1_INDICATOR, l1_get_pos)
{
    bool result = false;
    com::rdk::hal::indicator::State getState;
    INDICATOR_SET(gINDICATORHandle, com::rdk::hal::indicator::State::ACTIVE, result);
    UT_ASSERT_TRUE(result);
    INDICATOR_GET(gINDICATORHandle, getState);
    UT_ASSERT_EQUAL(getState, com::rdk::hal::indicator::State::ACTIVE);
    return;
}

// Test case for set negative scenarios
 UT_ADD_TEST(VTS_L1_INDICATOR, l1_set_neg)
{
    bool result = false;
 
    INDICATOR_SET(gINDICATORHandle, com::rdk::hal::indicator::State::BOOT, result);
    UT_ASSERT_FALSE(result);

    INDICATOR_SET(gINDICATORHandle, com::rdk::hal::indicator::State::ERROR_UNKNOWN, result);
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