

#include "UnitTest.h"

#include <stdio.h>
#include <string.h> 


Failure::Failure (const SimpleString&	theTestName, 
				  const SimpleString&	theFileName, 
		          long	 				theLineNumber,
		          const SimpleString&	theCondition) 
: message (theCondition), 
  testName (theTestName), 
  fileName (theFileName), 
  lineNumber (theLineNumber),
  pNextFailure(0)
{
}


Failure::Failure (const SimpleString&	theTestName, 
			 	  const SimpleString&	theFileName, 
				  long					theLineNumber,
				  const SimpleString&	expected,
				  const SimpleString&	actual) 
: testName (theTestName), 
  fileName (theFileName), 
  lineNumber (theLineNumber),
  pNextFailure(0)
{
	char *part1 = "expected ";
	char *part3 = " but was: ";
    int length = strlen (part1) 
					+ expected.length () 
					+ strlen (part3)
					+ actual.length ()
					+ 1;
	char *stage = new char [length];
	sprintf_s(stage, length, "%s%s%s%s", 
		part1, 
		expected.asCharString(), 
		part3, 
		actual.asCharString());

	this->message = SimpleString(stage);

	delete stage;
}

Failure::Failure( const Failure& inFailure)
    : testName (inFailure.testName), 
    fileName (inFailure.fileName), 
    lineNumber (inFailure.lineNumber),
    message(inFailure.message),
    pNextFailure(0)
{
}
