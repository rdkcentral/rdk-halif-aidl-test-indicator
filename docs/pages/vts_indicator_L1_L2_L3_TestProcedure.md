# Indicator L1, L2, L3 Test Procedure

## Table of Contents
- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Build the VTS](#build-the-vts)
- [Run L1 L2 Tests Without Python](#run-l1-l2-test-without-python)
- [Run Tests in Python Environment](#run-tests-in-python-environment)
  - [Update Configuration Files](#update-configuration-files)
  - [Install the Python Packages](#install-the-python-packages)
  - [Run the Tests](#run-test-cases)
- [Notes](#note)

## Acronyms, Terms and Abbreviations

- `HAL`    - Hardware Abstraction Layer
- `VTS`    - Vendor Test Suite
- `L1`     - Level 1 Testing
- `L2`     - Level 2 Testing
- `L3`     - Level 3 Testing
- `DUT`    - Device Under Test
- `RAFT`   - Rapid Automation Framework for Testing
- `YAML`   - YAML Ain't Markup Language
- `AIDL`   - Android Interface Definition Language

## Build the VTS

### Build Linux binder

The test suite depends on the Linux binder with `AIDL` support. Follow these steps to build it:

For detailed build instructions, please refer to [Linux Binder](https://github.com/rdkcentral/linux_binder_idl/tree/1.0.0)

Here are the simplest steps outlined:

```bash
git clone -b develop 'https://github.com/rdkcentral/linux_binder_idl.git'

cd linux_binder_idl

./build-linux-binder-aidl.sh 64
```

### Build VTS binaries

Clone and build the test suite:

```bash
git clone git@github.com:rdkcentral/rdk-halif-aidl-test-indicator.git
```

```bash
cd rdk-halif-aidl-test-indicator
```

Set the following environment variables:

- AIDL_BIN: Path to the `AIDL` compiler (e.g., /path/to/linux_binder_idl/out/aidl).

- LINUX_BINDER_OUT_DIR: Path to the Linux binder output directory (e.g., /path/to/linux_binder_idl/local).

- UT_CORE_VERSION: Specific version of the UT-Core framework (e.g., 4.7.0). Defaults to the latest tagged version.

- VCOMPONENT_INDICATOR_VERSION: Specific version of the INDICATOR Virtual Component (e.g., 0.1.0). Defaults to the latest HEAD.

- RDK_HALIF_AIDL_VERSION: Specific version of the AIDL HAL Specification (e.g., 0.12.0). Defaults to the latest HEAD.

Example:

```bash
export UT_CORE_VERSION=4.7.3
export RDK_HALIF_AIDL_VERSION=0.12.0
export VCOMPONENT_INDICATOR_VERSION=0.1.0
export AIDL_BIN=/path/to/linux_binder_idl/out/aidl
export LINUX_BINDER_OUT_DIR=/path/to/linux_binder_idl/local/
```

By default, `UT` logs are disabled. To enable them, set the following environment variable:

```bash
export ENABLE_UT_INFO_LOGGING=1
```

Run the build script:

```bash
./build.sh Target=<Target-name>

# Supported Targets: linux, arm
```

The build.sh script:

- Clones the `rdk-halif-aidl` repository and UT-Core framework.
- Compiles the test suite.
- Generates binaries in the `build/bin` directory.
- Generates tar file `vts-Indicator.tar.gz` in the `build/bin` directory.

## Run L1 L2 Test Without Python

### Transfer Tar File to Target Device

Copy the `vts` binaries (`vts-Indicator.tar.gz`) to the target device (e.g., using `scp`):

```bash
scp -P <port> vts-Indicator.tar.gz root@target-device:/tmp/
```

### Extract on Target Device

Log into the target device and extract the tarball:

```bash
ssh root@target-device
mkdir /tmp/Indicator
tar -zxf vts-Indicator.tar.gz -C /tmp/Indicator
cd /tmp/Indicator
```

### Run the VTS Test on Target Device

Run the following command to execute the VTS test:

```bash
./run.sh -p profiles/hfp-indicator_vcomponent.yaml
```

## Run Tests in Python Environment

### Update Configuration Files

#### Rack Configuration File

Example Rack configuration File: [vts_rack_configuration.yml](../../host/configs/vts_rack_configuration.yml)

For more details on rack configuration refer [RAFT](https://github.com/rdkcentral/python_raft/blob/1.7.1/README.md) and [example_rack_config.yml](https://github.com/rdkcentral/python_raft/blob/1.7.1/examples/configs/example_rack_config.yml)

In this file, update the configuration to define the console sessions for the `DUT` and the outbound settings:

|Console Session|Description|
|---------------|-----------|
|default|This session is used for basic operations, such as verifying the device status and retrieving the MAC address|
|ssh_hal_test|Executes the `HAL` binary for the test case|
|ssh_hal_test_1|Console to control device|

```yaml
rackConfig:
    rack1:
        name: "rack1"
        description: "example config at my desk"
        slot1:
            name: "slot1"
            devices:
                - dut:
                    ip: ""  # IP Address of the ADA Hub
                    description: "PC"
                    platform: "vDevice"
                    consoles:
                        - default:
                            type: "ssh"
                            port: 5522
                            username: "root"
                            ip: "" #IP address
                            password: ""
                            prompt: "~#" # Prompt string on console
                        - ssh_hal_test:
                            type: "ssh"
                            port: 5522
                            username: ""
                            ip: "" #IP address
                            password: ""
                            prompt: "~#" # Prompt string on console
                        - ssh_hal_test_1:
                            type: "ssh"
                            port: 5522
                            username: ""
                            ip: "" #IP address
                            password: ""
                            prompt: "~#" # Prompt string on console
                    outbound:
                        download_url: "tftp://tftp-server.com/rack1/slot1/"    # download location for the CPE device
                        upload_url: "sftp://server-address/home/workspace/tftp/rack1/slot1/" # upload location
                        upload_url_base_dir: "sftp://server-address/home/workspace/tftp/rack1/slot1" # alternative upload location
                        httpProxy:    # Local Proxy if required
                        workspaceDirectory: './logs/workspace'   # Local working directory
```

#### Device Configuration File

Example Device configuration File: [vts_device_configuration.yml](../../host/configs/vts_device_configuration.yml)

For more details refer [RAFT](https://github.com/rdkcentral/python_raft/blob/1.7.0/README.md) and [example_device_config.yml](https://github.com/rdkcentral/python_raft/blob/1.7.0/examples/configs/example_device_config.yml)

Ensure the `platform` should match with the `DUT` platform in [Rack Configuration](#rack-configuration-file)

```yaml
deviceConfig:
    cpe1:
        platform:   "vDevice"
        model:      "VTV"
        soc_vendor: "intel"
        target_directory: "/tmp/"
        indicator_process_name: "Vendor-Indicator"
        prompt: "~#" # Prompt string on console
        wait_time: 240 #Configurable timeout value to limit the total duration of individual tests
        test:
            profile: "../../profiles/hfp-indicator_vcomponent.yaml" #HFP profile used to meet platform requirements
            platform_led_config: "../../test_configuration/vts_indicator_LED_config_vdevice.yaml"
```

### Install the Python Packages

[host](../../host/) folder contains the script files to install required packages and set up the Python environment.

- Run install.sh once to create the virtual environment
- source activate_venv.sh
- Run install.sh again to install dependencies inside the environment.

Run the following commands:

```bash
./install.sh
source activate_venv.sh
./install.sh
```

For more details refer [Python Set up](https://github.com/rdkcentral/ut-raft/wiki/Guide-for-Setting-up-the-Python-RAFT-Testing-Suite) and [Raft Setup](https://github.com/rdkcentral/python_raft/?tab=readme-ov-file#installation)

### Run Test Cases

#### L1 and L2

Once the environment is set up, execute the test cases with the following command:

```bash
python vts_indicator_L1_L2_tests.py --config </PATH>/host/tests/configs/vts_rack_configuration.yaml --deviceConfig </PATH>/host/tests/configs/vts_device_configuration.yaml
```

#### L3

##### Device Setup

###### vDevice

For vDevice, no external hardware needs to be connected to the setup.

###### Real Device

The setup for real-device testing involves using the DUT’s built-in physical indicators (LEDs). No additional external hardware modules are needed for Indicator L3 tests.

The user must ensure:

   - The DUT is powered on and accessible.
   - All physical indicators on the DUT are unobstructed and visible.
   - The indicator subsystem (HAL/service) is functional before starting the test.
   - Manual visual verification of indicator states may be required during final validation steps.

##### Run Tests

Once the environment is set up, execute the test cases with the following command:

```bash
python <testcase>.py --config </PATH>/host/tests/configs/vts_rack_configuration.yaml --deviceConfig </PATH>/host/tests/configs/vts_device_configuration.yaml
```

### L3 Test Cases

#### Set States Test — `vts_indicator_L3_SetStates.py`

**Path:** [vts_indicator_L3_SetStates.py](../../host/tests/vts_indicator_L3_SetStates.py)

**Purpose:** Validates that the `DUT` can successfully sets the Indicator states and that the `HAL` generates the correct callbacks and metrics.

**Test Flow:**
- Copy the VTS binaries to the target device.
- Set all supported indicator states.
- Verify that:
  - Whether requested state is got set using `get()` method.
  - For the respective state check manually whether the LED colour, pattern status is got generated in `DUT`,
  and provide (y/n).

#### Stress Test — `vts_indicator_L3_StressTest.py`

**Path:** [vts_indicator_L3_StressTest.py](../../host/tests/vts_indicator_L3_StressTest.py)

**Purpose:**
Validates the robustness of the Indicator HAL by continuously toggling the indicator state and reading it back over an extended number of iterations, as defined in the configuration file. This test ensures that repeated state transitions do not lead to failures, unexpected behavior, or HAL instability.

**Test Flow:**

- Copy the `VTS` binaries to the target device.
- Confirm the DUT indicators are in a known, stable initial state.
- Stress Loop Execution:
    - For each iteration from 1 → repeat_count:
       - Set the indicator to a target state (e.g., ON/OFF/BLINK).
       - Validate the current state via HAL `get()` API.
       - Log mismatches or failures immediately.
- Post-Loop Validation:
    - After completing all iterations, perform final state verification for all indicator types once.
    - Confirm the indicator reflects the expected state.
    - For the respective state check manually whether the LED colour, pattern status is got generated in`DUT`,
  and provide (y/n).
    - Ensure no system errors, crashes, or HAL failures occurred during the stress cycle.

## Note

### Test Setup on vDevice

To validate automation on vDevice, create a password for the root user using the following command:

```bash
passwd root
```

Then, update the same password in the `vts_rack_configuration.yaml` file.

Currently, the Python `paramiko` library does not support empty passwords on vDevice, so setting a password is necessary.

### Run on Windows Environment

To run the Python environment tests in a Windows environment, follow these additional steps after checking out the repository and compiling the code:

1. Install the python environment and update the rack configuration files as in the Linux environment.

2. Move the entire project folder (including `host`) to the Windows machine.

3. Open the file located at `framework/plugins/ut_raft/interactive_shell.py`.

   - Comment out or remove the following import lines to avoid errors on Windows:
     ```python
     import pty
     import fcntl
     ```

4. After these changes, run the test cases using Python on the Windows system.