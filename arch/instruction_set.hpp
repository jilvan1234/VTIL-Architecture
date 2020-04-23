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
#pragma once
#include <vector>
#include <vtil/math>
#include "instruction_desc.hpp"

namespace vtil
{
    namespace ins
    {
        using op = math::operator_id;
        using a = operand_access;

        //  -- Data/Memory instructions
        //
        //    MOV        Reg,    Reg/Imm                                     | OP1 = OP2
        //    MOVR       Reg,    Imm                                         | OP1 = Relocate(OP2)
        //    STR        Reg,    Imm,    Reg/Imm                             | [OP1+OP2] <= OP3
        //    LDD        Reg,    Reg,    Imm                                 | OP1 <= [OP2+OP3]
        //
        /*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
        /*                                          [Name]        [Operands...]                                     [ASizeOp]   [Volatile]  [Operator]               [BranchOps] [MemOps]     */
        static const instruction_desc mov =        { "mov",        { a::write,    a::read_any                   },    2,          false,      {},         {},         {}           };
        static const instruction_desc movr =       { "movr",       { a::write,    a::read_imm                   },    2,          false,      {},         {},         {}           };
        static const instruction_desc str =        { "str",        { a::read_reg, a::read_imm,     a::read_any  },    3,          false,      {},         {},         { 1, true }  };
        static const instruction_desc ldd =        { "ldd",        { a::write,    a::read_reg,     a::read_imm  },    1,          false,      {},         {},         { 2, false } };
        /*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

        //    -- Arithmetic instructions
        //
        //    NEG        Reg                                                 | OP1 = -OP1
        //    ADD        Reg,    Reg/Imm                                     | OP1 = OP1 + OP2
        //    SUB        Reg,    Reg/Imm                                     | OP1 = OP1 - OP2
        //    MUL        Reg,    Reg/Imm                                     | OP1 = OP1 * OP2
        //    MULHI      Reg,    Reg/Imm                                     | OP1 = [OP1 * OP2]>>N
        //    IMUL       Reg,    Reg/Imm                                     | OP1 = OP1 * OP2         (Signed)
        //    IMULHI     Reg,    Reg/Imm                                     | OP1 = [OP1 * OP2]>>N    (Signed)
        //    DIV        Reg,    Reg/Imm    Reg/Imm                          | OP1 = [OP2:OP1] / OP3         
        //    REM        Reg,    Reg/Imm                                     | OP1 = OP1 % OP2         
        //    IDIV       Reg,    Reg/Imm    Reg/Imm                          | OP1 = [OP2:OP1] / OP3   (Signed)
        //    IREM       Reg,    Reg/Imm                                     | OP1 = OP1 % OP2         (Signed)
        //
        /*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
        /*                                          [Name]        [Operands...]                                     [ASizeOp]   [Volatile]  [Operator]               [BranchOps] [MemOps]     */
        static const instruction_desc neg =        { "neg",       { a::readwrite                                 },    1,            false,    op::negate,              {},         {}           };
        static const instruction_desc add =        { "add",       { a::readwrite,  a::read_any                   },    1,            false,    op::add,                 {},         {}           };
        static const instruction_desc sub =        { "sub",       { a::readwrite,  a::read_any                   },    1,            false,    op::substract,           {},         {}           };
        static const instruction_desc mul =        { "mul",       { a::readwrite,  a::read_any                   },    1,            false,    op::umultiply,           {},         {}           };
        static const instruction_desc imul =       { "imul",      { a::readwrite,  a::read_any                   },    1,            false,    op::multiply,            {},         {}           };
        static const instruction_desc mulhi =      { "mulhi",     { a::readwrite,  a::read_any                   },    1,            false,    op::multiply_high,       {},         {}           };
        static const instruction_desc imulhi =     { "imulhi",    { a::readwrite,  a::read_any                   },    1,            false,    op::umultiply_high,      {},         {}           };
        static const instruction_desc div =        { "div",       { a::readwrite,  a::read_any,     a::read_any  },    1,            false,    op::udivide,             {},         {}           };
        static const instruction_desc idiv =       { "idiv",      { a::readwrite,  a::read_any,     a::read_any  },    1,            false,    op::divide,              {},         {}           };
        static const instruction_desc rem =        { "rem",       { a::readwrite,  a::read_any,     a::read_any  },    1,            false,    op::uremainder,          {},         {}           };
        static const instruction_desc irem =       { "irem",      { a::readwrite,  a::read_any,     a::read_any  },    1,            false,    op::remainder,           {},         {}           };
        /*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    
        //  -- Bitwise instructions
        //
        //    NOT        Reg                                                 | OP1 = ~OP1
        //    SHR        Reg,    Reg/Imm                                     | OP1 >>= OP2
        //    SHL        Reg,    Reg/Imm                                     | OP1 <<= OP2
        //    XOR        Reg,    Reg/Imm                                     | OP1 ^= OP2
        //    OR         Reg,    Reg/Imm                                     | OP1 |= OP2
        //    AND        Reg,    Reg/Imm                                     | OP1 &= OP2
        //    ROR        Reg,    Reg/Imm                                     | OP1 = (OP1>>OP2) | (OP1<<(N-OP2))
        //    ROL        Reg,    Reg/Imm                                     | OP1 = (OP1<<OP2) | (OP1>>(N-OP2))
        //
        /*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
        /*                                          [Name]        [Operands...]                                     [ASizeOp]   [Volatile]  [Operator]               [BranchOps] [MemOps]     */
        static const instruction_desc bnot =        { "not",      { a::readwrite                                 },    1,          false,      op::bitwise_not,         {},          {}          };
        static const instruction_desc bshr =        { "shr",      { a::readwrite,  a::read_any                   },    1,          false,      op::shift_right,         {},          {}          };
        static const instruction_desc bshl =        { "shl",      { a::readwrite,  a::read_any                   },    1,          false,      op::shift_left,          {},          {}          };
        static const instruction_desc bxor =        { "xor",      { a::readwrite,  a::read_any                   },    1,          false,      op::bitwise_xor,         {},          {}          };
        static const instruction_desc bor =         { "or",       { a::readwrite,  a::read_any                   },    1,          false,      op::bitwise_xor,         {},          {}          };
        static const instruction_desc band =        { "and",      { a::readwrite,  a::read_any                   },    1,          false,      op::bitwise_and,         {},          {}          };
        static const instruction_desc bror =        { "ror",      { a::readwrite,  a::read_any                   },    1,          false,      op::rotate_right,        {},          {}          };
        static const instruction_desc brol =        { "rol",      { a::readwrite,  a::read_any                   },    1,          false,      op::rotate_left,         {},          {}          };
        /*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    
        //  -- Control flow instructions
        //                                                            
        //    JS         Reg,    Reg/Imm,    Reg/Imm                        | Jumps to OP3 if OP1 != 0, else jumps to OP2, continues virtual execution
        //    JMP        Reg/Imm                                            | Jumps to OP1, continues virtual execution
        //    VEXIT      Reg/Imm                                            | Jumps to OP1, continues real execution
        //    VXCALL     Reg/Imm                                            | Calls into OP1, pauses virtual execution until the call returns
        //
        /*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
        /*                                          [Name]        [Operands...]                                     [ASizeOp]   [Volatile]  [Operator]               [BranchOps] [MemOps]     */
        static const instruction_desc js =         { "js",        { a::read_reg,   a::read_any,     a::read_any    },  2,          true,        {},                     { 1, 2 },    {}          };
        static const instruction_desc jmp =        { "jmp",       { a::read_any                                    },  1,          true,        {},                     { 1 },       {}          };
        static const instruction_desc vexit =      { "vexit",     { a::read_any                                    },  1,          true,        {},                     { -1 },      {}          };
        static const instruction_desc vxcall =     { "vxcall",    { a::read_any                                    },  1,          true,        {},                     {},          {}          };
        /*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

        //    -- Special instructions
        //
        //    NOP                                                           | Placeholder
        //    UPFLGW     Reg                                                | Indicates that flags were updated according to the previous instruction and written into OP1.
        //    VSETCC     Reg,    Imm                                        | Emits SETcc on OP1 based on the [OP2]th bit of RFLAGS
        //    VEMIT      Imm                                                | Emits the opcode as is to the final instruction stream.
        //    VPINR      Reg                                                | Pins the register for read
        //    VPINW      Reg                                                | Pins the register for write
        //    VPINRM     Reg,    Imm                                        | Pins the qword @ memory location for read
        //    VPINWM     Reg,    Imm                                        | Pins the qword @ memory location for write
        //
        /*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
        /*                                          [Name]        [Operands...]                                     [ASizeOp]   [Volatile]  [Operator]               [BranchOps] [MemOps]     */
        static const instruction_desc nop =        { "nop",       {                                             },  0,          false,      {},                      {},         {}           };
        static const instruction_desc upflg =      { "upflg",     { a::readwrite                                },  1,          false,      {},                      {},         {}           };
        static const instruction_desc vsetcc =     { "vsetcc",    { a::write,      a::read_imm                  },  1,          false,      {},                      {},         {}           };
        static const instruction_desc vemit =      { "vemit",     { a::read_imm                                 },  1,          true,       {},                      {},         {}           };
        static const instruction_desc vpinr =      { "vpinr",     { a::read_reg                                 },  1,          true,       {},                      {},         {}           };
        static const instruction_desc vpinw =      { "vpinw",     { a::write                                    },  1,          true,       {},                      {},         {}           };
        static const instruction_desc vpinrm =     { "vpinrm",    { a::read_reg,   a::read_imm,                 },  1,          true,       {},                      {},         { 1, false } };
        static const instruction_desc vpinwm =     { "vpinwm",    { a::read_reg,   a::read_imm                  },  1,          true,       {},                      {},         { 1, true }  };
        /*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    };

    // List of all instructions.
    //
    static const instruction_desc instruction_list[] = 
    {
        ins::mov, ins::movr, ins::str, ins::ldd, ins::neg, ins::add, ins::sub, ins::mul,
        ins::imul, ins::mulhi, ins::imulhi, ins::div, ins::idiv, ins::rem, ins::irem, ins::bnot,
        ins::bshr, ins::bshl, ins::bxor, ins::bor, ins::band, ins::bror, ins::brol, ins::upflg,
        ins::js, ins::jmp, ins::vexit, ins::vxcall, ins::nop, ins::vsetcc, ins::vemit, 
        ins::vpinr, ins::vpinw, ins::vpinrm, ins::vpinwm
    };
};