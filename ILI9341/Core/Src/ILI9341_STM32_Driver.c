#include "ILI9341_STM32_Driver.h"

volatile uint16_t LCD_HEIGHT = ILI9341_SCREEN_HEIGHT;
volatile uint16_t LCD_WIDTH  = ILI9341_SCREEN_WIDTH;

enum command{
  NOP              = 0x00,
  SWRESET          = 0x01,
  RDDIDIF          = 0x04,
  RDDST            = 0x09,
  RDDPM            = 0x0A,
  RDDMADCTL        = 0x0B,
  RDDCOLMOD        = 0x0C,
  RDDIM = 0x0D,
  RDDSM = 0x0E,
  RDDSDR = 0x0F,
  SPLIN = 0x10,
  SLPOUT = 0x11,
  PTLON = 0x12,
  NORON = 0x13,
  DINVOFF = 0x20,
  DINVON = 0x21,
  GAMSET = 0x26,
  DISPOFF = 0x28,
  DISPON = 0x29,
  CASET = 0x2A,
  PASET = 0x2B,
  RAMWR = 0x2C,
  RGBSET = 0x2D,
  RAMRD = 0x2E,
  PLTAR = 0x30,
  VSCRDEF = 0x33,
  TEOFF = 0x34,
  TEON = 0x35,
  MADCTL = 0x36,
  VSCRSADD = 0x37,
  IDMOFF = 0x38,
  IDMON = 0x39,
  PIXSET = 0x3A,
  WMC = 0x3C,
  RMC = 0x3E,
  STS = 0x44,
  GS = 0x45,
  WRDISBV = 0x51,
  RDDISBV = 0x52,
  WRCTRLD = 0x53,
  RDCTRLD = 0x54,
  WRCABC = 0x55,
  RDCABC = 0x56,
  WRCABCMINBR = 0x5E,
  RDCABCMINBR = 0x5F,
  RDID1 = 0xDA,
  RDID2 = 0xDB,
  RDID3 = 0xDC,
  IFMODE = 0xB0,
  FRMCTR1 = 0xB1,
  FRMCTR2 = 0xB2,
  FRMCTR3 = 0xB3,
  INVTR = 0xB4,
  PRCTR = 0xB5,
  DISCTRL = 0xB6,
  ETMOD = 0xB7,
  BC1 = 0xB8,
  BC2 = 0xB9,
  BC3 = 0xBA,
  BC4 = 0xBB,
  BC4 = 0xBC,
  BC7 = 0xBE,
  BC8 = 0xBF,
  PWCTRL1 = 0xC0,
  PWCTRL2 = 0xC1,
  VMCTRL1 = 0xC5,
  VMCTRL2 = 0xC7,
  NVMWR = 0xD0,
  NVMPKE = 0xD1,
  RDNVM = 0xD2,
  RDID4 = 0xD3,
  PGAMCTRL1 = 0xE0,
  PGAMCTRL2 = 0xE1,
  DGAMCTRL1 = 0xE2,
  DGAMCTRL2 = 0xE3,
  IFCTL = 0xF6,
  RWRCTRLA = 0xCB,
  RWRCTRLB = 0xCF,
  DTCA = 0xE8,
  DTCB = 0xE9,
  DTCC = 0xEA,
  PWRSECCTRL = 0xED,
  E3G = 0xF2,
  PRC = 0xF7,



};

const connection_info_t* ci;

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef* hspi) {
  /* Deselect when Tx Complete */
  if(hspi == ci->spi)
    HAL_GPIO_WritePin(ci->cs.port, ci->cs.pin, GPIO_PIN_SET);
}

static void ILI9341_SPI_Tx(uint8_t data) {
  while(!__HAL_SPI_GET_FLAG(ci->spi, SPI_FLAG_TXE)){};
  HAL_SPI_Transmit_DMA(ci->spi, &data, 1);
  //HAL_SPI_Transmit(HSPI_INSTANCE, &data, 1, 10);
}

static void ILI9341_SPI_TxBuffer(uint8_t *buffer, uint16_t len) {
  while(!__HAL_SPI_GET_FLAG(ci->spi, SPI_FLAG_TXE)){};
  HAL_SPI_Transmit_DMA(ci->spi, buffer, len);
  //HAL_SPI_Transmit(HSPI_INSTANCE, buffer, len, 10);
}

void ILI9341_WriteCommand(uint8_t cmd)
{
  HAL_GPIO_WritePin(ci->dc.port, ci->dc.pin, GPIO_PIN_RESET);  //command
  HAL_GPIO_WritePin(ci->cs.port, ci->cs.pin, GPIO_PIN_RESET);  //select
  ILI9341_SPI_Tx(cmd);
  //HAL_GPIO_WritePin(ci->cs.port, ci->cs.pin, GPIO_PIN_SET);  //deselect
}

void ILI9341_WriteData(uint8_t data)
{
  HAL_GPIO_WritePin(ci->dc.port, ci->dc.pin, GPIO_PIN_SET);  //data
  HAL_GPIO_WritePin(ci->cs.port, ci->cs.pin, GPIO_PIN_RESET);  //select
  ILI9341_SPI_Tx(data);
  //HAL_GPIO_WritePin(ci->cs.port, ci->cs.pin, GPIO_PIN_SET);  //deselect
}

void ILI9341_WriteBuffer(uint8_t *buffer, uint16_t len)
{
  HAL_GPIO_WritePin(ci->dc.port, ci->dc.pin, GPIO_PIN_SET);  //data
  HAL_GPIO_WritePin(ci->cs.port, ci->cs.pin, GPIO_PIN_RESET);  //select
  ILI9341_SPI_TxBuffer(buffer, len);
  //HAL_GPIO_WritePin(ci->cs.port, ci->cs.pin, GPIO_PIN_SET);  //deselect
}

void ILI9341_SetAddress(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
  uint8_t buffer[4];
  buffer[0] = x1 >> 8;
  buffer[1] = x1;
  buffer[2] = x2 >> 8;
  buffer[3] = x2;

  ILI9341_WriteCommand(0x2A);
  ILI9341_WriteBuffer(buffer, sizeof(buffer));

  buffer[0] = y1 >> 8;
  buffer[1] = y1;
  buffer[2] = y2 >> 8;
  buffer[3] = y2;

  ILI9341_WriteCommand(0x2B);
  ILI9341_WriteBuffer(buffer, sizeof(buffer));

  ILI9341_WriteCommand(0x2C);
}

void ILI9341_Reset(void)
{
  HAL_GPIO_WritePin(ci->rst.port, ci->rst.pin, GPIO_PIN_RESET);  //Disable
  HAL_Delay(50);
  HAL_GPIO_WritePin(ci->cs.port, ci->cs.pin, GPIO_PIN_RESET);    //Select
  HAL_Delay(50);
  HAL_GPIO_WritePin(ci->rst.port, ci->rst.pin, GPIO_PIN_SET);    //Enable
  HAL_GPIO_WritePin(ci->cs.port, ci->cs.pin, GPIO_PIN_SET);     //Deselect
}

void ILI9341_Enable(void) {
  HAL_GPIO_WritePin(ci->rst.port, ci->rst.pin, GPIO_PIN_SET);    //Enable
}
#if 0
void ILI9341_Init(void)
{
  ILI9341_Enable();
  ILI9341_Reset();

  //SOFTWARE RESET
  ILI9341_WriteCommand(0x01);
  HAL_Delay(50);

  //POWER CONTROL A
  ILI9341_WriteCommand(0xCB);
  ILI9341_WriteData(0x39);
  ILI9341_WriteData(0x2C);
  ILI9341_WriteData(0x00);
  ILI9341_WriteData(0x34);
  ILI9341_WriteData(0x02);

  //POWER CONTROL B
  ILI9341_WriteCommand(0xCF);
  ILI9341_WriteData(0x00);
  ILI9341_WriteData(0xC1);
  ILI9341_WriteData(0x30);

  //DRIVER TIMING CONTROL A
  ILI9341_WriteCommand(0xE8);
  ILI9341_WriteData(0x85);
  ILI9341_WriteData(0x00);
  ILI9341_WriteData(0x78);

  //DRIVER TIMING CONTROL B
  ILI9341_WriteCommand(0xEA);
  ILI9341_WriteData(0x00);
  ILI9341_WriteData(0x00);

  //POWER ON SEQUENCE CONTROL
  ILI9341_WriteCommand(0xED);
  ILI9341_WriteData(0x64);
  ILI9341_WriteData(0x03);
  ILI9341_WriteData(0x12);
  ILI9341_WriteData(0x81);

  //PUMP RATIO CONTROL
  ILI9341_WriteCommand(0xF7);
  ILI9341_WriteData(0x20);

  //POWER CONTROL,VRH[5:0]
  ILI9341_WriteCommand(0xC0);
  ILI9341_WriteData(0x23);

  //POWER CONTROL,SAP[2:0];BT[3:0]
  ILI9341_WriteCommand(0xC1);
  ILI9341_WriteData(0x10);

  //VCM CONTROL
  ILI9341_WriteCommand(0xC5);
  ILI9341_WriteData(0x3E);
  ILI9341_WriteData(0x28);

  //VCM CONTROL 2
  ILI9341_WriteCommand(0xC7);
  ILI9341_WriteData(0x86);

  //MEMORY ACCESS CONTROL
  ILI9341_WriteCommand(0x36);
  ILI9341_WriteData(0x48);

  //PIXEL FORMAT
  ILI9341_WriteCommand(0x3A);
  ILI9341_WriteData(0x55);

  //FRAME RATIO CONTROL, STANDARD RGB COLOR
  ILI9341_WriteCommand(0xB1);
  ILI9341_WriteData(0x00);
  ILI9341_WriteData(0x18);

  //DISPLAY FUNCTION CONTROL
  ILI9341_WriteCommand(0xB6);
  ILI9341_WriteData(0x08);
  ILI9341_WriteData(0x82);
  ILI9341_WriteData(0x27);

  //3GAMMA FUNCTION DISABLE
  ILI9341_WriteCommand(0xF2);
  ILI9341_WriteData(0x00);

  //GAMMA CURVE SELECTED
  ILI9341_WriteCommand(0x26);
  ILI9341_WriteData(0x01);

  //POSITIVE GAMMA CORRECTION
  ILI9341_WriteCommand(0xE0);
  ILI9341_WriteData(0x0F);
  ILI9341_WriteData(0x31);
  ILI9341_WriteData(0x2B);
  ILI9341_WriteData(0x0C);
  ILI9341_WriteData(0x0E);
  ILI9341_WriteData(0x08);
  ILI9341_WriteData(0x4E);
  ILI9341_WriteData(0xF1);
  ILI9341_WriteData(0x37);
  ILI9341_WriteData(0x07);
  ILI9341_WriteData(0x10);
  ILI9341_WriteData(0x03);
  ILI9341_WriteData(0x0E);
  ILI9341_WriteData(0x09);
  ILI9341_WriteData(0x00);

  //NEGATIVE GAMMA CORRECTION
  ILI9341_WriteCommand(0xE1);
  ILI9341_WriteData(0x00);
  ILI9341_WriteData(0x0E);
  ILI9341_WriteData(0x14);
  ILI9341_WriteData(0x03);
  ILI9341_WriteData(0x11);
  ILI9341_WriteData(0x07);
  ILI9341_WriteData(0x31);
  ILI9341_WriteData(0xC1);
  ILI9341_WriteData(0x48);
  ILI9341_WriteData(0x08);
  ILI9341_WriteData(0x0F);
  ILI9341_WriteData(0x0C);
  ILI9341_WriteData(0x31);
  ILI9341_WriteData(0x36);
  ILI9341_WriteData(0x0F);

  //EXIT SLEEP
  ILI9341_WriteCommand(0x11);
  HAL_Delay(100);

  //TURN ON DISPLAY
  ILI9341_WriteCommand(0x29);

  //STARTING ROTATION
  ILI9341_SetRotation(SCREEN_VERTICAL_1);
}
#endif
void ILI9341_Init_Ex(const connection_info_t* value) {
  ci = value;
  ILI9341_Enable();
  ILI9341_Reset();

  //SOFTWARE RESET
  ILI9341_WriteCommand(0x01);
  HAL_Delay(50);

  //POWER CONTROL A
  ILI9341_WriteCommand(0xCB);
  ILI9341_WriteData(0x39);
  ILI9341_WriteData(0x2C);
  ILI9341_WriteData(0x00);
  ILI9341_WriteData(0x34);
  ILI9341_WriteData(0x02);

  //POWER CONTROL B
  ILI9341_WriteCommand(0xCF);
  ILI9341_WriteData(0x00);
  ILI9341_WriteData(0xC1);
  ILI9341_WriteData(0x30);

  //DRIVER TIMING CONTROL A
  ILI9341_WriteCommand(0xE8);
  ILI9341_WriteData(0x85);
  ILI9341_WriteData(0x00);
  ILI9341_WriteData(0x78);

  //DRIVER TIMING CONTROL B
  ILI9341_WriteCommand(0xEA);
  ILI9341_WriteData(0x00);
  ILI9341_WriteData(0x00);

  //POWER ON SEQUENCE CONTROL
  ILI9341_WriteCommand(0xED);
  ILI9341_WriteData(0x64);
  ILI9341_WriteData(0x03);
  ILI9341_WriteData(0x12);
  ILI9341_WriteData(0x81);

  //PUMP RATIO CONTROL
  ILI9341_WriteCommand(0xF7);
  ILI9341_WriteData(0x20);

  //POWER CONTROL,VRH[5:0]
  ILI9341_WriteCommand(0xC0);
  ILI9341_WriteData(0x23);

  //POWER CONTROL,SAP[2:0];BT[3:0]
  ILI9341_WriteCommand(0xC1);
  ILI9341_WriteData(0x10);

  //VCM CONTROL
  ILI9341_WriteCommand(0xC5);
  ILI9341_WriteData(0x3E);
  ILI9341_WriteData(0x28);

  //VCM CONTROL 2
  ILI9341_WriteCommand(0xC7);
  ILI9341_WriteData(0x86);

  //MEMORY ACCESS CONTROL
  ILI9341_WriteCommand(0x36);
  ILI9341_WriteData(0x48);

  //PIXEL FORMAT
  ILI9341_WriteCommand(0x3A);
  ILI9341_WriteData(0x55);

  //FRAME RATIO CONTROL, STANDARD RGB COLOR
  ILI9341_WriteCommand(0xB1);
  ILI9341_WriteData(0x00);
  ILI9341_WriteData(0x18);

  //DISPLAY FUNCTION CONTROL
  ILI9341_WriteCommand(0xB6);
  ILI9341_WriteData(0x08);
  ILI9341_WriteData(0x82);
  ILI9341_WriteData(0x27);

  //3GAMMA FUNCTION DISABLE
  ILI9341_WriteCommand(0xF2);
  ILI9341_WriteData(0x00);

  //GAMMA CURVE SELECTED
  ILI9341_WriteCommand(0x26);
  ILI9341_WriteData(0x01);

  //POSITIVE GAMMA CORRECTION
  ILI9341_WriteCommand(0xE0);
  ILI9341_WriteData(0x0F);
  ILI9341_WriteData(0x31);
  ILI9341_WriteData(0x2B);
  ILI9341_WriteData(0x0C);
  ILI9341_WriteData(0x0E);
  ILI9341_WriteData(0x08);
  ILI9341_WriteData(0x4E);
  ILI9341_WriteData(0xF1);
  ILI9341_WriteData(0x37);
  ILI9341_WriteData(0x07);
  ILI9341_WriteData(0x10);
  ILI9341_WriteData(0x03);
  ILI9341_WriteData(0x0E);
  ILI9341_WriteData(0x09);
  ILI9341_WriteData(0x00);

  //NEGATIVE GAMMA CORRECTION
  ILI9341_WriteCommand(0xE1);
  ILI9341_WriteData(0x00);
  ILI9341_WriteData(0x0E);
  ILI9341_WriteData(0x14);
  ILI9341_WriteData(0x03);
  ILI9341_WriteData(0x11);
  ILI9341_WriteData(0x07);
  ILI9341_WriteData(0x31);
  ILI9341_WriteData(0xC1);
  ILI9341_WriteData(0x48);
  ILI9341_WriteData(0x08);
  ILI9341_WriteData(0x0F);
  ILI9341_WriteData(0x0C);
  ILI9341_WriteData(0x31);
  ILI9341_WriteData(0x36);
  ILI9341_WriteData(0x0F);

  //EXIT SLEEP
  ILI9341_WriteCommand(0x11);
  HAL_Delay(100);

  //TURN ON DISPLAY
  ILI9341_WriteCommand(0x29);

  //STARTING ROTATION
  ILI9341_SetRotation(SCREEN_VERTICAL_1);
}


void ILI9341_SetRotation(uint8_t rotation)
{
  ILI9341_WriteCommand(0x36);
  HAL_Delay(1);

  switch(rotation)
  {
  case SCREEN_VERTICAL_1:
    ILI9341_WriteData(0x40|0x08);
    LCD_WIDTH = 240;
    LCD_HEIGHT = 320;
    break;
  case SCREEN_HORIZONTAL_1:
    ILI9341_WriteData(0x20|0x08);
    LCD_WIDTH  = 320;
    LCD_HEIGHT = 240;
    break;
  case SCREEN_VERTICAL_2:
    ILI9341_WriteData(0x80|0x08);
    LCD_WIDTH  = 240;
    LCD_HEIGHT = 320;
    break;
  case SCREEN_HORIZONTAL_2:
    ILI9341_WriteData(0x40|0x80|0x20|0x08);
    LCD_WIDTH  = 320;
    LCD_HEIGHT = 240;
    break;
  default:
    break;
  }
}

void ILI9341_DrawColor(uint16_t color)
{
  uint8_t buffer[2] = {color>>8, color};
  ILI9341_WriteBuffer(buffer, sizeof(buffer));
}

void ILI9341_DrawColorBurst(uint16_t color, uint32_t size)
{
  uint32_t BufferSize = 0;

  if((size*2) < BURST_MAX_SIZE)
  {
    BufferSize = size;
  }
  else
  {
    BufferSize = BURST_MAX_SIZE;
  }

  HAL_GPIO_WritePin(ci->dc.port, ci->dc.pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(ci->cs.port, ci->cs.pin, GPIO_PIN_RESET);

  uint8_t chifted = color>>8;
  uint8_t BurstBuffer[BufferSize];

  for(uint32_t j = 0; j < BufferSize; j+=2)
  {
    BurstBuffer[j] = chifted;
    BurstBuffer[j+1] = color;
  }

  uint32_t SendingSize = size * 2;
  uint32_t SendingInBlock = SendingSize / BufferSize;
  uint32_t RemainderFromBlock = SendingSize % BufferSize;

  if(SendingInBlock != 0)
  {
    for(uint32_t j = 0; j < (SendingInBlock); j++)
    {
      HAL_SPI_Transmit(ci->spi, BurstBuffer, BufferSize, 10);
    }
  }

  HAL_SPI_Transmit(ci->spi, BurstBuffer, RemainderFromBlock, 10);
  HAL_GPIO_WritePin(ci->cs.port, ci->cs.pin, GPIO_PIN_SET);
}

void ILI9341_FillScreen(uint16_t color)
{
  ILI9341_SetAddress(0, 0, LCD_WIDTH, LCD_HEIGHT);
  ILI9341_DrawColorBurst(color, LCD_WIDTH*LCD_HEIGHT);
}

void ILI9341_DrawPixel(uint16_t x,uint16_t y,uint16_t color)
{
  if((x >=LCD_WIDTH) || (y >=LCD_HEIGHT)) return;

  uint8_t bufferX[4] = {x>>8, x, (x+1)>>8, (x+1)};
  uint8_t bufferY[4] = {y>>8, y, (y+1)>>8, (y+1)};
  uint8_t bufferC[2] = {color>>8, color};

  ILI9341_WriteCommand(0x2A);            //ADDRESS
  ILI9341_WriteBuffer(bufferX, sizeof(bufferX));  //XDATA

  ILI9341_WriteCommand(0x2B);            //ADDRESS
  ILI9341_WriteBuffer(bufferY, sizeof(bufferY));  //YDATA

  ILI9341_WriteCommand(0x2C);            //ADDRESS
  ILI9341_WriteBuffer(bufferC, sizeof(bufferC));  //COLOR
}

void ILI9341_DrawRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color)
{
  if((x >=LCD_WIDTH) || (y >=LCD_HEIGHT)) return;

  if((x+width-1)>=LCD_WIDTH)
  {
    width=LCD_WIDTH-x;
  }

  if((y+height-1)>=LCD_HEIGHT)
  {
    height=LCD_HEIGHT-y;
  }

  ILI9341_SetAddress(x, y, x+width-1, y+height-1);
  ILI9341_DrawColorBurst(color, height*width);
}

void ILI9341_DrawHLine(uint16_t x, uint16_t y, uint16_t width, uint16_t color)
{
  if((x >=LCD_WIDTH) || (y >=LCD_HEIGHT)) return;

  if((x+width-1)>=LCD_WIDTH)
  {
    width=LCD_WIDTH-x;
  }

  ILI9341_SetAddress(x, y, x+width-1, y);
  ILI9341_DrawColorBurst(color, width);
}

void ILI9341_DrawVLine(uint16_t x, uint16_t y, uint16_t height, uint16_t color)
{
  if((x >=LCD_WIDTH) || (y >=LCD_HEIGHT)) return;

  if((y+height-1)>=LCD_HEIGHT)
  {
    height=LCD_HEIGHT-y;
  }

  ILI9341_SetAddress(x, y, x, y+height-1);
  ILI9341_DrawColorBurst(color, height);
}
