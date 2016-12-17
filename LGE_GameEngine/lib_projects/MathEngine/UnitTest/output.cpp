#include <stdio.h>
#include <assert.h>
#include "output.h"


void io::create(const char * const name)
{
	privGetInstance()->privCreate( name );
}

void io::create(const char * const name, const char * const filename )
{
	privGetInstance()->privCreate( name, filename );
}

void io::destroy()
{
	privGetInstance()->privDestroy();
}

FILE *io::getHandle()
{
	return privGetInstance()->privGetHandle();
}

io *io::privGetInstance()
{
	static io instance;
	return &instance;
}

void io::privDestroy()
{
	errno_t fileError;
	assert( fileHandle );

	fileError = fflush( fileHandle );
	assert( !fileError );

	fileError = fclose( fileHandle);
	fileHandle = 0;
	assert( !fileError );	
}

void io::privCreate(const char * const name)
{
	errno_t fileError;

	fileError = fopen_s(&fileHandle,"output.txt","wt");
	assert( fileHandle );

	fprintf(fileHandle,"Program Assignment: 5 \n");
	fprintf(fileHandle,"Name: %s\n",name);
	fprintf(fileHandle,"PA5 - Intrinsics & SIMD\n\n");
}

void io::privCreate(const char * const name, const char * const filename )
{
	errno_t fileError;

	fileError = fopen_s(&fileHandle,filename,"wt");
	assert( fileHandle );

	fprintf(fileHandle,"Program Assignment: 5 \n");
	fprintf(fileHandle,"Name: %s\n",name);
	fprintf(fileHandle,"PA5 - Intrinsics & SIMD\n\n");


}

FILE *io::privGetHandle()
{
	assert( fileHandle );
	return fileHandle;
}


