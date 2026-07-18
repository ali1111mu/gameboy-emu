#pragma once
#include <cstdint>

class CPU {

    private:
        struct register_pair {
            uint8_t high;
            uint8_t low;

            uint16_t get() const {
                return (static_cast<uint16_t>(high)<<8) | low;
            }

            void set(uint16_t value) {
                high = value >> 8;
                low = value & 0x00FF;
            }
        };

        register_pair AF;
        register_pair BC;
        register_pair DE;
        register_pair HL;

        uint16_t SP;
        uint16_t PC;

        uint8_t cycle_count;

        uint8_t memory[65536] = {};

        void inc_16(register_pair& reg);

        uint16_t fetch_16();

        uint8_t fetch_8();

        void ld_mem_reg(register_pair& reg, uint8_t value);

        void inc_8(uint8_t& byte);

        void dec_8(uint8_t& byte);

        void set_16(uint16_t address, uint16_t data);

        void add_16(uint16_t value_1, uint16_t value_2);

    public:
        
        void set_AF(uint16_t value) {
            AF.set(value & 0xFFF0);
        }

        bool get_zero_flag() {
            return (AF.low & 0x80) != 0;
        }

        void set_zero_flag(bool value) {
            if (value) {
                AF.low |= 0x80;
            } else {
                AF.low &= ~0x80;
            }
        }

        bool get_sub_flag() {
            return (AF.low & 0x40) != 0;
        }

        void set_sub_flag(bool value) {
            if (value) {
                AF.low |= 0x40;
            } else {
                AF.low &= ~0x40;
            }
        }

        bool get_half_carry_flag() {
            return (AF.low & 0x20) != 0;
        }

        void set_half_carry_flag(bool value) {
            if (value) {
                AF.low |= 0x20;
            } else {
                AF.low &= ~0x20;
            }
        }

        bool get_carry_flag() {
            return (AF.low & 0x10) != 0;
        }

        void set_carry_flag(bool value) {
            if (value) {
                AF.low |= 0x10;
            } else {
                AF.low &= ~0x10;
            }
        }

        // temporary memory functions

        uint8_t get_memory_temp(uint16_t address) {
            return memory[address];
        }

        void set_memory_temp(uint16_t address, uint8_t byte) {
            memory[address] = byte;
        }

        void tick();
};