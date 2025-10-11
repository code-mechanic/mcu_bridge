#include "mcu_bridge.h"

#define MCU_CFG_CPU_FREQUENCY_HZ (16000000U)
#define LED_IDX (0U)

static status_t mcu_clock_config(void);

int main(void) {
    mcu_bridge_init_param_t mcu_bridge_init_param = {
        .mcu_clock_config = mcu_clock_config
    };
    mcu_bridge_init(&mcu_bridge_init_param);

    mcu_gpio_config_t led_config = {
        .pin = mcu_gpio_create_pin(0 , 4),
        .pin_dir = MCU_GPIO_PIN_DIR_OUTPUT,
        .op_pin_initial_val = MCU_GPIO_PIN_VAL_LOW,
        .op_pin_speed = MCU_GPIO_PIN_SPEED_LOW,
    };

    mcu_gpio_config_set_default(LED_IDX, &led_config);
    mcu_gpio_config(LED_IDX, &led_config);

    while(1) {
        mcu_gpio_write(LED_IDX, MCU_GPIO_PIN_VAL_HIGH);
        mcu_bridge_delay_ms(1000);
        mcu_gpio_write(LED_IDX, MCU_GPIO_PIN_VAL_LOW);
        mcu_bridge_delay_ms(1000);
    }

    return 0;
}

static status_t mcu_clock_config(void)
{
    status_t status = STATUS_SUCCESS;
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
     */
    HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
    RCC_OscInitStruct.PLL.PLLN = (MCU_CFG_CPU_FREQUENCY_HZ / 1000000);
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
    RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        status = STATUS_FAILURE;
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
    {
        status = STATUS_FAILURE;
    }

    return status;
}
