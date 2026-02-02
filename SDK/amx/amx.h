/*  Pawn Abstract Machine (for the Pawn language)
 *
 *  Copyright (c) ITB CompuPhase, 1997-2005
 *
 *  This software is provided "as-is", without any express or implied warranty.
 *  In no event will the authors be held liable for any damages arising from
 *  the use of this software.
 *
 *  Permission is granted to anyone to use this software for any purpose,
 *  including commercial applications, and to alter it and redistribute it
 *  freely, subject to the following restrictions:
 *
 *  1.  The origin of this software must not be misrepresented; you must not
 *      claim that you wrote the original software. If you use this software in
 *      a product, an acknowledgment in the product documentation would be
 *      appreciated but is not required.
 *  2.  Altered source versions must be plainly marked as such, and must not be
 *      misrepresented as being the original software.
 *  3.  This notice may not be removed or altered from any source distribution.
 */

#ifndef AMX_H_INCLUDED
#define AMX_H_INCLUDED

#include <stddef.h>
#include <limits.h>

#if defined(__linux__) || defined(__linux) || defined(__unix__) || defined(__APPLE__)
  #if !defined __GNUC__
    #define __GNUC__ 1
  #endif
#endif

#if defined(__GNUC__)
  #define PACKED __attribute__((packed))
#else
  #define PACKED
#endif

#if defined(_MSC_VER)
  #pragma warning(disable:4100)
#endif

#if defined __LCC__ || defined __DMC__ || defined LINUX || defined __GNUC__
  #if defined HAVE_STDINT_H
    #include <stdint.h>
  #else
    #if defined __FreeBSD__
      #include <inttypes.h>
    #endif
    typedef signed char         int8_t;
    typedef unsigned char       uint8_t;
    typedef signed short        int16_t;
    typedef unsigned short      uint16_t;
    typedef signed int          int32_t;
    typedef unsigned int        uint32_t;
  #endif
  typedef int32_t               cell;
  typedef uint32_t              ucell;
#else
  typedef signed int            cell;
  typedef unsigned int          ucell;
#endif

#if defined _I64_MAX
  typedef signed __int64        cell64_t;
  typedef unsigned __int64      ucell64_t;
  #define REAL double
#else
  #define REAL float
#endif

/* Various compile-time options */
#ifndef AMX_ANSIONLY
  #if defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #define AMX_WIN32 1
  #endif
#endif

#if !defined AMX_NO_ALIGN
  #if defined __LINUX__ || defined __FreeBSD__ || defined __APPLE__
    #pragma pack(1)
  #endif
#endif

#if !defined AMXAPI
  #if defined STDECL
    #define AMXAPI      __stdcall
  #elif defined CDECL
    #define AMXAPI      __cdecl
  #elif defined GCC_HASCLASSVISIBILITY
    #define AMXAPI __attribute__ ((visibility("default")))
  #else
    #define AMXAPI
  #endif
#endif
#if !defined AMXEXPORT
  #if defined STDECL
    #define AMXEXPORT   __stdcall
  #elif defined CDECL
    #define AMXEXPORT   __cdecl
  #elif defined GCC_HASCLASSVISIBILITY
    #define AMXEXPORT __attribute__ ((visibility("default")))
  #else
    #define AMXEXPORT
  #endif
#endif

/* calling convention for native functions */
#if !defined AMX_NATIVE_CALL
  #define AMX_NATIVE_CALL
#endif

struct tagAMX;

typedef cell   (AMXAPI *AMX_NATIVE)(struct tagAMX *amx, cell *params);
typedef int    (AMXAPI *AMX_CALLBACK)(struct tagAMX *amx, cell index, cell *result, cell *params);
typedef int    (AMXAPI *AMX_DEBUG)(struct tagAMX *amx);
typedef int    (AMXAPI *AMX_IDLE)(struct tagAMX *amx, int AMXAPI Exec(struct tagAMX *, cell *, int));

#if !defined FAR
  #define FAR
#endif

#if defined _MSC_VER
  #pragma warning(disable:4103)
  #pragma warning(disable:4100)
  #if _MSC_VER >= 1400
    #if !defined _CRT_SECURE_NO_DEPRECATE
      #define _CRT_SECURE_NO_DEPRECATE
    #endif
    #if !defined _CRT_SECURE_NO_WARNINGS
      #define _CRT_SECURE_NO_WARNINGS
    #endif
  #endif
#endif

#if !defined SMALL_CELL_SIZE
  #define SMALL_CELL_SIZE 32
#endif

typedef struct tagAMX_NATIVE_INFO {
  const char FAR *name;
  AMX_NATIVE func;
} AMX_NATIVE_INFO;

#define AMX_USERNUM     4

#define sEXPMAX         19
#define sCHARBIT        8

typedef struct tagFUNCSTUB {
  ucell address;
  char    name[sEXPMAX+1];
} FUNCSTUB;

typedef struct tagFUNCSTUBNT {
  ucell address;
  uint32_t nameofs;
} FUNCSTUBNT;

#define DEFSTACK_SIZE   4096
#define DEFHEAP_SIZE    16384

#define AMX_ERR_NONE        0
#define AMX_ERR_EXIT        1
#define AMX_ERR_ASSERT      2
#define AMX_ERR_STACKERR    3
#define AMX_ERR_BOUNDS      4
#define AMX_ERR_MEMACCESS   5
#define AMX_ERR_INVINSTR    6
#define AMX_ERR_STACKLOW    7
#define AMX_ERR_HEAPLOW     8
#define AMX_ERR_CALLBACK    9
#define AMX_ERR_NATIVE      10
#define AMX_ERR_DIVIDE      11
#define AMX_ERR_SLEEP       12
#define AMX_ERR_INVSTATE    13

#define AMX_ERR_MEMORY      16
#define AMX_ERR_FORMAT      17
#define AMX_ERR_VERSION     18
#define AMX_ERR_NOTFOUND    19
#define AMX_ERR_INDEX       20
#define AMX_ERR_DEBUG       21
#define AMX_ERR_INIT        22
#define AMX_ERR_USERDATA    23
#define AMX_ERR_INIT_JIT    24
#define AMX_ERR_PARAMS      25
#define AMX_ERR_DOMAIN      26
#define AMX_ERR_GENERAL     27

#define AMX_FLAG_DEBUG      0x02
#define AMX_FLAG_COMPACT    0x04
#define AMX_FLAG_BYTEOPC    0x08
#define AMX_FLAG_NOCHECKS   0x10
#define AMX_FLAG_NTVREG     0x1000
#define AMX_FLAG_JITC       0x2000
#define AMX_FLAG_BROWSE     0x4000
#define AMX_FLAG_RELOC      0x8000

#define AMX_EXEC_MAIN       (-1)
#define AMX_EXEC_CONT       (-2)

#define AMX_USERTAG(a,b,c,d)  ((a) | ((b)<<8) | ((long)(c)<<16) | ((long)(d)<<24))

typedef struct tagAMX_HEADER {
  int32_t size;
  uint16_t magic;
  char    file_version;
  char    amx_version;
  int16_t flags;
  int16_t defsize;
  int32_t cod;
  int32_t dat;
  int32_t hea;
  int32_t stp;
  int32_t cip;
  int32_t publics;
  int32_t natives;
  int32_t libraries;
  int32_t pubvars;
  int32_t tags;
  int32_t nametable;
} PACKED AMX_HEADER;

#define AMX_MAGIC   0xf1e0

typedef struct tagAMX {
  unsigned char FAR *base;
  unsigned char FAR *data;
  AMX_CALLBACK callback;
  AMX_DEBUG debug;
  cell cip;
  cell frm;
  cell hea;
  cell hlw;
  cell stk;
  cell stp;
  int flags;
  long usertags[AMX_USERNUM];
  void FAR *userdata[AMX_USERNUM];
  int error;
  int paramcount;
  cell pri;
  cell alt;
  cell reset_stk;
  cell reset_hea;
  cell sysreq_d;
#if defined AMX_JIT
  int reloc_size;
  long code_size;
#endif
} PACKED AMX;

enum {
  DBG_INIT,
  DBG_FILE,
  DBG_LINE,
  DBG_SYMBOL,
  DBG_CLRSYM,
  DBG_CALL,
  DBG_RETURN,
  DBG_TERMINATE,
  DBG_SRANGE,
  DBG_SYMTAG,
};

typedef struct tagAMX_DBG_HDR {
  int32_t size;
  uint16_t magic;
  char    file_version;
  char    amx_version;
  int16_t flags;
  int16_t files;
  int16_t lines;
  int16_t symbols;
  int16_t tags;
  int16_t automatons;
  int16_t states;
} PACKED AMX_DBG_HDR;

typedef struct tagAMX_DBG_FILE {
  ucell address;
  const char name[1];
} PACKED AMX_DBG_FILE;

typedef struct tagAMX_DBG_LINE {
  ucell address;
  int32_t line;
} PACKED AMX_DBG_LINE;

typedef struct tagAMX_DBG_SYMBOL {
  ucell address;
  int16_t tag;
  cell    codestart;
  cell    codeend;
  char    ident;
  char    vclass;
  int16_t dim;
  const char name[1];
} PACKED AMX_DBG_SYMBOL;

typedef struct tagAMX_DBG_SYMDIM {
  int16_t tag;
  ucell size;
} PACKED AMX_DBG_SYMDIM;

typedef struct tagAMX_DBG_TAG {
  int16_t tag;
  const char name[1];
} PACKED AMX_DBG_TAG;

typedef struct tagAMX_DBG_MACHINE {
  int16_t automaton;
  ucell address;
  const char name[1];
} PACKED AMX_DBG_MACHINE;

typedef struct tagAMX_DBG_STATE {
  int16_t state;
  int16_t automaton;
  const char name[1];
} PACKED AMX_DBG_STATE;

typedef struct tagAMX_DBG {
  AMX_DBG_HDR FAR *hdr;
  AMX_DBG_FILE FAR **filetbl;
  AMX_DBG_LINE FAR *linetbl;
  AMX_DBG_SYMBOL FAR **symboltbl;
  AMX_DBG_TAG FAR **tagtbl;
  AMX_DBG_MACHINE FAR **automatontbl;
  AMX_DBG_STATE FAR **statetbl;
} AMX_DBG;

#if !defined iVARIABLE
  #define iVARIABLE  1
  #define iREFERENCE 2
  #define iARRAY     3
  #define iREFARRAY  4
#endif

#if !defined AMXAPI
  #if defined STDECL
    #define AMXAPI      __stdcall
  #elif defined CDECL
    #define AMXAPI      __cdecl
  #else
    #define AMXAPI
  #endif
#endif

#if defined __cplusplus
  extern "C" {
#endif

uint16_t * AMXAPI amx_Align16(uint16_t *v);
uint32_t * AMXAPI amx_Align32(uint32_t *v);
#if defined _I64_MAX || defined HAVE_I64
  uint64_t * AMXAPI amx_Align64(uint64_t *v);
#endif
int AMXAPI amx_Allot(AMX *amx, int cells, cell *amx_addr, cell **phys_addr);
int AMXAPI amx_Callback(AMX *amx, cell index, cell *result, cell *params);
int AMXAPI amx_Cleanup(AMX *amx);
int AMXAPI amx_Clone(AMX *amxClone, AMX *amxSource, void *data);
int AMXAPI amx_Exec(AMX *amx, cell *retval, int index);
int AMXAPI amx_FindNative(AMX *amx, const char *name, int *index);
int AMXAPI amx_FindPublic(AMX *amx, const char *funcname, int *index);
int AMXAPI amx_FindPubVar(AMX *amx, const char *varname, cell *amx_addr);
int AMXAPI amx_FindTagId(AMX *amx, cell tag_id, char *tagname);
int AMXAPI amx_Flags(AMX *amx, uint16_t *flags);
int AMXAPI amx_GetAddr(AMX *amx, cell amx_addr, cell **phys_addr);
int AMXAPI amx_GetNative(AMX *amx, int index, char *funcname);
int AMXAPI amx_GetPublic(AMX *amx, int index, char *funcname);
int AMXAPI amx_GetPubVar(AMX *amx, int index, char *varname, cell *amx_addr);
int AMXAPI amx_GetString(char *dest, const cell *source, int use_wchar, size_t size);
int AMXAPI amx_GetTag(AMX *amx, int index, char *tagname, cell *tag_id);
int AMXAPI amx_GetUserData(AMX *amx, long tag, void **ptr);
int AMXAPI amx_Init(AMX *amx, void *program);
int AMXAPI amx_InitJIT(AMX *amx, void *reloc_table, void *native_code);
int AMXAPI amx_MemInfo(AMX *amx, long *codesize, long *datasize, long *stackheap);
int AMXAPI amx_NameLength(AMX *amx, int *length);
AMX_NATIVE_INFO * AMXAPI amx_NativeInfo(const char *name, AMX_NATIVE func);
int AMXAPI amx_NumNatives(AMX *amx, int *number);
int AMXAPI amx_NumPublics(AMX *amx, int *number);
int AMXAPI amx_NumPubVars(AMX *amx, int *number);
int AMXAPI amx_NumTags(AMX *amx, int *number);
int AMXAPI amx_Push(AMX *amx, cell value);
int AMXAPI amx_PushArray(AMX *amx, cell *amx_addr, cell **phys_addr, const cell array[], int numcells);
int AMXAPI amx_PushString(AMX *amx, cell *amx_addr, cell **phys_addr, const char *string, int pack, int use_wchar);
int AMXAPI amx_RaiseError(AMX *amx, int error);
int AMXAPI amx_Register(AMX *amx, const AMX_NATIVE_INFO *nativelist, int number);
int AMXAPI amx_Release(AMX *amx, cell amx_addr);
int AMXAPI amx_SetCallback(AMX *amx, AMX_CALLBACK callback);
int AMXAPI amx_SetDebugHook(AMX *amx, AMX_DEBUG debug);
int AMXAPI amx_SetString(cell *dest, const char *source, int pack, int use_wchar, size_t size);
int AMXAPI amx_SetUserData(AMX *amx, long tag, void *ptr);
int AMXAPI amx_StrLen(const cell *cstring, int *length);
int AMXAPI amx_UTF8Check(const char *string, int *length);
int AMXAPI amx_UTF8Get(const char *string, const char **endptr, cell *value);
int AMXAPI amx_UTF8Len(const cell *cstr, int *length);
int AMXAPI amx_UTF8Put(char *string, char **endptr, int maxchars, cell value);

#if defined __cplusplus
  }
#endif

#if !defined AMX_NO_ALIGN
  #if defined __LINUX__ || defined __FreeBSD__ || defined __APPLE__
    #pragma pack()
  #endif
#endif

#if defined __GNUC__
  #undef PACKED
#endif

#define amx_ctof(c)   ( *((float*)&(c)) )
#define amx_ftoc(f)   ( *((cell*)&(f)) )

#define amx_StrParam(amx,param,result)                                      \
    do {                                                                    \
      cell *amx_cstr_; int amx_length_;                                     \
      amx_GetAddr((amx), (param), &amx_cstr_);                              \
      amx_StrLen(amx_cstr_, &amx_length_);                                  \
      if (amx_length_ > 0 &&                                                \
          ((result) = (char*)alloca((amx_length_ + 1) * sizeof(*(result)))) != NULL) \
        amx_GetString((char*)(result), amx_cstr_, sizeof(*(result)) > 1, amx_length_ + 1); \
      else (result) = NULL;                                                 \
    } while (0)

#endif /* AMX_H_INCLUDED */
