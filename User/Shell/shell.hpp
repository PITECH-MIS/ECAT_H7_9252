#include "global_include.h"

#include "parser.h"
#include "kfifo.h"

typedef uint8_t (*tx_cb)(uint8_t *buffer, uint16_t len);

typedef void (*update_cb)(char *buffer, uint16_t len);

class Shell
{
public:
    void Init();
    void OnRxMsg(uint8_t *buffer, uint32_t len);
    void RegisterTxCallback(tx_cb cb) { _tx_callback = cb; };
    void RegisterUpdateCallback(update_cb cb) { _update_callback = cb; };
    void PutTxFifo(uint8_t *buffer, uint32_t len);
    bool Transmit();
    void Update();
private:
    volatile uint8_t incoming_messages = 0;
    kfifo_t* rx_fifo = nullptr;
    kfifo_t* tx_fifo = nullptr;
    char tx_buffer[128];
    tx_cb _tx_callback = nullptr;
    update_cb _update_callback = nullptr;
};

void Shell::Init()
{
    rx_fifo = kfifo_init(128);
    tx_fifo = kfifo_init(128);
}

void Shell::OnRxMsg(uint8_t *buffer, uint32_t len)
{
    if(!rx_fifo) return;
    kfifo_put(rx_fifo, (char*)buffer, len);
    incoming_messages++;
}

void Shell::PutTxFifo(uint8_t *buffer, uint32_t len)
{
    if(!tx_fifo) return;
    kfifo_put(tx_fifo, (char*)buffer, len);
}

bool Shell::Transmit()
{
    if(!_tx_callback || !tx_fifo) return false;
    uint32_t len = kfifo_used(tx_fifo);
    if(len == 0) return false;
    kfifo_get(tx_fifo, tx_buffer, len);
    _tx_callback((uint8_t*)tx_buffer, len);
    return true;
}

void Shell::Update()
{
    if(incoming_messages)
    {
        uint32_t len = kfifo_used(rx_fifo);
        char rx_buffer[128];
        kfifo_get(rx_fifo, rx_buffer, len);
        if(_update_callback) _update_callback(rx_buffer, len);
        incoming_messages--;
    }
}