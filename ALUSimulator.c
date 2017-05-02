//*****************************************************************************
//--ALUSimulator.c
//
//		Author: 		Gary J. Minden
//		Organization:	KU/EECS/EECS 645
//		Date:			2017-04-22 (B70422)
//		Version:		1.0
//		Description:	This is the test standin for a simple ALU simulator
//		Notes:
//
//*****************************************************************************
//

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>

#include <stdio.h>

#include "RegisterFile_01.h"
#include "ALUSimulator.h"

extern void ALUSimulator( RegisterFile theRegisterFile,
				uint32_t OpCode,
				uint32_t Rs, uint32_t Rt, uint32_t Rd,
				uint32_t ShiftAmt,
				uint32_t FunctionCode,
				uint32_t ImmediateValue,
				uint32_t* Status ) {


  uint32_t Rdvalue = 0;
  uint32_t RdValue_S;
  uint32_t RdValue_T;
  RegisterFile_Read(theRegisterFile, Rs, &RdValue_S, Rt, &RdValue_T);
	printf( ">>ALU: Opcode: %02X; Rs: %02X; Rt: %02X; Rd: %02X;\n",
				OpCode,
				Rs,
				Rt,
				Rd );

	printf( ">>>>ALU: ShiftAmt: %02X; FunctionCode: %02X; ImmediateValue: %04X;\n",
				ShiftAmt,
				FunctionCode,
				ImmediateValue );


  //If statement to determine whether R type or I type instruction
  if(OpCode == 00){
    switch(FunctionCode){
      case 00 : //SLL
        Rdvalue = (RdValue_T << ShiftAmt);
        break;

      case 02 : //SRL
        Rdvalue = (int)((unsigned int)RdValue_T >> ShiftAmt) ;
        break;

      case 03 : //SRA
        Rdvalue = (RdValue_S >> ShiftAmt);
        break;

      case 04 : //SLLV
        Rdvalue = (int)((unsigned int)RdValue_S << RdValue_T);
        break;

      case 06 : //SLRV
        Rdvalue = (int)((unsigned int)RdValue_S >> RdValue_T);
        break;

      case 32 : //ADD
        Rdvalue = RdValue_S + RdValue_T;
        break;

      case 33 : //ADDU
        Rdvalue = (int)(unsigned int)RdValue_S + (int)(unsigned int)RdValue_T;
        break;

      case 34 : //SUB
        Rdvalue = RdValue_S - RdValue_T;
        break;

      case 35 : //SUBU
        Rdvalue = (int)(unsigned int)RdValue_S - (int)(unsigned int)RdValue_T;
        break;

      case 36 : //AND
        Rdvalue = RdValue_S & RdValue_T;
        break;

      case 37 : //OR
        Rdvalue = RdValue_S | RdValue_T;
        break;

      case 38 : //XOR
        Rdvalue = RdValue_S ^ RdValue_T;
        break;

      case 42 : //SLT
        Rdvalue = RdValue_S < RdValue_T ? 1 : 0;
        break;

      case 43 : //SLTU
        Rdvalue = (int)(unsigned int)RdValue_S < (int)(unsigned int)RdValue_T ? 1 : 0;
        break;
    }//end switch
		//printf("%02X\n", Rdvalue);
		RegisterFile_Write(theRegisterFile, 1, Rd, Rdvalue);

  }
  else if(OpCode == 8){
		Rdvalue = RdValue_S + (int32_t)(int16_t)ImmediateValue;
		RegisterFile_Write(theRegisterFile, 1, Rt, Rdvalue);
  }
	else if(OpCode == 9){
		Rdvalue = (int)(unsigned int)RdValue_S + (int32_t)(int16_t)ImmediateValue;
		RegisterFile_Write(theRegisterFile, 1, Rt, Rdvalue);
	}
	else if(OpCode == 10){
		Rdvalue = RdValue_S < (int32_t)(int16_t)ImmediateValue ? 1 : 0;
		RegisterFile_Write(theRegisterFile, 1, Rt, Rdvalue);
	}
	else if(OpCode == 11){
		Rdvalue = (int)(unsigned int)RdValue_S < (int32_t)(int16_t)ImmediateValue ? 1 : 0;
		RegisterFile_Write(theRegisterFile, 1, Rt, Rdvalue);
	}

}
