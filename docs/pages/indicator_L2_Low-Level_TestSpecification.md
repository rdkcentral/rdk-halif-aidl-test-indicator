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
| Description | Call `set()` for each general state (`ACTIVE`, `STANDBY`, `OFF`, `DEEP_SLEEP`) and verify correctness using `get()`. |
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

| Variation / Steps | Description                             | Test Data          | Expected Result             | Notes |
| ----------------- | --------------------------------------- | ------------------ | --------------------------- | ----- |
| 1                 | Obtain Indicator service handle         | None               | Valid handle acquired            | Ensure service is initialized      |
| 2                 | Set state to `ACTIVE` using `set()`     | state = ACTIVE     | Status is OK                | -     |
| 3                 | Get current state using `get()`         | None               | Returned state = ACTIVE     | -     |
| 4                 | Set state to `STANDBY` using `set()`    | state = STANDBY    | Status is OK                | -     |
| 5                 | Get current state using `get()`         | None               | Returned state = STANDBY    | -     |
| 6                 | Set state to `OFF` using `set()`        | state = OFF        | Status is OK                | -     |
| 7                 | Get current state using `get()`         | None               | Returned state = OFF        | -     |
| 8                 | Set state to `DEEP_SLEEP` using `set()` | state = DEEP_SLEEP | Status is OK                | -     |
| 9                 | Get current state using `get()`         | None               | Returned state = DEEP_SLEEP | -     |

### Test 2

| Title | Details |
| -- | -- |
| Function Name | `test_WPSStates` |
| Description | Call `set()` for each WPS state (`WPS_CONNECTING`, `WPS_CONNECTED`, `WPS_ERROR`, `WPS_SES_OVERLAP`) and verify correctness using `get()`. |
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

| Variation / Steps | Description                                  | Test Data               | Expected Result                  | Notes |
| ----------------- | -------------------------------------------- | ----------------------- | -------------------------------- | ----- |
| 1                 | Obtain Indicator service handle         | None               | Valid handle acquired            | Ensure service is initialized      |
| 2                 | Set state to `WPS_CONNECTING` using `set()`  | state = WPS_CONNECTING  | Status is OK                     | -     |
| 3                 | Get current state using `get()`              | None                    | Returned state = WPS_CONNECTING  | -     |
| 4                 | Set state to `WPS_CONNECTED` using `set()`   | state = WPS_CONNECTED   | Status is OK                     | -     |
| 5                 | Get current state using `get()`              | None                    | Returned state = WPS_CONNECTED   | -     |
| 6                 | Set state to `WPS_ERROR` using `set()`       | state = WPS_ERROR       | Status is OK                     | -     |
| 7                 | Get current state using `get()`              | None                    | Returned state = WPS_ERROR       | -     |
| 8                 | Set state to `WPS_SES_OVERLAP` using `set()` | state = WPS_SES_OVERLAP | Status is OK                     | -     |
| 9                 | Get current state using `get()`              | None                    | Returned state = WPS_SES_OVERLAP | -     |

### Test 3

| Title | Details |
| -- | -- |
| Function Name | `test_NetworkStates` |
| Description | Call `set()` for network-related states (`WIFI_ERROR`, `IP_ACQUIRED`, `NO_IP`) and verify correctness using `get()`. |
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

| Variation / Steps | Description                              | Test Data           | Expected Result              | Notes |
| ----------------- | ---------------------------------------- | ------------------- | ---------------------------- | ----- |
| 1                 | Obtain Indicator service handle         | None               | Valid handle acquired            | Ensure service is initialized      |
| 2                 | Set state to `WIFI_ERROR` using `set()`  | state = WIFI_ERROR  | Status is OK                 | -     |
| 3                 | Get current state using `get()`          | None                | Returned state = WIFI_ERROR  | -     |
| 4                 | Set state to `IP_ACQUIRED` using `set()` | state = IP_ACQUIRED | Status is OK                 | -     |
| 5                 | Get current state using `get()`          | None                | Returned state = IP_ACQUIRED | -     |
| 6                 | Set state to `NO_IP` using `set()`       | state = NO_IP       | Status is OK                 | -     |
| 7                 | Get current state using `get()`          | None                | Returned state = NO_IP       | -     |

### Test 4

| Title | Details |
| -- | -- |
| Function Name | `test_MaintenanceStates` |
| Description | Call `set()` for system maintenance states (`FULL_SYSTEM_RESET`, `USB_UPGRADE`, `SOFTWARE_DOWNLOAD_ERROR`, `PSU_FAILURE`) and verify correctness using `get()`. |
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

| Variation / Steps | Description                                          | Test Data                       | Expected Result                          | Notes |
| ----------------- | ---------------------------------------------------- | ------------------------------- | ---------------------------------------- | ----- |
| 1                 | Obtain Indicator service handle         | None               | Valid handle acquired            | Ensure service is initialized      |
| 2                 | Set state to `FULL_SYSTEM_RESET` using `set()`       | state = FULL_SYSTEM_RESET       | Status is OK                             | -     |
| 3                 | Get current state using `get()`                      | None                            | Returned state = FULL_SYSTEM_RESET       | -     |
| 4                 | Set state to `USB_UPGRADE` using `set()`             | state = USB_UPGRADE             | Status is OK                             | -     |
| 5                 | Get current state using `get()`                      | None                            | Returned state = USB_UPGRADE             | -     |
| 6                 | Set state to `SOFTWARE_DOWNLOAD_ERROR` using `set()` | state = SOFTWARE_DOWNLOAD_ERROR | Status is OK                             | -     |
| 7                 | Get current state using `get()`                      | None                            | Returned state = SOFTWARE_DOWNLOAD_ERROR | -     |
| 8                 | Set state to `PSU_FAILURE` using `set()`             | state = PSU_FAILURE             | Status is OK                             | -     |
| 9                 | Get current state using `get()`                      | None                            | Returned state = PSU_FAILURE             | -     |
