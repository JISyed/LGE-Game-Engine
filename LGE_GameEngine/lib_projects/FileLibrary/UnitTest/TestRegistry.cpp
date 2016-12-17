

#include "UnitTest.h"
#include "TestRegistry.h"

TestRegistry::TestRegistry()
    :_pFirstTest(0),
     _pLastTest(0)
{
}

void TestRegistry::init()
{
    instance();
}

void TestRegistry::shutdown()
{
    instance()._pFirstTest = 0;
    instance()._pLastTest = 0;
}

void TestRegistry::addTest (Test *test) 
{
	instance ().add (test);
}


void TestRegistry::runAllTests (TestResult& result) 
{
	instance ().run (result);
    result.report();
}


TestRegistry& TestRegistry::instance () 
{
	static TestRegistry registry;
	return registry;
}


void TestRegistry::add (Test *test) 
{
    if (_pFirstTest == 0) {
		_pFirstTest = test;
        _pLastTest = test;
		return;
	}
	
    this->_pLastTest->setNextTest(test);
    this->_pLastTest = test;
}


void TestRegistry::run (TestResult& result) 
{
	for (Test *test = _pFirstTest; test != 0; test = test->getNextTest ())
    {
        int failCount = result.getFailureCount();
        result.addTest();
		test->run (result);
        if(result.getFailureCount() > failCount)
        {
            UnitTest_platform_report("F");
        }
        else
        {
            UnitTest_platform_report(".");
        }
    }
    UnitTest_platform_report("\n");
}



