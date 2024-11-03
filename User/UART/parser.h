#ifndef _PARSER_H
#define _PARSER_H

#include <cstdint>

#define COMMAND_COUNT 5

class Parser
{
public:
    struct cmd_t
    {
        char *name;
        bool occupied;
        uint32_t hash;
        float *modify_target;
        void (*cmd_callback)(char *name, float *argv, uint16_t arg_len){};
    };
    Parser();
    bool Register(char *_name, void (*_cb)(char *name, float *argv, uint16_t arg_len), float *_target);
    bool Parse(char *str, float *argv, uint16_t arg_len);
private:
    const uint32_t P = 131;
    cmd_t cmd_list[COMMAND_COUNT];
    uint32_t GetHash(char *str);
};

#endif