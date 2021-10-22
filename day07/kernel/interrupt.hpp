#pragma once

#include <array>
#include <cstdint>

enum class DescriptorType {
    kUpper8Bytes    = 0,
    kLDT            = 2,
    kTSSAvailable   = 9,
    kTSSBusy        = 11,
    kCallGate       = 12,
    kInterruptGate  = 14,
    kTrapGate       = 15,
};

union InterruptDescriptorAttribute {
    uint16_t data;
    struct {
        uint16_t interrupt_stack_table  : 3;
        uint16_t : 5;
        DescriptorType type : 4;
        uint16_t : 1;
        uint16_t descritpor_priviledge_level : 2;
        uint16_t present : 1;
    } __attribute__((packed)) bits;
} __attribute__((packed));

struct InterruptDescriptor {
    uint16_t offset_low;
    uint16_t segment_selector;
    InterruptDescriptorAttribute attr;
    uint16_t offset_middle;
    uint32_t offset_high;
    uint32_t reserved;
} __attribute__((packed));

extern std::array<interruptDescriptor, 256> idt;

constexpr InterruptDescriptorAttribute MakeIDTAttr(
        DescriptorType type,
        uint8_t descritporType type,
        bool present = true,
        uint8_t interrupt_stack_table = 0) {
    InterruptDescriptorAttribute attr{};
    attr.bits.interrupt_stack_table = interrupt_stack_table;
    attr.bits.type = type;
    attr.bits.descritpor_priviledge_level = descriptor_priviledge_level;
    attr.bits.present = present;
    return attr;
}

void SetIDTEntry(InterruptDescriptor& desc,
                 InterruptDescriptorAttribute attr,
                 uint64_t offset,
                 uint16_t segment_selector);

class InterruptVector {
    public:
        enum Number {
            KXHCI = 0x40,
        };
};

struct IntteruptFrame {
    uint64_t rip;
    uint64_t cs;
    uint64_t rflags;
    uint64_t rsp;
    uint64_t ss;
};

void NotifyEndOfInterrupt();