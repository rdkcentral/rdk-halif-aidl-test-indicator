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
 * @defgroup INDICATOR_HALTEST_CLASS INDICATOR HAL Header File
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
 * @file vts_indicator.h
 *
 */

 #pragma once

 #include <ut.h>
 #include <ut_kvp_profile.h>
 #include <com/rdk/hal/indicator/BpIndicator.h>
 #include <com/rdk/hal/indicator/Capabilities.h>
 #include <utils/String16.h>
 //#include <com/rdk/hal/indicator/HALVersion.h>
 //#include <com/rdk/hal/indicator/SetPropertyResult.h>
 
 using android::sp;
 using android::String8;
 using com::rdk::hal::indicator::IIndicator;
 using com::rdk::hal::indicator::Capabilities;
 
 // Macro for getCapabilities - positive case
 #define INDICATOR_GET_CAPABILITIES(indicatorHandle, caps) \
     do { \
         ::android::binder::Status status; \
         UT_LOG_DEBUG("Calling getCapabilities(OUT:caps[])"); \
         status = (indicatorHandle)->getCapabilities(&caps); \
         UT_LOG_DEBUG("Result getCapabilities(OUT:caps), status:[isOK:%d, exception:%d]", status.isOk(), status.exceptionCode()); \
         UT_ASSERT_TRUE(status.isOk()); \
         UT_ASSERT_EQUAL(status.exceptionCode(), ::android::binder::Status::EX_NONE); \
         UT_LOG_DEBUG("Capabilities supportedStates size: %zu", caps.supportedStates.size()); \
     } while (0)
 
 /**
  * @} // End of INDICATOR_HALTEST_CLASS
  * @} // End of INDICATOR_HALTEST
  * @} // End of INDICATOR
  * @} // End of HPK
  */
 /* End of vts_indicator.h */