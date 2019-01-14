//----------------------------------------------------------------------------
// Licensed under the MIT/X11 license - https://opensource.org/licenses/MIT
//----
// Copyright (c) 2018, Codalogic Ltd (http://www.codalogic.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//----------------------------------------------------------------------------

#ifndef CODALOGIC_VALUE_OR
#define CODALOGIC_VALUE_OR

#include <optional>

namespace valueor {

//----------------------------------------------------------------------------
// The default validators
//----------------------------------------------------------------------------

template< typename Tvalue >
struct value_or_validator
{
	static bool is_valid( const Tvalue & v ) { return false; }
};

template< typename Tvalue >
struct value_or_validator< Tvalue * >
{
	static bool is_valid( const Tvalue * const p_v ) { return p_v; }
};

//----------------------------------------------------------------------------
// The functions
//----------------------------------------------------------------------------

template < typename Texception, typename Tvalue >
const Tvalue & value_or( const Tvalue & v )
{
	if( ! value_or_validator<const Tvalue &>::is_valid( v ) )
		throw Texception();
	return v;
}

template < typename Texception, typename Tvalue >
Tvalue & value_or( Tvalue & v )
{
	if( ! value_or_validator<const Tvalue &>::is_valid( v ) )
		throw Texception();
	return v;
}

template < typename Texception, typename Tvalue >
const Tvalue * value_or( const Tvalue * p_v )
{
	if( ! value_or_validator<const Tvalue *>::is_valid( p_v ) )
		throw Texception();
	return p_v;
}

template < typename Texception, typename Tvalue >
Tvalue * value_or( Tvalue * p_v )
{
	if( ! value_or_validator<const Tvalue *>::is_valid( p_v ) )
		throw Texception();
	return p_v;
}

template < typename Texception, typename Tvalue >
const Tvalue & value_or( const std::optional<Tvalue> & v )
{
	if( ! v.has_value() )
		throw Texception();
	return v.value();
}

template < typename Texception, typename Tvalue >
Tvalue & value_or( std::optional<Tvalue> & v )
{
	if( ! v.has_value() )
		throw Texception();
	return v.value();
}

//template < typename Texception >
//int * value_or( int * p_v )
//{
//	if( ! value_or_validator<int *>::is_valid( p_v ) )
//		throw Texception();
//	return p_v;
//}

} // End of namespace valueor

#endif	// CODALOGIC_VALUE_OR
