/**
 * A module to create human-redable relative dates.
 */
#ifndef RELATIVE_DATE_H_
#define RELATIVE_DATE_H_

#include <string>
#include <ctime>

namespace relative {
    /**
     * Time difference less than DEFAULT_NOW_TOLERANCE seconds
     * is treated as 'just now' or 'soon'
     */
    const int DEFAULT_NOW_TOLERANCE = 30;

    /**
     * A shorthand to declate a translator function:
     * it must take a string argument and return a translation.
     * All strings are UTF-8.
     */
    typedef std::string (*fn_translator) (const std::string&);

    /**
     * A main function to convert time difference to human-readable string.
     * @param time_diff is a time difference in seconds. Positive value means
     *    the event happend in the past.
     * @param msg is an output parameter that contains a raw message to display
     *    after the function executes. The message may contain format specifier
     *    and is ready for translation.
     * @param value is an output parameter that contains a number to put into
     *    msg to build the ready to display message. In the simplest case it
     *    may be used as printf(msg.c_str(), value).
     * @param now_tolerance is the minimal number of seconds that converted to
     *    human-readable format. All differences less than now_tolerance return
     *    'just now'.
     */
    void relative_date(int time_diff,
            std::string &msg, int &value,
            int now_tolerance = DEFAULT_NOW_TOLERANCE);
    /**
     * A helper function to get ready to display user-readable message.
     * @param time_diff is a time difference in seconds. Positive value means
     *    the event happend in the past.
     * @param translator is a pointer to a function that translates messages.
          It can be both a generic function and lambda function. If translator
          is nullptr(NULL) then the returned message is in English.
     * @param now_tolerance is the minimal number of seconds that converted to
     *    human-readable format. All differences less than now_tolerance return
     *    'just now'.
     */
    std::string relative_date(int time_diff,
            fn_translator translator = nullptr,
            int now_tolerance = DEFAULT_NOW_TOLERANCE);

    /**
     * A helper function to get ready to display user-readable relative date
     *   between two time_t time points.
     * @param time_point is a time point for which a human-readable message
        is generated.
     * @param now is a base time point. By default it equal the current time.
     * @param translator is a pointer to a functino that translates messages.
          It can be both a generic function and lambda function. If translator
          is nullptr(NULL) then the returned message is in English.
     * @param now_tolerance is the minimal number of seconds that converted to
     *    human-readable format. All differences less than now_tolerance return
     *    'just now'.
     */
    std::string relative_date(const std::time_t &time_point,
            const std::time_t &now = std::time(nullptr),
            fn_translator translator = nullptr,
            int now_tolerance = DEFAULT_NOW_TOLERANCE);
}

#endif // RELATIVE_DATE_H_
