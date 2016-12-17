//---------------------------------------------------------------------------
// HEADER FILES:
//---------------------------------------------------------------------------
#include <stdlib.h>

#include "UnitTest.h"

//---------------------------------------------------------------------------
// MAIN METHOD:
//---------------------------------------------------------------------------
int main()
{
	UnitTest_platform_init();

	const int numFailures = UnitTest_platform_runTests();
	
	UnitTest_platform_exit();

   // cleanup: the delete test files
   system("del *.bin");
   

	return( numFailures );
}
