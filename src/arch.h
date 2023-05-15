/*
 * Authors:
 *   Andrew Clark     - andrew.clark.6@bc.edu
 *   Alex Liu         - alex.liu@bc.edu
 *   Caden Parajuli   - caden.parajuli@bc.edu
 *   Micheal Lebreck  - michael.lebreck@bc.edu
 *   William Morrison - william.morrison.2@bc.edu
 */


#ifndef ARCH_H
#define ARCH_H


typedef enum {
    cpu_x86_64, cpu_x86_32, cpu_8086,
    cpu_arm_v2, cpu_arm_v3, cpu_arm_v4t, cpu_arm_v5, cpu_arm_v6t2, cpu_arm_v6, cpu_arm_64,
    cpu_mips,
    cpu_superh,
    cpu_powerpc,
    cpu_powerpc_64,
    cpu_sparc,
    cpu_m68k,
    cpu_unknown
} CpuArch;

typedef enum {
    os_linux,
    os_mac,
    os_windows
} OSInfo;

/* Check operating system
 * Based on github.com/cpredef/predef/blob/master/OperatingSystems.md
 */

#if defined(__linux__)
#define __build_os__ os_linux
#elif defined(macintosh) || defined(Macintosh) || (defined(__APPLE__) && defined(__MACH__))
#define __build_os__ os_mac
#elif defined(_WIN16) || defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
#define __build_os__ os_windows
#endif


/* Check CPU architecture. Currently errors out if it isn't x86-64
 * Adapted from https://stackoverflow.com/a/66249936/6616869
 * with additions from https://sourceforge.net/p/predef/wiki/Architectures
 */

#if defined(__x86_64__) || defined(_M_X64) || defined(_M_AMD64) || defined(__amd64__) || defined(__amd64)
#define __build_cpu_arch__ cpu_x86_64
#elif defined(_M_I86)
#define __build_cpu_arch__ cpu_8086
#elif defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86) || defined(_X86_)
#define __build_cpu_arch__ cpu_x86_32
#elif defined(__ARM_ARCH_2__)
#define __build_cpu_arch__ cpu_arm_v2
#elif defined(__ARM_ARCH_3__) || defined(__ARM_ARCH_3M__)
#define __build_cpu_arch__ cpu_arm_v3
#elif defined(__ARM_ARCH_4T__) || defined(__TARGET_ARM_4T)
#define __build_cpu_arch__ cpu_arm_v4t
#elif defined(__ARM_ARCH_5_) || defined(__ARM_ARCH_5E_)
#define __build_cpu_arch__ cpu_arm_v5
#elif defined(__ARM_ARCH_6T2_)
#define __build_cpu_arch__ cpu_arm_v6t2
#elif defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) || defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__) || defined(__ARM_ARCH_6ZK__)
#define __build_cpu_arch__ cpu_arm_v6
#elif defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
#define __build_cpu_arch__ cpu_arm_v7
#elif defined(__aarch64__) || defined(_M_ARM64)
#define __build_cpu_arch__ cpu_arm_64
#elif defined(mips) || defined(__mips__) || defined(__mips)
#define __build_cpu_arch__ cpu_mips
#elif defined(__sh__)
#define __build_cpu_arch__ cpu_superh
#elif defined(__powerpc) || defined(__powerpc__)  || defined(__POWERPC__) || defined(__ppc__) || defined(__PPC__) || defined(_ARCH_PPC)
#define __build_cpu_arch__ cpu_powerpc
#elif defined(__PPC64__) || defined(__ppc64__) || defined(_ARCH_PPC64) || defined(__powerpc64__)
#define __build_cpu_arch__ cpu_powerpc_64
#elif defined(__sparc__) || defined(__sparc)
#define __build_cpu_arch__ cpu_sparc
#elif defined(__m68k__) || defined(M68000) || defined(__MC68K__)
#define __build_cpu_arch__ cpu_m68k
#else
#define __build_cpu_arch__ cpu_unknown
#endif

/* Error out if CPU architecture is unsupported */
#if __build_cpu_arch__!=cpu_x86_64
#error "CPU architecture not supported. Currently only x86-64 is supported"
#endif

#endif /* ARCH_H */
