#pragma once

#include "instruction.h"

class Pipeline
{
    
    enum {
        IF=0,
        ID=1,
        EX=2,
        MEM=3,
        WB=4
    };
    
    public:
    /*Instruction IF = Instruction("(","(","(","(","(","(","(","(");
    Instruction ID = Instruction("(","(","(","(","(","(","(","(");
    Instruction EX = Instruction("(","(","(","(","(","(","(","(");
    Instruction MEM = Instruction("(","(","(","(","(","(","(","(");
    Instruction WB = Instruction("(","(","(","(","(","(","(","(");*/
    
    Instruction estagio[5];
    
    
    Pipeline();
    
    bool push(Instruction inst);
    
    bool checkDep(Instruction inst);
    
    void move();
};