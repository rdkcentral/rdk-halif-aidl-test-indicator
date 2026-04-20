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
 #include <string>
 #include <sstream>
 #include <chrono>
 #include <thread>
 #include <com/rdk/hal/indicator/BpIndicator.h>
 #include <com/rdk/hal/indicator/BpIndicatorManager.h>
 #include <com/rdk/hal/indicator/Capabilities.h>
 #include <utils/String16.h>
 #include "vts_indicator_helper_functions.h"
 
 using android::sp;
 using android::String8;
 using com::rdk::hal::indicator::IIndicator;
 using com::rdk::hal::indicator::IIndicatorManager;
 using com::rdk::hal::indicator::Capabilities;

#define INDICATOR_GET_INDICATORIDS(indicatorHandle, indicatorIds) \
     do { \
         UT_ASSERT_TRUE((indicatorHandle) != nullptr); \
         ::android::binder::Status status; \
         UT_LOG_DEBUG("Calling getIndicatorIds(OUT:indicatorIds[])"); \
         status = (indicatorHandle)->getIndicatorIds(&(indicatorIds)); \
         UT_LOG_DEBUG("Result getIndicatorIds(OUT:indicatorIds[]), status:[isOK:%s, exception:%s]", \
            UT_Control_GetMapString(bool_mapTable_indicator, status.isOk()), \ 
            UT_Control_GetMapString(statusIndicatorException_mapTable, status.exceptionCode())); \
         UT_ASSERT_TRUE(status.isOk()); \
         UT_ASSERT_EQUAL(status.exceptionCode(), ::android::binder::Status::EX_NONE); \
         UT_LOG_DEBUG("IndicatorIds size %zu", indicatorIds.size()); \
     } while (0)

#define INDICATOR_GET_INDICATOR(indicatorHandle, indicatorId, indicatorObj) \
    do { \
        UT_ASSERT_TRUE((indicatorHandle) != nullptr); \
        ::android::binder::Status status; \
        UT_LOG_DEBUG("Calling getIndicator case, id=%d", indicatorId.value); \
        status = (indicatorHandle)->getIndicator(indicatorId, &(indicatorObj)); \
        UT_LOG_DEBUG("Result getIndicator, status:[isOK:%s, exception:%s]", \
            UT_Control_GetMapString(bool_mapTable_indicator, status.isOk()), \
            UT_Control_GetMapString(statusIndicatorException_mapTable, status.exceptionCode())); \
        UT_ASSERT_TRUE(status.isOk()); \
        UT_ASSERT_EQUAL(status.exceptionCode(), ::android::binder::Status::EX_NONE); \
    } while (0)

#define INDICATOR_GET_INDICATOR_NEG(indicatorHandle, indicatorObj, indicatorId) \
    do { \
        UT_ASSERT_TRUE((indicatorHandle) != nullptr); \
        ::android::binder::Status status; \
        UT_LOG_DEBUG("Calling getIndicator NEG (invalid ID), id=%d", indicatorId.value); \
        status = (indicatorHandle)->getIndicator(indicatorId, &indicatorObj); \
        UT_LOG_DEBUG("Result getIndicator NEG, status:[isOK:%s, exception:%s]", \
            UT_Control_GetMapString(bool_mapTable_indicator, status.isOk()), \
            UT_Control_GetMapString(statusIndicatorException_mapTable, status.exceptionCode())); \
        UT_ASSERT_TRUE(status.isOk()); \
        UT_ASSERT_EQUAL(status.exceptionCode(), ::android::binder::Status::EX_NONE); \
    } while (0)


#define INDICATOR_GET_CAPS(indicatorObj, capsObj) \
    do { \
        ::android::binder::Status status; \
        status = indicatorObj->getCapabilities(&capsObj); \
        UT_ASSERT_TRUE(status.isOk()); \
        UT_ASSERT_EQUAL(status.exceptionCode(), ::android::binder::Status::EX_NONE); \
        UT_ASSERT_TRUE(!capsObj.supportedStates.empty()); \
        UT_LOG_DEBUG("Capabilities returned: %zu states", capsObj.supportedStates.size()); \
    } while (0)

#define INDICATOR_SET_STATE_POS(indicatorObj, stateStr) \
    do { \
        bool success = false; \
        ::android::binder::Status status; \
        UT_LOG_DEBUG("Setting state='%s'", android::String8(stateStr).string()); \
        status = indicatorObj->set(stateStr, &success); \
        UT_ASSERT_TRUE(status.isOk()); \
        UT_ASSERT_EQUAL(status.exceptionCode(), ::android::binder::Status::EX_NONE); \
        UT_ASSERT_TRUE(success); \
    } while (0)

#define INDICATOR_GET_STATE_POS(indicatorObj, stateStr) \
    do { \
        ::android::binder::Status status; \
        status = indicatorObj->get(&stateStr); \
        UT_ASSERT_TRUE(status.isOk()); \
        UT_ASSERT_EQUAL(status.exceptionCode(), ::android::binder::Status::EX_NONE); \
        UT_ASSERT_TRUE(stateStr.size() > 0); \
        UT_LOG_DEBUG("Current state='%s'", android::String8(stateStr).string()); \
    } while (0)


#define INDICATOR_SET_STATE_NEG(indicatorObj, stateStr) \
    do { \
        bool success = false; \
        ::android::binder::Status status; \
        status = (indicatorObj)->set(stateStr, &success); \
        UT_ASSERT_TRUE(status.isOk()); \
        UT_ASSERT_EQUAL(status.exceptionCode(), ::android::binder::Status::EX_NONE); \
        UT_ASSERT_FALSE(success); \
        UT_LOG_INFO("NEG: set() failed as expected for state '%s'", android::String8(stateStr).string()); \
    } while (0)

 /**
  * @} // End of INDICATOR_HALTEST_CLASS
  * @} // End of INDICATOR_HALTEST
  * @} // End of INDICATOR
  * @} // End of HPK
  */
 /* End of vts_indicator.h */
