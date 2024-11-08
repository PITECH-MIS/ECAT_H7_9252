#ifndef ECAT_H7_9252_CAN_ARBITER_HPP
#define ECAT_H7_9252_CAN_ARBITER_HPP

#include "canfd_interface.hpp"
#include "can_opcodes_enum.h"

template<typename Intf>
class CANArbiter
{
public:
    explicit CANArbiter(Intf& _intf) : interface(_intf)
    {
        static_assert(std::is_base_of<CANBase, Intf>::value, "CAN Implementation must be derived from CANBase");
    };
    void Init(bool initHW = false);
    void Tick(float Ts);
    void OnDataFrame(uint32_t id, uint8_t *payload, uint8_t len);
    void OnRemoteFrame(uint32_t id);
private:
    Intf& interface;
    uint8_t tx_buffer[8] = {0x00};
};

template<typename Intf>
void CANArbiter<Intf>::Init(bool initHW)
{
    interface.ConfigFilter(0x00, 0x00, 0, 0); // receive all CAN packets
    if(initHW) interface.InitHW();
}

template<typename Intf>
void CANArbiter<Intf>::Tick(float Ts)
{

}

template<typename Intf>
void CANArbiter<Intf>::OnDataFrame(uint32_t id, uint8_t *payload, uint8_t len)
{
    uint8_t node_id = GetCANNodeID(id);
    auto opcode = static_cast<CAN_OPCODES>(GetCANCmdID(id));
    printf("Node 0x%x sent data frame ID: %d with %d payload\n", node_id, (uint16_t)opcode, len);
    // switch(opcode)
    // {
    //     default: break;
    // }
}

template<typename Intf>
void CANArbiter<Intf>::OnRemoteFrame(uint32_t id)
{
    uint8_t node_id = GetCANNodeID(id);
    auto opcode = static_cast<CAN_OPCODES>(GetCANCmdID(id));
    printf("Node 0x%x sent remote frame ID: %d\n", node_id, (uint16_t)opcode);
}

#endif //ECAT_H7_9252_CAN_ARBITER_HPP
