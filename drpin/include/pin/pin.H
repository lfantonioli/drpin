#if !defined(PIN_H)

#define PIN_H

#define IARG_END IARG_LAST

#include <string>
#include <stddef.h>
#include <iostream>
#include <sstream>      // std::istringstream
#include <map>

typedef signed char int8_t;
typedef short int int16_t;
typedef int int32_t;
typedef long int int64_t;
typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long int uint64_t;

typedef enum
{
    PIN_ERR_NONE = 0,
    PIN_ERR_INTERNAL,
    PIN_ERR_ASSERT,
    PIN_ERR_TOOL,
    PIN_ERR_CMD_LINE,
    PIN_ERR_PARSING,
    PIN_ERR_NO_APP,
    PIN_ERR_INVALID_PLOAD,
    PIN_ERR_FILE_NOT_FOUND,
    PIN_ERR_ELF_HEADER,
    PIN_ERR_NO_PIE,
    PIN_ERR_NO_ENTRY_OFFSET,
    PIN_ERR_INVALID_ADDRESS,
    PIN_ERR_INVALID_ADDRESS_RANGE,
    PIN_ERR_CANNOT_LOAD_TOOL,
    PIN_ERR_PIN_INJECTION,
    PIN_ERR_WAIT_FOR_INJECTOR,
    PIN_ERR_BAD_OS_FILE,
    PIN_ERR_UNSUPPORTED_OS,
    PIN_ERR_BIN32,
    PIN_ERR_BIN64,
    PIN_ERR_CANNOT_RUN,
    PIN_ERR_ATTACH_PID,
    PIN_ERR_ATTACH_NYI,
    PIN_ERR_ATTACH_REJECTED,
    PIN_ERR_ATTACH_PTRACE_SCOPE_1,
    PIN_ERR_DETACH_PID,
    PIN_ERR_WAIT_PID,
    PIN_ERR_STEP_PID,
    PIN_ERR_WAIT_EXECV,
    PIN_ERR_APP_RESUME,
    PIN_ERR_NO_INSTRUMENT,
    PIN_ERR_CHILD_PTRACEME,
    PIN_ERR_CHILD_RESUME,
    PIN_ERR_RELINK_APP,
    PIN_ERR_KNOB_BAD,
    PIN_ERR_NO_RELOCS,
    PIN_ERR_VERSION_SKEW,
    PIN_ERR_MS_DOS,
    PIN_ERR_LONG_PATH,
    PIN_ERR_CANNOT_EXECUTE_FILE,
    PIN_ERR_BLOCKSIG_TOOL,

    PIN_ERR_BLOCKSIG_APP,

    PIN_ERR_USER_SPECIFIED_ERROR,
    PIN_ERR_OUT_OF_MEMORY,
    PIN_ERR_NON_NUMERIC_STRING,
    PIN_ERR_EMPTY_STRING,
    PIN_ERR_NUMERIC_FROM_STRING,
    PIN_ERR_ALREADY_ATTACHED,
    PIN_ERR_ILLEGAL_EXCEPTION,
    PIN_ERR_EXCEPTION_NEEDS_ADDR,
    PIN_ERR_PREDEFINED_INSTRUMENTATION_FAILED,
    PIN_ERR_UNSUPPORTED_SYSCALL,
    PIN_ERR_ACCESS_DENIED,
    PIN_ERR_INVALID_SUSPEND_REQUEST,
    PIN_ERR_DEBUGGER,
    PIN_ERR_LAST
} PIN_ERRTYPE;



namespace FUND {
    typedef uint8_t UINT8;
    typedef uint16_t UINT16;
    typedef uint32_t UINT32;
    typedef uint64_t UINT64;
    typedef int8_t INT8;
    typedef int16_t INT16;
    typedef int32_t INT32;
    typedef int64_t INT64;
    typedef UINT64 PTRINT;
    typedef UINT64 ADDRINT;
    typedef UINT64 ANYADDR;
}

namespace UTIL {

union X87REG_PADDED
{
    struct
    {
        FUND::UINT64 _significand;
        FUND::UINT16 _exponent;
        FUND::UINT16 _pad[3];
    } _fp;
    struct
    {
        FUND::UINT64 _lo;
        FUND::UINT64 _hi;
    } _raw;
};


union XMMREG
{
    FUND::UINT8 _vec8[16];
    FUND::UINT16 _vec16[8];
    FUND::UINT32 _vec32[4];
    FUND::UINT64 _vec64[2];
};


struct FXSAVE_INTEL64_DEFAULT
{
    FUND::UINT16 _fcw;
    FUND::UINT16 _fsw;
    FUND::UINT8 _ftw;
    FUND::UINT8 _pad1;
    FUND::UINT16 _fop;
    FUND::UINT32 _fpuip;
    FUND::UINT16 _cs;
    FUND::UINT16 _pad2;
    FUND::UINT32 _fpudp;
    FUND::UINT16 _ds;
    FUND::UINT16 _pad3;
    FUND::UINT32 _mxcsr;
    FUND::UINT32 _mxcsrmask;
    X87REG_PADDED _sts[8];
    XMMREG _xmms[16];
    FUND::UINT8 _pad4[96];
};


}


namespace LEVEL_BASE {

using namespace std;


extern "C" {
   #include "xed-iclass-enum.h"
   #include "xed-category-enum.h"
}


/*
 * Generic macro definitions
 */

#ifndef MAX
#define MAX(a, b) (((a)>(b))?(a) : (b))
#endif

#ifndef MIN
#define MIN(a, b) (((a)<(b))?(a) : (b))
#endif


typedef char CHAR;

typedef unsigned long UINT64;
typedef void VOID;

typedef uint8_t UINT8;
typedef uint16_t UINT16;
typedef uint32_t UINT32;
typedef uint64_t UINT64;
typedef int8_t INT8;
typedef int16_t INT16;
typedef int32_t INT32;
typedef int64_t INT64;

typedef char CHAR;
typedef unsigned int UINT;
typedef int INT;
typedef double FLT64;
typedef float FLT32;
typedef unsigned int USIZE;
typedef signed int SIZE;

typedef UINT64 ADDRINT;

typedef bool BOOL;
typedef VOID (*AFUNPTR)();


typedef enum
{
    REG_INVALID_ = 0,
    REG_NONE = 1,
    REG_FIRST = 2,
    REG_RBASE,
    REG_MACHINE_BASE = REG_RBASE,
    REG_APPLICATION_BASE = REG_RBASE,
    REG_PHYSICAL_CONTEXT_BEGIN = REG_RBASE,
    REG_GR_BASE = REG_RBASE,
    REG_RDI = REG_GR_BASE,
    REG_GDI = REG_RDI,
    REG_RSI,
    REG_GSI = REG_RSI,
    REG_RBP,
    REG_GBP = REG_RBP,
    REG_RSP,
    REG_STACK_PTR = REG_RSP,
    REG_RBX,
    REG_GBX = REG_RBX,
    REG_RDX,
    REG_GDX = REG_RDX,
    REG_RCX,
    REG_GCX = REG_RCX,
    REG_RAX,
    REG_GAX = REG_RAX,
    REG_R8,
    REG_R9,
    REG_R10,
    REG_R11,
    REG_R12,
    REG_R13,
    REG_R14,
    REG_R15,
    REG_GR_LAST = REG_R15,
    REG_SEG_BASE,
    REG_SEG_CS = REG_SEG_BASE,
    REG_SEG_SS,
    REG_SEG_DS,
    REG_SEG_ES,
    REG_SEG_FS,
    REG_SEG_GS,
    REG_SEG_LAST = REG_SEG_GS,
    REG_RFLAGS,
    REG_GFLAGS=REG_RFLAGS,
    REG_RIP,
    REG_INST_PTR = REG_RIP,
    REG_PHYSICAL_CONTEXT_END = REG_INST_PTR,
    REG_AL,
    REG_AH,
    REG_AX,
    REG_CL,
    REG_CH,
    REG_CX,
    REG_DL,
    REG_DH,
    REG_DX,
    REG_BL,
    REG_BH,
    REG_BX,
    REG_BP,
    REG_SI,
    REG_DI,
    REG_SP,
    REG_FLAGS,
    REG_IP,
    REG_EDI,
    REG_DIL,
    REG_ESI,
    REG_SIL,
    REG_EBP,
    REG_BPL,
    REG_ESP,
    REG_SPL,
    REG_EBX,
    REG_EDX,
    REG_ECX,
    REG_EAX,
    REG_EFLAGS,
    REG_EIP,
    REG_R8B,
    REG_R8W,
    REG_R8D,
    REG_R9B,
    REG_R9W,
    REG_R9D,
    REG_R10B,
    REG_R10W,
    REG_R10D,
    REG_R11B,
    REG_R11W,
    REG_R11D,
    REG_R12B,
    REG_R12W,
    REG_R12D,
    REG_R13B,
    REG_R13W,
    REG_R13D,
    REG_R14B,
    REG_R14W,
    REG_R14D,
    REG_R15B,
    REG_R15W,
    REG_R15D,
    REG_MM_BASE,
    REG_MM0 = REG_MM_BASE,
    REG_MM1,
    REG_MM2,
    REG_MM3,
    REG_MM4,
    REG_MM5,
    REG_MM6,
    REG_MM7,
    REG_MM_LAST = REG_MM7,
    REG_EMM_BASE,
    REG_EMM0 = REG_EMM_BASE,
    REG_EMM1,
    REG_EMM2,
    REG_EMM3,
    REG_EMM4,
    REG_EMM5,
    REG_EMM6,
    REG_EMM7,
    REG_EMM_LAST = REG_EMM7,
    REG_X87,
    REG_XMM_BASE,
    REG_FIRST_FP_REG = REG_XMM_BASE,
    REG_XMM0 = REG_XMM_BASE,
    REG_XMM1,
    REG_XMM2,
    REG_XMM3,
    REG_XMM4,
    REG_XMM5,
    REG_XMM6,
    REG_XMM7,
    REG_XMM8,
    REG_XMM9,
    REG_XMM10,
    REG_XMM11,
    REG_XMM12,
    REG_XMM13,
    REG_XMM14,
    REG_XMM15,
    REG_XMM_LAST = REG_XMM15,
    REG_YMM_BASE,
    REG_YMM0 = REG_YMM_BASE,
    REG_YMM1,
    REG_YMM2,
    REG_YMM3,
    REG_YMM4,
    REG_YMM5,
    REG_YMM6,
    REG_YMM7,
    REG_YMM8,
    REG_YMM9,
    REG_YMM10,
    REG_YMM11,
    REG_YMM12,
    REG_YMM13,
    REG_YMM14,
    REG_YMM15,
    REG_YMM_LAST = REG_YMM15,
    REG_ZMM_BASE,
    REG_ZMM_LAST = REG_ZMM_BASE,
    REG_K_BASE,
    REG_K_LAST = REG_K_BASE,
    REG_MXCSR,
    REG_MXCSRMASK,
    REG_ORIG_RAX,
    REG_ORIG_GAX = REG_ORIG_RAX,
    REG_DR_BASE,
    REG_DR0 = REG_DR_BASE,
    REG_DR1,
    REG_DR2,
    REG_DR3,
    REG_DR4,
    REG_DR5,
    REG_DR6,
    REG_DR7,
    REG_DR_LAST = REG_DR7,
    REG_CR_BASE,
    REG_CR0 = REG_CR_BASE,
    REG_CR1,
    REG_CR2,
    REG_CR3,
    REG_CR4,
    REG_CR_LAST = REG_CR4,
    REG_TSSR,
    REG_LDTR,
    REG_TR_BASE,
    REG_TR = REG_TR_BASE,
    REG_TR3,
    REG_TR4,
    REG_TR5,
    REG_TR6,
    REG_TR7,
    REG_TR_LAST = REG_TR7,
    REG_FPST_BASE,
    REG_FPSTATUS_BASE = REG_FPST_BASE,
    REG_FPCW = REG_FPSTATUS_BASE,
    REG_FPSW,
    REG_FPTAG,
    REG_FPIP_OFF,
    REG_FPIP_SEL,
    REG_FPOPCODE,
    REG_FPDP_OFF,
    REG_FPDP_SEL,
    REG_FPSTATUS_LAST = REG_FPDP_SEL,
    REG_FPTAG_FULL,
    REG_ST_BASE,
    REG_ST0 = REG_ST_BASE,
    REG_ST1,
    REG_ST2,
    REG_ST3,
    REG_ST4,
    REG_ST5,
    REG_ST6,
    REG_ST7,
    REG_ST_LAST = REG_ST7,
    REG_FPST_LAST = REG_ST_LAST,
    REG_MACHINE_LAST = REG_FPST_LAST,
    REG_STATUS_FLAGS,
    REG_DF_FLAG,
    REG_APPLICATION_LAST = REG_DF_FLAG,
    REG_PIN_BASE,
    REG_PIN_GR_BASE = REG_PIN_BASE,
    REG_PIN_EDI = REG_PIN_GR_BASE,
    REG_PIN_ESI,
    REG_PIN_EBP,
    REG_PIN_ESP,
    REG_PIN_EBX,
    REG_PIN_EDX,
    REG_PIN_ECX,
    REG_PIN_EAX,
    REG_PIN_AL,
    REG_PIN_AH,
    REG_PIN_AX,
    REG_PIN_CL,
    REG_PIN_CH,
    REG_PIN_CX,
    REG_PIN_DL,
    REG_PIN_DH,
    REG_PIN_DX,
    REG_PIN_BL,
    REG_PIN_BH,
    REG_PIN_BX,
    REG_PIN_BP,
    REG_PIN_SI,
    REG_PIN_DI,
    REG_PIN_SP,
    REG_PIN_RDI,
    REG_PIN_GDI = REG_PIN_RDI,
    REG_PIN_RSI,
    REG_PIN_GSI = REG_PIN_RSI,
    REG_PIN_RBP,
    REG_PIN_GBP = REG_PIN_RBP,
    REG_PIN_RSP,
    REG_PIN_STACK_PTR = REG_PIN_RSP,
    REG_PIN_RBX,
    REG_PIN_GBX = REG_PIN_RBX,
    REG_PIN_RDX,
    REG_PIN_GDX = REG_PIN_RDX,
    REG_PIN_RCX,
    REG_PIN_GCX = REG_PIN_RCX,
    REG_PIN_RAX,
    REG_PIN_GAX = REG_PIN_RAX,
    REG_PIN_R8,
    REG_PIN_R9,
    REG_PIN_R10,
    REG_PIN_R11,
    REG_PIN_R12,
    REG_PIN_R13,
    REG_PIN_R14,
    REG_PIN_R15,
    REG_PIN_DIL,
    REG_PIN_SIL,
    REG_PIN_BPL,
    REG_PIN_SPL,
    REG_PIN_R8B,
    REG_PIN_R8W,
    REG_PIN_R8D,
    REG_PIN_R9B,
    REG_PIN_R9W,
    REG_PIN_R9D,
    REG_PIN_R10B,
    REG_PIN_R10W,
    REG_PIN_R10D,
    REG_PIN_R11B,
    REG_PIN_R11W,
    REG_PIN_R11D,
    REG_PIN_R12B,
    REG_PIN_R12W,
    REG_PIN_R12D,
    REG_PIN_R13B,
    REG_PIN_R13W,
    REG_PIN_R13D,
    REG_PIN_R14B,
    REG_PIN_R14W,
    REG_PIN_R14D,
    REG_PIN_R15B,
    REG_PIN_R15W,
    REG_PIN_R15D,
    REG_THREAD_ID,
    REG_SEG_GS_VAL,
    REG_SEG_FS_VAL,
    REG_PIN_INDIRREG,
    REG_PIN_IPRELADDR,
    REG_PIN_SYSENTER_RESUMEADDR,
    REG_PIN_VMENTER,
    REG_PIN_T_BASE,
    REG_PIN_T0 = REG_PIN_T_BASE,
    REG_PIN_T1,
    REG_PIN_T2,
    REG_PIN_T3,
    REG_PIN_T0L,
    REG_PIN_T1L,
    REG_PIN_T2L,
    REG_PIN_T3L,
    REG_PIN_T0W,
    REG_PIN_T1W,
    REG_PIN_T2W,
    REG_PIN_T3W,
    REG_PIN_T0D,
    REG_PIN_T1D,
    REG_PIN_T2D,
    REG_PIN_T3D,
    REG_PIN_T_LAST = REG_PIN_T3D,
    REG_SEG_GS_BASE,
    REG_SEG_FS_BASE,
    REG_INST_BASE,
    REG_INST_SCRATCH_BASE = REG_INST_BASE,
    REG_INST_G0 = REG_INST_SCRATCH_BASE,
    REG_INST_G1,
    REG_INST_G2,
    REG_INST_G3,
    REG_INST_G4,
    REG_INST_G5,
    REG_INST_G6,
    REG_INST_G7,
    REG_INST_G8,
    REG_INST_G9,
    REG_INST_G10,
    REG_INST_G11,
    REG_INST_G12,
    REG_INST_G13,
    REG_INST_G14,
    REG_INST_G15,
    REG_INST_G16,
    REG_INST_G17,
    REG_INST_G18,
    REG_INST_G19,
    REG_INST_G20,
    REG_INST_G21,
    REG_INST_G22,
    REG_INST_G23,
    REG_INST_G24,
    REG_INST_G25,
    REG_INST_G26,
    REG_INST_G27,
    REG_INST_G28,
    REG_INST_G29,
    REG_INST_TOOL_FIRST = REG_INST_G0,
    REG_INST_TOOL_LAST = REG_INST_G29,
    REG_BUF_BASE0,
    REG_BUF_BASE1,
    REG_BUF_BASE2,
    REG_BUF_BASE3,
    REG_BUF_BASE4,
    REG_BUF_BASE5,
    REG_BUF_BASE6,
    REG_BUF_BASE7,
    REG_BUF_BASE8,
    REG_BUF_BASE9,
    REG_BUF_BASE_LAST = REG_BUF_BASE9,
    REG_BUF_END0,
    REG_BUF_END1,
    REG_BUF_END2,
    REG_BUF_END3,
    REG_BUF_END4,
    REG_BUF_END5,
    REG_BUF_END6,
    REG_BUF_END7,
    REG_BUF_END8,
    REG_BUF_END9,
    REG_BUF_ENDLAST = REG_BUF_END9,
    REG_BUF_LAST = REG_BUF_ENDLAST,
    REG_INST_SCRATCH_LAST = REG_BUF_ENDLAST,
    REG_INST_G0D,
    REG_INST_G1D,
    REG_INST_G2D,
    REG_INST_G3D,
    REG_INST_G4D,
    REG_INST_G5D,
    REG_INST_G6D,
    REG_INST_G7D,
    REG_INST_G8D,
    REG_INST_G9D,
    REG_INST_G10D,
    REG_INST_G11D,
    REG_INST_G12D,
    REG_INST_G13D,
    REG_INST_G14D,
    REG_INST_G15D,
    REG_INST_G16D,
    REG_INST_G17D,
    REG_INST_G18D,
    REG_INST_G19D,
    REG_INST_COND,
    REG_INST_LAST = REG_INST_COND,
    REG_INST_T0,
    REG_INST_T0L,
    REG_INST_T0W,
    REG_INST_T0D,
    REG_INST_T1,
    REG_INST_T1L,
    REG_INST_T1W,
    REG_INST_T1D,
    REG_INST_T2,
    REG_INST_T2L,
    REG_INST_T2W,
    REG_INST_T2D,
    REG_INST_T3,
    REG_INST_T3L,
    REG_INST_T3W,
    REG_INST_T3D,
    REG_INST_PRESERVED_PREDICATE,
    REG_FLAGS_BEFORE_AC_CLEARING,
    REG_PIN_BRIDGE_ORIG_SP,
    REG_PIN_BRIDGE_APP_IP,
    REG_PIN_BRIDGE_SP_BEFORE_ALIGN,
    REG_PIN_BRIDGE_SP_BEFORE_CALL,
    REG_PIN_BRIDGE_SP_BEFORE_MARSHALLING_FRAME,
    REG_PIN_BRIDGE_MARSHALLING_FRAME,
    REG_PIN_BRIDGE_ON_STACK_CONTEXT_FRAME,
    REG_PIN_BRIDGE_ON_STACK_CONTEXT_SP,
    REG_PIN_BRIDGE_MULTI_MEMORYACCESS_FRAME,
    REG_PIN_BRIDGE_MULTI_MEMORYACCESS_SP,
    REG_PIN_MULTI_MEM_ACCESS_AND_REWRITE_EMULATION_INFO_FRAME,
    REG_PIN_BRIDGE_TRANS_MEMORY_CALLBACK_FRAME,
    REG_PIN_BRIDGE_TRANS_MEMORY_CALLBACK_SP,
    REG_PIN_TRANS_MEMORY_CALLBACK_READ_ADDR,
    REG_PIN_TRANS_MEMORY_CALLBACK_READ2_ADDR,
    REG_PIN_TRANS_MEMORY_CALLBACK_WRITE_ADDR,
    REG_PIN_BRIDGE_SPILL_AREA_CONTEXT_FRAME,
    REG_PIN_BRIDGE_SPILL_AREA_CONTEXT_SP,
    REG_PIN_SPILLPTR,
    REG_PIN_GR_LAST = REG_PIN_SPILLPTR,
    REG_PIN_X87,
    REG_PIN_MXCSR,
    REG_PIN_STATUS_FLAGS,
    REG_PIN_DF_FLAG,
    REG_PIN_FLAGS,
    REG_PIN_XMM_BASE,
    REG_PIN_XMM0 = REG_PIN_XMM_BASE,
    REG_PIN_XMM1,
    REG_PIN_XMM2,
    REG_PIN_XMM3,
    REG_PIN_XMM4,
    REG_PIN_XMM5,
    REG_PIN_XMM6,
    REG_PIN_XMM7,
    REG_PIN_XMM8,
    REG_PIN_XMM9,
    REG_PIN_XMM10,
    REG_PIN_XMM11,
    REG_PIN_XMM12,
    REG_PIN_XMM13,
    REG_PIN_XMM14,
    REG_PIN_XMM15,
    REG_PIN_XMM_LAST = REG_PIN_XMM15,
    REG_PIN_YMM_BASE,
    REG_PIN_YMM0 = REG_PIN_YMM_BASE,
    REG_PIN_YMM1,
    REG_PIN_YMM2,
    REG_PIN_YMM3,
    REG_PIN_YMM4,
    REG_PIN_YMM5,
    REG_PIN_YMM6,
    REG_PIN_YMM7,
    REG_PIN_YMM8,
    REG_PIN_YMM9,
    REG_PIN_YMM10,
    REG_PIN_YMM11,
    REG_PIN_YMM12,
    REG_PIN_YMM13,
    REG_PIN_YMM14,
    REG_PIN_YMM15,
    REG_PIN_YMM_LAST = REG_PIN_YMM15,
    REG_PIN_ZMM_BASE,
    REG_PIN_ZMM_LAST = REG_PIN_ZMM_BASE,
    REG_PIN_K_BASE,
    REG_PIN_K_LAST = REG_PIN_K_BASE,
    REG_PIN_LAST = REG_PIN_K_LAST,
    REG_LAST
} REG;


typedef UTIL::FXSAVE_INTEL64_DEFAULT FXSAVE;


struct XSAVE_HEADER
{
    UINT64 _mask;
    UINT64 _reserved[7];
};


struct FPSTATE
{

    FXSAVE fxsave_legacy;

    struct XSTATE
    {
        XSAVE_HEADER _extendedHeader;
        UINT8 _ymmUpper[16*16];
    } _xstate;
};


class LOGFILE
{
  public:
    virtual VOID Open(const CHAR *name, BOOL append) = 0;
    virtual BOOL IsOpen() const = 0;
    virtual VOID Close() = 0;
    virtual VOID Write(const CHAR* message, size_t length) = 0;
    VOID Write(const string& message);
    virtual VOID WriteAtPosition( const CHAR* message, size_t length, size_t offset) = 0;
    virtual ~LOGFILE() {}
};


enum LOGTYPE
{
    LOGTYPE_CONSOLE,
    LOGTYPE_LOGFILE,
    LOGTYPE_CONSOLE_AND_LOGFILE
};

typedef BOOL (*MESSAGE_CALLBACK)(const string &message, PIN_ERRTYPE type, INT32 userType, INT32 severity, INT32 numArgs, va_list ap);



class MESSAGE_TYPE
{
  private:
    static VOID (*_panic_callback) ();
    static VOID (*_terminate_callback) ();
    static string _log_fname;
    static string _image_name;
    static MESSAGE_TYPE *_list;
    static LOGFILE *_logstream;
    static BOOL _logstreamAppend;
    static MESSAGE_CALLBACK _message_callback;

  private:
    const string _name;
    const string _prefix;
    const string _comment;
    BOOL _terminate;
    BOOL _trace;
    BOOL _enabled;
    BOOL _resource;
    LOGTYPE _log;

    BOOL _initted;

    MESSAGE_TYPE *_next;


  public:
    static VOID RegisterPanicCallBack( VOID (*cb) () );
    static VOID RegisterTerminateCallBack( VOID (*cb) () );
    static VOID RegisterLogFile(const string& name, BOOL append);
    static string GetLogFileName();
    static VOID RegisterImageName(const string& name );
    static MESSAGE_TYPE * Find(const string& name);
    static BOOL Disable(const string& name);
    static BOOL Enable(const string& name);
    static UINT32 Number();
    static string StringLongAll();
    static BOOL IsTerminating();
    static __attribute__ ((noreturn)) VOID PrintMessageAndExit(const char *message, const char *message2,
                                    PIN_ERRTYPE errType = PIN_ERR_NONE, INT32 numArgs = 0, ...);
    static VOID RegisterMessageCallBack(MESSAGE_CALLBACK fun);
    static VOID UnregisterMessageCallBack();
    static MESSAGE_CALLBACK MessageCallBack();
    static BOOL ErrorFileSpecified();

  private:
    static VOID DumpTrace();

  public:
    MESSAGE_TYPE( string name, string prefix, BOOL terminate, BOOL trace, BOOL enabled, BOOL resource,
                  LOGTYPE log, string comment);

    VOID Message(const string& message, BOOL printPrefix = 1,
                 PIN_ERRTYPE errType = PIN_ERR_NONE, INT32 numArgs=0, ...);

    VOID __attribute__ ((noreturn)) MessageNoReturn(const string& message, BOOL printPrefix = 1,
                 PIN_ERRTYPE errType = PIN_ERR_NONE, INT32 numArgs=0, ...);

    BOOL inline on() const {return _enabled;}
    VOID disable() {_enabled=false;}
    VOID enable() {_enabled=true;}

    int Compare(const MESSAGE_TYPE & k2) const;

  private:
    VOID MessageInternal(const string& message, BOOL printPrefix, PIN_ERRTYPE errType, va_list va, INT32 numArgs);
};

extern MESSAGE_TYPE MessageTypeError;

typedef enum
{
    KNOB_MODE_INVALID,
    KNOB_MODE_COMMENT,
    KNOB_MODE_WRITEONCE,
    KNOB_MODE_OVERWRITE,
    KNOB_MODE_ACCUMULATE,
    KNOB_MODE_APPEND,
    KNOB_MODE_LAST
} KNOB_MODE;

template<class TYPE> class KNOBVALUE
{
  private:
    TYPE _value;
    string _value_string;
    KNOBVALUE<TYPE> * _next;


    KNOBVALUE(const KNOBVALUE &) { do{ if(MessageTypeError.on()) MessageTypeError.MessageNoReturn("KNOBVALUE should not be copied",1,PIN_ERR_INTERNAL,0); }while(0); }

    KNOBVALUE& operator=(const KNOBVALUE &) { do{ if(MessageTypeError.on()) MessageTypeError.MessageNoReturn("KNOBVALUE should not be copied",1,PIN_ERR_INTERNAL,0); }while(0); };

  public:

    static TYPE FromString(const string & strvalue) {
        if( !strvalue.empty( ))
        {
            TYPE ret;
            std::istringstream iss( strvalue );
            if( strvalue.find( "0x" ) != std::string::npos )
            {
                iss >> std::hex >> ret;
            }
            else if (strvalue.find("true") or strvalue.find("false"))
            {
                iss >> std::boolalpha >> ret;
            } 
            else
            {
                iss >> std::dec >> ret;
            }

            if( iss.fail( ))
            {
            std::cout << "Convert error: cannot convert string '" << strvalue << "' to value" << std::endl;
            return TYPE( );
            }
            return ret;
        }
    return TYPE( );
    }
    static string ToString(const TYPE & value, const string & origString)
    {
        return origString;
    }


    static TYPE Accumulate(TYPE & lVal, const TYPE & rVal)
    {
        return (lVal += rVal);
    }

    static const string Type() {return "Not yet implemented";}

    KNOBVALUE() : _next(__null) {}

    const TYPE & Value() const { return _value; }
    const string & ValueString() const { return _value_string; }

    KNOBVALUE * Next() const { return _next; }

    VOID Overwrite(const string & valstring)
    {
        _value = FromString(valstring);
        _value_string = ToString(_value, valstring);
    }
    VOID Accumulate(const string & valstring)
    {
        Accumulate(_value, FromString(valstring));
        _value_string = ToString(_value, valstring);
    }
    VOID Append(KNOBVALUE * next)
    {
        _next = next;
    }
};

template<class TYPE> class KNOBVALUE_LIST
{
  private:
    typedef KNOBVALUE<TYPE> listnode;
    listnode _first;
    UINT32 _numNodes;

  public:



    KNOBVALUE_LIST(const string & valstring, BOOL hasDefault) : _numNodes(0)
    {
        if (hasDefault)
        {
            Append(valstring);
        }
    }
    ~KNOBVALUE_LIST()
    {
        listnode * next;
        for (listnode * node = _first.Next(); node; node = next)
        {
            next = node->Next();
            delete node;
        }
    }




  private:

    KNOBVALUE_LIST(const KNOBVALUE_LIST &) { do{ if(MessageTypeError.on()) MessageTypeError.MessageNoReturn("KNOBVALUE_LIST should not be copied",1,PIN_ERR_INTERNAL,0); }while(0); }

    KNOBVALUE_LIST& operator=(const KNOBVALUE_LIST&) { do{ if(MessageTypeError.on()) MessageTypeError.MessageNoReturn("KNOBVALUE_LIST should not be copied",1,PIN_ERR_INTERNAL,0); }while(0); }



    const listnode * Node(const UINT32 index) const { return GetNode(index); }
    listnode * Node(const UINT32 index) { return const_cast<listnode *>(GetNode(index)); }
    const listnode * GetNode(const UINT32 index) const
    {

        const listnode * node = & _first;
        for (UINT32 i = index; i > 0; i--)
        {
            node = node->Next();
        }

        return node;
    }

  public:
    UINT32 NumberOfValues() const { return _numNodes; }
    const string & ValueString(const UINT32 index) const { return Node(index)->ValueString(); }
    const TYPE & Value(const UINT32 index) const { return Node(index)->Value(); }
    const TYPE & Value() const { return _first.Value(); }
    const string & ValueString() const { return _first.ValueString(); }




    VOID Overwrite(const string & valstring) { _first.Overwrite(valstring); }
    VOID Accumulate(const string & valstring) { _first.Accumulate(valstring); }
    VOID Append(const string & valstring)
    {
        listnode * node;
        if (_numNodes == 0)
        {
            node = & _first;
        }
        else
        {
            node = new listnode;
            listnode * const last = Node(_numNodes - 1);
            last->Append(node);
        }
        node->Overwrite(valstring);
        _numNodes++;
    }
};

class KNOB_BASE
{
  private:
    static KNOB_BASE *_knob_list;

  protected:
    KNOB_BASE *_next;
    const string _family;
    const string _name;
    const string _purpose;
    const string _default_value;
    const KNOB_MODE _mode;
    BOOL _disabled;
    INT32 _nreads;
    INT32 _nwrites;

    const string _prefix;

  public:



    static std::map<std::string, std::string> dr_knob_cmd_map;

    KNOB_BASE(const string & myprefix, const string & myname, const string & myfamily, 
              const string & mydefault, const string & mypurpose, 
              KNOB_MODE mymode = KNOB_MODE_WRITEONCE) :  _next(nullptr), _family(myfamily), _name(myname), _purpose(mypurpose), _default_value(mydefault),  _mode(mymode), _disabled(false), _nreads(0), _nwrites(0), _prefix(myprefix){

    if(_knob_list == nullptr){
        _knob_list = this;
    }
    else {
        // insert itself as the last knob in the linked list
        KNOB_BASE *p = _knob_list;
        while (p->_next != nullptr){
            p = p->_next;
        }
        p->_next = this;
    }
  }

    virtual ~KNOB_BASE() {}

    virtual const string Type() = 0;
    KNOB_MODE Mode() const {return _mode;}
    const string & Family() const {return _family;}
    const string & Name() const {return _name;}
    string Cmd() const { return ("-" + _name); }
    BOOL Enabled() const {return !_disabled;}
    static VOID CheckAllKnobs(BOOL allowDashes = 0);
    static UINT32 NumberOfKnobs();
    static VOID DisableKnobFamily(const string & myfamily);
    static VOID EnableKnobFamily(const string & myfamily);
    static VOID DisableKnob(const string & myname);
    static VOID EnableKnob(const string & myname);

    static string StringKnobSummary(){
        string retVal = "\nPin tools switches\n\n" ;
        KNOB_BASE *p = _knob_list;
        while(p != nullptr) {
            retVal += "-" + p->_name; 
            retVal += "  [Default " + p->_default_value + "]\n";
            retVal += "\t" + p->_purpose + "\n";
            p = p->_next;
        }
        return retVal;
    }

    static string StringLongAll();

    static KNOB_BASE * FindKnob(const string & name){
        KNOB_BASE *p = _knob_list;
        while(p != nullptr) {
            if(p->_name == name) {
                return p;
            }
            p = p->_next;
        }
        return nullptr;
    }

    static KNOB_BASE * FindFamily(const string & name);
    static KNOB_BASE * FindEnabledKnob(const string & name);
    int Compare(const KNOB_BASE & k2) const;
    virtual const string & ValueString(const UINT32 index) const = 0;
    virtual UINT32 NumberOfValues() const = 0;
    virtual VOID AddValue(const string & valstring) = 0;
};


template<class TYPE> class KNOB : public KNOB_BASE
{
  private:
    typedef KNOBVALUE_LIST<TYPE> valuelist;
    valuelist _value_list;


    KNOB() { do{ if(MessageTypeError.on()) MessageTypeError.MessageNoReturn("KNOB should not be constructed using default constructor",1,PIN_ERR_INTERNAL,0); }while(0); }

    KNOB(const KNOB&) { do{ if(MessageTypeError.on()) MessageTypeError.MessageNoReturn("KNOB should not be copied",1,PIN_ERR_INTERNAL,0); }while(0); }

    KNOB& operator=(const KNOB&) { do{ if(MessageTypeError.on()) MessageTypeError.MessageNoReturn("KNOB should not be copied",1,PIN_ERR_INTERNAL,0); }while(0); }

  public:
    
    KNOB(KNOB_MODE mymode, const string & myfamily, const string & myname,
         const string & mydefault, const string & mypurpose, const string & myprefix = "")
    :
        KNOB_BASE(myprefix, myname, myfamily, mydefault, mypurpose, mymode),
        _value_list((KNOB_BASE::dr_knob_cmd_map.find(myname) != KNOB_BASE::dr_knob_cmd_map.end()) ? KNOB_BASE::dr_knob_cmd_map[myname] : mydefault, (mymode != KNOB_MODE_APPEND))
    {
    }

    VOID AddValue(const string & valstring)
    {
        switch (_mode)
        {
          case KNOB_MODE_WRITEONCE:

            _value_list.Overwrite(valstring);
          case KNOB_MODE_OVERWRITE:

            _value_list.Overwrite(valstring);
            break;

          case KNOB_MODE_ACCUMULATE:
            std::cout << __func__ << std::endl;
            std::cout << __PRETTY_FUNCTION__ << std::endl;
            std::cout << "Function not implemented" << std::endl << std::flush;
            exit(1);

            _value_list.Accumulate(valstring);
            break;

          case KNOB_MODE_APPEND:
            std::cout << __func__ << std::endl;
            std::cout << __PRETTY_FUNCTION__ << std::endl;
            std::cout << "Function not implemented" << std::endl << std::flush;
            exit(1);

            _value_list.Append(valstring);
            break;

          default:
            std::cout << __func__ << std::endl;
            std::cout << __PRETTY_FUNCTION__ << std::endl;
            std::cout << "Function not implemented" << std::endl << std::flush;
            exit(1);

            printf("default case not implemented");
            exit(1);
        }

        _nwrites++;
    }





    const string Type() { return KNOBVALUE<TYPE>::Type(); }

    const TYPE & Value() const { return _value_list.Value(); }
    const string & ValueString() const { return _value_list.ValueString(); }

    operator TYPE() const { return Value(); }

    const TYPE & Value(const UINT32 index) { _nreads++; return _value_list.Value(index); }
    const string & ValueString(const UINT32 index) const { return _value_list.ValueString(index); }
    UINT32 NumberOfValues() const { return _value_list.NumberOfValues(); }
};


class COMMAND_LINE_ARGUMENTS
{
  public:
    COMMAND_LINE_ARGUMENTS()
    {
        Enter(0, __null, __null);
    }
    COMMAND_LINE_ARGUMENTS(INT argc, const CHAR * const * argv, const CHAR * delimiter = __null)
    {
        Enter(argc, argv, delimiter);
    }
    COMMAND_LINE_ARGUMENTS(const string & commandLine)
    {
        Enter(commandLine);
    }

    COMMAND_LINE_ARGUMENTS(const COMMAND_LINE_ARGUMENTS & source)
    {
        Enter(source.m_argc, source.m_argv, __null);
    }
    COMMAND_LINE_ARGUMENTS & operator= (const COMMAND_LINE_ARGUMENTS & source)
    {
        if(this != &source)
        {
            Clean();
            Enter(source.m_argc, source.m_argv, __null);
        }
        return *this;
    }
    COMMAND_LINE_ARGUMENTS & Insert (const COMMAND_LINE_ARGUMENTS & right, INT pos = -1);
    COMMAND_LINE_ARGUMENTS & Insert (const string & arg, INT pos = -1);
    INT FindArgument(const string& argStr) const;
    BOOL RemoveArguments(const string& argStr, INT numOfArgs);


    INT Argc() const
    {
        return m_argc;
    }

    const CHAR * const * Argv() const
    {
        return m_argv;
    }

    string String() const;

    ~COMMAND_LINE_ARGUMENTS()
    {
        Clean();
    }

  private:



    BOOL Enter(INT argc, const CHAR * const * argv, const CHAR * delimiter);




    BOOL Enter(const string & commandLine);




    BOOL Clean();




    INT FindArraySize(INT argc, const CHAR * const * argv, const CHAR * delimiter);




    VOID RemoveArgument(INT index);

  private:
    INT m_argc;
    CHAR ** m_argv;
};


class CHILD_PROCESS_CLASS
{
  public:
    CHILD_PROCESS_CLASS(UINT32 processId, const COMMAND_LINE_ARGUMENTS & appCmd, const COMMAND_LINE_ARGUMENTS & pinCmd) : m_processId(processId), m_appCmd(appCmd), m_pinCmd(pinCmd), m_isPinCmdModified(0)
    {
        (m_pinAndAppCmd = m_pinCmd).Insert(m_appCmd);
    }

    UINT32 GetId()
    {
        return m_processId;
    }
    BOOL GetApplicationCommandLine(INT * pArgc, const CHAR * const ** pArgv);
    BOOL SetPinCommandLine(INT argc, const CHAR * const * argv);
    BOOL GetPinCommandLine(INT * pArgc, const CHAR * const ** pArgv);
    BOOL GetFullCommandLine(INT * pArgc, const CHAR * const ** pArgv);
    BOOL IsPinCommandLineModified();

    ~CHILD_PROCESS_CLASS() {}

  private:
    UINT32 m_processId;
    COMMAND_LINE_ARGUMENTS m_appCmd;
    COMMAND_LINE_ARGUMENTS m_pinCmd;
    COMMAND_LINE_ARGUMENTS m_pinAndAppCmd;
    BOOL m_isPinCmdModified;
};


enum EXCEPTION_CLASS
{
    EXCEPTCLASS_NONE,
    EXCEPTCLASS_UNKNOWN,
    EXCEPTCLASS_ACCESS_FAULT,
    EXCEPTCLASS_INVALID_INS,
    EXCEPTCLASS_INT_ERROR,
    EXCEPTCLASS_FP_ERROR,
    EXCEPTCLASS_MULTIPLE_FP_ERROR,
    EXCEPTCLASS_DEBUG,
    EXCEPTCLASS_OS
};

enum EXCEPTION_CODE
{
    EXCEPTCODE_NONE,
    EXCEPTCODE_ACCESS_INVALID_ADDRESS,
    EXCEPTCODE_ACCESS_DENIED,
    EXCEPTCODE_ACCESS_INVALID_PAGE,
    EXCEPTCODE_ACCESS_MISALIGNED,
    EXCEPTCODE_ILLEGAL_INS,
    EXCEPTCODE_PRIVILEGED_INS,
    EXCEPTCODE_INT_DIVIDE_BY_ZERO,
    EXCEPTCODE_INT_OVERFLOW_TRAP,
    EXCEPTCODE_INT_BOUNDS_EXCEEDED,
    EXCEPTCODE_X87_DIVIDE_BY_ZERO,
    EXCEPTCODE_X87_OVERFLOW,
    EXCEPTCODE_X87_UNDERFLOW,
    EXCEPTCODE_X87_INEXACT_RESULT,
    EXCEPTCODE_X87_INVALID_OPERATION,
    EXCEPTCODE_X87_DENORMAL_OPERAND,
    EXCEPTCODE_X87_STACK_ERROR,
    EXCEPTCODE_SIMD_DIVIDE_BY_ZERO,
    EXCEPTCODE_SIMD_OVERFLOW,
    EXCEPTCODE_SIMD_UNDERFLOW,
    EXCEPTCODE_SIMD_INEXACT_RESULT,
    EXCEPTCODE_SIMD_INVALID_OPERATION,
    EXCEPTCODE_SIMD_DENORMAL_OPERAND,
    EXCEPTCODE_DBG_BREAKPOINT_TRAP,
    EXCEPTCODE_DBG_SINGLE_STEP_TRAP,
    EXCEPTCODE_ACCESS_WINDOWS_GUARD_PAGE,
    EXCEPTCODE_ACCESS_WINDOWS_STACK_OVERFLOW,
    EXCEPTCODE_WINDOWS,
    EXCEPTCODE_RECEIVED_UNKNOWN,
    EXCEPTCODE_RECEIVED_ACCESS_FAULT,
    EXCEPTCODE_RECEIVED_AMBIGUOUS_X87,
    EXCEPTCODE_RECEIVED_AMBIGUOUS_SIMD
};

enum FAULTY_ACCESS_TYPE
{
    FAULTY_ACCESS_TYPE_UNKNOWN,
    FAULTY_ACCESS_READ,
    FAULTY_ACCESS_WRITE,
    FAULTY_ACCESS_EXECUTE
};

template <typename T> struct OPTIONAL_VALUE
{
    BOOL m_hasValue;
    T m_value;
    VOID Set(const T & value)
    {
        m_hasValue = 1;
        m_value = value;
    }

    VOID Set(const T * pValue)
    {
        if (pValue != 0)
        {
            Set(*pValue);
        }
        else
        {
            Reset();
        }
    }

    VOID Reset() {m_hasValue = 0;}

    BOOL Get(T * pValue) const
    {
        if (m_hasValue && (pValue != 0)) {*pValue = m_value;}
        return m_hasValue;
    }

    BOOL HasValue() const {return m_hasValue;}

    T & Value() {return m_value;}
    const T & Value() const {return m_value;}

    T * ValuePtr() {return ((m_hasValue) ? &m_value : 0);}
    const T * ValuePtr() const {return ((m_hasValue) ? &m_value : 0);}
};

const UINT32 MAX_WINDOWS_EXCEPTION_ARGS = 5;

struct EXCEPTION_INFO
{
    EXCEPTION_INFO & Init(EXCEPTION_CODE exceptCode, ADDRINT exceptAddress);
    EXCEPTION_CODE GetExceptCode() const {return m_exceptCode;}

    static EXCEPTION_CLASS GetExceptClass(EXCEPTION_CODE exceptCode);
    EXCEPTION_CLASS GetExceptClass() const {return GetExceptClass(m_exceptCode);}

    ADDRINT GetExceptAddress() const {return m_exceptAddress;}

    VOID SetExceptAddress(ADDRINT exceptAddress) {m_exceptAddress = exceptAddress;}

    static BOOL IsTrap(EXCEPTION_CODE exceptCode);
    BOOL IsTrap() const {return IsTrap(m_exceptCode);}

    VOID Reset() {m_exceptCode = EXCEPTCODE_NONE;}

    BOOL IsEmpty() const {return (m_exceptCode == EXCEPTCODE_NONE);}

    string ToString() const{
        return "Not yet Implemented EXCEPTION_INFO::ToString";
    }

    string GetCodeAsString() const;

  public:
    EXCEPTION_INFO & InitAccessFault(EXCEPTION_CODE exceptCode,
                                     ADDRINT exceptAddress,
                                     ADDRINT accessAddress,
                                     FAULTY_ACCESS_TYPE accessType = FAULTY_ACCESS_TYPE_UNKNOWN);


    BOOL IsAccessFault() const {return GetExceptClass() == EXCEPTCLASS_ACCESS_FAULT;}


    FAULTY_ACCESS_TYPE GetFaultyAccessType() const
    {
        return m_specific.m_access.m_type;
    }
    BOOL GetFaultyAccessAddress(ADDRINT * pAccessAddress) const
    {
        return m_specific.m_access.m_address.Get(pAccessAddress);
    }

  public:
    EXCEPTION_INFO & InitMultipleFpError(EXCEPTION_CODE exceptCode,
                                         ADDRINT exceptAddress,
                                         UINT32 fpErrors);



    BOOL IsMultipleFpException() const {return GetExceptClass() == EXCEPTCLASS_MULTIPLE_FP_ERROR;}

    UINT32 GetFpErrors() const
    {
        return m_specific.m_multipleFp.m_fpErrors;
    }

  public:
    EXCEPTION_INFO & InitWindowsSysException(UINT32 sysExceptCode,
                                          ADDRINT exceptAddress,
                                          UINT32 numArgs = 0,
                                          const ADDRINT * pArgs = 0);

    BOOL IsWindowsSysException() const {return m_exceptCode == EXCEPTCODE_WINDOWS;}


    UINT32 GetWindowsSysExceptionCode() const
    {
        return m_specific.m_winsys.m_exceptCode;
    }


    UINT32 CountWindowsSysArguments() const
    {
        return m_specific.m_winsys.m_numArgs;
    }
    ADDRINT GetWindowsSysArgument(UINT32 argNum) const
    {
        return m_specific.m_winsys.m_args[argNum];
    }

  public:


    EXCEPTION_CODE m_exceptCode;
    ADDRINT m_exceptAddress;


    union EXCEPTION_SPECIFIC
    {
        struct ACCESS_FAULT
        {
            FAULTY_ACCESS_TYPE m_type;
            OPTIONAL_VALUE<ADDRINT> m_address;
        }m_access;

        struct WINDOWS_SYS
        {
            UINT32 m_exceptCode;
            UINT32 m_numArgs;
            ADDRINT m_args[MAX_WINDOWS_EXCEPTION_ARGS];
        }m_winsys;

        struct MULTIPLE_FP
        {
            UINT32 m_fpErrors;
        }m_multipleFp;
    }m_specific;
};


typedef struct EXCEPTION_INFO EXCEPTION_INFO;


const size_t FPSTATE_SIZE = sizeof(FPSTATE);

const size_t FPSTATE_ALIGNMENT = 64;

const ADDRINT AC_FLAG_BIT = 0x40000;

const ADDRINT NUM_PHYSICAL_REGS = REG_PHYSICAL_CONTEXT_END - REG_PHYSICAL_CONTEXT_BEGIN + 1;


const ADDRINT NUM_SCRATCH_REGS = REG_INST_SCRATCH_LAST - REG_INST_SCRATCH_BASE + 1;


const ADDRINT NUM_SPECIAL_REGS = 2 + NUM_SCRATCH_REGS;


const ADDRINT NUM_CONTEXT_INT_REGS = NUM_PHYSICAL_REGS + NUM_SPECIAL_REGS;


const ADDRINT ARCH_STATE_SIZE = (NUM_PHYSICAL_REGS + NUM_SPECIAL_REGS)*sizeof(ADDRINT) + (FPSTATE_SIZE + FPSTATE_ALIGNMENT);




typedef UINT16 OPCODE;

typedef unsigned int USIZE;

extern REG REG_FullRegName(const REG reg);

extern string REG_StringShort(REG reg);


inline EXCEPTION_CODE PIN_GetExceptionCode(const EXCEPTION_INFO * pExceptInfo)
{
    return pExceptInfo->GetExceptCode();
}


inline ADDRINT PIN_GetExceptionAddress(const EXCEPTION_INFO * pExceptInfo)
{
    return pExceptInfo->GetExceptAddress();
}


inline string PIN_ExceptionToString(const EXCEPTION_INFO * pExceptInfo)
{
    return pExceptInfo->ToString();
}


inline BOOL PIN_GetFaultyAccessAddress(const EXCEPTION_INFO * pExceptInfo,
                                             ADDRINT * pAccessAddress)
{
    return pExceptInfo->GetFaultyAccessAddress(pAccessAddress);
}

inline FAULTY_ACCESS_TYPE PIN_GetFaultyAccessType(const EXCEPTION_INFO * pExceptInfo)
{
    return pExceptInfo->GetFaultyAccessType();
}

}

namespace LEVEL_CORE {

using namespace LEVEL_BASE;
template <int dummy> class INDEX {

public:
    INT32 index;
    BOOL
    operator==(const INDEX<dummy> right) const
    {
        return right.index == index;
    }
    BOOL
    operator!=(const INDEX<dummy> right) const
    {
        return right.index != index;
    }
    BOOL
    operator<(const INDEX<dummy> right) const
    {
        return index < right.index;
    }

    INT32
    q() const
    {
        return index;
    }
    BOOL
    is_valid() const
    {
        return (index > 0);
    }
    VOID
    q_set(INT32 y)
    {
        index = y;
    }
    VOID
    invalidate()
    {
        index = 0;
    }
};

struct BBL {
    void * drcontext;
    void * instr_list;
    void * instr;
};

struct INS {
    void * drcontext;
    void * instr_list;
    void * instr;
};

struct IMG {
    // int drpin_placeholder;
    bool valid;
    string img_uniq_identifier;
    string name;
    bool main_module;
    void * drcontext;
    void * module_data;
    void * lowest_address;
    void * highest_address;
};

struct SEC {
    bool valid;
    string belonging_img;
    string sec_uniq_identifier;
};

struct RTN {
    bool valid;
    string belonging_sec;
    string belonging_img;
    string rtn_uniq_identifier;
    size_t modoffs; 
    string name;
    // int drpin_placeholder;

    inline bool operator==(RTN a) {
       if (a.rtn_uniq_identifier==rtn_uniq_identifier)
          return true;
       else
          return false;
    }
};

typedef enum
{
    IMG_TYPE_INVALID,
    IMG_TYPE_STATIC,
    IMG_TYPE_SHARED,
    IMG_TYPE_SHAREDLIB,
    IMG_TYPE_RELOCATABLE,
    IMG_TYPE_DYNAMIC_CODE,
    IMG_TYPE_API_CREATED,
    IMG_TYPE_LAST
}IMG_TYPE;

typedef enum
{
    SYSCALL_STANDARD_INVALID,
    SYSCALL_STANDARD_IA32_LINUX,
    SYSCALL_STANDARD_IA32E_LINUX,
    SYSCALL_STANDARD_IA32_MAC,
    SYSCALL_STANDARD_IA32E_MAC,
    SYSCALL_STANDARD_IA32_WINDOWS_FAST,
    SYSCALL_STANDARD_IA32E_WINDOWS_FAST,
    SYSCALL_STANDARD_IA32_WINDOWS_ALT,
    SYSCALL_STANDARD_WOW64,
    SYSCALL_STANDARD_WINDOWS_INT
} SYSCALL_STANDARD;

// functions declarations

extern std::string INS_Disassemble(INS ins);

extern UINT32 INS_OperandCount(INS ins);

extern BOOL INS_OperandRead(INS ins, UINT32 n);

extern BOOL INS_OperandWritten(INS ins, UINT32 n);

extern BOOL INS_OperandIsMemory(INS ins, UINT32 n);

extern BOOL INS_OperandIsReg(INS ins, UINT32 n);

extern REG INS_OperandReg(INS ins, UINT32 n);

extern REG INS_OperandMemoryBaseReg(INS ins, UINT32 n);

extern REG INS_OperandMemoryIndexReg(INS ins, UINT32 n);

extern BOOL INS_LockPrefix(INS ins);

extern UINT32 INS_OperandWidth(INS ins, UINT32 n);

extern INT32 INS_Category(const INS ins);

extern OPCODE INS_Opcode(INS ins);

extern BOOL INS_IsAtomicUpdate(const INS ins);

extern BOOL INS_OperandIsImmediate(INS ins, UINT32 n);

extern BOOL INS_IsDirectBranch(INS ins);

extern BOOL INS_IsDirectBranchOrCall(INS ins);

extern UINT32 BBL_NumIns(BBL bbl);

}

namespace LEVEL_VM {
using namespace LEVEL_CORE;


#define PIN_FAST_ANALYSIS_CALL

typedef UINT32 THREADID;

typedef enum
{
    IARG_INVALID,
    IARG_ADDRINT,
    IARG_PTR,
    IARG_BOOL,
    IARG_UINT32,
    IARG_INST_PTR,
    IARG_REG_VALUE,
    IARG_REG_REFERENCE,
    IARG_REG_CONST_REFERENCE,
    IARG_MEMORYREAD_EA,
    IARG_MEMORYREAD2_EA,
    IARG_MEMORYWRITE_EA,
    IARG_MEMORYREAD_SIZE,
    IARG_MEMORYWRITE_SIZE,
    IARG_MEMORYREAD_PTR,
    IARG_MEMORYREAD2_PTR,
    IARG_MEMORYWRITE_PTR,
    IARG_MEMORYOP_PTR,
    IARG_MULTI_MEMORYACCESS_EA,
    IARG_EXPLICIT_MEMORY_EA,
    IARG_BRANCH_TAKEN,
    IARG_BRANCH_TARGET_ADDR,
    IARG_FALLTHROUGH_ADDR,
    IARG_EXECUTING,
    IARG_FIRST_REP_ITERATION,
    IARG_PREDICATE,
    IARG_STACK_VALUE,
    IARG_STACK_REFERENCE,
    IARG_MEMORY_VALUE,
    IARG_MEMORY_REFERENCE,
    IARG_SYSCALL_NUMBER,
    IARG_SYSARG_REFERENCE,
    IARG_SYSARG_VALUE,
    IARG_SYSRET_VALUE,
    IARG_SYSRET_ERRNO,
    IARG_FUNCARG_CALLSITE_REFERENCE,
    IARG_FUNCARG_CALLSITE_VALUE,
    IARG_FUNCARG_ENTRYPOINT_REFERENCE,
    IARG_FUNCARG_ENTRYPOINT_VALUE,
    IARG_FUNCRET_EXITPOINT_REFERENCE,
    IARG_FUNCRET_EXITPOINT_VALUE,
    IARG_RETURN_IP,
    IARG_ORIG_FUNCPTR,
    IARG_PROTOTYPE,
    IARG_THREAD_ID,
    IARG_CONTEXT,
    IARG_CONST_CONTEXT,
    IARG_PARTIAL_CONTEXT,
    IARG_PRESERVE,
    IARG_RETURN_REGS,
    IARG_CALL_ORDER,
    IARG_REG_NAT_VALUE,
    IARG_REG_OUTPUT_FRAME_VALUE,
    IARG_REG_OUTPUT_FRAME_REFERENCE,
    IARG_IARGLIST,
    IARG_FAST_ANALYSIS_CALL,
    IARG_SYSCALL_ARG0,
    IARG_SYSCALL_ARGBASE = IARG_SYSCALL_ARG0,
    IARG_SYSCALL_ARG1,
    IARG_SYSCALL_ARG2,
    IARG_SYSCALL_ARG3,
    IARG_SYSCALL_ARG4,
    IARG_SYSCALL_ARG5,
    IARG_SYSCALL_ARGLAST = IARG_SYSCALL_ARG5,
    IARG_G_RESULT0,
    IARG_G_RETBASE = IARG_G_RESULT0,
    IARG_G_RESULTLAST = IARG_G_RESULT0,
    IARG_G_ARG0_CALLEE,
    IARG_G_ARGBASE_CALLEE = IARG_G_ARG0_CALLEE,
    IARG_G_ARG1_CALLEE,
    IARG_G_ARG2_CALLEE,
    IARG_G_ARG3_CALLEE,
    IARG_G_ARG4_CALLEE,
    IARG_G_ARG5_CALLEE,
    IARG_G_ARGLAST_CALLEE = IARG_G_ARG5_CALLEE,
    IARG_G_ARG0_CALLER,
    IARG_G_ARGBASE_CALLER = IARG_G_ARG0_CALLER,
    IARG_G_ARG1_CALLER,
    IARG_G_ARG2_CALLER,
    IARG_G_ARG3_CALLER,
    IARG_G_ARG4_CALLER,
    IARG_G_ARG5_CALLER,
    IARG_G_ARGLAST_CALLER = IARG_G_ARG5_CALLER,
    IARG_MEMORYOP_EA,
    IARG_MEMORYOP_MASKED_ON,
    IARG_TSC,
    IARG_FILE_NAME,
    IARG_LINE_NO,
    IARG_LAST
} IARG_TYPE;

 typedef enum
{
    PROBE_INVALID,
    PROBE_REDIRECT,

    PROBE_REDIRECT_TO_ORIGINAL,

    PROBE_SINGLE_THREAD,
    PROBE_MULTI_THREAD,
    PROBE_FUNCTION_WRAPPER,
    PROBE_NO_WRAPPER,
    PROBE_RELOCATE
} PROBE_TYPE;

typedef enum {
    IPOINT_INVALID,
    IPOINT_BEFORE,
    IPOINT_AFTER,
    IPOINT_ANYWHERE,
    IPOINT_TAKEN_BRANCH

} IPOINT;


 typedef VOID ROOT_THREAD_FUNC(VOID * arg);

 typedef UINT64 PIN_THREAD_UID;

 const ADDRINT DEFAULT_CONTEXT_IMPL = 0;
 

 struct CONTEXT
 {
    CONTEXT() : _impl(DEFAULT_CONTEXT_IMPL) {}

    ADDRINT _impl;
    CHAR _state[ARCH_STATE_SIZE];
    void * drcontext;
    int syscallnumber;
 };

 typedef struct CONTEXT CONTEXT;

 enum CONTEXT_CHANGE_REASON
{
    CONTEXT_CHANGE_REASON_FATALSIGNAL,
    CONTEXT_CHANGE_REASON_SIGNAL,
    CONTEXT_CHANGE_REASON_SIGRETURN,
    CONTEXT_CHANGE_REASON_APC,
    CONTEXT_CHANGE_REASON_EXCEPTION,
    CONTEXT_CHANGE_REASON_CALLBACK
};

enum EXCEPT_HANDLING_RESULT
{
    EHR_HANDLED,
    EHR_UNHANDLED,
    EHR_CONTINUE_SEARCH
};

 struct PHYSICAL_CONTEXT
{
    PHYSICAL_CONTEXT(CONTEXT * pCtxt) : _pCtxt(pCtxt) {}

    CONTEXT * _pCtxt;
};


 typedef struct PHYSICAL_CONTEXT PHYSICAL_CONTEXT;
}

namespace LEVEL_PINCLIENT {

using namespace LEVEL_VM;


class COMPLEX_CALLBACKVAL_BASE;

typedef COMPLEX_CALLBACKVAL_BASE * PIN_CALLBACK;

typedef VOID (*INS_INSTRUMENT_CALLBACK)(INS ins, VOID *v);

typedef VOID (*FINI_CALLBACK)(INT32 code, VOID *v);



struct TRACE {
    BBL only_bbl;
};

typedef LEVEL_BASE::CHILD_PROCESS_CLASS * CHILD_PROCESS;

typedef VOID (*TRACE_INSTRUMENT_CALLBACK)(TRACE trace, VOID *v);

typedef VOID (*THREAD_START_CALLBACK)(THREADID threadIndex, CONTEXT *ctxt, INT32 flags, VOID *v);

typedef VOID (*THREAD_FINI_CALLBACK)(THREADID threadIndex, const CONTEXT *ctxt, INT32 code, VOID *v);


typedef VOID (*SYSCALL_ENTRY_CALLBACK)(THREADID threadIndex, CONTEXT *ctxt,
                                                  SYSCALL_STANDARD std, VOID *v);


typedef VOID (*SYSCALL_EXIT_CALLBACK)(THREADID threadIndex, CONTEXT *ctxt,
                                                 SYSCALL_STANDARD std, VOID *v);


typedef VOID (*CONTEXT_CHANGE_CALLBACK)(THREADID threadIndex, CONTEXT_CHANGE_REASON reason,
                                                   const CONTEXT *from, CONTEXT *to, INT32 info, VOID *v);

typedef VOID (*FORK_CALLBACK)(THREADID threadid, const CONTEXT *ctxt, VOID *v);

typedef VOID (*IMAGECALLBACK)(IMG, VOID *);

// functions declarations

extern PIN_CALLBACK INS_AddInstrumentFunction(INS_INSTRUMENT_CALLBACK fun, VOID *val);

extern VOID INS_InsertCall(INS ins, IPOINT action, AFUNPTR funptr, ...);

extern BOOL PIN_Init(INT32 argc, CHAR ** argv);

extern PIN_CALLBACK PIN_AddFiniFunction(FINI_CALLBACK fun, VOID *val);

extern VOID PIN_StartProgram();

extern ADDRINT INS_Address(INS ins);

extern THREADID PIN_SpawnInternalThread(ROOT_THREAD_FUNC * pThreadFunc, VOID * arg, size_t stackSize, PIN_THREAD_UID * pThreadUid);

extern INS INS_Next(INS x);

extern BOOL INS_Valid(INS x);

extern USIZE BBL_Size(BBL bbl);

extern INS BBL_InsHead(BBL x);

extern USIZE INS_Size(INS ins);

extern ADDRINT BBL_Address(BBL bbl);

extern THREADID PIN_ThreadId();

extern ADDRINT PIN_GetSyscallNumber(const CONTEXT *ctxt, SYSCALL_STANDARD std);

extern VOID PIN_SetSyscallArgument(CONTEXT *ctxt, SYSCALL_STANDARD std, UINT32 argNum, ADDRINT val);

extern ADDRINT PIN_GetSyscallArgument(const CONTEXT *ctxt, SYSCALL_STANDARD std, UINT32 argNum);

extern VOID PIN_SetContextReg(CONTEXT * ctxt, REG reg, ADDRINT val);

extern VOID PIN_SetSyscallNumber(CONTEXT *ctxt, SYSCALL_STANDARD std, ADDRINT val);

extern ADDRINT PIN_GetContextReg(const CONTEXT * ctxt, REG reg);

extern size_t PIN_SafeCopy(VOID * dst, const VOID * src, size_t size);

extern VOID PIN_RemoveInstrumentation();

extern BBL TRACE_BblHead(TRACE trace);

extern BOOL BBL_Valid(BBL x);

extern VOID BBL_InsertCall(BBL bbl, IPOINT action, AFUNPTR funptr, ...);

extern BBL BBL_Next(BBL x);

extern INT PIN_GetPid();

extern VOID GetVmLock();

extern VOID ReleaseVmLock();

extern VOID PIN_InitSymbols();

typedef EXCEPT_HANDLING_RESULT (*INTERNAL_EXCEPTION_CALLBACK)(THREADID tid,
                   EXCEPTION_INFO * pExceptInfo, PHYSICAL_CONTEXT * pPhysCtxt, VOID * v);

extern PIN_CALLBACK PIN_AddInternalExceptionHandler(INTERNAL_EXCEPTION_CALLBACK fun, VOID *val);


extern VOID CHILD_PROCESS_GetCommandLine(CHILD_PROCESS childProcess, INT * pArgc, const CHAR * const ** pArgv); 

extern VOID CHILD_PROCESS_SetPinCommandLine(CHILD_PROCESS childProcess, INT argc, const CHAR * const * argv);

extern PIN_CALLBACK TRACE_AddInstrumentFunction(TRACE_INSTRUMENT_CALLBACK fun, VOID *val);

extern PIN_CALLBACK PIN_AddThreadStartFunction(THREAD_START_CALLBACK fun, VOID *val);

extern PIN_CALLBACK PIN_AddThreadFiniFunction(THREAD_FINI_CALLBACK fun, VOID *val);

extern PIN_CALLBACK PIN_AddSyscallEntryFunction(SYSCALL_ENTRY_CALLBACK fun, VOID *val);

extern PIN_CALLBACK PIN_AddSyscallExitFunction(SYSCALL_EXIT_CALLBACK fun, VOID *val);

extern PIN_CALLBACK PIN_AddContextChangeFunction(CONTEXT_CHANGE_CALLBACK fun, VOID *val);


typedef LEVEL_BASE::CHILD_PROCESS_CLASS * CHILD_PROCESS;

typedef BOOL (*FOLLOW_CHILD_PROCESS_CALLBACK)(CHILD_PROCESS childProcess, VOID * val);

extern PIN_CALLBACK PIN_AddFollowChildProcessFunction(FOLLOW_CHILD_PROCESS_CALLBACK fun, VOID * val);

enum FPOINT
{
    FPOINT_BEFORE,
    FPOINT_AFTER_IN_PARENT,
    FPOINT_AFTER_IN_CHILD
};

extern PIN_CALLBACK PIN_AddForkFunction(FPOINT point, FORK_CALLBACK fun, VOID *val);

extern PIN_CALLBACK IMG_AddInstrumentFunction(IMAGECALLBACK fun, VOID *v);

extern RTN RTN_FindByName(IMG img, const CHAR * name);

extern ADDRINT RTN_Address(RTN rtn);

extern RTN RTN_Invalid();

extern IMG IMG_Open(const string& filename);

extern VOID IMG_Close(IMG img);

extern INS BBL_InsTail(BBL bbl);

extern ADDRINT INS_DirectBranchOrCallTargetAddress(INS ins);

extern IMG_TYPE IMG_Type(IMG img);

extern BOOL IMG_IsMainExecutable(IMG x);

extern const string& IMG_Name(IMG img);

extern SEC IMG_SecHead(IMG img);

extern BOOL IMG_Valid(IMG img);

extern BOOL SEC_Valid(SEC x);

extern IMG IMG_FindByAddress(ADDRINT address);

extern ADDRINT IMG_LowAddress(IMG img);

extern ADDRINT IMG_HighAddress(IMG img);

extern PIN_CALLBACK IMG_AddUnloadFunction(IMAGECALLBACK fun, VOID *v);

extern string RTN_FindNameByAddress(ADDRINT address);

}



using namespace LEVEL_PINCLIENT;

extern BOOL INS_IsMemoryRead(INS ins);

extern BOOL INS_IsMemoryWrite(INS ins);

extern BOOL INS_IsPredicated(INS ins);

extern BOOL INS_HasMemoryRead2(INS ins);

extern BOOL INS_IsXchg(INS ins);

extern BOOL INS_IsRDTSC(const INS ins);

extern BOOL INS_IsCall(INS ins);

extern BOOL INS_IsRet(INS ins);

#endif
