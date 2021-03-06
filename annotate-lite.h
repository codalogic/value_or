//----------------------------------------------------------------------------
// Copyright (c) 2014-18, Codalogic Ltd (http://www.codalogic.com)
// All rights reserved.
//
// The license for this file is based on the BSD-3-Clause license
// (http://www.opensource.org/licenses/BSD-3-Clause).
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
// - Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// - Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
// - Neither the name Codalogic Ltd nor the names of its contributors may be
//   used to endorse or promote products derived from this software without
//   specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//----------------------------------------------------------------------------

#ifndef ANNOTATE_LITE_H
#define ANNOTATE_LITE_H

#include <string>
#include <iostream>

namespace annotate_lite {

#ifndef ANNOTATE_LITE_SECONDARY
int n_bad_things = 0;
#else
extern int n_bad_things;
#endif

void Scenario( const std::string & msg )
{
    std::cout << "\n";
    std::cout << "       " << msg << "\n";
    std::cout << "       ";
	for( size_t i=0; i< msg.size(); ++i )
		std::cout << "=";
	std::cout << "\n";
}

void Good( const std::string & msg )
{
    std::cout << "    ok: " << msg << "\n";
}

void Bad( const std::string & msg )
{
    std::cout << "not ok: " << msg << "\n";
    ++n_bad_things;
}

void Verify( bool result, const std::string & msg )
{
    result ? Good( msg ) : Bad( msg );
}

void Report()
{
    std::cout << n_bad_things << " bad thing(s) happened\n";
}

} // End of namespace annotate_lite

#endif  // ANNOTATE_LITE_H
