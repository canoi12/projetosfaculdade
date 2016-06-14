#pragma once
#include<string>

using namespace std;

class Instruction
{
    public:
    string m_id;
    string m_type;
    string m_rg1;
    string m_rg2;
    string m_rg3;
    string m_dep[3];
    
    Instruction();
    
    Instruction(string id, string type, string rg1, string rg2, string rg3, string dep1,string dep2, string dep3);
};