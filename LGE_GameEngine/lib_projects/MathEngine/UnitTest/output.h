#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdio.h>
#include <assert.h>

class io
{
public:

	static void create(const char * const name);
	static void create(const char * const name, const char * const filename );
	static void destroy();
	static FILE *getHandle();

private:
	io()
	:fileHandle(0)
	{
	};


	~io() 
	{
		if(0 != fileHandle)
		{
			privDestroy();
		}
	};


	FILE *fileHandle;

	static io	*privGetInstance();
	void		privDestroy();
	void		privCreate(const char * const name);
	void		privCreate(const char * const name, const char * const filename );
	FILE		*privGetHandle();

};


#endif //output.h