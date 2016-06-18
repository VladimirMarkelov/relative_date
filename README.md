# Relative date in human-readable format
Converts a time difference in seconds into human-readable format:
*    170 seconds ago --> 3 minutes ago
*    3600 seconds ago --> an hour ago
*    5 seconds ago --> just now

# API
## Core functions
**void relative_date(int time_diff, std::string &msg, int &value, int now_tolerance = DEFAULT_NOW_TOLERANCE);**

A main function to convert time difference to human-readable string.
* time_diff - is a time difference in seconds. Positive value means the event happend in the past.
* msg - is an output parameter that contains a raw message to display after the function executes. The message may contain format specifier and is ready for translation.
* value - is an output parameter that contains a number to put into **msg** to build the ready to display message. In the simplest case it may be used as printf(msg.c_str(), value).
* now_tolerance is the minimal number of seconds that converted to human-readable format. All differences less than **now_tolerance** return 'just now'.

## Helper functions
**std::string relative_date(int time_diff, fn_translator translator = nullptr, int now_tolerance = DEFAULT_NOW_TOLERANCE);**

A helper function to get ready to display user-readable message.
* time_diff - is a time difference in seconds. Positive value means the event happend in the past.
* translator - is a pointer to a function that translates messages. It can be both a generic function and lambda function. If **translator** is **nullptr**(NULL) then the returned message is in English.
* now_tolerance is the minimal number of seconds that converted to human-readable format. All differences less than **now_tolerance** return 'just now'.

**std::string relative_date(const std::time_t &time_point, const std::time_t &now = std::time(nullptr), fn_translator translator = nullptr, int now_tolerance = DEFAULT_NOW_TOLERANCE);**

A helper function to get ready to display user-readable relative date between two **time_t** time points.
* time_point - is a time point for which a human-readable message is generated.
* now - is a base time point. By default it equal the current time.
* translator - is a pointer to a functino that translates messages. It can be both a generic function and lambda function. If **translator** is **nullptr**(NULL) then the returned message is in English.
* now_tolerance is the minimal number of seconds that converted to human-readable format. All differences less than **now_tolerance** return 'just now'.


**std::string relative_date(const system_time_point &time_point, const system_time_point &now = std::chrono::system_clock::now(), fn_translator translator = nullptr, int now_tolerance = DEFAULT_NOW_TOLERANCE);**

The function is the same as about just uses C++11 **std::chrono::time_point<std::chrono::system_clock>** (the library introduces a shortcut for this long definition: **system_time_point**) instead of **time_t**.


# Building the library
Use CMake to build library and the test application.
Steps to build on Windows using MinGW:
* Install CMake if it is not already installed. Minimal required version is 2.8
* Open command prompt
* Make the project directory current with command **cd <path-to-library>**
* Configure the library: **cmake -H. -Bbuild -G "MinGW Makefiles"**
* Build the library: **cmake --build build**

After completing the steps above the compiled library and test application are created in **build** subdirectory
