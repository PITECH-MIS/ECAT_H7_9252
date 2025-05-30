#include "classes.hpp"
#include "commands.hpp"

void rx_pdo_payload_cb(char *payload, uint8_t len)
{
    printf("Received PDO Payload: ");
    size_t str_len = strnlen(payload, len);
    // pdo_protocol.SendPayload(payload, str_len);
    parser.ParseRaw(payload, len);
    while(str_len--)
    {
        printf("%c", *payload++);
    }
}

void usb_update_cb(char* buffer, uint16_t len)
{
    pdo_protocol.SendPayload(buffer, len);
}

class USBTask : public RTOSTask
{
public:
    void setup() final
    {
        usb_shell.RegisterTxCallback(CDC_Transmit_HS);
        usb_shell.RegisterUpdateCallback(usb_update_cb);
    }
    void loop() final
    {
        usb_shell.Update();
        usb_shell.Transmit();
        sleep(2);
    }
};
USBTask usbTask;

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if(UART_1.OnIdleIRQ(huart, Size)) return;
    if(UART_2.OnIdleIRQ(huart, Size)) return;
    if(UART_3.OnIdleIRQ(huart, Size)) return;
    if(UART_4.OnIdleIRQ(huart, Size)) return;
    if(UART_6.OnIdleIRQ(huart, Size)) return;
    if(UART_7.OnIdleIRQ(huart, Size)) return;
    if(UART_8.OnIdleIRQ(huart, Size)) return;
}

void uart_1_rx_cb(uint16_t Size) { arbiter.OnRxEvent(&UART_1, UART_1.rx_buffer, Size); }
void uart_2_rx_cb(uint16_t Size) { arbiter.OnRxEvent(&UART_2, UART_2.rx_buffer, Size); }
void uart_3_rx_cb(uint16_t Size) { arbiter.OnRxEvent(&UART_3, UART_3.rx_buffer, Size); }
void uart_4_rx_cb(uint16_t Size) { arbiter.OnRxEvent(&UART_4, UART_4.rx_buffer, Size); }
void uart_6_rx_cb(uint16_t Size) { arbiter.OnRxEvent(&UART_6, UART_6.rx_buffer, Size); }
void uart_7_rx_cb(uint16_t Size) { arbiter.OnRxEvent(&UART_7, UART_7.rx_buffer, Size); }
void uart_8_rx_cb(uint16_t Size) { arbiter.OnRxEvent(&UART_8, UART_8.rx_buffer, Size); }
void mx_pdo_payload_cb(uint8_t x, uint8_t *payload, uint8_t len)
{
    if(arbiter.protocols[x].IsAlive())
    {
        auto sn_trimmed = getLastFourDigits(arbiter.protocols[x]._SN);
        pdo_protocol.print("Slave %d: ", sn_trimmed);
        pdo_protocol.SendPayload((char*)payload, len);
    }
}
inline void m1_pdo_payload_cb(uint8_t *payload, uint8_t len) { mx_pdo_payload_cb(0, payload, len); }
inline void m2_pdo_payload_cb(uint8_t *payload, uint8_t len) { mx_pdo_payload_cb(1, payload, len); }
inline void m3_pdo_payload_cb(uint8_t *payload, uint8_t len) { mx_pdo_payload_cb(2, payload, len); }
inline void m4_pdo_payload_cb(uint8_t *payload, uint8_t len) { mx_pdo_payload_cb(3, payload, len); }
inline void m5_pdo_payload_cb(uint8_t *payload, uint8_t len) { mx_pdo_payload_cb(4, payload, len); }
inline void m6_pdo_payload_cb(uint8_t *payload, uint8_t len) { mx_pdo_payload_cb(5, payload, len); }
inline void m7_pdo_payload_cb(uint8_t *payload, uint8_t len) { mx_pdo_payload_cb(6, payload, len); }
inline void m8_pdo_payload_cb(uint8_t *payload, uint8_t len) { mx_pdo_payload_cb(7, payload, len); }

void master_set_cb()
{
    if(ethercat.isSafeToRun)
    {
        auto *ptr = (motor_set_t*)&Obj.Motor1_Set;
        for(uint8_t i = 0; i < PROTOCOL_COUNT; i++)
        {
            auto &protocol = arbiter.protocols[i];
            if(protocol.IsAlive())
            {
                protocol.PrepareSetBuf(ptr);
                if(protocol.requestedTx)
                {
                    if(arbiter.instances[i]) arbiter.instances[i]->PutTxFifo((char*)&protocol.set_buffer, sizeof(protocol.set_buffer));
                }
            }
            else if(protocol._SN != 0)
            {
                // Try to send payload using CAN interface
            }
            ptr++;
        }
        for(uint8_t i = 0; i < PROTOCOL_COUNT; i++)
        {
            if(arbiter.instances[i])
            {
                if (__HAL_UART_GET_FLAG(arbiter.instances[i]->huart, UART_FLAG_TC))
                {
                    auto len = arbiter.instances[i]->GetTxFifoLen();
                    if(len > 0)
                    {
                        if (len % sizeof(UARTProtocol::set_buffer) == 0) arbiter.instances[i]->Transmit();
                        else arbiter.instances[i]->FlushTxFifo();
                    }
                }
                arbiter.protocols[i].requestedTx = false;
            }
        }
    }
}

void master_get_cb()
{
    Obj.Interface_State.Uptime = (uint32_t)ethercat.uptime_sec;
    Obj.Interface_State.MotorCount = 0;
    Obj.Interface_State.FramesPerSec = ethercat.fps;
    Obj.Interface_State.Vbus = (uint16_t)(getVoltage(_adc_1_value) * 11.0f);
    Obj.Interface_State.MCUTemp = (uint8_t)getMCUTemperature();
    auto *ptr = (motor_state_t*)&Obj.Motor1_State;
    for(const auto &protocol : arbiter.protocols)
    {
        if(protocol.state_buffer.header == MOTOR_STATE_HEADER)
        {
            const auto state_ptr = protocol.state_buffer.state();
            if(state_ptr->SN != 0)
            {
                memcpy(ptr, state_ptr, sizeof(motor_state_t));
            }
        }
        ptr->IsAlive = protocol.IsAlive();
        Obj.Interface_State.MotorCount += (ptr->IsAlive > 0);
        ptr++;
    }
}

void user_enterop()
{
    // printf("Enter OP Mode\n");
    ws2812.SetColor(0, 0, 255, 0);
    ws2812.Update();
}

void user_failsafe()
{
    // printf("Failsafe\n");
    pdo_protocol.Reset();
    ws2812.SetColor(0, 255, 0, 0);
    ws2812.Update();
}

void ecat_app_cb()
{
    pdo_protocol.onPDOLoop();
}

void app_main()
{
    __HAL_DBGMCU_FREEZE_IWDG1();
    ws2812.Init(0.05f);
    usb_shell.Init();
    pdo_protocol.RegisterRxPayloadCallback(rx_pdo_payload_cb);
    ethercat.Init();
    HAL_IWDG_Refresh(&hiwdg1);

    LL_TIM_EnableIT_UPDATE(TIM17); // 2ms UPDATE
    LL_TIM_EnableCounter(TIM17);

    UART_1.RegisterCallback(uart_1_rx_cb);
    UART_2.RegisterCallback(uart_2_rx_cb);
    UART_3.RegisterCallback(uart_3_rx_cb);
    UART_4.RegisterCallback(uart_4_rx_cb);
    UART_6.RegisterCallback(uart_6_rx_cb);
    UART_7.RegisterCallback(uart_7_rx_cb);
    UART_8.RegisterCallback(uart_8_rx_cb);
    arbiter.protocols[0]._payload_cb = m1_pdo_payload_cb;
    arbiter.protocols[1]._payload_cb = m2_pdo_payload_cb;
    arbiter.protocols[2]._payload_cb = m3_pdo_payload_cb;
    arbiter.protocols[3]._payload_cb = m4_pdo_payload_cb;
    arbiter.protocols[4]._payload_cb = m5_pdo_payload_cb;
    arbiter.protocols[5]._payload_cb = m6_pdo_payload_cb;
    arbiter.protocols[6]._payload_cb = m7_pdo_payload_cb;
    arbiter.protocols[7]._payload_cb = m8_pdo_payload_cb;
    UART_1.Init();
    UART_2.Init();
    UART_3.Init(); 
    UART_4.Init(); 
    UART_6.Init(); 
    UART_7.Init();
    UART_8.Init();  

    can_arbiter.Init(true);

    parser.Register((char*)"check_uart", check_uart_cmd, nullptr);
    parser.Register((char*)"slave", slave_cmd, nullptr);
    // parser.Register((char*)"reboot", reboot_cmd, nullptr);

    // ws2812task.start((char*)"WS2812Task", 128, osPriorityBelowNormal);
    // ecatTask.start((char*)"ECATTask", 256, osPriorityAboveNormal);
    usbTask.start((char*)"USBTask", 512, osPriorityNormal);

    osKernelStart();
    while(1);
}
