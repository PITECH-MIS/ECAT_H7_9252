#include "classes.hpp"
#include <set>
#include <map>

int8_t match(UART* ptr)
{
    if(ptr == &UART_1) return 1;
    if(ptr == &UART_2) return 2;
    if(ptr == &UART_3) return 3;
    if(ptr == &UART_4) return 4;
    // if(ptr == &UART_5) return 5;
    if(ptr == &UART_6) return 6;
    if(ptr == &UART_7) return 7;
    if(ptr == &UART_8) return 8;
    return -1;
}

void check_uart_cmd(char *name, float *argv, uint16_t arg_len)
{
    if(arg_len != 0) pdo_protocol.print("Invalid arg for check_uart!");
    else
    {
        char buffer[42] = {0};
        auto ptr = (uint8_t)snprintf(buffer, sizeof(buffer), "In use: UART ");
        std::map<int8_t, uint8_t> uartMap;
        // std::set<int8_t> numberSet;
        for(uint8_t i = 0; i < PROTOCOL_COUNT; i++)
        {
            if(arbiter.protocols[i].IsAlive() && arbiter.instances[i])
            {
                // numberSet.insert(match(arbiter.instances[i]));
                auto uart_id = match(arbiter.instances[i]);
                auto it = uartMap.find(uart_id);
                if(it != uartMap.end())
                {
                    it->second++;
                }
                else uartMap.emplace(std::pair<int8_t, uint8_t>(uart_id, 1));
            }
        }
        for(const auto &it : uartMap)
        {
            ptr += (uint8_t)snprintf(buffer + ptr, sizeof(buffer) - ptr, "%d(%d), ", it.first, it.second);
        }
        pdo_protocol.SendPayload(buffer, strnlen(buffer, sizeof(buffer)));
    }
}

uint16_t getLastFourDigits(uint32_t input)
{
    return (uint16_t)(input % 10000);
}

void slave_cmd(char *name, float *argv, uint16_t arg_len)
{
    if(arg_len == 0) // print all available SNs (last 4 number)
    {
        char buffer[42] = {0};
        auto ptr = (uint8_t)snprintf(buffer, sizeof(buffer), "Alive SN: ");
        for(uint8_t i = 0; i < PROTOCOL_COUNT; i++)
        {
            if(arbiter.protocols[i].IsAlive() && arbiter.instances[i])
            {
                auto sn_trimmed = getLastFourDigits(arbiter.protocols[i]._SN);
                ptr += (uint8_t)snprintf(buffer + ptr, sizeof(buffer) - ptr, "%d, ", sn_trimmed);
            }
        }
        pdo_protocol.SendPayload(buffer, strnlen(buffer, sizeof(buffer)));
    }
    else if(arg_len == 1)
    {
        auto input_sn = getLastFourDigits((uint32_t)argv[0]);
        for(uint8_t i = 0; i < PROTOCOL_COUNT; i++)
        {
            if(arbiter.protocols[i].IsAlive() && arbiter.instances[i])
            {
                if(input_sn == getLastFourDigits(arbiter.protocols[i]._SN))
                {
                    pdo_protocol.print("Slave SN: %d alive @ UART%d", input_sn, match(arbiter.instances[i]));
                    return;
                }
            }
        }
        pdo_protocol.print("Slave SN: %d not available now", input_sn);
    }
    else
    {
        auto input_sn = getLastFourDigits((uint32_t)argv[0]);
        for(uint8_t i = 0; i < PROTOCOL_COUNT; i++)
        {
            if(arbiter.protocols[i].IsAlive() && arbiter.instances[i])
            {
                if(input_sn == getLastFourDigits(arbiter.protocols[i]._SN))
                {
                    pdo_protocol.print("Sending %d args to slave %d @ UART%d", arg_len - 1, input_sn, match(arbiter.instances[i]));
                    char buffer[42] = {0};
                    uint8_t ptr = 0;
                    for(uint16_t j = 1; j < arg_len; j++) ptr += (uint8_t)snprintf(buffer + ptr, sizeof(buffer) - ptr, "%.2f ", argv[j]);
                    arbiter.protocols[i].PreparePayloadToSetBuf(buffer, strlen(buffer));
                    return;
                }
            }
        }
        pdo_protocol.print("Slave SN: %d not available now", input_sn);
    }
}

// void reboot_cmd(char *name, float *argv, uint16_t arg_len)
// {
//     static uint8_t state = 0;
//     if(arg_len == 0)
//     {
//         if(state == 0)
//         {
//             pdo_protocol.print("Reboot interface? type again.");
//             state = 1;
//         }
//         else if(state == 1) NVIC_SystemReset();
//     }
//     else
//     {
//         if(arg_len == 1)
//         {
//             if(argv[0] == -1.0f) NVIC_SystemReset(); // force reboot interface
//         }
//     }
// }