#include "stm32f3xx_ll_bus.h"

int main(){
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
	return 0;
}
