include <system_LPC17xx.h>
 
 
void delay_ms(unsigned int ms)
{
    unsigned int i,j;
 
    for(i=0;i<ms;i++)
        for(j=0;j<20000;j++);
}
 
 
int main() 
{
 
    LPC_PINCON->PINSEL4 &= !(1<<1);     // ����������� ��� HL1 ��� GPIO
    LPC_PINCON->PINSEL4 &= !(1<<0);     // ����������� ��� HL2 ��� GPIO
    LPC_PINCON->PINSEL0 &= !(1<<9);     // ����������� ��� SA ��� GPIO
 
    LPC_GPIO2->FIODIR |= (1<<1);    // ��������� ��� ��� HL1 - ���������
    LPC_GPIO2->FIODIR |= (1<<0);    // ��������� ��� ��� HL2 - ���������
    LPC_GPIO0->FIODIR &= !(1<<9);   // ��������� ��� ��� SA - ��������
    
    LPC_GPIO2->FIOSET |= 1<<1;      // �������� HL1
    LPC_GPIO2->FIOCLR |= 1<<0;      // ��������� HL2
 
    while(1)
    {   
    if(getPinState())           // ������ ������
        LPC_GPIO2->FIOSET |= 1<<0;  // ������ + �� HL2
    else                    // �����
        LPC_GPIO2->FIOCLR |= 1<<0;  // ������ 0 �� HL2
 
        LPC_GPIO2->FIOSET |= 1<<7;  // ������ ������������� ������ �� HL1
        delay_ms(1000);         // ���� 1 �������
 
        LPC_GPIO2->FIOCLR |= 1<<7;  // ������ "0" �� HL1
        delay_ms(1000);         // ���� 1 �������
    }
 
}
 
int getPinState()
{
 
  int pinBlockState = LPC_GPIO0->FIOPIN;        // ��������� �������� ����� P0
  int pinState = (pinBlockState & (1 << 9)) ? 1 : 0;    // ���������, + ��� - ����� �� ���� SA
  return pinState;                  // ������� �������� ���� SA
}
}
 
