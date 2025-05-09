/* David Wang
   CSE 140
*/

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include "computer.h"
#undef mips			/* gcc already has a def for mips */

unsigned int endianSwap(unsigned int);

void PrintInfo (int changedReg, int changedMem);
unsigned int Fetch (int);
void Decode (unsigned int, DecodedInstr*, RegVals*);
int Execute (DecodedInstr*, RegVals*);
int Mem(DecodedInstr*, int, int *);
void RegWrite(DecodedInstr*, int, int *);
void UpdatePC(DecodedInstr*, int);
void PrintInstruction (DecodedInstr*);

/*Globally accessible Computer variable*/
Computer mips;
RegVals rVals;

/*
 *  Return an initialized computer with the stack pointer set to the
 *  address of the end of data memory, the remaining registers initialized
 *  to zero, and the instructions read from the given file.
 *  The other arguments govern how the program interacts with the user.
 */
void InitComputer (FILE* filein, int printingRegisters, int printingMemory,
  int debugging, int interactive) {
    int k;
    unsigned int instr;

    /* Initialize registers and memory */

    for (k=0; k<32; k++) {
        mips.registers[k] = 0;
    }
    
    /* stack pointer - Initialize to highest address of data segment */
    mips.registers[29] = 0x00400000 + (MAXNUMINSTRS+MAXNUMDATA)*4;

    for (k=0; k<MAXNUMINSTRS+MAXNUMDATA; k++) {
        mips.memory[k] = 0;
    }

    k = 0;
    while (fread(&instr, 4, 1, filein)) {
	/*swap to big endian, convert to host byte order. Ignore this.*/
        mips.memory[k] = ntohl(endianSwap(instr));
        k++;
        if (k>MAXNUMINSTRS) {
            fprintf (stderr, "Program too big.\n");
            exit (1);
        }
    }

    mips.printingRegisters = printingRegisters;
    mips.printingMemory = printingMemory;
    mips.interactive = interactive;
    mips.debugging = debugging;
}

unsigned int endianSwap(unsigned int i) {
    return (i>>24)|(i>>8&0x0000ff00)|(i<<8&0x00ff0000)|(i<<24);
}

/*
 *  Run the simulation.
 */
void Simulate () {
    char s[40];  /* used for handling interactive input */
    unsigned int instr;
    int changedReg=-1, changedMem=-1, val;
    DecodedInstr d;
    
    /* Initialize the PC to the start of the code section */
    mips.pc = 0x00400000;
    while (1) {
        if (mips.interactive) {
            printf ("> ");
            fgets (s,sizeof(s),stdin);
            if (s[0] == 'q') {
                return;
            }
        }

        /* Fetch instr at mips.pc, returning it in instr */
        instr = Fetch (mips.pc);

        printf ("Executing instruction at %8.8x: %8.8x\n", mips.pc, instr);

        /* 
	 * Decode instr, putting decoded instr in d
	 * Note that we reuse the d struct for each instruction.
	 */
        Decode (instr, &d, &rVals);

        /*Print decoded instruction*/
        PrintInstruction(&d);

        /* 
	 * Perform computation needed to execute d, returning computed value 
	 * in val 
	 */
        val = Execute(&d, &rVals);

	UpdatePC(&d,val);

        /* 
	 * Perform memory load or store. Place the
	 * address of any updated memory in *changedMem, 
	 * otherwise put -1 in *changedMem. 
	 * Return any memory value that is read, otherwise return -1.
         */
        val = Mem(&d, val, &changedMem);

        /* 
	 * Write back to register. If the instruction modified a register--
	 * (including jal, which modifies $ra) --
         * put the index of the modified register in *changedReg,
         * otherwise put -1 in *changedReg.
         */
        RegWrite(&d, val, &changedReg);

        PrintInfo (changedReg, changedMem);
    }
}

/*
 *  Print relevant information about the state of the computer.
 *  changedReg is the index of the register changed by the instruction
 *  being simulated, otherwise -1.
 *  changedMem is the address of the memory location changed by the
 *  simulated instruction, otherwise -1.
 *  Previously initialized flags indicate whether to print all the
 *  registers or just the one that changed, and whether to print
 *  all the nonzero memory or just the memory location that changed.
 */
void PrintInfo ( int changedReg, int changedMem) {
    int k, addr;
    printf ("New pc = %8.8x\n", mips.pc);
    if (!mips.printingRegisters && changedReg == -1) {
        printf ("No register was updated.\n");
    } else if (!mips.printingRegisters) {
        printf ("Updated r%2.2d to %8.8x\n",
        changedReg, mips.registers[changedReg]);
    } else {
        for (k=0; k<32; k++) {
            printf ("r%2.2d: %8.8x  ", k, mips.registers[k]);
            if ((k+1)%4 == 0) {
                printf ("\n");
            }
        }
    }
    if (!mips.printingMemory && changedMem == -1) {
        printf ("No memory location was updated.\n");
    } else if (!mips.printingMemory) {
        printf ("Updated memory at address %8.8x to %8.8x\n",
        changedMem, Fetch (changedMem));
    } else {
        printf ("Nonzero memory\n");
        printf ("ADDR	  CONTENTS\n");
        for (addr = 0x00400000+4*MAXNUMINSTRS;
             addr < 0x00400000+4*(MAXNUMINSTRS+MAXNUMDATA);
             addr = addr+4) {
            if (Fetch (addr) != 0) {
                printf ("%8.8x  %8.8x\n", addr, Fetch (addr));
            }
        }
    }
}

/*
 *  Return the contents of memory at the given address. Simulates
 *  instruction fetch. 
 */
unsigned int Fetch ( int addr) {
    return mips.memory[(addr-0x00400000)/4];
}

/* Decode instr, returning decoded instruction. */
void Decode ( unsigned int instr, DecodedInstr* d, RegVals* rVals) {

	//(instruction to be decoded, d to store op, reg vals rs, rt, rd)

    /* Your code goes here */

    //read instruction and split into fields

    d->op = instr >> 26; //since opcode is leftmost 6 bits, shift right to seperate

        switch ((op)d->op) //check op struct values, and d's member op value
        {
            case 0: //if op = 0

            d->type = R; // d's type = R, op rs rt rd shamt funct	

            //instr & hex number to turn all the other fields to 0, then shift the remaining portion accordingly to the right to isolate field value.


            //store into rVals struct members	
            rVals->R_rs = mips.registers[d->regs.r.rs = (instr & 0x03e00000) >> 21]; //shift right by 21 to seperate rs
            rVals->R_rt = mips.registers[d->regs.r.rt = (instr & 0x001f0000) >> 16]; //shift right by 16 to seperate rt
            rVals->R_rd = mips.registers[d->regs.r.rd = (instr & 0x0000f800) >> 11]; //shift left by 11 to seperate rd
            d->regs.r.shamt = (instr & 0x000007c0) >> 6; //shift right by 6 to seperate shamt field
            d->regs.r.funct = instr & 0x0000003f; //last 6 are funct
                break;  
        case j: //if opcode = j opcode

        case jal:   //if opcode = jal opcode
            d->type = J; // J-type
            d->regs.j.target = instr & 0x03ffffff;
                break;

        default: //else, I type

            d->type = I; // I-type, op rs rt address
            rVals->R_rs = mips.registers[d->regs.i.rs = (instr & 0x03e00000) >> 21];
            rVals->R_rt = mips.registers[d->regs.i.rt = (instr & 0x001f0000) >> 16];
            d->regs.i.addr_or_immed = (short)(instr & 0x0000ffff); //sign extend to 16 bit value.
        }
}

/*
 *  Print the disassembled version of the given instruction
 *  followed by a newline.
 */
void PrintInstruction ( DecodedInstr* d) {
    /* Your code goes here */
    char* print; //instr type to print out
    
    //prints instr type based on op and funct, checks with header values

    switch ((op)(d->op)) 
    {
        case 0: //if opcode is 0,
            switch ((fnc)(d->regs.r.funct)) 
            {
            	//if opcode is 0 and funct matches

                case 0x00:
                    print = "sll"; //corresponds with header values.
                            break;
                case 0x02:
                    print = "srl"; 
                            break;
                case 0x08:
                    print = "jr"; 
                            break;
                case 0x21:
                    print = "addu"; 
                            break;
                case 0x23:
                    print = "subu"; 
                            break;
                case 0x24:
                    print = "and";
                            break;
                case 0x25:
                    print = "or"; 
                            break;
                case 0x2A:
                    print = "slt"; 
                            break;
                default:
                    exit(1);
            } 
                
            break;

        //if opcode matches

        case 0x02:
            print = "j"; 
                    break;
        case 0x03:
            print = "jal"; 
                    break;
        case 0x04:
            print = "beq"; 
                    break;
        case 0x05:
            print = "bne"; 
                    break;
        case 0x09:
            print = "addiu"; 
                    break;
        case 0x0C:
            print = "andi"; 
                    break;
        case 0x0D:
            print = "ori"; 
                    break;
        case 0x0f:
            print = "lui"; 
                    break;
        case 0x23:
            print = "lw"; 
                    break;
        case 0x2B:
            print = "sw"; 
                    break;
        default:
            exit(1);
    }

    //stores rs, rt, rd, immediate into variables to use

    int rs = d->regs.r.rs; 
    int rt = d->regs.r.rt;
    int rd = d->regs.r.rd;
    short immediate = d->regs.i.addr_or_immed;

    //printing fields for different types, checks d's type member

    switch (d->type) { 

    //if d's type = R

        case R:
            switch ((fnc)(d->regs.r.funct)) //check if fnc struct values are equal to d's r.funct value
            {

            // sll  
                case 0x00: 
            // srl
                case 0x02: 
                    printf("%s\t$%d, $%d, %d\n", print, rd, rt, d->regs.r.shamt); 	
                        return;
            // jr
                case 0x08:
                    printf("%s\t$%d\n", print, rs); 
                        return;
                default:
                    printf("%s\t$%d, $%d, $%d\n", print, rd, rs, rt); 
                        return;
            }

        case I:
            switch ((op)(d->op)) 
            {
            // beq
                case 0x04:
            // bne
                case 0x05:
                	//to calculate address, sign extend to 16 bit, multiply by 4 (shift left 2), then add to pc + 4.
                    printf("%s\t$%d, $%d, 0x%.8x\n", print, rs, rt, mips.pc + 4 + (immediate << 2)); 
                        return;
            // addiu
                case 0x09:
                    printf("%s\t$%d, $%d, %d\n", print, rt, rs, immediate); 
                        return;
            // andi
                case 0x0C:
            // ori
                case 0x0D:
            // lui
                case 0x0f:
                    printf("%s\t$%d, $%d, 0x%x\n", print, rt, rs, (unsigned short)immediate); 
                        return;
            // lw
                case 0x23:
            // sw
                case 0x2B:
                    printf("%s\t$%d, %d($%d)\n", print, rt, immediate, rs); 
                        return;
            }


        case J:

        //calulating jump address, replace lower 28 bits of PC with lower 26 bits of the fetched immediate (converted to word-aligned)

        //(mips.pc & 0xf0000000) replaces every bit with 0 except first 4 for PC)

        //(d->regs.j.target << 2) puts the immediate into word-aligned form. Then, & 0x0fffffff to put it into 32 bit

       	//the bitwise | concatenates the leftwise 4 bits from PC to the 28 bits from target, resulting in J address

            printf("%s\t0x%.8x\n", print, (mips.pc & 0xf0000000) | ((d->regs.j.target << 2) & 0x0fffffff));                     
                    return;


    }
}

/* Perform computation needed to execute d, returning computed value */
int Execute ( DecodedInstr* d, RegVals* rVals) {
    /* Your code goes here */

	//(decoded instruction with op + regs, rVals with rs rt rd)

    switch ((op)d->op) 
    {
        case 0: //ALU computations based on the type of instruction, using opcode and funct values to check type

            switch ((fnc)d->regs.r.funct) 
            {
            // sll
                case 0x00:

                	//shifts rt value left by the shift amount, rt << shamt

                    return rVals->R_rt << d->regs.r.shamt;
            // srl
                case 0x02:

                	//shifts rt value right by shift amount, rt >> shamt

                    return (unsigned int)rVals->R_rt >> d->regs.r.shamt;

            // jr
                case 0x08:

                	//returns rs to be used later.

                    return rVals->R_rs;
            // addu
                case 0x21:

                	//adds rs and rt and returns value to be written to register

                    return rVals->R_rs + rVals->R_rt;
            // subu
                case 0x23:

                	//performs rs - rt, returns value to be written to register

                    return rVals->R_rs - rVals->R_rt;
            // and
                case 0x24:

                	//returns rs & rt

                    return rVals->R_rs & rVals->R_rt;
            // or
                case 0x25:

                	//returns rs | rt

                    return rVals->R_rs | rVals->R_rt;
            // slt
                case 0x2A:

                	//returns 1 if rs < rt

                    return rVals->R_rs < rVals->R_rt;
            } 

            break;
    
    // j
        case 0x02:

        	//target address calculated in print

            break;
    // jal
        case 0x03:

        	//$31 = PC + 4

            return mips.pc + 4;
    // beq
        case 0x04:

        	//checks if rs = rt, returns 1 if true

            return rVals->R_rs == rVals->R_rt;
    // bne
        case 0x05:

        	//checks if rs != rt, returns 1 if true

            return rVals->R_rs != rVals->R_rt;
    // addiu
        case 0x09:

        	//adds rs with immediate returns result

            return rVals->R_rs + d->regs.i.addr_or_immed;
    // andi
        case 0x0C:

        	//bitwise and, rs & immediate, returns result

            return rVals->R_rs & d->regs.i.addr_or_immed;
    // ori
        case 0x0D:

        	//bitwise or, rs | immediate, returns result

            return rVals->R_rs | d->regs.i.addr_or_immed;
    // lui
        case 0x0f:

        	//returns immediate, shifted left by 16

            return d->regs.i.addr_or_immed << 16;
    // lw
        case 0x23:

        //calculations done in regwrite

    // sw
        case 0x2B:

        	//adds address in rs + offset to calculate address to update

            return rVals->R_rs + (short)d->regs.i.addr_or_immed;
    }
  return 0;
}

/* 
 * Update the program counter based on the current instruction. For
 * instructions other than branches and jumps, for example, the PC
 * increments by 4 (which we have provided).
 */
void UpdatePC ( DecodedInstr* d, int val) {

    mips.pc+=4; //PC points to next word, unless its branch or jump instruction.

    //for dealing with jr, treat as R type and use the rs field.
    if (d->type == R && (fnc)d->regs.r.funct == jr)
    {
    	//if type is R and fnc struct and funct match with jr,

        mips.pc = mips.registers[d->regs.r.rs]; //pc address equal to the return address stored in rs.
    }
    else if ((op)d->op == beq || (op)d->op == bne) {

    	//if branch statement, address is changed to word-aligned immediate address

        if (val)
        {
            mips.pc += (short) d->regs.i.addr_or_immed << 2; //mip
        }
    }
    else if (d->type == J)
    {
    	//concatenates first 4 bits of PC with word-aligned 28 bits of target address to get updated address
        mips.pc = (mips.pc & 0xf0000000) | ((d->regs.j.target << 2) & 0x0fffffff);
    }
    if(mips.pc < 0x00400000 || mips.pc > 0x00401000 || mips.pc % 4 != 0)
    {
    	//if PC address is out of bounds, or is not word-aligned.
        exit(3);
    }

}

/*
 * Perform memory load or store. Place the address of any updated memory 
 * in *changedMem, otherwise put -1 in *changedMem. Return any memory value 
 * that is read, otherwise return -1. 
 *
 * Remember that we're mapping MIPS addresses to indices in the mips.memory 
 * array. mips.memory[0] corresponds with address 0x00400000, mips.memory[1] 
 * with address 0x00400004, and so forth.
 *
 */
int Mem( DecodedInstr* d, int val, int *changedMem) {
    /* Your code goes here */
    if (((op)d->op == lw || (op)d->op == sw) && ( val % 4 !=0|| val < 0x00401000 ||val > 0x00403fff )) 
    {
    	//if the calculated mem address is out of bounds or not word-aligned
        printf("Memory Access Exception at 0x%.8x: address 0x%.8x", mips.pc - 4, val);
        exit(2);
    }
    *changedMem = -1;

    switch ((op)d->op) 
    { 
    
    // lw       
        case 0x23:

        	//calculated memory address to load from, minus address of mem[0] for address, converts to word-aligned

            return mips.memory[(val - 0x00400000) >> 2]; //returns value at mem[address]
    // sw
        case 0x2B:

        	//updates changedMem with val, which contains the address to store to.
        	//memory address at word-aligned[val - mem[0]] = rt. (Stores rt into that address)
            mips.memory[((*changedMem = val) - 0x00400000) >> 2] = mips.registers[d->regs.i.rt]; 

            break;
    }
    return val;   //else return val
}

/* 
 * Write back to register. If the instruction modified a register--
 * (including jal, which modifies $ra) --
 * put the index of the modified register in *changedReg,
 * otherwise put -1 in *changedReg.
 */
void RegWrite( DecodedInstr* d, int val, int *changedReg) {
    /* Your code goes here */
        *changedReg = -1;

    switch ((op)d->op) {
        case 0:
            switch ((fnc)d->regs.r.funct){
            // sll
                case 0x00:
            // srl              
                case 0x02:
            // addu
                case 0x21:
            // subu
                case 0x23:
            // and
                case 0x24:
            // or
                case 0x25:
            // slt
                case 0x2A:
                    *changedReg = d->regs.r.rd; //updated rd value
                    mips.registers[d->regs.r.rd] = val; //mips[rd] assigned value from calculations
                        return;     
            } return;
    // jal      
        case 0x03:
            *changedReg = 31; //$31 changed for jal instructions
            mips.registers[31] = val; //register[31] assigned value from calculations.
                return;
    // addiu
        case 0x09:
    // andi
        case 0x0C:
    // ori
        case 0x0D:
    // lui
        case 0x0f:
    // lw
        case 0x23:
            *changedReg = d->regs.i.rt; //memory stored into rt
            mips.registers[d->regs.i.rt] = val; //rt updated with val from mem calculations
                return;
    }
}
