//
// Platform.h
// Platform and architecture identification macros.
//
// NOTE: This file may be included from both C++ and C code, so it
//       must not contain any C++ specific things.
//
//


#ifndef Foundation_Platform_INCLUDED
#define Foundation_Platform_INCLUDED


//
// Platform Identification
//
#define HERMES_OS_FREE_BSD      0x0001
#define HERMES_OS_AIX           0x0002
#define HERMES_OS_HPUX          0x0003
#define HERMES_OS_TRU64         0x0004
#define HERMES_OS_LINUX         0x0005
#define HERMES_OS_MAC_OS_X      0x0006
#define HERMES_OS_NET_BSD       0x0007
#define HERMES_OS_OPEN_BSD      0x0008
#define HERMES_OS_IRIX          0x0009
#define HERMES_OS_SOLARIS       0x000a
#define HERMES_OS_QNX           0x000b
#define HERMES_OS_VXWORKS       0x000c
#define HERMES_OS_CYGWIN        0x000d
#define HERMES_OS_UNKNOWN_UNIX  0x00ff
#define HERMES_OS_WINDOWS_NT    0x1001
#define HERMES_OS_WINDOWS_CE    0x1011
#define HERMES_OS_VMS           0x2001


#if defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
	#define HERMES_OS_FAMILY_UNIX 1
	#define HERMES_OS_FAMILY_BSD 1
	#define HERMES_OS HERMES_OS_FREE_BSD
#elif defined(_AIX) || defined(__TOS_AIX__)
	#define HERMES_OS_FAMILY_UNIX 1
	#define HERMES_OS HERMES_OS_AIX
#elif defined(hpux) || defined(_hpux) || defined(__hpux)
	#define HERMES_OS_FAMILY_UNIX 1
	#define HERMES_OS HERMES_OS_HPUX
#elif defined(__digital__) || defined(__osf__)
	#define HERMES_OS_FAMILY_UNIX 1
	#define HERMES_OS HERMES_OS_TRU64
#elif defined(linux) || defined(__linux) || defined(__linux__) || defined(__TOS_LINUX__) || defined(EMSCRIPTEN)
	#define HERMES_OS_FAMILY_UNIX 1
	#define HERMES_OS HERMES_OS_LINUX
#elif defined(__APPLE__) || defined(__TOS_MACOS__)
	#define HERMES_OS_FAMILY_UNIX 1
	#define HERMES_OS_FAMILY_BSD 1
	#define HERMES_OS HERMES_OS_MAC_OS_X
#elif defined(__NetBSD__)
	#define HERMES_OS_FAMILY_UNIX 1
	#define HERMES_OS_FAMILY_BSD 1
	#define HERMES_OS HERMES_OS_NET_BSD
#elif defined(__OpenBSD__)
	#define HERMES_OS_FAMILY_UNIX 1
	#define HERMES_OS_FAMILY_BSD 1
	#define HERMES_OS HERMES_OS_OPEN_BSD
#elif defined(sgi) || defined(__sgi)
	#define HERMES_OS_FAMILY_UNIX 1
	#define HERMES_OS HERMES_OS_IRIX
#elif defined(sun) || defined(__sun)
	#define HERMES_OS_FAMILY_UNIX 1
	#define HERMES_OS HERMES_OS_SOLARIS
#elif defined(__QNX__)
	#define HERMES_OS_FAMILY_UNIX 1
	#define HERMES_OS HERMES_OS_QNX
#elif defined(__CYGWIN__)
	#define HERMES_OS_FAMILY_UNIX 1
	#define HERMES_OS HERMES_OS_CYGWIN
#elif defined(HERMES_VXWORKS)
  #define HERMES_OS_FAMILY_UNIX 1
  #define HERMES_OS HERMES_OS_VXWORKS
#elif defined(unix) || defined(__unix) || defined(__unix__)
	#define HERMES_OS_FAMILY_UNIX 1
	#define HERMES_OS HERMES_OS_UNKNOWN_UNIX
#elif defined(_WIN32_WCE)
	#define HERMES_OS_FAMILY_WINDOWS 1
	#define HERMES_OS HERMES_OS_WINDOWS_CE
#elif defined(_WIN32) || defined(_WIN64)
	#define HERMES_OS_FAMILY_WINDOWS 1
	#define HERMES_OS HERMES_OS_WINDOWS_NT
#elif defined(__VMS)
	#define HERMES_OS_FAMILY_VMS 1
	#define HERMES_OS HERMES_OS_VMS
#endif


#if !defined(HERMES_OS)
	#error "Unknown Platform."
#endif


#ifndef HERMES_OS_FAMILY_UNIX
	#define GCC_DIAG_OFF(x)
	#define GCC_DIAG_ON(x)
#endif

//
// Hardware Architecture and Byte Order
//
#define HERMES_ARCH_ALPHA   0x01
#define HERMES_ARCH_IA32    0x02
#define HERMES_ARCH_IA64    0x03
#define HERMES_ARCH_MIPS    0x04
#define HERMES_ARCH_HPPA    0x05
#define HERMES_ARCH_PPC     0x06
#define HERMES_ARCH_POWER   0x07
#define HERMES_ARCH_SPARC   0x08
#define HERMES_ARCH_AMD64   0x09
#define HERMES_ARCH_ARM     0x0a
#define HERMES_ARCH_M68K    0x0b
#define HERMES_ARCH_S390    0x0c
#define HERMES_ARCH_SH      0x0d
#define HERMES_ARCH_NIOS2   0x0e
#define HERMES_ARCH_AARCH64 0x0f


#if defined(__ALPHA) || defined(__alpha) || defined(__alpha__) || defined(_M_ALPHA)
	#define HERMES_ARCH HERMES_ARCH_ALPHA
	#define HERMES_ARCH_LITTLE_ENDIAN 1
#elif defined(i386) || defined(__i386) || defined(__i386__) || defined(_M_IX86) || defined(EMSCRIPTEN)
	#define HERMES_ARCH HERMES_ARCH_IA32
	#define HERMES_ARCH_LITTLE_ENDIAN 1
#elif defined(_IA64) || defined(__IA64__) || defined(__ia64__) || defined(__ia64) || defined(_M_IA64)
	#define HERMES_ARCH HERMES_ARCH_IA64
	#if defined(hpux) || defined(_hpux)
		#define HERMES_ARCH_BIG_ENDIAN 1
	#else
		#define HERMES_ARCH_LITTLE_ENDIAN 1
	#endif
#elif defined(__x86_64__) || defined(_M_X64)
	#define HERMES_ARCH HERMES_ARCH_AMD64
	#define HERMES_ARCH_LITTLE_ENDIAN 1
#elif defined(__mips__) || defined(__mips) || defined(__MIPS__) || defined(_M_MRX000)
	#define HERMES_ARCH HERMES_ARCH_MIPS
	#if defined(HERMES_OS_FAMILY_WINDOWS)
		// Is this OK? Supports windows only little endian??
		#define HERMES_ARCH_LITTLE_ENDIAN 1
	#elif defined(__MIPSEB__) || defined(_MIPSEB) || defined(__MIPSEB)
		#define HERMES_ARCH_BIG_ENDIAN 1
	#elif defined(__MIPSEL__) || defined(_MIPSEL) || defined(__MIPSEL)
		#define HERMES_ARCH_LITTLE_ENDIAN 1
	#else
		#error "MIPS but neither MIPSEL nor MIPSEB?"
	#endif

#elif defined(__hppa) || defined(__hppa__)
	#define HERMES_ARCH HERMES_ARCH_HPPA
	#define HERMES_ARCH_BIG_ENDIAN 1
#elif defined(__PPC) || defined(__POWERPC__) || defined(__powerpc) || defined(__PPC__) || \
      defined(__powerpc__) || defined(__ppc__) || defined(__ppc) || defined(_ARCH_PPC) || defined(_M_PPC)
	#define HERMES_ARCH HERMES_ARCH_PPC
	#define HERMES_ARCH_BIG_ENDIAN 1
#elif defined(_POWER) || defined(_ARCH_PWR) || defined(_ARCH_PWR2) || defined(_ARCH_PWR3) || \
      defined(_ARCH_PWR4) || defined(__THW_RS6000)
	#define HERMES_ARCH HERMES_ARCH_POWER
	#define HERMES_ARCH_BIG_ENDIAN 1
#elif defined(__sparc__) || defined(__sparc) || defined(sparc)
	#define HERMES_ARCH HERMES_ARCH_SPARC
	#define HERMES_ARCH_BIG_ENDIAN 1
#elif defined(__arm__) || defined(__arm) || defined(ARM) || defined(_ARM_) || defined(__ARM__) || defined(_M_ARM)
	#define HERMES_ARCH HERMES_ARCH_ARM
	#if defined(__ARMEB__)
		#define HERMES_ARCH_BIG_ENDIAN 1
	#else
		#define HERMES_ARCH_LITTLE_ENDIAN 1
	#endif
#elif defined(__arm64__) || defined(__arm64) 
	#define HERMES_ARCH HERMES_ARCH_ARM64
	#if defined(__ARMEB__)
		#define HERMES_ARCH_BIG_ENDIAN 1
	#elif defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		#define HERMES_ARCH_BIG_ENDIAN 1
	#else
		#define HERMES_ARCH_LITTLE_ENDIAN 1
	#endif
#elif defined(__m68k__)
	#define HERMES_ARCH HERMES_ARCH_M68K
	#define HERMES_ARCH_BIG_ENDIAN 1
#elif defined(__s390__)
	#define HERMES_ARCH HERMES_ARCH_S390
	#define HERMES_ARCH_BIG_ENDIAN 1
#elif defined(__sh__) || defined(__sh) || defined(SHx) || defined(_SHX_)
	#define HERMES_ARCH HERMES_ARCH_SH
	#if defined(__LITTLE_ENDIAN__) || (HERMES_OS == HERMES_OS_WINDOWS_CE)
		#define HERMES_ARCH_LITTLE_ENDIAN 1
	#else
		#define HERMES_ARCH_BIG_ENDIAN 1
	#endif
#elif defined (nios2) || defined(__nios2) || defined(__nios2__)
	#define HERMES_ARCH HERMES_ARCH_NIOS2
	#if defined(__nios2_little_endian) || defined(nios2_little_endian) || defined(__nios2_little_endian__)
		#define HERMES_ARCH_LITTLE_ENDIAN 1
	#else
		#define HERMES_ARCH_BIG_ENDIAN 1
	#endif
#elif defined(__AARCH64EL__)
	#define HERMES_ARCH HERMES_ARCH_AARCH64
	#define HERMES_ARCH_LITTLE_ENDIAN 1
#elif defined(__AARCH64EB__)
	#define HERMES_ARCH HERMES_ARCH_AARCH64
	#define HERMES_ARCH_BIG_ENDIAN 1
#endif


#if defined(_MSC_VER)
	#define HERMES_COMPILER_MSVC
#elif defined(__clang__)
	#define HERMES_COMPILER_CLANG
#elif defined (__GNUC__)
	#define HERMES_COMPILER_GCC
#elif defined (__MINGW32__) || defined (__MINGW64__)
	#define HERMES_COMPILER_MINGW
#elif defined (__INTEL_COMPILER) || defined(__ICC) || defined(__ECC) || defined(__ICL)
	#define HERMES_COMPILER_INTEL
#elif defined (__SUNPRO_CC)
	#define HERMES_COMPILER_SUN
#elif defined (__MWERKS__) || defined(__CWCC__)
	#define HERMES_COMPILER_CODEWARRIOR
#elif defined (__sgi) || defined(sgi)
	#define HERMES_COMPILER_SGI
#elif defined (__HP_aCC)
	#define HERMES_COMPILER_HP_ACC
#elif defined (__BORLANDC__) || defined(__CODEGEARC__)
	#define HERMES_COMPILER_CBUILDER
#elif defined (__DMC__)
	#define HERMES_COMPILER_DMARS
#elif defined (__HP_aCC)
	#define HERMES_COMPILER_HP_ACC
#elif (defined (__xlc__) || defined (__xlC__)) && defined(__IBMCPP__)
	#define HERMES_COMPILER_IBM_XLC // IBM XL C++
#elif defined (__IBMCPP__) && defined(__COMPILER_VER__)
	#define HERMES_COMPILER_IBM_XLC_ZOS // IBM z/OS C++
#endif


#if !defined(HERMES_ARCH)
	#error "Unknown Hardware Architecture."
#endif


#if defined(HERMES_OS_FAMILY_WINDOWS)
	#define HERMES_DEFAULT_NEWLINE_CHARS "\r\n"
#else
	#define HERMES_DEFAULT_NEWLINE_CHARS "\n"
#endif


#endif // Foundation_Platform_INCLUDED
