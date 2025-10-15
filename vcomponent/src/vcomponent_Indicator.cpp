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

/* 
* @brief 
* vcomponent_Indicator.cpp
* Implementation of the Indicator service implementation
*/

#include "vcomponent_Indicator.h"
#include "vcomponent_Indicator_parse_config.h"
#include <regex>

namespace com
{
    namespace rdk
    {
        namespace hal
        {
            namespace indicator
            {

                Indicator::Indicator()
                {
                }
                Indicator::~Indicator()
                {
                }

                ::android::binder::Status Indicator::getCapabilities(Capabilities *_aidl_return)
                {
                    if (!_aidl_return)
                    {
                        return android::binder::Status::fromExceptionCode(android::binder::Status::EX_ILLEGAL_ARGUMENT);
                    }
                    *_aidl_return = Capabilities();
                    _aidl_return->supportedStates.push_back(::com::rdk::hal::indicator::State::BOOT);
                    _aidl_return->supportedStates.push_back(::com::rdk::hal::indicator::State::ACTIVE);
                    _aidl_return->supportedStates.push_back(::com::rdk::hal::indicator::State::STANDBY);
                    _aidl_return->supportedStates.push_back(::com::rdk::hal::indicator::State::OFF);
                    _aidl_return->supportedStates.push_back(::com::rdk::hal::indicator::State::DEEP_SLEEP);
                    _aidl_return->supportedStates.push_back(::com::rdk::hal::indicator::State::WPS_CONNECTING);
                    _aidl_return->supportedStates.push_back(::com::rdk::hal::indicator::State::WPS_CONNECTED);
                    _aidl_return->supportedStates.push_back(::com::rdk::hal::indicator::State::WPS_ERROR);
                    _aidl_return->supportedStates.push_back(::com::rdk::hal::indicator::State::WPS_SES_OVERLAP);
                    _aidl_return->supportedStates.push_back(::com::rdk::hal::indicator::State::WIFI_ERROR);
                    _aidl_return->supportedStates.push_back(::com::rdk::hal::indicator::State::IP_ACQUIRED);
                    _aidl_return->supportedStates.push_back(::com::rdk::hal::indicator::State::NO_IP);
                    _aidl_return->supportedStates.push_back(::com::rdk::hal::indicator::State::FULL_SYSTEM_RESET);
                    _aidl_return->supportedStates.push_back(::com::rdk::hal::indicator::State::USB_UPGRADE);
                    _aidl_return->supportedStates.push_back(::com::rdk::hal::indicator::State::SOFTWARE_DOWNLOAD_ERROR);
                    _aidl_return->supportedStates.push_back(::com::rdk::hal::indicator::State::PSU_FAILURE);
                    return ::android::binder::Status::ok();
                }
                
                ::android::binder::Status Indicator::set(State state, bool* _aidl_return) {
                    if (!_aidl_return) return ::android::binder::Status::fromExceptionCode(
                        ::android::binder::Status::EX_NULL_POINTER);
                
                    //mCurrentState = state;
                    if(state == State::BOOT || state == State::ERROR_UNKNOWN)
                    {
                        *_aidl_return = false;
                        mCurrentState == State::ERROR_UNKNOWN;
                    }
                    else
                    {
                        *_aidl_return = true;
                        mCurrentState = state;
                    }
                
                    return ::android::binder::Status::ok();
                }
                
                ::android::binder::Status Indicator::get(State* _aidl_return) {
                    if (!_aidl_return) return ::android::binder::Status::fromExceptionCode(
                        ::android::binder::Status::EX_NULL_POINTER);
                
                    *_aidl_return = mCurrentState;
                    return ::android::binder::Status::ok();
                }
                

                void Indicator::binderDied(const ::android::wp<::android::IBinder> &who)
                {
                    // Handle binder death if necessary
                }
    

            } // namespace indicator
        } // namespace hal
    } // namespace rdk
} // namespace com