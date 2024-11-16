#ifndef ECAT_H7_9252_CAN_ARBITER_HPP
#define ECAT_H7_9252_CAN_ARBITER_HPP

#include "canfd_interface.hpp"
#include "can_opcodes_enum.h"
#include <map>

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
    void Identify();
    void SetEnable(uint8_t node_id, uint8_t enable);
    void SetMode(uint8_t node_id, uint8_t mode);
    void OnDataFrame(uint32_t id, uint8_t *payload, uint8_t len);
    void OnRemoteFrame(uint32_t id);
    std::map<uint32_t, uint8_t> snToNodeIDMap;
    // std::set<std::pair<uint32_t, uint8_t>> snToNodeIDSet;
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
void CANArbiter<Intf>::Identify()
{
    interface.SendRemoteFrame(GetCANFrameID(0x3F, ADDRESS));
}

template<typename Intf>
void CANArbiter<Intf>::OnDataFrame(uint32_t id, uint8_t *payload, uint8_t len)
{
    uint8_t node_id = GetCANNodeID(id);
    auto opcode = static_cast<CAN_OPCODES>(GetCANCmdID(id));
    // printf("Node 0x%x sent data frame ID: %d with %d payload\n", node_id, (uint16_t)opcode, len);
    switch(opcode)
    {
        case ADDRESS:
        {
            if(len == 7)
            {
                uint8_t packet_node_id = payload[0];
                uint64_t _sn = 0;
                memcpy(&_sn, &payload[1], 6);
                auto sn = (uint32_t)_sn;
                if(packet_node_id == 0x3F)
                {
                    printf("Found unaddressed node, SN:%lu\n", sn);
                }
                else
                {
                    for(const auto &i : snToNodeIDMap)
                    {
                        printf("Curr map: 0x%x, %lu\n", i.second, i.first);
                    }
                    auto it = snToNodeIDMap.find(sn);
                    if(it != snToNodeIDMap.end())
                    {
                        printf("Found registered node, id: 0x%x, sn: %lu\n", it->second, it->first);
                    }
                    else
                    {
                        snToNodeIDMap.emplace(std::pair<uint32_t, uint8_t>(sn, packet_node_id));
                        printf("New register node, id: 0x%x, sn: %lu\n", packet_node_id, sn);
                    }
                }

            }
            break;
        }
        default: break;
    }
}

template<typename Intf>
void CANArbiter<Intf>::OnRemoteFrame(uint32_t id)
{
    uint8_t node_id = GetCANNodeID(id);
    auto opcode = static_cast<CAN_OPCODES>(GetCANCmdID(id));
    printf("Node 0x%x sent remote frame ID: %d\n", node_id, (uint16_t)opcode);
}

#endif //ECAT_H7_9252_CAN_ARBITER_HPP
