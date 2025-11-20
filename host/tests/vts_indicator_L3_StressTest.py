#!/usr/bin/env python3
#** *****************************************************************************
# *
# * If not stated otherwise in this file or this component's LICENSE file the
# * following copyright and licenses apply:
# *
# * Copyright 2024 RDK Management
# *
# * Licensed under the Apache License, Version 2.0 (the "License");
# * you may not use this file except in compliance with the License.
# * You may obtain a copy of the License at
# *
# *
# http://www.apache.org/licenses/LICENSE-2.0
# *
# * Unless required by applicable law or agreed to in writing, software
# * distributed under the License is distributed on an "AS IS" BASIS,
# * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# * See the License for the specific language governing permissions and
# * limitations under the License.
# *
#* ******************************************************************************

import os
import sys
import time
import threading

dir_path = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.join(dir_path, "../"))

from raft.framework.plugins.ut_raft.configRead import ConfigRead
from raft.framework.core.logModule import logModule
from raft.framework.plugins.ut_raft import utHelperClass
from raft.framework.plugins.ut_raft.utSuiteNavigator import UTSuiteNavigatorClass
from raft.framework.plugins.ut_raft.utBaseUtils import utBaseUtils
from vts_indicator_helper import indicatorHelperClass

INDICATOR_L3_TEST_SUITE_NAME = "VTS_L3_INDICATOR"

class  VTS_INDICATOR_L3_StressTest(indicatorHelperClass):
    """
    Runs L3 ReceiveMessage test
    """
    def __init__(self, log:logModule=None):
        """
        Initializes the test class
        """
        self.testName = "Indicator_L3_StressTest"
        qcId = "2"
        
        super().__init__(self.testName, qcId, log)

    
    def updateTestconfigurationFile(self, set_state:str, states_list:list, stress:bool):
        """
        Updates the HDMI CEC L3 ReceiveMessage YAML configuration file.
        """

        data = self.indicatorReadYaml(self.l3TestConfigFile)
        config_statelist = data["Indicator"]["L3"]["SetStates"]["Parameters"]["state"]
        repeat_count = 1

        if stress:
            config_statelist.clear()
            for states in states_list:
                if states == "BOOT":
                    continue

                if states == False:
                    states = "OFF"

                config_statelist.append(states)
        else:
            config_statelist.clear()
            config_statelist.append(str(set_state))
            data["Indicator"]["L3"]["SetStates"]["Parameters"]["repeat"] = repeat_count

        # write to YAML
        self.indicatorWriteYaml(self.l3TestConfigFile, data)

    def testVerifyState(self, state:str, pattern:str, color:str, timing:str, manual=False):

        if manual == True and timing:
            return self.testUserResponse.getUserYN(f"Is the pattern {pattern} and color {color} of the Indicator state {state} active on the device for time period {timing}? (Y/N):")
        elif manual == True:
            return self.testUserResponse.getUserYN(f"Is the pattern {pattern} and color {color} of the Indicator state {state} active on the device? (Y/N):")
        else :
            return False

    def testFunction(self):
        """
        The main test function to run the L3 Stress Test.

        Returns:
            bool: Final result of the test.
        """
        self.utilities.change_directory(self.hal_session, self.targetWorkspace)
        results = False
        self.testcase = "SetStates"

        self.profileConfiguration = ConfigRead(self.moduleHFPFile, self.profile_moduleName)
        supported_states = self.profileConfiguration.supportedStates

        self.platformLEDConfiguration = ConfigRead(self.PlatformLEDConfigFile, self.moduleName)
        led_config = self.platformLEDConfiguration.States

        # First, run the stress test with all supported states
        self.updateTestconfigurationFile("", supported_states, True)

        self.utilities.sftpCopy(self.hal_session, self.l3TestConfigFile, self.l3TestConfigFolder)

        self.utMenu.start()

        self.log.stepStart(f'Test Suit: {INDICATOR_L3_TEST_SUITE_NAME} Test Case: {self.testcase}')

        output = self.utMenu.select(INDICATOR_L3_TEST_SUITE_NAME, self.testcase, None, self.waitTime, False)

        results = self.utMenu.collect_results(output, True)

        self.log.stepResult(results, f'Test Suit: {INDICATOR_L3_TEST_SUITE_NAME} Test Case: {self.testcase}')

        # Iterate through each supported state and validate after Stress test
        for state in supported_states:

            if state == "BOOT":
                continue
            
            if state == False:
                state = "OFF"

            self.updateTestconfigurationFile(state, [], False)

            self.utilities.sftpCopy(self.hal_session, self.l3TestConfigFile, self.l3TestConfigFolder)

            self.utMenu.start()

            self.log.stepStart(f'Test Suit: {INDICATOR_L3_TEST_SUITE_NAME} Test Case: {self.testcase}')
            output = self.utMenu.select(INDICATOR_L3_TEST_SUITE_NAME, self.testcase, None, self.waitTime, False)

            results = self.utMenu.collect_results(output, True)

            if led_config is not None:
                state_info = led_config.get(state)
                pattern = state_info.get("pattern")
                color = state_info.get("color")
                timing = state_info.get("timing")

                result = self.testVerifyState(state, pattern, color, timing, True)
                self.log.stepResult(result, f'Test Suit: {INDICATOR_L3_TEST_SUITE_NAME} Test Case: {self.testcase}')
            else:
                self.log.stepResult(False, f'State {state} is not present in platform config unable to validate')

        return result

if __name__ == '__main__':
    summaryLogName = os.path.splitext(os.path.basename(__file__))[0] + "_summery"
    summaryLog  = logModule(summaryLogName, level=logModule.INFO)
    test = VTS_INDICATOR_L3_StressTest(summaryLog )
    test.run(False)
