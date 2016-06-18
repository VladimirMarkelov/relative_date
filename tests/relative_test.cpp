#include <iostream>
#include <string>
#include <stdio.h>
#include "relative_date.h"
#include "unittest.h"

using namespace std;
using namespace relative;

int tests_run = 0;

const char* test_basic() {
    string res = relative_date(-60*60*23);
    ut_assert("23 hours ahead", res == std::string("23 hours from now"));
    res = relative_date(-10);
    ut_assert("10 seconds ahead", res == std::string("soon"));
    res = relative_date(10);
    ut_assert("10 seconds back", res == std::string("just now"));
    res = relative_date(10, nullptr, 5);
    ut_assert("10 seconds back with custom now_tolerance", res == std::string("10 seconds ago"));
    res = relative_date(62);
    ut_assert("62 seconds back", res == std::string("a minute ago"));
    res = relative_date(162);
    ut_assert("162 seconds back", res == std::string("2 minutes ago"));
    res = relative_date(60*60+60);
    ut_assert("61 minutes back", res == std::string("an hour ago"));
    res = relative_date(60*60*4);
    ut_assert("240 minutes back", res == std::string("4 hours ago"));
    res = relative_date(60*60*26);
    ut_assert("a day back", res == std::string("a day ago"));
    res = relative_date(60*60*24*5);
    ut_assert("5 days back", res == std::string("5 days ago"));
    res = relative_date(60*60*24*34);
    ut_assert("a month back", res == std::string("a month ago"));
    res = relative_date(60*60*24*30*7);
    ut_assert("7 months back", res == std::string("7 months ago"));
    res = relative_date(60*60*24*500);
    ut_assert("year and a half back", res == std::string("a year ago"));
    res = relative_date(60*60*24*366*10);
    ut_assert("10 years", res == std::string("10 years ago"));

    return nullptr;
}

const char* test_time_t() {
    time_t point = time(nullptr);
    time_t now = time(nullptr);

    string res = relative_date(point);
    ut_assert("now", res == std::string("just now"));
    point += 40;
    res = relative_date(point);
    ut_assert("40 seconds ahead", res == std::string("40 seconds from now"));
    point -= 80;
    res = relative_date(point);
    ut_assert("40 seconds back", res == std::string("40 seconds ago"));
    point -= 60*60*11;
    res = relative_date(point);
    ut_assert("11 hours back", res == std::string("11 hours ago"));

    return 0;
}

const char* test_translation_lambda() {
    auto translator = [] (const string &in_str) -> string {
        if (in_str == "just now") {
            return "a little while ago";
        } else if (in_str == "%d seconds ago") {
            return "less than a minute ago";
        } else {
            return in_str;
        }
    };

    string res = relative_date(-10, translator);
    ut_assert("10 seconds ahead", res == std::string("soon"));
    res = relative_date(10, translator);
    ut_assert("10 seconds back", res == std::string("a little while ago"));
    res = relative_date(50, translator);
    ut_assert("50 seconds back", res == std::string("less than a minute ago"));
    res = relative_date(60*60*4, translator);
    ut_assert("240 minutes back", res == std::string("4 hours ago"));
    res = relative_date(60*60*26, translator);
    ut_assert("a day back", res == std::string("a day ago"));

    return 0;
}

std::string lakota(const std::string &msg) {
    if (msg == "%d days ago") {
        return "hékta aŋpétu %d k'uŋ héhaŋ";
    } else if (msg == "%d weeks ago") {
        return "hékta okó %d k'uŋ héhaŋ";
    } else {
        return msg;
    }
}

const char* test_translation_func() {
    std::string res = relative_date(60*60*24*6, lakota);
    ut_assert("6 days back", res == std::string("hékta aŋpétu 6 k'uŋ héhaŋ"));
    res = relative_date(60*60*24*15, lakota);
    ut_assert("2 weeks back", res == std::string("hékta okó 2 k'uŋ héhaŋ"));
    res = relative_date(60*60*4, lakota);
    ut_assert("240 minutes back", res == std::string("4 hours ago"));
    res = relative_date(60*60*26, lakota);
    ut_assert("a day back", res == std::string("a day ago"));

    return 0;
}

const char * run_all_test() {
    ut_run_test("Basic test", test_basic);
    ut_run_test("Time_t test", test_time_t);
    ut_run_test("Translation with lambda test", test_translation_lambda);
    ut_run_test("Lakota translation with function test", test_translation_func);
    return 0;
}

int main() {
    const char* res = run_all_test();
    if (res) {
        printf("%s\n", res);
    } else {
        printf("All tests passed successfully.\n");
    }
    return 0;
}
