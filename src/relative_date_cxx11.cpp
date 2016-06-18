#include "relative_date_cxx11.h"

namespace relative {
    std::string relative_date(const system_time_point &time_point,
            const system_time_point &now,
            fn_translator translator,
            int now_tolerance) {
        auto diff = now - time_point;
        auto seconds_diff = std::chrono::duration_cast<std::chrono::seconds>(diff);
        int seconds = seconds_diff.count();
        return relative_date(seconds, translator, now_tolerance);
    }
}
