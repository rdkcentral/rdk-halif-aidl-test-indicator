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
#include <thread>

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
        
                   _aidl_return->supportedStates = gIndicatorConfig.supportedStatesValues;

                    return ::android::binder::Status::ok();
                }
                
                ::android::binder::Status Indicator::set(State state, bool* _aidl_return) 
                {
                    if (!_aidl_return) return ::android::binder::Status::fromExceptionCode(
                        ::android::binder::Status::EX_NULL_POINTER);
                
                    mCurrentState = state;
                    if(mCurrentState != State::BOOT && mCurrentState != State::ERROR_UNKNOWN)
                    {
                        *_aidl_return = true;
                    }
                    else
                    {
                        *_aidl_return = false;
                    }
                
                    return ::android::binder::Status::ok();
                }
                
                ::android::binder::Status Indicator::get(State* _aidl_return) 
                {
                    if (!_aidl_return)
                    {
                        return ::android::binder::Status::fromExceptionCode(
                            ::android::binder::Status::EX_NULL_POINTER);
                    }
                
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