/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2024 RDK Management
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

/** @brief
* vcomponent_Indicator_parse_config.cpp
*
* Implementation of vcomponent Indicator driver
*/

#include "vcomponent_Indicator_parse_config.h"

static std::string prefix;
static std::string key;
indicatorConfiguration_t gIndicatorConfig = {};

static void* vcomponent_indicator_kvp_create_instance(char *fileName)
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

static void vcomponent_indicator_kvp_destroy_instance(void *instance)
{
    ut_kvp_destroyInstance((ut_kvp_instance_t*)instance);
}

void vcomponent_Indicator_parse_config(char *configurationFile)
{
    ut_kvp_instance_t* instance = (ut_kvp_instance_t*)vcomponent_indicator_kvp_create_instance(configurationFile);
    if(!instance)
    {
        UT_LOG_ERROR("[VCOMPONENT_INDICATOR]Failed to create kvp instance");
        return;
    }

    indicatorConfiguration_t devConfig = {};

    const std::vector<std::string> indicatorStates = {
        "BOOT", "ACTIVE", "STANDBY", "OFF", "DEEP_SLEEP",
        "WPS_CONNECTING", "WPS_CONNECTED", "WPS_ERROR", "WPS_SES_OVERLAP", "WIFI_ERROR",
        "IP_ACQUIRED", "NO_IP", "FULL_SYSTEM_RESET", "USB_UPGRADE", "SOFTWARE_DOWNLOAD_ERROR", "PSU_FAILURE"
    };

    prefix = "IIndicator/supportedStates/";

    for (const auto& state : indicatorStates) 
    {
        std::string fullPath = prefix + state;
        if (ut_kvp_fieldPresent(instance, fullPath.c_str())) 
        {
            uint32_t value = ut_kvp_getUInt32Field(instance, fullPath.c_str());
            UT_LOG_INFO("supportedStates value:%d", value);
            devConfig.supportedStatesValues.push_back(static_cast<::com::rdk::hal::indicator::State>(value));
        } 
        else 
        {
            UT_LOG_DEBUG("key not found in yaml, continue");
        }
      }

    gIndicatorConfig = devConfig;

    vcomponent_indicator_kvp_destroy_instance(instance);
}


