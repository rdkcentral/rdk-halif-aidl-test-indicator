#!/usr/bin/env python3
#** *****************************************************************************
# *
# * If not stated otherwise in this file or this component's LICENSE file the
# * following copyright and licenses apply:
# *
# * Copyright 2026 RDK Management
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
from typing import Optional, List

dir_path = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.join(dir_path, "../"))

from raft.framework.plugins.ut_raft.configRead import ConfigRead
from raft.framework.core.logModule import logModule
from raft.framework.plugins.ut_raft import utHelperClass
from raft.framework.plugins.ut_raft.utSuiteNavigator import UTSuiteNavigatorClass
from raft.framework.plugins.ut_raft.utBaseUtils import utBaseUtils
from vts_indicator_helper import indicatorHelperClass

INDICATOR_L3_TEST_SUITE_NAME = "VTS_L3_INDICATOR"

class  VTS_INDICATOR_L3_SetStates(indicatorHelperClass):
    """
    Runs L3 Set States test
    """
    def __init__(self, log:logModule=None, hfpfile:str=None, ledConfig:str=None, testMenuConfigFile=None, moduleName=None, artifactDirPath=None):
        """
        Initializes the test class
        """
        self.testName = "Indicator_L3_SetStates"
        qcId = "1"
        
        super().__init__(self.testName, qcId, log, hfpfile, ledConfig, testMenuConfigFile, moduleName, artifactDirPath)
        

    def testVerifyState(self, state:str, pattern:str, color: Optional[List[str]] = None, timing: Optional[List[int]] = None, 
        transition: Optional[List[str]] = None, manual=False):
        """
        Verifies the Indicator state on the device manually
        Args:
            state (str): The state to verify.
            pattern (str): The expected pattern of the indicator.
            color (str): The expected color of the indicator.
            timing (str): The expected timing of the indicator.
            transition (str): The expected transition of the indicator.
            manual (bool): If True, prompts the user for manual verification.
        Returns:
            bool: True if the state is verified, False otherwise.
        """

        color_str = ', '.join(color) if color else "none"
        timing_str = ', '.join(map(str, timing)) if timing else "none"
        transition_str = ', '.join(transition) if transition else "none"

        if self.platform == "vDevice":
            return True
        
        # Manual user verification
        if manual:
            if timing_str != "none" or transition_str != "none":
                prompt = (
                    f"Is the pattern '{pattern}' with colors [{color_str}], timing [{timing_str}] mSecs, "
                    f"and transition for the colors [{transition_str}] of the Indicator state '{state}' active on the device? (Y/N): "
                )
            else:
                prompt = (
                    f"Is the pattern '{pattern}' with colors [{color_str}] of the Indicator state '{state}' active on the device? (Y/N): "
                )
            return self.testUserResponse.getUserYN(prompt)

        # Default auto-fail if not manual and not vDevice
        return False

    def testFunction(self):
        """
        The main test function to run the L3 Indicator Set states.

        Returns:
            bool: Final result of the test.
        """
        self.utilities.change_directory(self.hal_session, self.targetWorkspace)
        results = False
        result = False
        self.testcase = "SetStates"
        
        self.profileConfiguration = ConfigRead(self.moduleHFPFile, self.profile_moduleName)
        supported_states = self.profileConfiguration.supportedStates

        self.platformLEDConfiguration = ConfigRead(self.PlatformLEDConfigFile, self.PlatformLEDModuleName)
        led_config = self.platformLEDConfiguration.States
        
        for state in supported_states:

            self.updateTestconfigurationFile(state, [], False)

            self.utilities.sftpCopy(self.hal_session, self.l3TestConfigFile, self.l3TestConfigFolder)

            self.utMenu.start()

            output = self.utMenu.select(INDICATOR_L3_TEST_SUITE_NAME, self.testcase, None, self.waitTime, False)

            results = self.utMenu.collect_results(output, True)

            self.log.stepResult(results, f'Test Suit: {INDICATOR_L3_TEST_SUITE_NAME} Test Case: {self.testcase}')

            self.log.stepStart(f'Test Suit: {INDICATOR_L3_TEST_SUITE_NAME} Validating_State: {state}')

            if led_config is not None:
                state_info = led_config.get(state)
                pattern = state_info.get("pattern")
                color = state_info.get("color")
                timing = state_info.get("timing")
                transition = state_info.get("transition")

                result = self.testVerifyState(state, pattern, color, timing, transition, True)
                self.log.stepResult(result, f'Test Suit: {INDICATOR_L3_TEST_SUITE_NAME} Test Case: {self.testcase}')
            else:
                self.log.stepResult(result, f'State {state} is not present in platform config unable to validate')

        return result

if __name__ == '__main__':
    summaryLogName = os.path.splitext(os.path.basename(__file__))[0] + "_summery"
    summaryLog  = logModule(summaryLogName, level=logModule.INFO)
    test = VTS_INDICATOR_L3_SetStates(summaryLog )
    test.run(False)
