#include "cpu.hpp"

void CPU::inc_16(register_pair& reg) {
    reg.set(reg.get() + 0x0001);
}

uint16_t CPU::fetch_16() {
    uint8_t low = fetch_8();
    uint8_t high = fetch_8();
    return (static_cast<uint16_t>(high)<<8) | low;
}

uint8_t CPU::fetch_8() {
    return(get_memory_temp(PC++));
}

void CPU::ld_mem_reg(register_pair& reg, uint8_t value) {
    set_memory_temp(reg.get(), value);
}

void CPU::inc_8(uint8_t& byte) {
    set_half_carry_flag((byte & 0x0F) == 0x0F);
    byte++;
    set_zero_flag(byte == 0);
    set_sub_flag(false);
}

void CPU::dec_8(uint8_t& byte) {
    set_half_carry_flag((byte & 0x0F) == 0x00);
    byte--;
    set_zero_flag(byte == 0);
    set_sub_flag(true);
}

void CPU::set_16(uint16_t address, uint16_t data) {
    uint8_t low = data & 0x00FF;
    uint8_t high = data >> 8;
    set_memory_temp(address, low);
    set_memory_temp(address + 1, high);
}

uint16_t CPU::add_16(uint16_t value_1, uint16_t value_2) {
    set_half_carry_flag(((value_1 & 0x0FFF) + (value_2 & 0x0FFF)) > 0x0FFF);
    set_sub_flag(false);
    uint32_t sum = static_cast<uint32_t>(value_1)+static_cast<uint32_t>(value_2);
    set_carry_flag(sum > 0x0000FFFF);
    
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
            ld_mem_reg(BC, AF.high);
            cycle_count += 8;
            break;
        case 0x03: // INC BC
            inc_16(BC);
            cycle_count += 8;
            break;
        case 0x04: // INC B
            inc_8(BC.high);
            cycle_count += 4;
            break;
        case 0x05: // DEC B
            dec_8(BC.high);
            cycle_count += 4;
            break;
        case 0x06: // LD B, d8
            BC.high = fetch_8();
            cycle_count += 8;
            break;
        case 0x07: { // RLCA
            uint8_t big_bit = AF.high & 0x80;
            set_carry_flag(big_bit == 0x80);
            AF.high = (AF.high << 1) | (big_bit>>7);
            set_zero_flag(false);
            set_sub_flag(false);
            set_half_carry_flag(false);
            cycle_count += 4;
            break;
        }
        case 0x08: // LD (a16), SP
            set_16(fetch_16(), SP);
            cycle_count += 20;
            break;
        case 0x09: // ADD HL, BC
            

    }
}