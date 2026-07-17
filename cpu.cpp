#include "cpu.hpp"

void CPU::inc_16(registerpair& reg) {
    reg.set(reg.get() + 0x0001);
}

uint16_t CPU::fetch_16() {
    uint8_t low = get_memory_temp(PC);
    uint8_t high = get_memory_temp(PC+1);
    PC+=2;
    return (static_cast<uint16_t>(high)<<8) | low;
}

void CPU::ld_mem_reg(registerpair& reg, uint8_t value) {
    set_memory_temp(reg.get(), value);
}

void CPU::inc_8(uint8_t byte) {
    byte++;
    set_zero_flag(byte == 0);
    set

}

void CPU::tick() {
    cycle_count = 0;
    uint8_t opcode = get_memory_temp(PC);
    PC+=1;
    switch (opcode) {
        case 0x00: // no operation
            cycle_count += 4;
            break;
        case 0x01: { // LD BC, d16
            BC.set(fetch_16());
            cycle_count += 12;
            break;
        }
        case 0x02: // LD (BC), A
            ld_mem_reg(BC, AF.high)
            cycle_count += 8;
            break;
        case 0x03: // INC BC
            inc_16(BC);
            cycle_count += 8;
            break;
        case 0x04:

    }
}