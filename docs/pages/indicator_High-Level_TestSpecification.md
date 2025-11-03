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

- Indicator Interface Definitions - [Indicator HAL](https://github.com/rdkcentral/rdk-halif-aidl/tree/main/indicator/current/com/rdk/hal/indicator)
- Indicator `HAL` Feature Profile - [hfp-indicator.yaml](https://github.com/rdkcentral/rdk-halif-aidl/blob/main/indicator/current/hfp-indicator.yaml)


## Module Description

The Indicator `HAL` defines an abstraction layer for controlling device visual indicators (e.g., LEDs, panels) to signal system states to end users. It exposes an interface to query supported capabilities and to set or get the current indicator state.  

The `HAL` supports a predefined set of states (e.g., `BOOT`, `ACTIVE`, `WPS_CONNECTING`, `PSU_FAILURE`) that reflect system conditions. 


## L2 Test Specification

| Test | Description | HAL APIs |
|------|-------------|----------|
| Set and Get – General States | Set and get each general state (`ACTIVE`, `STANDBY`, `OFF`, `DEEP_SLEEP`). Verify the response of `get()` matches the set state. | `set()`, `get()` |
| Set and Get – WPS States |Set and get each WPS-related states `WPS_CONNECTING`, `WPS_CONNECTED`, `WPS_ERROR`, `WPS_SES_OVERLAP`. Verify the response of `get()` matches the set state. | `set()`, `get()` |
| Set and Get – Network States | Set and get each network-related states: `WIFI_ERROR`, `IP_ACQUIRED`, `NO_IP`. Verify the response of `get()` matches the set state. | `set()`, `get()` |
| Set and Get – System Maintenance States | Set and get each system operational states `FULL_SYSTEM_RESET`, `USB_UPGRADE`, `SOFTWARE_DOWNLOAD_ERROR`, `PSU_FAILURE`. Verify the response of `get()` matches the set state.| `set()`, `get()` |


## L3 Test Specification

| Test | Description | Validation Method |
|------|-------------|-------------------|
| General States Validation | Set each supported state (`ACTIVE`, `STANDBY`, `OFF`, `DEEP_SLEEP`) and verify that the corresponding indicator behavior matches the platform specification. | Observe hardware indicators (LED color, blink pattern, panel display). |
| WPS States Validation | Set `WPS_CONNECTING`, `WPS_CONNECTED`, `WPS_ERROR`, `WPS_SES_OVERLAP` and verify corresponding LED patterns. | Validate LED patterns. |
| Network Connectivity Indication | Set `WIFI_ERROR`, `IP_ACQUIRED`, and `NO_IP` and verify LED patterns. | Validate LED patterns. |
| System Operation & Maintenance | Set `FULL_SYSTEM_RESET`, `USB_UPGRADE`, `SOFTWARE_DOWNLOAD_ERROR` and verify LED patterns. | Validate LED patterns. |
| Vendor Extension Validation | If platform defines states ≥ USER_DEFINED_BASE (e.g., `VOICE_MODE_ACTIVE`), verify indicator follows documented vendor-specific behavior. | Validate LED patterns. |
| Enforcement of Read-Only States | Use automation to reboot the device and validate LED pattern for `BOOT`. For `ERROR_UNKNOWN`, simulate or trigger an error condition and validate LED behavior. | Validate LED patterns. |
| Stress & Endurance | Cycle through all supported states for extended duration. Verify no stuck indicators, drift, or crash. | Continuous monitoring on state toggle. |
