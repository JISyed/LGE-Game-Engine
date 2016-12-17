#include "UnitTest.h"
#include "TestRegistry.h"

#include <stdio.h>
#include <Windows.h>

// Inititializes the platform environment 
void UnitTest_platform_init( void )
{
    TestRegistry::init();
}

// Returns the number of failures that were encountered.
int UnitTest_platform_runTests()
{
    TestResult result;
    TestRegistry::runAllTests(result);
    return result.getFailureCount();
}

// Tears down the platform environment used
void UnitTest_platform_exit( void )
{
}

// Displays the specified text. 
void UnitTest_platform_report( const char* const pText )
{
    //send to debug
    printf(pText);

	// If you are here due to an error, convert your project to multi-byte char, not UNICODE
    OutputDebugString(pText);
}