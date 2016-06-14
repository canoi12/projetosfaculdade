#include "pipeline.h"
#include<iostream>

Pipeline::Pipeline()
{
    estagio[IF] = Instruction("(","(","(","(","(","(","(","(");
    estagio[ID] = Instruction("(","(","(","(","(","(","(","(");
    estagio[EX] = Instruction("(","(","(","(","(","(","(","(");
    estagio[MEM] = Instruction("(","(","(","(","(","(","(","(");
    estagio[WB] = Instruction("(","(","(","(","(","(","(","(");
            
}

bool Pipeline::push(Instruction inst)
{
    if(&inst == NULL)
    {
        return false;
    }
    else{    
        estagio[IF] = inst;
        return true;
    }
}

bool Pipeline::checkDep(Instruction inst)
{
    /*if(inst.m_id != IF.m_dep[0] && inst.m_id != ID.m_dep[0] && inst.m_id != EX.m_dep[0] && 
       inst.m_id!= IF.m_dep[1] && inst.m_id != ID.m_dep[1] && inst.m_id != EX.m_dep[1] && 
       inst.m_id != IF.m_dep[2] && inst.m_id != ID.m_dep[2] && inst.m_id != EX.m_dep[2])
    {*/
    if(inst.m_dep[0] != estagio[IF].m_id && inst.m_dep[0] != estagio[ID].m_id && inst.m_dep[0] != estagio[EX].m_id && 
       inst.m_dep[1] != estagio[IF].m_id && inst.m_dep[1] != estagio[ID].m_id && inst.m_dep[1] != estagio[EX].m_id && 
       inst.m_dep[2] != estagio[IF].m_id && inst.m_dep[2] != estagio[ID].m_id && inst.m_dep[2] != estagio[EX].m_id)
    {
        return false;
    }
    else
    {
        return true;
    }
    return true;
}

void Pipeline::move()
{
    estagio[WB] = estagio[MEM];
    estagio[MEM] = estagio[EX];
    estagio[EX] = estagio[ID];
    estagio[ID] = estagio[IF];
    estagio[IF] = Instruction("(","(","(","(","(","(","(","(");
}