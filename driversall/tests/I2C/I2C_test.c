#include "../../SERVICES/BIT_MATH.h"
#include "../../SERVICES/STD_TYPES.h"
#include "../../MCAL/GPIO/GPIO_interface.h"
#include "../../MCAL/I2C/I2C.h"

void main() {
    u8 test_data = 0x55;

    GPIO_Init();  // Initializes TRIS and PORT registers
    I2C_Init();   // Configures MSSP for 100kHz Master Mode
    Delay_ms(100);

    while(1) {
        // --- I2C Write Sequence ---

        // A. Send Start Condition
        I2C_Start();

        I2C_Write(0x30);

        // C. Send the Data Byte
        I2C_Write(test_data);

        // D. Send Stop Condition
        I2C_Stop();

        // Increment data just to see changes in Proteus I2C Debugger
        test_data++;

        // Wait 1 second before sending again
        Delay_ms(1000);
    }
}
