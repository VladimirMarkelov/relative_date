#include "relative_date.h"

#include <cassert>
#include <sstream>

namespace relative {
    // a placeholder to replace with real relative value
    const std::string format_specifier = "%d";

    // constants for time ranges in seconds
    const int minute = 60;
    const int hour = 60 * 60;
    const int day = 60 * 60 * 24;
    const int week = 60 * 60 * 24 * 7;
    const int month = 60 * 60 * 24 * 30;
    const int year = 60 * 60 * 24 * 365;

    /** \struct relative_t
     *  \brief An internal structure for time ranges.
     */
    struct relative_t {
        int max_value; /**< maximum value of a range */
        int divisor;   /**< a normalization coefficient to convert a difference
                        * into a human-readable value, zero means - no
                        * convertion is required */
    };

    /** Time ranges list.
     * The last value is special: max_value must be greater than the value
     * the previous one and the divisor must be the value of the biggest range
     */
    const relative_t relative_ranges[] = {
        {30,       0},
        {minute,   1},
        {minute*2, 0},
        {hour,     minute},
        {hour*2,   0},
        {day,      hour},
        {day*2,    0},
        {week,     day},
        {week*2,   0},
        {day*30,   week},
        {day*30*2, 0},
        {year,     month},
        {year*2,   0},
        {year*3,   year},
    };

    /** Array of strings to make messages about the past */
    const std::string past_messages[] = {
        "just now",
        "%d seconds ago",
        "a minute ago",
        "%d minutes ago",
        "an hour ago",
        "%d hours ago",
        "a day ago",
        "%d days ago",
        "a week ago",
        "%d weeks ago",
        "a month ago",
        "%d months ago",
        "a year ago",
        "%d years ago",
    };
    /** Array of strings to make messages about the future */
    const std::string future_messages[] = {
        "soon",
        "%d seconds from now",
        "a minute from now",
        "%d minutes from now",
        "an hour from now",
        "%d hours from now",
        "a day from now",
        "%d days from now",
        "a week from now",
        "%d weeks from now",
        "a month from now",
        "%d months from now",
        "a year from now",
        "%d years from now",
    };

    void relative_date(int time_diff,
            std::string &msg, int &value,
            int now_tolerance) {
        assert(sizeof(relative_ranges)/sizeof(relative_ranges[0]) > 1);
        assert(sizeof(relative_ranges)/sizeof(relative_ranges[0]) ==
                 sizeof(past_messages)/sizeof(past_messages[0]) &&
               sizeof(relative_ranges)/sizeof(relative_ranges[0]) ==
                 sizeof(future_messages)/sizeof(future_messages[0]));

        size_t arr_size = sizeof(relative_ranges)/sizeof(relative_ranges[0]);
        size_t msg_id = arr_size - 1;
        int divisor = relative_ranges[msg_id].divisor;

        if (abs(time_diff) < now_tolerance) {
            msg_id = 0;
            divisor = relative_ranges[0].divisor;
        } else {
            size_t idx = 1;
            while (idx < arr_size) {
                if (relative_ranges[idx].max_value > abs(time_diff)) {
                    msg_id = idx;
                    divisor = relative_ranges[idx].divisor;
                    break;
                }

                ++idx;
            }
        }

        msg = time_diff >= 0 ?
            past_messages[msg_id] : future_messages[msg_id];

        value = abs(time_diff);
        if (divisor > 0) {
            value = value / divisor;
        }
    }

    std::string relative_date(int time_diff,
            fn_translator translator,
            int now_tolerance) {
        std::string msg;
        int value;
        relative_date(time_diff, msg, value, now_tolerance);

        if (translator) {
            msg = translator(msg);
        }

        size_t idx = msg.find(format_specifier);
        // Using the very simple solution to replace a placeholder with
        // real value. It can be done either with snprintf(that requires
        // char* buffer manipulation) or with external functions like
        // Boost.format. The solution below does not require any
        // external libraries
        if (idx != std::string::npos) {
            std::ostringstream convert;
            convert << value;
            msg.replace(idx, format_specifier.length(), convert.str());
        }

        return msg;
    }

    std::string relative_date(const std::time_t &time_point,
            const std::time_t &now,
            fn_translator translator,
            int now_tolerance) {
        double seconds = difftime(now, time_point);
        return relative_date((int)seconds, translator, now_tolerance);
    }
}
