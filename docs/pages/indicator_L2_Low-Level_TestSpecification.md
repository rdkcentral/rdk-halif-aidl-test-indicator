# Indicator L2 Low Level Test Specification and Procedure Documentation

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
| Function Name | `test_GeneralStates` |
| Description | Validate General State handling for all supported indicators. The test first retrieves all indicator IDs using `getIndicatorIds()`, obtains each indicator instance, and queries its supported capabilities using `getCapabilities()`. For every supported General state, the test calls `set()` followed by `get()` to verify the state change. |
| Test Group | 02 |
| Test Case ID | 001 |
| Priority | High |

**Pre-Conditions :**  
None  

**Dependencies :**  
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Variation / Steps | Description | Test Data | Expected Result | Notes |
| ----------------- | ----------- | --------- | --------------- | ----- |
| 1 | Obtain Indicator service handle | None | Valid handle acquired | Ensure service is initialized |
| 2 | Retrieve indicator IDs using `getIndicatorIds()` | None | List of IDs returned | Multiple indicator instances possible |
| 3 | For each indicator ID, retrieve indicator instance | ID from Step 2 | Non-null indicator object | Test must run per instance |
| 4 | For current indicator instance, get supported capabilities using `getCapabilities()` | Indicator object | Supported General states obtained | Determines valid states for that instance |
| 5 | If `ACTIVE` is supported, call `set()` | state = ACTIVE | Status is OK | Skip if not supported for this instance |
| 6 | Call `get()` | None | Returned state = ACTIVE | Only if Step 5 executed |
| 7 | If `STANDBY` is supported, call `set()` | state = STANDBY | Status is OK | Skip if not supported for this instance |
| 8 | Call `get()` | None | Returned state = STANDBY | Only if Step 7 executed |
| 9 | If `OFF` is supported, call `set()` | state = OFF | Status is OK | Skip if not supported for this instance |
| 10 | Call `get()` | None | Returned state = OFF | Only if Step 9 executed |
| 11 | If `DEEP_SLEEP` is supported, call `set()` | state = DEEP_SLEEP | Status is OK | Skip if not supported for this instance |
| 12 | Call `get()` | None | Returned state = DEEP_SLEEP | Only if Step 11 executed |
| 13 | Repeat Steps 4–12 for the next indicator instance | Next ID | All supported states validated | Ensures full multi-instance coverage |

### Test 2

| Title | Details |
| -- | -- |
| Function Name | `test_WPSStates` |
| Description | Validate WPS state handling for all supported indicator instances. The test retrieves all indicator IDs using `getIndicatorIds()`, obtains each indicator instance, and queries its supported capabilities using `getCapabilities()`. For every supported WPS state, the test calls `set()` followed by `get()` to verify the state transition. |
| Test Group | 02 |
| Test Case ID | 002 |
| Priority | High |

**Pre-Conditions :**  
None  

**Dependencies :**  
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Variation / Steps | Description | Test Data | Expected Result | Notes |
| ----------------- | ----------- | --------- | --------------- | ----- |
| 1 | Obtain Indicator service handle | None | Valid handle acquired | Ensure service is initialized |
| 2 | Retrieve indicator IDs using `getIndicatorIds()` | None | List of IDs returned | Multiple indicator instances possible |
| 3 | For each indicator ID, retrieve indicator instance | ID from Step 2 | Non-null indicator object | Test must run per instance |
| 4 | For current indicator instance, get supported capabilities using `getCapabilities()` | Indicator object | Supported WPS states obtained | Determines valid states for that instance |
| 5 | If `WPS_CONNECTING` is supported, call `set()` | state = WPS_CONNECTING | Status is OK | Skip if not supported for this instance |
| 6 | Call `get()` | None | Returned state = WPS_CONNECTING | Only if Step 5 executed |
| 7 | If `WPS_CONNECTED` is supported, call `set()` | state = WPS_CONNECTED | Status is OK | Skip if not supported for this instance |
| 8 | Call `get()` | None | Returned state = WPS_CONNECTED | Only if Step 7 executed |
| 9 | If `WPS_ERROR` is supported, call `set()` | state = WPS_ERROR | Status is OK | Skip if not supported for this instance |
| 10 | Call `get()` | None | Returned state = WPS_ERROR | Only if Step 9 executed |
| 11 | If `WPS_SES_OVERLAP` is supported, call `set()` | state = WPS_SES_OVERLAP | Status is OK | Skip if not supported for this instance |
| 12 | Call `get()` | None | Returned state = WPS_SES_OVERLAP | Only if Step 11 executed |
| 13 | Repeat Steps 4–12 for the next indicator instance | Next ID | All supported WPS states validated | Ensures full multi-instance coverage |

### Test 3

| Title | Details |
| -- | -- |
| Function Name | `test_NetworkStates` |
| Description | Validate Network state handling for all supported indicator instances. The test retrieves all indicator IDs using `getIndicatorIds()`, obtains each indicator instance, and queries its supported capabilities using `getCapabilities()`. For every supported Network state, the test calls `set()` followed by `get()` to verify the state transition. |
| Test Group | 02 |
| Test Case ID | 003 |
| Priority | High |

**Pre-Conditions :**  
None  

**Dependencies :**  
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Variation / Steps | Description | Test Data | Expected Result | Notes |
| ----------------- | ----------- | --------- | --------------- | ----- |
| 1 | Obtain Indicator service handle | None | Valid handle acquired | Ensure service is initialized |
| 2 | Retrieve indicator IDs using `getIndicatorIds()` | None | List of IDs returned | Multiple indicator instances possible |
| 3 | For each indicator ID, retrieve indicator instance | ID from Step 2 | Non-null indicator object | Test must run per instance |
| 4 | For current indicator instance, get supported capabilities using `getCapabilities()` | Indicator object | Supported Network states obtained | Determines valid states for that instance |
| 5 | If `WIFI_ERROR` is supported, call `set()` | state = WIFI_ERROR | Status is OK | Skip if not supported for this instance |
| 6 | Call `get()` | None | Returned state = WIFI_ERROR | Only if Step 5 executed |
| 7 | If `IP_ACQUIRED` is supported, call `set()` | state = IP_ACQUIRED | Status is OK | Skip if not supported for this instance |
| 8 | Call `get()` | None | Returned state = IP_ACQUIRED | Only if Step 7 executed |
| 9 | If `NO_IP` is supported, call `set()` | state = NO_IP | Status is OK | Skip if not supported for this instance |
| 10 | Call `get()` | None | Returned state = NO_IP | Only if Step 9 executed |
| 11 | Repeat Steps 4–10 for the next indicator instance | Next ID | All supported Network states validated | Ensures full multi-instance coverage |

### Test 4

| Title | Details |
| -- | -- |
| Function Name | `test_MaintenanceStates` |
| Description | Validate Maintenance state handling for all supported indicator instances. The test retrieves all indicator IDs using `getIndicatorIds()`, obtains each indicator instance, and queries its supported capabilities using `getCapabilities()`. For every supported Maintenance state, the test calls `set()` followed by `get()` to verify the state transition. |
| Test Group | 02 |
| Test Case ID | 004 |
| Priority | High |

**Pre-Conditions :**  
None  

**Dependencies :**  
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Variation / Steps | Description | Test Data | Expected Result | Notes |
| ----------------- | ----------- | --------- | --------------- | ----- |
| 1 | Obtain Indicator service handle | None | Valid handle acquired | Ensure service is initialized |
| 2 | Retrieve indicator IDs using `getIndicatorIds()` | None | List of IDs returned | Multiple indicator instances possible |
| 3 | For **each indicator ID**, retrieve indicator instance | ID from Step 2 | Non-null indicator object | Test must run per instance |
| 4 | For current indicator instance, get supported capabilities using `getCapabilities()` | Indicator object | Supported Maintenance states obtained | Determines valid states for that instance |
| 5 | If `FULL_SYSTEM_RESET` is supported, call `set()` | state = FULL_SYSTEM_RESET | Status is OK | Skip if not supported for this instance |
| 6 | Call `get()` | None | Returned state = FULL_SYSTEM_RESET | Only if Step 5 executed |
| 7 | If `USB_UPGRADE` is supported, call `set()` | state = USB_UPGRADE | Status is OK | Skip if not supported for this instance |
| 8 | Call `get()` | None | Returned state = USB_UPGRADE | Only if Step 7 executed |
| 9 | If `SOFTWARE_DOWNLOAD_ERROR` is supported, call `set()` | state = SOFTWARE_DOWNLOAD_ERROR | Status is OK | Skip if not supported for this instance |
| 10 | Call `get()` | None | Returned state = SOFTWARE_DOWNLOAD_ERROR | Only if Step 9 executed |
| 11 | If `PSU_FAILURE` is supported, call `set()` | state = PSU_FAILURE | Status is OK | Skip if not supported for this instance |
| 12 | Call `get()` | None | Returned state = PSU_FAILURE | Only if Step 11 executed |
| 13 | Repeat Steps 4–12 for the next indicator instance | Next ID | All supported Maintenance states validated | Ensures full multi-instance coverage |
