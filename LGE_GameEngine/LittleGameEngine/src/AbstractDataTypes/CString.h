#ifndef H_LGE_C_STRING_WRAPPER
#define H_LGE_C_STRING_WRAPPER

namespace lge
{
	// Simple wrapper for C-strings
	class CString
	{
	public:

		//
		// Big 4 + Other Ctors
		//

		// Default Ctor
		CString();

		// C-string Ctor
		explicit CString(const char* const newString);

		// Copy Ctor
		CString(const CString& other);

		// Copy Assignment
		CString& operator=(const CString& other);

		// Move Ctor
		CString(CString&& other);

		// Move Assignment
		CString& operator=(CString&& other);

		// Dtor
		~CString();



		//
		// Accessors
		//

		// Get the string in C form
		const char* const GetString() const;

		// Get the length of the string (excludes null character!)
		const size_t GetLength() const;

		// Set a new string into this wrapper
		void Set(const char* const newString);

		// Get a character, given the index
		const char operator[](const unsigned int index) const;


		//
		// Utilities
		//

		// if CString == CString
		const bool operator==(const CString& other) const;

		// if CString != CString
		const bool operator!=(const CString& other) const;

		// Check if the string is invalid (has no data)
		const bool IsNull() const;

		// if CString == const char* const
		const bool operator==(const char* const other) const;

		// if CString != const char* const
		const bool operator!=(const char* const other) const;

	private:

		//
		// Data
		//

		char* string;
		size_t length;

	};
}
#endif