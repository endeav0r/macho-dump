#include "macho_field_string.h"

#include "macho_spec.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct string_search {
  uint32_t value;
  const char * string;
};

#define STRING_SEARCH_UNKNOWN_STR_SIZE 64
char STRING_SEARCH_UNKNOWN_STR[STRING_SEARCH_UNKNOWN_STR_SIZE];

#define STRING_SEARCH_FLAGS_STR_SIZE 1024
char STRING_SEARCH_FLAGS_STR[STRING_SEARCH_FLAGS_STR_SIZE];

struct string_search STRING_SEARCH_CPUTYPE [] = {
    {CPU_TYPE_ANY, "ANY"},
    {CPU_ARCH_ABI64, "ABI64"},
    {CPU_TYPE_VAX, "VAX"},
    {CPU_TYPE_ROMP, "ROMP"},
    {CPU_TYPE_NS32032, "NS32032"},
    {CPU_TYPE_NS32332, "NS32332"},
    {CPU_TYPE_MC680x0, "MC680x0"},
    {CPU_TYPE_I386, "I386"},
    {CPU_TYPE_X86_64, "X86_64"},
    {CPU_TYPE_MIPS, "MIPS"},
    {CPU_TYPE_NS32532, "NS32532"},
    {CPU_TYPE_HPPA, "HPPA"},
    {CPU_TYPE_ARM, "ARM"},
    {CPU_TYPE_MC88000, "MC88000"},
    {CPU_TYPE_SPARC, "SPARC"},
    {CPU_TYPE_I860, "I860"},
    {CPU_TYPE_I860_LITTLE, "I860_LITTLE"},
    {CPU_TYPE_RS6000, "RS6000"},
    {CPU_TYPE_MC98000, "MC98000"},
    {CPU_TYPE_POWERPC, "POWERPC"},
    {CPU_TYPE_POWERPC64, "POWERPC64"},
    {CPU_TYPE_VEO, "VEO"},
    {0, NULL}
};

/*
    {CPU_SUBTYPE_MASK, "MASK"},
    {CPU_SUBTYPE_LIB64, "LIB64"},
    {CPU_SUBTYPE_MULTIPLE, "MULTIPLE"},
*/

struct string_search STRING_SEARCH_CPUSUBTYPE_VAX [] = {
    {CPU_SUBTYPE_VAX_ALL, "VAX_ALL"},
    {CPU_SUBTYPE_VAX780, "VAX780"},
    {CPU_SUBTYPE_VAX785, "VAX785"},
    {CPU_SUBTYPE_VAX750, "VAX750"},
    {CPU_SUBTYPE_VAX730, "VAX730"},
    {CPU_SUBTYPE_UVAXI, "UVAXI"},
    {CPU_SUBTYPE_UVAXII, "UVAXII"},
    {CPU_SUBTYPE_VAX8200, "VAX8200"},
    {CPU_SUBTYPE_VAX8500, "VAX8500"},
    {CPU_SUBTYPE_VAX8600, "VAX8600"},
    {CPU_SUBTYPE_VAX8650, "VAX8650"},
    {CPU_SUBTYPE_VAX8800, "VAX8800"},
    {CPU_SUBTYPE_UVAXIII, "UVAXIII"},
    {0, NULL}
};

/*
    I have no idea what these are
    {CPU_SUBTYPE_RT_ALL, "RT_ALL"},
    {CPU_SUBTYPE_RT_PC, "RT_PC"},
    {CPU_SUBTYPE_RT_APC, "RT_APC"},
    {CPU_SUBTYPE_RT_135, "RT_135"},
    {CPU_SUBTYPE_MMAX_ALL, "MMAX_ALL"},
    {CPU_SUBTYPE_MMAX_DPC, "MMAX_DPC"},
    {CPU_SUBTYPE_SQT, "SQT"},
    {CPU_SUBTYPE_MMAX_APC_FPU, "MMAX_APC_FPU"},
    {CPU_SUBTYPE_MMAX_APC_FPA, "MMAX_APC_FPA"},
    {CPU_SUBTYPE_MMAX_XPC, "MMAX_XPC"},
*/


struct string_search STRING_SEARCH_CPUSUBTYPE_INTEL [] = {
    {CPU_SUBTYPE_I386_ALL, "I386_ALL"},
    {CPU_SUBTYPE_X86_64_ALL, "X86_64_ALL"},
    {CPU_SUBTYPE_386, "386"},
    {CPU_SUBTYPE_486, "486"},
    {CPU_SUBTYPE_486SX, "486SX"},
    {CPU_SUBTYPE_586, "586"},
    {CPU_SUBTYPE_PENT, "PENT"},
    {CPU_SUBTYPE_PENTPRO, "PENTPRO"},
    {CPU_SUBTYPE_PENTII_M3, "PENTII_M3"},
    {CPU_SUBTYPE_PENTII_M5, "PENTII_M5"},
    {CPU_SUBTYPE_PENTIUM_4, "PENTIUM_4"},
    {CPU_SUBTYPE_INTEL_MODEL_ALL, "INTEL_MODEL_ALL"},
    {0, NULL}
};

struct string_search STRING_SEARCH_CPUSUBTYPE_MIPS [] = {
    {CPU_SUBTYPE_MIPS_ALL, "MIPS_ALL"},
    {CPU_SUBTYPE_MIPS_R2300, "MIPS_R2300"},
    {CPU_SUBTYPE_MIPS_R2600, "MIPS_R2600"},
    {CPU_SUBTYPE_MIPS_R2800, "MIPS_R2800"},
    {CPU_SUBTYPE_MIPS_R2000a, "MIPS_R2000a"},
    {0, NULL}
};


struct string_search STRING_SEARCH_CPUSUBTYPE_MC680x0 [] = {
    {CPU_SUBTYPE_MC680x0_ALL, "MC680x0_ALL"},
    {CPU_SUBTYPE_MC68030, "MC68030"},
    {CPU_SUBTYPE_MC68040, "MC68040"},
    {CPU_SUBTYPE_MC68030_ONLY, "MC68030_ONLY"},
    {0, NULL}
};


struct string_search STRING_SEARCH_CPUSUBTYPE_HPPA [] = {
    {CPU_SUBTYPE_HPPA_ALL, "HPPA_ALL"},
    {CPU_SUBTYPE_HPPA_7100, "HPPA_7100"},
    {CPU_SUBTYPE_HPPA_7100LC, "HPPA_7100LC"},
    {0, NULL}
};


struct string_search STRING_SEARCH_CPUSUBTYPE_ARM [] = {
    {CPU_SUBTYPE_ARM_ALL, "ARM_ALL"},
    {CPU_SUBTYPE_ARM_A500_ARCH, "ARM_A500_ARCH"},
    {CPU_SUBTYPE_ARM_A500, "ARM_A500"},
    {CPU_SUBTYPE_ARM_A440, "ARM_A440"},
    {CPU_SUBTYPE_ARM_M4, "ARM_M4"},
    {CPU_SUBTYPE_ARM_V4T, "ARM_V4T"},
    {CPU_SUBTYPE_ARM_V6, "ARM_V6"},
    {CPU_SUBTYPE_ARM_V5TEJ, "ARM_V5TEJ"},
    {CPU_SUBTYPE_ARM_XSCALE, "ARM_XSCALE"},
    {0, NULL}
};

struct string_search STRING_SEARCH_CPUSUBTYPE_MC88000 [] = {
    {CPU_SUBTYPE_MC88000_ALL, "MC88000_ALL"},
    {CPU_SUBTYPE_MMAX_JPC, "MMAX_JPC"},
    {CPU_SUBTYPE_MC88100, "MC88100"},
    {CPU_SUBTYPE_MC88110, "MC88110"},
    {CPU_SUBTYPE_MC98000_ALL, "MC98000_ALL"},
    {CPU_SUBTYPE_MC98601, "MC98601"},
    {0, NULL}
};

struct string_search STRING_SEARCH_CPUSUBTYPE_I860 [] = {
    {CPU_SUBTYPE_I860_ALL, "I860_ALL"},
    {CPU_SUBTYPE_I860_860, "I860_860"},
    {0, NULL}
};

/*
    {CPU_SUBTYPE_LITTLE_ENDIAN, "LITTLE_ENDIAN"},
    {CPU_SUBTYPE_BIG_ENDIAN, "BIG_ENDIAN"},
*/

struct string_search STRING_SEARCH_CPUSUBTYPE_I860_LITTLE [] = {
    {CPU_SUBTYPE_I860_LITTLE_ALL, "I860_LITTLE_ALL"},
    {CPU_SUBTYPE_I860_LITTLE, "I860_LITTLE"},
    {0, NULL}
};

struct string_search STRING_SEARCH_CPUSUBTYPE_RS6000 [] = {
    {CPU_SUBTYPE_RS6000_ALL, "RS6000_ALL"},
    {CPU_SUBTYPE_RS6000, "RS6000"},
    {0, NULL}
};

struct string_search STRING_SEARCH_CPUSUBTYPE_SPARC [] = {
    {CPU_SUBTYPE_SUN4_ALL, "SUN4_ALL"},
    {CPU_SUBTYPE_SUN4_260, "SUN4_260"},
    {CPU_SUBTYPE_SUN4_110, "SUN4_110"},
    {CPU_SUBTYPE_SPARC_ALL, "SPARC_ALL"},
    {0, NULL}
};


struct string_search STRING_SEARCH_CPUSUBTYPE_POWERPC [] = {
    {CPU_SUBTYPE_POWERPC_ALL, "POWERPC_ALL"},
    {CPU_SUBTYPE_POWERPC_601, "POWERPC_601"},
    {CPU_SUBTYPE_POWERPC_602, "POWERPC_602"},
    {CPU_SUBTYPE_POWERPC_603, "POWERPC_603"},
    {CPU_SUBTYPE_POWERPC_603e, "POWERPC_603e"},
    {CPU_SUBTYPE_POWERPC_603ev, "POWERPC_603ev"},
    {CPU_SUBTYPE_POWERPC_604, "POWERPC_604"},
    {CPU_SUBTYPE_POWERPC_604e, "POWERPC_604e"},
    {CPU_SUBTYPE_POWERPC_620, "POWERPC_620"},
    {CPU_SUBTYPE_POWERPC_750, "POWERPC_750"},
    {CPU_SUBTYPE_POWERPC_7400, "POWERPC_7400"},
    {CPU_SUBTYPE_POWERPC_7450, "POWERPC_7450"},
    {CPU_SUBTYPE_POWERPC_970, "POWERPC_970"},
    {0, NULL}
};


struct string_search STRING_SEARCH_CPUSUBTYPE_VEO [] = {
    {CPU_SUBTYPE_VEO_1, "VEO_1"},
    {CPU_SUBTYPE_VEO_2, "VEO_2"},
    {CPU_SUBTYPE_VEO_3, "VEO_3"},
    {CPU_SUBTYPE_VEO_4, "VEO_4"},
    {CPU_SUBTYPE_VEO_ALL, "VEO_ALL"},
    {0, NULL}
};

struct string_search STRING_SEARCH_FILETYPE [] = {
    {MH_OBJECT, "OBJECT"},
    {MH_EXECUTE, "EXECUTE"},
    {MH_FVMLIB, "FVMLIB"},
    {MH_CORE, "CORE"},
    {MH_PRELOAD, "PRELOAD"},
    {MH_DYLIB, "DYLIB"},
    {MH_DYLINKER, "DYLINKER"},
    {MH_BUNDLE, "BUNDLE"},
    {MH_DYLIB_STUB, "DYLIB_STUB"},
    {MH_DSYM, "DSYM"},
    {MH_KEXT_BUNDLE, "KEXT_BUNDLE"},
    {0, NULL}
};

struct string_search STRING_SEARCH_MACH_HEADER_FLAGS [] = {
    {MH_NOUNDEFS, "NOUNDEFS"},
    {MH_INCRLINK, "INCRLINK"},
    {MH_DYLDLINK, "DYLDLINK"},
    {MH_BINDATLOAD, "BINDATLOAD"},
    {MH_PREBOUND, "PREBOUND"},
    {MH_SPLIT_SEGS, "SPLIT_SEGS"},
    {MH_LAZY_INIT, "LAZY_INIT"},
    {MH_TWOLEVEL, "TWOLEVEL"},
    {MH_FORCE_FLAT, "FORCE_FLAT"},
    {MH_NOMULTIDEFS, "NOMULTIDEFS"},
    {MH_NOFIXPREBINDING, "NOFIXPREBINDING"},
    {MH_PREBINDABLE, "PREBINDABLE"},
    {MH_ALLMODSBOUND, "ALLMODSBOUND"},
    {MH_SUBSECTIONS_VIA_SYMBOLS, "SUBSECTIONS_VIA_SYMBOLS"},
    {MH_CANONICAL, "CANONICAL"},
    {MH_WEAK_DEFINES, "WEAK_DEFINES"},
    {MH_BINDS_TO_WEAK, "BINDS_TO_WEAK"},
    {MH_ALLOW_STACK_EXECUTION, "ALLOW_STACK_EXECUTION"},
    {MH_DEAD_STRIPPABLE_DYLIB, "DEAD_STRIPPABLE_DYLIB"},
    {MH_ROOT_SAFE, "ROOT_SAFE"},
    {MH_SETUID_SAFE, "SETUID_SAFE"},
    {MH_NO_REEXPORTED_DYLIBS, "NO_REEXPORTED_DYLIBS"},
    {MH_PIE, "PIE"},
};

struct string_search STRING_SEARCH_LOAD_COMMAND_CMD [] = {
    {LC_SEGMENT, "SEGMENT"},
    {LC_SYMTAB, "SYMTAB"},
    {LC_SYMSEG, "SYMSEG"},
    {LC_THREAD, "THREAD"},
    {LC_UNIXTHREAD, "UNIXTHREAD"},
    {LC_LOADFVMLIB, "LOADFVMLIB"},
    {LC_IDFVMLIB, "IDFVMLIB"},
    {LC_IDENT, "IDENT"},
    {LC_FVMFILE, "FVMFILE"},
    {LC_PREPAGE, "PREPAGE"},
    {LC_DYSYMTAB, "DYSYMTAB"},
    {LC_LOAD_DYLIB, "LOAD_DYLIB"},
    {LC_ID_DYLIB, "ID_DYLIB"},
    {LC_LOAD_DYLINKER, "LOAD_DYLINKER"},
    {LC_ID_DYLINKER, "ID_DYLINKER"},
    {LC_PREBOUND_DYLIB, "PREBOUND_DYLIB"},
    {LC_ROUTINES, "ROUTINES"},
    {LC_SUB_FRAMEWORK, "SUB_FRAMEWORK"},
    {LC_SUB_UMBRELLA, "SUB_UMBRELLA"},
    {LC_SUB_CLIENT, "SUB_CLIENT"},
    {LC_SUB_LIBRARY, "SUB_LIBRARY"},
    {LC_TWOLEVEL_HINTS, "TWOLEVEL_HINTS"},
    {LC_PREBIND_CKSUM, "PREBIND_CKSUM"},
    {LC_LOAD_WEAK_DYLIB, "LOAD_WEAK_DYLIB"},
    {LC_SEGMENT_64, "SEGMENT_64"},
    {LC_ROUTINES_64, "ROUTINES_64"},
    {LC_UUID, "UUID"},
    {LC_RPATH, "RPATH"},
    {LC_CODE_SIGNATURE, "CODE_SIGNATURE"},
    {LC_SEGMENT_SPLIT_INFO, "SEGMENT_SPLIT_INFO"},
    {LC_REEXPORT_DYLIB, "REEXPORT_DYLIB"},
    {LC_LAZY_LOAD_DYLIB, "LAZY_LOAD_DYLIB"},
    {LC_ENCRYPTION_INFO, "ENCRYPTION_INFO"},
    {LC_DYLD_INFO, "DYLD_INFO"},
    {LC_DYLD_INFO_ONLY, "DYLD_INFO_ONLY"},
    {0, NULL}
};



const char * string_search (struct string_search * haystack, uint32_t needle)
{
    size_t i;
    for (i = 0; haystack[i].string != NULL; i++) {
        if (haystack[i].value == needle)
            return haystack[i].string;
    }

    snprintf(STRING_SEARCH_UNKNOWN_STR, STRING_SEARCH_UNKNOWN_STR_SIZE, "Unknown %x", needle);
    return STRING_SEARCH_UNKNOWN_STR;
}


const char * string_search_flags (struct string_search * haystack, uint32_t needle)
{
    memset(STRING_SEARCH_FLAGS_STR, 0, STRING_SEARCH_FLAGS_STR_SIZE);

    size_t i = 0;
    for (i = 0; haystack[i].string != NULL; i++) {
        if (haystack[i].value & needle) {
            strncat(STRING_SEARCH_FLAGS_STR, haystack[i].string, STRING_SEARCH_FLAGS_STR_SIZE);
            strncat(STRING_SEARCH_FLAGS_STR, " ", STRING_SEARCH_FLAGS_STR_SIZE);
        }
    }

    STRING_SEARCH_FLAGS_STR[STRING_SEARCH_FLAGS_STR_SIZE - 1] = '\0';

    return STRING_SEARCH_FLAGS_STR;
}


const char * string_search_cputype (uint32_t cputype)
{
    return string_search(STRING_SEARCH_CPUTYPE, cputype);
}


const char * string_search_cpusubtype (uint32_t cputype, uint32_t cpusubtype)
{
    struct string_search * haystack = NULL;

    switch (cputype) {
    case CPU_TYPE_VAX :
        haystack = STRING_SEARCH_CPUSUBTYPE_VAX;
        break;
    case CPU_TYPE_I386 :
    case CPU_TYPE_X86_64 :
        haystack = STRING_SEARCH_CPUSUBTYPE_INTEL;
        break;
    case CPU_TYPE_MIPS :
        haystack = STRING_SEARCH_CPUSUBTYPE_MIPS;
        break;
    case CPU_TYPE_MC680x0 :
        haystack = STRING_SEARCH_CPUSUBTYPE_MC680x0;
        break;
    case CPU_TYPE_HPPA :
        haystack = STRING_SEARCH_CPUSUBTYPE_HPPA;
        break;
    case CPU_TYPE_ARM :
        haystack = STRING_SEARCH_CPUSUBTYPE_ARM;
        break;
    case CPU_TYPE_MC88000 :
        haystack = STRING_SEARCH_CPUSUBTYPE_MC88000;
        break;
    case CPU_TYPE_I860 :
        haystack = STRING_SEARCH_CPUSUBTYPE_I860;
        break;
    case CPU_TYPE_I860_LITTLE :
        haystack = STRING_SEARCH_CPUSUBTYPE_I860_LITTLE;
        break;
    case CPU_TYPE_RS6000 :
        haystack = STRING_SEARCH_CPUSUBTYPE_RS6000;
        break;
    case CPU_TYPE_SPARC :
        haystack = STRING_SEARCH_CPUSUBTYPE_SPARC;
        break;
    case CPU_TYPE_POWERPC :
        haystack = STRING_SEARCH_CPUSUBTYPE_POWERPC;
        break;
    case CPU_TYPE_VEO :
        haystack = STRING_SEARCH_CPUSUBTYPE_VEO;
        break;
    }

    if (haystack == NULL)
        return NULL;

    return string_search(haystack, cpusubtype);
}

const char * string_search_filetype (uint32_t filetype)
{
    return string_search(STRING_SEARCH_FILETYPE, filetype);
}

const char * string_search_mach_header_flags (uint32_t flags)
{
    return string_search_flags(STRING_SEARCH_MACH_HEADER_FLAGS, flags);
}

const char * string_search_load_command_cmd (uint32_t cmd)
{
    return string_search(STRING_SEARCH_LOAD_COMMAND_CMD, cmd);
}