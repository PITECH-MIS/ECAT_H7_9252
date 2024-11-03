#include "parser.h"
Parser::Parser()
{
    for(auto &cmd : cmd_list)
    {
        cmd.name = (char*)"default";
        cmd.occupied = false;
        cmd.hash = 0;
        cmd.modify_target = nullptr;
        cmd.cmd_callback = nullptr;
    }
}

// using Rolling Hash Algorithm, P = 131
uint32_t Parser::GetHash(char *str)
{
    uint32_t result = 0;
    while(*str != '\0')
    {
        result = (result * P + (*str));
        str++;
    }
    return result;
}

bool Parser::Register(char *_name, void (*_cb)(char *name, float *argv, uint16_t arg_len), float *_target)
{
    uint32_t raw_hash = GetHash(_name);
    uint16_t slot = raw_hash % COMMAND_COUNT;
    if(cmd_list[slot].occupied)
    {
        for(uint16_t i = 0; i < COMMAND_COUNT; i++)
        {
            if(!cmd_list[i].occupied)
            {
                slot = i;
                break;
            }
        }
    }
    if(!cmd_list[slot].occupied)
    {
        cmd_list[slot].name = _name;
        cmd_list[slot].occupied = true;
        cmd_list[slot].hash = raw_hash;
        cmd_list[slot].modify_target = _target;
        cmd_list[slot].cmd_callback = _cb;
        return true;
    }
    return false;
}

bool Parser::Parse(char *str, float *argv, uint16_t arg_len)
{
    uint32_t raw_hash = GetHash(str);
    uint16_t slot = raw_hash % COMMAND_COUNT;
    if(!cmd_list[slot].occupied) return false;
    if(cmd_list[slot].hash != raw_hash) // hash conflict
    {
        for(uint16_t i = 0; i < COMMAND_COUNT; i++)
        {
            if(cmd_list[i].hash == raw_hash)
            {
                slot = i;
                break;
            }
        }
    }
    if(cmd_list[slot].hash != raw_hash || !cmd_list[slot].occupied) return false;
    if(cmd_list[slot].modify_target != nullptr)
    {
        *(cmd_list[slot].modify_target) = argv[0];
        return true;
    }
    if(cmd_list[slot].cmd_callback != nullptr)
    {
        cmd_list[slot].cmd_callback(str, argv, arg_len);
        return true;
    }
    return false;
}