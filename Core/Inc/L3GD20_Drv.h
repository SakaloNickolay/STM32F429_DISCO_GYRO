/* File L3GD20.h*/

#ifndef L3GD20_DRV_H
#define L3GD20_DRV_H

#include <stdint.h>

#define RW_CMD                  ((uint8_t)0x80)
#define MULTIPLEBYTE_CMD        ((uint8_t)0x40)
#define DUMMY                   ((uint8_t)0x00)
#define GYRO_SPI                SPI5

/* Initial Gyro structure*/

typedef struct
{
  uint8_t Power_Mode;
  uint8_t Output_DataRate;
  uint8_t Axes_Enable;
  uint8_t Band_Width;
  uint8_t Block_Data;
  uint8_t Endiannes;
  uint8_t Full_Scale;
  
} GYRO_InitStruct;

/* Filter config structure */
 
typedef struct
{
  uint8_t HPF_Mode;
  uint8_t HPF_CutOff_Frequency;
  
} GYRO_FilterConfigStruct;

/* Interrupt config structure*/
typedef struct
{
  uint8_t Interrupt_Request;
  uint8_t Interrupt_Axes;
  uint8_t Interrupt_Edge;
  
} GYRO_InterruptConfigStruct;


/*******************************************************
************** Define L3GD20 Registers *****************
********************************************************/

#define GYRO_WHO_AM_I         ((uint8_t)0x0F)
#define GYRO_CTRL_REG1        ((uint8_t)0x20)
#define GYRO_CTRL_REG2        ((uint8_t)0x21)
#define GYRO_CTRL_REG3        ((uint8_t)0x22)
#define GYRO_CTRL_REG4        ((uint8_t)0x23)
#define GYRO_CTRL_REG5        ((uint8_t)0x24)
#define GYRO_REFERENCE        ((uint8_t)0x25)
#define GYRO_OUT_TEMP         ((uint8_t)0x26)
#define GYRO_STATUS_REG       ((uint8_t)0x27)
#define GYRO_OUT_X_L          ((uint8_t)0x28)
#define GYRO_OUT_X_H          ((uint8_t)0x29)
#define GYRO_OUT_Y_L          ((uint8_t)0x2A)
#define GYRO_OUT_Y_H          ((uint8_t)0x2B)
#define GYRO_OUT_Z_L          ((uint8_t)0x2C)
#define GYRO_OUT_Z_H          ((uint8_t)0x2D)
#define GYRO_FIFO_CTRL_REG    ((uint8_t)0x2E)
#define GYRO_FIFO_SRC_REF     ((uint8_t)0x2F)
#define GYRO_INT1_CFG         ((uint8_t)0x30)
#define GYRO_INT1_SRC         ((uint8_t)0x31)
#define GYRO_INT1_THS_XH      ((uint8_t)0x32)
#define GYRO_INT1_THS_XL      ((uint8_t)0x33)
#define GYRO_INT1_THS_YH      ((uint8_t)0x34)
#define GYRO_INT1_THS_YL      ((uint8_t)0x35)
#define GYRO_INT1_THS_ZH      ((uint8_t)0x36)
#define GYRO_INT1_THS_ZL      ((uint8_t)0x37)
#define GYRO_INT1_DURATION    ((uint8_t)0x38)


/************** Power Modes ************************
***************************************************/

#define GYRO_POWERDOWN_MODE     ((uint8_t)0x00)
#define GYRO_NORMAL_MODE        ((uint8_t)0x08)

/**************** Output DataRate ******************
****************************************************/

#define GYRO_OUTPUT_DATARATE1   ((uint8_t)0x00)
#define GYRO_OUTPUT_DATARATE2   ((uint8_t)0x40)
#define GYRO_OUTPUT_DATARATE3   ((uint8_t)0x80)
#define GYRO_OUTPUT_DATARATE4   ((uint8_t)0xC0)

/**************** Axes Selection *******************
****************************************************/

#define GYRO_X_ENABLE           ((uint8_t)0x02)
#define GYRO_Y_ENABLE           ((uint8_t)0x01)
#define GYRO_Z_ENABLE           ((uint8_t)0x04)
#define GYRO_AXES_ENABLE        ((uint8_t)0x07)
#define GYRO_AXES_DISABLE       ((uint8_t)0x00)

/***************** Bandwidth Selection ***************
*****************************************************/

#define GYRO_BANDWIDTH_1   ((uint8_t)0x00)
#define GYRO_BANDWIDTH_2   ((uint8_t)0x10)
#define GYRO_BANDWIDTH_3   ((uint8_t)0x20)
#define GYRO_BANDWIDTH_4   ((uint8_t)0x30)

/***************** Full Scale selection **************
*****************************************************/

#define GYRO_FULLSCALE_250              ((uint8_t)0x00)
#define GYRO_FULLSCALE_500              ((uint8_t)0x10)
#define GYRO_FULLSCALE_2000             ((uint8_t)0x20)
#define GYRO_FULLSCALE_SELECTION        ((uint8_t)0x30)

/****************** Sensitivity ***********************
******************************************************/

#define GYRO_SENSITIVITY_250PS             ((float)8.75)
#define GYRO_SENSITIVITY_500PS             ((float)17.50)
#define GYRO_SENSITIVITY_2000PS            ((float)70.00)

/******************* Data update *********************
*****************************************************/

#define GYRO_DATAUPDATE_CONTINOUS       ((uint8_t)0x00)
#define GYRO_DATAUPDATE_SINGLE          ((uint8_t)0x80)

/************ Endian direction **********************
*****************************************************/

#define GYRO_LSB_DATA       ((uint8_t)0x00)
#define GYRO_MSB_DATA       ((uint8_t)0x40)

/*********** High Pass Filter ***********************
*****************************************************/

#define GYRO_HP_FILTER_ENABLE        ((uint8_t)0x00)
#define GYRO_HP_FILTER_DISABLE       ((uint8_t)0x10)

/************* Interrupt selection *******************
******************************************************/

#define GYRO_INT1        ((uint8_t)0x00)
#define GYRO_INT2        ((uint8_t)0x01)

/************* INT1 status ***************************
******************************************************/

#define GYRO_INT1_STATUS_ENABLE         ((uint8_t)0x80)
#define GYRO_INT1_STATUS_DISABLE        ((uint8_t)0x00)

/************* INT2 status****************************
******************************************************/

#define GYRO_INT2_STATUS_ENABLE         ((uint8_t)0x00)
#define GYRO_INT2_STATUS_DISABLE        ((uint8_t)0x08)

/************* Interrupt Edge Selection ***************
******************************************************/

#define GYRO_INT_LOW_EDGE         ((uint8_t)0x20)
#define GYRO_INT_HIGH_EDGE        ((uint8_t)0x00)

/************** Boot Mode selection *******************
******************************************************/

#define GYRO_NORMALMODE_BOOT            ((uint8_t)0x00)
#define GYRO_REBOOTMEMORY_BOOT          ((uint8_t)0x80)


/************ High Pass Filter mode *******************
******************************************************/

#define GYRO_HPF_NORMALMODE_RES         ((uint8_t)0x00)
#define GYRO_HPF_REF                    ((uint8_t)0x10)
#define GYRO_HPF_NORMAL                 ((uint8_t)0x20)
#define GYRO_HPF_AUTORESET              ((uint8_t)0x30)

/*********** High Pass Cut-off Freq *******************
******************************************************/

#define GYRO_HPFCF_0              ((uint8_t)0x00)
#define GYRO_HPFCF_1              ((uint8_t)0x01)
#define GYRO_HPFCF_2              ((uint8_t)0x02)
#define GYRO_HPFCF_3              ((uint8_t)0x03)
#define GYRO_HPFCF_4              ((uint8_t)0x04)
#define GYRO_HPFCF_5              ((uint8_t)0x05)
#define GYRO_HPFCF_6              ((uint8_t)0x06)
#define GYRO_HPFCF_7              ((uint8_t)0x07)
#define GYRO_HPFCF_8              ((uint8_t)0x08)
#define GYRO_HPFCF_9              ((uint8_t)0x09)

#define GYRO_CS_LOW()           LL_GPIO_ResetOutputPin(GPIOC,LL_GPIO_PIN_1);
#define GYRO_CS_HIGH()          LL_GPIO_SetOutputPin(GPIOC,LL_GPIO_PIN_1);

/******** Private functions **************/

void GYRO_Init(GYRO_InitStruct* InitStruct);
void GYRO_Reboot(void);

void GYRO_INT1InterruptCmd(uint8_t state);
void GYRO_INT2InterruptCmd(uint8_t state);
void Gyro_InterruptConfig(GYRO_InterruptConfigStruct* interruptStruct);

void GYRO_FilterConfig(GYRO_FilterConfigStruct* Filter);
void GYRO_FilterCmd(uint8_t HPFState);
uint8_t GYRO_GetStatus(void);
void GYRO_ReadXYZ(float* pdata);
void GYRO_Write(uint8_t* pBuff, uint8_t addr, uint8_t numBytes);
void GYRO_Read(uint8_t* pBuff,uint8_t addr,uint8_t numBytes);

#endif