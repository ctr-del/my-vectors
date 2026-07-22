#include "test.h"
#include "test_failure_codes.h"

TestResult::TestResult(short statusCode):
    _statusCode(statusCode)
{
    if(status() == Status::pass){
        _desc = "Test passed with no errors.";
    }else{
        _desc = "Test failed unexpectedly.";
    }
}

TestResult::TestResult():
    _statusCode(T_FAILURE_TEST_NOT_INITIALIZED),
    _desc("Result object not initialized. Are you sure you remembered to modify it in your test?")
{

}
    

TestResult::TestResult(short statusCode, std::string description):
    _statusCode(statusCode),
    _desc(std::move(description))
{

}

Test::Test(std::string test_name, TestResult (*test_func)(void)):
    _label(std::move(test_name)),
    _test_function(test_func)
{
    _tests.push_back(this);
}

TestResult Test::run() {
    std::cout << "Running test '" << _label << "'...";
    TestResult result;

    try {
        result = _test_function();
    } catch (const std::exception& exception) {
        std::string out = "Unhandled std exception during test: ";
        out.append(exception.what());
        result = TestResult(T_FAILURE_UNCAUGHT_STD_EXCEPTION, out);
    } catch (...) {
        std::string out = "Unhandled non-std exception during test.";
        result = TestResult(T_FAILURE_UNCAUGHT_NON_STD_EXCEPTION, out);
    }

    if (result.status() == TestResult::Status::pass) {
        std::cout << "OK." << std::endl;
    }else{
        std::cout << "FAIL." << std::endl << result.description() << std::endl;
    }

    return result;
}

auto TestResult::status() const -> TestResult::Status {
    return (_statusCode == 0 ? Status::pass : Status::fail);
}

auto TestResult::status_code() const -> short {
    return _statusCode;
}

const std::string& TestResult::description() const {
    return _desc;
}

std::list<Test*> Test::_tests;

std::list<TestResult> Test::run_all() {
    std::list<TestResult> results = {};
    int testsRan = 0, testsPassed = 0, testsFailed = 0;

    for(auto* test : _tests) {
        TestResult result = test->run();
        ++testsRan;
        if(result.status() == TestResult::Status::pass){
            ++testsPassed;
        }else{
            ++testsFailed;
        }
        results.push_back(result);
    }

    std::cout << testsRan << " tests ran.\n" << testsPassed << " tests passed.\n" << testsFailed << " tests failed." << std::endl;

    return results;
}