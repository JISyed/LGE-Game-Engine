#include "UnitTest.h"

#include <stdio.h>

TestResult::TestResult ()
	: _failureCount (0),
    _testCount(0),
    _pFirstFailure(0),
    _pLastFailure(0)
{
}

TestResult::~TestResult()
{
    while (this->_pFirstFailure != this->_pLastFailure)
    {
        Failure* temp = this->_pFirstFailure;
        this->_pFirstFailure = temp->pNextFailure;
        delete temp;
    }
    if(this->_pLastFailure != 0)
    {
        delete this->_pLastFailure;
    }
}

void TestResult::addTest()
{
    this->_testCount++;
}

void TestResult::addFailure (const Failure& failure) 
{
    Failure* fail = new Failure(failure); //make a copy, because it will go out of scope after run() ends
    this->_failureCount++;
    //add to failure LL
	if (this->_pFirstFailure == 0) {
		this->_pFirstFailure = fail; 
		this->_pLastFailure = fail;
        return;
	}
	
    //append to end of LL, so last is the most recent, and first is the first test to fail
    this->_pLastFailure->pNextFailure = fail;
	this->_pLastFailure = fail;
}

void TestResult::report() const
{
    if(this->_failureCount > 0)
    {
        this->reportFailures();
    }
    else 
    {
        this->reportGoodResult();
    }
}

int TestResult::getFailureCount() const
{
    return this->_failureCount;
}

void TestResult::reportGoodResult() const
{
    char str[64];
    sprintf_s(str, 64, "OK( %d tests) \n", _testCount);
    UnitTest_platform_report(str);
}

void TestResult::reportFailures () const
{
    UnitTest_platform_report("Test Results: \n");
    char str[128];
    sprintf_s(str, 128, "tests: %d failures: %d \n", _testCount, _failureCount);
    UnitTest_platform_report(str);
    for(Failure *fail = _pFirstFailure; fail != 0; fail = fail->pNextFailure)
    {
        UnitTest_platform_report(fail->fileName.asCharString());
        sprintf_s(str,128,"(%d): ", fail->lineNumber);
        UnitTest_platform_report(str);
        UnitTest_platform_report(fail->testName.asCharString());
        UnitTest_platform_report(" failure: \"");
        UnitTest_platform_report(fail->message.asCharString());
        UnitTest_platform_report("\" \n");
    }
}
