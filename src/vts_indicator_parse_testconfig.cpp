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
 * @defgroup INDICATOR_HALTEST_PARSE_TESTCONFIG Indicator HAL Tests parse test configuration file
 * @{
 * @parblock
 *
 * ### Parse test configuration functions for Indicator :
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
 * @file vts_indicator_parse_testconfig.cpp
 *
 */

#include "vts_indicator_parse_testconfig.h"

static void* vcomponentkvp_create_instance(char *fileName)
{
    ut_kvp_instance_t* instance;
    ut_kvp_status_t result;

    instance = ut_kvp_createInstance();

    if(!instance)
    {
        UT_LOG_ERROR("[VCOMPONENT_INDICATOR]Failed to create ut kvp instance");
        return nullptr;
    }

    result = ut_kvp_open(instance, fileName);

    if(result != UT_KVP_STATUS_SUCCESS)
    {
        UT_LOG_ERROR("[VCOMPONENT_INDICATOR]Failed to open test configuration file");
        ut_kvp_destroyInstance(instance);
        return nullptr;
    }

    return (ut_kvp_instance_t*)instance;
}

static void vcomponentkvp_destroy_instance(void *instance)
{
    ut_kvp_destroyInstance((ut_kvp_instance_t*)instance);
}


UT_status_t vts_indicator_parse_SetStates_config(char *configurationFile, const char *module, const char *testGroup,
                                                 const char *testName, std::vector<com::rdk::hal::indicator::State> &indicator_state, int32_t* repeat)
{
    char resultKVP[UT_KVP_MAX_ELEMENT_SIZE] = {0};
    int32_t statesSize = 0;

    void *testconfig = vcomponentkvp_create_instance(configurationFile);
    ut_kvp_instance_t* kvpTestInstance = (ut_kvp_instance_t*)testconfig;

    const std::string testNode = string(module) + "." + string(testGroup) + "." + string(testName);
    const std::string inputstatestr = testNode + ".Parameters" + ".state";
    const std::string repeat_value = testNode + ".Parameters" + ".repeat";

    *repeat = ut_kvp_getUInt32Field(kvpTestInstance, repeat_value.c_str());

    char states[UT_KVP_MAX_ELEMENT_SIZE] = {0};
    
    statesSize = ut_kvp_getListCount(kvpTestInstance, inputstatestr.c_str());

    if(statesSize > 0)
    {
        for (int32_t index = 0; index < statesSize; index++)
        {
            char states[UT_KVP_MAX_ELEMENT_SIZE] = {0};
            ut_kvp_getStringField(kvpTestInstance, (inputstatestr + "." + std::to_string(index)).c_str(),states, UT_KVP_MAX_ELEMENT_SIZE);
            indicator_state.push_back(fromString(states));
        }
    }
    else
    {
        UT_LOG_ERROR("Failed to parse message from test configuration");
        return UT_STATUS_FAILURE;
    }

    vcomponentkvp_destroy_instance(kvpTestInstance);
    return UT_STATUS_OK;
}



/** @} */ // End of INDICATOR_HALTEST_PARSE_TESTCONFIG
/** @} */ // End of INDICATOR_HALTEST
/** @} */ // End of INDICATOR
/** @} */ // End of HPK