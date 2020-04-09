#pragma once
#include <cstdint>
#include <memory>

enum class register_code {
    // General Purpose Registers
    rax, rbx, rcx, rdx,
    eax, ebx, ecx, edx,
     ax,  bx,  cx,  dx,
     al,  bl,  cl,  dl,
     ah,  bh,  ch,  dh,

     // Floating Point Registers
     st0, st1, st2, st3,
     st4, st5, st6, st7
};

class Register {
private:
    register_code code;
public:
    using register_ptr = std::shared_ptr<Register>;

    Register() = delete;
    Register(register_code);

    register_code get_code() const;
    void clear();

    virtual uint64_t get_value() const = 0;
    virtual void set_value(uint64_t) = 0;
    virtual void increment() = 0;

    virtual ~Register() = default;
};


class FullRegister : public Register {
private:
    uint64_t value;
public:
    FullRegister() = delete;
    FullRegister(register_code);

    uint64_t get_value() const override;
    void set_value(uint64_t) override;
    void increment() override;
};

class PartRegister : public Register {
private:
    register_ptr reg;
    unsigned int size;
    unsigned int offset;
public:
    PartRegister() = delete;
    PartRegister(register_code, register_ptr, unsigned int, unsigned int);

    uint64_t get_value() const override;
    void set_value(uint64_t) override;
    void increment() override;
};
