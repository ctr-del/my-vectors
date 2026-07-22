//TEST SUITE HEADER V.0.1.0

#ifndef TEST_SUITE_HPP
#define TEST_SUITE_HPP

#include <iostream>
#include <string>
#include <list>

class TestResult {
    public:
    enum Status {
        PASS,
        FAIL
    };
    TestResult(short statusCode, std::string desc);
    TestResult(short statusCode);
    TestResult();
    Status status() const;
    short status_code() const;
    const std::string description() const;

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