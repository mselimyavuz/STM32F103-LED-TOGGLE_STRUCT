// Where is the LED connected?
// Port	: A
// Pin	: 5

#include <stdint.h>

#define PERIPH_BASE				(0x40000000UL)

#define APB2PERIPH_OFFSET		(0x00010000UL)
#define APB2PERIPH_BASE			(PERIPH_BASE + APB2PERIPH_OFFSET)

#define GPIOA_OFFSET			(0x0800UL)
#define GPIOA_BASE				(APB2PERIPH_BASE + GPIOA_OFFSET)

#define AHBPERIPH_OFFSET		(0x00018000)
#define AHBPERIPH_BASE			(PERIPH_BASE + AHBPERIPH_OFFSET)

#define RCC_OFFSET				(0x9000UL)
#define RCC_BASE				(AHBPERIPH_BASE + RCC_OFFSET)

#define IOPAEN					(1U<<2) // 0b 0000 0000 0000 0000 0000 0000 0000 0100 # bit 2 of IO port A clock enable

#define PIN5					(1U<<5)
#define LED_PIN					PIN5

#define __IO volatile


typedef struct
{
	__IO uint32_t DUMMY[6];
	__IO uint32_t APB2ENR;
} RCC_TypeDef;


typedef struct
{
	__IO uint32_t CRL;
	__IO uint32_t DUMMY[2];
	__IO uint32_t ODR;

} GPIO_TypeDef;


#define RCC		((RCC_TypeDef*) RCC_BASE)
#define GPIOA	((GPIO_TypeDef*) GPIOA_BASE)

int main(void)
{
	/* 1. Enable clock access GPIOA */
	RCC->APB2ENR |= IOPAEN; // OR the bits

	/* 2. Set PA5 as output mode */
	GPIOA->CRL |= (1U<<20); // Set bit 20 to 1
	GPIOA->CRL &=~ (1U<<21); // Set bit 21 to 0
	GPIOA->CRL &=~ (1U<<22); // Set bit 22 to 0
	GPIOA->CRL &=~ (1U<<23); // Set bit 23 to 0

	while(1)
	{
		GPIOA-> ODR ^= LED_PIN;

		for(int i = 0; i<100000; i++){}
	}

}
