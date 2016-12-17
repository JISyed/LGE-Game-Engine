#include "CString.h"
#include <cstring>
#include <cassert>

namespace lge
{
	// Default Ctor
	CString::CString() :
		string(nullptr),
		length(0)
	{
	}

	// C-string Ctor
	CString::CString(const char* const newString) :
		string(nullptr),
		length(0)
	{
		assert(newString != nullptr);

		// Get allocation size
		this->length = std::strlen(newString);
		const size_t size = this->length + 1;

		// Create string data
		this->string = new char[size];
		std::memcpy(this->string, newString, size);
		this->string[size - 1] = '\0';
	}

	// Copy Ctor
	CString::CString(const CString& other) :
		string(nullptr),
		length(other.length)
	{
		// Allocate and create data
		const size_t size = this->length + 1;
		this->string = new char[size];
		std::memcpy(this->string, other.string, size);
		this->string[size - 1] = '\0';
	}

	// Copy Assignment
	CString& CString::operator=(const CString& other)
	{
		if (this == &other)
		{
			return *this;
		}

		// Delete existing data, if any
		if (this->string != nullptr)
		{
			assert(this->length != 0);
			delete[] this->string;
			this->string = nullptr;
			this->length = 0;
		}

		// Get allocation size
		this->length = other.length;
		const size_t size = this->length + 1;

		// Create string data
		this->string = new char[size];
		std::memcpy(this->string, other.string, size);
		this->string[size - 1] = '\0';

		return *this;
	}

	// Move Ctor
	CString::CString(CString&& other) :
		string(nullptr),
		length(other.length)
	{
		// Allocate and create data
		const size_t size = this->length + 1;
		this->string = new char[size];
		std::memcpy(this->string, other.string, size);
		this->string[size - 1] = '\0';

		// Clear other string (since we are moving)
		other.length = 0;
		other.string = nullptr;
	}

	// Move Assignment
	CString& CString::operator=(CString&& other)
	{
		if (this == &other)
		{
			return *this;
		}

		// Delete existing data, if any
		if (this->string != nullptr)
		{
			assert(this->length != 0);
			delete[] this->string;
			this->string = nullptr;
			this->length = 0;
		}

		// Get allocation size
		this->length = other.length;
		const size_t size = this->length + 1;

		// Create string data
		this->string = new char[size];
		std::memcpy(this->string, other.string, size);
		this->string[size - 1] = '\0';

		// Clear other string (since we are moving)
		other.length = 0;
		other.string = nullptr;

		return *this;
	}

	// Dtor
	CString::~CString()
	{
		if (this->string != nullptr)
		{
			assert(this->length != 0);
			delete[] this->string;
		}
	}



	

	// Get the string in C form
	const char* const CString::GetString() const
	{
		return this->string;
	}

	// Get the length of the string (excludes null character!)
	const size_t CString::GetLength() const
	{
		return this->length;
	}

	// Set a new string into this wrapper
	void CString::Set(const char* const newString)
	{
		// Delete existing data, if any
		if (this->string != nullptr)
		{
			assert(this->length != 0);
			delete[] this->string;
			this->string = nullptr;
			this->length = 0;
		}

		// Get allocation size
		this->length = std::strlen(newString);
		const size_t size = this->length + 1;

		// Create string data
		this->string = new char[size];
		std::memcpy(this->string, newString, size);
		this->string[size - 1] = '\0';
	}

	// Get a character, given the index
	const char CString::operator[](const unsigned int index) const
	{
		assert(index < (this->length + 1));
		return this->string[index];
	}


	// if CString == CString
	const bool CString::operator==(const CString& other) const
	{
		// Both null
		if (this->string == nullptr && other.string == nullptr)
		{
			assert(this->length != 0);
			assert(other.length != 0);
			return true;
		}
		// Only one is null
		else if ((this->string == nullptr) != (other.string == nullptr)) // logical XOR
		{
			return false;
		}

		// Lengths are different
		if (this->length != other.length)
		{
			return false;
		}

		assert(this->string != nullptr);
		assert(other.string != nullptr);

		// Actual comparison
		return 0 == std::strcmp(this->string, other.string);
	}

	// if CString != CString
	const bool CString::operator!=(const CString& other) const
	{
		return !(this->operator==(other));
	}

	// Check if the string is invalid (has no data)
	const bool CString::IsNull() const
	{
		return this->string == nullptr;
	}

	// if CString == const char* const
	const bool CString::operator==(const char* const other) const
	{
		// Both null
		if (this->string == nullptr && other == nullptr)
		{
			assert(this->length != 0);
			return true;
		}
		// Only one is null
		else if ((this->string == nullptr) != (other == nullptr)) // logical XOR
		{
			return false;
		}

		assert(this->string != nullptr);
		assert(other != nullptr);

		// Actual comparison
		return 0 == std::strcmp(this->string, other);
	}

	// if CString != const char* const
	const bool CString::operator!=(const char* const other) const
	{
		return !(this->operator==(other));
	}


}