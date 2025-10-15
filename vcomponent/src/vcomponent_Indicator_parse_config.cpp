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

indicatorConfiguration_t gindicatorConfiguration;

static std::string prefix;
static std::string key;

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

    indicatorConfiguration_t indc = {};

    // Example of reading a string value from the configuration file
    prefix = "indicator/supportedStates/";
    char value[256];
    memset(value, 0, sizeof(value));

    indc.boot = ut_kvp_getStringField(instance, (prefix + "BOOT").c_str(), value, sizeof(value));
    indc.active = ut_kvp_getStringField(instance, (prefix + "ACTIVE").c_str(), value, sizeof(value));
    indc.standby = ut_kvp_getStringField(instance, (prefix + "STANDBY").c_str(), value, sizeof(value));
    indc.off = ut_kvp_getStringField(instance, (prefix + "OFF").c_str(), value, sizeof(value));
    indc.deepsleep = ut_kvp_getStringField(instance, (prefix + "DEEP_SLEEP").c_str(), value, sizeof(value));
    indc.wpsConnecting = ut_kvp_getStringField(instance, (prefix + "WPS_CONNECTING").c_str(), value, sizeof(value));
    indc.wpsConnected = ut_kvp_getStringField(instance, (prefix + "WPS_CONNECTED").c_str(), value, sizeof(value));
    indc.wpsError = ut_kvp_getStringField(instance, (prefix + "WPS_ERROR").c_str(), value, sizeof(value));
    indc.wpsSesOverlap = ut_kvp_getStringField(instance, (prefix + "WPS_SES_OVERLAP").c_str(), value, sizeof(value));
    indc.wifiError = ut_kvp_getStringField(instance, (prefix + "WIFI_ERROR").c_str(), value, sizeof(value));
    indc.ipAcquired = ut_kvp_getStringField(instance, (prefix + "IP_ACQUIRED").c_str(), value, sizeof(value));
    indc.noIP = ut_kvp_getStringField(instance, (prefix + "NO_IP").c_str(), value, sizeof(value));
    indc.fullSystemReset = ut_kvp_getStringField(instance, (prefix + "FULL_SYSTEM_RESET").c_str(), value, sizeof(value));
    indc.usbUpgrade = ut_kvp_getStringField(instance, (prefix + "USB_UPGRADE").c_str(), value, sizeof(value));
    indc.softwareDownloadError = ut_kvp_getStringField(instance, (prefix + "SOFTWARE_DOWNLOAD_ERROR").c_str(), value, sizeof(value));
    indc.psuFailure = ut_kvp_getStringField(instance, (prefix + "PSU_FAILURE").c_str(), value, sizeof(value));

    gindicatorConfiguration = indc;
    
    vcomponent_indicator_kvp_destroy_instance(instance);
}

