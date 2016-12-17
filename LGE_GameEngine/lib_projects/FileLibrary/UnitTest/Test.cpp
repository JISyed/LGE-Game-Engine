

#include "UnitTest.h"
#include "TestRegistry.h"


Test::Test (const SimpleString& testName) 
	: _name (testName),
    _pNextTest(0)
{
	TestRegistry::addTest (this);
}

Test::~Test()
{
}

Test *Test::getNextTest()
{
	return this->_pNextTest;
}


void Test::setNextTest(Test * const inTest)
{	
	this->_pNextTest = inTest;
}

const SimpleString& Test::getName() const
{
    return this->_name;
}