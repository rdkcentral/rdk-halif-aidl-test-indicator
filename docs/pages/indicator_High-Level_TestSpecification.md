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

| Test | Description | Validation Method |
|------|-------------|-------------------|
| General States Validation | Set each supported state (`BOOT`, `ACTIVE`, `STANDBY`, `OFF`, `DEEP_SLEEP`) one by one and verify that the corresponding indicator behavior matches the platform specification. | Observe hardware indicators (LED color, blink pattern, panel display). |
| WPS Workflow Validation | Set `WPS_CONNECTING` → `WPS_CONNECTED`. Confirm LEDs/panel reflect Wi-Fi onboarding patterns. | External Wi-Fi AP and LED observation. |
| Network Connectivity Indication | Set `WIFI_ERROR`, `IP_ACQUIRED`, and `NO_IP`. Verify hardware indicator reflects connectivity condition. | Network setup tool and hardware observation. |
| System Operation & Maintenance | Set `FULL_SYSTEM_RESET`, `USB_UPGRADE`, `SOFTWARE_DOWNLOAD_ERROR`. Validate indicator reflects upgrade/reset states. | USB injection and LED monitoring. |
| Vendor Extension Validation | If platform defines states ≥ USER_DEFINED_BASE (e.g., `VOICE_MODE_ACTIVE`), verify indicator follows documented vendor-specific behavior. | Observe hardware behavior |
| Enforcement of Read-Only States | Set reserved states like `BOOT` and `ERROR_UNKNOWN`. HAL must reject these. | Observe hardware behavior |
| Stress & Endurance | Cycle through all supported states listed in `indicator.yaml` for extended duration. Verify no stuck indicators, drift, or crash. | continuous monitoring on state toggle. |
