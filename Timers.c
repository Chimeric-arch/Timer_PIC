// PIC16F627A / 628A / 648A

#define led RB0_bit

int timer = 0x00;

// Port�tipo de fun��es
void interrupt();

// Inicio Main
void main() 
{
  // Inicializa��o das PORTB's
  TRISB = 0x00;
  PORTB = 0x00;
  
  // Desativa comparadores internos
  CMCON = 0x07;
  
  // Inicializa��o Timer0
  OPTION_REG = 0x81;     // Desabilita pull-ups do PORTB e seta prescaler 1:4
  GIE_bit = 0x01;        // Habilita interrup��es globais
  PEIE_bit = 0x01;       // Habilita interrup��es perif�ficas
  T0IE_bit = 0x01;       // Habilita interrup��o do TIMER0
  TMR0 = 0x06;           // Inicializa o TIMER0
  
  // Inicio loop
  while (1)
  {
    if (timer == 0x01F4) // (ciclo de maquina * prescaler * registrador_8_bit)
    {
      timer = 0x00;
      led = ~led;
    }
  }// Fim loop
}// Fim main

void interrupt()
{
  if (T0IF_bit)          // Verifica overflow do TMR0
  {
    timer++;             // Incrementa var. timer a cada overflow de TMR0
    T0IF_bit = 0x00;     // Limpa flag T0IF
  }
}
