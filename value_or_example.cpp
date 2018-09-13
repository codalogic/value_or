#include "annotate-lite.h"
using namespace annotate_lite;
#include "include/value_or/value_or.h"
using namespace valueor;

#pragma warning( disable:4996 )

#include <cstdio>
#include <fstream>
#include <optional>

void pointer_types()
{
	Scenario( "Pointer Types" );

	struct BadPointer1 {};
	struct BadPointer2 {};
	try
	{
		int i = 0;
		int * p_i = value_or<BadPointer1>( &i );
		Good( "Exception should not thrown" );
		p_i = value_or<BadPointer2>( (int*)0 );
		Bad( "Exception should have thrown" );
	}
	catch( const BadPointer1 & )
	{
		Bad( "Exception thrown" );
	}
	catch( const BadPointer2 & )
	{
		Good( "Exception thrown" );
	}
}

void unknown_types()
{
	Scenario( "Unknown Types" );

	struct BadUnknown {};
	try
	{
		float f = value_or<BadUnknown>( 1.0f );
		Bad( "Exception should have thrown" );
	}
	catch( const BadUnknown & )
	{
		Good( "Exception thrown" );
	}
}

namespace valueor {
	template<>
	struct value_or_validator< const std::ifstream & >
	{
		static bool is_valid( const std::ifstream & v ) { return v.is_open(); }
	};
}

void fopen_file_types()
{
	Scenario( "File Types - fopen" );

	struct BadFile1 {};
	struct BadFile2 {};
	try
	{
		FILE * fin1 = value_or<BadFile1>( fopen( "value_or_example.cpp", "r" ) );
		Good( "Exception not thrown" );
		fclose( fin1 );

		FILE * fin2 = value_or<BadFile2>( fopen( "Non-existent file", "r" ) );
		Bad( "Exception should have thrown" );
	}
	catch( const BadFile1 & )
	{
		Bad( "Exception should have thrown" );
	}
	catch( const BadFile2 & )
	{
		Good( "Exception thrown" );
	}
}

void fstream_file_types()
{
	Scenario( "File Types - ifstream" );

	struct BadFile1 {};
	struct BadFile2 {};
	try
	{
		std::ifstream fin1( "value_or_example.cpp" );
		value_or<BadFile1>( fin1 );
		Good( "Exception not thrown" );

		std::ifstream fin2( "non-existent file" );
		value_or<BadFile2>( fin2 );
		Bad( "Exception should have thrown" );
	}
	catch( const BadFile1 & )
	{
		Bad( "Exception should have thrown" );
	}
	catch( const BadFile2 & )
	{
		Good( "Exception thrown" );
	}
}

template< typename Texception >
class ifstream_or : public std::ifstream
{
public:
	ifstream_or<Texception>( const char *_Filename,
		ios_base::openmode _Mode = std::ios_base::in,
		int _Prot = (int)std::ios_base::_Openprot )
		:
		std::ifstream( _Filename, _Mode, _Prot )
	{
		if( ! is_open() )
			throw Texception();
	}
};

void fstream_or_file_types()
{
	Scenario( "File Types - ifstream_or" );

	struct BadFile1 {};
	struct BadFile2 {};
	try
	{
		ifstream_or<BadFile1> fin1( "value_or_example.cpp" );
		Good( "Exception not thrown" );

		ifstream_or<BadFile2> fin2( "non-existent file" );
		Bad( "Exception should have thrown" );
	}
	catch( const BadFile1 & )
	{
		Bad( "Exception should have thrown" );
	}
	catch( const BadFile2 & )
	{
		Good( "Exception thrown" );
	}
}

namespace valueor {
	template< typename T >
	struct value_or_validator< const std::optional<T> & >
	{
		static bool is_valid( const std::optional<T> & v ) { return v.has_value(); }
	};
}

void std_optional_types()
{
	Scenario( "std::optional" );

	struct BadOption1 {};
	struct BadOption2 {};
	try
	{
		auto optional1 = std::optional<int>( 1 );
		int i1 = value_or<BadOption1>( optional1 ).value();
		Good( "Exception not thrown" );

		auto optional2 = std::optional<int>();
		int i2 = value_or<BadOption2>( optional2 ).value();
		Bad( "Exception should have thrown" );
	}
	catch( const BadOption1 & )
	{
		Bad( "Exception should have thrown" );
	}
	catch( const BadOption2 & )
	{
		Good( "Exception thrown" );
	}
}

int main()
{
	pointer_types();
	unknown_types();
	fopen_file_types();
	fstream_file_types();
	fstream_or_file_types();
	std_optional_types();
}
