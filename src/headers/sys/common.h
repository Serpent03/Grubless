#pragma once

#define true 1
#define false 0
#define __stdcall __attribute__((stdcall))
#define __cdecl __attribute__((cdecl))
#define __syscall __attribute__((syscall))
#define __ms_abi __attribute__((ms_abi))

typedef unsigned char uint8;
typedef char int8;
typedef unsigned short int uint16;
typedef short int int16;
typedef unsigned int uint32;
typedef int int32;
typedef unsigned long int uint64;
typedef long int int64;

typedef unsigned char bool;