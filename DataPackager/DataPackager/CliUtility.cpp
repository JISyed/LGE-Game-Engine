#include "CliUtility.h"
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include "DirectoryUtility.h"


//
// Static Data
//

// All the error messages in vodka
static const char* const s_errorMessages[] = {
	"Code= 0x0: No error (This should not be seen, otherwise InvokeCliError() is being used incorrectly) %s",
	"ERROR 0x1: Too many parameters provided! %s\n",
	"ERROR 0x2: Too few parameters provided! %s\n",
	"ERROR 0x3: Options need to be prefixed with a hyphen \"-\". Using \"%c\" instead\n",
	"ERROR 0x4: Unrecognized option \"%s\"\n",
	"ERROR 0x5: Option \"%s\" is being repeated\n",
	"ERROR 0x6: The package version ID \"%s\" is too long. Needs to be max of 19 characters\n",
	"ERROR 0x7: The package name \"%s\" is too long. Needs to be max of 19 characters\n",
	"ERROR 0x8: Could not load the file \"%s\". Either it doesn't exist or its spelled wrong\n",
	"ERROR 0x9: There was a problem determining the size of the chunk file \"%s\"",
	"ERROR 0xA: There was an error reading the file \"%s\"",
	"ERROR 0xB: There was an error closing the file \"%s\"",
	"ERROR 0xC: There was an error writing the PackageHeader from memory into the output file \"%s\"",
	"ERROR 0xD: There was an error writing an LGE file \"%s\" into the package",
	"Error 0xE: There were no LGE files in the current directory \"%s\""
};




//
// Functions
//

// Print the usage information for this program
void PrintCliHelp()
{
	printf("\nUSAGE:\n");

	printf(" DataPackager outputFile.ext [ -n PACKAGE_NAME ] [ -v VERSION_STRING ]\n");
	printf("\n");
	printf("      - outputFile.ext can be any name, and any extension\n");
	printf("      - [PACKAGE_NAME] can be any name with max of 19 characters (no spaces)\n");
	printf("      - [VERSION_STRING] can be a mixture of numbers and characters,\n");
	printf("                         but has max 19 characters (no spaces)\n");
	printf("      - There must be at least 1 .%s file in the working directory of DataPackager\n", LGE_EXT_FOR_CHUNKS);

	printf("\n");
}



// Print an error message including context for the error.
// Will exit the program on the given error code.
// If no context is needed, use empty string ("").
void InvokeCliError(unsigned int errorCode, const char* const context)
{
	printf("\n");

	// Error code 3 (no hyphens) has different formatting from the other error messages
	if (errorCode == LGE_ERROR_OPTION_NO_HYPHEN)
	{
		printf(s_errorMessages[errorCode], context[0]);
	}
	else
	{
		printf(s_errorMessages[errorCode], context);
	}

	PrintCliHelp();

#if LGE_CMD_PAUSE
	system("pause");
#endif

	exit(errorCode);
}



// Get the package name and version from the command line arguments. Assumes that argc is 6
void ProcessArguments(char* argv[], PackageHeader& pkgHdrInOut)
{
	// For DataPackager, the option arguments are the 2nd and 4th in argv
	char* const firstOption = argv[2];
	char* const secondOption = argv[4];

	// Check if the options start with a hyphen
	if (firstOption[0] != '-')
	{
		InvokeCliError(LGE_ERROR_OPTION_NO_HYPHEN, firstOption);
	}
	if (secondOption[0] != '-')
	{
		InvokeCliError(LGE_ERROR_OPTION_NO_HYPHEN, secondOption);
	}

	// Make the options lower case
	firstOption[1] = (char)tolower(firstOption[1]);
	secondOption[1] = (char)tolower(secondOption[1]);

	// Examine the options (must be -v then -n, or -n then -v)
	if (!strcmp(firstOption, "-v"))
	{
		// The second option should be -n
		if (!strcmp(secondOption, "-n"))
		{
			// 3rd argument is package version and 5th argument is package name
			pkgHdrInOut.ProcessArgs(argv[3], argv[5]);
			printf("Package Name:      %s\n", argv[5]);
			printf("Package Version:   %s\n", argv[3]);
		}
		// -v should not occur twice in this branch
		else if (!strcmp(secondOption, "-v"))
		{
			InvokeCliError(LGE_ERROR_REPEATING_OPTION, secondOption);
		}
		else
		{
			InvokeCliError(LGE_ERROR_UNKNOWN_OPTION, secondOption);
		}
	}
	else if (!strcmp(firstOption, "-n"))
	{
		// The second option should be -t
		if (!strcmp(secondOption, "-v"))
		{
			// 3rd argument is package name and 5th argument is package version
			pkgHdrInOut.ProcessArgs(argv[5], argv[3]);
			printf("Package Name:      %s\n", argv[3]);
			printf("Package Version:   %s\n", argv[5]);
		}
		// -n should not occur twice in this branch
		else if (!strcmp(secondOption, "-n"))
		{
			InvokeCliError(LGE_ERROR_REPEATING_OPTION, secondOption);
		}
		else
		{
			InvokeCliError(LGE_ERROR_UNKNOWN_OPTION, secondOption);
		}
	}
	else
	{
		InvokeCliError(LGE_ERROR_UNKNOWN_OPTION, firstOption);
	}
}

