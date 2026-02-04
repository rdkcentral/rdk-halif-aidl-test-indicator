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
 * @defgroup INDICATOR_HALTEST_CLASS INDICATOR HAL Tests initialization source File
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
 * @file vts_indicator_init.cpp
 *
 */

 #include "vts_indicator_init.h"
 #include "ut_log.h"
 
 #include "com/rdk/hal/indicator/IIndicatorManager.h"
 
 #include <binder/IServiceManager.h>
 #include <binder/IBinder.h>
 #include <binder/ProcessState.h>
 #include <utils/String16.h>
 #include <utils/StrongPointer.h>
 
 using android::sp;
 using android::String16;
 using android::defaultServiceManager;
 using android::binder::Status;
 
 using namespace com::rdk::hal;
 using namespace com::rdk::hal::indicator;
 
 sp<IIndicatorManager> gINDICATORHandle = nullptr;
 
 static UT_status_t vts_indicator_getService()
 {
     gINDICATORHandle = android::interface_cast<IIndicatorManager>(
         defaultServiceManager()->getService(String16(IIndicatorManager::serviceName().c_str())));
 
     if (gINDICATORHandle == nullptr)
     {
         UT_LOG_ERROR("Failed to get Indicator service");
         return UT_STATUS_FAILURE;
     }
     UT_LOG_INFO("Successfully obtained Indicator service");
     return UT_STATUS_OK;
 }
 
 UT_status_t VTS_INDICATOR_init()
 {
     if(vts_indicator_getService() != UT_STATUS_OK)
     {
         UT_LOG_ERROR("Failed to get Indicator Service");
         return UT_STATUS_FAILURE;
     }
 
     return UT_STATUS_OK;
 }
 
 void VTS_INDICATOR_destroy()
 {
     UT_LOG_INFO("Destroying VTS_INDICATOR...");
     // De-initialization code goes here
 }
 
 /** @} */ // End of INDICATOR_HALTEST_CLASS
 /** @} */ // End of INDICATOR_HALTEST
 /** @} */ // End of INDICATOR
 /** @} */ // End of HPK
 
 // End of vts_indicator_init.cpp