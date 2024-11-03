#include "bsp_isr.h"
#include "esc.h"

volatile uint8_t ecat_isr_sem = 0;

#define ESC_IRQ_CFG_REG          0x054
#define ESC_INT_EN_REG           0x05C

void ESC_interrupt_enable(uint32_t mask)
{
    // HAL_NVIC_EnableIRQ(ESC_PDI_IRQn); // always enable PDI interrupt
    // if(mask & ESCREG_ALEVENT_DC_SYNC0)
    // {
    //     HAL_NVIC_EnableIRQ(ESC_SYNC0_IRQn);
    //     mask &= ~ESCREG_ALEVENT_DC_SYNC0;
    // }
    // // SYNC1...
    // ESC_ALeventmaskwrite(ESC_ALeventmaskread() | mask);
    // printf("Enable IRQ Mask: 0x%x\n", mask);
    HAL_NVIC_EnableIRQ(ESC_PDI_IRQn); // always enable PDI interrupt
    uint32_t user_int_mask = ESCREG_ALEVENT_DC_SYNC0 |
                             ESCREG_ALEVENT_SM2 |
                             ESCREG_ALEVENT_SM3;
    if(mask & user_int_mask) ESC_ALeventmaskwrite(ESC_ALeventmaskread() | (mask & user_int_mask));
    if(mask & ESCREG_ALEVENT_DC_SYNC0) HAL_NVIC_EnableIRQ(ESC_SYNC0_IRQn);
    lan9252_write_32(ESC_IRQ_CFG_REG, 0x00000111); // Set LAN9252 interrupt pin driver as push-pull active high
    lan9252_write_32(ESC_INT_EN_REG, 0x00000001);  // Enable LAN9252 interrupt
}

void ESC_interrupt_disable(uint32_t mask)
{
    // printf("Disable IRQ Mask: 0x%x\n", mask);
    HAL_NVIC_DisableIRQ(ESC_PDI_IRQn);
    uint32_t user_int_mask = ESCREG_ALEVENT_DC_SYNC0 |
                             ESCREG_ALEVENT_SM2 |
                             ESCREG_ALEVENT_SM3;
    if(mask & user_int_mask) ESC_ALeventmaskwrite(ESC_ALeventmaskread() & ~(mask & user_int_mask));
    if(mask & ESCREG_ALEVENT_DC_SYNC0) HAL_NVIC_DisableIRQ(ESC_SYNC0_IRQn);
    lan9252_write_32(ESC_INT_EN_REG, 0x00000000);  // Disable LAN9252 interrupt
}

void pdi_isr()
{
    // CC_ATOMIC_SET(ESCvar.ALevent, ESC_ALeventread());
    ESC_read(ESCREG_LOCALTIME, (void *) &ESCvar.Time, sizeof (ESCvar.Time));
    if(ESCvar.ALevent & ESCREG_ALEVENT_SM2)
    {
        if(ESCvar.dcsync == 0)
        {
            // printf("PDI_ISR: DCSYNC = 0\n");
            DIG_process(DIG_PROCESS_OUTPUTS_FLAG | DIG_PROCESS_APP_HOOK_FLAG | DIG_PROCESS_INPUTS_FLAG);
        }
        else
        {
            // printf("PDI_ISR: DCSYNC = 1\n");
            DIG_process(DIG_PROCESS_OUTPUTS_FLAG);
        }
    }
    // if(ESCvar.ALevent & (ESCREG_ALEVENT_CONTROL | ESCREG_ALEVENT_SMCHANGE | ESCREG_ALEVENT_SM0 | ESCREG_ALEVENT_SM1 | ESCREG_ALEVENT_EEP))
    // {
    //     printf("Get ECAT_ISR_SEM\n");
    //     uint32_t mask = ESCvar.ALevent;
    //     mask &= ~(ESCREG_ALEVENT_CONTROL | ESCREG_ALEVENT_SMCHANGE
    //         | ESCREG_ALEVENT_SM0 | ESCREG_ALEVENT_SM1 | ESCREG_ALEVENT_EEP);
    //     ESC_ALeventmaskwrite(mask);
    //     ecat_isr_sem++;
    // }
}

void pdi_isr_background()
{
    // if(ecat_isr_sem)
    // {
    //     printf("Served ECAT_ISR_SEM\n");
    //     ecat_slv_worker(ESCREG_ALEVENT_CONTROL | ESCREG_ALEVENT_SMCHANGE | ESCREG_ALEVENT_SM0 | ESCREG_ALEVENT_SM1 | ESCREG_ALEVENT_EEP);
    //     ecat_isr_sem--;
    // }
}

void sync0_isr()
{
    DIG_process(DIG_PROCESS_APP_HOOK_FLAG | DIG_PROCESS_INPUTS_FLAG);
}