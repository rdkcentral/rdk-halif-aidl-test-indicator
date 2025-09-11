# Indicator HAL High Level Test Specification Document

## Table of Contents

- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Introduction](#introduction)
- [Module Description](#module-description)
- [L2 Test Specification](#l2-test-specification)
- [L3 Test Specification](#l3-test-specification)


## Acronyms, Terms and Abbreviations

- `HAL`    - Hardware Abstraction Layer  
- `API`    - Application Programming Interface  
- `AIDL`   - Android Interface Definition Language  
- `L2`     - Level 2 Testing  
- `L3`     - Level 3 Testing  
- `HFP`    - HAL Feature Profile
- `LED`    - Light Emitting Diode  
- `PSU`    - Power Supply Unit  
- `WPS`    - Wi-Fi Protected Setup  


## Introduction

This document provides an overview of the testing requirements for the Indicator `HAL` module. It outlines the scope of testing, objectives, testing levels and approaches, and specific test requirements.

- Indicator Interface Definitions - [Indicator HAL](https://github.com/rdkcentral/rdk-halif-aidl/tree/current/indicator/current/com/rdk/hal/indicator)  
- Indicator `HAL` Feature Profile - [hfp-indicator.yaml](https://github.com/rdkcentral/rdk-halif-aidl/tree/current/indicator/current/hfp-indicator.yaml)


## Module Description

The Indicator `HAL` defines an abstraction layer for controlling device visual indicators (e.g., LEDs, panels) to signal system states to end users. It exposes an interface to query supported capabilities and to set or get the current indicator state.  

The `HAL` supports a predefined set of mutually exclusive persistent states (e.g., `BOOT`, `ACTIVE`, `WPS_CONNECTING`, `PSU_FAILURE`) that reflect system conditions. These states are represented as an enum (`State`) and must be supported according to the platform's `HAL` Feature Profile (HFP).


## L2 Test Specification

| Test | Description | HAL APIs |
|------|-------------|----------|
| Get Supported Capabilities | Call `getCapabilities()` and verify returned states match the ones listed in `hfp-indicator.yaml`. | `getCapabilities()` |
| Set and Get – General States | Set and get each general state (e.g., `ACTIVE`, `STANDBY`, `OFF`, `DEEP_SLEEP`). Verify the response of `get()` matches the set state. | `set()`, `get()` |
| Set and Get – WPS States | Verify states like `WPS_CONNECTING`, `WPS_CONNECTED`, `WPS_ERROR`, `WPS_SES_OVERLAP`. Ensure proper setting and reading. | `set()`, `get()` |
| Set and Get – Network States | Test network-related states: `WIFI_ERROR`, `IP_ACQUIRED`, `NO_IP`. Validate correctness. | `set()`, `get()` |
| Set and Get – System Maintenance States | Validate system operational states like `FULL_SYSTEM_RESET`, `USB_UPGRADE`, `SOFTWARE_DOWNLOAD_ERROR`, `PSU_FAILURE`. | `set()`, `get()` |


## L3 Test Specification

| Test | Description | HAL APIs |
|------|-------------|----------|
| Full-State Lifecycle Validation | Set each supported state and verify the state transition via `get()`. Confirm hardware behavior (e.g., LED change) if applicable. | `set()`, `get()` |
| State Exclusivity Check | Ensure only one state is active at a time. Set a new state and verify previous one is overwritten. | `set()`, `get()` |
| Enforcement of Read-Only States | Attempt to set reserved states like `BOOT` and `ERROR_UNKNOWN`. HAL must reject these. | `set()`, `get()` |
| Sequential Transition Validation | Perform ordered transitions between valid states (e.g., `ACTIVE → STANDBY → OFF`) and confirm HAL consistency. | `set()`, `get()` |
| Vendor Extension State Testing | For platforms supporting vendor states (≥ 1000), test setting and getting those states if they are declared in HFP. | `set()`, `get()`, `getCapabilities()` |
| Stress and Loop Testing | Repeatedly set and get all supported states in a loop. Check for memory issues, crashes, or incorrect state. | `set()`, `get()` |
| Fault and Error Visual Verification | Set fault states (e.g., `WPS_ERROR`, `SOFTWARE_DOWNLOAD_ERROR`) and check if visual indicator behavior aligns with spec. | `set()`, `get()` |
