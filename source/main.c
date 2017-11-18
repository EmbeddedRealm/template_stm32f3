#include "stm32f3xx_ll_bus.h"
#include "stm32f3xx_ll_gpio.h"
#include "stm32f3xx_ll_tim.h"

void led_init(void){
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
  LL_GPIO_InitTypeDef gpio;
  LL_GPIO_StructInit(&gpio);
  gpio.Mode = LL_GPIO_MODE_OUTPUT;
  gpio.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  gpio.Pin = LL_GPIO_PIN_13;
  LL_GPIO_Init(GPIOB, &gpio);
  LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_13);
}

void led_toggle(void){
  LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_13);
}

void timer15_init(unsigned int period_us){
  SystemCoreClockUpdate();
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM15);
  LL_TIM_InitTypeDef timer;
  LL_TIM_StructInit(&timer);
  timer.CounterMode = LL_TIM_COUNTERDIRECTION_DOWN;
  timer.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
  timer.Prescaler = 3;
  timer.Autoreload = period_us - 1;
  LL_TIM_Init(TIM15, &timer);
  LL_TIM_SetClockSource(TIM15, LL_TIM_CLOCKSOURCE_INTERNAL);

  LL_TIM_EnableIT_UPDATE(TIM15);
  NVIC_EnableIRQ(TIM1_BRK_TIM15_IRQn);
  LL_TIM_EnableCounter(TIM15);
}



void TIM1_BRK_TIM15_IRQHandler(void){
  static int count = 0;
  LL_TIM_ClearFlag_UPDATE(TIM15);
  if(count <= 20){
    led_toggle(); 
  }else if(count >= 2000){
    count = 0;
  }
  count++;
}

int main(){
  led_init();
  timer15_init(25);
  while(1){
  }
}
