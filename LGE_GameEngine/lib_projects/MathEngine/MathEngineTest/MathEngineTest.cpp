// MathEngineTest.cpp : Defines the entry point for the console application.
//


//---------------------------------------------------------------------------
// HEADER FILES:
//---------------------------------------------------------------------------
#include "UnitTest.h"


//---------------------------------------------------------------------------
// MAIN METHOD:
//---------------------------------------------------------------------------
int main()
{
	UnitTest_platform_init();

	const int numFailures = UnitTest_platform_runTests();
	
	UnitTest_platform_exit();
	return( numFailures );
}



