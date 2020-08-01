include <system_LPC17xx.h>
 
 
void delay_ms(unsigned int ms)
{
    unsigned int i,j;
 
    for(i=0;i<ms;i++)
        for(j=0;j<20000;j++);
}
 
 
int main() 
{
 
    LPC_PINCON->PINSEL4 &= !(1<<1);     // Настраиваем пин HL1 как GPIO
    LPC_PINCON->PINSEL4 &= !(1<<0);     // Настраиваем пин HL2 как GPIO
    LPC_PINCON->PINSEL0 &= !(1<<9);     // Настраиваем пин SA как GPIO
 
    LPC_GPIO2->FIODIR |= (1<<1);    // Указываем что пин HL1 - выводящий
    LPC_GPIO2->FIODIR |= (1<<0);    // Указываем что пин HL2 - выводящий
    LPC_GPIO0->FIODIR &= !(1<<9);   // Указываем что пин SA - вводящий
    
    LPC_GPIO2->FIOSET |= 1<<1;      // Включаем HL1
    LPC_GPIO2->FIOCLR |= 1<<0;      // Выключаем HL2
 
    while(1)
    {   
    if(getPinState())           // Кнопка нажата
        LPC_GPIO2->FIOSET |= 1<<0;  // Подаем + на HL2
    else                    // Иначе
        LPC_GPIO2->FIOCLR |= 1<<0;  // Подаем 0 на HL2
 
        LPC_GPIO2->FIOSET |= 1<<7;  // Подаем положительный сигнал на HL1
        delay_ms(1000);         // Ждем 1 секунду
 
        LPC_GPIO2->FIOCLR |= 1<<7;  // Подаем "0" на HL1
        delay_ms(1000);         // Ждем 1 секунду
    }
 
}
 
int getPinState()
{
 
  int pinBlockState = LPC_GPIO0->FIOPIN;        // Прочитать значения пинов P0
  int pinState = (pinBlockState & (1 << 9)) ? 1 : 0;    // Проверить, + или - подан на ногу SA
  return pinState;                  // Вернуть значение пина SA
}
}
 
