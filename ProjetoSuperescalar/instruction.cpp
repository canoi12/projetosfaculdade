#include"instruction.h"

Instruction::Instruction()
{
    
}

Instruction::Instruction(string id, string type, string rg1, string rg2, string rg3, string dep1,string dep2, string dep3)
{
    m_id = id;
    m_type = type;
    m_rg1 = rg1;
    m_rg2 = rg2;
    m_rg3 = rg3;
    
    m_dep[0] = dep1;
    m_dep[1] = dep2;
    m_dep[2] = dep3;
}