#include "L3GD20_Drv.h"
#include "main.h"

static uint8_t GYRO_SendByte(uint8_t byte);
static void GYRO_Hardware_Init(void);


void GYRO_Init(GYRO_InitStruct* InitStruct)
{
  uint8_t  cnt1 = 0x00, cnt4 = 0x00;
  
  GYRO_Hardware_Init();
  
  cnt1 |= (uint8_t)(InitStruct->Power_Mode | InitStruct->Output_DataRate | InitStruct->Axes_Enable | InitStruct->Band_Width);
  cnt4 |= (uint8_t)(InitStruct->Block_Data | InitStruct->Endiannes | InitStruct->Full_Scale);
  
  GYRO_Write(&cnt1,GYRO_CTRL_REG1,1);
  GYRO_Write(&cnt4,GYRO_CTRL_REG4,1);
  
}

void GYRO_Reboot(void)
{
  uint8_t var;
  GYRO_Read(&var,GYRO_CTRL_REG5,1);
  var |= GYRO_REBOOTMEMORY_BOOT;
  GYRO_Write(&var,GYRO_CTRL_REG5,1);

}

void GYRO_INT1InterruptCmd(uint8_t state)
{
  uint8_t var;
  
  GYRO_Read(&var,GYRO_CTRL_REG3,1);
  
  var &= 0x7F;
  var |= state;
  
  GYRO_Read(&var,GYRO_CTRL_REG3,1);
}
void GYRO_INT2InterruptCmd(uint8_t state)
{
  uint8_t var;
  
  GYRO_Read(&var,GYRO_CTRL_REG3,1);
  
  var &= 0xF7;
  var |= state;
  
  GYRO_Read(&var,GYRO_CTRL_REG3,1);
  
}
void Gyro_InterruptConfig(GYRO_InterruptConfigStruct* Interrupt)
{
  uint8_t cnt_cf = 0, cnt = 0;
  
  GYRO_Read(&cnt_cf,GYRO_INT1_CFG,1);
  GYRO_Read(&cnt,GYRO_CTRL_REG3,1);
  
  cnt_cf &= 0x80;
  cnt &= 0xDF;
  
  cnt_cf |= (uint8_t)(Interrupt->Interrupt_Request | Interrupt->Interrupt_Axes);
  
  cnt |= (uint8_t)(Interrupt->Interrupt_Edge);
  
  GYRO_Write(&cnt_cf,GYRO_INT1_CFG,1);
  GYRO_Write(&cnt,GYRO_CTRL_REG3,1);
}

void GYRO_FilterConfig(GYRO_FilterConfigStruct* Filter)
{
   uint8_t var;
   GYRO_Read(&var,GYRO_CTRL_REG2,1);
   var &= 0xC0;
   
   var |= Filter->HPF_CutOff_Frequency | Filter->HPF_Mode;
   
   GYRO_Write(&var,GYRO_CTRL_REG2,1);
}
void GYRO_FilterCmd(uint8_t HPFState)
{
    uint8_t var;
    GYRO_Read(&var,GYRO_CTRL_REG5,1);
    var &= 0xEF;
    var |= HPFState;
    GYRO_Write(&var,GYRO_CTRL_REG5,1);
}
uint8_t GYRO_GetStatus(void)
{
  uint8_t status;
  GYRO_Read(&status,GYRO_STATUS_REG,1);
  return status;
}

void GYRO_ReadXYZ(float* pdata)
{
  uint8_t buffer[6] = {0};
  int16_t Raw[3] = {0};
  uint8_t var = 0;
  float sens = 0.00;
  
  int i = 0;
  
  GYRO_Read(&var,GYRO_CTRL_REG4,1);
  GYRO_Read(buffer,GYRO_OUT_X_L,6);

  if(!(var & GYRO_MSB_DATA))
  {
    for(i = 0; i < 3; i++)
    {
        Raw[i] = (int16_t)(((uint16_t)buffer[2*i + 1] << 8) + buffer[2*i]);
    }
  }
  else
  {
      Raw[i] = (int16_t)(((uint16_t)buffer[2*i] << 8) + buffer[2*i+1]);
  }
  
  switch(var & GYRO_FULLSCALE_SELECTION)
  {
    case GYRO_FULLSCALE_250:
      sens = GYRO_SENSITIVITY_250PS;
    break;
    case GYRO_FULLSCALE_500:
      sens = GYRO_SENSITIVITY_500PS;
    break;
    case GYRO_FULLSCALE_2000:
      sens = GYRO_SENSITIVITY_2000PS;
    break;
  }
  
  for(i = 0; i < 3; i++)
  {
    pdata[i] = (float)(Raw[i]*sens);
  }
}
void GYRO_Write(uint8_t* pBuff, uint8_t addr, uint8_t numBytes)
{
  if(numBytes > 1)
  {
      addr |= MULTIPLEBYTE_CMD;
  }
  GYRO_CS_LOW()
  GYRO_SendByte(addr);
  while(numBytes > 0)
  {
    GYRO_SendByte(*pBuff);
    numBytes--;
    pBuff++;
  }
  GYRO_CS_HIGH()
}
void GYRO_Read(uint8_t* pBuff,uint8_t addr,uint8_t numBytes)
{
  if(numBytes > 1)
  {
    addr |= RW_CMD | MULTIPLEBYTE_CMD;
  }
  else
  {
    addr |= RW_CMD;
  }
  
  GYRO_CS_LOW()
  GYRO_SendByte(addr);
  
  while(numBytes > 0)
  {
      *pBuff = GYRO_SendByte(DUMMY);
      numBytes--;
      pBuff++;
  }
  GYRO_CS_HIGH()
}

static uint8_t GYRO_SendByte(uint8_t byte)
{
  while(!LL_SPI_IsActiveFlag_TXE(GYRO_SPI) ){}
  LL_SPI_TransmitData8(GYRO_SPI,byte);
  while(!LL_SPI_IsActiveFlag_RXNE(GYRO_SPI)){}
  return LL_SPI_ReceiveData8(GYRO_SPI);
}
static void GYRO_Hardware_Init(void)
{
  LL_SPI_InitTypeDef SPI_InitStruct ;
  LL_GPIO_InitTypeDef GPIO_InitStruct ;

  /* Peripheral clock enable */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI5);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOF);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
  
  /** PC1 Configure as SPI5_CS ***/
  
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Pin = LL_GPIO_PIN_1;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  LL_GPIO_Init(GPIOC,&GPIO_InitStruct);
  
  /**SPI5 GPIO Configuration
  PF7   ------> SPI5_SCK
  PF8   ------> SPI5_MISO
  PF9   ------> SPI5_MOSI
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_7|LL_GPIO_PIN_8|LL_GPIO_PIN_9;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_5;
  LL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /* SPI5 parameter configuration*/
  SPI_InitStruct.TransferDirection = LL_SPI_FULL_DUPLEX;
  SPI_InitStruct.Mode = LL_SPI_MODE_MASTER;
  SPI_InitStruct.DataWidth = LL_SPI_DATAWIDTH_8BIT;
  SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_LOW;
  SPI_InitStruct.ClockPhase = LL_SPI_PHASE_1EDGE;
  SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;
  SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV2;
  SPI_InitStruct.BitOrder = LL_SPI_MSB_FIRST;
  SPI_InitStruct.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;
  SPI_InitStruct.CRCPoly = 10;
  
  LL_SPI_Init(SPI5, &SPI_InitStruct);
  LL_SPI_SetStandard(SPI5, LL_SPI_PROTOCOL_MOTOROLA);
  LL_SPI_Enable(SPI5);
}