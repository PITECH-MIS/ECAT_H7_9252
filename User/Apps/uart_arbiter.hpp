#ifndef _UART_ARBITER_HPP
#define _UART_ARBITER_HPP

#include "uart_protocol.hpp"

#define PROTOCOL_COUNT 8

class UARTArbiter
{
public:
    UARTArbiter() = default;
    UARTProtocol protocols[PROTOCOL_COUNT];
    UART *instances[PROTOCOL_COUNT];
    void OnRxEvent(UART* uart, uint8_t *buffer, uint16_t len);
};

void UARTArbiter::OnRxEvent(UART* uart, uint8_t *buffer, uint16_t len)
{
    if(len < sizeof(UARTProtocol::state_buffer)) return;
    uint16_t start_ptr = 0;
    while(start_ptr < len)
    {
        auto p = buffer + start_ptr;
        // Start by directly check header & slot.
        if(*p == MOTOR_STATE_HEADER ||
           *p == PAYLOAD_HEADER)
        {
            if(len - start_ptr >= sizeof(UARTProtocol::state_buffer))
            {
                auto x = (decltype(UARTProtocol::state_buffer)*)p;
                uint32_t SN = 0;
                if(*p == MOTOR_STATE_HEADER) SN = x->state()->SN;
                else memcpy(&SN, x->payload, sizeof(SN));
                uint16_t slot = SN % PROTOCOL_COUNT;
                uint32_t slot_SN = protocols[slot].state_buffer.state()->SN;
                if(slot_SN != 0 && (slot_SN != SN && protocols[slot].IsAlive())) // slot conflict
                {
                    for(uint16_t t = 0; t <= PROTOCOL_COUNT; t++)
                    {
                        if(t == slot) continue;
                        slot = t;
                        slot_SN = protocols[slot].state_buffer.state()->SN;
                        if(slot_SN == 0 || slot_SN == SN || !protocols[slot].IsAlive()) break;
                    }
                    if(slot >= PROTOCOL_COUNT) continue;
                }
                if(protocols[slot].ReceiveStateBuf((char*)p, sizeof(UARTProtocol::state_buffer)))
                {
                    instances[slot] = uart;
                }
                start_ptr += sizeof(UARTProtocol::state_buffer);
            }
            else break;
        }
        else start_ptr++;
    }

    // if(len % sizeof(UARTProtocol::state_buffer) == 0)
    // {
    //     for(uint16_t i = 0; i < (len / sizeof(UARTProtocol::state_buffer)); i++)
    //     {
    //         UARTProtocol temp;
    //         temp.ReceiveRxStateBuf(buffer + i * sizeof(UARTProtocol::state_buffer), sizeof(UARTProtocol::state_buffer));
    //         uint16_t slot = temp.state.SN % PROTOCOL_COUNT;
    //         if(protocols[slot].state.SN != 0 && (protocols[slot].state.SN != temp.state.SN && protocols[slot].keep_alive)) // slot conflict
    //         {
    //             for(uint16_t t = 0; t <= PROTOCOL_COUNT; t++)
    //             {
    //                 if(t == slot) continue;
    //                 slot = t;
    //                 if(protocols[slot].state.SN == 0 ||              // empty slot
    //                    protocols[slot].state.SN == temp.state.SN ||  // matched slot
    //                    !protocols[slot].keep_alive                   // dead device
    //                 )
    //                 break;
    //             }
    //             // if(slot >= PROTOCOL_COUNT) continue;
    //             if(slot >= PROTOCOL_COUNT) break;
    //         }
    //         instances[slot] = uart;
    //         memcpy(&protocols[slot].state, &temp.state, sizeof(UARTProtocol::state));
    //         protocols[slot].last_rec_tick = temp.last_rec_tick;
    //         protocols[slot].keep_alive = true;
    //     }
    // }
}

#endif