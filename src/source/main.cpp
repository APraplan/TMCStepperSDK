#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/dma.h"
#include "string.h"
#include "pico/multicore.h"
#include "hardware/pio.h"
#include "AccelStepperSDK/src/AccelStepper.hpp"
#include "TMCStepperSDK/src/source/TMCStepper.h"

#include "Falcon.hpp"

TMC2209Stepper driverOne(uart1, D1_RS, D1_ADDRESS);
TMC2209Stepper driverTwo(uart1, D2_RS, D2_ADDRESS);
TMC2209Stepper driverThree(uart1, D3_RS, D3_ADDRESS);
TMC2209Stepper driverFour(uart0, D4_RS, D4_ADDRESS);
TMC2209Stepper driverFive(uart0, D5_RS, D5_ADDRESS);
TMC2209Stepper driverSix(uart0, D6_RS, D6_ADDRESS);

AccelStepper stepperOne(AccelStepper::DRIVER, D1_STEP, D1_DIR);
AccelStepper stepperTwo(AccelStepper::DRIVER, D2_STEP, D2_DIR);
AccelStepper stepperThree(AccelStepper::DRIVER, D3_STEP, D3_DIR);
AccelStepper stepperFour(AccelStepper::DRIVER, D4_STEP, D4_DIR);
AccelStepper stepperFive(AccelStepper::DRIVER, D5_STEP, D5_DIR);
AccelStepper stepperSix(AccelStepper::DRIVER, D6_STEP, D6_DIR);

void secondary(); // Core 1 entry

int main() // Core 0 entry
{

    stdio_init_all();

    multicore_launch_core1(secondary);

    gpio_set_function(0, GPIO_FUNC_UART);
    gpio_set_function(1, GPIO_FUNC_UART);
    gpio_set_function(4, GPIO_FUNC_UART);
    gpio_set_function(5, GPIO_FUNC_UART);

    gpio_init(D1_STEP);
    gpio_set_dir(D1_STEP, GPIO_OUT);
    gpio_init(D1_DIR);
    gpio_set_dir(D1_DIR, GPIO_OUT);
    gpio_init(D1_DIAG);
    gpio_set_dir(D1_DIAG, GPIO_IN);

    gpio_init(D2_STEP);
    gpio_set_dir(D2_STEP, GPIO_OUT);
    gpio_init(D2_DIR);
    gpio_set_dir(D2_DIR, GPIO_OUT);
    gpio_init(D2_DIAG);
    gpio_set_dir(D2_DIAG, GPIO_IN);

    gpio_init(D3_STEP);
    gpio_set_dir(D3_STEP, GPIO_OUT);
    gpio_init(D3_DIR);
    gpio_set_dir(D3_DIR, GPIO_OUT);
    gpio_init(D3_DIAG);
    gpio_set_dir(D3_DIAG, GPIO_IN);

    gpio_init(D4_STEP);
    gpio_set_dir(D4_STEP, GPIO_OUT);
    gpio_init(D4_DIR);
    gpio_set_dir(D4_DIR, GPIO_OUT);
    gpio_init(D4_DIAG);
    gpio_set_dir(D4_DIAG, GPIO_IN);

    gpio_init(D5_STEP);
    gpio_set_dir(D5_STEP, GPIO_OUT);
    gpio_init(D5_DIR);
    gpio_set_dir(D5_DIR, GPIO_OUT);
    gpio_init(D5_DIAG);
    gpio_set_dir(D5_DIAG, GPIO_IN);

    gpio_init(D6_STEP);
    gpio_set_dir(D6_STEP, GPIO_OUT);
    gpio_init(D6_DIR);
    gpio_set_dir(D6_DIR, GPIO_OUT);
    gpio_init(D6_DIAG);
    gpio_set_dir(D6_DIAG, GPIO_IN);

    gpio_init(D_ENABLE);
    gpio_set_dir(D_ENABLE, GPIO_OUT);
    gpio_put(D_ENABLE, D_ON);

    uart_init(uart0, 115200);
    uart_init(uart1, 115200);

    driverOne.begin();            
    driverOne.rms_current(700);
    //driverOne.en_pwm_mode(1);
    driverOne.pwm_autoscale(1);
    driverOne.microsteps(16);
    driverOne.TCOOLTHRS(0xFFFFF);
    // driverOne.SGTHRS(STALLA_VALUE);

    stepperOne.setMaxSpeed(1000.0);
    stepperOne.setAcceleration(1000.0);

    stepperTwo.setMaxSpeed(1000.0);
    stepperTwo.setAcceleration(1000.0);

    stepperThree.setMaxSpeed(1000.0);
    stepperThree.setAcceleration(1000.0);

    stepperFour.setMaxSpeed(1000.0);
    stepperFour.setAcceleration(1000.0);

    stepperFive.setMaxSpeed(1000.0);
    stepperFive.setAcceleration(1000.0);

    stepperSix.setMaxSpeed(1000.0);
    stepperSix.setAcceleration(1000.0);

    stepperOne.moveTo(1000);
    stepperTwo.moveTo(1000);
    stepperThree.moveTo(1000);
    stepperFour.moveTo(1000);
    stepperFive.moveTo(1000);
    stepperSix.moveTo(1000);

    while(true){
        stepperOne.run();
        stepperTwo.run();
        stepperThree.run();
        stepperFour.run();
        stepperFive.run();
        stepperSix.run();

        uint32_t status = driverOne.DRV_STATUS();
        printf("Driver One Status: 0x%08x\n", status);

        sleep_ms(10);
    }

    return 0;
}

void secondary()
{ 

};