//TEST SUITE HEADER V.0.1.0

/*
Hard-coded status codes, avoid using when possible as they are used by the testing framework itself.
====================================================================================================|
0       ->     Success, and should always mean success for consistancy.                             |
-501    ->     Test result never properly initialized, usually a sign of a badly written test.      |
-502    ->     An unhandled exception occured during the test. Defaults to a test failure,          |
====================================================================================================|
*/

#ifndef TEST_SUITE_HPP
#define TEST_SUITE_HPP

#include <iostream>
#include <string>
#include <utility>
#include <list>

#include "test_failure_codes.h"

class TestResult {
    public:
    enum class Status {
        pass,
        fail
    };
    TestResult(short statusCode, std::string desc);
    TestResult(short statusCode);
    TestResult();
    Status status() const;
    short status_code() const;
    const std::string& description() const;

    private:
        Status _status;
        short _statusCode;
        std::string _desc;
};

class Test {
    private:
        static std::list<Test*> _tests;
        std::string _label;
        TestResult (*_test_function)(void);
    public:
        Test(std::string test_name, TestResult (*test_func)(void));

        TestResult run();

        static std::list<TestResult> run_all();
};

#endif