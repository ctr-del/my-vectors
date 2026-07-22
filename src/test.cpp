#include "test.h"


TestResult::TestResult(short statusCode):
    _status(statusCode == 0 ? PASS : FAIL),
    _statusCode(statusCode)
{
    if(_status == PASS){
        _desc = "Test passed with no errors.";
    }else{
        _desc = "Test failed unexpectedly.";
    }
}

TestResult::TestResult():
    _status(FAIL),
    _statusCode(-202),
    _desc("Result object not initialized. Are you sure you remembered to modify it in your test?")
{

}
    

TestResult::TestResult(short statusCode, std::string description):
    _status(statusCode == 0 ? PASS : FAIL),
    _statusCode(statusCode),
    _desc(description)
{

}

Test::Test(std::string test_name, TestResult (*test_func)(void)):
    _label(test_name),
    _test_function(test_func)
{
    _tests.push_back(this);
}

TestResult Test::run() {
    std::cout << "Running test '" << _label << "'...";
            
    TestResult result = _test_function();

    if (result.status() == TestResult::PASS) {
        std::cout << "PASS." << std::endl;
    }else{
        std::cout << "FAILED." << std::endl << result.description() << std::endl;
    }

    return result;
}

auto TestResult::status() const -> Status {
    return _status;
}

auto TestResult::status_code() const -> short {
    return _statusCode;
}

auto TestResult::description() const -> const std::string {
    return _desc;
}

std::list<Test*> Test::_tests;
std::list<TestResult> Test::run_all() {
    std::list<TestResult> results = {};
    for(auto test : _tests) {
        TestResult result = test->run();
        results.push_back(result);
    }

    return results;
}