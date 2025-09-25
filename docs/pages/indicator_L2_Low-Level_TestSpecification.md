# Indicator Module L2 Low Level Test Specification and Procedure Documentation

## Table of Contents

- [Overview](#overview)
- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Definitions](#definitions)
- [References](#references)
- [Level 2 Test Procedure](#level-2-test-procedure)

## Overview

This document describes the Level 2 testing suite for the Indicator HAL module.  

### Acronyms, Terms and Abbreviations

- `HAL` – Hardware Abstraction Layer  
- `UT` – Unit Test(s)  
- `OEM` – Original Equipment Manufacturer  
- `SoC` – System on a Chip  

### Definitions

- `ut-core` – Common Testing Framework <https://github.com/rdkcentral/ut-core>, which wraps an open-source framework and can be extended for future requirements.

### References

- `High Level Test Specification` – [indicator_High-Level_TestSpecification.md](indicator_High-Level_TestSpecification.md)  

## Level 2 Test Procedure

The following functions validate correct operation of the Indicator HAL APIs.

### Test 1

| Title | Details |
| -- | -- |
| Function Name | `test_l2_IndicatorBaseTest_TestGetCapabilities` |
| Description | Call `getCapabilities()` and verify that the returned supported states match exactly with the ones listed in profile specification entries. |
| Test Group | Module : 01 |
| Test Case ID | 001 |
| Priority | High |

**Pre-Conditions :**  
None  

**Dependencies :**  
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Step | Description | Expected Result |
| -- | ----------- | ---------------- |
| 01 | Call `getCapabilities()` | Status is OK |
| 02 | Verify returned states list against profile specification entries | Lists must match exactly |

### Test 2

| Title | Details |
| -- | -- |
| Function Name | `test_l2_IndicatorBaseTest_TestGeneralStates` |
| Description | Call `set()` for each general state (`ACTIVE`, `STANDBY`, `OFF`, `DEEP_SLEEP`) and verify correctness using `get()`. |
| Test Group | Module : 01 |
| Test Case ID | 002 |
| Priority | High |

**Pre-Conditions :**  
None  

**Dependencies :**  
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Step | Description | Expected Result |
| -- | ----------- | ---------------- |
| 01 | Call `set(ACTIVE)` | Status is OK |
| 02 | Call `get()` and verify state = `ACTIVE` | State matches |
| 03 | Call `set(STANDBY)` | Status is OK |
| 04 | Call `get()` and verify state = `STANDBY` | State matches |
| 05 | Call `set(OFF)` | Status is OK |
| 06 | Call `get()` and verify state = `OFF` | State matches |
| 07 | Call `set(DEEP_SLEEP)` | Status is OK |
| 08 | Call `get()` and verify state = `DEEP_SLEEP` | State matches |

### Test 3

| Title | Details |
| -- | -- |
| Function Name | `test_l2_IndicatorBaseTest_TestWPSStates` |
| Description | Call `set()` for each WPS state (`WPS_CONNECTING`, `WPS_CONNECTED`, `WPS_ERROR`, `WPS_SES_OVERLAP`) and verify correctness using `get()`. |
| Test Group | Module : 01 |
| Test Case ID | 003 |
| Priority | High |

**Pre-Conditions :**  
None  

**Dependencies :**  
States must be supported by the platform.
(None)

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Step | Description | Expected Result |
| -- | ----------- | ---------------- |
| 01 | Call `set(WPS_CONNECTING)` | Status is OK |
| 02 | Call `get()` and verify state = `WPS_CONNECTING` | State matches |
| 03 | Repeat steps for `WPS_CONNECTED`, `WPS_ERROR`, `WPS_SES_OVERLAP` | All transitions succeed |
| 04 | Call `set(WPS_CONNECTED)` | Status is OK |
| 05 | Call `get()` and verify state = `WPS_CONNECTED` | State matches |
| 06 | Call `set(WPS_ERROR)` | Status is OK |
| 07 | Call `get()` and verify state = `WPS_ERROR` | State matches |
| 08 | Call `set(WPS_SES_OVERLAP)` | Status is OK |
| 09 | Call `get()` and verify state = `WPS_SES_OVERLAP` | State matches |

### Test 4

| Title | Details |
| -- | -- |
| Function Name | `test_l2_IndicatorBaseTest_TestNetworkStates` |
| Description | Call `set()` for network-related states (`WIFI_ERROR`, `IP_ACQUIRED`, `NO_IP`) and verify correctness using `get()`. |
| Test Group | Module : 01 |
| Test Case ID | 004 |
| Priority | Medium |

**Pre-Conditions :**  
None  

**Dependencies :**  
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Step | Description | Expected Result |
| -- | ----------- | ---------------- |
| 01 | Call `set(WIFI_ERROR)` | Status is OK |
| 02 | Call `get()` and verify state = `WIFI_ERROR` | State matches |
| 03 | Call `set(IP_ACQUIRED)` | Status is OK |
| 04 | Call `get()` and verify state = `IP_ACQUIRED` | State matches |
| 05 | Call `set(NO_IP)` | Status is OK |
| 06 | Call `get()` and verify state = `NO_IP` | State matches |

### Test 5

| Title | Details |
| -- | -- |
| Function Name | `test_l2_IndicatorBaseTest_TestSystemMaintenanceStates` |
| Description | Call `set()` for system maintenance states (`FULL_SYSTEM_RESET`, `USB_UPGRADE`, `SOFTWARE_DOWNLOAD_ERROR`, `PSU_FAILURE`) and verify correctness using `get()`. |
| Test Group | Module : 01 |
| Test Case ID | 005 |
| Priority | Medium |

**Pre-Conditions :**  
None  

**Dependencies :**  
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Step | Description | Expected Result |
| -- | ----------- | ---------------- |
| 01 | Call `set(FULL_SYSTEM_RESET)` | Status is OK |
| 02 | Call `get()` and verify state = `FULL_SYSTEM_RESET` | State matches |
| 03 | Call `set(USB_UPGRADE)` | Status is OK |
| 04 | Call `get()` and verify state = `USB_UPGRADE` | State matches |
| 05 | Call `set(SOFTWARE_DOWNLOAD_ERROR)` | Status is OK |
| 06 | Call `get()` and verify state = `SOFTWARE_DOWNLOAD_ERROR` | State matches |
| 07 | Call `set(PSU_FAILURE)` | Status is OK |
| 08 | Call `get()` and verify state = `PSU_FAILURE` | State matches |
