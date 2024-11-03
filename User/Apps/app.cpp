#include "classes.hpp"

// class WS2812Task : public RTOSTask
// {
// public:
//     uint8_t state = 0; // 0 - off, 1 - steady RGB, 2 - color wheel
//     uint8_t r = 0;
//     uint8_t g = 0;
//     uint8_t b = 0;
// private:
//     uint8_t sleep_ms = 10;
//     uint8_t j = 0;
//     void setup() final
//     {
//         ws2812.Init(0.1f);
//     }
//     void loop() final
//     {
//         switch(state)
//         {
//             case 0:
//             {
//                 r = 0;
//                 g = 0;
//                 b = 0;
//                 break;
//             }
//             case 2:
//             {
//                 j++;
//                 GetColorWheel(j, &r, &g, &b);
//                 break;
//             }
//             default: break;
//         }
//         ws2812.SetColor(0, r, g, b);
//         ws2812.Update();
//         sleep(sleep_ms);
//     }
// };
// WS2812Task ws2812task;

// class ECATTask : public RTOSTask
// {
// public:
//     void loop() final
//     {
//         taskENTER_CRITICAL();
//         ethercat.Update();
//         taskEXIT_CRITICAL();
//         HAL_IWDG_Refresh(&hiwdg1);
//         sleep(2);
//     }
// };
// ECATTask ecatTask;

void rx_pdo_payload_cb(char *payload, uint8_t len)
{
    printf("Received PDO Payload: ");
    size_t str_len = strnlen(payload, len);
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
        usb_shell.Init();
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

void uart_1_rx_cb(uint16_t Size)
{
    arbiter.OnRxEvent(&UART_1, UART_1.rx_buffer, Size);
}
void uart_2_rx_cb(uint16_t Size)
{
    arbiter.OnRxEvent(&UART_2, UART_2.rx_buffer, Size);
}
void uart_3_rx_cb(uint16_t Size)
{
    arbiter.OnRxEvent(&UART_3, UART_3.rx_buffer, Size);
}
void uart_4_rx_cb(uint16_t Size)
{
    arbiter.OnRxEvent(&UART_4, UART_4.rx_buffer, Size);
}
void uart_6_rx_cb(uint16_t Size)
{
    arbiter.OnRxEvent(&UART_6, UART_6.rx_buffer, Size);
}
void uart_7_rx_cb(uint16_t Size)
{
    arbiter.OnRxEvent(&UART_7, UART_7.rx_buffer, Size);
}
void uart_8_rx_cb(uint16_t Size)
{
    arbiter.OnRxEvent(&UART_8, UART_8.rx_buffer, Size);
}

void master_set_cb()
{
    if(ethercat.isSafeToRun)
    {
        // memcpy(&arbiter.protocols[0].set, &Obj.Motor1_Set, sizeof(motor_set_t));
        // memcpy(&arbiter.protocols[1].set, &Obj.Motor2_Set, sizeof(motor_set_t));
        // memcpy(&arbiter.protocols[2].set, &Obj.Motor3_Set, sizeof(motor_set_t));
        // memcpy(&arbiter.protocols[3].set, &Obj.Motor4_Set, sizeof(motor_set_t));
        // memcpy(&arbiter.protocols[4].set, &Obj.Motor5_Set, sizeof(motor_set_t));
        // memcpy(&arbiter.protocols[5].set, &Obj.Motor6_Set, sizeof(motor_set_t));
        // memcpy(&arbiter.protocols[6].set, &Obj.Motor7_Set, sizeof(motor_set_t));
        // memcpy(&arbiter.protocols[7].set, &Obj.Motor8_Set, sizeof(motor_set_t));
        // for(uint8_t i = 0; i < 8; i++) arbiter.instances[i]->tx_len = 0;
        // for(uint8_t i = 0; i < 8; i++)
        // {
        //     if(arbiter.protocols[i].IsAlive()) 
        //     {
        //         arbiter.protocols[i].PrepareTxSetBuf();
        //         // arbiter.instances[i]->PutTxFifo((char*)arbiter.protocols[i].set_buffer, sizeof(UARTProtocol::set_buffer));
        //         // if(arbiter.instances[i]->GetTxFifoLen() == 2 * sizeof(UARTProtocol::set_buffer)) arbiter.instances[i]->Transmit();
        //         memcpy(arbiter.instances[i]->tx_buffer + arbiter.instances[i]->tx_len, arbiter.protocols[i].set_buffer, sizeof(UARTProtocol::set_buffer));
        //         arbiter.instances[i]->tx_len += sizeof(UARTProtocol::set_buffer);
        //         if(arbiter.instances[i]->tx_len == 2 * sizeof(UARTProtocol::set_buffer)) arbiter.instances[i]->Transmit();
        //     }
        // }
    }
}

void master_get_cb()
{
    Obj.Interface_State.Uptime = (uint32_t)ethercat.uptime_sec;
    Obj.Interface_State.MotorCount = 0;
    Obj.Interface_State.FramesPerSec = ethercat.fps;
    Obj.Interface_State.Vbus = (uint16_t)(getVoltage(_adc_1_value) * 11.0f);
    Obj.Interface_State.MCUTemp = (uint8_t)getMCUTemperature();
    // if(arbiter.protocols[0].state.SN != 0)
    // {
    //     memcpy(&Obj.Motor1_State, &arbiter.protocols[0].state, sizeof(motor_state_t));
    //     Obj.Interface_State.MotorCount += (Obj.Motor1_State.IsAlive = arbiter.protocols[0].IsAlive());
    // }
    // if(arbiter.protocols[1].state.SN != 0)
    // {
    //     memcpy(&Obj.Motor2_State, &arbiter.protocols[1].state, sizeof(motor_state_t));
    //     Obj.Interface_State.MotorCount += (Obj.Motor2_State.IsAlive = arbiter.protocols[1].IsAlive());
    // }
    // if(arbiter.protocols[2].state.SN != 0)
    // {
    //     memcpy(&Obj.Motor3_State, &arbiter.protocols[2].state, sizeof(motor_state_t));
    //     Obj.Interface_State.MotorCount += (Obj.Motor3_State.IsAlive = arbiter.protocols[2].IsAlive());
    // }
    // if(arbiter.protocols[3].state.SN != 0)
    // {
    //     memcpy(&Obj.Motor4_State, &arbiter.protocols[3].state, sizeof(motor_state_t));
    //     Obj.Interface_State.MotorCount += (Obj.Motor4_State.IsAlive = arbiter.protocols[3].IsAlive());
    // }
    // if(arbiter.protocols[4].state.SN != 0)
    // {
    //     memcpy(&Obj.Motor5_State, &arbiter.protocols[4].state, sizeof(motor_state_t));
    //     Obj.Interface_State.MotorCount += (Obj.Motor5_State.IsAlive = arbiter.protocols[4].IsAlive());
    // }
    // if(arbiter.protocols[5].state.SN != 0)
    // {
    //     memcpy(&Obj.Motor6_State, &arbiter.protocols[5].state, sizeof(motor_state_t));
    //     Obj.Interface_State.MotorCount += (Obj.Motor6_State.IsAlive = arbiter.protocols[5].IsAlive());
    // }
    // if(arbiter.protocols[6].state.SN != 0)
    // {
    //     memcpy(&Obj.Motor7_State, &arbiter.protocols[6].state, sizeof(motor_state_t));
    //     Obj.Interface_State.MotorCount += (Obj.Motor7_State.IsAlive = arbiter.protocols[6].IsAlive());
    // }
    // if(arbiter.protocols[7].state.SN != 0)
    // {
    //     memcpy(&Obj.Motor8_State, &arbiter.protocols[7].state, sizeof(motor_state_t));
    //     Obj.Interface_State.MotorCount += (Obj.Motor8_State.IsAlive = arbiter.protocols[7].IsAlive());
    // }
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
    pdo_protocol.RegisterRxPayloadCallback(rx_pdo_payload_cb);
    ethercat.Init();
    HAL_IWDG_Refresh(&hiwdg1);

    LL_TIM_EnableIT_UPDATE(TIM17); // 2ms UPDATE
    LL_TIM_EnableCounter(TIM17);

    arbiter.protocols[0].target_rx_ptr = (motor_state_t*)&Obj.Motor1_State;
    arbiter.protocols[1].target_rx_ptr = (motor_state_t*)&Obj.Motor2_State;
    arbiter.protocols[2].target_rx_ptr = (motor_state_t*)&Obj.Motor3_State;
    arbiter.protocols[3].target_rx_ptr = (motor_state_t*)&Obj.Motor4_State;
    arbiter.protocols[4].target_rx_ptr = (motor_state_t*)&Obj.Motor5_State;
    arbiter.protocols[5].target_rx_ptr = (motor_state_t*)&Obj.Motor6_State;
    arbiter.protocols[6].target_rx_ptr = (motor_state_t*)&Obj.Motor7_State;
    arbiter.protocols[7].target_rx_ptr = (motor_state_t*)&Obj.Motor8_State;

    UART_1.RegisterCallback(uart_1_rx_cb);
    UART_2.RegisterCallback(uart_2_rx_cb);
    UART_3.RegisterCallback(uart_3_rx_cb);
    UART_4.RegisterCallback(uart_4_rx_cb);
    UART_6.RegisterCallback(uart_6_rx_cb);
    UART_7.RegisterCallback(uart_7_rx_cb);
    UART_8.RegisterCallback(uart_8_rx_cb);
    UART_1.Init();
    UART_2.Init();
    UART_3.Init(); 
    UART_4.Init(); 
    UART_6.Init(); 
    UART_7.Init();
    UART_8.Init();  

    // ws2812task.start((char*)"WS2812Task", 128, osPriorityBelowNormal);
    // ecatTask.start((char*)"ECATTask", 256, osPriorityAboveNormal);
    usbTask.start((char*)"USBTask", 512, osPriorityNormal);

    osKernelStart();
    while(1);
}
