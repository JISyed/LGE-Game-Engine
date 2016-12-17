#ifndef UNIT_Test
#define UNIT_Test

//---------------------------------------------------------------------------
// WARNING CONFIGURATION:
//---------------------------------------------------------------------------

	// Allow conditional expressions that are constant.
	#pragma warning( disable : 4127 )

	// Allow unreferenced inlined functions.
	#pragma warning( disable : 4514 )


//---------------------------------------------------------------------------
// HEADER FILES:
//---------------------------------------------------------------------------

#include <stddef.h>

class SimpleString
{
	public:
		// Creates an empty SimpleString. 
		SimpleString();
	
		// Creates a string with the specified text. 
		explicit SimpleString( const char* const text );
	
		// Creates a copy of the specified string. 
		SimpleString( const SimpleString& );
	
		// Assigns the right-hand string to this SimpleString.
		SimpleString& operator=( const SimpleString& rhs );

		// destructor
		~SimpleString();

		//@ returns a raw version of this SimpleString.
		const char* asCharString() const;
	
		// return the length of this SimpleString.
		size_t length() const;
	
		// return true if this SimpleString is equal to the right-hand side. 
		bool operator==( const SimpleString& rhs ) const;
		
	
		// return true if this SimpleString is NOT equal to the right-hand side. 
		bool operator!=( const SimpleString& rhs ) const;

	private:
		char* _pBuffer;
};

//---------------------------------------------------------------------------
// DEFAULT CONVERSIONS:
//---------------------------------------------------------------------------

// Used by CHECK_EQUAL() to turn boolean values into strings.
const SimpleString StringFrom( const bool );

// Used by CHECK_EQUAL() to signed character values into strings.
const SimpleString StringFrom( const char );

// Used by CHECK_EQUAL() to unsigned character values into strings.
const SimpleString StringFrom( const unsigned char );

// Used by CHECK_EQUAL() to turn integral values into strings.
const SimpleString StringFrom( const int );

// Used by CHECK_EQUAL() to turn unsigned integral values into strings.
const SimpleString StringFrom( const unsigned int );

// Used by CHECK_EQUAL() to turn large integral values into strings.
const SimpleString StringFrom( const long );

// Used by CHECK_EQUAL() to turn large unsigned integral values into strings.
const SimpleString StringFrom( const unsigned long );

// Used by CHECK_EQUAL() to turn floating point values into strings.
const SimpleString StringFrom( const float );

// Used by CHECK_EQUAL() to turn large floating point values into strings.
const SimpleString StringFrom( const double );
const SimpleString StringFrom( const SimpleString& );

//---------------------------------------------------------------------------
// CLASS DECLARATION:
//---------------------------------------------------------------------------
struct Failure
{
	SimpleString message;
	SimpleString testName;
	SimpleString fileName;

	long lineNumber;

	Failure* pNextFailure;

	Failure(
		const SimpleString& testName, 
		const SimpleString& fileName, 
		const long          lineNumber,
		const SimpleString& condition
	);

	Failure(
		const SimpleString& testName, 
		const SimpleString& fileName, 
		long                lineNumber,
		const SimpleString& expected,
		const SimpleString& actual
	);

	Failure( const Failure& );
};

//---------------------------------------------------------------------------
// CLASS DECLARATION:
//---------------------------------------------------------------------------
class TestResult
{
	public:
		TestResult(); 
		~TestResult();
		void addTest();
		void addFailure( const Failure& failure );
		void report() const;
		int getFailureCount() const;
	
	private:
		void reportGoodResult() const;
		void reportFailures() const;
		int _testCount;
		int _failureCount;
		Failure* _pFirstFailure;
		Failure* _pLastFailure;
};


	#include <math.h>   // for fabs()


//---------------------------------------------------------------------------
// TEST DECLARATION:
//---------------------------------------------------------------------------

/**
 * @hideinitializer
 *
 * Defines a test that is ready for implementation.
 *
 *
 * @param testName  
 *        The name of this test.
 *
 * @param groupName 
 *        The name of the <i>group</i> that distinguishes
 *        this test from other tests with the same testName.
 *
 *
 * @b Example:
 *    @code
 *    #include "UnitTest.h"
 *
 *    TEST( Addition, IntTests )
 *    {
 *       CHECK( 1 + 1 == 2 );
 *    }
 *
 *    TEST( Addition, FloatTests )
 *    {
 *       CHECK( 1.0f + 1.0f == 2.0f );
 *    }
 *    @endcode
 *
 *
 * @see CHECK(), CHECK_EQUAL(), DOUBLES_EQUAL(), FAIL()
 */
#define TEST( testName, groupName ) \
  /*lint -esym( 765, *_instance ) : Allow *_instance to be non-static. */ \
  class groupName##testName##_Test : public Test \
  { \
     public: \
        groupName##testName##_Test(): \
           Test( SimpleString( #groupName "." #testName ) ) \
        { } \
        \
        void run(TestResult& result_); \
  } groupName##testName##_instance; \
  \
  void groupName##testName##_Test::run( TestResult& result ) 



//---------------------------------------------------------------------------
// TEST FUNCTIONS:
//---------------------------------------------------------------------------

/**
 * @hideinitializer
 *
 * Used in a #TEST to report failure when a condition evaluates to false.
 *
 *
 * @param condition 
 *        The condition that will generate a failure if it evaluates to false.
 *
 *
 * @b Example:
 *    @code
 *    #include "UnitTest.h"
 *
 *    TEST( Addition, MathTests )
 *    {
 *       CHECK( 1 + 1 == 2 );
 *       CHECK( 2 + 2 == 4 );
 *    }
 *    @endcode
 */
#define CHECK( condition ) \
   { \
      /*lint -e( 506, 774 ) : Allow constant conditions. */ \
      if( !( condition ) ) \
      { \
         result.addFailure( \
            Failure( \
               this->getName(), \
               SimpleString( __FILE__ ), \
               __LINE__, \
               SimpleString( #condition ) \
            ) \
         ); \
         \
         return; \
      } \
   }


/**
 * @hideinitializer
 *
 * Used in a #TEST to report failure when a value does not match
 * an expected value.
 *
 *
 * @param expectedValue A target value you're expecting in your test.
 * @param actualValue   The <i>actual</i> value that your test ends up generating.
 *
 *
 * @par Custom Types:
 * You can call CHECK_EQUAL() on your own value types as long as the following
 * are true:
 *    - The expected and actual values are comparable.
 *    - @link SimpleString StringFrom() @endlink implementation is available
 *      to turn your expected and actual values into text.
 *
 *
 * @b Example:
 *    @code
 *    #include "UnitTest.h"
 *
 *    TEST( Addition, MathTests )
 *    {
 *       CHECK_EQUAL( 2, 1 + 1 );
 *       CHECK_EQUAL( 4, 2 + 2 );
 *    }
 *    @endcode
 */
//lint -esym( 666, CHECK_EQUAL ) : CHECK_EQUAL() evaluates its arguments twice.
#define CHECK_EQUAL( expectedValue, actualValue ) \
   { \
      /*lint -e( 506, 774 ) : Allow constant conditions. */ \
      if( !( (expectedValue) == (actualValue) ) ) \
      { \
         result.addFailure( \
            Failure( \
               this->getName(), \
               SimpleString( __FILE__ ), \
               __LINE__, \
               StringFrom( expectedValue ), \
               StringFrom( actualValue ) \
            ) \
         ); \
         \
         return; \
      } \
   }


/**
 * @hideinitializer
 *
 * Used in a #TEST to report failure if a value does not fall within 
 * the specified threshold of an expected value.
 *
 *
 * @param expectedValue 
 *        A target floating point value you're expecting in your test.
 *
 * @param actualValue   
 *        The <i>actual</i> value your test ends up generating.
 *
 * @param threshold
 *        The the maximum absolute amount the actual value may deviate
 *        from the expected value without generating a failure.
 *
 *
 * @b Example:
 *    @code
 *    #include "UnitTest.h"
 *    #include <math.h>
 *
 *    TEST( SquareRoot, MathTests )
 *    {
 *       DOUBLES_EQUAL( 1.414, sqrt( 2.0 ), 0.001 );
 *    }
 *    @endcode
 */
#define DOUBLES_EQUAL( expectedValue, actualValue, threshold ) \
   { \
      /*lint -e1924 : Avoid requiring static_cast<> from compiler. */ \
      const double dExpected  = (double)expectedValue; \
      const double dActual    = (double)actualValue; \
      const double dThreshold = (double)threshold; \
      \
      if( dThreshold < fabs( dExpected - dActual ) ) \
      { \
         result.addFailure( \
            Failure( \
               this->getName(), \
               SimpleString( __FILE__ ), \
               __LINE__, \
               StringFrom( dExpected ), \
               StringFrom( dActual ) \
            ) \
         ); \
         \
         return; \
      } \
      \
      /*lint +e1924 */ \
   }


/**
 * @hideinitializer
 *
 * Used in a #TEST to report specific failure message.
 *
 * @param failureMessage The string to report for this failure.
 *
 * @b Example
 *    @code
 *    switch ( animalType )
 *    {
 *       case CAT:
 *          // Test cat.
 *          ...
 *          break;
 *
 *       case DOG:
 *          // Test dog.
 *          ...
 *          break;
 *
 *       default:
 *          FAIL( "Unknown animal type." );
 *    }
 *    @endcode
 */
#define FAIL( failureMessage ) \
   { \
      result.addFailure( \
         Failure( \
            this->getName(), \
            SimpleString( __FILE__ ), \
            __LINE__, \
            SimpleString( failureMessage ) \
         ) \
      ); \
   } \
   \
   return



//---------------------------------------------------------------------------
// INTERNAL INTERFACE:
//---------------------------------------------------------------------------
class Test
{
	public:
		explicit Test( const SimpleString& testName );
		virtual ~Test();
	
	public:
		virtual void run( TestResult& ) = 0;
	
	public:
		void setNextTest( Test* const );
		Test* getNextTest();
	
	protected:
		const SimpleString& getName() const;
	
	private:
		SimpleString _name;
		Test* _pNextTest;
};



//---------------------------------------------------------------------------
// METHOD DECLARATIONS:
//---------------------------------------------------------------------------

// Inititializes the platform environment 
void UnitTest_platform_init( void );

// Returns the number of failures that were encountered.
int UnitTest_platform_runTests();

// Tears down the platform environment used
void UnitTest_platform_exit( void );

// Displays the specified text. 
void UnitTest_platform_report( const char* const pText );


#endif   
