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
 * @defgroup INDICATOR_HALTEST_HELPER INDICATOR HAL Tests helper functions
 * @{
 * @parblock
 *
 * ### Helper functions for VTS tests :
 *
 * Helper functions required for the module across all vendors.
 *
 * **Pre-Conditions:**  None @n
 * **Dependencies:** None @n
 *
 * @endparblock
 *
 */

/**
 * @file vts_indicator_helper_functions.cpp
 *
 */

#include "vts_indicator_helper_functions.h"

const ut_control_keyStringMapping_t bool_mapTable_indicator[] =
{
    {"false", (int32_t) false},
    {"true",  (int32_t) true},
    {NULL, -1}
};

std::string vecIntToString(std::vector<int32_t>& addrs)
{
    std::string s;
    for (size_t i = 0; i < addrs.size(); ++i)
    {
        s += std::to_string(addrs[i]);
        if (i != addrs.size() - 1) s += ", ";
    }
    return s;
}

const std::vector<std::pair<State, std::string>> stateMap = {
    {State::BOOT, "BOOT"},
    {State::ACTIVE, "ACTIVE"},
    {State::STANDBY, "STANDBY"},
    {State::OFF, "OFF"},
    {State::DEEP_SLEEP, "DEEP_SLEEP"},
    {State::WPS_CONNECTING, "WPS_CONNECTING"},
    {State::WPS_CONNECTED, "WPS_CONNECTED"},
    {State::WPS_ERROR, "WPS_ERROR"},
    {State::WPS_SES_OVERLAP, "WPS_SES_OVERLAP"},
    {State::WIFI_ERROR, "WIFI_ERROR"},
    {State::IP_ACQUIRED, "IP_ACQUIRED"},
    {State::NO_IP, "NO_IP"},
    {State::FULL_SYSTEM_RESET, "FULL_SYSTEM_RESET"},
    {State::USB_UPGRADE, "USB_UPGRADE"},
    {State::SOFTWARE_DOWNLOAD_ERROR, "SOFTWARE_DOWNLOAD_ERROR"},
    {State::PSU_FAILURE, "PSU_FAILURE"},
    {State::USER_DEFINED_BASE, "USER_DEFINED_BASE"},
};

//Converting State to string
std::string stateToString(State state) 
{
    for (const auto& [s, name] : stateMap) 
    {
        if (s == state) return name;
    }
    return "UNKNOWN_STATE";
}

// Converting string to State
State stringToState(const std::string& str) 
{
    for (const auto& [s, name] : stateMap) 
    {
        if (name == str) return s;
    }
    return State::ERROR_UNKNOWN;
}

std::string vecByteToHexString(const std::vector<uint8_t>& data)
{
    std::ostringstream oss;
    oss << std::uppercase << std::hex;  // uppercase hex letters
    for (size_t i = 0; i < data.size(); ++i)
    {
        oss << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]);
        if (i + 1 < data.size())
            oss << ",";
    }
    return oss.str();
}

/** @} */ // End of INDICATOR_HALTEST_HELPER
/** @} */ // End of INDICATOR_HALTEST
/** @} */ // End of INDICATOR
/** @} */ // End of HPK