// Copyright (c) 2020 Can Boluk and contributors of the VTIL Project   
// All rights reserved.   
//    
// Redistribution and use in source and binary forms, with or without   
// modification, are permitted provided that the following conditions are met: 
//    
// 1. Redistributions of source code must retain the above copyright notice,   
//    this list of conditions and the following disclaimer.   
// 2. Redistributions in binary form must reproduce the above copyright   
//    notice, this list of conditions and the following disclaimer in the   
//    documentation and/or other materials provided with the distribution.   
// 3. Neither the name of mosquitto nor the names of its   
//    contributors may be used to endorse or promote products derived from   
//    this software without specific prior written permission.   
//    
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE   
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE  
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE   
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR   
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF   
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS   
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN   
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)   
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE  
// POSSIBILITY OF SUCH DAMAGE.        
//
#include "instruction_desc.hpp"

namespace vtil
{
	// Generic data-assignment constructor with certain validity checks.
	//
	instruction_desc::instruction_desc( const std::string& name, 
										const std::vector<operand_access>& access_types, 
										int access_size_index, 
										bool is_volatile, 
										math::operator_id symbolic_operator,
										std::vector<int> branch_operands, 
										const std::pair<int, bool>& memory_operands ) :
		name( name ), access_types( access_types ), access_size_index( access_size_index - 1 ),
		is_volatile( is_volatile ), symbolic_operator( symbolic_operator ),
		memory_operand_index( memory_operands.first - 1 ), memory_write( memory_operands.second )
	{
		fassert( operand_count() <= max_operand_count );

		// Validate all operand indices.
		//
		fassert( access_size_index == 0 || abs( access_size_index ) <= operand_count() );
		fassert( memory_operands.first == 0 || abs( memory_operands.first ) <= operand_count() );
		for ( int op : branch_operands )
			fassert( op != 0 && abs( op ) <= operand_count() );

		// Process branch operands.
		//
		for ( int op : branch_operands )
		{
			if ( op > 0 )
				branch_operands_vip.push_back( op - 1 );
			else
				branch_operands_rip.push_back( -op - 1 );
		}
	}
};