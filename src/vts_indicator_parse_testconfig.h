/**
 *  If not stated otherwise in this file or this component's LICENSE
 *  file the following copyright and licenses apply:
 *
 *  Copyright 2024 RDK Management
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
 * @defgroup INDICATOR_HALTEST_PARSE_TESTCONFIG_HEADER INDICATOR HAL Tests parse test configuration file
 * @{
 * @parblock
 *
 * ### Parse test configuration functions for INDICATOR :
 *
 * Parse configuration functions required for the module across all vendors.
 *
 * **Pre-Conditions:**  None @n
 * **Dependencies:** None @n
 *
 * @endparblock
 *
 */

/**
 * @file vts_indicator_parse_testconfig.h
 *
 */

#ifndef __VTS_INDICATOR_PARSE_TESTCONFIG_H__
#define __VTS_INDICATOR_PARSE_TESTCONFIG_H__

#include <ut.h>
#include <ut_log.h>
#include "ut_kvp_profile.h"
#include "vts_indicator.h"

using namespace std;

#define VTS_INDICATOR_TEST_CONFIG_PATH "./test_configuration/vts_l3_indicator.yaml"

UT_status_t vts_indicator_parse_SetStates_config(char *configurationFile, const char *module, const char *testGroup,
                                                 const char *testName, std::vector<com::rdk::hal::indicator::State> &indicator_state, uint32_t* repeat);
#endif //__VTS_INDICATOR_PARSE_TESTCONFIG_H__

/** @} */ // End of INDICATOR_HALTEST_PARSE_TESTCONFIG_HEADER
/** @} */ // End of INDICATOR_HALTEST
/** @} */ // End of INDICATOR
/** @} */ // End of HPK