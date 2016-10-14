/*******************************************************************************
* File Name: RedLED.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "RedLED.h"

static RedLED_BACKUP_STRUCT  RedLED_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: RedLED_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function must be called for SIO and USBIO
*  pins. It is not essential if using GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet RedLED_SUT.c usage_RedLED_Sleep_Wakeup
*******************************************************************************/
void RedLED_Sleep(void)
{
    #if defined(RedLED__PC)
        RedLED_backup.pcState = RedLED_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            RedLED_backup.usbState = RedLED_CR1_REG;
            RedLED_USB_POWER_REG |= RedLED_USBIO_ENTER_SLEEP;
            RedLED_CR1_REG &= RedLED_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(RedLED__SIO)
        RedLED_backup.sioState = RedLED_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        RedLED_SIO_REG &= (uint32)(~RedLED_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: RedLED_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep().
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to RedLED_Sleep() for an example usage.
*******************************************************************************/
void RedLED_Wakeup(void)
{
    #if defined(RedLED__PC)
        RedLED_PC = RedLED_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            RedLED_USB_POWER_REG &= RedLED_USBIO_EXIT_SLEEP_PH1;
            RedLED_CR1_REG = RedLED_backup.usbState;
            RedLED_USB_POWER_REG &= RedLED_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(RedLED__SIO)
        RedLED_SIO_REG = RedLED_backup.sioState;
    #endif
}


/* [] END OF FILE */
