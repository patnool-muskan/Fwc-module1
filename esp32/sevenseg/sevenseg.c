#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

// 7-Segment pin connections
#define SEG_A GPIO_NUM_13
#define SEG_B GPIO_NUM_12
#define SEG_C GPIO_NUM_14
#define SEG_D GPIO_NUM_27
#define SEG_E GPIO_NUM_26
#define SEG_F GPIO_NUM_25
#define SEG_G GPIO_NUM_33

// Function prototypes
void display_number(int num);
void clear_display(void);

// 🧠 Main Program
void app_main(void)
{
    // Configure all segment pins as outputs
    gpio_reset_pin(SEG_A);
    gpio_reset_pin(SEG_B);
    gpio_reset_pin(SEG_C);
    gpio_reset_pin(SEG_D);
    gpio_reset_pin(SEG_E);
    gpio_reset_pin(SEG_F);
    gpio_reset_pin(SEG_G);

    gpio_set_direction(SEG_A, GPIO_MODE_OUTPUT);
    gpio_set_direction(SEG_B, GPIO_MODE_OUTPUT);
    gpio_set_direction(SEG_C, GPIO_MODE_OUTPUT);
    gpio_set_direction(SEG_D, GPIO_MODE_OUTPUT);
    gpio_set_direction(SEG_E, GPIO_MODE_OUTPUT);
    gpio_set_direction(SEG_F, GPIO_MODE_OUTPUT);
    gpio_set_direction(SEG_G, GPIO_MODE_OUTPUT);

    printf("\nLogic Gate Implementation: F = X'Y' + YZ\n");
    printf("Enter X, Y, Z (0 or 1 each)\n");

    int X, Y, Z;
    while (1)
    {
        printf("\nEnter X: ");
        scanf("%d", &X);
        printf("Enter Y: ");
        scanf("%d", &Y);
        printf("Enter Z: ");
        scanf("%d", &Z);

        // Logic equation
        int F = ((!X && !Y) || (Y && Z));
        printf("=> F = %d\n", F);

        // Display on 7-segment
        if (F == 1)
            display_number(1);
        else
            display_number(0);

        vTaskDelay(2000 / portTICK_PERIOD_MS); // Wait 2 seconds
    }
}

// Clear all segments (turn OFF)
void clear_display(void)
{
    gpio_set_level(SEG_A, 1);
    gpio_set_level(SEG_B, 1);
    gpio_set_level(SEG_C, 1);
    gpio_set_level(SEG_D, 1);
    gpio_set_level(SEG_E, 1);
    gpio_set_level(SEG_F, 1);
    gpio_set_level(SEG_G, 1);
}

// Display number on 7-segment (for Common Anode)
void display_number(int num)
{
    clear_display();
    switch (num)
    {
    case 0:
        // Segments ON = LOW
        gpio_set_level(SEG_A, 0);
        gpio_set_level(SEG_B, 0);
        gpio_set_level(SEG_C, 0);
        gpio_set_level(SEG_D, 0);
        gpio_set_level(SEG_E, 0);
        gpio_set_level(SEG_F, 0);
        // G OFF
        gpio_set_level(SEG_G, 1);
        break;

    case 1:
        gpio_set_level(SEG_A, 1);
        gpio_set_level(SEG_B, 0);
        gpio_set_level(SEG_C, 0);
        gpio_set_level(SEG_D, 1);
        gpio_set_level(SEG_E, 1);
        gpio_set_level(SEG_F, 1);
        gpio_set_level(SEG_G, 1);
        break;

    default:
        clear_display();
        break;
    }
}
