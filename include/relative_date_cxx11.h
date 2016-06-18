#ifndef RELATIVE_DATE_CXX11_H_
#define RELATIVE_DATE_CXX11_H_

#include <string>
#include <chrono>
#include "relative_date.h"

namespace relative {
    typedef std::chrono::time_point<std::chrono::system_clock> system_time_point;

    std::string relative_date(const system_time_point &time_point,
            const system_time_point &now = std::chrono::system_clock::now(),
            fn_translator translator = nullptr,
            int now_tolerance = DEFAULT_NOW_TOLERANCE);
}

#endif // RELATIVE_DATE_CXX11_H_
