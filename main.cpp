#include <system_LPC17xx.h>
#include <pt.h>
 

int getPinState()
{
 
  int pinBlockState = LPC_GPIO0->FIOPIN;        // Прочитать значения пинов P0
  int pinState = (pinBlockState & (1 << 9)) ? 1 : 0;    // Проверить, + или - подан на ногу SA
  return pinState;                  // Вернуть значение пина SA
}
 
int main() 
{
 
    LPC_PINCON->PINSEL4 &= ~(15);     // Настраиваем пины HL1 HL2 как GPIO
    LPC_PINCON->PINSEL0 &= ~(1<<9);     // Настраиваем пин SA как GPIO
 
    LPC_GPIO2->FIODIR |= (1<<1);    // Указываем что пин HL1 - выводящий
    LPC_GPIO2->FIODIR |= (1<<0);    // Указываем что пин HL2 - выводящий
    LPC_GPIO0->FIODIR &= ~(1<<9);   // Указываем что пин SA - вводящий
    
    LPC_GPIO2->FIOSET |= 1<<1;      // Включаем HL1
    LPC_GPIO2->FIOCLR |= 1<<0;      // Выключаем HL2
 
    while(1)
    {   
    if(!getPinState())           // Кнопка нажата
        LPC_GPIO2->FIOSET |= 1<<0;  // Подаем + на HL2
    else                    // Иначе
        LPC_GPIO2->FIOCLR |= 1<<0;  // Подаем - на HL2
 
        LPC_GPIO2->FIOSET |= 1<<1;  // Подаем + на HL1
                // Ждем 1 секунду
 
        LPC_GPIO2->FIOCLR |= 1<<1;  // Подаем - на HL1
             // Ждем 1 секунду
    }
 
}
 


 
