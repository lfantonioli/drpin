#include <stdio.h>
#include <stdarg.h>
#include "include/pin/pin.H"
#include "dr_api.h"
#include <unistd.h>
#include "drutil.h"
#include "drsyms.h"
#include "dr_tools.h"
#include <string>
#include <iostream>
#include <stack>
#include <utility>
#include <map>
#include <utility>
#include <queue>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string.h>
#include <vector>
#include <random>
#include <sys/signal.h>


// Auxiliar

//Generate UUID string

std::string generate_uuid() {
    static std::random_device dev;
    static std::mt19937 rng(dev());

    std::uniform_int_distribution<int> dist(0, 15);

    const char *v = "0123456789abcdef";
    const bool dash[] = { 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0 };

    std::string res;
    for (int i = 0; i < 16; i++) {
        if (dash[i]) res += "-";
        res += v[dist(rng)];
        res += v[dist(rng)];
    }
    return res;
}

// pretty print vector
template<typename T>
std::ostream & operator<<(std::ostream & os, std::vector<T> vec)
{
    os<<"{ ";
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<T>(os, " , "));
    os<<"}";
    return os;
}

void ___debug_print(int i){
  std::cout << "cheguei aqui " << i << std::endl << std::flush;
//   usleep(10000);

}

opnd_t OPND_CREATE_UINT64( UINT64 val) { 
  return opnd_create_immed_uint((ptr_int_t)(val), OPSZ_8);
}

opnd_t OPND_CREATE_UINT32( UINT32 val) { 
  return opnd_create_immed_uint((ptr_int_t)(val), OPSZ_4);
}

bool drpin_reg_is_8bit(reg_id_t drpin_reg){
    // only implementing this because cound't find an dynamorio api
    return (drpin_reg >= DR_REG_START_8 && drpin_reg <= DR_REG_STOP_8);
}

bool drpin_reg_is_16bit(reg_id_t drpin_reg){
    // only implementing this because cound't find an dynamorio api
    return (drpin_reg >= DR_REG_START_16 && drpin_reg <= DR_REG_STOP_16);
}

bool drpin_reg_is_32bit(reg_id_t drpin_reg){
    return reg_is_32bit(drpin_reg);
}

bool drpin_reg_is_64bit(reg_id_t drpin_reg){
    return reg_is_64bit(drpin_reg);
}

reg_id_t drpin_8bit_reg_to_64bit_reg(reg_id_t drpin_reg){

    return (drpin_reg - DR_REG_START_8) + DR_REG_START_64;
}

reg_id_t drpin_16bit_reg_to_64bit_reg(reg_id_t drpin_reg){
    return (drpin_reg - DR_REG_START_16) + DR_REG_START_64;
}

reg_id_t drpin_32bit_reg_to_64bit_reg(reg_id_t drpin_reg){
    return reg_32_to_64(drpin_reg);
}

// static std::vector<std::pair<ROOT_THREAD_FUNC*, VOID*>> spawnInternalThreadCallbacks;

reg_id_t convert_pin_reg_to_drpin_reg(REG pin_reg){
    // Dynamorio does not have the REG_EFLAGS or REG_RFLAGS register as this abstractions. So we should be careful to
    // not blindly use this function when the user is requesting eflags/rflags data
    reg_id_t drpin_reg = REG_INVALID;

    if( pin_reg == LEVEL_BASE::REG::REG_EFLAGS ){
        std::cout << "ASKED FOR REF_EFLAGS.... cannot provide it" << std::endl << std::flush;
    }

    if( pin_reg == LEVEL_BASE::REG::REG_RFLAGS ){
        std::cout << "ASKED FOR REF_EFLAGS.... cannot provide it" << std::endl << std::flush;
    }

    if ( pin_reg == LEVEL_BASE::REG::REG_RAX) {

        drpin_reg = DR_REG_RAX;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_RCX) {

        drpin_reg = DR_REG_RCX;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_RDX) {

        drpin_reg = DR_REG_RDX;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_RBX) {

        drpin_reg = DR_REG_RBX;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_RSP) {

        drpin_reg = DR_REG_RSP;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_RBP) {

        drpin_reg = DR_REG_RBP;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_RSI) {

        drpin_reg = DR_REG_RSI;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_RDI) {

        drpin_reg = DR_REG_RDI;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_R8) {

        drpin_reg = DR_REG_R8;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_R9) {

        drpin_reg = DR_REG_R9;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_R10) {

        drpin_reg = DR_REG_R10;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_R11) {

        drpin_reg = DR_REG_R11;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_R12) {

        drpin_reg = DR_REG_R12;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_R13) {

        drpin_reg = DR_REG_R13;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_R14) {

        drpin_reg = DR_REG_R14;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_R15) {

        drpin_reg = DR_REG_R15;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_EAX) {

        drpin_reg = DR_REG_EAX;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_ECX) {

        drpin_reg = DR_REG_ECX;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_EDX) {

        drpin_reg = DR_REG_EDX;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_EBX) {

        drpin_reg = DR_REG_EBX;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_ESP) {

        drpin_reg = DR_REG_ESP;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_EBP) {

        drpin_reg = DR_REG_EBP;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_ESI) {

        drpin_reg = DR_REG_ESI;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_EDI) {

        drpin_reg = DR_REG_EDI;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_R8D) {

        drpin_reg = DR_REG_R8D;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_R9D) {

        drpin_reg = DR_REG_R9D;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_R10D) {

        drpin_reg = DR_REG_R10D;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_R11D) {

        drpin_reg = DR_REG_R11D;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_R12D) {

        drpin_reg = DR_REG_R12D;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_R13D) {

        drpin_reg = DR_REG_R13D;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_R14D) {

        drpin_reg = DR_REG_R14D;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_R15D) {

        drpin_reg = DR_REG_R15D;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_AX) {

        drpin_reg = DR_REG_AX;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_CX) {

        drpin_reg = DR_REG_CX;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_DX) {

        drpin_reg = DR_REG_DX;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_BX) {

        drpin_reg = DR_REG_BX;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_SP) {

        drpin_reg = DR_REG_SP;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_BP) {

        drpin_reg = DR_REG_BP;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_SI) {

        drpin_reg = DR_REG_SI;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_DI) {

        drpin_reg = DR_REG_DI;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_R8W) {

        drpin_reg = DR_REG_R8W;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_R9W) {

        drpin_reg = DR_REG_R9W;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_R10W) {

        drpin_reg = DR_REG_R10W;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_R11W) {

        drpin_reg = DR_REG_R11W;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_R12W) {

        drpin_reg = DR_REG_R12W;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_R13W) {

        drpin_reg = DR_REG_R13W;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_R14W) {

        drpin_reg = DR_REG_R14W;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_R15W) {

        drpin_reg = DR_REG_R15W;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_AL) {

        drpin_reg = DR_REG_AL;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_CL) {

        drpin_reg = DR_REG_CL;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_DL) {

        drpin_reg = DR_REG_DL;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_BL) {

        drpin_reg = DR_REG_BL;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_AH) {

        drpin_reg = DR_REG_AH;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_CH) {

        drpin_reg = DR_REG_CH;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_DH) {

        drpin_reg = DR_REG_DH;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_BH) {

        drpin_reg = DR_REG_BH;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_SPL) {

        drpin_reg = DR_REG_SPL;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_BPL) {

        drpin_reg = DR_REG_BPL;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_SIL) {

        drpin_reg = DR_REG_SIL;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_DIL) {

        drpin_reg = DR_REG_DIL;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_MM0) {

        drpin_reg = DR_REG_MM0;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_MM1) {

        drpin_reg = DR_REG_MM1;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_MM2) {

        drpin_reg = DR_REG_MM2;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_MM3) {

        drpin_reg = DR_REG_MM3;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_MM4) {

        drpin_reg = DR_REG_MM4;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_MM5) {

        drpin_reg = DR_REG_MM5;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_MM6) {

        drpin_reg = DR_REG_MM6;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_MM7) {

        drpin_reg = DR_REG_MM7;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_XMM0) {

        drpin_reg = DR_REG_XMM0;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_XMM1) {

        drpin_reg = DR_REG_XMM1;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_XMM2) {

        drpin_reg = DR_REG_XMM2;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_XMM3) {

        drpin_reg = DR_REG_XMM3;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_XMM4) {

        drpin_reg = DR_REG_XMM4;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_XMM5) {

        drpin_reg = DR_REG_XMM5;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_XMM6) {

        drpin_reg = DR_REG_XMM6;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_XMM7) {

        drpin_reg = DR_REG_XMM7;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_XMM8) {

        drpin_reg = DR_REG_XMM8;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_XMM9) {

        drpin_reg = DR_REG_XMM9;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_XMM10) {

        drpin_reg = DR_REG_XMM10;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_XMM11) {

        drpin_reg = DR_REG_XMM11;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_XMM12) {

        drpin_reg = DR_REG_XMM12;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_XMM13) {

        drpin_reg = DR_REG_XMM13;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_XMM14) {

        drpin_reg = DR_REG_XMM14;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_XMM15) {

        drpin_reg = DR_REG_XMM15;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_ST0) {

        drpin_reg = DR_REG_ST0;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_ST1) {

        drpin_reg = DR_REG_ST1;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_ST2) {

        drpin_reg = DR_REG_ST2;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_ST3) {

        drpin_reg = DR_REG_ST3;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_ST4) {

        drpin_reg = DR_REG_ST4;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_ST5) {

        drpin_reg = DR_REG_ST5;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_ST6) {

        drpin_reg = DR_REG_ST6;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_ST7) {

        drpin_reg = DR_REG_ST7;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_DR0) {

        drpin_reg = DR_REG_DR0;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_DR1) {

        drpin_reg = DR_REG_DR1;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_DR2) {

        drpin_reg = DR_REG_DR2;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_DR3) {

        drpin_reg = DR_REG_DR3;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_DR4) {

        drpin_reg = DR_REG_DR4;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_DR5) {

        drpin_reg = DR_REG_DR5;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_DR6) {

        drpin_reg = DR_REG_DR6;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_DR7) {

        drpin_reg = DR_REG_DR7;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_CR0) {

        drpin_reg = DR_REG_CR0;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_CR1) {

        drpin_reg = DR_REG_CR1;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_CR2) {

        drpin_reg = DR_REG_CR2;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_CR3) {

        drpin_reg = DR_REG_CR3;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_CR4) {

        drpin_reg = DR_REG_CR4;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_INVALID_) {

        drpin_reg = DR_REG_INVALID;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_YMM0) {

        drpin_reg = DR_REG_YMM0;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_YMM1) {

        drpin_reg = DR_REG_YMM1;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_YMM2) {

        drpin_reg = DR_REG_YMM2;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_YMM3) {

        drpin_reg = DR_REG_YMM3;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_YMM4) {

        drpin_reg = DR_REG_YMM4;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_YMM5) {

        drpin_reg = DR_REG_YMM5;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_YMM6) {

        drpin_reg = DR_REG_YMM6;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_YMM7) {

        drpin_reg = DR_REG_YMM7;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_YMM8) {

        drpin_reg = DR_REG_YMM8;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_YMM9) {

        drpin_reg = DR_REG_YMM9;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_YMM10) {

        drpin_reg = DR_REG_YMM10;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_YMM11) {

        drpin_reg = DR_REG_YMM11;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_YMM12) {

        drpin_reg = DR_REG_YMM12;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_YMM13) {

        drpin_reg = DR_REG_YMM13;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_YMM14) {

        drpin_reg = DR_REG_YMM14;
    
    } else if ( pin_reg == LEVEL_BASE::REG::REG_YMM15) {

        drpin_reg = DR_REG_YMM15;
    
    }




    return drpin_reg;
}

REG convert_drpin_reg_to_pin_reg(reg_id_t drpin_reg){
    REG pin_reg = LEVEL_BASE::REG::REG_INVALID_;


    if ( drpin_reg == DR_REG_NULL) {

        pin_reg = LEVEL_BASE::REG::REG_INVALID_;
    
    } else if ( drpin_reg == DR_REG_RAX) {

        pin_reg = LEVEL_BASE::REG::REG_RAX;
    
    } else if ( drpin_reg == DR_REG_RCX) {

        pin_reg = LEVEL_BASE::REG::REG_RCX;
    
    } else if ( drpin_reg == DR_REG_RDX) {

        pin_reg = LEVEL_BASE::REG::REG_RDX;
    
    } else if ( drpin_reg == DR_REG_RBX) {

        pin_reg = LEVEL_BASE::REG::REG_RBX;
    
    } else if ( drpin_reg == DR_REG_RSP) {

        pin_reg = LEVEL_BASE::REG::REG_RSP;
    
    } else if ( drpin_reg == DR_REG_RBP) {

        pin_reg = LEVEL_BASE::REG::REG_RBP;
    
    } else if ( drpin_reg == DR_REG_RSI) {

        pin_reg = LEVEL_BASE::REG::REG_RSI;
    
    } else if ( drpin_reg == DR_REG_RDI) {

        pin_reg = LEVEL_BASE::REG::REG_RDI;
    
    } else if ( drpin_reg == DR_REG_R8) {

        pin_reg = LEVEL_BASE::REG::REG_R8;
    
    } else if ( drpin_reg == DR_REG_R9) {

        pin_reg = LEVEL_BASE::REG::REG_R9;
    
    } else if ( drpin_reg == DR_REG_R10) {

        pin_reg = LEVEL_BASE::REG::REG_R10;
    
    } else if ( drpin_reg == DR_REG_R11) {

        pin_reg = LEVEL_BASE::REG::REG_R11;
    
    } else if ( drpin_reg == DR_REG_R12) {

        pin_reg = LEVEL_BASE::REG::REG_R12;
    
    } else if ( drpin_reg == DR_REG_R13) {

        pin_reg = LEVEL_BASE::REG::REG_R13;
    
    } else if ( drpin_reg == DR_REG_R14) {

        pin_reg = LEVEL_BASE::REG::REG_R14;
    
    } else if ( drpin_reg == DR_REG_R15) {

        pin_reg = LEVEL_BASE::REG::REG_R15;
    
    } else if ( drpin_reg == DR_REG_EAX) {

        pin_reg = LEVEL_BASE::REG::REG_EAX;
    
    } else if ( drpin_reg == DR_REG_ECX) {

        pin_reg = LEVEL_BASE::REG::REG_ECX;
    
    } else if ( drpin_reg == DR_REG_EDX) {

        pin_reg = LEVEL_BASE::REG::REG_EDX;
    
    } else if ( drpin_reg == DR_REG_EBX) {

        pin_reg = LEVEL_BASE::REG::REG_EBX;
    
    } else if ( drpin_reg == DR_REG_ESP) {

        pin_reg = LEVEL_BASE::REG::REG_ESP;
    
    } else if ( drpin_reg == DR_REG_EBP) {

        pin_reg = LEVEL_BASE::REG::REG_EBP;
    
    } else if ( drpin_reg == DR_REG_ESI) {

        pin_reg = LEVEL_BASE::REG::REG_ESI;
    
    } else if ( drpin_reg == DR_REG_EDI) {

        pin_reg = LEVEL_BASE::REG::REG_EDI;
    
    } else if ( drpin_reg == DR_REG_R8D) {

        pin_reg = LEVEL_BASE::REG::REG_R8D;
    
    } else if ( drpin_reg == DR_REG_R9D) {

        pin_reg = LEVEL_BASE::REG::REG_R9D;
    
    } else if ( drpin_reg == DR_REG_R10D) {

        pin_reg = LEVEL_BASE::REG::REG_R10D;
    
    } else if ( drpin_reg == DR_REG_R11D) {

        pin_reg = LEVEL_BASE::REG::REG_R11D;
    
    } else if ( drpin_reg == DR_REG_R12D) {

        pin_reg = LEVEL_BASE::REG::REG_R12D;
    
    } else if ( drpin_reg == DR_REG_R13D) {

        pin_reg = LEVEL_BASE::REG::REG_R13D;
    
    } else if ( drpin_reg == DR_REG_R14D) {

        pin_reg = LEVEL_BASE::REG::REG_R14D;
    
    } else if ( drpin_reg == DR_REG_R15D) {

        pin_reg = LEVEL_BASE::REG::REG_R15D;
    
    } else if ( drpin_reg == DR_REG_AX) {

        pin_reg = LEVEL_BASE::REG::REG_AX;
    
    } else if ( drpin_reg == DR_REG_CX) {

        pin_reg = LEVEL_BASE::REG::REG_CX;
    
    } else if ( drpin_reg == DR_REG_DX) {

        pin_reg = LEVEL_BASE::REG::REG_DX;
    
    } else if ( drpin_reg == DR_REG_BX) {

        pin_reg = LEVEL_BASE::REG::REG_BX;
    
    } else if ( drpin_reg == DR_REG_SP) {

        pin_reg = LEVEL_BASE::REG::REG_SP;
    
    } else if ( drpin_reg == DR_REG_BP) {

        pin_reg = LEVEL_BASE::REG::REG_BP;
    
    } else if ( drpin_reg == DR_REG_SI) {

        pin_reg = LEVEL_BASE::REG::REG_SI;
    
    } else if ( drpin_reg == DR_REG_DI) {

        pin_reg = LEVEL_BASE::REG::REG_DI;
    
    } else if ( drpin_reg == DR_REG_R8W) {

        pin_reg = LEVEL_BASE::REG::REG_R8W;
    
    } else if ( drpin_reg == DR_REG_R9W) {

        pin_reg = LEVEL_BASE::REG::REG_R9W;
    
    } else if ( drpin_reg == DR_REG_R10W) {

        pin_reg = LEVEL_BASE::REG::REG_R10W;
    
    } else if ( drpin_reg == DR_REG_R11W) {

        pin_reg = LEVEL_BASE::REG::REG_R11W;
    
    } else if ( drpin_reg == DR_REG_R12W) {

        pin_reg = LEVEL_BASE::REG::REG_R12W;
    
    } else if ( drpin_reg == DR_REG_R13W) {

        pin_reg = LEVEL_BASE::REG::REG_R13W;
    
    } else if ( drpin_reg == DR_REG_R14W) {

        pin_reg = LEVEL_BASE::REG::REG_R14W;
    
    } else if ( drpin_reg == DR_REG_R15W) {

        pin_reg = LEVEL_BASE::REG::REG_R15W;
    
    } else if ( drpin_reg == DR_REG_AL) {

        pin_reg = LEVEL_BASE::REG::REG_AL;
    
    } else if ( drpin_reg == DR_REG_CL) {

        pin_reg = LEVEL_BASE::REG::REG_CL;
    
    } else if ( drpin_reg == DR_REG_DL) {

        pin_reg = LEVEL_BASE::REG::REG_DL;
    
    } else if ( drpin_reg == DR_REG_BL) {

        pin_reg = LEVEL_BASE::REG::REG_BL;
    
    } else if ( drpin_reg == DR_REG_AH) {

        pin_reg = LEVEL_BASE::REG::REG_AH;
    
    } else if ( drpin_reg == DR_REG_CH) {

        pin_reg = LEVEL_BASE::REG::REG_CH;
    
    } else if ( drpin_reg == DR_REG_DH) {

        pin_reg = LEVEL_BASE::REG::REG_DH;
    
    } else if ( drpin_reg == DR_REG_BH) {

        pin_reg = LEVEL_BASE::REG::REG_BH;
    
    } else if ( drpin_reg == DR_REG_SPL) {

        pin_reg = LEVEL_BASE::REG::REG_SPL;
    
    } else if ( drpin_reg == DR_REG_BPL) {

        pin_reg = LEVEL_BASE::REG::REG_BPL;
    
    } else if ( drpin_reg == DR_REG_SIL) {

        pin_reg = LEVEL_BASE::REG::REG_SIL;
    
    } else if ( drpin_reg == DR_REG_DIL) {

        pin_reg = LEVEL_BASE::REG::REG_DIL;
    
    } else if ( drpin_reg == DR_REG_MM0) {

        pin_reg = LEVEL_BASE::REG::REG_MM0;
    
    } else if ( drpin_reg == DR_REG_MM1) {

        pin_reg = LEVEL_BASE::REG::REG_MM1;
    
    } else if ( drpin_reg == DR_REG_MM2) {

        pin_reg = LEVEL_BASE::REG::REG_MM2;
    
    } else if ( drpin_reg == DR_REG_MM3) {

        pin_reg = LEVEL_BASE::REG::REG_MM3;
    
    } else if ( drpin_reg == DR_REG_MM4) {

        pin_reg = LEVEL_BASE::REG::REG_MM4;
    
    } else if ( drpin_reg == DR_REG_MM5) {

        pin_reg = LEVEL_BASE::REG::REG_MM5;
    
    } else if ( drpin_reg == DR_REG_MM6) {

        pin_reg = LEVEL_BASE::REG::REG_MM6;
    
    } else if ( drpin_reg == DR_REG_MM7) {

        pin_reg = LEVEL_BASE::REG::REG_MM7;
    
    } else if ( drpin_reg == DR_REG_XMM0) {

        pin_reg = LEVEL_BASE::REG::REG_XMM0;
    
    } else if ( drpin_reg == DR_REG_XMM1) {

        pin_reg = LEVEL_BASE::REG::REG_XMM1;
    
    } else if ( drpin_reg == DR_REG_XMM2) {

        pin_reg = LEVEL_BASE::REG::REG_XMM2;
    
    } else if ( drpin_reg == DR_REG_XMM3) {

        pin_reg = LEVEL_BASE::REG::REG_XMM3;
    
    } else if ( drpin_reg == DR_REG_XMM4) {

        pin_reg = LEVEL_BASE::REG::REG_XMM4;
    
    } else if ( drpin_reg == DR_REG_XMM5) {

        pin_reg = LEVEL_BASE::REG::REG_XMM5;
    
    } else if ( drpin_reg == DR_REG_XMM6) {

        pin_reg = LEVEL_BASE::REG::REG_XMM6;
    
    } else if ( drpin_reg == DR_REG_XMM7) {

        pin_reg = LEVEL_BASE::REG::REG_XMM7;
    
    } else if ( drpin_reg == DR_REG_XMM8) {

        pin_reg = LEVEL_BASE::REG::REG_XMM8;
    
    } else if ( drpin_reg == DR_REG_XMM9) {

        pin_reg = LEVEL_BASE::REG::REG_XMM9;
    
    } else if ( drpin_reg == DR_REG_XMM10) {

        pin_reg = LEVEL_BASE::REG::REG_XMM10;
    
    } else if ( drpin_reg == DR_REG_XMM11) {

        pin_reg = LEVEL_BASE::REG::REG_XMM11;
    
    } else if ( drpin_reg == DR_REG_XMM12) {

        pin_reg = LEVEL_BASE::REG::REG_XMM12;
    
    } else if ( drpin_reg == DR_REG_XMM13) {

        pin_reg = LEVEL_BASE::REG::REG_XMM13;
    
    } else if ( drpin_reg == DR_REG_XMM14) {

        pin_reg = LEVEL_BASE::REG::REG_XMM14;
    
    } else if ( drpin_reg == DR_REG_XMM15) {

        pin_reg = LEVEL_BASE::REG::REG_XMM15;
    
    } else if ( drpin_reg == DR_REG_ST0) {

        pin_reg = LEVEL_BASE::REG::REG_ST0;
    
    } else if ( drpin_reg == DR_REG_ST1) {

        pin_reg = LEVEL_BASE::REG::REG_ST1;
    
    } else if ( drpin_reg == DR_REG_ST2) {

        pin_reg = LEVEL_BASE::REG::REG_ST2;
    
    } else if ( drpin_reg == DR_REG_ST3) {

        pin_reg = LEVEL_BASE::REG::REG_ST3;
    
    } else if ( drpin_reg == DR_REG_ST4) {

        pin_reg = LEVEL_BASE::REG::REG_ST4;
    
    } else if ( drpin_reg == DR_REG_ST5) {

        pin_reg = LEVEL_BASE::REG::REG_ST5;
    
    } else if ( drpin_reg == DR_REG_ST6) {

        pin_reg = LEVEL_BASE::REG::REG_ST6;
    
    } else if ( drpin_reg == DR_REG_ST7) {

        pin_reg = LEVEL_BASE::REG::REG_ST7;
    
    } else if ( drpin_reg == DR_REG_DR0) {

        pin_reg = LEVEL_BASE::REG::REG_DR0;
    
    } else if ( drpin_reg == DR_REG_DR1) {

        pin_reg = LEVEL_BASE::REG::REG_DR1;
    
    } else if ( drpin_reg == DR_REG_DR2) {

        pin_reg = LEVEL_BASE::REG::REG_DR2;
    
    } else if ( drpin_reg == DR_REG_DR3) {

        pin_reg = LEVEL_BASE::REG::REG_DR3;
    
    } else if ( drpin_reg == DR_REG_DR4) {

        pin_reg = LEVEL_BASE::REG::REG_DR4;
    
    } else if ( drpin_reg == DR_REG_DR5) {

        pin_reg = LEVEL_BASE::REG::REG_DR5;
    
    } else if ( drpin_reg == DR_REG_DR6) {

        pin_reg = LEVEL_BASE::REG::REG_DR6;
    
    } else if ( drpin_reg == DR_REG_DR7) {

        pin_reg = LEVEL_BASE::REG::REG_DR7;
    
    } else if ( drpin_reg == DR_REG_CR0) {

        pin_reg = LEVEL_BASE::REG::REG_CR0;
    
    } else if ( drpin_reg == DR_REG_CR1) {

        pin_reg = LEVEL_BASE::REG::REG_CR1;
    
    } else if ( drpin_reg == DR_REG_CR2) {

        pin_reg = LEVEL_BASE::REG::REG_CR2;
    
    } else if ( drpin_reg == DR_REG_CR3) {

        pin_reg = LEVEL_BASE::REG::REG_CR3;
    
    } else if ( drpin_reg == DR_REG_CR4) {

        pin_reg = LEVEL_BASE::REG::REG_CR4;
    
    } else if ( drpin_reg == DR_REG_INVALID) {

        pin_reg = LEVEL_BASE::REG::REG_INVALID_;
    
    } else if ( drpin_reg == DR_REG_YMM0) {

        pin_reg = LEVEL_BASE::REG::REG_YMM0;
    
    } else if ( drpin_reg == DR_REG_YMM1) {

        pin_reg = LEVEL_BASE::REG::REG_YMM1;
    
    } else if ( drpin_reg == DR_REG_YMM2) {

        pin_reg = LEVEL_BASE::REG::REG_YMM2;
    
    } else if ( drpin_reg == DR_REG_YMM3) {

        pin_reg = LEVEL_BASE::REG::REG_YMM3;
    
    } else if ( drpin_reg == DR_REG_YMM4) {

        pin_reg = LEVEL_BASE::REG::REG_YMM4;
    
    } else if ( drpin_reg == DR_REG_YMM5) {

        pin_reg = LEVEL_BASE::REG::REG_YMM5;
    
    } else if ( drpin_reg == DR_REG_YMM6) {

        pin_reg = LEVEL_BASE::REG::REG_YMM6;
    
    } else if ( drpin_reg == DR_REG_YMM7) {

        pin_reg = LEVEL_BASE::REG::REG_YMM7;
    
    } else if ( drpin_reg == DR_REG_YMM8) {

        pin_reg = LEVEL_BASE::REG::REG_YMM8;
    
    } else if ( drpin_reg == DR_REG_YMM9) {

        pin_reg = LEVEL_BASE::REG::REG_YMM9;
    
    } else if ( drpin_reg == DR_REG_YMM10) {

        pin_reg = LEVEL_BASE::REG::REG_YMM10;
    
    } else if ( drpin_reg == DR_REG_YMM11) {

        pin_reg = LEVEL_BASE::REG::REG_YMM11;
    
    } else if ( drpin_reg == DR_REG_YMM12) {

        pin_reg = LEVEL_BASE::REG::REG_YMM12;
    
    } else if ( drpin_reg == DR_REG_YMM13) {

        pin_reg = LEVEL_BASE::REG::REG_YMM13;
    
    } else if ( drpin_reg == DR_REG_YMM14) {

        pin_reg = LEVEL_BASE::REG::REG_YMM14;
    
    } else if ( drpin_reg == DR_REG_YMM15) {

        pin_reg = LEVEL_BASE::REG::REG_YMM15;
    }

    return pin_reg;

}

struct drpin_cbr_fn_pack {
    instrlist_t *ilist; 
    instr_t *where;
    void *callee;
    std::vector<UINT64>* iarg_vector;
};


// void drpin_insert_clean_call_trampoline(void *drcontext, dr_mcontext_t* mcontext, instrlist_t *ilist, instr_t *where, void *callee,  std::vector<UINT64>* iarg_vector){
void drpin_insert_clean_call_trampoline(instrlist_t *ilist, instr_t *where, void *callee,  std::vector<UINT64>* iarg_vector, bool branch_taken,  app_pc branch_target, app_pc branch_fallthrough){

    void* drcontext = dr_get_current_drcontext();
    dr_mcontext_t mcontext = {sizeof(mcontext), DR_MC_ALL};
    dr_get_mcontext(drcontext, &mcontext);


    std::vector<UINT64> func_parameters;
    // this will be called at application run time
    for(int i = 0; i < iarg_vector->size(); i++){
        IARG_TYPE arg = (IARG_TYPE) (*iarg_vector)[i];

        if (arg == IARG_ADDRINT) {
            // next value will be an addrint variable
            i++;
            UINT64 next_arg = (*iarg_vector)[i];
            func_parameters.push_back(next_arg);

            // ADDRINT operand = va_arg( listPointer, ADDRINT );
            // call_operands.push_back(OPND_CREATE_UINT64(operand));

        } else if (arg == IARG_UINT32) {
            // next value will be an UINT32 variable
            i++;
            UINT64 next_arg = (*iarg_vector)[i];
            func_parameters.push_back(next_arg);

        } else if (arg == IARG_INST_PTR) {

            UINT64 ins_address = (UINT64)instr_get_app_pc(where);
            func_parameters.push_back(ins_address);

        } else if (arg == IARG_FAST_ANALYSIS_CALL) {
            // does nothing because we currently do not have an optimazation to do

        } else if (arg == IARG_PTR) {
            // next value will be an UINT32 variable
            i++;
            UINT64 next_arg = (*iarg_vector)[i];
            func_parameters.push_back(next_arg);

        } else if (arg == IARG_THREAD_ID) {
            // next value will be an UINT32 variable
            thread_id_t thread_id = dr_get_thread_id(drcontext);
            func_parameters.push_back(thread_id);

        } else if (arg == IARG_MEMORYREAD_EA) {
            if (!instr_reads_memory(where)){
                std::cout << "This instruction does not reads memory " << std::endl << std::flush;
                // std::cout << std::string(buffer)  << " " << std::endl << std::flush;
                exit(1);
            }
            bool found = false;
            app_pc memory_address = (app_pc)123456;
            for(int i = 0; i < instr_num_srcs(where); i++){

                opnd_t operand = instr_get_src( where, i);
                if (opnd_is_memory_reference(operand)){
                    found = true;
                    memory_address = opnd_compute_address(operand, &mcontext);
                    break;
                }

            }

            func_parameters.push_back((UINT64) memory_address);

        } else if (arg == IARG_MEMORYREAD2_EA) {
            if (!instr_reads_memory(where)){
                std::cout << "This instruction does not reads memory " << std::endl << std::flush;
                // std::cout << std::string(buffer)  << " " << std::endl << std::flush;
                exit(1);
            }
            bool found = false;
            bool found2 = false;
            //Dummy initial value. its easier to debug if the initial value is known
            app_pc memory_address = (app_pc)123456;
            for(int i = 0; i < instr_num_srcs(where); i++){

                opnd_t operand = instr_get_src( where, i);
                if (opnd_is_memory_reference(operand)){
                    if(found == false){
                        // found the first
                        found = true;
                    } else {
                        found2 = true;
                        memory_address = opnd_compute_address(operand, &mcontext);
                        break;
                    }

                }

            }

            func_parameters.push_back((UINT64) memory_address);

        } else if (arg == IARG_BRANCH_TAKEN) {
//          
            func_parameters.push_back((UINT64) branch_taken);

        } else if (arg == IARG_BRANCH_TARGET_ADDR) {

            func_parameters.push_back((UINT64) branch_target);

        } else if (arg == IARG_FALLTHROUGH_ADDR) {

            func_parameters.push_back((UINT64) branch_fallthrough);

        } else if (arg == IARG_EXECUTING) {

            dr_pred_trigger_t will_execute_pred =  instr_predicate_triggered(where, &mcontext);
            bool will_execute = (will_execute_pred != DR_PRED_TRIGGER_MISMATCH);
            func_parameters.push_back((UINT64) will_execute);

        } else if (arg == IARG_MEMORYWRITE_EA) {
            if (!instr_writes_memory(where)){
                std::cout << "This instruction does not writes memory " << std::endl << std::flush;
                exit(1);
            }
            bool found = false;
            app_pc memory_address = (app_pc)123456;
            for(int i = 0; i < instr_num_dsts(where); i++){

                opnd_t operand = instr_get_dst( where, i);
                if (opnd_is_memory_reference(operand)){
                    found = true;
                    memory_address = opnd_compute_address(operand, &mcontext);
                    break;
                }

            }

            func_parameters.push_back((UINT64) memory_address);

        } else if (arg == IARG_REG_VALUE) {
            // next value will be an UINT32 variable
            i++;
            UINT64 pin_reg_id_raw = (*iarg_vector)[i];
            REG pin_reg = (REG)pin_reg_id_raw;
            reg_id_t drpin_reg = convert_pin_reg_to_drpin_reg(pin_reg);
            reg_t reg_value = reg_get_value(drpin_reg, &mcontext);
            func_parameters.push_back((UINT64)reg_value);

        } else if (arg == IARG_REG_REFERENCE) {
            i++;
            // UINT64 pin_reg_id_raw = (*iarg_vector)[i];
            // REG pin_reg = (REG)pin_reg_id_raw;
            // reg_id_t drpin_reg = convert_pin_reg_to_drpin_reg(pin_reg);
            // reg_t reg_value = reg_get_value(drpin_reg, &mcontext);
            UINT64* fakeregister = new UINT64[1];
            func_parameters.push_back((UINT64)fakeregister);


        } else if (arg == IARG_LAST) {
            // is the last one 
            // break;

        } else {
            std::cout << "DrPin is not prepared yet for handling IARG_TYPE of the type: " << arg << std::endl << std::flush;
            exit(1);
        }
    }

    if(func_parameters.size() > 40){
        std::cout << "DrPin cannot place clean calls with more than 40 arguments" << std::endl << std::flush;
        exit(1);
    }

    if(func_parameters.size() == 0){
        ((void (*)(void)) callee)();
    }
    else if(func_parameters.size() == 1){
        ( (void(*)(UINT64))callee )(func_parameters[0]);
    }
    else if(func_parameters.size() == 2){
        ( (void(*)(UINT64, UINT64))callee )(func_parameters[0], func_parameters[1]);
    }
    else if(func_parameters.size() == 3){
        ( (void(*)(UINT64, UINT64, UINT64))callee )(func_parameters[0], func_parameters[1], func_parameters[2]);
    }
    else if(func_parameters.size() == 4){
        ( (void(*)(UINT64, UINT64, UINT64, UINT64))callee )(func_parameters[0], func_parameters[1], func_parameters[2], func_parameters[3]);
    }
    else if(func_parameters.size() == 5){
        ( (void(*)(UINT64, UINT64, UINT64, UINT64, UINT64))callee )(func_parameters[0], func_parameters[1], func_parameters[2], func_parameters[3], func_parameters[4]);
    }
    else if(func_parameters.size() == 6){
        ( (void(*)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64))callee )(func_parameters[0], func_parameters[1], func_parameters[2], func_parameters[3], func_parameters[4], func_parameters[5]);
    }
    else if(func_parameters.size() == 7){
        ( (void(*)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64))callee )(func_parameters[0], func_parameters[1], func_parameters[2], func_parameters[3], func_parameters[4], func_parameters[5], func_parameters[6]);
    }
    else if(func_parameters.size() == 8){
        ( (void(*)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64))callee )(func_parameters[0], func_parameters[1], func_parameters[2], func_parameters[3], func_parameters[4], func_parameters[5], func_parameters[6], func_parameters[7]);
    }
    else if(func_parameters.size() == 9){
        ( (void(*)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64))callee )(func_parameters[0], func_parameters[1], func_parameters[2], func_parameters[3], func_parameters[4], func_parameters[5], func_parameters[6], func_parameters[7], func_parameters[8]);
    }
    else if(func_parameters.size() == 10){
        ( (void(*)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64))callee )(func_parameters[0], func_parameters[1], func_parameters[2], func_parameters[3], func_parameters[4], func_parameters[5], func_parameters[6], func_parameters[7], func_parameters[8], func_parameters[9]);
    }
    else if(func_parameters.size() == 11){
        ( (void(*)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64))callee )(func_parameters[0], func_parameters[1], func_parameters[2], func_parameters[3], func_parameters[4], func_parameters[5], func_parameters[6], func_parameters[7], func_parameters[8], func_parameters[9], func_parameters[10]);
    }
    else if(func_parameters.size() == 12){
        ( (void(*)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64))callee )(func_parameters[0], func_parameters[1], func_parameters[2], func_parameters[3], func_parameters[4], func_parameters[5], func_parameters[6], func_parameters[7], func_parameters[8], func_parameters[9], func_parameters[10], func_parameters[11]);
    }
    else if(func_parameters.size() == 13){
        ( (void(*)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64))callee )(func_parameters[0], func_parameters[1], func_parameters[2], func_parameters[3], func_parameters[4], func_parameters[5], func_parameters[6], func_parameters[7], func_parameters[8], func_parameters[9], func_parameters[10], func_parameters[11], func_parameters[12]);
    }
    else if(func_parameters.size() == 14){
        ( (void(*)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64))callee )(func_parameters[0], func_parameters[1], func_parameters[2], func_parameters[3], func_parameters[4], func_parameters[5], func_parameters[6], func_parameters[7], func_parameters[8], func_parameters[9], func_parameters[10], func_parameters[11], func_parameters[12], func_parameters[13]);
    }
    else if(func_parameters.size() == 15){
        ( (void(*)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64))callee )(func_parameters[0], func_parameters[1], func_parameters[2], func_parameters[3], func_parameters[4], func_parameters[5], func_parameters[6], func_parameters[7], func_parameters[8], func_parameters[9], func_parameters[10], func_parameters[11], func_parameters[12], func_parameters[13], func_parameters[14]);
    }
    else if(func_parameters.size() == 16){
        ( (void(*)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64))callee )(func_parameters[0], func_parameters[1], func_parameters[2], func_parameters[3], func_parameters[4], func_parameters[5], func_parameters[6], func_parameters[7], func_parameters[8], func_parameters[9], func_parameters[10], func_parameters[11], func_parameters[12], func_parameters[13], func_parameters[14], func_parameters[15]);
    }
    else if(func_parameters.size() == 17){
        ( (void(*)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64))callee )(func_parameters[0], func_parameters[1], func_parameters[2], func_parameters[3], func_parameters[4], func_parameters[5], func_parameters[6], func_parameters[7], func_parameters[8], func_parameters[9], func_parameters[10], func_parameters[11], func_parameters[12], func_parameters[13], func_parameters[14], func_parameters[15], func_parameters[16]);
    }
    else if(func_parameters.size() == 18){
        ( (void(*)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64))callee )(func_parameters[0], func_parameters[1], func_parameters[2], func_parameters[3], func_parameters[4], func_parameters[5], func_parameters[6], func_parameters[7], func_parameters[8], func_parameters[9], func_parameters[10], func_parameters[11], func_parameters[12], func_parameters[13], func_parameters[14], func_parameters[15], func_parameters[16], func_parameters[17]);
    }
    else if(func_parameters.size() == 19){
        ( (void(*)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64))callee )(func_parameters[0], func_parameters[1], func_parameters[2], func_parameters[3], func_parameters[4], func_parameters[5], func_parameters[6], func_parameters[7], func_parameters[8], func_parameters[9], func_parameters[10], func_parameters[11], func_parameters[12], func_parameters[13], func_parameters[14], func_parameters[15], func_parameters[16], func_parameters[17], func_parameters[18]);
    }
    else if(func_parameters.size() == 20){
        ( (void(*)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64))callee )(func_parameters[0], func_parameters[1], func_parameters[2], func_parameters[3], func_parameters[4], func_parameters[5], func_parameters[6], func_parameters[7], func_parameters[8], func_parameters[9], func_parameters[10], func_parameters[11], func_parameters[12], func_parameters[13], func_parameters[14], func_parameters[15], func_parameters[16], func_parameters[17], func_parameters[18], func_parameters[19]);
    }
    else if(func_parameters.size() == 21){
        ( (void(*)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64))callee )(func_parameters[0], func_parameters[1], func_parameters[2], func_parameters[3], func_parameters[4], func_parameters[5], func_parameters[6], func_parameters[7], func_parameters[8], func_parameters[9], func_parameters[10], func_parameters[11], func_parameters[12], func_parameters[13], func_parameters[14], func_parameters[15], func_parameters[16], func_parameters[17], func_parameters[18], func_parameters[19], func_parameters[20]);
    }
    else if(func_parameters.size() == 22){
        ( (void(*)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64))callee )(func_parameters[0], func_parameters[1], func_parameters[2], func_parameters[3], func_parameters[4], func_parameters[5], func_parameters[6], func_parameters[7], func_parameters[8], func_parameters[9], func_parameters[10], func_parameters[11], func_parameters[12], func_parameters[13], func_parameters[14], func_parameters[15], func_parameters[16], func_parameters[17], func_parameters[18], func_parameters[19], func_parameters[20], func_parameters[21]);
    }
    else if(func_parameters.size() == 23){
        ( (void(*)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64))callee )(func_parameters[0], func_parameters[1], func_parameters[2], func_parameters[3], func_parameters[4], func_parameters[5], func_parameters[6], func_parameters[7], func_parameters[8], func_parameters[9], func_parameters[10], func_parameters[11], func_parameters[12], func_parameters[13], func_parameters[14], func_parameters[15], func_parameters[16], func_parameters[17], func_parameters[18], func_parameters[19], func_parameters[20], func_parameters[21], func_parameters[22]);
    }
    else if(func_parameters.size() == 24){
        ( (void(*)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64))callee )(func_parameters[0], func_parameters[1], func_parameters[2], func_parameters[3], func_parameters[4], func_parameters[5], func_parameters[6], func_parameters[7], func_parameters[8], func_parameters[9], func_parameters[10], func_parameters[11], func_parameters[12], func_parameters[13], func_parameters[14], func_parameters[15], func_parameters[16], func_parameters[17], func_parameters[18], func_parameters[19], func_parameters[20], func_parameters[21], func_parameters[22], func_parameters[23]);
    }
    else if(func_parameters.size() == 25){
        ( (void(*)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64))callee )(func_parameters[0], func_parameters[1], func_parameters[2], func_parameters[3], func_parameters[4], func_parameters[5], func_parameters[6], func_parameters[7], func_parameters[8], func_parameters[9], func_parameters[10], func_parameters[11], func_parameters[12], func_parameters[13], func_parameters[14], func_parameters[15], func_parameters[16], func_parameters[17], func_parameters[18], func_parameters[19], func_parameters[20], func_parameters[21], func_parameters[22], func_parameters[23], func_parameters[24]);
    }
    else if(func_parameters.size() == 26){
        ( (void(*)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64))callee )(func_parameters[0], func_parameters[1], func_parameters[2], func_parameters[3], func_parameters[4], func_parameters[5], func_parameters[6], func_parameters[7], func_parameters[8], func_parameters[9], func_parameters[10], func_parameters[11], func_parameters[12], func_parameters[13], func_parameters[14], func_parameters[15], func_parameters[16], func_parameters[17], func_parameters[18], func_parameters[19], func_parameters[20], func_parameters[21], func_parameters[22], func_parameters[23], func_parameters[24], func_parameters[25]);
    }
    else if(func_parameters.size() == 27){
        ( (void(*)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64))callee )(func_parameters[0], func_parameters[1], func_parameters[2], func_parameters[3], func_parameters[4], func_parameters[5], func_parameters[6], func_parameters[7], func_parameters[8], func_parameters[9], func_parameters[10], func_parameters[11], func_parameters[12], func_parameters[13], func_parameters[14], func_parameters[15], func_parameters[16], func_parameters[17], func_parameters[18], func_parameters[19], func_parameters[20], func_parameters[21], func_parameters[22], func_parameters[23], func_parameters[24], func_parameters[25], func_parameters[26]);
    }
    else if(func_parameters.size() == 28){
        ( (void(*)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64))callee )(func_parameters[0], func_parameters[1], func_parameters[2], func_parameters[3], func_parameters[4], func_parameters[5], func_parameters[6], func_parameters[7], func_parameters[8], func_parameters[9], func_parameters[10], func_parameters[11], func_parameters[12], func_parameters[13], func_parameters[14], func_parameters[15], func_parameters[16], func_parameters[17], func_parameters[18], func_parameters[19], func_parameters[20], func_parameters[21], func_parameters[22], func_parameters[23], func_parameters[24], func_parameters[25], func_parameters[26], func_parameters[27]);
    }
    else if(func_parameters.size() == 29){
        ( (void(*)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64))callee )(func_parameters[0], func_parameters[1], func_parameters[2], func_parameters[3], func_parameters[4], func_parameters[5], func_parameters[6], func_parameters[7], func_parameters[8], func_parameters[9], func_parameters[10], func_parameters[11], func_parameters[12], func_parameters[13], func_parameters[14], func_parameters[15], func_parameters[16], func_parameters[17], func_parameters[18], func_parameters[19], func_parameters[20], func_parameters[21], func_parameters[22], func_parameters[23], func_parameters[24], func_parameters[25], func_parameters[26], func_parameters[27], func_parameters[28]);
    }
    else if(func_parameters.size() == 30){
        ( (void(*)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64))callee )(func_parameters[0], func_parameters[1], func_parameters[2], func_parameters[3], func_parameters[4], func_parameters[5], func_parameters[6], func_parameters[7], func_parameters[8], func_parameters[9], func_parameters[10], func_parameters[11], func_parameters[12], func_parameters[13], func_parameters[14], func_parameters[15], func_parameters[16], func_parameters[17], func_parameters[18], func_parameters[19], func_parameters[20], func_parameters[21], func_parameters[22], func_parameters[23], func_parameters[24], func_parameters[25], func_parameters[26], func_parameters[27], func_parameters[28], func_parameters[29]);
    }
    else if(func_parameters.size() == 31){
        ( (void(*)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64))callee )(func_parameters[0], func_parameters[1], func_parameters[2], func_parameters[3], func_parameters[4], func_parameters[5], func_parameters[6], func_parameters[7], func_parameters[8], func_parameters[9], func_parameters[10], func_parameters[11], func_parameters[12], func_parameters[13], func_parameters[14], func_parameters[15], func_parameters[16], func_parameters[17], func_parameters[18], func_parameters[19], func_parameters[20], func_parameters[21], func_parameters[22], func_parameters[23], func_parameters[24], func_parameters[25], func_parameters[26], func_parameters[27], func_parameters[28], func_parameters[29], func_parameters[30]);
    }
    else if(func_parameters.size() == 32){
        ( (void(*)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64))callee )(func_parameters[0], func_parameters[1], func_parameters[2], func_parameters[3], func_parameters[4], func_parameters[5], func_parameters[6], func_parameters[7], func_parameters[8], func_parameters[9], func_parameters[10], func_parameters[11], func_parameters[12], func_parameters[13], func_parameters[14], func_parameters[15], func_parameters[16], func_parameters[17], func_parameters[18], func_parameters[19], func_parameters[20], func_parameters[21], func_parameters[22], func_parameters[23], func_parameters[24], func_parameters[25], func_parameters[26], func_parameters[27], func_parameters[28], func_parameters[29], func_parameters[30], func_parameters[31]);
    }
    else if(func_parameters.size() == 33){
        ( (void(*)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64))callee )(func_parameters[0], func_parameters[1], func_parameters[2], func_parameters[3], func_parameters[4], func_parameters[5], func_parameters[6], func_parameters[7], func_parameters[8], func_parameters[9], func_parameters[10], func_parameters[11], func_parameters[12], func_parameters[13], func_parameters[14], func_parameters[15], func_parameters[16], func_parameters[17], func_parameters[18], func_parameters[19], func_parameters[20], func_parameters[21], func_parameters[22], func_parameters[23], func_parameters[24], func_parameters[25], func_parameters[26], func_parameters[27], func_parameters[28], func_parameters[29], func_parameters[30], func_parameters[31], func_parameters[32]);
    }
    else if(func_parameters.size() == 34){
        ( (void(*)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64))callee )(func_parameters[0], func_parameters[1], func_parameters[2], func_parameters[3], func_parameters[4], func_parameters[5], func_parameters[6], func_parameters[7], func_parameters[8], func_parameters[9], func_parameters[10], func_parameters[11], func_parameters[12], func_parameters[13], func_parameters[14], func_parameters[15], func_parameters[16], func_parameters[17], func_parameters[18], func_parameters[19], func_parameters[20], func_parameters[21], func_parameters[22], func_parameters[23], func_parameters[24], func_parameters[25], func_parameters[26], func_parameters[27], func_parameters[28], func_parameters[29], func_parameters[30], func_parameters[31], func_parameters[32], func_parameters[33]);
    }
    else if(func_parameters.size() == 35){
        ( (void(*)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64))callee )(func_parameters[0], func_parameters[1], func_parameters[2], func_parameters[3], func_parameters[4], func_parameters[5], func_parameters[6], func_parameters[7], func_parameters[8], func_parameters[9], func_parameters[10], func_parameters[11], func_parameters[12], func_parameters[13], func_parameters[14], func_parameters[15], func_parameters[16], func_parameters[17], func_parameters[18], func_parameters[19], func_parameters[20], func_parameters[21], func_parameters[22], func_parameters[23], func_parameters[24], func_parameters[25], func_parameters[26], func_parameters[27], func_parameters[28], func_parameters[29], func_parameters[30], func_parameters[31], func_parameters[32], func_parameters[33], func_parameters[34]);
    }
    else if(func_parameters.size() == 36){
        ( (void(*)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64))callee )(func_parameters[0], func_parameters[1], func_parameters[2], func_parameters[3], func_parameters[4], func_parameters[5], func_parameters[6], func_parameters[7], func_parameters[8], func_parameters[9], func_parameters[10], func_parameters[11], func_parameters[12], func_parameters[13], func_parameters[14], func_parameters[15], func_parameters[16], func_parameters[17], func_parameters[18], func_parameters[19], func_parameters[20], func_parameters[21], func_parameters[22], func_parameters[23], func_parameters[24], func_parameters[25], func_parameters[26], func_parameters[27], func_parameters[28], func_parameters[29], func_parameters[30], func_parameters[31], func_parameters[32], func_parameters[33], func_parameters[34], func_parameters[35]);
    }
    else if(func_parameters.size() == 37){
        ( (void(*)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64))callee )(func_parameters[0], func_parameters[1], func_parameters[2], func_parameters[3], func_parameters[4], func_parameters[5], func_parameters[6], func_parameters[7], func_parameters[8], func_parameters[9], func_parameters[10], func_parameters[11], func_parameters[12], func_parameters[13], func_parameters[14], func_parameters[15], func_parameters[16], func_parameters[17], func_parameters[18], func_parameters[19], func_parameters[20], func_parameters[21], func_parameters[22], func_parameters[23], func_parameters[24], func_parameters[25], func_parameters[26], func_parameters[27], func_parameters[28], func_parameters[29], func_parameters[30], func_parameters[31], func_parameters[32], func_parameters[33], func_parameters[34], func_parameters[35], func_parameters[36]);
    }
    else if(func_parameters.size() == 38){
        ( (void(*)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64))callee )(func_parameters[0], func_parameters[1], func_parameters[2], func_parameters[3], func_parameters[4], func_parameters[5], func_parameters[6], func_parameters[7], func_parameters[8], func_parameters[9], func_parameters[10], func_parameters[11], func_parameters[12], func_parameters[13], func_parameters[14], func_parameters[15], func_parameters[16], func_parameters[17], func_parameters[18], func_parameters[19], func_parameters[20], func_parameters[21], func_parameters[22], func_parameters[23], func_parameters[24], func_parameters[25], func_parameters[26], func_parameters[27], func_parameters[28], func_parameters[29], func_parameters[30], func_parameters[31], func_parameters[32], func_parameters[33], func_parameters[34], func_parameters[35], func_parameters[36], func_parameters[37]);
    }
    else if(func_parameters.size() == 39){
        ( (void(*)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64))callee )(func_parameters[0], func_parameters[1], func_parameters[2], func_parameters[3], func_parameters[4], func_parameters[5], func_parameters[6], func_parameters[7], func_parameters[8], func_parameters[9], func_parameters[10], func_parameters[11], func_parameters[12], func_parameters[13], func_parameters[14], func_parameters[15], func_parameters[16], func_parameters[17], func_parameters[18], func_parameters[19], func_parameters[20], func_parameters[21], func_parameters[22], func_parameters[23], func_parameters[24], func_parameters[25], func_parameters[26], func_parameters[27], func_parameters[28], func_parameters[29], func_parameters[30], func_parameters[31], func_parameters[32], func_parameters[33], func_parameters[34], func_parameters[35], func_parameters[36], func_parameters[37], func_parameters[38]);
    }
    else if(func_parameters.size() == 40){
        ( (void(*)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64))callee )(func_parameters[0], func_parameters[1], func_parameters[2], func_parameters[3], func_parameters[4], func_parameters[5], func_parameters[6], func_parameters[7], func_parameters[8], func_parameters[9], func_parameters[10], func_parameters[11], func_parameters[12], func_parameters[13], func_parameters[14], func_parameters[15], func_parameters[16], func_parameters[17], func_parameters[18], func_parameters[19], func_parameters[20], func_parameters[21], func_parameters[22], func_parameters[23], func_parameters[24], func_parameters[25], func_parameters[26], func_parameters[27], func_parameters[28], func_parameters[29], func_parameters[30], func_parameters[31], func_parameters[32], func_parameters[33], func_parameters[34], func_parameters[35], func_parameters[36], func_parameters[37], func_parameters[38], func_parameters[39]);
    }


}

void drpin_cbr_trampoline(app_pc inst_addr, app_pc targ_addr, app_pc fall_addr, int taken, drpin_cbr_fn_pack *cbr_pack_raw){
    bool branch_taken = (taken != 0);
    drpin_insert_clean_call_trampoline(cbr_pack_raw->ilist, cbr_pack_raw->where, cbr_pack_raw->callee, cbr_pack_raw->iarg_vector, branch_taken, targ_addr, fall_addr);
}

bool drpin_iarg_vector_only_static_info(std::vector<UINT64>& iarg_vector){
    bool only_static = true;
    for(int i = 0; i < iarg_vector.size(); i++){

        IARG_TYPE arg = (IARG_TYPE)iarg_vector[i];

        if (arg == IARG_ADDRINT) {
            // next value would be the addrint value;
            i++;

        } else if (arg == IARG_UINT32){

            // next value would be the uint32 value
            i++;

        } else if (arg == IARG_FAST_ANALYSIS_CALL){

            // We currently do not have an optimization to this case, but at least is 
            // not dynamic information

        } else if( arg == IARG_PTR){
            // next value would be the ptr value
            i++;

        } else if (arg == IARG_END){
            // no problem

        } else {
            only_static = false;
            break;
        }

    }
    return only_static;

}

void drpin_insert_clean_call(void *drcontext, instrlist_t *ilist, instr_t *where, void *callee, bool save_fpstate, std::vector<UINT64>& iarg_vector){
    // ___debug_print(10);
    // this will be called at instrumentation time
    // std::cout << "#############################################" << std::endl << std::flush;
    // INS ins;
    // ins.drcontext = drcontext;
    // ins.instr = where;
    // ins.instr_list = ilist;
    // std::cout << "disassemble " << INS_Disassemble(ins) << std::endl << std::flush;
    // for(int i = 0; i < iarg_vector.size(); i++){
    //     std::cout << "IARG_[" << i << "] = " << iarg_vector[i] << std::endl << std::flush;
    // }
    // std::cout << "#############################################" << std::endl << std::flush;
    if(drpin_iarg_vector_only_static_info(iarg_vector)){
        std::vector<opnd_t> operands;
        for(int i = 0; i < iarg_vector.size(); i++){

            IARG_TYPE arg = (IARG_TYPE)iarg_vector[i];

            if (arg == IARG_ADDRINT) {
                i++;
                ADDRINT operand = (ADDRINT)iarg_vector[i];
                operands.push_back(OPND_CREATE_UINT64(operand));

            } else if (arg == IARG_UINT32){

                i++;
                UINT32 operand = (UINT32)iarg_vector[i];
                operands.push_back(OPND_CREATE_UINT32(operand));

            } else if (arg == IARG_FAST_ANALYSIS_CALL){

                // We currently do not have an optimization to this case

            } else if( arg == IARG_PTR){
                i++;
                UINT64 operand = (UINT64)iarg_vector[i];
                operands.push_back(OPND_CREATE_UINT64(operand));

            } else if (arg == IARG_END){
                // no problem

            } else {
                std::cout << "DrPin insert call error. This should not happen. Needs further investigation" << arg << std::endl << std::flush;
                exit(1);
            }
        }


        if(operands.size() > 40) {
            std::cout << "DrPin cannot place clean calls with more than 40 arguments" << std::endl << std::flush;
            exit(1);
        }
        if(operands.size() == 0) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 0);
        } else if (operands.size() == 1) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 1, operands[0] );
        } else if (operands.size() == 2) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 2, operands[0], operands[1] );
        } else if (operands.size() == 3) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 3, operands[0], operands[1], operands[2] );
        } else if (operands.size() == 4) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 4, operands[0], operands[1], operands[2], operands[3] );
        } else if (operands.size() == 5) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 5, operands[0], operands[1], operands[2], operands[3], operands[4] );
        } else if (operands.size() == 6) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 6, operands[0], operands[1], operands[2], operands[3], operands[4], operands[5] );
        } else if (operands.size() == 7) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 7, operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6] );
        } else if (operands.size() == 8) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 8, operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6], operands[7] );
        } else if (operands.size() == 9) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 9, operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6], operands[7], operands[8] );
        } else if (operands.size() == 10) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 10, operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6], operands[7], operands[8], operands[9] );
        } else if (operands.size() == 11) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 11, operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6], operands[7], operands[8], operands[9], operands[10] );
        } else if (operands.size() == 12) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 12, operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6], operands[7], operands[8], operands[9], operands[10], operands[11] );
        } else if (operands.size() == 13) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 13, operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6], operands[7], operands[8], operands[9], operands[10], operands[11], operands[12] );
        } else if (operands.size() == 14) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 14, operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6], operands[7], operands[8], operands[9], operands[10], operands[11], operands[12], operands[13] );
        } else if (operands.size() == 15) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 15, operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6], operands[7], operands[8], operands[9], operands[10], operands[11], operands[12], operands[13], operands[14] );
        } else if (operands.size() == 16) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 16, operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6], operands[7], operands[8], operands[9], operands[10], operands[11], operands[12], operands[13], operands[14], operands[15] );
        } else if (operands.size() == 17) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 17, operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6], operands[7], operands[8], operands[9], operands[10], operands[11], operands[12], operands[13], operands[14], operands[15], operands[16] );
        } else if (operands.size() == 18) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 18, operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6], operands[7], operands[8], operands[9], operands[10], operands[11], operands[12], operands[13], operands[14], operands[15], operands[16], operands[17] );
        } else if (operands.size() == 19) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 19, operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6], operands[7], operands[8], operands[9], operands[10], operands[11], operands[12], operands[13], operands[14], operands[15], operands[16], operands[17], operands[18] );
        } else if (operands.size() == 20) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 20, operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6], operands[7], operands[8], operands[9], operands[10], operands[11], operands[12], operands[13], operands[14], operands[15], operands[16], operands[17], operands[18], operands[19] );
        } else if (operands.size() == 21) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 21, operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6], operands[7], operands[8], operands[9], operands[10], operands[11], operands[12], operands[13], operands[14], operands[15], operands[16], operands[17], operands[18], operands[19], operands[20] );
        } else if (operands.size() == 22) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 22, operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6], operands[7], operands[8], operands[9], operands[10], operands[11], operands[12], operands[13], operands[14], operands[15], operands[16], operands[17], operands[18], operands[19], operands[20], operands[21] );
        } else if (operands.size() == 23) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 23, operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6], operands[7], operands[8], operands[9], operands[10], operands[11], operands[12], operands[13], operands[14], operands[15], operands[16], operands[17], operands[18], operands[19], operands[20], operands[21], operands[22] );
        } else if (operands.size() == 24) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 24, operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6], operands[7], operands[8], operands[9], operands[10], operands[11], operands[12], operands[13], operands[14], operands[15], operands[16], operands[17], operands[18], operands[19], operands[20], operands[21], operands[22], operands[23] );
        } else if (operands.size() == 25) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 25, operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6], operands[7], operands[8], operands[9], operands[10], operands[11], operands[12], operands[13], operands[14], operands[15], operands[16], operands[17], operands[18], operands[19], operands[20], operands[21], operands[22], operands[23], operands[24] );
        } else if (operands.size() == 26) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 26, operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6], operands[7], operands[8], operands[9], operands[10], operands[11], operands[12], operands[13], operands[14], operands[15], operands[16], operands[17], operands[18], operands[19], operands[20], operands[21], operands[22], operands[23], operands[24], operands[25] );
        } else if (operands.size() == 27) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 27, operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6], operands[7], operands[8], operands[9], operands[10], operands[11], operands[12], operands[13], operands[14], operands[15], operands[16], operands[17], operands[18], operands[19], operands[20], operands[21], operands[22], operands[23], operands[24], operands[25], operands[26] );
        } else if (operands.size() == 28) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 28, operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6], operands[7], operands[8], operands[9], operands[10], operands[11], operands[12], operands[13], operands[14], operands[15], operands[16], operands[17], operands[18], operands[19], operands[20], operands[21], operands[22], operands[23], operands[24], operands[25], operands[26], operands[27] );
        } else if (operands.size() == 29) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 29, operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6], operands[7], operands[8], operands[9], operands[10], operands[11], operands[12], operands[13], operands[14], operands[15], operands[16], operands[17], operands[18], operands[19], operands[20], operands[21], operands[22], operands[23], operands[24], operands[25], operands[26], operands[27], operands[28] );
        } else if (operands.size() == 30) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 30, operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6], operands[7], operands[8], operands[9], operands[10], operands[11], operands[12], operands[13], operands[14], operands[15], operands[16], operands[17], operands[18], operands[19], operands[20], operands[21], operands[22], operands[23], operands[24], operands[25], operands[26], operands[27], operands[28], operands[29] );
        } else if (operands.size() == 31) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 31, operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6], operands[7], operands[8], operands[9], operands[10], operands[11], operands[12], operands[13], operands[14], operands[15], operands[16], operands[17], operands[18], operands[19], operands[20], operands[21], operands[22], operands[23], operands[24], operands[25], operands[26], operands[27], operands[28], operands[29], operands[30] );
        } else if (operands.size() == 32) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 32, operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6], operands[7], operands[8], operands[9], operands[10], operands[11], operands[12], operands[13], operands[14], operands[15], operands[16], operands[17], operands[18], operands[19], operands[20], operands[21], operands[22], operands[23], operands[24], operands[25], operands[26], operands[27], operands[28], operands[29], operands[30], operands[31] );
        } else if (operands.size() == 33) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 33, operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6], operands[7], operands[8], operands[9], operands[10], operands[11], operands[12], operands[13], operands[14], operands[15], operands[16], operands[17], operands[18], operands[19], operands[20], operands[21], operands[22], operands[23], operands[24], operands[25], operands[26], operands[27], operands[28], operands[29], operands[30], operands[31], operands[32] );
        } else if (operands.size() == 34) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 34, operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6], operands[7], operands[8], operands[9], operands[10], operands[11], operands[12], operands[13], operands[14], operands[15], operands[16], operands[17], operands[18], operands[19], operands[20], operands[21], operands[22], operands[23], operands[24], operands[25], operands[26], operands[27], operands[28], operands[29], operands[30], operands[31], operands[32], operands[33] );
        } else if (operands.size() == 35) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 35, operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6], operands[7], operands[8], operands[9], operands[10], operands[11], operands[12], operands[13], operands[14], operands[15], operands[16], operands[17], operands[18], operands[19], operands[20], operands[21], operands[22], operands[23], operands[24], operands[25], operands[26], operands[27], operands[28], operands[29], operands[30], operands[31], operands[32], operands[33], operands[34] );
        } else if (operands.size() == 36) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 36, operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6], operands[7], operands[8], operands[9], operands[10], operands[11], operands[12], operands[13], operands[14], operands[15], operands[16], operands[17], operands[18], operands[19], operands[20], operands[21], operands[22], operands[23], operands[24], operands[25], operands[26], operands[27], operands[28], operands[29], operands[30], operands[31], operands[32], operands[33], operands[34], operands[35] );
        } else if (operands.size() == 37) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 37, operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6], operands[7], operands[8], operands[9], operands[10], operands[11], operands[12], operands[13], operands[14], operands[15], operands[16], operands[17], operands[18], operands[19], operands[20], operands[21], operands[22], operands[23], operands[24], operands[25], operands[26], operands[27], operands[28], operands[29], operands[30], operands[31], operands[32], operands[33], operands[34], operands[35], operands[36] );
        } else if (operands.size() == 38) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 38, operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6], operands[7], operands[8], operands[9], operands[10], operands[11], operands[12], operands[13], operands[14], operands[15], operands[16], operands[17], operands[18], operands[19], operands[20], operands[21], operands[22], operands[23], operands[24], operands[25], operands[26], operands[27], operands[28], operands[29], operands[30], operands[31], operands[32], operands[33], operands[34], operands[35], operands[36], operands[37] );
        } else if (operands.size() == 39) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 39, operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6], operands[7], operands[8], operands[9], operands[10], operands[11], operands[12], operands[13], operands[14], operands[15], operands[16], operands[17], operands[18], operands[19], operands[20], operands[21], operands[22], operands[23], operands[24], operands[25], operands[26], operands[27], operands[28], operands[29], operands[30], operands[31], operands[32], operands[33], operands[34], operands[35], operands[36], operands[37], operands[38] );
        } else if (operands.size() == 40) {
            dr_insert_clean_call(drcontext, ilist, where, callee, save_fpstate, 40, operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6], operands[7], operands[8], operands[9], operands[10], operands[11], operands[12], operands[13], operands[14], operands[15], operands[16], operands[17], operands[18], operands[19], operands[20], operands[21], operands[22], operands[23], operands[24], operands[25], operands[26], operands[27], operands[28], operands[29], operands[30], operands[31], operands[32], operands[33], operands[34], operands[35], operands[36], operands[37], operands[38], operands[39] );
        }




        return;
    }


    // if execution got here it is because callee needs information only available at runtime. Its dispatch is going to be made using a trampoline function that will
    // provide the necessary data to it
    // this vector will be needed every time this call is executed during runtime. Because of this we will never free it.
    std::vector<UINT64>* iarg_vector_ptr = new std::vector<UINT64>(); // new std::vector<UINT64>(iarg_vector);
    for (int i = 0; i < iarg_vector.size(); i++){
        iarg_vector_ptr->push_back(iarg_vector[i]);
    }


    instr_t* newWhere = instr_clone(drcontext, where);

    // dr_insert_clean_call(drcontext, ilist, where, (void*)drpin_insert_clean_call_trampoline, save_fpstate, 5, OPND_CREATE_INTPTR(drcontext), OPND_CREATE_INTPTR(ilist), OPND_CREATE_INTPTR(where), OPND_CREATE_INTPTR(callee), OPND_CREATE_INTPTR(iarg_vector_ptr) );
    if(instr_is_cbr(where)){

        // is a conditional branch instruction
        // this struct will be needed every time this call is executed during runtime. Because of this we will never free it.
        drpin_cbr_fn_pack* cbr_pack = new drpin_cbr_fn_pack();
        cbr_pack->ilist = ilist;
        cbr_pack->where = newWhere;
        cbr_pack->callee = callee;
        cbr_pack->iarg_vector = iarg_vector_ptr;

        dr_insert_cbr_instrumentation_ex(drcontext, ilist, where, (void *)drpin_cbr_trampoline, OPND_CREATE_INTPTR(cbr_pack));

    // } else if (instr_is_return(where)){
    //     app_pc target = 0; 
    //     // instr__memory

    //     /* the retaddr operand is always the final source for all OP_ret* instrs */
    //     dr_mcontext_t mcontext = {sizeof(mcontext), DR_MC_ALL};
    //     dr_get_mcontext(drcontext, &mcontext);

    //     opnd_t retaddr = instr_get_src(where, instr_num_srcs(where) - 1);
    //     target = opnd_compute_address(retaddr, &mcontext);

    //     dr_insert_clean_call(drcontext, ilist, where, (void*)drpin_insert_clean_call_trampoline, save_fpstate, 7, OPND_CREATE_INTPTR(ilist), OPND_CREATE_INTPTR(newWhere), OPND_CREATE_INTPTR(callee), OPND_CREATE_INTPTR(iarg_vector_ptr), OPND_CREATE_INT64(1), OPND_CREATE_INTPTR(target), OPND_CREATE_INTPTR(0) );
        
    } else if (instr_is_cti(where)) {
        // is a branch instruction, but not conditional
        app_pc target;
        if (opnd_is_near_pc(instr_get_target(where))){
            target = opnd_get_pc(instr_get_target(where));
        } else {
            target = 0;
        }
        dr_insert_clean_call(drcontext, ilist, where, (void*)drpin_insert_clean_call_trampoline, save_fpstate, 7, OPND_CREATE_INTPTR(ilist), OPND_CREATE_INTPTR(newWhere), OPND_CREATE_INTPTR(callee), OPND_CREATE_INTPTR(iarg_vector_ptr), OPND_CREATE_INT64(1), OPND_CREATE_INTPTR(target), OPND_CREATE_INTPTR(0) );


    } else {
        // is not a branch instruction
        dr_insert_clean_call(drcontext, ilist, where, (void*)drpin_insert_clean_call_trampoline, save_fpstate, 7, OPND_CREATE_INTPTR(ilist), OPND_CREATE_INTPTR(newWhere), OPND_CREATE_INTPTR(callee), OPND_CREATE_INTPTR(iarg_vector_ptr), OPND_CREATE_INT64(0), OPND_CREATE_INTPTR(0), OPND_CREATE_INTPTR(0) );
    }
}


// ------------------------------------------------------------------
// External flag (from drpin.cpp) that indicates if the drpin is running in debug mode
extern bool drpin_debug_flag;
extern string drpin_pintool_op_flag;

// Prints msg only if the drpin is running in debug mode
static void drpin_debug_print(const std::string& msg){
  if(drpin_debug_flag){
    printf("\n===============[DRPIN DEBUG]=================\n");
    printf("%s\n", msg.c_str());
    printf("=============================================\n\n");
  }

}

// Stores exit functions callbacks that should be called when drpin is about to finish, i.e. exit event
static std::vector<std::pair<FINI_CALLBACK, VOID*>> drpin_exit_event_callbacks;

// Stores the functions callbacks that should be called when a new instruction is discovered. It's used inside dynamorio bb_event calback
static std::vector<std::pair<INS_INSTRUMENT_CALLBACK, VOID*>> drpin_bb_event_ins_callbacks;

// Stores the functions callbacks that should be called when a new trace is discovered. Because there is no Trace in dynamorio as there is in pin, we are goint to thread that our traces only have one basic block. It's used inside dynamorio bb_event calback
static std::vector<std::pair<TRACE_INSTRUMENT_CALLBACK, VOID*>> drpin_bb_event_trace_callbacks;

// Stores the functions callbacks that should be called when a new thread is started. 
static std::vector<std::pair<THREAD_START_CALLBACK, VOID*>> drpin_thread_init_event_callbacks;

// Stores the functions callbacks that should be called when a new thread is started. 
static std::vector<std::pair<THREAD_FINI_CALLBACK, VOID*>> drpin_thread_exit_event_callbacks;

// Stores the functions callbacks that should be called when a fork happens. 
static std::vector<std::pair<FORK_CALLBACK, VOID*>> drpin_fork_init_event_callbacks;

// Stores the functions callbacks that should be called before a system call happens. 
static std::vector<std::pair<SYSCALL_ENTRY_CALLBACK, VOID*>> drpin_pre_syscall_event_callbacks;

// Stores the functions callbacks that should be called after a system call happened. 
static std::vector<std::pair<SYSCALL_EXIT_CALLBACK, VOID*>> drpin_post_syscall_event_callbacks;

// Stores the functions callbacks that should be called after a context change happened. 
static std::vector<std::pair<CONTEXT_CHANGE_CALLBACK, VOID*>> drpin_context_change_event_callbacks;

// Stores the functions callbacks that should be called when a new image is discovered.
static std::vector<std::pair<IMAGECALLBACK, VOID*>> drpin_img_event_callbacks;

// Stores the functions callbacks that should be called when a new image is unloaded.
static std::vector<std::pair<IMAGECALLBACK, VOID*>> drpin_img_unload_event_callbacks;


static std::vector<IMG> drpin_application_imgs;

static std::map<std::string, std::vector<SEC>> drpin_img_secs;

static std::map<std::string, std::vector<RTN>> drpin_sec_rtns;


static IMG& drpin_find_img_by_name(const string& name){
    for(int i = 0; i < drpin_application_imgs.size(); i++){
        if(drpin_application_imgs[i].name == name) {
            return drpin_application_imgs[i];
        }
    }
    // should never happen this
    return drpin_application_imgs[0];
}

static IMG& drpin_find_img_with_uuid(const string& uuid){
    for(int i = 0; i < drpin_application_imgs.size(); i++){
        if(drpin_application_imgs[i].img_uniq_identifier == uuid) {
            return drpin_application_imgs[i];
        }
    }
    // should never happen this
    return drpin_application_imgs[0];
}

static std::vector<SEC>& drpin_secs_for_img(const IMG& img){
    // bool image_exists = (drpin_img_secs.find(img.img_uniq_identifier) != drpin_img_secs.end());
    return drpin_img_secs[img.img_uniq_identifier];
}

static SEC& drpin_find_sec_with_uuid(const string& uuid){

    // for every image in the application
    for (auto it = drpin_img_secs.begin(); it != drpin_img_secs.end(); ++it){
        // for every section in the image
        for(int i = 0; i < it->second.size(); i++){
            if(it->second[i].sec_uniq_identifier == uuid){
                return it->second[i];
            }
        }
    }

}


static int drpin_get_number_secs_of_img(const IMG& img){
    bool image_exists = (drpin_img_secs.find(img.img_uniq_identifier) != drpin_img_secs.end());
    if (!image_exists) {
        return 0;
    }
    return drpin_img_secs[img.img_uniq_identifier].size();
}

static int drpin_get_sec_index(const SEC& sec){
    bool image_exists = (drpin_img_secs.find(sec.belonging_img) != drpin_img_secs.end());
    if (!image_exists){
        return 0;
    }
    for(int i = 0; i < drpin_img_secs[sec.belonging_img].size(); i++){
        if (drpin_img_secs[sec.belonging_img][i].sec_uniq_identifier == sec.sec_uniq_identifier) {
            return i;
        }
    }
    // no sec found;
    return -1;
}


static std::vector<RTN>& drpin_rtns_for_sec(const SEC& sec){
    // return drpin_rtn_secs[sec.sec_uniq_identifier];
    return drpin_sec_rtns[sec.sec_uniq_identifier];
}

static RTN& drpin_find_rtn_with_uuid(const string& uuid){

    // for every section in the application
    for (auto it = drpin_sec_rtns.begin(); it != drpin_sec_rtns.end(); ++it){
        // for every routine in the section
        for(int i = 0; i < it->second.size(); i++){
            if(it->second[i].rtn_uniq_identifier == uuid){
                return it->second[i];
            }
        }
    }
}

static int drpin_get_number_rtn_of_sec(const SEC& sec){

    bool sec_exists = (drpin_sec_rtns.find(sec.sec_uniq_identifier) != drpin_sec_rtns.end());
    if (!sec_exists) {
        return 0;
    }
    return drpin_sec_rtns[sec.sec_uniq_identifier].size();

}

static int drpin_get_rtn_index(const RTN& rtn){

    bool sec_exists = (drpin_sec_rtns.find(rtn.belonging_sec) != drpin_sec_rtns.end());
    if (!sec_exists) {
        return 0;
    }
    for(int i = 0; i < drpin_sec_rtns[rtn.belonging_sec].size(); i++){
        if (drpin_sec_rtns[rtn.belonging_sec][i].rtn_uniq_identifier == rtn.rtn_uniq_identifier) {
            return i;
        }
    }
    // no sec found;
    return -1;

}

static bool drpin_new_symbol_event(const char *name, size_t modoffs, void *data){
    string section_uuid = string((const char*) data);
    RTN rtn;
    rtn.valid = true;
    rtn.name = string(name);
    rtn.modoffs = modoffs;
    rtn.rtn_uniq_identifier = generate_uuid();
    rtn.belonging_sec = section_uuid;
    SEC& related_sec = drpin_find_sec_with_uuid(section_uuid);
    rtn.belonging_img = related_sec.belonging_img;
    drpin_sec_rtns[rtn.belonging_sec].push_back(rtn);
    return true;
}



static void drpin_module_unload_event(void *drcontext, const module_data_t* info){

    IMG img = drpin_find_img_by_name(string(info->full_path));
    std::cout << "ESTAMOSD AQUI NELASKLJ" << std::endl;
    std::cout << "ESTAMOSD AQUI NELASKLJ" << std::endl;
    std::cout << "ESTAMOSD AQUI NELASKLJ" << std::endl;
    std::cout << "ESTAMOSD AQUI NELASKLJ" << std::endl;

    for(std::vector<std::pair<IMAGECALLBACK, VOID*>>::iterator it = drpin_img_unload_event_callbacks.begin(); it != drpin_img_unload_event_callbacks.end(); ++it){
        it->first(img, it->second);
    }

}

static void drpin_module_event(void *drcontext, const module_data_t* info, bool loaded){
    module_data_t* copied_data = dr_copy_module_data(info);

    IMG img;
    img.valid = true;
    img.module_data = copied_data;
    img.lowest_address = copied_data->start;
    img.highest_address = copied_data->end;
    img.img_uniq_identifier = generate_uuid();
    img.drcontext = drcontext;
    img.name = string(copied_data->full_path);
    module_data_t* main_module =  dr_get_main_module();
    string main_module_name = string(main_module->full_path);
    img.main_module = false;
    if(main_module_name == img.name){
        img.main_module = true;
    }
    dr_free_module_data(main_module);
    drpin_application_imgs.push_back(img);

    // For now, will create one sec for each image

    SEC sec;
    sec.valid = true;
    sec.belonging_img = img.img_uniq_identifier;
    sec.sec_uniq_identifier = generate_uuid();
    drpin_img_secs[sec.belonging_img].push_back(sec);

    // For every rtn in this module
    drsym_enumerate_symbols(copied_data->full_path, drpin_new_symbol_event , (void*) sec.sec_uniq_identifier.c_str(), DRSYM_DEFAULT_FLAGS);




    // will not notify pintool if the image loaded is libdrpin.so
    if (img.name.find("libdrpin.so") != std::string::npos) {
        return;
    }
    // will not notify pintool if the image loaded is libdynamorio.so
    if (img.name.find("libdynamorio.so") != std::string::npos) {
        return;
    }

    for(std::vector<std::pair<IMAGECALLBACK, VOID*>>::iterator it = drpin_img_event_callbacks.begin(); it != drpin_img_event_callbacks.end(); ++it){
        it->first(img, it->second);
    }
}

static dr_signal_action_t drpin_signal_event(void *drcontext, dr_siginfo_t *info) {
    if (info->sig == SIGTERM || info->sig == SIGKILL) {

        for(std::vector<std::pair<CONTEXT_CHANGE_CALLBACK, VOID*>>::iterator it = drpin_context_change_event_callbacks.begin(); it != drpin_context_change_event_callbacks.end(); ++it){
            thread_id_t t_id = dr_get_thread_id(drcontext);
            CONTEXT_CHANGE_REASON reason = CONTEXT_CHANGE_REASON_FATALSIGNAL; 
            it->first((THREADID) t_id, reason, NULL, NULL, 0, it->second);
        }

    }
    // else if (info->sig == SIGSEGV) {
    //     /* Skip the faulting instruction.  This is a sample only! */
    //     std::cout << "DEU MERDA " << std::endl << std::flush;
    //     app_pc pc = decode_next_pc(drcontext, info->mcontext->pc);
    //     if (pc != NULL)
    //         info->mcontext->pc = pc;
    //     return DR_SIGNAL_REDIRECT;
    // }

    return DR_SIGNAL_DELIVER;
}

static void drpin_post_syscall_event(void *drcontext, int sysnum){
    for(std::vector<std::pair<SYSCALL_EXIT_CALLBACK, VOID*>>::iterator it = drpin_post_syscall_event_callbacks.begin(); it != drpin_post_syscall_event_callbacks.end(); ++it){
        thread_id_t t_id = dr_get_thread_id(drcontext);
        // TODO suppport windows aswell
        SYSCALL_STANDARD pin_syscall_std = SYSCALL_STANDARD_IA32E_LINUX; 
        CONTEXT ctx;
        ctx.drcontext = drcontext;
        ctx.syscallnumber = sysnum;
        it->first((THREADID) t_id, &ctx, pin_syscall_std, it->second);
    }
   return; 
}

static bool drpin_pre_syscall_event(void *drcontext, int sysnum){
    for(std::vector<std::pair<SYSCALL_ENTRY_CALLBACK, VOID*>>::iterator it = drpin_pre_syscall_event_callbacks.begin(); it != drpin_pre_syscall_event_callbacks.end(); ++it){
        thread_id_t t_id = dr_get_thread_id(drcontext);
        // TODO suppport windows aswell
        SYSCALL_STANDARD pin_syscall_std = SYSCALL_STANDARD_IA32E_LINUX; 
        CONTEXT ctx;
        ctx.drcontext = drcontext;
        ctx.syscallnumber = sysnum;
        it->first((THREADID) t_id, &ctx, pin_syscall_std, it->second);
    }
    return true;
}

static bool drpin_filter_syscall_event(void *drcontext, int sysnum){
    return true;
}

static void drpin_fork_init_event(void *drcontext){
  for(std::vector<std::pair<FORK_CALLBACK, VOID*>>::iterator it = drpin_fork_init_event_callbacks.begin(); it != drpin_fork_init_event_callbacks.end(); ++it){
    thread_id_t t_id = dr_get_thread_id(drcontext);
    it->first((THREADID) t_id, NULL, it->second);
  }
}

static void drpin_thread_init_event(void *drcontext){
  for(std::vector<std::pair<THREAD_START_CALLBACK, VOID*>>::iterator it = drpin_thread_init_event_callbacks.begin(); it != drpin_thread_init_event_callbacks.end(); ++it){
    thread_id_t t_id = dr_get_thread_id(drcontext);
    it->first((THREADID) t_id, NULL, 0, it->second);
  }
}

static void drpin_thread_exit_event(void *drcontext){
  for(std::vector<std::pair<THREAD_FINI_CALLBACK, VOID*>>::iterator it = drpin_thread_exit_event_callbacks.begin(); it != drpin_thread_exit_event_callbacks.end(); ++it){
    thread_id_t t_id = dr_get_thread_id(drcontext);
    it->first((THREADID) t_id, NULL, 0, it->second);
  }
}

// This function is called when drpin is about to exit. It is registered to follow the exit event by dr_register_exit_event
static void drpin_exit_event(){
  drpin_debug_print("drpin_exit_event called");

  for(std::vector<std::pair<FINI_CALLBACK, VOID*>>::iterator it = drpin_exit_event_callbacks.begin(); it != drpin_exit_event_callbacks.end(); ++it){

    // TODO: right now we are always passing 0 as the exit code. we should pass the actual exit code to the fini function
    it->first(0, it->second);
  }
  drsym_exit();
  drutil_exit();
}

// This function is called whenever dynamorio finds a new basic block.
static dr_emit_flags_t drpin_bb_event(void *drcontext, void *tag, instrlist_t *bb, bool for_trace, bool translating){
  drpin_debug_print("drpin_bb_event called");
//   if(translating || for_trace){
//     return DR_EMIT_DEFAULT;
//   }
  if(translating){
    return DR_EMIT_DEFAULT;
  }


//    drutil_expand_rep_string(drcontext, bb);
  // Everytime a new BB is found, we consider a creation of a TRACE with 1 BBL only
  for(std::vector<std::pair<TRACE_INSTRUMENT_CALLBACK, VOID*>>::iterator it = drpin_bb_event_trace_callbacks.begin(); it != drpin_bb_event_trace_callbacks.end(); ++it){
      TRACE trace;
      BBL only_bbl;
      only_bbl.drcontext = drcontext; 
      only_bbl.instr = instrlist_first_app(bb);
      only_bbl.instr_list = bb;
      trace.only_bbl = only_bbl;
      it->first(trace, it->second);
  }

  instr_t *instr, *next;
  for (instr = instrlist_first_app(bb); instr != NULL; instr = next) {
    next = instr_get_next_app(instr);

    for(std::vector<std::pair<INS_INSTRUMENT_CALLBACK, VOID*>>::iterator it = drpin_bb_event_ins_callbacks.begin(); it != drpin_bb_event_ins_callbacks.end(); ++it){
      // TODO: right now the ins variable is blank. We should populate a instruction reference in this variable
      INS ins;
      ins.drcontext = drcontext;
      ins.instr = instr;
      ins.instr_list = bb;
      it->first(ins, it->second);
    }
  }
  
  

  return DR_EMIT_DEFAULT;
}


// // This function is called whenever dynamorio creates a new trace
// static dr_emit_flags_t drpin_trace_event(void *drcontext, void *tag, instrlist_t *trace, bool translating){
//   drpin_debug_print("drpin_trace_event called");

//   return DR_EMIT_DEFAULT;
// }


class DRPin_unique_identifier {
  private:
    static int identifier;
  public:
    static int get_unique_id();
};

int DRPin_unique_identifier::identifier = 0;
int DRPin_unique_identifier::get_unique_id(){
  identifier ++;
  return identifier;
}


// static void drpin_insert_call(int id){
//   // long long id_int = (long long) opnd_get_addr(id);
//   std::cout << "operand is "  << id <<   std::endl;
// }





















// PIN related variables that are not in the oficial PIN API


static INT32 PIN_Init_argc;
static CHAR ** PIN_Init_argv;
bool PIN_Init_already_called = false;







// PIN API

class  LEVEL_PINCLIENT::COMPLEX_CALLBACKVAL_BASE{};

 /* -------------------------------------------- */

std::vector<std::string> tokenize(const std::string& str, const std::string& delimiters = " ", bool trimEmpty = false) {
   std::string::size_type pos, lastPos = 0, length = str.length();

   using value_type = typename std::vector<std::string>::value_type;
   using size_type  = typename std::vector<std::string>::size_type;

   std::vector<std::string> retTokens;
   while(lastPos < length + 1)
   {
      pos = str.find_first_of(delimiters, lastPos);
      if(pos == std::string::npos)
      {
         pos = length;
      }

      if(pos != lastPos || !trimEmpty)
         retTokens.push_back(value_type(str.data()+lastPos, (size_type)pos-lastPos ));

      lastPos = pos + 1;
   }
   return retTokens;
}

DR_EXPORT BOOL LEVEL_PINCLIENT::PIN_Init(INT32 argc, CHAR ** argv){
  drpin_debug_print("PIN_Init() called");
  if(PIN_Init_already_called){

    // we don't support nested PIN_Init calls
    drpin_debug_print("Nested PIN_Init call. Aborting");
    return true;
  } else {
    PIN_Init_argc = argc;
    PIN_Init_argv = argv;
    PIN_Init_already_called = true;

    std::vector<std::string> parsedOpts = tokenize(drpin_pintool_op_flag, " ", true);
    std::stack<std::string> opt_stack;
    for (int i = parsedOpts.size() -1; i >= 0; i--) {
      if(parsedOpts[i].size() == 0){
        continue;
      }
      if(parsedOpts[i][0] == '-'){
        std::string opt_name = parsedOpts[i].substr(1, parsedOpts[i].size() -1);
        KNOB_BASE* p = KNOB_BASE::FindKnob(opt_name);
        if(opt_stack.empty()){
          KNOB_BASE::dr_knob_cmd_map[opt_name] = "true";
          p->AddValue("true");
        }
        else {
          while(opt_stack.empty() == false){
          KNOB_BASE::dr_knob_cmd_map[opt_name] = opt_stack.top();
          p->AddValue(opt_stack.top());
          opt_stack.pop();
          }
        }
      }
      else {
        opt_stack.push(parsedOpts[i]);
      }
    }

    drutil_init();
    drsym_init(0);
    // drmgr_init();
    dr_register_module_unload_event(drpin_module_unload_event);
    dr_register_module_load_event(drpin_module_event);
    dr_register_signal_event(drpin_signal_event);
    dr_register_filter_syscall_event(drpin_filter_syscall_event);
    dr_register_pre_syscall_event(drpin_pre_syscall_event);
    dr_register_post_syscall_event(drpin_post_syscall_event);
    dr_register_fork_init_event(drpin_fork_init_event);
    dr_register_thread_exit_event(drpin_thread_exit_event);
    dr_register_thread_init_event(drpin_thread_init_event);
    dr_register_exit_event(drpin_exit_event);
    dr_register_bb_event(drpin_bb_event);
    // dr_register_trace_event(drpin_trace_event);
  }
  return false;
}

/* -------------------------------------------- */

DR_EXPORT PIN_CALLBACK LEVEL_PINCLIENT::INS_AddInstrumentFunction(INS_INSTRUMENT_CALLBACK fun, VOID *val){
  drpin_debug_print("ADDInstrumentFunction() called");

  drpin_bb_event_ins_callbacks.push_back(std::pair<INS_INSTRUMENT_CALLBACK, VOID*>(fun, val));;


  LEVEL_PINCLIENT::PIN_CALLBACK pincallback  = new LEVEL_PINCLIENT::COMPLEX_CALLBACKVAL_BASE();
  return pincallback;
}

// /* -------------------------------------------- */

DR_EXPORT PIN_CALLBACK LEVEL_PINCLIENT::PIN_AddFiniFunction(FINI_CALLBACK fun, VOID *val){
  drpin_debug_print("PIN_AddFiniFunction() called");

  drpin_exit_event_callbacks.push_back(std::pair<FINI_CALLBACK, VOID*>(fun, val));

  LEVEL_PINCLIENT::PIN_CALLBACK pincallback  = new LEVEL_PINCLIENT::COMPLEX_CALLBACKVAL_BASE();
  return pincallback;
}

// /* -------------------------------------------- */

DR_EXPORT VOID LEVEL_PINCLIENT::PIN_StartProgram(){
  //By default, DR executes the program at the end of instrumentation. So this method does nothing
  drpin_debug_print("PIN_StartProgram() called");
  if(!PIN_Init_already_called){
    drpin_debug_print("PIN_Init not called before PIN_StartProgram.");
  }

// for(std::vector<std::pair<ROOT_THREAD_FUNC*, VOID*>>::iterator it = spawnInternalThreadCallbacks.begin(); it != spawnInternalThreadCallbacks.end(); ++it){
//     it->first(  it->second);
// }
}


DR_EXPORT VOID LEVEL_PINCLIENT::INS_InsertCall(INS ins, IPOINT action , AFUNPTR funptr, ...) 	{
  // TODO: verify need of saving fp state on the clean call

    drpin_debug_print("INS_InsertCall() called");

    if (ins.instr == NULL || ins.instr_list == NULL){
        return ;
    }
    // ___debug_print(2);

    std::vector<UINT64> iarg_call_arguments;

    // ___debug_print(3);
    va_list listPointer;
    va_start( listPointer, funptr );
    UINT64 arg = (UINT64) va_arg( listPointer, UINT64 );
    iarg_call_arguments.push_back(arg);

    // ___debug_print(4);
    while( arg != IARG_LAST){

        arg = (UINT64) va_arg( listPointer, UINT64 );
        iarg_call_arguments.push_back(arg);

    }

    // ___debug_print(5);
    va_end(listPointer);

    // ___debug_print(6);
    drpin_insert_clean_call(ins.drcontext, (instrlist_t*) ins.instr_list, (instr_t *) ins.instr, (void *) funptr, false, iarg_call_arguments);
}

DR_EXPORT  ADDRINT LEVEL_PINCLIENT::INS_Address(INS ins){
  drpin_debug_print("INS_Address() called");

    if (ins.instr == NULL || ins.instr_list == NULL){
        return 0;
    }
  app_pc inst_addr = instr_get_app_pc((instr_t*) ins.instr);
  return (ADDRINT)inst_addr;
}

DR_EXPORT  std::string LEVEL_CORE::INS_Disassemble(INS ins){
  // return "mov bla bla";
  drpin_debug_print("INS_Disassemble() called");

    if (ins.instr == NULL || ins.instr_list == NULL){
        return "";
    }

  char buffer[100];
  size_t written_chars =  instr_disassemble_to_buffer	(	ins.drcontext, (instr_t*)ins.instr, buffer, 100);
  std::string ret_val(buffer);
  return ret_val;
}


// /* -------------------------------------------- */


namespace LEVEL_BASE {


//   KNOB_BASE::KNOB_BASE(const string & myprefix, const string & myname, const string & myfamily, const string & mydefault, const string & mypurpose, KNOB_MODE mymode) : _name(myname), _family(myfamily), _default_value(mydefault),_mode(mymode), _purpose(mypurpose){
//     drpin_debug_print("KNOB_BASE constructor called");
//   }

//   string KNOB_BASE::StringKnobSummary(){
//     return "NO DESCRIPTION";
//   }

  KNOB_BASE* KNOB_BASE::_knob_list = nullptr;

//   std::map<std::string, std::string> KNOB_BASE::dr_knob_cmd_map;


  std::map<std::string, std::string> KNOB_BASE::dr_knob_cmd_map = {};


  DR_EXPORT REG REG_FullRegName(const REG reg){
    drpin_debug_print("REG_FullRegName() called");
    reg_id_t drpin_reg = convert_pin_reg_to_drpin_reg(reg);
    reg_id_t drpin_64bit_reg;
    if (drpin_reg_is_8bit(drpin_reg)){
        drpin_64bit_reg = drpin_8bit_reg_to_64bit_reg(drpin_reg);
    } else if (drpin_reg_is_16bit(drpin_reg)){
        drpin_64bit_reg = drpin_16bit_reg_to_64bit_reg(drpin_reg);
    } else if (drpin_reg_is_32bit(drpin_reg)){
        drpin_64bit_reg = drpin_32bit_reg_to_64bit_reg(drpin_reg);
    } else {
        drpin_64bit_reg = drpin_reg;
    }
    return convert_drpin_reg_to_pin_reg(drpin_64bit_reg);
  }

  DR_EXPORT string REG_StringShort(REG reg){
    drpin_debug_print("REG_StringShort() called");
      reg_id_t drpin_reg = convert_pin_reg_to_drpin_reg(reg);
      const char* ret = get_register_name(drpin_reg);
      string retVal(ret);
      return retVal;
  }

}

namespace LEVEL_CORE {


// functions declarations

  // DR_EXPORT std::string INS_Disassemble(INS ins){
  //   std::cout << __func__ << std::endl;
  //   std::cout << __PRETTY_FUNCTION__ << std::endl;
  //   std::cout << "Function not implemented" << std::endl << std::flush;
  //   exit(1);
  // }

  DR_EXPORT UINT32 INS_OperandCount(INS ins){
    drpin_debug_print("INS_OperandRead() called");
    if (ins.instr == NULL || ins.instr_list == NULL){
        return 0;
    }
    UINT32 total = instr_num_srcs((instr_t *)ins.instr) + instr_num_dsts((instr_t *)ins.instr);
    return total;
  }

  DR_EXPORT BOOL INS_OperandRead(INS ins, UINT32 n){
    // the list of operands will always be the srcs first and later the dsts
    drpin_debug_print("INS_OperandRead() called");

    if (ins.instr == NULL || ins.instr_list == NULL){
        return false ;
    }
    if (n < instr_num_srcs((instr_t *)ins.instr)){
        return true;
    } else {
        return false;
    }
  }

  DR_EXPORT BOOL INS_OperandWritten(INS ins, UINT32 n){
    // the list of operands will always be the srcs first and later the dsts
    drpin_debug_print("INS_OperandWritten() called");

    if (ins.instr == NULL || ins.instr_list == NULL){
        return false ;
    }
    if (n >= instr_num_srcs((instr_t *)ins.instr) && n < instr_num_dsts((instr_t *)ins.instr) + instr_num_srcs((instr_t *)ins.instr) ){
        return true;
    } else {
        return false;
    }
  }

  DR_EXPORT BOOL INS_OperandIsMemory(INS ins, UINT32 n){
    drpin_debug_print("INS_OperandIsMemory() called");
    if (ins.instr == NULL || ins.instr_list == NULL){
        return false ;
    }
    opnd_t operand;

    if (instr_get_opcode((instr_t *)ins.instr) == OP_lea){
        // just to be compatible with pin behavior
        return false;
    }

    if (n < instr_num_srcs((instr_t *)ins.instr)){
        // is a src operand
        operand = instr_get_src((instr_t *)ins.instr, n);
        return opnd_is_memory_reference(operand);
        // drpin_reg = opnd_get_reg(operand);
    } else if (n < instr_num_srcs((instr_t *)ins.instr) + instr_num_dsts((instr_t *)ins.instr)){
        // is a dst operand
        operand = instr_get_dst((instr_t *)ins.instr, n - instr_num_srcs((instr_t *)ins.instr));
        return opnd_is_memory_reference(operand);
    } else {
        return false;
    }
  }

  DR_EXPORT BOOL INS_OperandIsReg(INS ins, UINT32 n){
    drpin_debug_print("INS_OperandIsReg() called");
    if (ins.instr == NULL || ins.instr_list == NULL){
        return false ;
    }
    opnd_t operand;

    if (n < instr_num_srcs((instr_t *)ins.instr)){
        // is a src operand
        operand = instr_get_src((instr_t *)ins.instr, n);
        return opnd_is_reg(operand);
        // drpin_reg = opnd_get_reg(operand);
    } else if (n < instr_num_srcs((instr_t *)ins.instr) + instr_num_dsts((instr_t *)ins.instr)){
        // is a dst operand
        operand = instr_get_dst((instr_t *)ins.instr, n - instr_num_srcs((instr_t *)ins.instr));
        return opnd_is_reg(operand);
    } else {
        return false;
    }
  }


  DR_EXPORT REG INS_OperandReg(INS ins, UINT32 n){
    drpin_debug_print("INS_OperandReg() called");

    if (ins.instr == NULL || ins.instr_list == NULL){
        REG reg = REG_INVALID_;
        return  reg;
    }
    opnd_t operand;
    reg_id_t drpin_reg;
    REG pin_reg = REG_INVALID_;

    if (n < instr_num_srcs((instr_t *)ins.instr)){
        // is a src operand
        operand = instr_get_src((instr_t *)ins.instr, n);
        drpin_reg = opnd_get_reg(operand);
    } else if (n < instr_num_srcs((instr_t *)ins.instr) + instr_num_dsts((instr_t *)ins.instr)){
        // is a dst operand
        operand = instr_get_dst((instr_t *)ins.instr, n - instr_num_srcs((instr_t *)ins.instr));
        drpin_reg = opnd_get_reg(operand);
    } else {
        return REG_INVALID_;
    }

    pin_reg = convert_drpin_reg_to_pin_reg(drpin_reg);

    return pin_reg;
  }

  DR_EXPORT REG INS_OperandMemoryBaseReg(INS ins, UINT32 n){
    drpin_debug_print("INS_OperandMemoryBaseReg() called");

    if (ins.instr == NULL || ins.instr_list == NULL){
        REG reg = REG_INVALID_;
        return  reg;
    }
    opnd_t operand;
    reg_id_t drpin_reg;
    REG pin_reg = REG_INVALID_;

    if (n < instr_num_srcs((instr_t *)ins.instr)){
        // is a src operand
        operand = instr_get_src((instr_t *)ins.instr, n);
        drpin_reg = opnd_get_base(operand);
    } else if (n < instr_num_srcs((instr_t *)ins.instr) + instr_num_dsts((instr_t *)ins.instr)){
        // is a dst operand
        operand = instr_get_dst((instr_t *)ins.instr, n - instr_num_srcs((instr_t *)ins.instr));
        drpin_reg = opnd_get_base(operand);
    } else {
        return REG_INVALID_;
    }

    pin_reg = convert_drpin_reg_to_pin_reg(drpin_reg);

    return pin_reg;
  }

  DR_EXPORT REG INS_OperandMemoryIndexReg(INS ins, UINT32 n){

    drpin_debug_print("INS_OperandMemoryIndexReg() called");

    if (ins.instr == NULL || ins.instr_list == NULL){
        REG reg = REG_INVALID_;
        return  reg;
    }
    opnd_t operand;
    reg_id_t drpin_reg;
    REG pin_reg = REG_INVALID_;

    if (n < instr_num_srcs((instr_t *)ins.instr)){
        // is a src operand
        operand = instr_get_src((instr_t *)ins.instr, n);
        drpin_reg = opnd_get_index(operand);
    } else if (n < instr_num_srcs((instr_t *)ins.instr) + instr_num_dsts((instr_t *)ins.instr)){
        // is a dst operand
        operand = instr_get_dst((instr_t *)ins.instr, n - instr_num_srcs((instr_t *)ins.instr));
        drpin_reg = opnd_get_index(operand);
    } else {
        return REG_INVALID_;
    }

    pin_reg = convert_drpin_reg_to_pin_reg(drpin_reg);

    return pin_reg;
  }

  DR_EXPORT BOOL INS_LockPrefix(INS ins){
    drpin_debug_print("INS_LockPrefix() called");
    if (ins.instr == NULL || ins.instr_list == NULL){
        return false;
    }
    return instr_get_prefix_flag((instr_t *)ins.instr, PREFIX_LOCK);
  }

  DR_EXPORT UINT32 INS_OperandWidth(INS ins, UINT32 n){
    drpin_debug_print("INS_OperandWidth() called");

    if (ins.instr == NULL || ins.instr_list == NULL){
        REG reg = REG_INVALID_;
        return  0;
    }
    opnd_t operand;

    if (n < instr_num_srcs((instr_t *)ins.instr)){
        // is a src operand
        operand = instr_get_src((instr_t *)ins.instr, n);
        opnd_size_t opnd_sz = opnd_get_size(operand);
        return opnd_size_in_bits(opnd_sz);
    } else if (n < instr_num_srcs((instr_t *)ins.instr) + instr_num_dsts((instr_t *)ins.instr)){
        // is a dst operand
        operand = instr_get_dst((instr_t *)ins.instr, n - instr_num_srcs((instr_t *)ins.instr));
        opnd_size_t opnd_sz = opnd_get_size(operand);
        return opnd_size_in_bits(opnd_sz);
    } else {
        return 0;
    }

  }

  DR_EXPORT INT32 INS_Category(const INS ins){
    if(instr_is_cbr((instr_t*) ins.instr)){
      return XED_CATEGORY_COND_BR;
    } else {
      return XED_CATEGORY_NOP;
    }
  }

  DR_EXPORT OPCODE INS_Opcode(INS ins){
    drpin_debug_print("INS_Opcode() called");
    if (ins.instr == NULL || ins.instr_list == NULL){
        return 0;
    }
    int drpin_opcode = instr_get_opcode((instr_t*) ins.instr);
    OPCODE pin_opcode = XED_ICLASS_INVALID;

    if ( drpin_opcode == OP_INVALID) {

        pin_opcode = XED_ICLASS_INVALID;
    
    } else if ( drpin_opcode == OP_aaa) {

        pin_opcode = XED_ICLASS_AAA;
    
    } else if ( drpin_opcode == OP_aad) {

        pin_opcode = XED_ICLASS_AAD;
    
    } else if ( drpin_opcode == OP_aam) {

        pin_opcode = XED_ICLASS_AAM;
    
    } else if ( drpin_opcode == OP_aas) {

        pin_opcode = XED_ICLASS_AAS;
    
    } else if ( drpin_opcode == OP_adc) {

        pin_opcode = XED_ICLASS_ADC;
    
    } else if ( drpin_opcode == OP_adcx) {

        pin_opcode = XED_ICLASS_ADCX;
    
    } else if ( drpin_opcode == OP_add) {

        pin_opcode = XED_ICLASS_ADD;
    
    } else if ( drpin_opcode == OP_addpd) {

        pin_opcode = XED_ICLASS_ADDPD;
    
    } else if ( drpin_opcode == OP_addps) {

        pin_opcode = XED_ICLASS_ADDPS;
    
    } else if ( drpin_opcode == OP_addsd) {

        pin_opcode = XED_ICLASS_ADDSD;
    
    } else if ( drpin_opcode == OP_addss) {

        pin_opcode = XED_ICLASS_ADDSS;
    
    } else if ( drpin_opcode == OP_addsubpd) {

        pin_opcode = XED_ICLASS_ADDSUBPD;
    
    } else if ( drpin_opcode == OP_addsubps) {

        pin_opcode = XED_ICLASS_ADDSUBPS;
    
    } else if ( drpin_opcode == OP_adox) {

        pin_opcode = XED_ICLASS_ADOX;
    
    } else if ( drpin_opcode == OP_aesdec) {

        pin_opcode = XED_ICLASS_AESDEC;
    
    } else if ( drpin_opcode == OP_aesdeclast) {

        pin_opcode = XED_ICLASS_AESDECLAST;
    
    } else if ( drpin_opcode == OP_aesenc) {

        pin_opcode = XED_ICLASS_AESENC;
    
    } else if ( drpin_opcode == OP_aesenclast) {

        pin_opcode = XED_ICLASS_AESENCLAST;
    
    } else if ( drpin_opcode == OP_aesimc) {

        pin_opcode = XED_ICLASS_AESIMC;
    
    } else if ( drpin_opcode == OP_aeskeygenassist) {

        pin_opcode = XED_ICLASS_AESKEYGENASSIST;
    
    } else if ( drpin_opcode == OP_and) {

        pin_opcode = XED_ICLASS_AND;
    
    } else if ( drpin_opcode == OP_andn) {

        pin_opcode = XED_ICLASS_ANDN;
    
    } else if ( drpin_opcode == OP_andnpd) {

        pin_opcode = XED_ICLASS_ANDNPD;
    
    } else if ( drpin_opcode == OP_andnps) {

        pin_opcode = XED_ICLASS_ANDNPS;
    
    } else if ( drpin_opcode == OP_andpd) {

        pin_opcode = XED_ICLASS_ANDPD;
    
    } else if ( drpin_opcode == OP_andps) {

        pin_opcode = XED_ICLASS_ANDPS;
    
    } else if ( drpin_opcode == OP_arpl) {

        pin_opcode = XED_ICLASS_ARPL;
    
    } else if ( drpin_opcode == OP_bextr) {

        pin_opcode = XED_ICLASS_BEXTR;
    
    } else if ( drpin_opcode == OP_blcfill) {

        pin_opcode = XED_ICLASS_BLCFILL;
    
    } else if ( drpin_opcode == OP_blci) {

        pin_opcode = XED_ICLASS_BLCI;
    
    } else if ( drpin_opcode == OP_blcic) {

        pin_opcode = XED_ICLASS_BLCIC;
    
    } else if ( drpin_opcode == OP_blcmsk) {

        pin_opcode = XED_ICLASS_BLCMSK;
    
    } else if ( drpin_opcode == OP_blcs) {

        pin_opcode = XED_ICLASS_BLCS;
    
    } else if ( drpin_opcode == OP_blendpd) {

        pin_opcode = XED_ICLASS_BLENDPD;
    
    } else if ( drpin_opcode == OP_blendps) {

        pin_opcode = XED_ICLASS_BLENDPS;
    
    } else if ( drpin_opcode == OP_blendvpd) {

        pin_opcode = XED_ICLASS_BLENDVPD;
    
    } else if ( drpin_opcode == OP_blendvps) {

        pin_opcode = XED_ICLASS_BLENDVPS;
    
    } else if ( drpin_opcode == OP_blsfill) {

        pin_opcode = XED_ICLASS_BLSFILL;
    
    } else if ( drpin_opcode == OP_blsi) {

        pin_opcode = XED_ICLASS_BLSI;
    
    } else if ( drpin_opcode == OP_blsic) {

        pin_opcode = XED_ICLASS_BLSIC;
    
    } else if ( drpin_opcode == OP_blsmsk) {

        pin_opcode = XED_ICLASS_BLSMSK;
    
    } else if ( drpin_opcode == OP_blsr) {

        pin_opcode = XED_ICLASS_BLSR;
    
    } else if ( drpin_opcode == OP_bndcl) {

        pin_opcode = XED_ICLASS_BNDCL;
    
    } else if ( drpin_opcode == OP_bndcn) {

        pin_opcode = XED_ICLASS_BNDCN;
    
    } else if ( drpin_opcode == OP_bndcu) {

        pin_opcode = XED_ICLASS_BNDCU;
    
    } else if ( drpin_opcode == OP_bndldx) {

        pin_opcode = XED_ICLASS_BNDLDX;
    
    } else if ( drpin_opcode == OP_bndmk) {

        pin_opcode = XED_ICLASS_BNDMK;
    
    } else if ( drpin_opcode == OP_bndmov) {

        pin_opcode = XED_ICLASS_BNDMOV;
    
    } else if ( drpin_opcode == OP_bndstx) {

        pin_opcode = XED_ICLASS_BNDSTX;
    
    } else if ( drpin_opcode == OP_bound) {

        pin_opcode = XED_ICLASS_BOUND;
    
    } else if ( drpin_opcode == OP_bsf) {

        pin_opcode = XED_ICLASS_BSF;
    
    } else if ( drpin_opcode == OP_bsr) {

        pin_opcode = XED_ICLASS_BSR;
    
    } else if ( drpin_opcode == OP_bswap) {

        pin_opcode = XED_ICLASS_BSWAP;
    
    } else if ( drpin_opcode == OP_bt) {

        pin_opcode = XED_ICLASS_BT;
    
    } else if ( drpin_opcode == OP_btc) {

        pin_opcode = XED_ICLASS_BTC;
    
    } else if ( drpin_opcode == OP_btr) {

        pin_opcode = XED_ICLASS_BTR;
    
    } else if ( drpin_opcode == OP_bts) {

        pin_opcode = XED_ICLASS_BTS;
    
    } else if ( drpin_opcode == OP_bzhi) {

        pin_opcode = XED_ICLASS_BZHI;
    
    } else if ( drpin_opcode == OP_call_far) {

        pin_opcode = XED_ICLASS_CALL_FAR;
    
    } else if ( drpin_opcode == OP_call_far_ind) {

        pin_opcode = XED_ICLASS_CALL_FAR;
    
    } else if ( drpin_opcode == OP_call) {

        pin_opcode = XED_ICLASS_CALL_NEAR;
    
    } else if ( drpin_opcode == OP_call_ind) {

        pin_opcode = XED_ICLASS_CALL_NEAR;
    
    } else if ( drpin_opcode == OP_cbw) {

        pin_opcode = XED_ICLASS_CBW;
    
    } else if ( drpin_opcode == OP_cdq) {

        pin_opcode = XED_ICLASS_CDQ;
    
    } else if ( drpin_opcode == OP_cdqe) {

        pin_opcode = XED_ICLASS_CDQE;
    
    } else if ( drpin_opcode == OP_clc) {

        pin_opcode = XED_ICLASS_CLC;
    
    } else if ( drpin_opcode == OP_cld) {

        pin_opcode = XED_ICLASS_CLD;
    
    } else if ( drpin_opcode == OP_clflush) {

        pin_opcode = XED_ICLASS_CLFLUSH;
    
    } else if ( drpin_opcode == OP_clgi) {

        pin_opcode = XED_ICLASS_CLGI;
    
    } else if ( drpin_opcode == OP_cli) {

        pin_opcode = XED_ICLASS_CLI;
    
    } else if ( drpin_opcode == OP_clts) {

        pin_opcode = XED_ICLASS_CLTS;
    
    } else if ( drpin_opcode == OP_cmc) {

        pin_opcode = XED_ICLASS_CMC;
    
    } else if ( drpin_opcode == OP_cmovb) {

        pin_opcode = XED_ICLASS_CMOVB;
    
    } else if ( drpin_opcode == OP_cmovbe) {

        pin_opcode = XED_ICLASS_CMOVBE;
    
    } else if ( drpin_opcode == OP_cmovl) {

        pin_opcode = XED_ICLASS_CMOVL;
    
    } else if ( drpin_opcode == OP_cmovle) {

        pin_opcode = XED_ICLASS_CMOVLE;
    
    } else if ( drpin_opcode == OP_cmovnb) {

        pin_opcode = XED_ICLASS_CMOVNB;
    
    } else if ( drpin_opcode == OP_cmovnbe) {

        pin_opcode = XED_ICLASS_CMOVNBE;
    
    } else if ( drpin_opcode == OP_cmovnl) {

        pin_opcode = XED_ICLASS_CMOVNL;
    
    } else if ( drpin_opcode == OP_cmovnle) {

        pin_opcode = XED_ICLASS_CMOVNLE;
    
    } else if ( drpin_opcode == OP_cmovno) {

        pin_opcode = XED_ICLASS_CMOVNO;
    
    } else if ( drpin_opcode == OP_cmovnp) {

        pin_opcode = XED_ICLASS_CMOVNP;
    
    } else if ( drpin_opcode == OP_cmovns) {

        pin_opcode = XED_ICLASS_CMOVNS;
    
    } else if ( drpin_opcode == OP_cmovnz) {

        pin_opcode = XED_ICLASS_CMOVNZ;
    
    } else if ( drpin_opcode == OP_cmovo) {

        pin_opcode = XED_ICLASS_CMOVO;
    
    } else if ( drpin_opcode == OP_cmovp) {

        pin_opcode = XED_ICLASS_CMOVP;
    
    } else if ( drpin_opcode == OP_cmovs) {

        pin_opcode = XED_ICLASS_CMOVS;
    
    } else if ( drpin_opcode == OP_cmovz) {

        pin_opcode = XED_ICLASS_CMOVZ;
    
    } else if ( drpin_opcode == OP_cmp) {

        pin_opcode = XED_ICLASS_CMP;
    
    } else if ( drpin_opcode == OP_cmppd) {

        pin_opcode = XED_ICLASS_CMPPD;
    
    } else if ( drpin_opcode == OP_cmpps) {

        pin_opcode = XED_ICLASS_CMPPS;
    
    } else if ( drpin_opcode == OP_cmpsd) {

        pin_opcode = XED_ICLASS_CMPSD;
    
    } else if ( drpin_opcode == OP_cmpss) {

        pin_opcode = XED_ICLASS_CMPSS;
    
    } else if ( drpin_opcode == OP_cmpxchg) {

        pin_opcode = XED_ICLASS_CMPXCHG;
    
    } else if ( drpin_opcode == OP_cmpxchg16b) {

        pin_opcode = XED_ICLASS_CMPXCHG16B;
    
    } else if ( drpin_opcode == OP_cmpxchg8b) {

        pin_opcode = XED_ICLASS_CMPXCHG8B;
    
    } else if ( drpin_opcode == OP_comisd) {

        pin_opcode = XED_ICLASS_COMISD;
    
    } else if ( drpin_opcode == OP_comiss) {

        pin_opcode = XED_ICLASS_COMISS;
    
    } else if ( drpin_opcode == OP_cpuid) {

        pin_opcode = XED_ICLASS_CPUID;
    
    } else if ( drpin_opcode == OP_cqo) {

        pin_opcode = XED_ICLASS_CQO;
    
    } else if ( drpin_opcode == OP_crc32) {

        pin_opcode = XED_ICLASS_CRC32;
    
    } else if ( drpin_opcode == OP_cvtdq2pd) {

        pin_opcode = XED_ICLASS_CVTDQ2PD;
    
    } else if ( drpin_opcode == OP_cvtdq2ps) {

        pin_opcode = XED_ICLASS_CVTDQ2PS;
    
    } else if ( drpin_opcode == OP_cvtpd2dq) {

        pin_opcode = XED_ICLASS_CVTPD2DQ;
    
    } else if ( drpin_opcode == OP_cvtpd2pi) {

        pin_opcode = XED_ICLASS_CVTPD2PI;
    
    } else if ( drpin_opcode == OP_cvtpd2ps) {

        pin_opcode = XED_ICLASS_CVTPD2PS;
    
    } else if ( drpin_opcode == OP_cvtpi2pd) {

        pin_opcode = XED_ICLASS_CVTPI2PD;
    
    } else if ( drpin_opcode == OP_cvtpi2ps) {

        pin_opcode = XED_ICLASS_CVTPI2PS;
    
    } else if ( drpin_opcode == OP_cvtps2dq) {

        pin_opcode = XED_ICLASS_CVTPS2DQ;
    
    } else if ( drpin_opcode == OP_cvtps2pd) {

        pin_opcode = XED_ICLASS_CVTPS2PD;
    
    } else if ( drpin_opcode == OP_cvtps2pi) {

        pin_opcode = XED_ICLASS_CVTPS2PI;
    
    } else if ( drpin_opcode == OP_cvtsd2si) {

        pin_opcode = XED_ICLASS_CVTSD2SI;
    
    } else if ( drpin_opcode == OP_cvtsd2ss) {

        pin_opcode = XED_ICLASS_CVTSD2SS;
    
    } else if ( drpin_opcode == OP_cvtsi2sd) {

        pin_opcode = XED_ICLASS_CVTSI2SD;
    
    } else if ( drpin_opcode == OP_cvtsi2ss) {

        pin_opcode = XED_ICLASS_CVTSI2SS;
    
    } else if ( drpin_opcode == OP_cvtss2sd) {

        pin_opcode = XED_ICLASS_CVTSS2SD;
    
    } else if ( drpin_opcode == OP_cvtss2si) {

        pin_opcode = XED_ICLASS_CVTSS2SI;
    
    } else if ( drpin_opcode == OP_cvttpd2dq) {

        pin_opcode = XED_ICLASS_CVTTPD2DQ;
    
    } else if ( drpin_opcode == OP_cvttpd2pi) {

        pin_opcode = XED_ICLASS_CVTTPD2PI;
    
    } else if ( drpin_opcode == OP_cvttps2dq) {

        pin_opcode = XED_ICLASS_CVTTPS2DQ;
    
    } else if ( drpin_opcode == OP_cvttps2pi) {

        pin_opcode = XED_ICLASS_CVTTPS2PI;
    
    } else if ( drpin_opcode == OP_cvttsd2si) {

        pin_opcode = XED_ICLASS_CVTTSD2SI;
    
    } else if ( drpin_opcode == OP_cvttss2si) {

        pin_opcode = XED_ICLASS_CVTTSS2SI;
    
    } else if ( drpin_opcode == OP_cwd) {

        pin_opcode = XED_ICLASS_CWD;
    
    } else if ( drpin_opcode == OP_cwde) {

        pin_opcode = XED_ICLASS_CWDE;
    
    } else if ( drpin_opcode == OP_daa) {

        pin_opcode = XED_ICLASS_DAA;
    
    } else if ( drpin_opcode == OP_das) {

        pin_opcode = XED_ICLASS_DAS;
    
    } else if ( drpin_opcode == OP_dec) {

        pin_opcode = XED_ICLASS_DEC;
    
    } else if ( drpin_opcode == OP_div) {

        pin_opcode = XED_ICLASS_DIV;
    
    } else if ( drpin_opcode == OP_divpd) {

        pin_opcode = XED_ICLASS_DIVPD;
    
    } else if ( drpin_opcode == OP_divps) {

        pin_opcode = XED_ICLASS_DIVPS;
    
    } else if ( drpin_opcode == OP_divsd) {

        pin_opcode = XED_ICLASS_DIVSD;
    
    } else if ( drpin_opcode == OP_divss) {

        pin_opcode = XED_ICLASS_DIVSS;
    
    } else if ( drpin_opcode == OP_dppd) {

        pin_opcode = XED_ICLASS_DPPD;
    
    } else if ( drpin_opcode == OP_dpps) {

        pin_opcode = XED_ICLASS_DPPS;
    
    } else if ( drpin_opcode == OP_emms) {

        pin_opcode = XED_ICLASS_EMMS;
    
    } else if ( drpin_opcode == OP_enter) {

        pin_opcode = XED_ICLASS_ENTER;
    
    } else if ( drpin_opcode == OP_extractps) {

        pin_opcode = XED_ICLASS_EXTRACTPS;
    
    } else if ( drpin_opcode == OP_extrq) {

        pin_opcode = XED_ICLASS_EXTRQ;
    
    } else if ( drpin_opcode == OP_f2xm1) {

        pin_opcode = XED_ICLASS_F2XM1;
    
    } else if ( drpin_opcode == OP_fabs) {

        pin_opcode = XED_ICLASS_FABS;
    
    } else if ( drpin_opcode == OP_fadd) {

        pin_opcode = XED_ICLASS_FADD;
    
    } else if ( drpin_opcode == OP_faddp) {

        pin_opcode = XED_ICLASS_FADDP;
    
    } else if ( drpin_opcode == OP_fbld) {

        pin_opcode = XED_ICLASS_FBLD;
    
    } else if ( drpin_opcode == OP_fbstp) {

        pin_opcode = XED_ICLASS_FBSTP;
    
    } else if ( drpin_opcode == OP_fchs) {

        pin_opcode = XED_ICLASS_FCHS;
    
    } else if ( drpin_opcode == OP_fcmovb) {

        pin_opcode = XED_ICLASS_FCMOVB;
    
    } else if ( drpin_opcode == OP_fcmovbe) {

        pin_opcode = XED_ICLASS_FCMOVBE;
    
    } else if ( drpin_opcode == OP_fcmove) {

        pin_opcode = XED_ICLASS_FCMOVE;
    
    } else if ( drpin_opcode == OP_fcmovnb) {

        pin_opcode = XED_ICLASS_FCMOVNB;
    
    } else if ( drpin_opcode == OP_fcmovnbe) {

        pin_opcode = XED_ICLASS_FCMOVNBE;
    
    } else if ( drpin_opcode == OP_fcmovne) {

        pin_opcode = XED_ICLASS_FCMOVNE;
    
    } else if ( drpin_opcode == OP_fcmovnu) {

        pin_opcode = XED_ICLASS_FCMOVNU;
    
    } else if ( drpin_opcode == OP_fcmovu) {

        pin_opcode = XED_ICLASS_FCMOVU;
    
    } else if ( drpin_opcode == OP_fcom) {

        pin_opcode = XED_ICLASS_FCOM;
    
    } else if ( drpin_opcode == OP_fcomi) {

        pin_opcode = XED_ICLASS_FCOMI;
    
    } else if ( drpin_opcode == OP_fcomip) {

        pin_opcode = XED_ICLASS_FCOMIP;
    
    } else if ( drpin_opcode == OP_fcomp) {

        pin_opcode = XED_ICLASS_FCOMP;
    
    } else if ( drpin_opcode == OP_fcompp) {

        pin_opcode = XED_ICLASS_FCOMPP;
    
    } else if ( drpin_opcode == OP_fcos) {

        pin_opcode = XED_ICLASS_FCOS;
    
    } else if ( drpin_opcode == OP_fdecstp) {

        pin_opcode = XED_ICLASS_FDECSTP;
    
    } else if ( drpin_opcode == OP_nop) {

        pin_opcode = XED_ICLASS_FDISI8087_NOP;
    
    } else if ( drpin_opcode == OP_fdiv) {

        pin_opcode = XED_ICLASS_FDIV;
    
    } else if ( drpin_opcode == OP_fdivp) {

        pin_opcode = XED_ICLASS_FDIVP;
    
    } else if ( drpin_opcode == OP_fdivr) {

        pin_opcode = XED_ICLASS_FDIVR;
    
    } else if ( drpin_opcode == OP_fdivrp) {

        pin_opcode = XED_ICLASS_FDIVRP;
    
    } else if ( drpin_opcode == OP_femms) {

        pin_opcode = XED_ICLASS_FEMMS;
    
    } else if ( drpin_opcode == OP_nop) {

        pin_opcode = XED_ICLASS_FENI8087_NOP;
    
    } else if ( drpin_opcode == OP_ffree) {

        pin_opcode = XED_ICLASS_FFREE;
    
    } else if ( drpin_opcode == OP_ffreep) {

        pin_opcode = XED_ICLASS_FFREEP;
    
    } else if ( drpin_opcode == OP_fiadd) {

        pin_opcode = XED_ICLASS_FIADD;
    
    } else if ( drpin_opcode == OP_ficom) {

        pin_opcode = XED_ICLASS_FICOM;
    
    } else if ( drpin_opcode == OP_ficomp) {

        pin_opcode = XED_ICLASS_FICOMP;
    
    } else if ( drpin_opcode == OP_fidiv) {

        pin_opcode = XED_ICLASS_FIDIV;
    
    } else if ( drpin_opcode == OP_fidivr) {

        pin_opcode = XED_ICLASS_FIDIVR;
    
    } else if ( drpin_opcode == OP_fild) {

        pin_opcode = XED_ICLASS_FILD;
    
    } else if ( drpin_opcode == OP_fimul) {

        pin_opcode = XED_ICLASS_FIMUL;
    
    } else if ( drpin_opcode == OP_fincstp) {

        pin_opcode = XED_ICLASS_FINCSTP;
    
    } else if ( drpin_opcode == OP_fist) {

        pin_opcode = XED_ICLASS_FIST;
    
    } else if ( drpin_opcode == OP_fistp) {

        pin_opcode = XED_ICLASS_FISTP;
    
    } else if ( drpin_opcode == OP_fisttp) {

        pin_opcode = XED_ICLASS_FISTTP;
    
    } else if ( drpin_opcode == OP_fisub) {

        pin_opcode = XED_ICLASS_FISUB;
    
    } else if ( drpin_opcode == OP_fisubr) {

        pin_opcode = XED_ICLASS_FISUBR;
    
    } else if ( drpin_opcode == OP_fld) {

        pin_opcode = XED_ICLASS_FLD;
    
    } else if ( drpin_opcode == OP_fld1) {

        pin_opcode = XED_ICLASS_FLD1;
    
    } else if ( drpin_opcode == OP_fldcw) {

        pin_opcode = XED_ICLASS_FLDCW;
    
    } else if ( drpin_opcode == OP_fldenv) {

        pin_opcode = XED_ICLASS_FLDENV;
    
    } else if ( drpin_opcode == OP_fldl2e) {

        pin_opcode = XED_ICLASS_FLDL2E;
    
    } else if ( drpin_opcode == OP_fldl2t) {

        pin_opcode = XED_ICLASS_FLDL2T;
    
    } else if ( drpin_opcode == OP_fldlg2) {

        pin_opcode = XED_ICLASS_FLDLG2;
    
    } else if ( drpin_opcode == OP_fldln2) {

        pin_opcode = XED_ICLASS_FLDLN2;
    
    } else if ( drpin_opcode == OP_fldpi) {

        pin_opcode = XED_ICLASS_FLDPI;
    
    } else if ( drpin_opcode == OP_fldz) {

        pin_opcode = XED_ICLASS_FLDZ;
    
    } else if ( drpin_opcode == OP_fmul) {

        pin_opcode = XED_ICLASS_FMUL;
    
    } else if ( drpin_opcode == OP_fmulp) {

        pin_opcode = XED_ICLASS_FMULP;
    
    } else if ( drpin_opcode == OP_fnclex) {

        pin_opcode = XED_ICLASS_FNCLEX;
    
    } else if ( drpin_opcode == OP_fninit) {

        pin_opcode = XED_ICLASS_FNINIT;
    
    } else if ( drpin_opcode == OP_fnop) {

        pin_opcode = XED_ICLASS_FNOP;
    
    } else if ( drpin_opcode == OP_fnsave) {

        pin_opcode = XED_ICLASS_FNSAVE;
    
    } else if ( drpin_opcode == OP_fnstcw) {

        pin_opcode = XED_ICLASS_FNSTCW;
    
    } else if ( drpin_opcode == OP_fnstenv) {

        pin_opcode = XED_ICLASS_FNSTENV;
    
    } else if ( drpin_opcode == OP_fnstsw) {

        pin_opcode = XED_ICLASS_FNSTSW;
    
    } else if ( drpin_opcode == OP_fpatan) {

        pin_opcode = XED_ICLASS_FPATAN;
    
    } else if ( drpin_opcode == OP_fprem) {

        pin_opcode = XED_ICLASS_FPREM;
    
    } else if ( drpin_opcode == OP_fprem1) {

        pin_opcode = XED_ICLASS_FPREM1;
    
    } else if ( drpin_opcode == OP_fptan) {

        pin_opcode = XED_ICLASS_FPTAN;
    
    } else if ( drpin_opcode == OP_frndint) {

        pin_opcode = XED_ICLASS_FRNDINT;
    
    } else if ( drpin_opcode == OP_frstor) {

        pin_opcode = XED_ICLASS_FRSTOR;
    
    } else if ( drpin_opcode == OP_fscale) {

        pin_opcode = XED_ICLASS_FSCALE;
    
    } else if ( drpin_opcode == OP_nop) {

        pin_opcode = XED_ICLASS_FSETPM287_NOP;
    
    } else if ( drpin_opcode == OP_fsin) {

        pin_opcode = XED_ICLASS_FSIN;
    
    } else if ( drpin_opcode == OP_fsincos) {

        pin_opcode = XED_ICLASS_FSINCOS;
    
    } else if ( drpin_opcode == OP_fsqrt) {

        pin_opcode = XED_ICLASS_FSQRT;
    
    } else if ( drpin_opcode == OP_fst) {

        pin_opcode = XED_ICLASS_FST;
    
    } else if ( drpin_opcode == OP_fstp) {

        pin_opcode = XED_ICLASS_FSTP;
    
    } else if ( drpin_opcode == OP_fsub) {

        pin_opcode = XED_ICLASS_FSUB;
    
    } else if ( drpin_opcode == OP_fsubp) {

        pin_opcode = XED_ICLASS_FSUBP;
    
    } else if ( drpin_opcode == OP_fsubr) {

        pin_opcode = XED_ICLASS_FSUBR;
    
    } else if ( drpin_opcode == OP_fsubrp) {

        pin_opcode = XED_ICLASS_FSUBRP;
    
    } else if ( drpin_opcode == OP_ftst) {

        pin_opcode = XED_ICLASS_FTST;
    
    } else if ( drpin_opcode == OP_fucom) {

        pin_opcode = XED_ICLASS_FUCOM;
    
    } else if ( drpin_opcode == OP_fucomi) {

        pin_opcode = XED_ICLASS_FUCOMI;
    
    } else if ( drpin_opcode == OP_fucomip) {

        pin_opcode = XED_ICLASS_FUCOMIP;
    
    } else if ( drpin_opcode == OP_fucomp) {

        pin_opcode = XED_ICLASS_FUCOMP;
    
    } else if ( drpin_opcode == OP_fucompp) {

        pin_opcode = XED_ICLASS_FUCOMPP;
    
    } else if ( drpin_opcode == OP_fwait) {

        pin_opcode = XED_ICLASS_FWAIT;
    
    } else if ( drpin_opcode == OP_fxam) {

        pin_opcode = XED_ICLASS_FXAM;
    
    } else if ( drpin_opcode == OP_fxch) {

        pin_opcode = XED_ICLASS_FXCH;
    
    } else if ( drpin_opcode == OP_fxrstor64) {

        pin_opcode = XED_ICLASS_FXRSTOR64;
    
    } else if ( drpin_opcode == OP_fxsave32) {

        pin_opcode = XED_ICLASS_FXSAVE;
    
    } else if ( drpin_opcode == OP_fxsave64) {

        pin_opcode = XED_ICLASS_FXSAVE64;
    
    } else if ( drpin_opcode == OP_fxtract) {

        pin_opcode = XED_ICLASS_FXTRACT;
    
    } else if ( drpin_opcode == OP_fyl2x) {

        pin_opcode = XED_ICLASS_FYL2X;
    
    } else if ( drpin_opcode == OP_fyl2xp1) {

        pin_opcode = XED_ICLASS_FYL2XP1;
    
    } else if ( drpin_opcode == OP_getsec) {

        pin_opcode = XED_ICLASS_GETSEC;
    
    } else if ( drpin_opcode == OP_haddpd) {

        pin_opcode = XED_ICLASS_HADDPD;
    
    } else if ( drpin_opcode == OP_haddps) {

        pin_opcode = XED_ICLASS_HADDPS;
    
    } else if ( drpin_opcode == OP_hlt) {

        pin_opcode = XED_ICLASS_HLT;
    
    } else if ( drpin_opcode == OP_hsubpd) {

        pin_opcode = XED_ICLASS_HSUBPD;
    
    } else if ( drpin_opcode == OP_hsubps) {

        pin_opcode = XED_ICLASS_HSUBPS;
    
    } else if ( drpin_opcode == OP_idiv) {

        pin_opcode = XED_ICLASS_IDIV;
    
    } else if ( drpin_opcode == OP_imul) {

        pin_opcode = XED_ICLASS_IMUL;
    
    } else if ( drpin_opcode == OP_in) {

        pin_opcode = XED_ICLASS_IN;
    
    } else if ( drpin_opcode == OP_inc) {

        pin_opcode = XED_ICLASS_INC;
    
    } else if ( drpin_opcode == OP_insertps) {

        pin_opcode = XED_ICLASS_INSERTPS;
    
    } else if ( drpin_opcode == OP_insertq) {

        pin_opcode = XED_ICLASS_INSERTQ;
    
    } else if ( drpin_opcode == OP_int) {

        pin_opcode = XED_ICLASS_INT;
    
    } else if ( drpin_opcode == OP_int1) {

        pin_opcode = XED_ICLASS_INT1;
    
    } else if ( drpin_opcode == OP_int3) {

        pin_opcode = XED_ICLASS_INT3;
    
    } else if ( drpin_opcode == OP_into) {

        pin_opcode = XED_ICLASS_INTO;
    
    } else if ( drpin_opcode == OP_invd) {

        pin_opcode = XED_ICLASS_INVD;
    
    } else if ( drpin_opcode == OP_invept) {

        pin_opcode = XED_ICLASS_INVEPT;
    
    } else if ( drpin_opcode == OP_invlpg) {

        pin_opcode = XED_ICLASS_INVLPG;
    
    } else if ( drpin_opcode == OP_invlpga) {

        pin_opcode = XED_ICLASS_INVLPGA;
    
    } else if ( drpin_opcode == OP_invpcid) {

        pin_opcode = XED_ICLASS_INVPCID;
    
    } else if ( drpin_opcode == OP_invvpid) {

        pin_opcode = XED_ICLASS_INVVPID;
    
    } else if ( drpin_opcode == OP_iret) {

        pin_opcode = XED_ICLASS_IRET;
    
    } else if ( drpin_opcode == OP_jb) {

        pin_opcode = XED_ICLASS_JB;

    } else if ( drpin_opcode == OP_jb_short) {

        pin_opcode = XED_ICLASS_JB;
    
    } else if ( drpin_opcode == OP_jbe) {

        pin_opcode = XED_ICLASS_JBE;

    } else if ( drpin_opcode == OP_jbe_short) {

        pin_opcode = XED_ICLASS_JBE;

    } else if ( drpin_opcode == OP_jl) {

        pin_opcode = XED_ICLASS_JL;

    } else if ( drpin_opcode == OP_jl_short) {

        pin_opcode = XED_ICLASS_JL;
    
    } else if ( drpin_opcode == OP_jle) {

        pin_opcode = XED_ICLASS_JLE;

    } else if ( drpin_opcode == OP_jle_short) {

        pin_opcode = XED_ICLASS_JLE;
    
    } else if ( drpin_opcode == OP_jmp) {

        pin_opcode = XED_ICLASS_JMP;

    } else if ( drpin_opcode == OP_jmp_short) {

        pin_opcode = XED_ICLASS_JMP;

    } else if ( drpin_opcode == OP_jmp_ind) {

        pin_opcode = XED_ICLASS_JMP;
    
    } else if ( drpin_opcode == OP_jmp_far_ind) {

        pin_opcode = XED_ICLASS_JMP_FAR;

    } else if ( drpin_opcode == OP_jmp_far) {

        pin_opcode = XED_ICLASS_JMP_FAR;
    
    } else if ( drpin_opcode == OP_jnb) {

        pin_opcode = XED_ICLASS_JNB;

    } else if ( drpin_opcode == OP_jnb_short) {

        pin_opcode = XED_ICLASS_JNB;
    
    } else if ( drpin_opcode == OP_jnbe) {

        pin_opcode = XED_ICLASS_JNBE;

    } else if ( drpin_opcode == OP_jnbe_short) {

        pin_opcode = XED_ICLASS_JNBE;
    
    } else if ( drpin_opcode == OP_jnl) {

        pin_opcode = XED_ICLASS_JNL;
    
    } else if ( drpin_opcode == OP_jnl_short) {

        pin_opcode = XED_ICLASS_JNL;
    
    } else if ( drpin_opcode == OP_jnle) {

        pin_opcode = XED_ICLASS_JNLE;
    
    } else if ( drpin_opcode == OP_jnle_short) {

        pin_opcode = XED_ICLASS_JNLE;
    
    } else if ( drpin_opcode == OP_jno) {

        pin_opcode = XED_ICLASS_JNO;
    
    } else if ( drpin_opcode == OP_jno_short) {

        pin_opcode = XED_ICLASS_JNO;
    
    } else if ( drpin_opcode == OP_jnp) {

        pin_opcode = XED_ICLASS_JNP;
    
    } else if ( drpin_opcode == OP_jnp_short) {

        pin_opcode = XED_ICLASS_JNP;
    
    } else if ( drpin_opcode == OP_jns) {

        pin_opcode = XED_ICLASS_JNS;
    
    } else if ( drpin_opcode == OP_jns_short) {

        pin_opcode = XED_ICLASS_JNS;
    
    } else if ( drpin_opcode == OP_jnz) {

        pin_opcode = XED_ICLASS_JNZ;

    } else if ( drpin_opcode == OP_jnz_short) {

        pin_opcode = XED_ICLASS_JNZ;
    
    } else if ( drpin_opcode == OP_jo) {

        pin_opcode = XED_ICLASS_JO;

    } else if ( drpin_opcode == OP_jo_short) {

        pin_opcode = XED_ICLASS_JO;
    
    } else if ( drpin_opcode == OP_jp) {

        pin_opcode = XED_ICLASS_JP;

    } else if ( drpin_opcode == OP_jp_short) {

        pin_opcode = XED_ICLASS_JP;
    
    } else if ( drpin_opcode == OP_jrcxz) {

        pin_opcode = XED_ICLASS_JRCXZ;
    
    } else if ( drpin_opcode == OP_js) {

        pin_opcode = XED_ICLASS_JS;

    } else if ( drpin_opcode == OP_js_short) {

        pin_opcode = XED_ICLASS_JS;
    
    } else if ( drpin_opcode == OP_jz) {

        pin_opcode = XED_ICLASS_JZ;

    } else if ( drpin_opcode == OP_jz_short) {

        pin_opcode = XED_ICLASS_JZ;
    
    } else if ( drpin_opcode == OP_kaddb) {

        pin_opcode = XED_ICLASS_KADDB;
    
    } else if ( drpin_opcode == OP_kaddd) {

        pin_opcode = XED_ICLASS_KADDD;
    
    } else if ( drpin_opcode == OP_kaddq) {

        pin_opcode = XED_ICLASS_KADDQ;
    
    } else if ( drpin_opcode == OP_kaddw) {

        pin_opcode = XED_ICLASS_KADDW;
    
    } else if ( drpin_opcode == OP_kandb) {

        pin_opcode = XED_ICLASS_KANDB;
    
    } else if ( drpin_opcode == OP_kandd) {

        pin_opcode = XED_ICLASS_KANDD;
    
    } else if ( drpin_opcode == OP_kandnb) {

        pin_opcode = XED_ICLASS_KANDNB;
    
    } else if ( drpin_opcode == OP_kandnd) {

        pin_opcode = XED_ICLASS_KANDND;
    
    } else if ( drpin_opcode == OP_kandnq) {

        pin_opcode = XED_ICLASS_KANDNQ;
    
    } else if ( drpin_opcode == OP_kandnw) {

        pin_opcode = XED_ICLASS_KANDNW;
    
    } else if ( drpin_opcode == OP_kandq) {

        pin_opcode = XED_ICLASS_KANDQ;
    
    } else if ( drpin_opcode == OP_kandw) {

        pin_opcode = XED_ICLASS_KANDW;
    
    } else if ( drpin_opcode == OP_kmovb) {

        pin_opcode = XED_ICLASS_KMOVB;
    
    } else if ( drpin_opcode == OP_kmovd) {

        pin_opcode = XED_ICLASS_KMOVD;
    
    } else if ( drpin_opcode == OP_kmovq) {

        pin_opcode = XED_ICLASS_KMOVQ;
    
    } else if ( drpin_opcode == OP_kmovw) {

        pin_opcode = XED_ICLASS_KMOVW;
    
    } else if ( drpin_opcode == OP_knotb) {

        pin_opcode = XED_ICLASS_KNOTB;
    
    } else if ( drpin_opcode == OP_knotd) {

        pin_opcode = XED_ICLASS_KNOTD;
    
    } else if ( drpin_opcode == OP_knotq) {

        pin_opcode = XED_ICLASS_KNOTQ;
    
    } else if ( drpin_opcode == OP_knotw) {

        pin_opcode = XED_ICLASS_KNOTW;
    
    } else if ( drpin_opcode == OP_korb) {

        pin_opcode = XED_ICLASS_KORB;
    
    } else if ( drpin_opcode == OP_kord) {

        pin_opcode = XED_ICLASS_KORD;
    
    } else if ( drpin_opcode == OP_korq) {

        pin_opcode = XED_ICLASS_KORQ;
    
    } else if ( drpin_opcode == OP_kortestb) {

        pin_opcode = XED_ICLASS_KORTESTB;
    
    } else if ( drpin_opcode == OP_kortestd) {

        pin_opcode = XED_ICLASS_KORTESTD;
    
    } else if ( drpin_opcode == OP_kortestq) {

        pin_opcode = XED_ICLASS_KORTESTQ;
    
    } else if ( drpin_opcode == OP_kortestw) {

        pin_opcode = XED_ICLASS_KORTESTW;
    
    } else if ( drpin_opcode == OP_korw) {

        pin_opcode = XED_ICLASS_KORW;
    
    } else if ( drpin_opcode == OP_kshiftlb) {

        pin_opcode = XED_ICLASS_KSHIFTLB;
    
    } else if ( drpin_opcode == OP_kshiftld) {

        pin_opcode = XED_ICLASS_KSHIFTLD;
    
    } else if ( drpin_opcode == OP_kshiftlq) {

        pin_opcode = XED_ICLASS_KSHIFTLQ;
    
    } else if ( drpin_opcode == OP_kshiftlw) {

        pin_opcode = XED_ICLASS_KSHIFTLW;
    
    } else if ( drpin_opcode == OP_kshiftrb) {

        pin_opcode = XED_ICLASS_KSHIFTRB;
    
    } else if ( drpin_opcode == OP_kshiftrd) {

        pin_opcode = XED_ICLASS_KSHIFTRD;
    
    } else if ( drpin_opcode == OP_kshiftrq) {

        pin_opcode = XED_ICLASS_KSHIFTRQ;
    
    } else if ( drpin_opcode == OP_kshiftrw) {

        pin_opcode = XED_ICLASS_KSHIFTRW;
    
    } else if ( drpin_opcode == OP_ktestb) {

        pin_opcode = XED_ICLASS_KTESTB;
    
    } else if ( drpin_opcode == OP_ktestd) {

        pin_opcode = XED_ICLASS_KTESTD;
    
    } else if ( drpin_opcode == OP_ktestq) {

        pin_opcode = XED_ICLASS_KTESTQ;
    
    } else if ( drpin_opcode == OP_ktestw) {

        pin_opcode = XED_ICLASS_KTESTW;
    
    } else if ( drpin_opcode == OP_kunpckbw) {

        pin_opcode = XED_ICLASS_KUNPCKBW;
    
    } else if ( drpin_opcode == OP_kunpckdq) {

        pin_opcode = XED_ICLASS_KUNPCKDQ;
    
    } else if ( drpin_opcode == OP_kunpckwd) {

        pin_opcode = XED_ICLASS_KUNPCKWD;
    
    } else if ( drpin_opcode == OP_kxnorb) {

        pin_opcode = XED_ICLASS_KXNORB;
    
    } else if ( drpin_opcode == OP_kxnord) {

        pin_opcode = XED_ICLASS_KXNORD;
    
    } else if ( drpin_opcode == OP_kxnorq) {

        pin_opcode = XED_ICLASS_KXNORQ;
    
    } else if ( drpin_opcode == OP_kxnorw) {

        pin_opcode = XED_ICLASS_KXNORW;
    
    } else if ( drpin_opcode == OP_kxorb) {

        pin_opcode = XED_ICLASS_KXORB;
    
    } else if ( drpin_opcode == OP_kxord) {

        pin_opcode = XED_ICLASS_KXORD;
    
    } else if ( drpin_opcode == OP_kxorq) {

        pin_opcode = XED_ICLASS_KXORQ;
    
    } else if ( drpin_opcode == OP_kxorw) {

        pin_opcode = XED_ICLASS_KXORW;
    
    } else if ( drpin_opcode == OP_lahf) {

        pin_opcode = XED_ICLASS_LAHF;
    
    } else if ( drpin_opcode == OP_lar) {

        pin_opcode = XED_ICLASS_LAR;
    
    } else if ( drpin_opcode == OP_lddqu) {

        pin_opcode = XED_ICLASS_LDDQU;
    
    } else if ( drpin_opcode == OP_ldmxcsr) {

        pin_opcode = XED_ICLASS_LDMXCSR;
    
    } else if ( drpin_opcode == OP_lds) {

        pin_opcode = XED_ICLASS_LDS;
    
    } else if ( drpin_opcode == OP_lea) {

        pin_opcode = XED_ICLASS_LEA;
    
    } else if ( drpin_opcode == OP_leave) {

        pin_opcode = XED_ICLASS_LEAVE;
    
    } else if ( drpin_opcode == OP_les) {

        pin_opcode = XED_ICLASS_LES;
    
    } else if ( drpin_opcode == OP_lfence) {

        pin_opcode = XED_ICLASS_LFENCE;
    
    } else if ( drpin_opcode == OP_lfs) {

        pin_opcode = XED_ICLASS_LFS;
    
    } else if ( drpin_opcode == OP_lgdt) {

        pin_opcode = XED_ICLASS_LGDT;
    
    } else if ( drpin_opcode == OP_lgs) {

        pin_opcode = XED_ICLASS_LGS;
    
    } else if ( drpin_opcode == OP_lidt) {

        pin_opcode = XED_ICLASS_LIDT;
    
    } else if ( drpin_opcode == OP_lldt) {

        pin_opcode = XED_ICLASS_LLDT;
    
    } else if ( drpin_opcode == OP_llwpcb) {

        pin_opcode = XED_ICLASS_LLWPCB;
    
    } else if ( drpin_opcode == OP_lmsw) {

        pin_opcode = XED_ICLASS_LMSW;
    
    } else if ( drpin_opcode == OP_loop) {

        pin_opcode = XED_ICLASS_LOOP;
    
    } else if ( drpin_opcode == OP_loope) {

        pin_opcode = XED_ICLASS_LOOPE;
    
    } else if ( drpin_opcode == OP_loopne) {

        pin_opcode = XED_ICLASS_LOOPNE;
    
    } else if ( drpin_opcode == OP_lsl) {

        pin_opcode = XED_ICLASS_LSL;
    
    } else if ( drpin_opcode == OP_lss) {

        pin_opcode = XED_ICLASS_LSS;
    
    } else if ( drpin_opcode == OP_ltr) {

        pin_opcode = XED_ICLASS_LTR;
    
    } else if ( drpin_opcode == OP_lwpins) {

        pin_opcode = XED_ICLASS_LWPINS;
    
    } else if ( drpin_opcode == OP_lwpval) {

        pin_opcode = XED_ICLASS_LWPVAL;
    
    } else if ( drpin_opcode == OP_lzcnt) {

        pin_opcode = XED_ICLASS_LZCNT;
    
    } else if ( drpin_opcode == OP_maskmovdqu) {

        pin_opcode = XED_ICLASS_MASKMOVDQU;
    
    } else if ( drpin_opcode == OP_maskmovq) {

        pin_opcode = XED_ICLASS_MASKMOVQ;
    
    } else if ( drpin_opcode == OP_maxpd) {

        pin_opcode = XED_ICLASS_MAXPD;
    
    } else if ( drpin_opcode == OP_maxps) {

        pin_opcode = XED_ICLASS_MAXPS;
    
    } else if ( drpin_opcode == OP_maxsd) {

        pin_opcode = XED_ICLASS_MAXSD;
    
    } else if ( drpin_opcode == OP_maxss) {

        pin_opcode = XED_ICLASS_MAXSS;
    
    } else if ( drpin_opcode == OP_mfence) {

        pin_opcode = XED_ICLASS_MFENCE;
    
    } else if ( drpin_opcode == OP_minpd) {

        pin_opcode = XED_ICLASS_MINPD;
    
    } else if ( drpin_opcode == OP_minps) {

        pin_opcode = XED_ICLASS_MINPS;
    
    } else if ( drpin_opcode == OP_minsd) {

        pin_opcode = XED_ICLASS_MINSD;
    
    } else if ( drpin_opcode == OP_minss) {

        pin_opcode = XED_ICLASS_MINSS;
    
    } else if ( drpin_opcode == OP_monitor) {

        pin_opcode = XED_ICLASS_MONITOR;
    
    } else if ( drpin_opcode == OP_mov_imm || drpin_opcode == OP_mov_ld || drpin_opcode == OP_mov_priv || drpin_opcode == OP_mov_priv || drpin_opcode == OP_mov_seg || drpin_opcode == OP_mov_st) {

        pin_opcode = XED_ICLASS_MOV;
    
    } else if ( drpin_opcode == OP_movapd) {

        pin_opcode = XED_ICLASS_MOVAPD;
    
    } else if ( drpin_opcode == OP_movaps) {

        pin_opcode = XED_ICLASS_MOVAPS;
    
    } else if ( drpin_opcode == OP_movbe) {

        pin_opcode = XED_ICLASS_MOVBE;
    
    } else if ( drpin_opcode == OP_movd) {

        pin_opcode = XED_ICLASS_MOVD;
    
    } else if ( drpin_opcode == OP_movddup) {

        pin_opcode = XED_ICLASS_MOVDDUP;
    
    } else if ( drpin_opcode == OP_movdq2q) {

        pin_opcode = XED_ICLASS_MOVDQ2Q;
    
    } else if ( drpin_opcode == OP_movdqa) {

        pin_opcode = XED_ICLASS_MOVDQA;
    
    } else if ( drpin_opcode == OP_movdqu) {

        pin_opcode = XED_ICLASS_MOVDQU;
    
    } else if ( drpin_opcode == OP_movhlps) {

        pin_opcode = XED_ICLASS_MOVHLPS;
    
    } else if ( drpin_opcode == OP_movhpd) {

        pin_opcode = XED_ICLASS_MOVHPD;
    
    } else if ( drpin_opcode == OP_movhps) {

        pin_opcode = XED_ICLASS_MOVHPS;
    
    } else if ( drpin_opcode == OP_movlhps) {

        pin_opcode = XED_ICLASS_MOVLHPS;
    
    } else if ( drpin_opcode == OP_movlpd) {

        pin_opcode = XED_ICLASS_MOVLPD;
    
    } else if ( drpin_opcode == OP_movlps) {

        pin_opcode = XED_ICLASS_MOVLPS;
    
    } else if ( drpin_opcode == OP_movmskpd) {

        pin_opcode = XED_ICLASS_MOVMSKPD;
    
    } else if ( drpin_opcode == OP_movmskps) {

        pin_opcode = XED_ICLASS_MOVMSKPS;
    
    } else if ( drpin_opcode == OP_movntdq) {

        pin_opcode = XED_ICLASS_MOVNTDQ;
    
    } else if ( drpin_opcode == OP_movntdqa) {

        pin_opcode = XED_ICLASS_MOVNTDQA;
    
    } else if ( drpin_opcode == OP_movnti) {

        pin_opcode = XED_ICLASS_MOVNTI;
    
    } else if ( drpin_opcode == OP_movntpd) {

        pin_opcode = XED_ICLASS_MOVNTPD;
    
    } else if ( drpin_opcode == OP_movntps) {

        pin_opcode = XED_ICLASS_MOVNTPS;
    
    } else if ( drpin_opcode == OP_movntq) {

        pin_opcode = XED_ICLASS_MOVNTQ;
    
    } else if ( drpin_opcode == OP_movntsd) {

        pin_opcode = XED_ICLASS_MOVNTSD;
    
    } else if ( drpin_opcode == OP_movntss) {

        pin_opcode = XED_ICLASS_MOVNTSS;
    
    } else if ( drpin_opcode == OP_movq) {

        pin_opcode = XED_ICLASS_MOVQ;
    
    } else if ( drpin_opcode == OP_movq2dq) {

        pin_opcode = XED_ICLASS_MOVQ2DQ;
    
    // } else if ( drpin_opcode == OP_movsb) {

    //     pin_opcode = XED_ICLASS_MOVSB;
    
    } else if ( drpin_opcode == OP_movsd) {

        pin_opcode = XED_ICLASS_MOVSD;
    
    // } else if ( drpin_opcode == OP_movsd_xmm) {

    //     pin_opcode = XED_ICLASS_MOVSD_XMM;
    
    } else if ( drpin_opcode == OP_movshdup) {

        pin_opcode = XED_ICLASS_MOVSHDUP;
    
    } else if ( drpin_opcode == OP_movsldup) {

        pin_opcode = XED_ICLASS_MOVSLDUP;
    
    // } else if ( drpin_opcode == OP_movsq) {

    //     pin_opcode = XED_ICLASS_MOVSQ;
    
    } else if ( drpin_opcode == OP_movss) {

        pin_opcode = XED_ICLASS_MOVSS;
    
    // } else if ( drpin_opcode == OP_movsw) {

    //     pin_opcode = XED_ICLASS_MOVSW;
    
    } else if ( drpin_opcode == OP_movsx) {

        pin_opcode = XED_ICLASS_MOVSX;
    
    } else if ( drpin_opcode == OP_movsxd) {

        pin_opcode = XED_ICLASS_MOVSXD;
    
    } else if ( drpin_opcode == OP_movupd) {

        pin_opcode = XED_ICLASS_MOVUPD;
    
    } else if ( drpin_opcode == OP_movups) {

        pin_opcode = XED_ICLASS_MOVUPS;
    
    } else if ( drpin_opcode == OP_movzx) {

        pin_opcode = XED_ICLASS_MOVZX;
    
    // } else if ( drpin_opcode == OP_mov_cr) {

    //     pin_opcode = XED_ICLASS_MOV_CR;
    
    // } else if ( drpin_opcode == OP_mov_dr) {

    //     pin_opcode = XED_ICLASS_MOV_DR;
    
    } else if ( drpin_opcode == OP_mpsadbw) {

        pin_opcode = XED_ICLASS_MPSADBW;
    
    } else if ( drpin_opcode == OP_mul) {

        pin_opcode = XED_ICLASS_MUL;
    
    } else if ( drpin_opcode == OP_mulpd) {

        pin_opcode = XED_ICLASS_MULPD;
    
    } else if ( drpin_opcode == OP_mulps) {

        pin_opcode = XED_ICLASS_MULPS;
    
    } else if ( drpin_opcode == OP_mulsd) {

        pin_opcode = XED_ICLASS_MULSD;
    
    } else if ( drpin_opcode == OP_mulss) {

        pin_opcode = XED_ICLASS_MULSS;
    
    } else if ( drpin_opcode == OP_mulx) {

        pin_opcode = XED_ICLASS_MULX;
    
    } else if ( drpin_opcode == OP_mwait) {

        pin_opcode = XED_ICLASS_MWAIT;
    
    } else if ( drpin_opcode == OP_neg) {

        pin_opcode = XED_ICLASS_NEG;
    
    } else if ( drpin_opcode == OP_nop) {

        pin_opcode = XED_ICLASS_NOP;

    } else if ( drpin_opcode == OP_nop_modrm) {

        pin_opcode = XED_ICLASS_NOP;

    // } else if ( drpin_opcode == OP_nop2) {

    //     pin_opcode = XED_ICLASS_NOP2;
    
    // } else if ( drpin_opcode == OP_nop3) {

    //     pin_opcode = XED_ICLASS_NOP3;
    
    // } else if ( drpin_opcode == OP_nop4) {

    //     pin_opcode = XED_ICLASS_NOP4;
    
    // } else if ( drpin_opcode == OP_nop5) {

    //     pin_opcode = XED_ICLASS_NOP5;
    
    // } else if ( drpin_opcode == OP_nop6) {

    //     pin_opcode = XED_ICLASS_NOP6;
    
    // } else if ( drpin_opcode == OP_nop7) {

    //     pin_opcode = XED_ICLASS_NOP7;
    
    // } else if ( drpin_opcode == OP_nop8) {

    //     pin_opcode = XED_ICLASS_NOP8;
    
    // } else if ( drpin_opcode == OP_nop9) {

    //     pin_opcode = XED_ICLASS_NOP9;
    
    } else if ( drpin_opcode == OP_not) {

        pin_opcode = XED_ICLASS_NOT;
    
    } else if ( drpin_opcode == OP_or) {

        pin_opcode = XED_ICLASS_OR;
    
    } else if ( drpin_opcode == OP_orpd) {

        pin_opcode = XED_ICLASS_ORPD;
    
    } else if ( drpin_opcode == OP_orps) {

        pin_opcode = XED_ICLASS_ORPS;
    
    } else if ( drpin_opcode == OP_out) {

        pin_opcode = XED_ICLASS_OUT;
    
    // } else if ( drpin_opcode == OP_outsb) {

    //     pin_opcode = XED_ICLASS_OUTSB;
    
    // } else if ( drpin_opcode == OP_outsd) {

    //     pin_opcode = XED_ICLASS_OUTSD;
    
    // } else if ( drpin_opcode == OP_outsw) {

    //     pin_opcode = XED_ICLASS_OUTSW;
    
    } else if ( drpin_opcode == OP_pabsb) {

        pin_opcode = XED_ICLASS_PABSB;
    
    } else if ( drpin_opcode == OP_pabsd) {

        pin_opcode = XED_ICLASS_PABSD;
    
    } else if ( drpin_opcode == OP_pabsw) {

        pin_opcode = XED_ICLASS_PABSW;
    
    } else if ( drpin_opcode == OP_packssdw) {

        pin_opcode = XED_ICLASS_PACKSSDW;
    
    } else if ( drpin_opcode == OP_packsswb) {

        pin_opcode = XED_ICLASS_PACKSSWB;
    
    } else if ( drpin_opcode == OP_packusdw) {

        pin_opcode = XED_ICLASS_PACKUSDW;
    
    } else if ( drpin_opcode == OP_packuswb) {

        pin_opcode = XED_ICLASS_PACKUSWB;
    
    } else if ( drpin_opcode == OP_paddb) {

        pin_opcode = XED_ICLASS_PADDB;
    
    } else if ( drpin_opcode == OP_paddd) {

        pin_opcode = XED_ICLASS_PADDD;
    
    } else if ( drpin_opcode == OP_paddq) {

        pin_opcode = XED_ICLASS_PADDQ;
    
    } else if ( drpin_opcode == OP_paddsb) {

        pin_opcode = XED_ICLASS_PADDSB;
    
    } else if ( drpin_opcode == OP_paddsw) {

        pin_opcode = XED_ICLASS_PADDSW;
    
    } else if ( drpin_opcode == OP_paddusb) {

        pin_opcode = XED_ICLASS_PADDUSB;
    
    } else if ( drpin_opcode == OP_paddusw) {

        pin_opcode = XED_ICLASS_PADDUSW;
    
    } else if ( drpin_opcode == OP_paddw) {

        pin_opcode = XED_ICLASS_PADDW;
    
    } else if ( drpin_opcode == OP_palignr) {

        pin_opcode = XED_ICLASS_PALIGNR;
    
    } else if ( drpin_opcode == OP_pand) {

        pin_opcode = XED_ICLASS_PAND;
    
    } else if ( drpin_opcode == OP_pandn) {

        pin_opcode = XED_ICLASS_PANDN;
    
    } else if ( drpin_opcode == OP_pause) {

        pin_opcode = XED_ICLASS_PAUSE;
    
    } else if ( drpin_opcode == OP_pavgb) {

        pin_opcode = XED_ICLASS_PAVGB;
    
    } else if ( drpin_opcode == OP_pavgusb) {

        pin_opcode = XED_ICLASS_PAVGUSB;
    
    } else if ( drpin_opcode == OP_pavgw) {

        pin_opcode = XED_ICLASS_PAVGW;
    
    } else if ( drpin_opcode == OP_pblendvb) {

        pin_opcode = XED_ICLASS_PBLENDVB;
    
    } else if ( drpin_opcode == OP_pblendw) {

        pin_opcode = XED_ICLASS_PBLENDW;
    
    } else if ( drpin_opcode == OP_pclmulqdq) {

        pin_opcode = XED_ICLASS_PCLMULQDQ;
    
    } else if ( drpin_opcode == OP_pcmpeqb) {

        pin_opcode = XED_ICLASS_PCMPEQB;
    
    } else if ( drpin_opcode == OP_pcmpeqd) {

        pin_opcode = XED_ICLASS_PCMPEQD;
    
    } else if ( drpin_opcode == OP_pcmpeqq) {

        pin_opcode = XED_ICLASS_PCMPEQQ;
    
    } else if ( drpin_opcode == OP_pcmpeqw) {

        pin_opcode = XED_ICLASS_PCMPEQW;
    
    } else if ( drpin_opcode == OP_pcmpestri) {

        pin_opcode = XED_ICLASS_PCMPESTRI;
    
    } else if ( drpin_opcode == OP_pcmpestrm) {

        pin_opcode = XED_ICLASS_PCMPESTRM;
    
    } else if ( drpin_opcode == OP_pcmpgtb) {

        pin_opcode = XED_ICLASS_PCMPGTB;
    
    } else if ( drpin_opcode == OP_pcmpgtd) {

        pin_opcode = XED_ICLASS_PCMPGTD;
    
    } else if ( drpin_opcode == OP_pcmpgtq) {

        pin_opcode = XED_ICLASS_PCMPGTQ;
    
    } else if ( drpin_opcode == OP_pcmpgtw) {

        pin_opcode = XED_ICLASS_PCMPGTW;
    
    } else if ( drpin_opcode == OP_pcmpistri) {

        pin_opcode = XED_ICLASS_PCMPISTRI;
    
    } else if ( drpin_opcode == OP_pcmpistrm) {

        pin_opcode = XED_ICLASS_PCMPISTRM;
    
    // } else if ( drpin_opcode == OP_pcommit) {

    //     pin_opcode = XED_ICLASS_PCOMMIT;
    
    } else if ( drpin_opcode == OP_pdep) {

        pin_opcode = XED_ICLASS_PDEP;
    
    } else if ( drpin_opcode == OP_pext) {

        pin_opcode = XED_ICLASS_PEXT;
    
    } else if ( drpin_opcode == OP_pextrb) {

        pin_opcode = XED_ICLASS_PEXTRB;
    
    } else if ( drpin_opcode == OP_pextrd) {

        pin_opcode = XED_ICLASS_PEXTRD;
    
    } else if ( drpin_opcode == OP_pextrq) {

        pin_opcode = XED_ICLASS_PEXTRQ;
    
    } else if ( drpin_opcode == OP_pextrw) {

        pin_opcode = XED_ICLASS_PEXTRW;
    
    // } else if ( drpin_opcode == OP_pextrw_sse4) {

    //     pin_opcode = XED_ICLASS_PEXTRW_SSE4;
    
    } else if ( drpin_opcode == OP_pf2id) {

        pin_opcode = XED_ICLASS_PF2ID;
    
    } else if ( drpin_opcode == OP_pf2iw) {

        pin_opcode = XED_ICLASS_PF2IW;
    
    } else if ( drpin_opcode == OP_pfacc) {

        pin_opcode = XED_ICLASS_PFACC;
    
    } else if ( drpin_opcode == OP_pfadd) {

        pin_opcode = XED_ICLASS_PFADD;
    
    } else if ( drpin_opcode == OP_pfcmpeq) {

        pin_opcode = XED_ICLASS_PFCMPEQ;
    
    } else if ( drpin_opcode == OP_pfcmpge) {

        pin_opcode = XED_ICLASS_PFCMPGE;
    
    } else if ( drpin_opcode == OP_pfcmpgt) {

        pin_opcode = XED_ICLASS_PFCMPGT;
    
    // } else if ( drpin_opcode == OP_pfcpit1) {

    //     pin_opcode = XED_ICLASS_PFCPIT1;
    
    } else if ( drpin_opcode == OP_pfmax) {

        pin_opcode = XED_ICLASS_PFMAX;
    
    } else if ( drpin_opcode == OP_pfmin) {

        pin_opcode = XED_ICLASS_PFMIN;
    
    } else if ( drpin_opcode == OP_pfmul) {

        pin_opcode = XED_ICLASS_PFMUL;
    
    } else if ( drpin_opcode == OP_pfnacc) {

        pin_opcode = XED_ICLASS_PFNACC;
    
    } else if ( drpin_opcode == OP_pfpnacc) {

        pin_opcode = XED_ICLASS_PFPNACC;
    
    } else if ( drpin_opcode == OP_pfrcp) {

        pin_opcode = XED_ICLASS_PFRCP;
    
    } else if ( drpin_opcode == OP_pfrcpit2) {

        pin_opcode = XED_ICLASS_PFRCPIT2;
    
    } else if ( drpin_opcode == OP_pfrsqit1) {

        pin_opcode = XED_ICLASS_PFRSQIT1;
    
    // } else if ( drpin_opcode == OP_pfsqrt) {

    //     pin_opcode = XED_ICLASS_PFSQRT;
    
    } else if ( drpin_opcode == OP_pfsub) {

        pin_opcode = XED_ICLASS_PFSUB;
    
    } else if ( drpin_opcode == OP_pfsubr) {

        pin_opcode = XED_ICLASS_PFSUBR;
    
    } else if ( drpin_opcode == OP_phaddd) {

        pin_opcode = XED_ICLASS_PHADDD;
    
    } else if ( drpin_opcode == OP_phaddsw) {

        pin_opcode = XED_ICLASS_PHADDSW;
    
    } else if ( drpin_opcode == OP_phaddw) {

        pin_opcode = XED_ICLASS_PHADDW;
    
    } else if ( drpin_opcode == OP_phminposuw) {

        pin_opcode = XED_ICLASS_PHMINPOSUW;
    
    } else if ( drpin_opcode == OP_phsubd) {

        pin_opcode = XED_ICLASS_PHSUBD;
    
    } else if ( drpin_opcode == OP_phsubsw) {

        pin_opcode = XED_ICLASS_PHSUBSW;
    
    } else if ( drpin_opcode == OP_phsubw) {

        pin_opcode = XED_ICLASS_PHSUBW;
    
    } else if ( drpin_opcode == OP_pi2fd) {

        pin_opcode = XED_ICLASS_PI2FD;
    
    } else if ( drpin_opcode == OP_pi2fw) {

        pin_opcode = XED_ICLASS_PI2FW;
    
    } else if ( drpin_opcode == OP_pinsrb) {

        pin_opcode = XED_ICLASS_PINSRB;
    
    } else if ( drpin_opcode == OP_pinsrd) {

        pin_opcode = XED_ICLASS_PINSRD;
    
    } else if ( drpin_opcode == OP_pinsrq) {

        pin_opcode = XED_ICLASS_PINSRQ;
    
    } else if ( drpin_opcode == OP_pinsrw) {

        pin_opcode = XED_ICLASS_PINSRW;
    
    } else if ( drpin_opcode == OP_pmaddubsw) {

        pin_opcode = XED_ICLASS_PMADDUBSW;
    
    } else if ( drpin_opcode == OP_pmaddwd) {

        pin_opcode = XED_ICLASS_PMADDWD;
    
    } else if ( drpin_opcode == OP_pmaxsb) {

        pin_opcode = XED_ICLASS_PMAXSB;
    
    } else if ( drpin_opcode == OP_pmaxsd) {

        pin_opcode = XED_ICLASS_PMAXSD;
    
    } else if ( drpin_opcode == OP_pmaxsw) {

        pin_opcode = XED_ICLASS_PMAXSW;
    
    } else if ( drpin_opcode == OP_pmaxub) {

        pin_opcode = XED_ICLASS_PMAXUB;
    
    } else if ( drpin_opcode == OP_pmaxud) {

        pin_opcode = XED_ICLASS_PMAXUD;
    
    } else if ( drpin_opcode == OP_pmaxuw) {

        pin_opcode = XED_ICLASS_PMAXUW;
    
    } else if ( drpin_opcode == OP_pminsb) {

        pin_opcode = XED_ICLASS_PMINSB;
    
    } else if ( drpin_opcode == OP_pminsd) {

        pin_opcode = XED_ICLASS_PMINSD;
    
    } else if ( drpin_opcode == OP_pminsw) {

        pin_opcode = XED_ICLASS_PMINSW;
    
    } else if ( drpin_opcode == OP_pminub) {

        pin_opcode = XED_ICLASS_PMINUB;
    
    } else if ( drpin_opcode == OP_pminud) {

        pin_opcode = XED_ICLASS_PMINUD;
    
    } else if ( drpin_opcode == OP_pminuw) {

        pin_opcode = XED_ICLASS_PMINUW;
    
    } else if ( drpin_opcode == OP_pmovmskb) {

        pin_opcode = XED_ICLASS_PMOVMSKB;
    
    } else if ( drpin_opcode == OP_pmovsxbd) {

        pin_opcode = XED_ICLASS_PMOVSXBD;
    
    } else if ( drpin_opcode == OP_pmovsxbq) {

        pin_opcode = XED_ICLASS_PMOVSXBQ;
    
    } else if ( drpin_opcode == OP_pmovsxbw) {

        pin_opcode = XED_ICLASS_PMOVSXBW;
    
    } else if ( drpin_opcode == OP_pmovsxdq) {

        pin_opcode = XED_ICLASS_PMOVSXDQ;
    
    } else if ( drpin_opcode == OP_pmovsxwd) {

        pin_opcode = XED_ICLASS_PMOVSXWD;
    
    } else if ( drpin_opcode == OP_pmovsxwq) {

        pin_opcode = XED_ICLASS_PMOVSXWQ;
    
    } else if ( drpin_opcode == OP_pmovzxbd) {

        pin_opcode = XED_ICLASS_PMOVZXBD;
    
    } else if ( drpin_opcode == OP_pmovzxbq) {

        pin_opcode = XED_ICLASS_PMOVZXBQ;
    
    } else if ( drpin_opcode == OP_pmovzxbw) {

        pin_opcode = XED_ICLASS_PMOVZXBW;
    
    } else if ( drpin_opcode == OP_pmovzxdq) {

        pin_opcode = XED_ICLASS_PMOVZXDQ;
    
    } else if ( drpin_opcode == OP_pmovzxwd) {

        pin_opcode = XED_ICLASS_PMOVZXWD;
    
    } else if ( drpin_opcode == OP_pmovzxwq) {

        pin_opcode = XED_ICLASS_PMOVZXWQ;
    
    } else if ( drpin_opcode == OP_pmuldq) {

        pin_opcode = XED_ICLASS_PMULDQ;
    
    } else if ( drpin_opcode == OP_pmulhrsw) {

        pin_opcode = XED_ICLASS_PMULHRSW;
    
    } else if ( drpin_opcode == OP_pmulhrw) {

        pin_opcode = XED_ICLASS_PMULHRW;
    
    } else if ( drpin_opcode == OP_pmulhuw) {

        pin_opcode = XED_ICLASS_PMULHUW;
    
    } else if ( drpin_opcode == OP_pmulhw) {

        pin_opcode = XED_ICLASS_PMULHW;
    
    } else if ( drpin_opcode == OP_pmulld) {

        pin_opcode = XED_ICLASS_PMULLD;
    
    } else if ( drpin_opcode == OP_pmullw) {

        pin_opcode = XED_ICLASS_PMULLW;
    
    } else if ( drpin_opcode == OP_pmuludq) {

        pin_opcode = XED_ICLASS_PMULUDQ;
    
    } else if ( drpin_opcode == OP_pop) {

        pin_opcode = XED_ICLASS_POP;
    
    } else if ( drpin_opcode == OP_popa) {

        pin_opcode = XED_ICLASS_POPA;
    
    // } else if ( drpin_opcode == OP_popad) {

    //     pin_opcode = XED_ICLASS_POPAD;
    
    } else if ( drpin_opcode == OP_popcnt) {

        pin_opcode = XED_ICLASS_POPCNT;
    
    } else if ( drpin_opcode == OP_popf) {

        pin_opcode = XED_ICLASS_POPF;
    
    // } else if ( drpin_opcode == OP_popfd) {

    //     pin_opcode = XED_ICLASS_POPFD;
    
    // } else if ( drpin_opcode == OP_popfq) {

    //     pin_opcode = XED_ICLASS_POPFQ;
    
    } else if ( drpin_opcode == OP_por) {

        pin_opcode = XED_ICLASS_POR;
    
    } else if ( drpin_opcode == OP_prefetchnta) {

        pin_opcode = XED_ICLASS_PREFETCHNTA;
    
    } else if ( drpin_opcode == OP_prefetcht0) {

        pin_opcode = XED_ICLASS_PREFETCHT0;
    
    } else if ( drpin_opcode == OP_prefetcht1) {

        pin_opcode = XED_ICLASS_PREFETCHT1;
    
    } else if ( drpin_opcode == OP_prefetcht2) {

        pin_opcode = XED_ICLASS_PREFETCHT2;
    
    } else if ( drpin_opcode == OP_prefetchw) {

        pin_opcode = XED_ICLASS_PREFETCHW;
    
    // } else if ( drpin_opcode == OP_prefetchwt1) {

    //     pin_opcode = XED_ICLASS_PREFETCHWT1;
    
    // } else if ( drpin_opcode == OP_exclusive) {

    //     pin_opcode = XED_ICLASS_PREFETCH_EXCLUSIVE;
    
    // } else if ( drpin_opcode == OP_prefetch_reserved) {

    //     pin_opcode = XED_ICLASS_PREFETCH_RESERVED;
    
    } else if ( drpin_opcode == OP_psadbw) {

        pin_opcode = XED_ICLASS_PSADBW;
    
    } else if ( drpin_opcode == OP_pshufb) {

        pin_opcode = XED_ICLASS_PSHUFB;
    
    } else if ( drpin_opcode == OP_pshufd) {

        pin_opcode = XED_ICLASS_PSHUFD;
    
    } else if ( drpin_opcode == OP_pshufhw) {

        pin_opcode = XED_ICLASS_PSHUFHW;
    
    } else if ( drpin_opcode == OP_pshuflw) {

        pin_opcode = XED_ICLASS_PSHUFLW;
    
    } else if ( drpin_opcode == OP_pshufw) {

        pin_opcode = XED_ICLASS_PSHUFW;
    
    } else if ( drpin_opcode == OP_psignb) {

        pin_opcode = XED_ICLASS_PSIGNB;
    
    } else if ( drpin_opcode == OP_psignd) {

        pin_opcode = XED_ICLASS_PSIGND;
    
    } else if ( drpin_opcode == OP_psignw) {

        pin_opcode = XED_ICLASS_PSIGNW;
    
    } else if ( drpin_opcode == OP_pslld) {

        pin_opcode = XED_ICLASS_PSLLD;
    
    } else if ( drpin_opcode == OP_pslldq) {

        pin_opcode = XED_ICLASS_PSLLDQ;
    
    } else if ( drpin_opcode == OP_psllq) {

        pin_opcode = XED_ICLASS_PSLLQ;
    
    } else if ( drpin_opcode == OP_psllw) {

        pin_opcode = XED_ICLASS_PSLLW;
    
    } else if ( drpin_opcode == OP_psrad) {

        pin_opcode = XED_ICLASS_PSRAD;
    
    } else if ( drpin_opcode == OP_psraw) {

        pin_opcode = XED_ICLASS_PSRAW;
    
    } else if ( drpin_opcode == OP_psrld) {

        pin_opcode = XED_ICLASS_PSRLD;
    
    } else if ( drpin_opcode == OP_psrldq) {

        pin_opcode = XED_ICLASS_PSRLDQ;
    
    } else if ( drpin_opcode == OP_psrlq) {

        pin_opcode = XED_ICLASS_PSRLQ;
    
    } else if ( drpin_opcode == OP_psrlw) {

        pin_opcode = XED_ICLASS_PSRLW;
    
    } else if ( drpin_opcode == OP_psubb) {

        pin_opcode = XED_ICLASS_PSUBB;
    
    } else if ( drpin_opcode == OP_psubd) {

        pin_opcode = XED_ICLASS_PSUBD;
    
    } else if ( drpin_opcode == OP_psubq) {

        pin_opcode = XED_ICLASS_PSUBQ;
    
    } else if ( drpin_opcode == OP_psubsb) {

        pin_opcode = XED_ICLASS_PSUBSB;
    
    } else if ( drpin_opcode == OP_psubsw) {

        pin_opcode = XED_ICLASS_PSUBSW;
    
    } else if ( drpin_opcode == OP_psubusb) {

        pin_opcode = XED_ICLASS_PSUBUSB;
    
    } else if ( drpin_opcode == OP_psubusw) {

        pin_opcode = XED_ICLASS_PSUBUSW;
    
    } else if ( drpin_opcode == OP_psubw) {

        pin_opcode = XED_ICLASS_PSUBW;
    
    } else if ( drpin_opcode == OP_pswapd) {

        pin_opcode = XED_ICLASS_PSWAPD;
    
    } else if ( drpin_opcode == OP_ptest) {

        pin_opcode = XED_ICLASS_PTEST;
    
    } else if ( drpin_opcode == OP_punpckhbw) {

        pin_opcode = XED_ICLASS_PUNPCKHBW;
    
    } else if ( drpin_opcode == OP_punpckhdq) {

        pin_opcode = XED_ICLASS_PUNPCKHDQ;
    
    } else if ( drpin_opcode == OP_punpckhqdq) {

        pin_opcode = XED_ICLASS_PUNPCKHQDQ;
    
    } else if ( drpin_opcode == OP_punpckhwd) {

        pin_opcode = XED_ICLASS_PUNPCKHWD;
    
    } else if ( drpin_opcode == OP_punpcklbw) {

        pin_opcode = XED_ICLASS_PUNPCKLBW;
    
    } else if ( drpin_opcode == OP_punpckldq) {

        pin_opcode = XED_ICLASS_PUNPCKLDQ;
    
    } else if ( drpin_opcode == OP_punpcklqdq) {

        pin_opcode = XED_ICLASS_PUNPCKLQDQ;
    
    } else if ( drpin_opcode == OP_punpcklwd) {

        pin_opcode = XED_ICLASS_PUNPCKLWD;
    
    } else if ( drpin_opcode == OP_push) {

        pin_opcode = XED_ICLASS_PUSH;
    
    } else if ( drpin_opcode == OP_push_imm) {

        pin_opcode = XED_ICLASS_PUSH;
    
    } else if ( drpin_opcode == OP_pusha) {

        pin_opcode = XED_ICLASS_PUSHA;
    
    // } else if ( drpin_opcode == OP_pushad) {

    //     pin_opcode = XED_ICLASS_PUSHAD;
    
    } else if ( drpin_opcode == OP_pushf) {

        pin_opcode = XED_ICLASS_PUSHF;
    
    // } else if ( drpin_opcode == OP_pushfd) {

    //     pin_opcode = XED_ICLASS_PUSHFD;
    
    // } else if ( drpin_opcode == OP_pushfq) {

    //     pin_opcode = XED_ICLASS_PUSHFQ;
    
    } else if ( drpin_opcode == OP_pxor) {

        pin_opcode = XED_ICLASS_PXOR;
    
    } else if ( drpin_opcode == OP_rcl) {

        pin_opcode = XED_ICLASS_RCL;
    
    } else if ( drpin_opcode == OP_rcpps) {

        pin_opcode = XED_ICLASS_RCPPS;
    
    } else if ( drpin_opcode == OP_rcpss) {

        pin_opcode = XED_ICLASS_RCPSS;
    
    } else if ( drpin_opcode == OP_rcr) {

        pin_opcode = XED_ICLASS_RCR;
    
    } else if ( drpin_opcode == OP_rdfsbase) {

        pin_opcode = XED_ICLASS_RDFSBASE;
    
    } else if ( drpin_opcode == OP_rdgsbase) {

        pin_opcode = XED_ICLASS_RDGSBASE;
    
    } else if ( drpin_opcode == OP_rdmsr) {

        pin_opcode = XED_ICLASS_RDMSR;
    
    } else if ( drpin_opcode == OP_rdpmc) {

        pin_opcode = XED_ICLASS_RDPMC;
    
    } else if ( drpin_opcode == OP_rdrand) {

        pin_opcode = XED_ICLASS_RDRAND;
    
    } else if ( drpin_opcode == OP_rdseed) {

        pin_opcode = XED_ICLASS_RDSEED;
    
    } else if ( drpin_opcode == OP_rdtsc) {

        pin_opcode = XED_ICLASS_RDTSC;
    
    } else if ( drpin_opcode == OP_rdtscp) {

        pin_opcode = XED_ICLASS_RDTSCP;
    
    } else if ( drpin_opcode == OP_ret_far) {

        pin_opcode = XED_ICLASS_RET_FAR;
    
    } else if ( drpin_opcode == OP_ret) {

        pin_opcode = XED_ICLASS_RET_NEAR;
    
    } else if ( drpin_opcode == OP_rol) {

        pin_opcode = XED_ICLASS_ROL;
    
    } else if ( drpin_opcode == OP_ror) {

        pin_opcode = XED_ICLASS_ROR;
    
    } else if ( drpin_opcode == OP_rorx) {

        pin_opcode = XED_ICLASS_RORX;
    
    } else if ( drpin_opcode == OP_roundpd) {

        pin_opcode = XED_ICLASS_ROUNDPD;
    
    } else if ( drpin_opcode == OP_roundps) {

        pin_opcode = XED_ICLASS_ROUNDPS;
    
    } else if ( drpin_opcode == OP_roundsd) {

        pin_opcode = XED_ICLASS_ROUNDSD;
    
    } else if ( drpin_opcode == OP_roundss) {

        pin_opcode = XED_ICLASS_ROUNDSS;
    
    } else if ( drpin_opcode == OP_rsm) {

        pin_opcode = XED_ICLASS_RSM;
    
    } else if ( drpin_opcode == OP_rsqrtps) {

        pin_opcode = XED_ICLASS_RSQRTPS;
    
    } else if ( drpin_opcode == OP_rsqrtss) {

        pin_opcode = XED_ICLASS_RSQRTSS;
    
    } else if ( drpin_opcode == OP_sahf) {

        pin_opcode = XED_ICLASS_SAHF;
    
    } else if ( drpin_opcode == OP_salc) {

        pin_opcode = XED_ICLASS_SALC;
    
    } else if ( drpin_opcode == OP_sar) {

        pin_opcode = XED_ICLASS_SAR;
    
    } else if ( drpin_opcode == OP_sarx) {

        pin_opcode = XED_ICLASS_SARX;
    
    } else if ( drpin_opcode == OP_sbb) {

        pin_opcode = XED_ICLASS_SBB;
    
    // } else if ( drpin_opcode == OP_scasb) {

    //     pin_opcode = XED_ICLASS_SCASB;
    
    // } else if ( drpin_opcode == OP_scasd) {

    //     pin_opcode = XED_ICLASS_SCASD;
    
    // } else if ( drpin_opcode == OP_scasq) {

    //     pin_opcode = XED_ICLASS_SCASQ;
    
    // } else if ( drpin_opcode == OP_scasw) {

    //     pin_opcode = XED_ICLASS_SCASW;
    
    } else if ( drpin_opcode == OP_setb) {

        pin_opcode = XED_ICLASS_SETB;
    
    } else if ( drpin_opcode == OP_setbe) {

        pin_opcode = XED_ICLASS_SETBE;
    
    } else if ( drpin_opcode == OP_setl) {

        pin_opcode = XED_ICLASS_SETL;
    
    } else if ( drpin_opcode == OP_setle) {

        pin_opcode = XED_ICLASS_SETLE;
    
    } else if ( drpin_opcode == OP_setnb) {

        pin_opcode = XED_ICLASS_SETNB;
    
    } else if ( drpin_opcode == OP_setnbe) {

        pin_opcode = XED_ICLASS_SETNBE;
    
    } else if ( drpin_opcode == OP_setnl) {

        pin_opcode = XED_ICLASS_SETNL;
    
    } else if ( drpin_opcode == OP_setnle) {

        pin_opcode = XED_ICLASS_SETNLE;
    
    } else if ( drpin_opcode == OP_setno) {

        pin_opcode = XED_ICLASS_SETNO;
    
    } else if ( drpin_opcode == OP_setnp) {

        pin_opcode = XED_ICLASS_SETNP;
    
    } else if ( drpin_opcode == OP_setns) {

        pin_opcode = XED_ICLASS_SETNS;
    
    } else if ( drpin_opcode == OP_setnz) {

        pin_opcode = XED_ICLASS_SETNZ;
    
    } else if ( drpin_opcode == OP_seto) {

        pin_opcode = XED_ICLASS_SETO;
    
    } else if ( drpin_opcode == OP_setp) {

        pin_opcode = XED_ICLASS_SETP;
    
    } else if ( drpin_opcode == OP_sets) {

        pin_opcode = XED_ICLASS_SETS;
    
    } else if ( drpin_opcode == OP_setz) {

        pin_opcode = XED_ICLASS_SETZ;
    
    } else if ( drpin_opcode == OP_sfence) {

        pin_opcode = XED_ICLASS_SFENCE;
    
    } else if ( drpin_opcode == OP_sgdt) {

        pin_opcode = XED_ICLASS_SGDT;
    
    } else if ( drpin_opcode == OP_sha1msg1) {

        pin_opcode = XED_ICLASS_SHA1MSG1;
    
    } else if ( drpin_opcode == OP_sha1msg2) {

        pin_opcode = XED_ICLASS_SHA1MSG2;
    
    } else if ( drpin_opcode == OP_sha1nexte) {

        pin_opcode = XED_ICLASS_SHA1NEXTE;
    
    } else if ( drpin_opcode == OP_sha1rnds4) {

        pin_opcode = XED_ICLASS_SHA1RNDS4;
    
    } else if ( drpin_opcode == OP_sha256msg1) {

        pin_opcode = XED_ICLASS_SHA256MSG1;
    
    } else if ( drpin_opcode == OP_sha256msg2) {

        pin_opcode = XED_ICLASS_SHA256MSG2;
    
    } else if ( drpin_opcode == OP_sha256rnds2) {

        pin_opcode = XED_ICLASS_SHA256RNDS2;
    
    } else if ( drpin_opcode == OP_shl) {

        pin_opcode = XED_ICLASS_SHL;
    
    } else if ( drpin_opcode == OP_shld) {

        pin_opcode = XED_ICLASS_SHLD;
    
    } else if ( drpin_opcode == OP_shlx) {

        pin_opcode = XED_ICLASS_SHLX;
    
    } else if ( drpin_opcode == OP_shr) {

        pin_opcode = XED_ICLASS_SHR;
    
    } else if ( drpin_opcode == OP_shrd) {

        pin_opcode = XED_ICLASS_SHRD;
    
    } else if ( drpin_opcode == OP_shrx) {

        pin_opcode = XED_ICLASS_SHRX;
    
    } else if ( drpin_opcode == OP_shufpd) {

        pin_opcode = XED_ICLASS_SHUFPD;
    
    } else if ( drpin_opcode == OP_shufps) {

        pin_opcode = XED_ICLASS_SHUFPS;
    
    } else if ( drpin_opcode == OP_sidt) {

        pin_opcode = XED_ICLASS_SIDT;
    
    } else if ( drpin_opcode == OP_skinit) {

        pin_opcode = XED_ICLASS_SKINIT;
    
    } else if ( drpin_opcode == OP_sldt) {

        pin_opcode = XED_ICLASS_SLDT;
    
    } else if ( drpin_opcode == OP_slwpcb) {

        pin_opcode = XED_ICLASS_SLWPCB;
    
    } else if ( drpin_opcode == OP_smsw) {

        pin_opcode = XED_ICLASS_SMSW;
    
    } else if ( drpin_opcode == OP_sqrtpd) {

        pin_opcode = XED_ICLASS_SQRTPD;
    
    } else if ( drpin_opcode == OP_sqrtps) {

        pin_opcode = XED_ICLASS_SQRTPS;
    
    } else if ( drpin_opcode == OP_sqrtsd) {

        pin_opcode = XED_ICLASS_SQRTSD;
    
    } else if ( drpin_opcode == OP_sqrtss) {

        pin_opcode = XED_ICLASS_SQRTSS;
    
    // } else if ( drpin_opcode == OP_stac) {

    //     pin_opcode = XED_ICLASS_STAC;
    
    } else if ( drpin_opcode == OP_stc) {

        pin_opcode = XED_ICLASS_STC;
    
    } else if ( drpin_opcode == OP_std) {

        pin_opcode = XED_ICLASS_STD;
    
    } else if ( drpin_opcode == OP_stgi) {

        pin_opcode = XED_ICLASS_STGI;
    
    } else if ( drpin_opcode == OP_sti) {

        pin_opcode = XED_ICLASS_STI;
    
    } else if ( drpin_opcode == OP_stmxcsr) {

        pin_opcode = XED_ICLASS_STMXCSR;
    
    // } else if ( drpin_opcode == OP_stosb) {

    //     pin_opcode = XED_ICLASS_STOSB;
    
    // } else if ( drpin_opcode == OP_stosd) {

    //     pin_opcode = XED_ICLASS_STOSD;
    
    // } else if ( drpin_opcode == OP_stosq) {

    //     pin_opcode = XED_ICLASS_STOSQ;
    
    // } else if ( drpin_opcode == OP_stosw) {

    //     pin_opcode = XED_ICLASS_STOSW;
    
    } else if ( drpin_opcode == OP_str) {

        pin_opcode = XED_ICLASS_STR;
    
    } else if ( drpin_opcode == OP_sub) {

        pin_opcode = XED_ICLASS_SUB;
    
    } else if ( drpin_opcode == OP_subpd) {

        pin_opcode = XED_ICLASS_SUBPD;
    
    } else if ( drpin_opcode == OP_subps) {

        pin_opcode = XED_ICLASS_SUBPS;
    
    } else if ( drpin_opcode == OP_subsd) {

        pin_opcode = XED_ICLASS_SUBSD;
    
    } else if ( drpin_opcode == OP_subss) {

        pin_opcode = XED_ICLASS_SUBSS;
    
    } else if ( drpin_opcode == OP_swapgs) {

        pin_opcode = XED_ICLASS_SWAPGS;
    
    } else if ( drpin_opcode == OP_syscall) {

        pin_opcode = XED_ICLASS_SYSCALL;
    
    // } else if ( drpin_opcode == OP_syscall_amd) {

    //     pin_opcode = XED_ICLASS_SYSCALL_AMD;
    
    } else if ( drpin_opcode == OP_sysenter) {

        pin_opcode = XED_ICLASS_SYSENTER;
    
    } else if ( drpin_opcode == OP_sysexit) {

        pin_opcode = XED_ICLASS_SYSEXIT;
    
    } else if ( drpin_opcode == OP_sysret) {

        pin_opcode = XED_ICLASS_SYSRET;
    
    // } else if ( drpin_opcode == OP_sysret_amd) {

    //     pin_opcode = XED_ICLASS_SYSRET_AMD;
    
    } else if ( drpin_opcode == OP_t1mskc) {

        pin_opcode = XED_ICLASS_T1MSKC;
    
    } else if ( drpin_opcode == OP_test) {

        pin_opcode = XED_ICLASS_TEST;
    
    } else if ( drpin_opcode == OP_tzcnt) {

        pin_opcode = XED_ICLASS_TZCNT;
    
    } else if ( drpin_opcode == OP_tzmsk) {

        pin_opcode = XED_ICLASS_TZMSK;
    
    } else if ( drpin_opcode == OP_ucomisd) {

        pin_opcode = XED_ICLASS_UCOMISD;
    
    } else if ( drpin_opcode == OP_ucomiss) {

        pin_opcode = XED_ICLASS_UCOMISS;
    
    // } else if ( drpin_opcode == OP_ud2) {

    //     pin_opcode = XED_ICLASS_UD2;
    
    } else if ( drpin_opcode == OP_unpckhpd) {

        pin_opcode = XED_ICLASS_UNPCKHPD;
    
    } else if ( drpin_opcode == OP_unpckhps) {

        pin_opcode = XED_ICLASS_UNPCKHPS;
    
    } else if ( drpin_opcode == OP_unpcklpd) {

        pin_opcode = XED_ICLASS_UNPCKLPD;
    
    } else if ( drpin_opcode == OP_unpcklps) {

        pin_opcode = XED_ICLASS_UNPCKLPS;
    
    } else if ( drpin_opcode == OP_vaddpd) {

        pin_opcode = XED_ICLASS_VADDPD;
    
    } else if ( drpin_opcode == OP_vaddps) {

        pin_opcode = XED_ICLASS_VADDPS;
    
    } else if ( drpin_opcode == OP_vaddsd) {

        pin_opcode = XED_ICLASS_VADDSD;
    
    } else if ( drpin_opcode == OP_vaddss) {

        pin_opcode = XED_ICLASS_VADDSS;
    
    } else if ( drpin_opcode == OP_vaddsubpd) {

        pin_opcode = XED_ICLASS_VADDSUBPD;
    
    } else if ( drpin_opcode == OP_vaddsubps) {

        pin_opcode = XED_ICLASS_VADDSUBPS;
    
    } else if ( drpin_opcode == OP_vaesdec) {

        pin_opcode = XED_ICLASS_VAESDEC;
    
    } else if ( drpin_opcode == OP_vaesdeclast) {

        pin_opcode = XED_ICLASS_VAESDECLAST;
    
    } else if ( drpin_opcode == OP_vaesenc) {

        pin_opcode = XED_ICLASS_VAESENC;
    
    } else if ( drpin_opcode == OP_vaesenclast) {

        pin_opcode = XED_ICLASS_VAESENCLAST;
    
    } else if ( drpin_opcode == OP_vaesimc) {

        pin_opcode = XED_ICLASS_VAESIMC;
    
    } else if ( drpin_opcode == OP_vaeskeygenassist) {

        pin_opcode = XED_ICLASS_VAESKEYGENASSIST;
    
    } else if ( drpin_opcode == OP_valignd) {

        pin_opcode = XED_ICLASS_VALIGND;
    
    } else if ( drpin_opcode == OP_valignq) {

        pin_opcode = XED_ICLASS_VALIGNQ;
    
    } else if ( drpin_opcode == OP_vandnpd) {

        pin_opcode = XED_ICLASS_VANDNPD;
    
    } else if ( drpin_opcode == OP_vandnps) {

        pin_opcode = XED_ICLASS_VANDNPS;
    
    } else if ( drpin_opcode == OP_vandpd) {

        pin_opcode = XED_ICLASS_VANDPD;
    
    } else if ( drpin_opcode == OP_vandps) {

        pin_opcode = XED_ICLASS_VANDPS;
    
    } else if ( drpin_opcode == OP_vblendmpd) {

        pin_opcode = XED_ICLASS_VBLENDMPD;
    
    } else if ( drpin_opcode == OP_vblendmps) {

        pin_opcode = XED_ICLASS_VBLENDMPS;
    
    } else if ( drpin_opcode == OP_vblendpd) {

        pin_opcode = XED_ICLASS_VBLENDPD;
    
    } else if ( drpin_opcode == OP_vblendps) {

        pin_opcode = XED_ICLASS_VBLENDPS;
    
    } else if ( drpin_opcode == OP_vblendvpd) {

        pin_opcode = XED_ICLASS_VBLENDVPD;
    
    } else if ( drpin_opcode == OP_vblendvps) {

        pin_opcode = XED_ICLASS_VBLENDVPS;
    
    } else if ( drpin_opcode == OP_vbroadcastf128) {

        pin_opcode = XED_ICLASS_VBROADCASTF128;
    
    } else if ( drpin_opcode == OP_vbroadcastf32x2) {

        pin_opcode = XED_ICLASS_VBROADCASTF32X2;
    
    } else if ( drpin_opcode == OP_vbroadcastf32x4) {

        pin_opcode = XED_ICLASS_VBROADCASTF32X4;
    
    } else if ( drpin_opcode == OP_vbroadcastf32x8) {

        pin_opcode = XED_ICLASS_VBROADCASTF32X8;
    
    } else if ( drpin_opcode == OP_vbroadcastf64x2) {

        pin_opcode = XED_ICLASS_VBROADCASTF64X2;
    
    } else if ( drpin_opcode == OP_vbroadcastf64x4) {

        pin_opcode = XED_ICLASS_VBROADCASTF64X4;
    
    } else if ( drpin_opcode == OP_vbroadcasti128) {

        pin_opcode = XED_ICLASS_VBROADCASTI128;
    
    } else if ( drpin_opcode == OP_vbroadcasti32x2) {

        pin_opcode = XED_ICLASS_VBROADCASTI32X2;
    
    } else if ( drpin_opcode == OP_vbroadcasti32x4) {

        pin_opcode = XED_ICLASS_VBROADCASTI32X4;
    
    } else if ( drpin_opcode == OP_vbroadcasti32x8) {

        pin_opcode = XED_ICLASS_VBROADCASTI32X8;
    
    } else if ( drpin_opcode == OP_vbroadcasti64x2) {

        pin_opcode = XED_ICLASS_VBROADCASTI64X2;
    
    } else if ( drpin_opcode == OP_vbroadcasti64x4) {

        pin_opcode = XED_ICLASS_VBROADCASTI64X4;
    
    } else if ( drpin_opcode == OP_vbroadcastsd) {

        pin_opcode = XED_ICLASS_VBROADCASTSD;
    
    } else if ( drpin_opcode == OP_vbroadcastss) {

        pin_opcode = XED_ICLASS_VBROADCASTSS;
    
    } else if ( drpin_opcode == OP_vcmppd) {

        pin_opcode = XED_ICLASS_VCMPPD;
    
    } else if ( drpin_opcode == OP_vcmpps) {

        pin_opcode = XED_ICLASS_VCMPPS;
    
    } else if ( drpin_opcode == OP_vcmpsd) {

        pin_opcode = XED_ICLASS_VCMPSD;
    
    } else if ( drpin_opcode == OP_vcmpss) {

        pin_opcode = XED_ICLASS_VCMPSS;
    
    } else if ( drpin_opcode == OP_vcomisd) {

        pin_opcode = XED_ICLASS_VCOMISD;
    
    } else if ( drpin_opcode == OP_vcomiss) {

        pin_opcode = XED_ICLASS_VCOMISS;
    
    } else if ( drpin_opcode == OP_vcompresspd) {

        pin_opcode = XED_ICLASS_VCOMPRESSPD;
    
    } else if ( drpin_opcode == OP_vcompressps) {

        pin_opcode = XED_ICLASS_VCOMPRESSPS;
    
    } else if ( drpin_opcode == OP_vcvtdq2pd) {

        pin_opcode = XED_ICLASS_VCVTDQ2PD;
    
    } else if ( drpin_opcode == OP_vcvtdq2ps) {

        pin_opcode = XED_ICLASS_VCVTDQ2PS;
    
    } else if ( drpin_opcode == OP_vcvtpd2dq) {

        pin_opcode = XED_ICLASS_VCVTPD2DQ;
    
    } else if ( drpin_opcode == OP_vcvtpd2ps) {

        pin_opcode = XED_ICLASS_VCVTPD2PS;
    
    } else if ( drpin_opcode == OP_vcvtpd2qq) {

        pin_opcode = XED_ICLASS_VCVTPD2QQ;
    
    } else if ( drpin_opcode == OP_vcvtpd2udq) {

        pin_opcode = XED_ICLASS_VCVTPD2UDQ;
    
    } else if ( drpin_opcode == OP_vcvtpd2uqq) {

        pin_opcode = XED_ICLASS_VCVTPD2UQQ;
    
    } else if ( drpin_opcode == OP_vcvtph2ps) {

        pin_opcode = XED_ICLASS_VCVTPH2PS;
    
    } else if ( drpin_opcode == OP_vcvtps2dq) {

        pin_opcode = XED_ICLASS_VCVTPS2DQ;
    
    } else if ( drpin_opcode == OP_vcvtps2pd) {

        pin_opcode = XED_ICLASS_VCVTPS2PD;
    
    } else if ( drpin_opcode == OP_vcvtps2ph) {

        pin_opcode = XED_ICLASS_VCVTPS2PH;
    
    } else if ( drpin_opcode == OP_vcvtps2qq) {

        pin_opcode = XED_ICLASS_VCVTPS2QQ;
    
    } else if ( drpin_opcode == OP_vcvtps2udq) {

        pin_opcode = XED_ICLASS_VCVTPS2UDQ;
    
    } else if ( drpin_opcode == OP_vcvtps2uqq) {

        pin_opcode = XED_ICLASS_VCVTPS2UQQ;
    
    } else if ( drpin_opcode == OP_vcvtqq2pd) {

        pin_opcode = XED_ICLASS_VCVTQQ2PD;
    
    } else if ( drpin_opcode == OP_vcvtqq2ps) {

        pin_opcode = XED_ICLASS_VCVTQQ2PS;
    
    } else if ( drpin_opcode == OP_vcvtsd2si) {

        pin_opcode = XED_ICLASS_VCVTSD2SI;
    
    } else if ( drpin_opcode == OP_vcvtsd2ss) {

        pin_opcode = XED_ICLASS_VCVTSD2SS;
    
    } else if ( drpin_opcode == OP_vcvtsd2usi) {

        pin_opcode = XED_ICLASS_VCVTSD2USI;
    
    } else if ( drpin_opcode == OP_vcvtsi2sd) {

        pin_opcode = XED_ICLASS_VCVTSI2SD;
    
    } else if ( drpin_opcode == OP_vcvtsi2ss) {

        pin_opcode = XED_ICLASS_VCVTSI2SS;
    
    } else if ( drpin_opcode == OP_vcvtss2sd) {

        pin_opcode = XED_ICLASS_VCVTSS2SD;
    
    } else if ( drpin_opcode == OP_vcvtss2si) {

        pin_opcode = XED_ICLASS_VCVTSS2SI;
    
    } else if ( drpin_opcode == OP_vcvtss2usi) {

        pin_opcode = XED_ICLASS_VCVTSS2USI;
    
    } else if ( drpin_opcode == OP_vcvttpd2dq) {

        pin_opcode = XED_ICLASS_VCVTTPD2DQ;
    
    } else if ( drpin_opcode == OP_vcvttpd2qq) {

        pin_opcode = XED_ICLASS_VCVTTPD2QQ;
    
    } else if ( drpin_opcode == OP_vcvttpd2udq) {

        pin_opcode = XED_ICLASS_VCVTTPD2UDQ;
    
    } else if ( drpin_opcode == OP_vcvttpd2uqq) {

        pin_opcode = XED_ICLASS_VCVTTPD2UQQ;
    
    } else if ( drpin_opcode == OP_vcvttps2dq) {

        pin_opcode = XED_ICLASS_VCVTTPS2DQ;
    
    } else if ( drpin_opcode == OP_vcvttps2qq) {

        pin_opcode = XED_ICLASS_VCVTTPS2QQ;
    
    } else if ( drpin_opcode == OP_vcvttps2udq) {

        pin_opcode = XED_ICLASS_VCVTTPS2UDQ;
    
    } else if ( drpin_opcode == OP_vcvttps2uqq) {

        pin_opcode = XED_ICLASS_VCVTTPS2UQQ;
    
    } else if ( drpin_opcode == OP_vcvttsd2si) {

        pin_opcode = XED_ICLASS_VCVTTSD2SI;
    
    } else if ( drpin_opcode == OP_vcvttsd2usi) {

        pin_opcode = XED_ICLASS_VCVTTSD2USI;
    
    } else if ( drpin_opcode == OP_vcvttss2si) {

        pin_opcode = XED_ICLASS_VCVTTSS2SI;
    
    } else if ( drpin_opcode == OP_vcvttss2usi) {

        pin_opcode = XED_ICLASS_VCVTTSS2USI;
    
    } else if ( drpin_opcode == OP_vcvtudq2pd) {

        pin_opcode = XED_ICLASS_VCVTUDQ2PD;
    
    } else if ( drpin_opcode == OP_vcvtudq2ps) {

        pin_opcode = XED_ICLASS_VCVTUDQ2PS;
    
    } else if ( drpin_opcode == OP_vcvtuqq2pd) {

        pin_opcode = XED_ICLASS_VCVTUQQ2PD;
    
    } else if ( drpin_opcode == OP_vcvtuqq2ps) {

        pin_opcode = XED_ICLASS_VCVTUQQ2PS;
    
    } else if ( drpin_opcode == OP_vcvtusi2sd) {

        pin_opcode = XED_ICLASS_VCVTUSI2SD;
    
    } else if ( drpin_opcode == OP_vcvtusi2ss) {

        pin_opcode = XED_ICLASS_VCVTUSI2SS;
    
    } else if ( drpin_opcode == OP_vdbpsadbw) {

        pin_opcode = XED_ICLASS_VDBPSADBW;
    
    } else if ( drpin_opcode == OP_vdivpd) {

        pin_opcode = XED_ICLASS_VDIVPD;
    
    } else if ( drpin_opcode == OP_vdivps) {

        pin_opcode = XED_ICLASS_VDIVPS;
    
    } else if ( drpin_opcode == OP_vdivsd) {

        pin_opcode = XED_ICLASS_VDIVSD;
    
    } else if ( drpin_opcode == OP_vdivss) {

        pin_opcode = XED_ICLASS_VDIVSS;
    
    } else if ( drpin_opcode == OP_vdppd) {

        pin_opcode = XED_ICLASS_VDPPD;
    
    } else if ( drpin_opcode == OP_vdpps) {

        pin_opcode = XED_ICLASS_VDPPS;
    
    } else if ( drpin_opcode == OP_verr) {

        pin_opcode = XED_ICLASS_VERR;
    
    } else if ( drpin_opcode == OP_verw) {

        pin_opcode = XED_ICLASS_VERW;
    
    } else if ( drpin_opcode == OP_vexp2pd) {

        pin_opcode = XED_ICLASS_VEXP2PD;
    
    } else if ( drpin_opcode == OP_vexp2ps) {

        pin_opcode = XED_ICLASS_VEXP2PS;
    
    } else if ( drpin_opcode == OP_vexpandpd) {

        pin_opcode = XED_ICLASS_VEXPANDPD;
    
    } else if ( drpin_opcode == OP_vexpandps) {

        pin_opcode = XED_ICLASS_VEXPANDPS;
    
    } else if ( drpin_opcode == OP_vextractf128) {

        pin_opcode = XED_ICLASS_VEXTRACTF128;
    
    } else if ( drpin_opcode == OP_vextractf32x4) {

        pin_opcode = XED_ICLASS_VEXTRACTF32X4;
    
    } else if ( drpin_opcode == OP_vextractf32x8) {

        pin_opcode = XED_ICLASS_VEXTRACTF32X8;
    
    } else if ( drpin_opcode == OP_vextractf64x2) {

        pin_opcode = XED_ICLASS_VEXTRACTF64X2;
    
    } else if ( drpin_opcode == OP_vextractf64x4) {

        pin_opcode = XED_ICLASS_VEXTRACTF64X4;
    
    } else if ( drpin_opcode == OP_vextracti128) {

        pin_opcode = XED_ICLASS_VEXTRACTI128;
    
    } else if ( drpin_opcode == OP_vextracti32x4) {

        pin_opcode = XED_ICLASS_VEXTRACTI32X4;
    
    } else if ( drpin_opcode == OP_vextracti32x8) {

        pin_opcode = XED_ICLASS_VEXTRACTI32X8;
    
    } else if ( drpin_opcode == OP_vextracti64x2) {

        pin_opcode = XED_ICLASS_VEXTRACTI64X2;
    
    } else if ( drpin_opcode == OP_vextracti64x4) {

        pin_opcode = XED_ICLASS_VEXTRACTI64X4;
    
    } else if ( drpin_opcode == OP_vextractps) {

        pin_opcode = XED_ICLASS_VEXTRACTPS;
    
    } else if ( drpin_opcode == OP_vfixupimmpd) {

        pin_opcode = XED_ICLASS_VFIXUPIMMPD;
    
    } else if ( drpin_opcode == OP_vfixupimmps) {

        pin_opcode = XED_ICLASS_VFIXUPIMMPS;
    
    } else if ( drpin_opcode == OP_vfixupimmsd) {

        pin_opcode = XED_ICLASS_VFIXUPIMMSD;
    
    } else if ( drpin_opcode == OP_vfixupimmss) {

        pin_opcode = XED_ICLASS_VFIXUPIMMSS;
    
    } else if ( drpin_opcode == OP_vfmadd132pd) {

        pin_opcode = XED_ICLASS_VFMADD132PD;
    
    } else if ( drpin_opcode == OP_vfmadd132ps) {

        pin_opcode = XED_ICLASS_VFMADD132PS;
    
    } else if ( drpin_opcode == OP_vfmadd132sd) {

        pin_opcode = XED_ICLASS_VFMADD132SD;
    
    } else if ( drpin_opcode == OP_vfmadd132ss) {

        pin_opcode = XED_ICLASS_VFMADD132SS;
    
    } else if ( drpin_opcode == OP_vfmadd213pd) {

        pin_opcode = XED_ICLASS_VFMADD213PD;
    
    } else if ( drpin_opcode == OP_vfmadd213ps) {

        pin_opcode = XED_ICLASS_VFMADD213PS;
    
    } else if ( drpin_opcode == OP_vfmadd213sd) {

        pin_opcode = XED_ICLASS_VFMADD213SD;
    
    } else if ( drpin_opcode == OP_vfmadd213ss) {

        pin_opcode = XED_ICLASS_VFMADD213SS;
    
    } else if ( drpin_opcode == OP_vfmadd231pd) {

        pin_opcode = XED_ICLASS_VFMADD231PD;
    
    } else if ( drpin_opcode == OP_vfmadd231ps) {

        pin_opcode = XED_ICLASS_VFMADD231PS;
    
    } else if ( drpin_opcode == OP_vfmadd231sd) {

        pin_opcode = XED_ICLASS_VFMADD231SD;
    
    } else if ( drpin_opcode == OP_vfmadd231ss) {

        pin_opcode = XED_ICLASS_VFMADD231SS;
    
    } else if ( drpin_opcode == OP_vfmaddpd) {

        pin_opcode = XED_ICLASS_VFMADDPD;
    
    } else if ( drpin_opcode == OP_vfmaddps) {

        pin_opcode = XED_ICLASS_VFMADDPS;
    
    } else if ( drpin_opcode == OP_vfmaddsd) {

        pin_opcode = XED_ICLASS_VFMADDSD;
    
    } else if ( drpin_opcode == OP_vfmaddss) {

        pin_opcode = XED_ICLASS_VFMADDSS;
    
    } else if ( drpin_opcode == OP_vfmaddsub132pd) {

        pin_opcode = XED_ICLASS_VFMADDSUB132PD;
    
    } else if ( drpin_opcode == OP_vfmaddsub132ps) {

        pin_opcode = XED_ICLASS_VFMADDSUB132PS;
    
    } else if ( drpin_opcode == OP_vfmaddsub213pd) {

        pin_opcode = XED_ICLASS_VFMADDSUB213PD;
    
    } else if ( drpin_opcode == OP_vfmaddsub213ps) {

        pin_opcode = XED_ICLASS_VFMADDSUB213PS;
    
    } else if ( drpin_opcode == OP_vfmaddsub231pd) {

        pin_opcode = XED_ICLASS_VFMADDSUB231PD;
    
    } else if ( drpin_opcode == OP_vfmaddsub231ps) {

        pin_opcode = XED_ICLASS_VFMADDSUB231PS;
    
    } else if ( drpin_opcode == OP_vfmaddsubpd) {

        pin_opcode = XED_ICLASS_VFMADDSUBPD;
    
    } else if ( drpin_opcode == OP_vfmaddsubps) {

        pin_opcode = XED_ICLASS_VFMADDSUBPS;
    
    } else if ( drpin_opcode == OP_vfmsub132pd) {

        pin_opcode = XED_ICLASS_VFMSUB132PD;
    
    } else if ( drpin_opcode == OP_vfmsub132ps) {

        pin_opcode = XED_ICLASS_VFMSUB132PS;
    
    } else if ( drpin_opcode == OP_vfmsub132sd) {

        pin_opcode = XED_ICLASS_VFMSUB132SD;
    
    } else if ( drpin_opcode == OP_vfmsub132ss) {

        pin_opcode = XED_ICLASS_VFMSUB132SS;
    
    } else if ( drpin_opcode == OP_vfmsub213pd) {

        pin_opcode = XED_ICLASS_VFMSUB213PD;
    
    } else if ( drpin_opcode == OP_vfmsub213ps) {

        pin_opcode = XED_ICLASS_VFMSUB213PS;
    
    } else if ( drpin_opcode == OP_vfmsub213sd) {

        pin_opcode = XED_ICLASS_VFMSUB213SD;
    
    } else if ( drpin_opcode == OP_vfmsub213ss) {

        pin_opcode = XED_ICLASS_VFMSUB213SS;
    
    } else if ( drpin_opcode == OP_vfmsub231pd) {

        pin_opcode = XED_ICLASS_VFMSUB231PD;
    
    } else if ( drpin_opcode == OP_vfmsub231ps) {

        pin_opcode = XED_ICLASS_VFMSUB231PS;
    
    } else if ( drpin_opcode == OP_vfmsub231sd) {

        pin_opcode = XED_ICLASS_VFMSUB231SD;
    
    } else if ( drpin_opcode == OP_vfmsub231ss) {

        pin_opcode = XED_ICLASS_VFMSUB231SS;
    
    } else if ( drpin_opcode == OP_vfmsubadd132pd) {

        pin_opcode = XED_ICLASS_VFMSUBADD132PD;
    
    } else if ( drpin_opcode == OP_vfmsubadd132ps) {

        pin_opcode = XED_ICLASS_VFMSUBADD132PS;
    
    } else if ( drpin_opcode == OP_vfmsubadd213pd) {

        pin_opcode = XED_ICLASS_VFMSUBADD213PD;
    
    } else if ( drpin_opcode == OP_vfmsubadd213ps) {

        pin_opcode = XED_ICLASS_VFMSUBADD213PS;
    
    } else if ( drpin_opcode == OP_vfmsubadd231pd) {

        pin_opcode = XED_ICLASS_VFMSUBADD231PD;
    
    } else if ( drpin_opcode == OP_vfmsubadd231ps) {

        pin_opcode = XED_ICLASS_VFMSUBADD231PS;
    
    } else if ( drpin_opcode == OP_vfmsubaddpd) {

        pin_opcode = XED_ICLASS_VFMSUBADDPD;
    
    } else if ( drpin_opcode == OP_vfmsubaddps) {

        pin_opcode = XED_ICLASS_VFMSUBADDPS;
    
    } else if ( drpin_opcode == OP_vfmsubpd) {

        pin_opcode = XED_ICLASS_VFMSUBPD;
    
    } else if ( drpin_opcode == OP_vfmsubps) {

        pin_opcode = XED_ICLASS_VFMSUBPS;
    
    } else if ( drpin_opcode == OP_vfmsubsd) {

        pin_opcode = XED_ICLASS_VFMSUBSD;
    
    } else if ( drpin_opcode == OP_vfmsubss) {

        pin_opcode = XED_ICLASS_VFMSUBSS;
    
    } else if ( drpin_opcode == OP_vfnmadd132pd) {

        pin_opcode = XED_ICLASS_VFNMADD132PD;
    
    } else if ( drpin_opcode == OP_vfnmadd132ps) {

        pin_opcode = XED_ICLASS_VFNMADD132PS;
    
    } else if ( drpin_opcode == OP_vfnmadd132sd) {

        pin_opcode = XED_ICLASS_VFNMADD132SD;
    
    } else if ( drpin_opcode == OP_vfnmadd132ss) {

        pin_opcode = XED_ICLASS_VFNMADD132SS;
    
    } else if ( drpin_opcode == OP_vfnmadd213pd) {

        pin_opcode = XED_ICLASS_VFNMADD213PD;
    
    } else if ( drpin_opcode == OP_vfnmadd213ps) {

        pin_opcode = XED_ICLASS_VFNMADD213PS;
    
    } else if ( drpin_opcode == OP_vfnmadd213sd) {

        pin_opcode = XED_ICLASS_VFNMADD213SD;
    
    } else if ( drpin_opcode == OP_vfnmadd213ss) {

        pin_opcode = XED_ICLASS_VFNMADD213SS;
    
    } else if ( drpin_opcode == OP_vfnmadd231pd) {

        pin_opcode = XED_ICLASS_VFNMADD231PD;
    
    } else if ( drpin_opcode == OP_vfnmadd231ps) {

        pin_opcode = XED_ICLASS_VFNMADD231PS;
    
    } else if ( drpin_opcode == OP_vfnmadd231sd) {

        pin_opcode = XED_ICLASS_VFNMADD231SD;
    
    } else if ( drpin_opcode == OP_vfnmadd231ss) {

        pin_opcode = XED_ICLASS_VFNMADD231SS;
    
    } else if ( drpin_opcode == OP_vfnmaddpd) {

        pin_opcode = XED_ICLASS_VFNMADDPD;
    
    } else if ( drpin_opcode == OP_vfnmaddps) {

        pin_opcode = XED_ICLASS_VFNMADDPS;
    
    } else if ( drpin_opcode == OP_vfnmaddsd) {

        pin_opcode = XED_ICLASS_VFNMADDSD;
    
    } else if ( drpin_opcode == OP_vfnmaddss) {

        pin_opcode = XED_ICLASS_VFNMADDSS;
    
    } else if ( drpin_opcode == OP_vfnmsub132pd) {

        pin_opcode = XED_ICLASS_VFNMSUB132PD;
    
    } else if ( drpin_opcode == OP_vfnmsub132ps) {

        pin_opcode = XED_ICLASS_VFNMSUB132PS;
    
    } else if ( drpin_opcode == OP_vfnmsub132sd) {

        pin_opcode = XED_ICLASS_VFNMSUB132SD;
    
    } else if ( drpin_opcode == OP_vfnmsub132ss) {

        pin_opcode = XED_ICLASS_VFNMSUB132SS;
    
    } else if ( drpin_opcode == OP_vfnmsub213pd) {

        pin_opcode = XED_ICLASS_VFNMSUB213PD;
    
    } else if ( drpin_opcode == OP_vfnmsub213ps) {

        pin_opcode = XED_ICLASS_VFNMSUB213PS;
    
    } else if ( drpin_opcode == OP_vfnmsub213sd) {

        pin_opcode = XED_ICLASS_VFNMSUB213SD;
    
    } else if ( drpin_opcode == OP_vfnmsub213ss) {

        pin_opcode = XED_ICLASS_VFNMSUB213SS;
    
    } else if ( drpin_opcode == OP_vfnmsub231pd) {

        pin_opcode = XED_ICLASS_VFNMSUB231PD;
    
    } else if ( drpin_opcode == OP_vfnmsub231ps) {

        pin_opcode = XED_ICLASS_VFNMSUB231PS;
    
    } else if ( drpin_opcode == OP_vfnmsub231sd) {

        pin_opcode = XED_ICLASS_VFNMSUB231SD;
    
    } else if ( drpin_opcode == OP_vfnmsub231ss) {

        pin_opcode = XED_ICLASS_VFNMSUB231SS;
    
    } else if ( drpin_opcode == OP_vfnmsubpd) {

        pin_opcode = XED_ICLASS_VFNMSUBPD;
    
    } else if ( drpin_opcode == OP_vfnmsubps) {

        pin_opcode = XED_ICLASS_VFNMSUBPS;
    
    } else if ( drpin_opcode == OP_vfnmsubsd) {

        pin_opcode = XED_ICLASS_VFNMSUBSD;
    
    } else if ( drpin_opcode == OP_vfnmsubss) {

        pin_opcode = XED_ICLASS_VFNMSUBSS;
    
    } else if ( drpin_opcode == OP_vfpclasspd) {

        pin_opcode = XED_ICLASS_VFPCLASSPD;
    
    } else if ( drpin_opcode == OP_vfpclassps) {

        pin_opcode = XED_ICLASS_VFPCLASSPS;
    
    } else if ( drpin_opcode == OP_vfpclasssd) {

        pin_opcode = XED_ICLASS_VFPCLASSSD;
    
    } else if ( drpin_opcode == OP_vfpclassss) {

        pin_opcode = XED_ICLASS_VFPCLASSSS;
    
    } else if ( drpin_opcode == OP_vfrczpd) {

        pin_opcode = XED_ICLASS_VFRCZPD;
    
    } else if ( drpin_opcode == OP_vfrczps) {

        pin_opcode = XED_ICLASS_VFRCZPS;
    
    } else if ( drpin_opcode == OP_vfrczsd) {

        pin_opcode = XED_ICLASS_VFRCZSD;
    
    } else if ( drpin_opcode == OP_vfrczss) {

        pin_opcode = XED_ICLASS_VFRCZSS;
    
    } else if ( drpin_opcode == OP_vgatherdpd) {

        pin_opcode = XED_ICLASS_VGATHERDPD;
    
    } else if ( drpin_opcode == OP_vgatherdps) {

        pin_opcode = XED_ICLASS_VGATHERDPS;
    
    } else if ( drpin_opcode == OP_vgatherpf0dpd) {

        pin_opcode = XED_ICLASS_VGATHERPF0DPD;
    
    } else if ( drpin_opcode == OP_vgatherpf0dps) {

        pin_opcode = XED_ICLASS_VGATHERPF0DPS;
    
    } else if ( drpin_opcode == OP_vgatherpf0qpd) {

        pin_opcode = XED_ICLASS_VGATHERPF0QPD;
    
    } else if ( drpin_opcode == OP_vgatherpf0qps) {

        pin_opcode = XED_ICLASS_VGATHERPF0QPS;
    
    } else if ( drpin_opcode == OP_vgatherpf1dpd) {

        pin_opcode = XED_ICLASS_VGATHERPF1DPD;
    
    } else if ( drpin_opcode == OP_vgatherpf1dps) {

        pin_opcode = XED_ICLASS_VGATHERPF1DPS;
    
    } else if ( drpin_opcode == OP_vgatherpf1qpd) {

        pin_opcode = XED_ICLASS_VGATHERPF1QPD;
    
    } else if ( drpin_opcode == OP_vgatherpf1qps) {

        pin_opcode = XED_ICLASS_VGATHERPF1QPS;
    
    } else if ( drpin_opcode == OP_vgatherqpd) {

        pin_opcode = XED_ICLASS_VGATHERQPD;
    
    } else if ( drpin_opcode == OP_vgatherqps) {

        pin_opcode = XED_ICLASS_VGATHERQPS;
    
    } else if ( drpin_opcode == OP_vgetexppd) {

        pin_opcode = XED_ICLASS_VGETEXPPD;
    
    } else if ( drpin_opcode == OP_vgetexpps) {

        pin_opcode = XED_ICLASS_VGETEXPPS;
    
    } else if ( drpin_opcode == OP_vgetexpsd) {

        pin_opcode = XED_ICLASS_VGETEXPSD;
    
    } else if ( drpin_opcode == OP_vgetexpss) {

        pin_opcode = XED_ICLASS_VGETEXPSS;
    
    } else if ( drpin_opcode == OP_vgetmantpd) {

        pin_opcode = XED_ICLASS_VGETMANTPD;
    
    } else if ( drpin_opcode == OP_vgetmantps) {

        pin_opcode = XED_ICLASS_VGETMANTPS;
    
    } else if ( drpin_opcode == OP_vgetmantsd) {

        pin_opcode = XED_ICLASS_VGETMANTSD;
    
    } else if ( drpin_opcode == OP_vgetmantss) {

        pin_opcode = XED_ICLASS_VGETMANTSS;
    
    } else if ( drpin_opcode == OP_vhaddpd) {

        pin_opcode = XED_ICLASS_VHADDPD;
    
    } else if ( drpin_opcode == OP_vhaddps) {

        pin_opcode = XED_ICLASS_VHADDPS;
    
    } else if ( drpin_opcode == OP_vhsubpd) {

        pin_opcode = XED_ICLASS_VHSUBPD;
    
    } else if ( drpin_opcode == OP_vhsubps) {

        pin_opcode = XED_ICLASS_VHSUBPS;
    
    } else if ( drpin_opcode == OP_vinsertf128) {

        pin_opcode = XED_ICLASS_VINSERTF128;
    
    } else if ( drpin_opcode == OP_vinsertf32x4) {

        pin_opcode = XED_ICLASS_VINSERTF32X4;
    
    } else if ( drpin_opcode == OP_vinsertf32x8) {

        pin_opcode = XED_ICLASS_VINSERTF32X8;
    
    } else if ( drpin_opcode == OP_vinsertf64x2) {

        pin_opcode = XED_ICLASS_VINSERTF64X2;
    
    } else if ( drpin_opcode == OP_vinsertf64x4) {

        pin_opcode = XED_ICLASS_VINSERTF64X4;
    
    } else if ( drpin_opcode == OP_vinserti128) {

        pin_opcode = XED_ICLASS_VINSERTI128;
    
    } else if ( drpin_opcode == OP_vinserti32x4) {

        pin_opcode = XED_ICLASS_VINSERTI32X4;
    
    } else if ( drpin_opcode == OP_vinserti32x8) {

        pin_opcode = XED_ICLASS_VINSERTI32X8;
    
    } else if ( drpin_opcode == OP_vinserti64x2) {

        pin_opcode = XED_ICLASS_VINSERTI64X2;
    
    } else if ( drpin_opcode == OP_vinserti64x4) {

        pin_opcode = XED_ICLASS_VINSERTI64X4;
    
    } else if ( drpin_opcode == OP_vinsertps) {

        pin_opcode = XED_ICLASS_VINSERTPS;
    
    } else if ( drpin_opcode == OP_vlddqu) {

        pin_opcode = XED_ICLASS_VLDDQU;
    
    } else if ( drpin_opcode == OP_vldmxcsr) {

        pin_opcode = XED_ICLASS_VLDMXCSR;
    
    } else if ( drpin_opcode == OP_vmaskmovdqu) {

        pin_opcode = XED_ICLASS_VMASKMOVDQU;
    
    } else if ( drpin_opcode == OP_vmaskmovpd) {

        pin_opcode = XED_ICLASS_VMASKMOVPD;
    
    } else if ( drpin_opcode == OP_vmaskmovps) {

        pin_opcode = XED_ICLASS_VMASKMOVPS;
    
    } else if ( drpin_opcode == OP_vmaxpd) {

        pin_opcode = XED_ICLASS_VMAXPD;
    
    } else if ( drpin_opcode == OP_vmaxps) {

        pin_opcode = XED_ICLASS_VMAXPS;
    
    } else if ( drpin_opcode == OP_vmaxsd) {

        pin_opcode = XED_ICLASS_VMAXSD;
    
    } else if ( drpin_opcode == OP_vmaxss) {

        pin_opcode = XED_ICLASS_VMAXSS;
    
    } else if ( drpin_opcode == OP_vmcall) {

        pin_opcode = XED_ICLASS_VMCALL;
    
    } else if ( drpin_opcode == OP_vmclear) {

        pin_opcode = XED_ICLASS_VMCLEAR;
    
    } else if ( drpin_opcode == OP_vmfunc) {

        pin_opcode = XED_ICLASS_VMFUNC;
    
    } else if ( drpin_opcode == OP_vminpd) {

        pin_opcode = XED_ICLASS_VMINPD;
    
    } else if ( drpin_opcode == OP_vminps) {

        pin_opcode = XED_ICLASS_VMINPS;
    
    } else if ( drpin_opcode == OP_vminsd) {

        pin_opcode = XED_ICLASS_VMINSD;
    
    } else if ( drpin_opcode == OP_vminss) {

        pin_opcode = XED_ICLASS_VMINSS;
    
    } else if ( drpin_opcode == OP_vmlaunch) {

        pin_opcode = XED_ICLASS_VMLAUNCH;
    
    } else if ( drpin_opcode == OP_vmload) {

        pin_opcode = XED_ICLASS_VMLOAD;
    
    } else if ( drpin_opcode == OP_vmmcall) {

        pin_opcode = XED_ICLASS_VMMCALL;
    
    } else if ( drpin_opcode == OP_vmovapd) {

        pin_opcode = XED_ICLASS_VMOVAPD;
    
    } else if ( drpin_opcode == OP_vmovaps) {

        pin_opcode = XED_ICLASS_VMOVAPS;
    
    } else if ( drpin_opcode == OP_vmovd) {

        pin_opcode = XED_ICLASS_VMOVD;
    
    } else if ( drpin_opcode == OP_vmovddup) {

        pin_opcode = XED_ICLASS_VMOVDDUP;
    
    } else if ( drpin_opcode == OP_vmovdqa) {

        pin_opcode = XED_ICLASS_VMOVDQA;
    
    } else if ( drpin_opcode == OP_vmovdqa32) {

        pin_opcode = XED_ICLASS_VMOVDQA32;
    
    } else if ( drpin_opcode == OP_vmovdqa64) {

        pin_opcode = XED_ICLASS_VMOVDQA64;
    
    } else if ( drpin_opcode == OP_vmovdqu) {

        pin_opcode = XED_ICLASS_VMOVDQU;
    
    } else if ( drpin_opcode == OP_vmovdqu16) {

        pin_opcode = XED_ICLASS_VMOVDQU16;
    
    } else if ( drpin_opcode == OP_vmovdqu32) {

        pin_opcode = XED_ICLASS_VMOVDQU32;
    
    } else if ( drpin_opcode == OP_vmovdqu64) {

        pin_opcode = XED_ICLASS_VMOVDQU64;
    
    } else if ( drpin_opcode == OP_vmovdqu8) {

        pin_opcode = XED_ICLASS_VMOVDQU8;
    
    } else if ( drpin_opcode == OP_vmovhlps) {

        pin_opcode = XED_ICLASS_VMOVHLPS;
    
    } else if ( drpin_opcode == OP_vmovhpd) {

        pin_opcode = XED_ICLASS_VMOVHPD;
    
    } else if ( drpin_opcode == OP_vmovhps) {

        pin_opcode = XED_ICLASS_VMOVHPS;
    
    } else if ( drpin_opcode == OP_vmovlhps) {

        pin_opcode = XED_ICLASS_VMOVLHPS;
    
    } else if ( drpin_opcode == OP_vmovlpd) {

        pin_opcode = XED_ICLASS_VMOVLPD;
    
    } else if ( drpin_opcode == OP_vmovlps) {

        pin_opcode = XED_ICLASS_VMOVLPS;
    
    } else if ( drpin_opcode == OP_vmovmskpd) {

        pin_opcode = XED_ICLASS_VMOVMSKPD;
    
    } else if ( drpin_opcode == OP_vmovmskps) {

        pin_opcode = XED_ICLASS_VMOVMSKPS;
    
    } else if ( drpin_opcode == OP_vmovntdq) {

        pin_opcode = XED_ICLASS_VMOVNTDQ;
    
    } else if ( drpin_opcode == OP_vmovntdqa) {

        pin_opcode = XED_ICLASS_VMOVNTDQA;
    
    } else if ( drpin_opcode == OP_vmovntpd) {

        pin_opcode = XED_ICLASS_VMOVNTPD;
    
    } else if ( drpin_opcode == OP_vmovntps) {

        pin_opcode = XED_ICLASS_VMOVNTPS;
    
    } else if ( drpin_opcode == OP_vmovq) {

        pin_opcode = XED_ICLASS_VMOVQ;
    
    } else if ( drpin_opcode == OP_vmovsd) {

        pin_opcode = XED_ICLASS_VMOVSD;
    
    } else if ( drpin_opcode == OP_vmovshdup) {

        pin_opcode = XED_ICLASS_VMOVSHDUP;
    
    } else if ( drpin_opcode == OP_vmovsldup) {

        pin_opcode = XED_ICLASS_VMOVSLDUP;
    
    } else if ( drpin_opcode == OP_vmovss) {

        pin_opcode = XED_ICLASS_VMOVSS;
    
    } else if ( drpin_opcode == OP_vmovupd) {

        pin_opcode = XED_ICLASS_VMOVUPD;
    
    } else if ( drpin_opcode == OP_vmovups) {

        pin_opcode = XED_ICLASS_VMOVUPS;
    
    } else if ( drpin_opcode == OP_vmpsadbw) {

        pin_opcode = XED_ICLASS_VMPSADBW;
    
    } else if ( drpin_opcode == OP_vmptrld) {

        pin_opcode = XED_ICLASS_VMPTRLD;
    
    } else if ( drpin_opcode == OP_vmptrst) {

        pin_opcode = XED_ICLASS_VMPTRST;
    
    } else if ( drpin_opcode == OP_vmread) {

        pin_opcode = XED_ICLASS_VMREAD;
    
    } else if ( drpin_opcode == OP_vmresume) {

        pin_opcode = XED_ICLASS_VMRESUME;
    
    } else if ( drpin_opcode == OP_vmrun) {

        pin_opcode = XED_ICLASS_VMRUN;
    
    } else if ( drpin_opcode == OP_vmsave) {

        pin_opcode = XED_ICLASS_VMSAVE;
    
    } else if ( drpin_opcode == OP_vmulpd) {

        pin_opcode = XED_ICLASS_VMULPD;
    
    } else if ( drpin_opcode == OP_vmulps) {

        pin_opcode = XED_ICLASS_VMULPS;
    
    } else if ( drpin_opcode == OP_vmulsd) {

        pin_opcode = XED_ICLASS_VMULSD;
    
    } else if ( drpin_opcode == OP_vmulss) {

        pin_opcode = XED_ICLASS_VMULSS;
    
    } else if ( drpin_opcode == OP_vmwrite) {

        pin_opcode = XED_ICLASS_VMWRITE;
    
    } else if ( drpin_opcode == OP_vmxoff) {

        pin_opcode = XED_ICLASS_VMXOFF;
    
    } else if ( drpin_opcode == OP_vmxon) {

        pin_opcode = XED_ICLASS_VMXON;
    
    } else if ( drpin_opcode == OP_vorpd) {

        pin_opcode = XED_ICLASS_VORPD;
    
    } else if ( drpin_opcode == OP_vorps) {

        pin_opcode = XED_ICLASS_VORPS;
    
    } else if ( drpin_opcode == OP_vpabsb) {

        pin_opcode = XED_ICLASS_VPABSB;
    
    } else if ( drpin_opcode == OP_vpabsd) {

        pin_opcode = XED_ICLASS_VPABSD;
    
    } else if ( drpin_opcode == OP_vpabsq) {

        pin_opcode = XED_ICLASS_VPABSQ;
    
    } else if ( drpin_opcode == OP_vpabsw) {

        pin_opcode = XED_ICLASS_VPABSW;
    
    } else if ( drpin_opcode == OP_vpackssdw) {

        pin_opcode = XED_ICLASS_VPACKSSDW;
    
    } else if ( drpin_opcode == OP_vpacksswb) {

        pin_opcode = XED_ICLASS_VPACKSSWB;
    
    } else if ( drpin_opcode == OP_vpackusdw) {

        pin_opcode = XED_ICLASS_VPACKUSDW;
    
    } else if ( drpin_opcode == OP_vpackuswb) {

        pin_opcode = XED_ICLASS_VPACKUSWB;
    
    } else if ( drpin_opcode == OP_vpaddb) {

        pin_opcode = XED_ICLASS_VPADDB;
    
    } else if ( drpin_opcode == OP_vpaddd) {

        pin_opcode = XED_ICLASS_VPADDD;
    
    } else if ( drpin_opcode == OP_vpaddq) {

        pin_opcode = XED_ICLASS_VPADDQ;
    
    } else if ( drpin_opcode == OP_vpaddsb) {

        pin_opcode = XED_ICLASS_VPADDSB;
    
    } else if ( drpin_opcode == OP_vpaddsw) {

        pin_opcode = XED_ICLASS_VPADDSW;
    
    } else if ( drpin_opcode == OP_vpaddusb) {

        pin_opcode = XED_ICLASS_VPADDUSB;
    
    } else if ( drpin_opcode == OP_vpaddusw) {

        pin_opcode = XED_ICLASS_VPADDUSW;
    
    } else if ( drpin_opcode == OP_vpaddw) {

        pin_opcode = XED_ICLASS_VPADDW;
    
    } else if ( drpin_opcode == OP_vpalignr) {

        pin_opcode = XED_ICLASS_VPALIGNR;
    
    } else if ( drpin_opcode == OP_vpand) {

        pin_opcode = XED_ICLASS_VPAND;
    
    } else if ( drpin_opcode == OP_vpandd) {

        pin_opcode = XED_ICLASS_VPANDD;
    
    } else if ( drpin_opcode == OP_vpandn) {

        pin_opcode = XED_ICLASS_VPANDN;
    
    } else if ( drpin_opcode == OP_vpandnd) {

        pin_opcode = XED_ICLASS_VPANDND;
    
    } else if ( drpin_opcode == OP_vpandnq) {

        pin_opcode = XED_ICLASS_VPANDNQ;
    
    } else if ( drpin_opcode == OP_vpandq) {

        pin_opcode = XED_ICLASS_VPANDQ;
    
    } else if ( drpin_opcode == OP_vpavgb) {

        pin_opcode = XED_ICLASS_VPAVGB;
    
    } else if ( drpin_opcode == OP_vpavgw) {

        pin_opcode = XED_ICLASS_VPAVGW;
    
    } else if ( drpin_opcode == OP_vpblendd) {

        pin_opcode = XED_ICLASS_VPBLENDD;
    
    } else if ( drpin_opcode == OP_vpblendmb) {

        pin_opcode = XED_ICLASS_VPBLENDMB;
    
    } else if ( drpin_opcode == OP_vpblendmd) {

        pin_opcode = XED_ICLASS_VPBLENDMD;
    
    } else if ( drpin_opcode == OP_vpblendmq) {

        pin_opcode = XED_ICLASS_VPBLENDMQ;
    
    } else if ( drpin_opcode == OP_vpblendmw) {

        pin_opcode = XED_ICLASS_VPBLENDMW;
    
    } else if ( drpin_opcode == OP_vpblendvb) {

        pin_opcode = XED_ICLASS_VPBLENDVB;
    
    } else if ( drpin_opcode == OP_vpblendw) {

        pin_opcode = XED_ICLASS_VPBLENDW;
    
    } else if ( drpin_opcode == OP_vpbroadcastb) {

        pin_opcode = XED_ICLASS_VPBROADCASTB;
    
    } else if ( drpin_opcode == OP_vpbroadcastd) {

        pin_opcode = XED_ICLASS_VPBROADCASTD;
    
    } else if ( drpin_opcode == OP_vpbroadcastmb2q) {

        pin_opcode = XED_ICLASS_VPBROADCASTMB2Q;
    
    } else if ( drpin_opcode == OP_vpbroadcastmw2d) {

        pin_opcode = XED_ICLASS_VPBROADCASTMW2D;
    
    } else if ( drpin_opcode == OP_vpbroadcastq) {

        pin_opcode = XED_ICLASS_VPBROADCASTQ;
    
    } else if ( drpin_opcode == OP_vpbroadcastw) {

        pin_opcode = XED_ICLASS_VPBROADCASTW;
    
    } else if ( drpin_opcode == OP_vpclmulqdq) {

        pin_opcode = XED_ICLASS_VPCLMULQDQ;
    
    } else if ( drpin_opcode == OP_vpcmov) {

        pin_opcode = XED_ICLASS_VPCMOV;
    
    } else if ( drpin_opcode == OP_vpcmpb) {

        pin_opcode = XED_ICLASS_VPCMPB;
    
    } else if ( drpin_opcode == OP_vpcmpd) {

        pin_opcode = XED_ICLASS_VPCMPD;
    
    } else if ( drpin_opcode == OP_vpcmpeqb) {

        pin_opcode = XED_ICLASS_VPCMPEQB;
    
    } else if ( drpin_opcode == OP_vpcmpeqd) {

        pin_opcode = XED_ICLASS_VPCMPEQD;
    
    } else if ( drpin_opcode == OP_vpcmpeqq) {

        pin_opcode = XED_ICLASS_VPCMPEQQ;
    
    } else if ( drpin_opcode == OP_vpcmpeqw) {

        pin_opcode = XED_ICLASS_VPCMPEQW;
    
    } else if ( drpin_opcode == OP_vpcmpestri) {

        pin_opcode = XED_ICLASS_VPCMPESTRI;
    
    } else if ( drpin_opcode == OP_vpcmpestrm) {

        pin_opcode = XED_ICLASS_VPCMPESTRM;
    
    } else if ( drpin_opcode == OP_vpcmpgtb) {

        pin_opcode = XED_ICLASS_VPCMPGTB;
    
    } else if ( drpin_opcode == OP_vpcmpgtd) {

        pin_opcode = XED_ICLASS_VPCMPGTD;
    
    } else if ( drpin_opcode == OP_vpcmpgtq) {

        pin_opcode = XED_ICLASS_VPCMPGTQ;
    
    } else if ( drpin_opcode == OP_vpcmpgtw) {

        pin_opcode = XED_ICLASS_VPCMPGTW;
    
    } else if ( drpin_opcode == OP_vpcmpistri) {

        pin_opcode = XED_ICLASS_VPCMPISTRI;
    
    } else if ( drpin_opcode == OP_vpcmpistrm) {

        pin_opcode = XED_ICLASS_VPCMPISTRM;
    
    } else if ( drpin_opcode == OP_vpcmpq) {

        pin_opcode = XED_ICLASS_VPCMPQ;
    
    } else if ( drpin_opcode == OP_vpcmpub) {

        pin_opcode = XED_ICLASS_VPCMPUB;
    
    } else if ( drpin_opcode == OP_vpcmpud) {

        pin_opcode = XED_ICLASS_VPCMPUD;
    
    } else if ( drpin_opcode == OP_vpcmpuq) {

        pin_opcode = XED_ICLASS_VPCMPUQ;
    
    } else if ( drpin_opcode == OP_vpcmpuw) {

        pin_opcode = XED_ICLASS_VPCMPUW;
    
    } else if ( drpin_opcode == OP_vpcmpw) {

        pin_opcode = XED_ICLASS_VPCMPW;
    
    } else if ( drpin_opcode == OP_vpcomb) {

        pin_opcode = XED_ICLASS_VPCOMB;
    
    } else if ( drpin_opcode == OP_vpcomd) {

        pin_opcode = XED_ICLASS_VPCOMD;
    
    } else if ( drpin_opcode == OP_vpcompressd) {

        pin_opcode = XED_ICLASS_VPCOMPRESSD;
    
    } else if ( drpin_opcode == OP_vpcompressq) {

        pin_opcode = XED_ICLASS_VPCOMPRESSQ;
    
    } else if ( drpin_opcode == OP_vpcomq) {

        pin_opcode = XED_ICLASS_VPCOMQ;
    
    } else if ( drpin_opcode == OP_vpcomub) {

        pin_opcode = XED_ICLASS_VPCOMUB;
    
    } else if ( drpin_opcode == OP_vpcomud) {

        pin_opcode = XED_ICLASS_VPCOMUD;
    
    } else if ( drpin_opcode == OP_vpcomuq) {

        pin_opcode = XED_ICLASS_VPCOMUQ;
    
    } else if ( drpin_opcode == OP_vpcomuw) {

        pin_opcode = XED_ICLASS_VPCOMUW;
    
    } else if ( drpin_opcode == OP_vpcomw) {

        pin_opcode = XED_ICLASS_VPCOMW;
    
    } else if ( drpin_opcode == OP_vpconflictd) {

        pin_opcode = XED_ICLASS_VPCONFLICTD;
    
    } else if ( drpin_opcode == OP_vpconflictq) {

        pin_opcode = XED_ICLASS_VPCONFLICTQ;
    
    } else if ( drpin_opcode == OP_vperm2f128) {

        pin_opcode = XED_ICLASS_VPERM2F128;
    
    } else if ( drpin_opcode == OP_vperm2i128) {

        pin_opcode = XED_ICLASS_VPERM2I128;
    
    // } else if ( drpin_opcode == OP_vpermb) {

    //     pin_opcode = XED_ICLASS_VPERMB;
    
    } else if ( drpin_opcode == OP_vpermd) {

        pin_opcode = XED_ICLASS_VPERMD;
    
    } else if ( drpin_opcode == OP_vpermi2b) {

        pin_opcode = XED_ICLASS_VPERMI2B;
    
    } else if ( drpin_opcode == OP_vpermi2d) {

        pin_opcode = XED_ICLASS_VPERMI2D;
    
    } else if ( drpin_opcode == OP_vpermi2pd) {

        pin_opcode = XED_ICLASS_VPERMI2PD;
    
    } else if ( drpin_opcode == OP_vpermi2ps) {

        pin_opcode = XED_ICLASS_VPERMI2PS;
    
    } else if ( drpin_opcode == OP_vpermi2q) {

        pin_opcode = XED_ICLASS_VPERMI2Q;
    
    } else if ( drpin_opcode == OP_vpermi2w) {

        pin_opcode = XED_ICLASS_VPERMI2W;
    
    } else if ( drpin_opcode == OP_vpermil2pd) {

        pin_opcode = XED_ICLASS_VPERMIL2PD;
    
    } else if ( drpin_opcode == OP_vpermil2ps) {

        pin_opcode = XED_ICLASS_VPERMIL2PS;
    
    } else if ( drpin_opcode == OP_vpermilpd) {

        pin_opcode = XED_ICLASS_VPERMILPD;
    
    } else if ( drpin_opcode == OP_vpermilps) {

        pin_opcode = XED_ICLASS_VPERMILPS;
    
    } else if ( drpin_opcode == OP_vpermpd) {

        pin_opcode = XED_ICLASS_VPERMPD;
    
    } else if ( drpin_opcode == OP_vpermps) {

        pin_opcode = XED_ICLASS_VPERMPS;
    
    } else if ( drpin_opcode == OP_vpermq) {

        pin_opcode = XED_ICLASS_VPERMQ;
    
    } else if ( drpin_opcode == OP_vpermt2b) {

        pin_opcode = XED_ICLASS_VPERMT2B;
    
    } else if ( drpin_opcode == OP_vpermt2d) {

        pin_opcode = XED_ICLASS_VPERMT2D;
    
    } else if ( drpin_opcode == OP_vpermt2pd) {

        pin_opcode = XED_ICLASS_VPERMT2PD;
    
    } else if ( drpin_opcode == OP_vpermt2ps) {

        pin_opcode = XED_ICLASS_VPERMT2PS;
    
    } else if ( drpin_opcode == OP_vpermt2q) {

        pin_opcode = XED_ICLASS_VPERMT2Q;
    
    } else if ( drpin_opcode == OP_vpermt2w) {

        pin_opcode = XED_ICLASS_VPERMT2W;
    
    } else if ( drpin_opcode == OP_vpermw) {

        pin_opcode = XED_ICLASS_VPERMW;
    
    } else if ( drpin_opcode == OP_vpexpandd) {

        pin_opcode = XED_ICLASS_VPEXPANDD;
    
    } else if ( drpin_opcode == OP_vpexpandq) {

        pin_opcode = XED_ICLASS_VPEXPANDQ;
    
    } else if ( drpin_opcode == OP_vpextrb) {

        pin_opcode = XED_ICLASS_VPEXTRB;
    
    } else if ( drpin_opcode == OP_vpextrd) {

        pin_opcode = XED_ICLASS_VPEXTRD;
    
    } else if ( drpin_opcode == OP_vpextrq) {

        pin_opcode = XED_ICLASS_VPEXTRQ;
    
    } else if ( drpin_opcode == OP_vpextrw) {

        pin_opcode = XED_ICLASS_VPEXTRW;
    
    } else if ( drpin_opcode == OP_vpgatherdd) {

        pin_opcode = XED_ICLASS_VPGATHERDD;
    
    } else if ( drpin_opcode == OP_vpgatherdq) {

        pin_opcode = XED_ICLASS_VPGATHERDQ;
    
    } else if ( drpin_opcode == OP_vpgatherqd) {

        pin_opcode = XED_ICLASS_VPGATHERQD;
    
    } else if ( drpin_opcode == OP_vpgatherqq) {

        pin_opcode = XED_ICLASS_VPGATHERQQ;
    
    } else if ( drpin_opcode == OP_vphaddbd) {

        pin_opcode = XED_ICLASS_VPHADDBD;
    
    } else if ( drpin_opcode == OP_vphaddbq) {

        pin_opcode = XED_ICLASS_VPHADDBQ;
    
    } else if ( drpin_opcode == OP_vphaddbw) {

        pin_opcode = XED_ICLASS_VPHADDBW;
    
    } else if ( drpin_opcode == OP_vphaddd) {

        pin_opcode = XED_ICLASS_VPHADDD;
    
    } else if ( drpin_opcode == OP_vphadddq) {

        pin_opcode = XED_ICLASS_VPHADDDQ;
    
    } else if ( drpin_opcode == OP_vphaddsw) {

        pin_opcode = XED_ICLASS_VPHADDSW;
    
    } else if ( drpin_opcode == OP_vphaddubd) {

        pin_opcode = XED_ICLASS_VPHADDUBD;
    
    } else if ( drpin_opcode == OP_vphaddubq) {

        pin_opcode = XED_ICLASS_VPHADDUBQ;
    
    } else if ( drpin_opcode == OP_vphaddubw) {

        pin_opcode = XED_ICLASS_VPHADDUBW;
    
    } else if ( drpin_opcode == OP_vphaddudq) {

        pin_opcode = XED_ICLASS_VPHADDUDQ;
    
    } else if ( drpin_opcode == OP_vphadduwd) {

        pin_opcode = XED_ICLASS_VPHADDUWD;
    
    } else if ( drpin_opcode == OP_vphadduwq) {

        pin_opcode = XED_ICLASS_VPHADDUWQ;
    
    } else if ( drpin_opcode == OP_vphaddw) {

        pin_opcode = XED_ICLASS_VPHADDW;
    
    } else if ( drpin_opcode == OP_vphaddwd) {

        pin_opcode = XED_ICLASS_VPHADDWD;
    
    } else if ( drpin_opcode == OP_vphaddwq) {

        pin_opcode = XED_ICLASS_VPHADDWQ;
    
    } else if ( drpin_opcode == OP_vphminposuw) {

        pin_opcode = XED_ICLASS_VPHMINPOSUW;
    
    } else if ( drpin_opcode == OP_vphsubbw) {

        pin_opcode = XED_ICLASS_VPHSUBBW;
    
    } else if ( drpin_opcode == OP_vphsubd) {

        pin_opcode = XED_ICLASS_VPHSUBD;
    
    } else if ( drpin_opcode == OP_vphsubdq) {

        pin_opcode = XED_ICLASS_VPHSUBDQ;
    
    } else if ( drpin_opcode == OP_vphsubsw) {

        pin_opcode = XED_ICLASS_VPHSUBSW;
    
    } else if ( drpin_opcode == OP_vphsubw) {

        pin_opcode = XED_ICLASS_VPHSUBW;
    
    } else if ( drpin_opcode == OP_vphsubwd) {

        pin_opcode = XED_ICLASS_VPHSUBWD;
    
    } else if ( drpin_opcode == OP_vpinsrb) {

        pin_opcode = XED_ICLASS_VPINSRB;
    
    } else if ( drpin_opcode == OP_vpinsrd) {

        pin_opcode = XED_ICLASS_VPINSRD;
    
    } else if ( drpin_opcode == OP_vpinsrq) {

        pin_opcode = XED_ICLASS_VPINSRQ;
    
    } else if ( drpin_opcode == OP_vpinsrw) {

        pin_opcode = XED_ICLASS_VPINSRW;
    
    } else if ( drpin_opcode == OP_vplzcntd) {

        pin_opcode = XED_ICLASS_VPLZCNTD;
    
    } else if ( drpin_opcode == OP_vplzcntq) {

        pin_opcode = XED_ICLASS_VPLZCNTQ;
    
    } else if ( drpin_opcode == OP_vpmacsdd) {

        pin_opcode = XED_ICLASS_VPMACSDD;
    
    } else if ( drpin_opcode == OP_vpmacsdqh) {

        pin_opcode = XED_ICLASS_VPMACSDQH;
    
    } else if ( drpin_opcode == OP_vpmacsdql) {

        pin_opcode = XED_ICLASS_VPMACSDQL;
    
    } else if ( drpin_opcode == OP_vpmacssdd) {

        pin_opcode = XED_ICLASS_VPMACSSDD;
    
    } else if ( drpin_opcode == OP_vpmacssdqh) {

        pin_opcode = XED_ICLASS_VPMACSSDQH;
    
    } else if ( drpin_opcode == OP_vpmacssdql) {

        pin_opcode = XED_ICLASS_VPMACSSDQL;
    
    } else if ( drpin_opcode == OP_vpmacsswd) {

        pin_opcode = XED_ICLASS_VPMACSSWD;
    
    } else if ( drpin_opcode == OP_vpmacssww) {

        pin_opcode = XED_ICLASS_VPMACSSWW;
    
    } else if ( drpin_opcode == OP_vpmacswd) {

        pin_opcode = XED_ICLASS_VPMACSWD;
    
    } else if ( drpin_opcode == OP_vpmacsww) {

        pin_opcode = XED_ICLASS_VPMACSWW;
    
    } else if ( drpin_opcode == OP_vpmadcsswd) {

        pin_opcode = XED_ICLASS_VPMADCSSWD;
    
    } else if ( drpin_opcode == OP_vpmadcswd) {

        pin_opcode = XED_ICLASS_VPMADCSWD;
    
    } else if ( drpin_opcode == OP_vpmadd52huq) {

        pin_opcode = XED_ICLASS_VPMADD52HUQ;
    
    } else if ( drpin_opcode == OP_vpmadd52luq) {

        pin_opcode = XED_ICLASS_VPMADD52LUQ;
    
    } else if ( drpin_opcode == OP_vpmaddubsw) {

        pin_opcode = XED_ICLASS_VPMADDUBSW;
    
    } else if ( drpin_opcode == OP_vpmaddwd) {

        pin_opcode = XED_ICLASS_VPMADDWD;
    
    } else if ( drpin_opcode == OP_vpmaskmovd) {

        pin_opcode = XED_ICLASS_VPMASKMOVD;
    
    } else if ( drpin_opcode == OP_vpmaskmovq) {

        pin_opcode = XED_ICLASS_VPMASKMOVQ;
    
    } else if ( drpin_opcode == OP_vpmaxsb) {

        pin_opcode = XED_ICLASS_VPMAXSB;
    
    } else if ( drpin_opcode == OP_vpmaxsd) {

        pin_opcode = XED_ICLASS_VPMAXSD;
    
    } else if ( drpin_opcode == OP_vpmaxsq) {

        pin_opcode = XED_ICLASS_VPMAXSQ;
    
    } else if ( drpin_opcode == OP_vpmaxsw) {

        pin_opcode = XED_ICLASS_VPMAXSW;
    
    } else if ( drpin_opcode == OP_vpmaxub) {

        pin_opcode = XED_ICLASS_VPMAXUB;
    
    } else if ( drpin_opcode == OP_vpmaxud) {

        pin_opcode = XED_ICLASS_VPMAXUD;
    
    } else if ( drpin_opcode == OP_vpmaxuq) {

        pin_opcode = XED_ICLASS_VPMAXUQ;
    
    } else if ( drpin_opcode == OP_vpmaxuw) {

        pin_opcode = XED_ICLASS_VPMAXUW;
    
    } else if ( drpin_opcode == OP_vpminsb) {

        pin_opcode = XED_ICLASS_VPMINSB;
    
    } else if ( drpin_opcode == OP_vpminsd) {

        pin_opcode = XED_ICLASS_VPMINSD;
    
    } else if ( drpin_opcode == OP_vpminsq) {

        pin_opcode = XED_ICLASS_VPMINSQ;
    
    } else if ( drpin_opcode == OP_vpminsw) {

        pin_opcode = XED_ICLASS_VPMINSW;
    
    } else if ( drpin_opcode == OP_vpminub) {

        pin_opcode = XED_ICLASS_VPMINUB;
    
    } else if ( drpin_opcode == OP_vpminud) {

        pin_opcode = XED_ICLASS_VPMINUD;
    
    } else if ( drpin_opcode == OP_vpminuq) {

        pin_opcode = XED_ICLASS_VPMINUQ;
    
    } else if ( drpin_opcode == OP_vpminuw) {

        pin_opcode = XED_ICLASS_VPMINUW;
    
    } else if ( drpin_opcode == OP_vpmovb2m) {

        pin_opcode = XED_ICLASS_VPMOVB2M;
    
    } else if ( drpin_opcode == OP_vpmovd2m) {

        pin_opcode = XED_ICLASS_VPMOVD2M;
    
    } else if ( drpin_opcode == OP_vpmovdb) {

        pin_opcode = XED_ICLASS_VPMOVDB;
    
    } else if ( drpin_opcode == OP_vpmovdw) {

        pin_opcode = XED_ICLASS_VPMOVDW;
    
    } else if ( drpin_opcode == OP_vpmovm2b) {

        pin_opcode = XED_ICLASS_VPMOVM2B;
    
    } else if ( drpin_opcode == OP_vpmovm2d) {

        pin_opcode = XED_ICLASS_VPMOVM2D;
    
    } else if ( drpin_opcode == OP_vpmovm2q) {

        pin_opcode = XED_ICLASS_VPMOVM2Q;
    
    } else if ( drpin_opcode == OP_vpmovm2w) {

        pin_opcode = XED_ICLASS_VPMOVM2W;
    
    } else if ( drpin_opcode == OP_vpmovmskb) {

        pin_opcode = XED_ICLASS_VPMOVMSKB;
    
    } else if ( drpin_opcode == OP_vpmovq2m) {

        pin_opcode = XED_ICLASS_VPMOVQ2M;
    
    } else if ( drpin_opcode == OP_vpmovqb) {

        pin_opcode = XED_ICLASS_VPMOVQB;
    
    } else if ( drpin_opcode == OP_vpmovqd) {

        pin_opcode = XED_ICLASS_VPMOVQD;
    
    } else if ( drpin_opcode == OP_vpmovqw) {

        pin_opcode = XED_ICLASS_VPMOVQW;
    
    } else if ( drpin_opcode == OP_vpmovsdb) {

        pin_opcode = XED_ICLASS_VPMOVSDB;
    
    } else if ( drpin_opcode == OP_vpmovsdw) {

        pin_opcode = XED_ICLASS_VPMOVSDW;
    
    } else if ( drpin_opcode == OP_vpmovsqb) {

        pin_opcode = XED_ICLASS_VPMOVSQB;
    
    } else if ( drpin_opcode == OP_vpmovsqd) {

        pin_opcode = XED_ICLASS_VPMOVSQD;
    
    } else if ( drpin_opcode == OP_vpmovsqw) {

        pin_opcode = XED_ICLASS_VPMOVSQW;
    
    } else if ( drpin_opcode == OP_vpmovswb) {

        pin_opcode = XED_ICLASS_VPMOVSWB;
    
    } else if ( drpin_opcode == OP_vpmovsxbd) {

        pin_opcode = XED_ICLASS_VPMOVSXBD;
    
    } else if ( drpin_opcode == OP_vpmovsxbq) {

        pin_opcode = XED_ICLASS_VPMOVSXBQ;
    
    } else if ( drpin_opcode == OP_vpmovsxbw) {

        pin_opcode = XED_ICLASS_VPMOVSXBW;
    
    } else if ( drpin_opcode == OP_vpmovsxdq) {

        pin_opcode = XED_ICLASS_VPMOVSXDQ;
    
    } else if ( drpin_opcode == OP_vpmovsxwd) {

        pin_opcode = XED_ICLASS_VPMOVSXWD;
    
    } else if ( drpin_opcode == OP_vpmovsxwq) {

        pin_opcode = XED_ICLASS_VPMOVSXWQ;
    
    } else if ( drpin_opcode == OP_vpmovusdb) {

        pin_opcode = XED_ICLASS_VPMOVUSDB;
    
    } else if ( drpin_opcode == OP_vpmovusdw) {

        pin_opcode = XED_ICLASS_VPMOVUSDW;
    
    } else if ( drpin_opcode == OP_vpmovusqb) {

        pin_opcode = XED_ICLASS_VPMOVUSQB;
    
    } else if ( drpin_opcode == OP_vpmovusqd) {

        pin_opcode = XED_ICLASS_VPMOVUSQD;
    
    } else if ( drpin_opcode == OP_vpmovusqw) {

        pin_opcode = XED_ICLASS_VPMOVUSQW;
    
    } else if ( drpin_opcode == OP_vpmovuswb) {

        pin_opcode = XED_ICLASS_VPMOVUSWB;
    
    } else if ( drpin_opcode == OP_vpmovw2m) {

        pin_opcode = XED_ICLASS_VPMOVW2M;
    
    } else if ( drpin_opcode == OP_vpmovwb) {

        pin_opcode = XED_ICLASS_VPMOVWB;
    
    } else if ( drpin_opcode == OP_vpmovzxbd) {

        pin_opcode = XED_ICLASS_VPMOVZXBD;
    
    } else if ( drpin_opcode == OP_vpmovzxbq) {

        pin_opcode = XED_ICLASS_VPMOVZXBQ;
    
    } else if ( drpin_opcode == OP_vpmovzxbw) {

        pin_opcode = XED_ICLASS_VPMOVZXBW;
    
    } else if ( drpin_opcode == OP_vpmovzxdq) {

        pin_opcode = XED_ICLASS_VPMOVZXDQ;
    
    } else if ( drpin_opcode == OP_vpmovzxwd) {

        pin_opcode = XED_ICLASS_VPMOVZXWD;
    
    } else if ( drpin_opcode == OP_vpmovzxwq) {

        pin_opcode = XED_ICLASS_VPMOVZXWQ;
    
    } else if ( drpin_opcode == OP_vpmuldq) {

        pin_opcode = XED_ICLASS_VPMULDQ;
    
    } else if ( drpin_opcode == OP_vpmulhrsw) {

        pin_opcode = XED_ICLASS_VPMULHRSW;
    
    } else if ( drpin_opcode == OP_vpmulhuw) {

        pin_opcode = XED_ICLASS_VPMULHUW;
    
    } else if ( drpin_opcode == OP_vpmulhw) {

        pin_opcode = XED_ICLASS_VPMULHW;
    
    } else if ( drpin_opcode == OP_vpmulld) {

        pin_opcode = XED_ICLASS_VPMULLD;
    
    } else if ( drpin_opcode == OP_vpmullq) {

        pin_opcode = XED_ICLASS_VPMULLQ;
    
    } else if ( drpin_opcode == OP_vpmullw) {

        pin_opcode = XED_ICLASS_VPMULLW;
    
    // } else if ( drpin_opcode == OP_vpmultishiftqb) {

    //     pin_opcode = XED_ICLASS_VPMULTISHIFTQB;
    
    } else if ( drpin_opcode == OP_vpmuludq) {

        pin_opcode = XED_ICLASS_VPMULUDQ;
    
    } else if ( drpin_opcode == OP_vpor) {

        pin_opcode = XED_ICLASS_VPOR;
    
    } else if ( drpin_opcode == OP_vpord) {

        pin_opcode = XED_ICLASS_VPORD;
    
    } else if ( drpin_opcode == OP_vporq) {

        pin_opcode = XED_ICLASS_VPORQ;
    
    } else if ( drpin_opcode == OP_vpperm) {

        pin_opcode = XED_ICLASS_VPPERM;
    
    } else if ( drpin_opcode == OP_vprold) {

        pin_opcode = XED_ICLASS_VPROLD;
    
    } else if ( drpin_opcode == OP_vprolq) {

        pin_opcode = XED_ICLASS_VPROLQ;
    
    } else if ( drpin_opcode == OP_vprolvd) {

        pin_opcode = XED_ICLASS_VPROLVD;
    
    } else if ( drpin_opcode == OP_vprolvq) {

        pin_opcode = XED_ICLASS_VPROLVQ;
    
    } else if ( drpin_opcode == OP_vprord) {

        pin_opcode = XED_ICLASS_VPRORD;
    
    } else if ( drpin_opcode == OP_vprorq) {

        pin_opcode = XED_ICLASS_VPRORQ;
    
    } else if ( drpin_opcode == OP_vprorvd) {

        pin_opcode = XED_ICLASS_VPRORVD;
    
    } else if ( drpin_opcode == OP_vprorvq) {

        pin_opcode = XED_ICLASS_VPRORVQ;
    
    } else if ( drpin_opcode == OP_vprotb) {

        pin_opcode = XED_ICLASS_VPROTB;
    
    } else if ( drpin_opcode == OP_vprotd) {

        pin_opcode = XED_ICLASS_VPROTD;
    
    } else if ( drpin_opcode == OP_vprotq) {

        pin_opcode = XED_ICLASS_VPROTQ;
    
    } else if ( drpin_opcode == OP_vprotw) {

        pin_opcode = XED_ICLASS_VPROTW;
    
    } else if ( drpin_opcode == OP_vpsadbw) {

        pin_opcode = XED_ICLASS_VPSADBW;
    
    } else if ( drpin_opcode == OP_vpscatterdd) {

        pin_opcode = XED_ICLASS_VPSCATTERDD;
    
    } else if ( drpin_opcode == OP_vpscatterdq) {

        pin_opcode = XED_ICLASS_VPSCATTERDQ;
    
    } else if ( drpin_opcode == OP_vpscatterqd) {

        pin_opcode = XED_ICLASS_VPSCATTERQD;
    
    } else if ( drpin_opcode == OP_vpscatterqq) {

        pin_opcode = XED_ICLASS_VPSCATTERQQ;
    
    } else if ( drpin_opcode == OP_vpshab) {

        pin_opcode = XED_ICLASS_VPSHAB;
    
    } else if ( drpin_opcode == OP_vpshad) {

        pin_opcode = XED_ICLASS_VPSHAD;
    
    } else if ( drpin_opcode == OP_vpshaq) {

        pin_opcode = XED_ICLASS_VPSHAQ;
    
    } else if ( drpin_opcode == OP_vpshaw) {

        pin_opcode = XED_ICLASS_VPSHAW;
    
    } else if ( drpin_opcode == OP_vpshlb) {

        pin_opcode = XED_ICLASS_VPSHLB;
    
    } else if ( drpin_opcode == OP_vpshld) {

        pin_opcode = XED_ICLASS_VPSHLD;
    
    } else if ( drpin_opcode == OP_vpshlq) {

        pin_opcode = XED_ICLASS_VPSHLQ;
    
    } else if ( drpin_opcode == OP_vpshlw) {

        pin_opcode = XED_ICLASS_VPSHLW;
    
    } else if ( drpin_opcode == OP_vpshufb) {

        pin_opcode = XED_ICLASS_VPSHUFB;
    
    } else if ( drpin_opcode == OP_vpshufd) {

        pin_opcode = XED_ICLASS_VPSHUFD;
    
    } else if ( drpin_opcode == OP_vpshufhw) {

        pin_opcode = XED_ICLASS_VPSHUFHW;
    
    } else if ( drpin_opcode == OP_vpshuflw) {

        pin_opcode = XED_ICLASS_VPSHUFLW;
    
    } else if ( drpin_opcode == OP_vpsignb) {

        pin_opcode = XED_ICLASS_VPSIGNB;
    
    } else if ( drpin_opcode == OP_vpsignd) {

        pin_opcode = XED_ICLASS_VPSIGND;
    
    } else if ( drpin_opcode == OP_vpsignw) {

        pin_opcode = XED_ICLASS_VPSIGNW;
    
    } else if ( drpin_opcode == OP_vpslld) {

        pin_opcode = XED_ICLASS_VPSLLD;
    
    } else if ( drpin_opcode == OP_vpslldq) {

        pin_opcode = XED_ICLASS_VPSLLDQ;
    
    } else if ( drpin_opcode == OP_vpsllq) {

        pin_opcode = XED_ICLASS_VPSLLQ;
    
    } else if ( drpin_opcode == OP_vpsllvd) {

        pin_opcode = XED_ICLASS_VPSLLVD;
    
    } else if ( drpin_opcode == OP_vpsllvq) {

        pin_opcode = XED_ICLASS_VPSLLVQ;
    
    } else if ( drpin_opcode == OP_vpsllvw) {

        pin_opcode = XED_ICLASS_VPSLLVW;
    
    } else if ( drpin_opcode == OP_vpsllw) {

        pin_opcode = XED_ICLASS_VPSLLW;
    
    } else if ( drpin_opcode == OP_vpsrad) {

        pin_opcode = XED_ICLASS_VPSRAD;
    
    } else if ( drpin_opcode == OP_vpsraq) {

        pin_opcode = XED_ICLASS_VPSRAQ;
    
    } else if ( drpin_opcode == OP_vpsravd) {

        pin_opcode = XED_ICLASS_VPSRAVD;
    
    } else if ( drpin_opcode == OP_vpsravq) {

        pin_opcode = XED_ICLASS_VPSRAVQ;
    
    } else if ( drpin_opcode == OP_vpsravw) {

        pin_opcode = XED_ICLASS_VPSRAVW;
    
    } else if ( drpin_opcode == OP_vpsraw) {

        pin_opcode = XED_ICLASS_VPSRAW;
    
    } else if ( drpin_opcode == OP_vpsrld) {

        pin_opcode = XED_ICLASS_VPSRLD;
    
    } else if ( drpin_opcode == OP_vpsrldq) {

        pin_opcode = XED_ICLASS_VPSRLDQ;
    
    } else if ( drpin_opcode == OP_vpsrlq) {

        pin_opcode = XED_ICLASS_VPSRLQ;
    
    } else if ( drpin_opcode == OP_vpsrlvd) {

        pin_opcode = XED_ICLASS_VPSRLVD;
    
    } else if ( drpin_opcode == OP_vpsrlvq) {

        pin_opcode = XED_ICLASS_VPSRLVQ;
    
    } else if ( drpin_opcode == OP_vpsrlvw) {

        pin_opcode = XED_ICLASS_VPSRLVW;
    
    } else if ( drpin_opcode == OP_vpsrlw) {

        pin_opcode = XED_ICLASS_VPSRLW;
    
    } else if ( drpin_opcode == OP_vpsubb) {

        pin_opcode = XED_ICLASS_VPSUBB;
    
    } else if ( drpin_opcode == OP_vpsubd) {

        pin_opcode = XED_ICLASS_VPSUBD;
    
    } else if ( drpin_opcode == OP_vpsubq) {

        pin_opcode = XED_ICLASS_VPSUBQ;
    
    } else if ( drpin_opcode == OP_vpsubsb) {

        pin_opcode = XED_ICLASS_VPSUBSB;
    
    } else if ( drpin_opcode == OP_vpsubsw) {

        pin_opcode = XED_ICLASS_VPSUBSW;
    
    } else if ( drpin_opcode == OP_vpsubusb) {

        pin_opcode = XED_ICLASS_VPSUBUSB;
    
    } else if ( drpin_opcode == OP_vpsubusw) {

        pin_opcode = XED_ICLASS_VPSUBUSW;
    
    } else if ( drpin_opcode == OP_vpsubw) {

        pin_opcode = XED_ICLASS_VPSUBW;
    
    } else if ( drpin_opcode == OP_vpternlogd) {

        pin_opcode = XED_ICLASS_VPTERNLOGD;
    
    } else if ( drpin_opcode == OP_vpternlogq) {

        pin_opcode = XED_ICLASS_VPTERNLOGQ;
    
    } else if ( drpin_opcode == OP_vptest) {

        pin_opcode = XED_ICLASS_VPTEST;
    
    } else if ( drpin_opcode == OP_vptestmb) {

        pin_opcode = XED_ICLASS_VPTESTMB;
    
    } else if ( drpin_opcode == OP_vptestmd) {

        pin_opcode = XED_ICLASS_VPTESTMD;
    
    } else if ( drpin_opcode == OP_vptestmq) {

        pin_opcode = XED_ICLASS_VPTESTMQ;
    
    } else if ( drpin_opcode == OP_vptestmw) {

        pin_opcode = XED_ICLASS_VPTESTMW;
    
    } else if ( drpin_opcode == OP_vptestnmb) {

        pin_opcode = XED_ICLASS_VPTESTNMB;
    
    } else if ( drpin_opcode == OP_vptestnmd) {

        pin_opcode = XED_ICLASS_VPTESTNMD;
    
    } else if ( drpin_opcode == OP_vptestnmq) {

        pin_opcode = XED_ICLASS_VPTESTNMQ;
    
    } else if ( drpin_opcode == OP_vptestnmw) {

        pin_opcode = XED_ICLASS_VPTESTNMW;
    
    } else if ( drpin_opcode == OP_vpunpckhbw) {

        pin_opcode = XED_ICLASS_VPUNPCKHBW;
    
    } else if ( drpin_opcode == OP_vpunpckhdq) {

        pin_opcode = XED_ICLASS_VPUNPCKHDQ;
    
    } else if ( drpin_opcode == OP_vpunpckhqdq) {

        pin_opcode = XED_ICLASS_VPUNPCKHQDQ;
    
    } else if ( drpin_opcode == OP_vpunpckhwd) {

        pin_opcode = XED_ICLASS_VPUNPCKHWD;
    
    } else if ( drpin_opcode == OP_vpunpcklbw) {

        pin_opcode = XED_ICLASS_VPUNPCKLBW;
    
    } else if ( drpin_opcode == OP_vpunpckldq) {

        pin_opcode = XED_ICLASS_VPUNPCKLDQ;
    
    } else if ( drpin_opcode == OP_vpunpcklqdq) {

        pin_opcode = XED_ICLASS_VPUNPCKLQDQ;
    
    } else if ( drpin_opcode == OP_vpunpcklwd) {

        pin_opcode = XED_ICLASS_VPUNPCKLWD;
    
    } else if ( drpin_opcode == OP_vpxor) {

        pin_opcode = XED_ICLASS_VPXOR;
    
    } else if ( drpin_opcode == OP_vpxord) {

        pin_opcode = XED_ICLASS_VPXORD;
    
    } else if ( drpin_opcode == OP_vpxorq) {

        pin_opcode = XED_ICLASS_VPXORQ;
    
    } else if ( drpin_opcode == OP_vrangepd) {

        pin_opcode = XED_ICLASS_VRANGEPD;
    
    } else if ( drpin_opcode == OP_vrangeps) {

        pin_opcode = XED_ICLASS_VRANGEPS;
    
    } else if ( drpin_opcode == OP_vrangesd) {

        pin_opcode = XED_ICLASS_VRANGESD;
    
    } else if ( drpin_opcode == OP_vrangess) {

        pin_opcode = XED_ICLASS_VRANGESS;
    
    } else if ( drpin_opcode == OP_vrcp14pd) {

        pin_opcode = XED_ICLASS_VRCP14PD;
    
    } else if ( drpin_opcode == OP_vrcp14ps) {

        pin_opcode = XED_ICLASS_VRCP14PS;
    
    } else if ( drpin_opcode == OP_vrcp14sd) {

        pin_opcode = XED_ICLASS_VRCP14SD;
    
    } else if ( drpin_opcode == OP_vrcp14ss) {

        pin_opcode = XED_ICLASS_VRCP14SS;
    
    } else if ( drpin_opcode == OP_vrcp28pd) {

        pin_opcode = XED_ICLASS_VRCP28PD;
    
    } else if ( drpin_opcode == OP_vrcp28ps) {

        pin_opcode = XED_ICLASS_VRCP28PS;
    
    } else if ( drpin_opcode == OP_vrcp28sd) {

        pin_opcode = XED_ICLASS_VRCP28SD;
    
    } else if ( drpin_opcode == OP_vrcp28ss) {

        pin_opcode = XED_ICLASS_VRCP28SS;
    
    } else if ( drpin_opcode == OP_vrcpps) {

        pin_opcode = XED_ICLASS_VRCPPS;
    
    } else if ( drpin_opcode == OP_vrcpss) {

        pin_opcode = XED_ICLASS_VRCPSS;
    
    } else if ( drpin_opcode == OP_vreducepd) {

        pin_opcode = XED_ICLASS_VREDUCEPD;
    
    } else if ( drpin_opcode == OP_vreduceps) {

        pin_opcode = XED_ICLASS_VREDUCEPS;
    
    } else if ( drpin_opcode == OP_vreducesd) {

        pin_opcode = XED_ICLASS_VREDUCESD;
    
    } else if ( drpin_opcode == OP_vreducess) {

        pin_opcode = XED_ICLASS_VREDUCESS;
    
    } else if ( drpin_opcode == OP_vrndscalepd) {

        pin_opcode = XED_ICLASS_VRNDSCALEPD;
    
    } else if ( drpin_opcode == OP_vrndscaleps) {

        pin_opcode = XED_ICLASS_VRNDSCALEPS;
    
    } else if ( drpin_opcode == OP_vrndscalesd) {

        pin_opcode = XED_ICLASS_VRNDSCALESD;
    
    } else if ( drpin_opcode == OP_vrndscaless) {

        pin_opcode = XED_ICLASS_VRNDSCALESS;
    
    } else if ( drpin_opcode == OP_vroundpd) {

        pin_opcode = XED_ICLASS_VROUNDPD;
    
    } else if ( drpin_opcode == OP_vroundps) {

        pin_opcode = XED_ICLASS_VROUNDPS;
    
    } else if ( drpin_opcode == OP_vroundsd) {

        pin_opcode = XED_ICLASS_VROUNDSD;
    
    } else if ( drpin_opcode == OP_vroundss) {

        pin_opcode = XED_ICLASS_VROUNDSS;
    
    } else if ( drpin_opcode == OP_vrsqrt14pd) {

        pin_opcode = XED_ICLASS_VRSQRT14PD;
    
    } else if ( drpin_opcode == OP_vrsqrt14ps) {

        pin_opcode = XED_ICLASS_VRSQRT14PS;
    
    } else if ( drpin_opcode == OP_vrsqrt14sd) {

        pin_opcode = XED_ICLASS_VRSQRT14SD;
    
    } else if ( drpin_opcode == OP_vrsqrt14ss) {

        pin_opcode = XED_ICLASS_VRSQRT14SS;
    
    } else if ( drpin_opcode == OP_vrsqrt28pd) {

        pin_opcode = XED_ICLASS_VRSQRT28PD;
    
    } else if ( drpin_opcode == OP_vrsqrt28ps) {

        pin_opcode = XED_ICLASS_VRSQRT28PS;
    
    } else if ( drpin_opcode == OP_vrsqrt28sd) {

        pin_opcode = XED_ICLASS_VRSQRT28SD;
    
    } else if ( drpin_opcode == OP_vrsqrt28ss) {

        pin_opcode = XED_ICLASS_VRSQRT28SS;
    
    } else if ( drpin_opcode == OP_vrsqrtps) {

        pin_opcode = XED_ICLASS_VRSQRTPS;
    
    } else if ( drpin_opcode == OP_vrsqrtss) {

        pin_opcode = XED_ICLASS_VRSQRTSS;
    
    } else if ( drpin_opcode == OP_vscalefpd) {

        pin_opcode = XED_ICLASS_VSCALEFPD;
    
    } else if ( drpin_opcode == OP_vscalefps) {

        pin_opcode = XED_ICLASS_VSCALEFPS;
    
    } else if ( drpin_opcode == OP_vscalefsd) {

        pin_opcode = XED_ICLASS_VSCALEFSD;
    
    } else if ( drpin_opcode == OP_vscalefss) {

        pin_opcode = XED_ICLASS_VSCALEFSS;
    
    } else if ( drpin_opcode == OP_vscatterdpd) {

        pin_opcode = XED_ICLASS_VSCATTERDPD;
    
    } else if ( drpin_opcode == OP_vscatterdps) {

        pin_opcode = XED_ICLASS_VSCATTERDPS;
    
    } else if ( drpin_opcode == OP_vscatterpf0dpd) {

        pin_opcode = XED_ICLASS_VSCATTERPF0DPD;
    
    } else if ( drpin_opcode == OP_vscatterpf0dps) {

        pin_opcode = XED_ICLASS_VSCATTERPF0DPS;
    
    } else if ( drpin_opcode == OP_vscatterpf0qpd) {

        pin_opcode = XED_ICLASS_VSCATTERPF0QPD;
    
    } else if ( drpin_opcode == OP_vscatterpf0qps) {

        pin_opcode = XED_ICLASS_VSCATTERPF0QPS;
    
    } else if ( drpin_opcode == OP_vscatterpf1dpd) {

        pin_opcode = XED_ICLASS_VSCATTERPF1DPD;
    
    } else if ( drpin_opcode == OP_vscatterpf1dps) {

        pin_opcode = XED_ICLASS_VSCATTERPF1DPS;
    
    } else if ( drpin_opcode == OP_vscatterpf1qpd) {

        pin_opcode = XED_ICLASS_VSCATTERPF1QPD;
    
    } else if ( drpin_opcode == OP_vscatterpf1qps) {

        pin_opcode = XED_ICLASS_VSCATTERPF1QPS;
    
    } else if ( drpin_opcode == OP_vscatterqpd) {

        pin_opcode = XED_ICLASS_VSCATTERQPD;
    
    } else if ( drpin_opcode == OP_vscatterqps) {

        pin_opcode = XED_ICLASS_VSCATTERQPS;
    
    } else if ( drpin_opcode == OP_vshuff32x4) {

        pin_opcode = XED_ICLASS_VSHUFF32X4;
    
    } else if ( drpin_opcode == OP_vshuff64x2) {

        pin_opcode = XED_ICLASS_VSHUFF64X2;
    
    } else if ( drpin_opcode == OP_vshufi32x4) {

        pin_opcode = XED_ICLASS_VSHUFI32X4;
    
    } else if ( drpin_opcode == OP_vshufi64x2) {

        pin_opcode = XED_ICLASS_VSHUFI64X2;
    
    } else if ( drpin_opcode == OP_vshufpd) {

        pin_opcode = XED_ICLASS_VSHUFPD;
    
    } else if ( drpin_opcode == OP_vshufps) {

        pin_opcode = XED_ICLASS_VSHUFPS;
    
    } else if ( drpin_opcode == OP_vsqrtpd) {

        pin_opcode = XED_ICLASS_VSQRTPD;
    
    } else if ( drpin_opcode == OP_vsqrtps) {

        pin_opcode = XED_ICLASS_VSQRTPS;
    
    } else if ( drpin_opcode == OP_vsqrtsd) {

        pin_opcode = XED_ICLASS_VSQRTSD;
    
    } else if ( drpin_opcode == OP_vsqrtss) {

        pin_opcode = XED_ICLASS_VSQRTSS;
    
    } else if ( drpin_opcode == OP_vstmxcsr) {

        pin_opcode = XED_ICLASS_VSTMXCSR;
    
    } else if ( drpin_opcode == OP_vsubpd) {

        pin_opcode = XED_ICLASS_VSUBPD;
    
    } else if ( drpin_opcode == OP_vsubps) {

        pin_opcode = XED_ICLASS_VSUBPS;
    
    } else if ( drpin_opcode == OP_vsubsd) {

        pin_opcode = XED_ICLASS_VSUBSD;
    
    } else if ( drpin_opcode == OP_vsubss) {

        pin_opcode = XED_ICLASS_VSUBSS;
    
    } else if ( drpin_opcode == OP_vtestpd) {

        pin_opcode = XED_ICLASS_VTESTPD;
    
    } else if ( drpin_opcode == OP_vtestps) {

        pin_opcode = XED_ICLASS_VTESTPS;
    
    } else if ( drpin_opcode == OP_vucomisd) {

        pin_opcode = XED_ICLASS_VUCOMISD;
    
    } else if ( drpin_opcode == OP_vucomiss) {

        pin_opcode = XED_ICLASS_VUCOMISS;
    
    } else if ( drpin_opcode == OP_vunpckhpd) {

        pin_opcode = XED_ICLASS_VUNPCKHPD;
    
    } else if ( drpin_opcode == OP_vunpckhps) {

        pin_opcode = XED_ICLASS_VUNPCKHPS;
    
    } else if ( drpin_opcode == OP_vunpcklpd) {

        pin_opcode = XED_ICLASS_VUNPCKLPD;
    
    } else if ( drpin_opcode == OP_vunpcklps) {

        pin_opcode = XED_ICLASS_VUNPCKLPS;
    
    } else if ( drpin_opcode == OP_vxorpd) {

        pin_opcode = XED_ICLASS_VXORPD;
    
    } else if ( drpin_opcode == OP_vxorps) {

        pin_opcode = XED_ICLASS_VXORPS;
    
    } else if ( drpin_opcode == OP_vzeroall) {

        pin_opcode = XED_ICLASS_VZEROALL;
    
    } else if ( drpin_opcode == OP_vzeroupper) {

        pin_opcode = XED_ICLASS_VZEROUPPER;
    
    } else if ( drpin_opcode == OP_wbinvd) {

        pin_opcode = XED_ICLASS_WBINVD;
    
    } else if ( drpin_opcode == OP_wrfsbase) {

        pin_opcode = XED_ICLASS_WRFSBASE;
    
    } else if ( drpin_opcode == OP_wrgsbase) {

        pin_opcode = XED_ICLASS_WRGSBASE;
    
    } else if ( drpin_opcode == OP_wrmsr) {

        pin_opcode = XED_ICLASS_WRMSR;
    
    } else if ( drpin_opcode == OP_xabort) {

        pin_opcode = XED_ICLASS_XABORT;
    
    } else if ( drpin_opcode == OP_xadd) {

        pin_opcode = XED_ICLASS_XADD;
    
    } else if ( drpin_opcode == OP_xbegin) {

        pin_opcode = XED_ICLASS_XBEGIN;
    
    } else if ( drpin_opcode == OP_xchg) {

        pin_opcode = XED_ICLASS_XCHG;
    
    } else if ( drpin_opcode == OP_xend) {

        pin_opcode = XED_ICLASS_XEND;
    
    } else if ( drpin_opcode == OP_xgetbv) {

        pin_opcode = XED_ICLASS_XGETBV;
    
    } else if ( drpin_opcode == OP_xlat) {

        pin_opcode = XED_ICLASS_XLAT;
    
    } else if ( drpin_opcode == OP_xor) {

        pin_opcode = XED_ICLASS_XOR;
    
    } else if ( drpin_opcode == OP_xorpd) {

        pin_opcode = XED_ICLASS_XORPD;
    
    } else if ( drpin_opcode == OP_xorps) {

        pin_opcode = XED_ICLASS_XORPS;
    
    } else if ( drpin_opcode == OP_xrstor32) {

        pin_opcode = XED_ICLASS_XRSTOR;
    
    } else if ( drpin_opcode == OP_xrstor64) {

        pin_opcode = XED_ICLASS_XRSTOR64;
    
    // } else if ( drpin_opcode == OP_xrstor) {

    //     pin_opcode = XED_ICLASS_XRSTORS;
    
    // } else if ( drpin_opcode == OP_xrstors64) {

    //     pin_opcode = XED_ICLASS_XRSTORS64;
    
    } else if ( drpin_opcode == OP_xsave32) {

        pin_opcode = XED_ICLASS_XSAVE;
    
    } else if ( drpin_opcode == OP_xsave64) {

        pin_opcode = XED_ICLASS_XSAVE64;
    
    } else if ( drpin_opcode == OP_xsavec32) {

        pin_opcode = XED_ICLASS_XSAVEC;
    
    } else if ( drpin_opcode == OP_xsavec64) {

        pin_opcode = XED_ICLASS_XSAVEC64;
    
    } else if ( drpin_opcode == OP_xsaveopt32) {

        pin_opcode = XED_ICLASS_XSAVEOPT;
    
    } else if ( drpin_opcode == OP_xsaveopt64) {

        pin_opcode = XED_ICLASS_XSAVEOPT64;
    
    // } else if ( drpin_opcode == OP_xsave) {

    //     pin_opcode = XED_ICLASS_XSAVES;
    
    // } else if ( drpin_opcode == OP_xsaves64) {

    //     pin_opcode = XED_ICLASS_XSAVES64;
    
    } else if ( drpin_opcode == OP_xsetbv) {

        pin_opcode = XED_ICLASS_XSETBV;
    
    } else if ( drpin_opcode == OP_xtest) {

        pin_opcode = XED_ICLASS_XTEST;
    
    } else if ( drpin_opcode == OP_LAST) {

        pin_opcode = XED_ICLASS_LAST;
   } else {

        std::cout << "INS_Opcode()" << std::endl;
        std::cout << "DrPin currently cant handle the following opcode: " << drpin_opcode << std::endl << std::flush;
        std::cout << "Instruction disassembly: " << INS_Disassemble(ins) << std::endl << std::flush;
        // exit(1);
   }
   return pin_opcode;

  }

  DR_EXPORT BOOL INS_IsAtomicUpdate(const INS ins){
    drpin_debug_print("INS_IsAtomicUpdate() called");

    if (ins.instr == NULL || ins.instr_list == NULL){
        return false;
    }

    if (INS_IsXchg(ins) || instr_get_prefix_flag((instr_t *)ins.instr, PREFIX_LOCK)){
        // bool flag = instr_get_prefix_flag((instr_t *)ins.instr, PREFIX_LOCK);
        // std::cout << "o morfetico tem o " << std::endl << std::flush;
        return true;
    } else {
        return false;
    }
  }

  DR_EXPORT BOOL INS_OperandIsImmediate(INS ins, UINT32 n){
    drpin_debug_print("INS_OperandIsImmediate() called");
    if (ins.instr == NULL || ins.instr_list == NULL){
        return false ;
    }
    opnd_t operand;

    if (n < instr_num_srcs((instr_t *)ins.instr)){
        // is a src operand
        operand = instr_get_src((instr_t *)ins.instr, n);
        return opnd_is_immed(operand);
    } else if (n < instr_num_srcs((instr_t *)ins.instr) + instr_num_dsts((instr_t *)ins.instr)){
        // is a dst operand
        operand = instr_get_dst((instr_t *)ins.instr, n - instr_num_srcs((instr_t *)ins.instr));
        return opnd_is_immed(operand);
    } else {
        return false;
    }
  }

  DR_EXPORT BOOL INS_IsDirectBranch(INS ins){
    drpin_debug_print("INS_IsDirectBranch() called");
    if (ins.instr == NULL || ins.instr_list == NULL){
        return false ;
    }
    return  instr_is_near_ubr((instr_t *)ins.instr) || instr_is_cbr((instr_t *)ins.instr);
  }

  DR_EXPORT BOOL INS_IsDirectBranchOrCall(INS ins){
    drpin_debug_print("INS_IsDirectBranchOrCall() called");
    if (ins.instr == NULL || ins.instr_list == NULL){
        return false ;
    }
    return  INS_IsDirectBranch(ins) && INS_IsCall(ins);
  }

  DR_EXPORT UINT32 BBL_NumIns(BBL bbl){
    drpin_debug_print("BBL_NumIns() called");
    if (bbl.instr == NULL || bbl.instr_list == NULL){
        return 0;
    }
    instr_t *instr, *next;
    instrlist_t* bb = (instrlist_t*)bbl.instr_list;
    UINT32 length = 0;
    for (instr = instrlist_first_app(bb); instr != NULL; instr = next) {
      next = instr_get_next_app(instr);
      length ++;
    }
    return length;
  }

}


namespace LEVEL_PINCLIENT {


// functions declarations


  DR_EXPORT THREADID PIN_SpawnInternalThread(ROOT_THREAD_FUNC * pThreadFunc, VOID * arg, size_t stackSize, PIN_THREAD_UID * pThreadUid){
    drpin_debug_print("PIN_SpawnInternalThread called");
    void (*drfunc)(void *param);
    drfunc = pThreadFunc;

    dr_create_client_thread(drfunc, arg);
    // for now
    return 0;
  }

  DR_EXPORT INS INS_Next(INS x){
    drpin_debug_print("INS_Next() called");
    if (x.instr == NULL || x.instr_list == NULL){
        INS ins;
        ins.instr = NULL;
        ins.instr_list = NULL;
        return ins;
    }
    instr_t * next_inst = instr_get_next_app((instr_t*) x.instr);
    INS ins;
    ins.drcontext = x.drcontext;
    ins.instr_list = x.instr_list;
    ins.instr = next_inst;
  }

  DR_EXPORT BOOL INS_Valid(INS x){
    drpin_debug_print("INS_Valid() called");
    drpin_debug_print("piu");
    return x.instr != NULL && x.instr_list != NULL;
  }

  DR_EXPORT USIZE BBL_Size(BBL bbl){
    drpin_debug_print("BBL_Size() called");
    if (bbl.instr == NULL || bbl.instr_list == NULL){
        return 0;
    }

    instr_t *instr, *next;
    instrlist_t* bb = (instrlist_t*)bbl.instr_list;
    USIZE bbl_size = 0;
    for (instr = instrlist_first_app(bb); instr != NULL; instr = next) {
      next = instr_get_next_app(instr);
      app_pc inst_addr = instr_get_app_pc((instr_t*) instr);
      int temp_size = decode_sizeof(bbl.drcontext, inst_addr, NULL, NULL);
      bbl_size += (USIZE) temp_size;
    }
    return bbl_size;
  }

  DR_EXPORT INS BBL_InsHead(BBL x){
      drpin_debug_print("BBL_InsHead() called");
      INS ins;
      ins.drcontext = x.drcontext;
      ins.instr = x.instr;
      ins.instr_list = x.instr_list;
      return ins;
  }

  DR_EXPORT USIZE INS_Size(INS ins){
    drpin_debug_print("INS_Size() called");
    if (ins.instr == NULL || ins.instr_list == NULL){
        return 0;
    }
    app_pc inst_addr = instr_get_app_pc((instr_t*) ins.instr);
    int temp_size = decode_sizeof(ins.drcontext, inst_addr, NULL, NULL);
    return (USIZE) temp_size;
  }

  DR_EXPORT ADDRINT BBL_Address(BBL bbl){
    drpin_debug_print("BBL_Address() called");

    if (bbl.instr == NULL || bbl.instr_list == NULL){
        return 0;
    }

    app_pc bbl_addr = instr_get_app_pc((instr_t*) bbl.instr);
    return (ADDRINT)bbl_addr;
  }

  DR_EXPORT THREADID PIN_ThreadId(){
    drpin_debug_print("PIN_ThreadId() called");
    void* context  = dr_get_current_drcontext();
    thread_id_t tid = dr_get_thread_id(context);
    return (THREADID)tid;
  }

  DR_EXPORT ADDRINT PIN_GetSyscallNumber(const CONTEXT *ctxt, SYSCALL_STANDARD std){
    drpin_debug_print("PIN_GetSyscallNumber() called");
    return (ADDRINT)ctxt->syscallnumber;
  }

  DR_EXPORT VOID PIN_SetSyscallArgument(CONTEXT *ctxt, SYSCALL_STANDARD std, UINT32 argNum, ADDRINT val){
    drpin_debug_print("PIN_SetSyscallArgument() called");
    dr_syscall_set_param(ctxt->drcontext, (int)argNum, (reg_t) val);
  }

  DR_EXPORT ADDRINT PIN_GetSyscallArgument(const CONTEXT *ctxt, SYSCALL_STANDARD std, UINT32 argNum){
    drpin_debug_print("PIN_GetContextReg() called");
    reg_t value = dr_syscall_get_param(ctxt->drcontext, (int)argNum);
    return (ADDRINT) value;
  }

  DR_EXPORT VOID PIN_SetContextReg(CONTEXT * ctxt, REG reg, ADDRINT val){
    drpin_debug_print("PIN_SetContextReg() called");
    dr_mcontext_t mcontext;
    dr_get_mcontext(ctxt->drcontext, &mcontext);
    reg_id_t drpin_reg = convert_pin_reg_to_drpin_reg(reg);
    reg_set_value(drpin_reg, &mcontext, (reg_t) val);
    dr_set_mcontext(ctxt->drcontext, &mcontext);
  }

  DR_EXPORT VOID PIN_SetSyscallNumber(CONTEXT *ctxt, SYSCALL_STANDARD std, ADDRINT val){
    drpin_debug_print("PIN_SetSyscallNumber() called");
    dr_syscall_set_sysnum(ctxt->drcontext, (int)val);
  }

  DR_EXPORT ADDRINT PIN_GetContextReg(const CONTEXT * ctxt, REG reg){
    drpin_debug_print("PIN_GetContextReg called");
    dr_mcontext_t mcontext;
    dr_get_mcontext(ctxt->drcontext, &mcontext);
    reg_id_t drpin_reg = convert_pin_reg_to_drpin_reg(reg);
    reg_t drpin_reg_value = reg_get_value(drpin_reg, &mcontext);
    return (ADDRINT)drpin_reg_value;
  }

  DR_EXPORT size_t PIN_SafeCopy(VOID * dst, const VOID * src, size_t size){
    drpin_debug_print("PIN_SafeCopy");
    memcpy(dst, src, size);
    return size;
  }

  DR_EXPORT VOID PIN_RemoveInstrumentation(){
    std::cout << __func__ << std::endl;
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::cout << "Function not implemented" << std::endl << std::flush;
    exit(1);
  }

  DR_EXPORT BBL TRACE_BblHead(TRACE trace){
    drpin_debug_print("TRACE_BblHead() called");
    return trace.only_bbl;
  }

  DR_EXPORT BOOL BBL_Valid(BBL x){
    drpin_debug_print("BBL_Valid() called");
    if(x.instr != NULL && x.instr_list != NULL){
      return true;
    } else {
      return false;
    }
  }

  DR_EXPORT VOID BBL_InsertCall(BBL bbl, IPOINT action, AFUNPTR funptr, ...){
    drpin_debug_print("BBL_InsertCall() called");

    // if (bbl.instr == NULL || bbl.instr_list == NULL){
    //     return ;
    // }

    // std::vector<opnd_t> call_operands;

    // va_list listPointer;
    // va_start( listPointer, funptr );
    // IARG_TYPE arg = (IARG_TYPE) va_arg( listPointer, int );

    // while( arg != IARG_LAST){

    //   if (arg == IARG_ADDRINT) {

    //     ADDRINT operand = va_arg( listPointer, ADDRINT );
    //     call_operands.push_back(OPND_CREATE_UINT64(operand));

    //   } else if (arg == IARG_UINT32){

    //     UINT32 operand = va_arg( listPointer, UINT32 );
    //     call_operands.push_back(OPND_CREATE_UINT32(operand));

    //   } else if (arg == IARG_FAST_ANALYSIS_CALL){

    //     // We currently do not have an optimization to this case
    // } else if( arg == IARG_THREAD_ID){
    //     thread_id_t tidt = dr_get_thread_id(bbl.drcontext);
    //     call_operands.push_back(OPND_CREATE_UINT32(tidt));
    // } else if( arg == IARG_PTR){
    //     UINT32 operand = va_arg( listPointer, UINT64 );
    //     call_operands.push_back(OPND_CREATE_UINT64(operand));
    //   } else {
        
    //     std::cout << "DrPin does not yet support IARG_TYPE of the type: " << arg << std::endl << std::flush;
    //     exit(1);

    //   }

    //   arg = (IARG_TYPE) va_arg( listPointer, int );

    // }

    // va_end(listPointer);

    // drpin_insert_clean_call(bbl.drcontext, (instrlist_t*) bbl.instr_list, (instr_t *) bbl.instr, (void *) funptr, true, call_operands);


    if (bbl.instr == NULL || bbl.instr_list == NULL){
        return ;
    }

    std::vector<UINT64> iarg_call_arguments;

    va_list listPointer;
    va_start( listPointer, funptr );
    UINT64 arg = (UINT64) va_arg( listPointer, UINT64 );
    iarg_call_arguments.push_back(arg);

    while( arg != IARG_LAST){

        arg = (UINT64) va_arg( listPointer, UINT64 );
        iarg_call_arguments.push_back(arg);

    }

    va_end(listPointer);

    drpin_insert_clean_call(bbl.drcontext, (instrlist_t*) bbl.instr_list, (instr_t *) bbl.instr, (void *) funptr, false, iarg_call_arguments);
  }

  DR_EXPORT BBL BBL_Next(BBL x){
    drpin_debug_print("BBL_Next() called");
    BBL next;
    next.instr = NULL;
    next.instr_list = NULL;
    return next;
  }

  DR_EXPORT INT PIN_GetPid(){
  
    drpin_debug_print("PIN_GetPid() called");
    process_id_t pid = dr_get_process_id();
    return pid;

  }

  DR_EXPORT VOID GetVmLock(){
    drpin_debug_print("GetVmLock() called");
    // std::cout << __func__ << std::endl;
    // std::cout << __PRETTY_FUNCTION__ << std::endl;
    // std::cout << "Function not implemented" << std::endl << std::flush;
    // exit(1);
  }

  DR_EXPORT VOID ReleaseVmLock(){
    drpin_debug_print("SetVmLock() called");
    // std::cout << __func__ << std::endl;
    // std::cout << __PRETTY_FUNCTION__ << std::endl;
    // std::cout << "Function not implemented" << std::endl << std::flush;
    // exit(1);
  }

  DR_EXPORT VOID PIN_InitSymbols(){

    // does nothing yet
    drpin_debug_print("PIN_InitSymbols() called");
  }

  DR_EXPORT PIN_CALLBACK PIN_AddInternalExceptionHandler(INTERNAL_EXCEPTION_CALLBACK fun, VOID *val){
    drpin_debug_print("PIN_AddInternalExceptionHandler() called");

    LEVEL_PINCLIENT::PIN_CALLBACK pincallback  = new LEVEL_PINCLIENT::COMPLEX_CALLBACKVAL_BASE();
    return pincallback;
  }

  DR_EXPORT VOID CHILD_PROCESS_GetCommandLine(CHILD_PROCESS childProcess, INT * pArgc, const CHAR * const ** pArgv){
    std::cout << __func__ << std::endl;
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::cout << "Function not implemented" << std::endl << std::flush;
    exit(1);
  }

  DR_EXPORT VOID CHILD_PROCESS_SetPinCommandLine(CHILD_PROCESS childProcess, INT argc, const CHAR * const * argv){
    std::cout << __func__ << std::endl;
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::cout << "Function not implemented" << std::endl << std::flush;
    exit(1);
  }

  DR_EXPORT PIN_CALLBACK TRACE_AddInstrumentFunction(TRACE_INSTRUMENT_CALLBACK fun, VOID *val){

    drpin_debug_print("TRACE_AddInstrumentFunction() called");

    drpin_bb_event_trace_callbacks.push_back(std::pair<TRACE_INSTRUMENT_CALLBACK, VOID*>(fun, val));;

    LEVEL_PINCLIENT::PIN_CALLBACK pincallback  = new LEVEL_PINCLIENT::COMPLEX_CALLBACKVAL_BASE();
    return pincallback;
  }

  DR_EXPORT PIN_CALLBACK PIN_AddThreadStartFunction(THREAD_START_CALLBACK fun, VOID *val){
    drpin_debug_print("PIN_AddThreadStartFunction() called");
    drpin_thread_init_event_callbacks.push_back(std::pair<THREAD_START_CALLBACK, VOID*>(fun, val));

    LEVEL_PINCLIENT::PIN_CALLBACK pincallback  = new LEVEL_PINCLIENT::COMPLEX_CALLBACKVAL_BASE();
    return pincallback;
  }

  DR_EXPORT PIN_CALLBACK PIN_AddThreadFiniFunction(THREAD_FINI_CALLBACK fun, VOID *val){
    drpin_debug_print("PIN_AddThreadFiniFunction() called");
    drpin_thread_exit_event_callbacks.push_back(std::pair<THREAD_FINI_CALLBACK, VOID*>(fun, val));

    LEVEL_PINCLIENT::PIN_CALLBACK pincallback  = new LEVEL_PINCLIENT::COMPLEX_CALLBACKVAL_BASE();
    return pincallback;
  }

  DR_EXPORT PIN_CALLBACK PIN_AddSyscallEntryFunction(SYSCALL_ENTRY_CALLBACK fun, VOID *val){
    drpin_debug_print("PIN_AddSyscallEntryFunction() called");
    drpin_pre_syscall_event_callbacks.push_back(std::pair<SYSCALL_ENTRY_CALLBACK, VOID*>(fun, val));

    LEVEL_PINCLIENT::PIN_CALLBACK pincallback  = new LEVEL_PINCLIENT::COMPLEX_CALLBACKVAL_BASE();
    return pincallback;
  }

  DR_EXPORT PIN_CALLBACK PIN_AddSyscallExitFunction(SYSCALL_EXIT_CALLBACK fun, VOID *val){
    drpin_debug_print("PIN_AddSyscallExitFunction() called");
    drpin_post_syscall_event_callbacks.push_back(std::pair<SYSCALL_EXIT_CALLBACK, VOID*>(fun, val));

    LEVEL_PINCLIENT::PIN_CALLBACK pincallback  = new LEVEL_PINCLIENT::COMPLEX_CALLBACKVAL_BASE();
    return pincallback;
  }

  DR_EXPORT PIN_CALLBACK PIN_AddContextChangeFunction(CONTEXT_CHANGE_CALLBACK fun, VOID *val){
    // TODO: simulate this behavior
    // dynamorio does not have this kind of functon
    drpin_debug_print("PIN_AddContextChangeFunction() called");

    // drpin_fork_init_event_callbacks.push_back(std::pair<FORK_CALLBACK, VOID*>(fun, val));
    drpin_context_change_event_callbacks.push_back(std::pair<CONTEXT_CHANGE_CALLBACK, VOID*>(fun, val));

    LEVEL_PINCLIENT::PIN_CALLBACK pincallback  = new LEVEL_PINCLIENT::COMPLEX_CALLBACKVAL_BASE();
    return pincallback;
  }

  DR_EXPORT PIN_CALLBACK PIN_AddFollowChildProcessFunction(FOLLOW_CHILD_PROCESS_CALLBACK fun, VOID * val){
    drpin_debug_print("PIN_AddFollowChildProcessFunction() called");
    // for now, we will ignore this because DynamoRIO by default follows all childs
  }

  DR_EXPORT PIN_CALLBACK PIN_AddForkFunction(FPOINT point, FORK_CALLBACK fun, VOID *val){
    // FPOINT dynamorio does not have any kind of distintion to say if it going to called
    // in the parent, the child or whatever
    drpin_debug_print("PIN_AddForkFunction() called");
    drpin_fork_init_event_callbacks.push_back(std::pair<FORK_CALLBACK, VOID*>(fun, val));

    LEVEL_PINCLIENT::PIN_CALLBACK pincallback  = new LEVEL_PINCLIENT::COMPLEX_CALLBACKVAL_BASE();
    return pincallback;
  }

 DR_EXPORT PIN_CALLBACK IMG_AddInstrumentFunction(IMAGECALLBACK fun, VOID *v){
    drpin_img_event_callbacks.push_back(std::pair<IMAGECALLBACK, VOID*>(fun, v));;

    LEVEL_PINCLIENT::PIN_CALLBACK pincallback  = new LEVEL_PINCLIENT::COMPLEX_CALLBACKVAL_BASE();
    return pincallback;
 }


 DR_EXPORT RTN RTN_FindByName(IMG img, const CHAR * name ){
    std::cout << __func__ << std::endl;
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::cout << "Function not implemented" << std::endl << std::flush;
    exit(1);
 }


DR_EXPORT ADDRINT RTN_Address(RTN rtn){
    std::cout << __func__ << std::endl;
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::cout << "Function not implemented" << std::endl << std::flush;
    exit(1);
}

DR_EXPORT RTN RTN_Invalid(){
    std::cout << __func__ << std::endl;
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::cout << "Function not implemented" << std::endl << std::flush;
    exit(1);
}

DR_EXPORT IMG IMG_Open(const string& filename){
    std::cout << __func__ << std::endl;
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::cout << "Function not implemented" << std::endl << std::flush;
    exit(1);
}

DR_EXPORT VOID IMG_Close(IMG img){
    std::cout << __func__ << std::endl;
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::cout << "Function not implemented" << std::endl << std::flush;
    exit(1);
}


  DR_EXPORT INS BBL_InsTail(BBL bbl){
    drpin_debug_print("BBL_InsTail() called");
    INS ins;
    ins.instr = NULL;
    ins.instr_list = NULL;
    if (bbl.instr == NULL || bbl.instr_list == NULL){
        return ins;
    }
    instr_t *instr, *next, *last;
    instrlist_t* bb = (instrlist_t*)bbl.instr_list;
    for (instr = instrlist_first_app(bb); instr != NULL; instr = next) {
      last = instr;
      next = instr_get_next_app(instr);
    }
    ins.drcontext = bbl.drcontext;
    ins.instr_list = bbl.instr_list;
    ins.instr = last;
    return ins;

  }

  DR_EXPORT ADDRINT INS_DirectBranchOrCallTargetAddress (INS ins){
    drpin_debug_print("INS_DirectBranchOrCallTargetAddress() called");
    if (ins.instr == NULL || ins.instr_list == NULL){
        return 0;
    }
    app_pc target_address = instr_get_branch_target_pc((instr_t*) ins.instr);
    return (ADDRINT) target_address;

  }

  DR_EXPORT IMG_TYPE IMG_Type(IMG img){
    drpin_debug_print("IMG_Type() called");
    // TODO: DynamoRIO does not provide this information
    IMG_TYPE img_type = IMG_TYPE_SHAREDLIB;
    return img_type;
  }

  DR_EXPORT BOOL IMG_IsMainExecutable(IMG x){
    drpin_debug_print("IMG_IsMainExecutable() called");
    return x.main_module;
  }

  DR_EXPORT const string& IMG_Name(IMG img) {
    drpin_debug_print("IMG_Name called");
    IMG& img_ref = drpin_find_img_with_uuid(img.img_uniq_identifier);
    return img_ref.name;
  }

  DR_EXPORT SEC IMG_SecHead(IMG img) {
    drpin_debug_print("IMG_SecHead called");

    // There is only one sec per image right now
    SEC& sec_ref = drpin_secs_for_img(img)[0];
    return sec_ref;
  }

  DR_EXPORT BOOL IMG_Valid(IMG img){
      return img.valid;
  }

  DR_EXPORT BOOL SEC_Valid(SEC x){
      return x.valid;
  }

  DR_EXPORT IMG IMG_FindByAddress(ADDRINT address){
    module_data_t * module_data = dr_lookup_module( (unsigned char *) address);
    if(module_data) {
        IMG img = drpin_find_img_by_name(string(module_data->full_path));
        dr_free_module_data(module_data);
        return img;
    } else {
        IMG img;
        img.valid = false;
        dr_free_module_data(module_data);
        return img;
    }
  }

  DR_EXPORT ADDRINT IMG_LowAddress(IMG img){
      return (ADDRINT) img.lowest_address;
  }

  DR_EXPORT ADDRINT IMG_HighAddress(IMG img){
      return (ADDRINT) img.highest_address;
  }

  DR_EXPORT PIN_CALLBACK IMG_AddUnloadFunction(IMAGECALLBACK fun, VOID *v){

    drpin_img_unload_event_callbacks.push_back(std::pair<IMAGECALLBACK, VOID*>(fun, v));;

    LEVEL_PINCLIENT::PIN_CALLBACK pincallback  = new LEVEL_PINCLIENT::COMPLEX_CALLBACKVAL_BASE();
    return pincallback;

  }

  DR_EXPORT string RTN_FindNameByAddress(ADDRINT address){
      
  }
}


DR_EXPORT BOOL INS_IsMemoryRead(INS ins){
    drpin_debug_print("INS_IsMemoryRead() called");
    if (ins.instr == NULL || ins.instr_list == NULL){
        return  false;
    }
    bool flag = instr_reads_memory((instr_t*) ins.instr);
    return flag;
}

DR_EXPORT BOOL INS_IsMemoryWrite(INS ins){
  drpin_debug_print("INS_IsMemoryWrite() called");

    if (ins.instr == NULL || ins.instr_list == NULL){
        return  false;
    }
  bool flag = instr_writes_memory((instr_t*) ins.instr);
  return flag;
}

DR_EXPORT BOOL INS_IsPredicated(INS ins){
    
  drpin_debug_print("INS_IsPredicated() called");

    if (ins.instr == NULL || ins.instr_list == NULL){
        return false;
    }
  bool flag = instr_is_predicated((instr_t*) ins.instr);
  return flag;
}

DR_EXPORT BOOL INS_HasMemoryRead2(INS ins){
    drpin_debug_print("INS_HasMemoryRead2 called");
    if (ins.instr == NULL || ins.instr_list == NULL){
        return  false;
    }
    int num_srcs = instr_num_srcs((instr_t *)ins.instr);
    if (num_srcs < 2){
        return false;
    }
    int memory_refs = 0;
    for(int i = 0; i < num_srcs; i++){
        opnd_t operand = instr_get_src((instr_t *)ins.instr, i);
        bool flag =  opnd_is_memory_reference(operand);
        if (flag){
            memory_refs ++;
        }
    }
    if (memory_refs == 2){
        return true;
    } else {
        return false;
    }
}

DR_EXPORT BOOL INS_IsXchg(INS ins){
  // x86 only API
  drpin_debug_print("INS_IsXchg() called");
    if (ins.instr == NULL || ins.instr_list == NULL){
        return  false;
    }
  int op_code = instr_get_opcode((instr_t*) ins.instr);
  return (op_code == OP_xchg);
}

DR_EXPORT BOOL INS_IsRDTSC(const INS ins){
  // x86 only API
  drpin_debug_print("INS_IsRDTSC() called");
  int op_code = instr_get_opcode((instr_t*) ins.instr);
  return (op_code == OP_rdtsc || op_code == OP_rdtscp);
}

DR_EXPORT BOOL INS_IsCJmp(INS ins){
  drpin_debug_print("INS_IsCJmp() called");
    if (ins.instr == NULL || ins.instr_list == NULL){
        return false;
    }
  bool flag = instr_is_cbr((instr_t*) ins.instr);
  return flag;
}

DR_EXPORT BOOL INS_IsBranch(INS ins){
  drpin_debug_print("INS_IsBranch() called");
    if (ins.instr == NULL || ins.instr_list == NULL){
        return false;
    }
  bool flag = instr_is_cbr((instr_t*) ins.instr) || instr_is_mbr((instr_t*) ins.instr) || instr_is_ubr((instr_t*) ins.instr) || instr_is_near_ubr((instr_t*) ins.instr) ;
  return flag;
}

DR_EXPORT BOOL INS_IsCall(INS ins){
  drpin_debug_print("INS_IsCall() called");
    if (ins.instr == NULL || ins.instr_list == NULL){
        return false;
    }
  bool flag = instr_is_call((instr_t*) ins.instr);
  return flag;
}

DR_EXPORT BOOL INS_IsRet(INS ins){
  drpin_debug_print("INS_IsRet() called");
    if (ins.instr == NULL || ins.instr_list == NULL){
        return false;
    }
  bool flag = instr_is_return((instr_t*) ins.instr);
  return flag;
}






