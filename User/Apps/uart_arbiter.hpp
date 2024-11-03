#ifndef _UART_ARBITER_HPP
#define _UART_ARBITER_HPP

#include "uart_protocol.hpp"

#define PROTOCOL_COUNT 8

class UARTArbiter
{
public:
    UARTArbiter() {};
    UARTProtocol protocols[PROTOCOL_COUNT];
    UART *instances[PROTOCOL_COUNT];
    void OnRxEvent(UART* uart, uint8_t *buffer, uint16_t len);
};

void UARTArbiter::OnRxEvent(UART* uart, uint8_t *buffer, uint16_t len)
{
    uint16_t max_packet_count = (len / sizeof(UARTProtocol::rx_buffer));
    while(max_packet_count--)
    {
        while(len)
        {
            if(*buffer == (uint8_t)uart_buffer_t<RX_STRUCT_NAME>::Type::MOTOR || 
            *buffer == (uint8_t)uart_buffer_t<RX_STRUCT_NAME>::Type::PAYLOAD) break;
            buffer++;
            len--;
        }
        if(len == 0) return;
        auto *ptr = (decltype(UARTProtocol::rx_buffer)*)buffer;
        if((*ptr).isValid())
        {
            auto target_SN = (*ptr).getPayload()->SN;
            uint16_t slot = target_SN % PROTOCOL_COUNT;
            auto slot_SN = protocols[slot].rx_buffer.getPayload()->SN;
            if(slot_SN != 0 && (slot_SN != target_SN && protocols[slot].IsRemoteAlive())) // slot conflict
            {
                for(uint16_t t = 0; t <= PROTOCOL_COUNT; t++)
                {
                    if(t == slot) continue;
                    slot = t;
                    slot_SN = protocols[slot].rx_buffer.getPayload()->SN;
                    if( slot_SN == 0 ||                   // empty slot
                        slot_SN == target_SN ||           // matched slot
                        !protocols[slot].IsRemoteAlive()  // dead device
                    )
                    break;
                }
                if(slot >= PROTOCOL_COUNT) continue; // no valid slot
            }
            instances[slot] = uart;
            protocols[slot].target_sn = target_SN;
            protocols[slot].OnRxBuffer((char*)buffer, len);
            len -= sizeof(UARTProtocol::rx_buffer);
        }
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