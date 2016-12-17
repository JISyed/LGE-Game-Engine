#include "UnitTest.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


static const int DEFAULT_SIZE = 20;

SimpleString::SimpleString ()
: _pBuffer(new char [1])
{
	this->_pBuffer [0] = '\0';
}


SimpleString::SimpleString (const char *other_pBuffer)
: _pBuffer (new char [strlen (other_pBuffer) + 1])
{
	strcpy_s (this->_pBuffer,strlen (other_pBuffer) + 1, other_pBuffer);
}

SimpleString::SimpleString (const SimpleString& other)
    : _pBuffer(new char [other.length() + 1])
{
	strcpy_s(this->_pBuffer,other.length() + 1, other._pBuffer);
}


SimpleString& SimpleString::operator= (const SimpleString& other)
{
	delete this->_pBuffer;
	this->_pBuffer = new char [other.length() + 1];
	strcpy_s(this->_pBuffer,other.length() + 1, other._pBuffer);	
	return *this;
}


const char *SimpleString::asCharString () const
{
	return this->_pBuffer;
}

size_t SimpleString::length() const
{
	return strlen (this->_pBuffer);
}

SimpleString::~SimpleString ()
{
	delete [] this->_pBuffer;
}

bool SimpleString::operator==( const SimpleString& rhs ) const
{
	return !strcmp( this->_pBuffer, rhs._pBuffer );
}

bool operator== (const SimpleString& left, const SimpleString& right)
{
	return !strcmp (left.asCharString (), right.asCharString ());
}

const SimpleString StringFrom (bool bvalue)
{
	char buffer [sizeof ("false") + 1];
	sprintf_s(buffer, sizeof ("false") + 1, "%s", bvalue ? "true" : "false");
	return SimpleString(buffer);
}

const SimpleString StringFrom (const char cvalue)
{
    char buffer [2];
    sprintf_s(buffer,2, "%c", cvalue);
	return SimpleString(buffer);
}

const SimpleString StringFrom (const unsigned char ucvalue)
{
    char buffer [2];
    sprintf_s(buffer, 2, "%u", ucvalue);
	return SimpleString(buffer);
}

const SimpleString StringFrom (int ivalue)
{
	char _pBuffer [DEFAULT_SIZE];
	sprintf_s(_pBuffer,DEFAULT_SIZE, "%d(0x%x)", ivalue, ivalue);
	return SimpleString(_pBuffer);
}

const SimpleString StringFrom (unsigned int value)
{
	char _pBuffer [DEFAULT_SIZE];
	sprintf_s(_pBuffer,DEFAULT_SIZE, "%u(0x%x)", value,value);
	return SimpleString(_pBuffer);
}

const SimpleString StringFrom (long value)
{
	char _pBuffer [DEFAULT_SIZE];
	sprintf_s(_pBuffer,DEFAULT_SIZE, "%ld", value);

	return SimpleString(_pBuffer);
}

const SimpleString StringFrom (unsigned long value)
{
	char _pBuffer [DEFAULT_SIZE];
	sprintf_s(_pBuffer,DEFAULT_SIZE, "%u", value);

	return SimpleString(_pBuffer);
}

const SimpleString StringFrom (float value)
{
	char _pBuffer [DEFAULT_SIZE];
	sprintf_s(_pBuffer,DEFAULT_SIZE, "%lf", value);

	return SimpleString(_pBuffer);
}

const SimpleString StringFrom (double value)
{
	char _pBuffer [DEFAULT_SIZE];
	sprintf_s(_pBuffer,DEFAULT_SIZE, "%lf", value);

	return SimpleString(_pBuffer);
}

const SimpleString StringFrom (const SimpleString& value)
{
	return SimpleString(value);
}


