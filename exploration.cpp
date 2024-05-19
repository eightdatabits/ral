
#include <stdint.h>

// Potential designs:
// 1. Raw preprocessor constants, calculations done inline
// 2. Raw preprocessor constants, calculations done in helper functions
// 3. Store base address of peripheral and calculate register addresses on the fly
// 4. Store register addresses
// 5. Overlay peripheral object on peripheral memory

#define CAN_BASE_ADDRESS 0xdeadbeef

#define CAN_REG1_OFFSET 0x00
#define CAN_REG1_VAL1_MASK 0x000000FF
#define CAN_REG1_VAL1_SHFT 0
#define CAN_REG1_VAL2_MASK 0x00000F00
#define CAN_REG1_VAL2_SHFT 8
#define CAN_REG1_VAL3_MASK 0x00003000
#define CAN_REG1_VAL3_SHFT 12
#define CAN_REG1_VAL4_MASK 0xFFFF0000
#define CAN_REG1_VAL4_SHFT 16

void can_init() {
    *((volatile uint32_t*)(CAN_BASE_ADDRESS + CAN_REG1_OFFSET)) = 0x11 << CAN_REG1_VAL1_SHFT;
}

void set_val2(uint8_t new_val) {
    *((volatile uint32_t*)(CAN_BASE_ADDRESS + CAN_REG1_OFFSET)) = (*((volatile uint32_t*)(CAN_BASE_ADDRESS + CAN_REG1_OFFSET)) & ~CAN_REG1_VAL2_MASK) | ((new_val << CAN_REG1_VAL2_SHFT) & CAN_REG1_VAL2_MASK);
}

class CanPeripheral {
    volatile uint32_t* base_address;
    static constexpr uint32_t reg1_offset = 0x00;
    static constexpr uint32_t reg1_val1_mask = 0x000000FF;
    static constexpr uint32_t reg1_val1_shift = 0;
    static constexpr uint32_t reg1_val2_mask = 0x00000F00;
    static constexpr uint32_t reg1_val2_shift = 8;

public:
    CanPeripheral() : base_address{(volatile uint32_t*)(0xdeadbeef + 0x00)} {}

    void init() {
        *(base_address + reg1_offset) = 0x11 << reg1_val1_shift;
    }

    void set_val2(uint8_t new_val) {
        *(base_address + reg1_offset) = (*(base_address + reg1_offset) & ~reg1_val2_mask) | ((new_val << reg1_val2_shift) & reg1_val2_mask);
    }
};

CanPeripheral can1;

int main(int argc) {
    can1.init();
    can1.set_val2(argc);
    return 0;
}