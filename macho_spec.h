/*
* This file is a modified version of several files required in the parsing
* of Mach-O binaries. The original code is from Apple.
*/

/*
 * Copyright (c) 1999-2008 Apple Inc.  All Rights Reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

struct mach_header {
    uint32_t magic;
    uint32_t cputype;    // typedef as int in mach/machine.h
    uint32_t cpusubtype; // typedef as int in mach/machine.h
    uint32_t filetype;
    uint32_t ncmds;
    uint32_t sizeofcmds;
    uint32_t flags;
};

#define MH_MAGIC 0xfeedface
#define MH_CIGAM 0xcdfaedfe

struct mach_header_64 {
    uint32_t magic;
    uint32_t cputype;
    uint32_t cpusubtype;
    uint32_t filetype;
    uint32_t ncmds;
    uint32_t sizeofcmds;
    uint32_t flags;
    uint32_t reserved;
};

#define MH_MAGIC_64 0xfeedfacf
#define MH_CIGAM_64 0xcffaedfe

#define CPU_TYPE_ANY         -1
#define CPU_ARCH_ABI64       0x1000000
#define CPU_TYPE_VAX         1
#define CPU_TYPE_ROMP        2
#define CPU_TYPE_NS32032     4
#define CPU_TYPE_NS32332     5
#define CPU_TYPE_MC680x0     6
#define CPU_TYPE_I386        7
#define CPU_TYPE_X86_64      (CPU_TYPE_I386 | CPU_ARCH_ABI64)
#define CPU_TYPE_MIPS        8
#define CPU_TYPE_NS32532     9
#define CPU_TYPE_HPPA        11
#define CPU_TYPE_ARM         12
#define CPU_TYPE_MC88000     13
#define CPU_TYPE_SPARC       14
#define CPU_TYPE_I860        15
#define CPU_TYPE_I860_LITTLE 16
#define CPU_TYPE_RS6000      17
#define CPU_TYPE_MC98000     18
#define CPU_TYPE_POWERPC     18
#define CPU_TYPE_POWERPC64   (CPU_TYPE_POWERPC | CPU_ARCH_ABI64)
#define CPU_TYPE_VEO         255
#define CPU_SUBTYPE_MASK       0xff000000      /* mask for feature flags */
#define CPU_SUBTYPE_LIB64      0x80000000      /* 64 bit libraries */
#define CPU_SUBTYPE_MULTIPLE    -1
#define CPU_SUBTYPE_VAX_ALL  0
#define CPU_SUBTYPE_VAX780   1
#define CPU_SUBTYPE_VAX785   2
#define CPU_SUBTYPE_VAX750   3
#define CPU_SUBTYPE_VAX730   4
#define CPU_SUBTYPE_UVAXI    5
#define CPU_SUBTYPE_UVAXII   6
#define CPU_SUBTYPE_VAX8200  7
#define CPU_SUBTYPE_VAX8500  8
#define CPU_SUBTYPE_VAX8600  9
#define CPU_SUBTYPE_VAX8650  10
#define CPU_SUBTYPE_VAX8800  11
#define CPU_SUBTYPE_UVAXIII  12
#define CPU_SUBTYPE_RT_ALL   0
#define CPU_SUBTYPE_RT_PC    1
#define CPU_SUBTYPE_RT_APC   2
#define CPU_SUBTYPE_RT_135   3
#define CPU_SUBTYPE_MMAX_ALL 0
#define CPU_SUBTYPE_MMAX_DPC 1
#define CPU_SUBTYPE_SQT      2
#define CPU_SUBTYPE_MMAX_APC_FPU 3
#define CPU_SUBTYPE_MMAX_APC_FPA 4
#define CPU_SUBTYPE_MMAX_XPC     5
#define CPU_SUBTYPE_I386_ALL     3
#define CPU_SUBTYPE_X86_64_ALL  CPU_SUBTYPE_I386_ALL
#define CPU_SUBTYPE_386     3
#define CPU_SUBTYPE_486     4
#define CPU_SUBTYPE_486SX   (4 + 128)
#define CPU_SUBTYPE_586     5
#define CPU_SUBTYPE_INTEL(f, m) ((f) + ((m) << 4))
#define CPU_SUBTYPE_PENT    CPU_SUBTYPE_INTEL(5, 0)
#define CPU_SUBTYPE_PENTPRO CPU_SUBTYPE_INTEL(6, 1)
#define CPU_SUBTYPE_PENTII_M3   CPU_SUBTYPE_INTEL(6, 3)
#define CPU_SUBTYPE_PENTII_M5   CPU_SUBTYPE_INTEL(6, 5)
#define CPU_SUBTYPE_PENTIUM_4   CPU_SUBTYPE_INTEL(10, 0)
#define CPU_SUBTYPE_INTEL_FAMILY(x) ((x) & 15)
#define CPU_SUBTYPE_INTEL_FAMILY_MAX 15
#define CPU_SUBTYPE_INTEL_MODEL(x)  ((x) >> 4)
#define CPU_SUBTYPE_INTEL_MODEL_ALL 0
#define CPU_SUBTYPE_MIPS_ALL     0
#define CPU_SUBTYPE_MIPS_R2300   1
#define CPU_SUBTYPE_MIPS_R2600   2
#define CPU_SUBTYPE_MIPS_R2800   3
#define CPU_SUBTYPE_MIPS_R2000a  4
#define CPU_SUBTYPE_MC680x0_ALL  1
#define CPU_SUBTYPE_MC68030      1
#define CPU_SUBTYPE_MC68040      2
#define CPU_SUBTYPE_MC68030_ONLY 3
#define CPU_SUBTYPE_HPPA_ALL     0
#define CPU_SUBTYPE_HPPA_7100    0
#define CPU_SUBTYPE_HPPA_7100LC  1
#define CPU_SUBTYPE_ARM_ALL       0
#define CPU_SUBTYPE_ARM_A500_ARCH 1
#define CPU_SUBTYPE_ARM_A500      2
#define CPU_SUBTYPE_ARM_A440      3
#define CPU_SUBTYPE_ARM_M4        4
#define CPU_SUBTYPE_ARM_V4T       5
#define CPU_SUBTYPE_ARM_V6        6
#define CPU_SUBTYPE_ARM_V5TEJ     7
#define CPU_SUBTYPE_ARM_XSCALE    8
#define CPU_SUBTYPE_MC88000_ALL   0
#define CPU_SUBTYPE_MMAX_JPC      1
#define CPU_SUBTYPE_MC88100       1
#define CPU_SUBTYPE_MC88110       2
#define CPU_SUBTYPE_MC98000_ALL   0
#define CPU_SUBTYPE_MC98601       1
#define CPU_SUBTYPE_I860_ALL      0
#define CPU_SUBTYPE_I860_860      1
#define CPU_SUBTYPE_LITTLE_ENDIAN 0
#define CPU_SUBTYPE_BIG_ENDIAN    1
#define CPU_SUBTYPE_I860_LITTLE_ALL 0
#define CPU_SUBTYPE_I860_LITTLE     1
#define CPU_SUBTYPE_RS6000_ALL    0
#define CPU_SUBTYPE_RS6000        1
#define CPU_SUBTYPE_SUN4_ALL      0
#define CPU_SUBTYPE_SUN4_260      1
#define CPU_SUBTYPE_SUN4_110      2
#define CPU_SUBTYPE_SPARC_ALL     0
#define CPU_SUBTYPE_POWERPC_ALL   0
#define CPU_SUBTYPE_POWERPC_601   1
#define CPU_SUBTYPE_POWERPC_602   2
#define CPU_SUBTYPE_POWERPC_603   3
#define CPU_SUBTYPE_POWERPC_603e  4
#define CPU_SUBTYPE_POWERPC_603ev 5
#define CPU_SUBTYPE_POWERPC_604   6
#define CPU_SUBTYPE_POWERPC_604e  7
#define CPU_SUBTYPE_POWERPC_620   8
#define CPU_SUBTYPE_POWERPC_750   9
#define CPU_SUBTYPE_POWERPC_7400  10
#define CPU_SUBTYPE_POWERPC_7450  11
#define CPU_SUBTYPE_POWERPC_970   100
#define CPU_SUBTYPE_VEO_1   1
#define CPU_SUBTYPE_VEO_2   2
#define CPU_SUBTYPE_VEO_3   3
#define CPU_SUBTYPE_VEO_4   4
#define CPU_SUBTYPE_VEO_ALL CPU_SUBTYPE_VEO_2

#define MH_OBJECT   0x1     /* relocatable object file */
#define MH_EXECUTE  0x2     /* demand paged executable file */
#define MH_FVMLIB   0x3     /* fixed VM shared library file */
#define MH_CORE     0x4     /* core file */
#define MH_PRELOAD  0x5     /* preloaded executable file */
#define MH_DYLIB    0x6     /* dynamically bound shared library */
#define MH_DYLINKER 0x7     /* dynamic link editor */
#define MH_BUNDLE   0x8     /* dynamically bound bundle file */
#define MH_DYLIB_STUB   0x9     /* shared library stub for static */
                    /*  linking only, no section contents */
#define MH_DSYM     0xa     /* companion file with only debug */
                    /*  sections */
#define MH_KEXT_BUNDLE  0xb     /* x86_64 kexts */

/* Constants for the flags field of the mach_header */
#define MH_NOUNDEFS 0x1     /* the object file has no undefined
                       references */
#define MH_INCRLINK 0x2     /* the object file is the output of an
                       incremental link against a base file
                       and can't be link edited again */
#define MH_DYLDLINK 0x4     /* the object file is input for the
                       dynamic linker and can't be staticly
                       link edited again */
#define MH_BINDATLOAD   0x8     /* the object file's undefined
                       references are bound by the dynamic
                       linker when loaded. */
#define MH_PREBOUND 0x10        /* the file has its dynamic undefined
                       references prebound. */
#define MH_SPLIT_SEGS   0x20        /* the file has its read-only and
                       read-write segments split */
#define MH_LAZY_INIT    0x40        /* the shared library init routine is
                       to be run lazily via catching memory
                       faults to its writeable segments
                       (obsolete) */
#define MH_TWOLEVEL 0x80        /* the image is using two-level name
                       space bindings */
#define MH_FORCE_FLAT   0x100       /* the executable is forcing all images
                       to use flat name space bindings */
#define MH_NOMULTIDEFS  0x200       /* this umbrella guarantees no multiple
                       defintions of symbols in its
                       sub-images so the two-level namespace
                       hints can always be used. */
#define MH_NOFIXPREBINDING 0x400    /* do not have dyld notify the
                       prebinding agent about this
                       executable */
#define MH_PREBINDABLE  0x800           /* the binary is not prebound but can
                       have its prebinding redone. only used
                                           when MH_PREBOUND is not set. */
#define MH_ALLMODSBOUND 0x1000      /* indicates that this binary binds to
                                           all two-level namespace modules of
                       its dependent libraries. only used
                       when MH_PREBINDABLE and MH_TWOLEVEL
                       are both set. */ 
#define MH_SUBSECTIONS_VIA_SYMBOLS 0x2000/* safe to divide up the sections into
                        sub-sections via symbols for dead
                        code stripping */
#define MH_CANONICAL    0x4000      /* the binary has been canonicalized
                       via the unprebind operation */
#define MH_WEAK_DEFINES 0x8000      /* the final linked image contains
                       external weak symbols */
#define MH_BINDS_TO_WEAK 0x10000    /* the final linked image uses
                       weak symbols */

#define MH_ALLOW_STACK_EXECUTION 0x20000/* When this bit is set, all stacks 
                       in the task will be given stack
                       execution privilege.  Only used in
                       MH_EXECUTE filetypes. */
#define MH_DEAD_STRIPPABLE_DYLIB 0x400000 /* Only for use on dylibs.  When
                         linking against a dylib that
                         has this bit set, the static linker
                         will automatically not create a
                         LC_LOAD_DYLIB load command to the
                         dylib if no symbols are being
                         referenced from the dylib. */
#define MH_ROOT_SAFE 0x40000           /* When this bit is set, the binary 
                      declares it is safe for use in
                      processes with uid zero */
                                         
#define MH_SETUID_SAFE 0x80000         /* When this bit is set, the binary 
                      declares it is safe for use in
                      processes when issetugid() is true */

#define MH_NO_REEXPORTED_DYLIBS 0x100000 /* When this bit is set on a dylib, 
                      the static linker does not need to
                      examine dependent dylibs to see
                      if any are re-exported */
#define MH_PIE 0x200000         /* When this bit is set, the OS will
                       load the main executable at a
                       random address.  Only used in
                       MH_EXECUTE filetypes. */

struct load_command {
    uint32_t cmd;       /* type of load command */
    uint32_t cmdsize;   /* total size of command in bytes */
};

#define LC_REQ_DYLD 0x80000000

/* Constants for the cmd field of all load commands, the type */
#define LC_SEGMENT        0x1 /* segment of this file to be mapped */
#define LC_SYMTAB         0x2 /* link-edit stab symbol table info */
#define LC_SYMSEG         0x3 /* link-edit gdb symbol table info (obsolete) */
#define LC_THREAD         0x4 /* thread */
#define LC_UNIXTHREAD     0x5 /* unix thread (includes a stack) */
#define LC_LOADFVMLIB     0x6 /* load a specified fixed VM shared library */
#define LC_IDFVMLIB       0x7 /* fixed VM shared library identification */
#define LC_IDENT          0x8 /* object identification info (obsolete) */
#define LC_FVMFILE        0x9 /* fixed VM file inclusion (internal use) */
#define LC_PREPAGE        0xa     /* prepage command (internal use) */
#define LC_DYSYMTAB       0xb /* dynamic link-edit symbol table info */
#define LC_LOAD_DYLIB     0xc /* load a dynamically linked shared library */
#define LC_ID_DYLIB       0xd /* dynamically linked shared lib ident */
#define LC_LOAD_DYLINKER  0xe    /* load a dynamic linker */
#define LC_ID_DYLINKER    0xf /* dynamic linker identification */
#define LC_PREBOUND_DYLIB 0x10  /* modules prebound for a dynamically */
                /*  linked shared library */
#define LC_ROUTINES       0x11    /* image routines */
#define LC_SUB_FRAMEWORK  0x12   /* sub framework */
#define LC_SUB_UMBRELLA   0x13    /* sub umbrella */
#define LC_SUB_CLIENT     0x14    /* sub client */
#define LC_SUB_LIBRARY    0x15    /* sub library */
#define LC_TWOLEVEL_HINTS 0x16  /* two-level namespace lookup hints */
#define LC_PREBIND_CKSUM  0x17  /* prebind checksum */

/*
 * load a dynamically linked shared library that is allowed to be missing
 * (all symbols are weak imported).
 */
#define LC_LOAD_WEAK_DYLIB (0x18 | LC_REQ_DYLD)

#define LC_SEGMENT_64         0x19    /* 64-bit segment of this file to be mapped */
#define LC_ROUTINES_64        0x1a    /* 64-bit image routines */
#define LC_UUID               0x1b    /* the uuid */
#define LC_RPATH              (0x1c | LC_REQ_DYLD)    /* runpath additions */
#define LC_CODE_SIGNATURE     0x1d  /* local of code signature */
#define LC_SEGMENT_SPLIT_INFO 0x1e /* local of info to split segments */
#define LC_REEXPORT_DYLIB     (0x1f | LC_REQ_DYLD) /* load and re-export dylib */
#define LC_LAZY_LOAD_DYLIB    0x20 /* delay load of dylib until first use */
#define LC_ENCRYPTION_INFO    0x21 /* encrypted segment information */
#define LC_DYLD_INFO          0x22    /* compressed dyld information */
#define LC_DYLD_INFO_ONLY     (0x22|LC_REQ_DYLD)    /* compressed dyld information only */

union lc_str {
    uint32_t    offset; /* offset to the string */
#ifndef __LP64__
    char        *ptr;   /* pointer to the string */
#endif 
};

struct segment_command { /* for 32-bit architectures */
    uint32_t cmd;        /* LC_SEGMENT */
    uint32_t cmdsize;    /* includes sizeof section structs */
    char     segname[16];    /* segment name */
    uint32_t vmaddr;     /* memory address of this segment */
    uint32_t vmsize;     /* memory size of this segment */
    uint32_t fileoff;    /* file offset of this segment */
    uint32_t filesize;   /* amount to map from the file */
    uint32_t maxprot;    /* maximum VM protection */
    uint32_t initprot;   /* initial VM protection */
    uint32_t nsects;     /* number of sections in segment */
    uint32_t flags;      /* flags */
};

struct segment_command_64 { /* for 64-bit architectures */
    uint32_t   cmd;        /* LC_SEGMENT_64 */
    uint32_t   cmdsize;    /* includes sizeof section_64 structs */
    char       segname[16];    /* segment name */
    uint64_t   vmaddr;     /* memory address of this segment */
    uint64_t   vmsize;     /* memory size of this segment */
    uint64_t   fileoff;    /* file offset of this segment */
    uint64_t   filesize;   /* amount to map from the file */
    uint32_t   maxprot;    /* maximum VM protection */
    uint32_t   initprot;   /* initial VM protection */
    uint32_t   nsects;     /* number of sections in segment */
    uint32_t   flags;      /* flags */
};

#define SG_HIGHVM   0x1 /* the file contents for this segment is for
                   the high part of the VM space, the low part
                   is zero filled (for stacks in core files) */
#define SG_FVMLIB   0x2 /* this segment is the VM that is allocated by
                   a fixed VM library, for overlap checking in
                   the link editor */
#define SG_NORELOC  0x4 /* this segment has nothing that was relocated
                   in it and nothing relocated to it, that is
                   it maybe safely replaced without relocation*/
#define SG_PROTECTED_VERSION_1  0x8 /* This segment is protected.  If the
                       segment starts at file offset 0, the
                       first page of the segment is not
                       protected.  All other pages of the
                       segment are protected. */


struct section { /* for 32-bit architectures */
    char        sectname[16];   /* name of this section */
    char        segname[16];    /* segment this section goes in */
    uint32_t    addr;       /* memory address of this section */
    uint32_t    size;       /* size in bytes of this section */
    uint32_t    offset;     /* file offset of this section */
    uint32_t    align;      /* section alignment (power of 2) */
    uint32_t    reloff;     /* file offset of relocation entries */
    uint32_t    nreloc;     /* number of relocation entries */
    uint32_t    flags;      /* flags (section type and attributes)*/
    uint32_t    reserved1;  /* reserved (for offset or index) */
    uint32_t    reserved2;  /* reserved (for count or sizeof) */
};

struct section_64 { /* for 64-bit architectures */
    char        sectname[16];   /* name of this section */
    char        segname[16];    /* segment this section goes in */
    uint64_t    addr;       /* memory address of this section */
    uint64_t    size;       /* size in bytes of this section */
    uint32_t    offset;     /* file offset of this section */
    uint32_t    align;      /* section alignment (power of 2) */
    uint32_t    reloff;     /* file offset of relocation entries */
    uint32_t    nreloc;     /* number of relocation entries */
    uint32_t    flags;      /* flags (section type and attributes)*/
    uint32_t    reserved1;  /* reserved (for offset or index) */
    uint32_t    reserved2;  /* reserved (for count or sizeof) */
    uint32_t    reserved3;  /* reserved */
};

#define SECTION_TYPE                 0x000000ff /* 256 section types */
#define SECTION_ATTRIBUTES           0xffffff00 /*  24 section attributes */
#define S_NON_LAZY_SYMBOL_POINTERS   0x6 /* section with only non-lazy symbol pointers */
#define S_LAZY_SYMBOL_POINTERS       0x7 /* section with only lazy symbol pointers */
#define S_SYMBOL_STUBS               0x8 /* section with only symbol stubs, byte size of stub in the reserved2 field */
#define S_MOD_INIT_FUNC_POINTERS     0x9 /* section with only function pointers for initialization*/
#define S_MOD_TERM_FUNC_POINTERS     0xa /* section with only function pointers for termination */
#define S_COALESCED                  0xb /* section contains symbols that are to be coalesced */
#define S_GB_ZEROFILL                0xc /* zero fill on demand section (that can be larger than 4 gigabytes) */
#define S_INTERPOSING                0xd /* section with only pairs of function pointers for interposing */
#define S_16BYTE_LITERALS            0xe /* section with only 16 byte literals */
#define S_DTRACE_DOF                 0xf /* section contains DTrace Object Format */
#define S_LAZY_DYLIB_SYMBOL_POINTERS 0x10 /* section with only lazy symbol pointers to lazy loaded dylibs */

#define SECTION_ATTRIBUTES_USR     0xff000000 /* User setable attributes */
#define S_ATTR_PURE_INSTRUCTIONS   0x80000000 /* section contains only true machine instructions */
#define S_ATTR_NO_TOC              0x40000000 /* section contains coalesced symbols that are not to be in a ranlib table of contents */
#define S_ATTR_STRIP_STATIC_SYMS   0x20000000 /* ok to strip static symbols in this section in files with the MH_DYLDLINK flag */
#define S_ATTR_NO_DEAD_STRIP       0x10000000 /* no dead stripping */
#define S_ATTR_LIVE_SUPPORT        0x08000000 /* blocks are live if they reference live blocks */
#define S_ATTR_SELF_MODIFYING_CODE 0x04000000   /* Used with i386 code stubs written on by dyld */

#define S_ATTR_DEBUG               0x02000000 /* a debug section */
#define SECTION_ATTRIBUTES_SYS     0x00ffff00 /* system setable attributes */
#define S_ATTR_SOME_INSTRUCTIONS   0x00000400 /* section contains some machine instructions */
#define S_ATTR_EXT_RELOC           0x00000200 /* section has external relocation entries */
#define S_ATTR_LOC_RELOC           0x00000100 /* section has local relocation entries */

#define SEG_PAGEZERO    "__PAGEZERO"    /* the pagezero segment which has no protections and catches NULL references for MH_EXECUTE files */
#define SEG_TEXT    "__TEXT"    /* the tradition UNIX text segment */
#define SECT_TEXT   "__text"    /* the real text part of the text section no headers, and no padding */
#define SECT_FVMLIB_INIT0 "__fvmlib_init0"  /* the fvmlib initialization section */
#define SECT_FVMLIB_INIT1 "__fvmlib_init1"  /* the section following the fvmlib initialization section */
#define SEG_DATA    "__DATA"    /* the tradition UNIX data segment the real initialized data section no padding, no bss overlap */
#define SECT_BSS    "__bss"     /* the real uninitialized data section no padding */
#define SECT_COMMON "__common"  /* the section common symbols are allocated in by the link editor */
#define SEG_OBJC    "__OBJC"    /* objective-C runtime segment */
#define SECT_OBJC_SYMBOLS "__symbol_table"  /* symbol table */
#define SECT_OBJC_MODULES "__module_info"   /* module information */
#define SECT_OBJC_STRINGS "__selector_strs" /* string table */
#define SECT_OBJC_REFS "__selector_refs"    /* string table */
#define SEG_ICON     "__ICON"   /* the icon segment */
#define SECT_ICON_HEADER "__header" /* the icon headers */
#define SECT_ICON_TIFF   "__tiff"   /* the icons in tiff format */
#define SEG_LINKEDIT    "__LINKEDIT"    /* the segment containing all structs */
                    /* created and maintained by the link */
                    /* editor.  Created with -seglinkedit */
                    /* option to ld(1) for MH_EXECUTE and */
                    /* FVMLIB file types only */
#define SEG_UNIXSTACK   "__UNIXSTACK"   /* the unix stack segment */
#define SEG_IMPORT  "__IMPORT"  /* the segment for the self (dyld) modifing code stubs that has read, write and execute permissions */


struct fvmlib {
    union lc_str    name;       /* library's target pathname */
    uint32_t    minor_version;  /* library's minor version number */
    uint32_t    header_addr;    /* library's header address */
};

struct fvmlib_command {
    uint32_t    cmd;        /* LC_IDFVMLIB or LC_LOADFVMLIB */
    uint32_t    cmdsize;    /* includes pathname string */
    struct fvmlib   fvmlib;     /* the library identification */
};

struct dylib {
    union lc_str  name;         /* library's path name */
    uint32_t timestamp;         /* library's build time stamp */
    uint32_t current_version;       /* library's current version number */
    uint32_t compatibility_version; /* library's compatibility vers number*/
};

struct dylib_command {
    uint32_t    cmd;        /* LC_ID_DYLIB, LC_LOAD_{,WEAK_}DYLIB,
                       LC_REEXPORT_DYLIB */
    uint32_t    cmdsize;    /* includes pathname string */
    struct dylib    dylib;      /* the library identification */
};

struct sub_framework_command {
    uint32_t    cmd;        /* LC_SUB_FRAMEWORK */
    uint32_t    cmdsize;    /* includes umbrella string */
    union lc_str    umbrella;   /* the umbrella framework name */
};

struct sub_client_command {
    uint32_t    cmd;        /* LC_SUB_CLIENT */
    uint32_t    cmdsize;    /* includes client string */
    union lc_str    client;     /* the client name */
};

struct sub_umbrella_command {
    uint32_t    cmd;        /* LC_SUB_UMBRELLA */
    uint32_t    cmdsize;    /* includes sub_umbrella string */
    union lc_str    sub_umbrella;   /* the sub_umbrella framework name */
};

struct sub_library_command {
    uint32_t    cmd;        /* LC_SUB_LIBRARY */
    uint32_t    cmdsize;    /* includes sub_library string */
    union lc_str    sub_library;    /* the sub_library name */
};

struct prebound_dylib_command {
    uint32_t    cmd;        /* LC_PREBOUND_DYLIB */
    uint32_t    cmdsize;    /* includes strings */
    union lc_str    name;       /* library's path name */
    uint32_t    nmodules;   /* number of modules in library */
    union lc_str    linked_modules; /* bit vector of linked modules */
};

struct dylinker_command {
    uint32_t    cmd;        /* LC_ID_DYLINKER or LC_LOAD_DYLINKER */
    uint32_t    cmdsize;    /* includes pathname string */
    union lc_str    name;       /* dynamic linker's path name */
};

struct thread_command {
    uint32_t    cmd;        /* LC_THREAD or  LC_UNIXTHREAD */
    uint32_t    cmdsize;    /* total size of this command */
    /* uint32_t flavor         flavor of thread state */
    /* uint32_t count          count of longs in thread state */
    /* struct XXX_thread_state state   thread state for this flavor */
    /* ... */
};

struct routines_command { /* for 32-bit architectures */
    uint32_t    cmd;        /* LC_ROUTINES */
    uint32_t    cmdsize;    /* total size of this command */
    uint32_t    init_address;   /* address of initialization routine */
    uint32_t    init_module;    /* index into the module table that */
                        /*  the init routine is defined in */
    uint32_t    reserved1;
    uint32_t    reserved2;
    uint32_t    reserved3;
    uint32_t    reserved4;
    uint32_t    reserved5;
    uint32_t    reserved6;
};

/*
 * The 64-bit routines command.  Same use as above.
 */
struct routines_command_64 { /* for 64-bit architectures */
    uint32_t    cmd;        /* LC_ROUTINES_64 */
    uint32_t    cmdsize;    /* total size of this command */
    uint64_t    init_address;   /* address of initialization routine */
    uint64_t    init_module;    /* index into the module table that */
                    /*  the init routine is defined in */
    uint64_t    reserved1;
    uint64_t    reserved2;
    uint64_t    reserved3;
    uint64_t    reserved4;
    uint64_t    reserved5;
    uint64_t    reserved6;
};

struct symtab_command {
    uint32_t    cmd;        /* LC_SYMTAB */
    uint32_t    cmdsize;    /* sizeof(struct symtab_command) */
    uint32_t    symoff;     /* symbol table offset */
    uint32_t    nsyms;      /* number of symbol table entries */
    uint32_t    stroff;     /* string table offset */
    uint32_t    strsize;    /* string table size in bytes */
};

struct dysymtab_command {
    uint32_t cmd;       /* LC_DYSYMTAB */
    uint32_t cmdsize;   /* sizeof(struct dysymtab_command) */

    uint32_t ilocalsym; /* index to local symbols */
    uint32_t nlocalsym; /* number of local symbols */

    uint32_t iextdefsym;/* index to externally defined symbols */
    uint32_t nextdefsym;/* number of externally defined symbols */

    uint32_t iundefsym; /* index to undefined symbols */
    uint32_t nundefsym; /* number of undefined symbols */

    uint32_t tocoff;    /* file offset to table of contents */
    uint32_t ntoc;  /* number of entries in table of contents */

    uint32_t modtaboff; /* file offset to module table */
    uint32_t nmodtab;   /* number of module table entries */

    uint32_t extrefsymoff;  /* offset to referenced symbol table */
    uint32_t nextrefsyms;   /* number of referenced symbol table entries */

    uint32_t indirectsymoff; /* file offset to the indirect symbol table */
    uint32_t nindirectsyms;  /* number of indirect symbol table entries */

    uint32_t extreloff; /* offset to external relocation entries */
    uint32_t nextrel;   /* number of external relocation entries */

    uint32_t locreloff; /* offset to local relocation entries */
    uint32_t nlocrel;   /* number of local relocation entries */
};

#define INDIRECT_SYMBOL_LOCAL   0x80000000
#define INDIRECT_SYMBOL_ABS     0x40000000

struct dylib_table_of_contents {
    uint32_t symbol_index;  /* the defined external symbol (index into the symbol table) */
    uint32_t module_index;  /* index into the module table this symbol is defined in */
};

struct dylib_module {
    uint32_t module_name;   /* the module name (index into string table) */
    uint32_t iextdefsym;    /* index into externally defined symbols */
    uint32_t nextdefsym;    /* number of externally defined symbols */
    uint32_t irefsym;       /* index into reference symbol table */
    uint32_t nrefsym;       /* number of reference symbol table entries */
    uint32_t ilocalsym;     /* index into symbols for local symbols */
    uint32_t nlocalsym;     /* number of local symbols */
    uint32_t iextrel;       /* index into external relocation entries */
    uint32_t nextrel;       /* number of external relocation entries */
    uint32_t iinit_iterm;   /* low 16 bits are the index into the init section, high 16 bits are the index into the term section */
    uint32_t ninit_nterm;   /* low 16 bits are the number of init section entries, high 16 bits are the number of term section entries */
    uint32_t objc_module_info_addr;  /* for this module address of the start of the (__OBJC,__module_info) section */
    uint32_t objc_module_info_size;  /* for this module size of the (__OBJC,__module_info) section */
};

struct dylib_module_64 {
    uint32_t module_name;   /* the module name (index into string table) */
    uint32_t iextdefsym;    /* index into externally defined symbols */
    uint32_t nextdefsym;    /* number of externally defined symbols */
    uint32_t irefsym;       /* index into reference symbol table */
    uint32_t nrefsym;       /* number of reference symbol table entries */
    uint32_t ilocalsym;     /* index into symbols for local symbols */
    uint32_t nlocalsym;     /* number of local symbols */
    uint32_t iextrel;       /* index into external relocation entries */
    uint32_t nextrel;       /* number of external relocation entries */
    uint32_t iinit_iterm;   /* low 16 bits are the index into the init section, high 16 bits are the index into the term section */
    uint32_t ninit_nterm;   /* low 16 bits are the number of init section entries, high 16 bits are the number of term section entries */
    uint32_t objc_module_info_size;  /* for this module size of the (__OBJC,__module_info) section */
    uint64_t objc_module_info_addr;  /* for this module address of the start of the (__OBJC,__module_info) section */
};

struct dylib_reference {
    uint32_t isym:24,       /* index into the symbol table */
              flags:8;  /* flags to indicate the type of reference */
};

struct twolevel_hints_command {
    uint32_t cmd;   /* LC_TWOLEVEL_HINTS */
    uint32_t cmdsize;   /* sizeof(struct twolevel_hints_command) */
    uint32_t offset;    /* offset to the hint table */
    uint32_t nhints;    /* number of hints in the hint table */
};

struct twolevel_hint {
    uint32_t 
    isub_image:8,   /* index into the sub images */
    itoc:24;    /* index into the table of contents */
};

struct prebind_cksum_command {
    uint32_t cmd;   /* LC_PREBIND_CKSUM */
    uint32_t cmdsize;   /* sizeof(struct prebind_cksum_command) */
    uint32_t cksum; /* the check sum or zero */
};

struct uuid_command {
    uint32_t    cmd;        /* LC_UUID */
    uint32_t    cmdsize;    /* sizeof(struct uuid_command) */
    uint8_t uuid[16];   /* the 128-bit uuid */
};

struct rpath_command {
    uint32_t     cmd;       /* LC_RPATH */
    uint32_t     cmdsize;   /* includes string */
    union lc_str path;      /* path to add to run path */
};

struct linkedit_data_command {
    uint32_t    cmd;        /* LC_CODE_SIGNATURE or LC_SEGMENT_SPLIT_INFO */
    uint32_t    cmdsize;    /* sizeof(struct linkedit_data_command) */
    uint32_t    dataoff;    /* file offset of data in __LINKEDIT segment */
    uint32_t    datasize;   /* file size of data in __LINKEDIT segment  */
};

struct encryption_info_command {
    uint32_t cmd;        /* LC_ENCRYPTION_INFO */
    uint32_t cmdsize;    /* sizeof(struct encryption_info_command) */
    uint32_t cryptoff;   /* file offset of encrypted range */
    uint32_t cryptsize;  /* file size of encrypted range */
    uint32_t cryptid;    /* which enryption system, 0 means not-encrypted yet */
};

struct dyld_info_command {
    uint32_t   cmd;      /* LC_DYLD_INFO or LC_DYLD_INFO_ONLY */
    uint32_t   cmdsize;  /* sizeof(struct dyld_info_command) */
    uint32_t   rebase_off;  /* file offset to rebase info  */
    uint32_t   rebase_size; /* size of rebase info   */
    uint32_t   bind_off;    /* file offset to binding info   */
    uint32_t   bind_size;   /* size of binding info  */
    uint32_t   weak_bind_off;   /* file offset to weak binding info   */
    uint32_t   weak_bind_size;  /* size of weak binding info  */
    uint32_t   lazy_bind_off;   /* file offset to lazy binding info */
    uint32_t   lazy_bind_size;  /* size of lazy binding infs */
    uint32_t   export_off;  /* file offset to lazy binding info */
    uint32_t   export_size; /* size of lazy binding infs */
};

#define REBASE_TYPE_POINTER         1
#define REBASE_TYPE_TEXT_ABSOLUTE32 2
#define REBASE_TYPE_TEXT_PCREL32    3

#define REBASE_OPCODE_MASK                          0xF0
#define REBASE_IMMEDIATE_MASK                       0x0F
#define REBASE_OPCODE_DONE                          0x00
#define REBASE_OPCODE_SET_TYPE_IMM                  0x10
#define REBASE_OPCODE_SET_SEGMENT_AND_OFFSET_ULEB   0x20
#define REBASE_OPCODE_ADD_ADDR_ULEB                 0x30
#define REBASE_OPCODE_ADD_ADDR_IMM_SCALED           0x40
#define REBASE_OPCODE_DO_REBASE_IMM_TIMES           0x50
#define REBASE_OPCODE_DO_REBASE_ULEB_TIMES          0x60
#define REBASE_OPCODE_DO_REBASE_ADD_ADDR_ULEB       0x70
#define REBASE_OPCODE_DO_REBASE_ULEB_TIMES_SKIPPING_ULEB 0x80

#define BIND_TYPE_POINTER                     1
#define BIND_TYPE_TEXT_ABSOLUTE32             2
#define BIND_TYPE_TEXT_PCREL32                3
#define BIND_SPECIAL_DYLIB_SELF               0
#define BIND_SPECIAL_DYLIB_MAIN_EXECUTABLE    -1
#define BIND_SPECIAL_DYLIB_FLAT_LOOKUP        -2
#define BIND_SYMBOL_FLAGS_WEAK_IMPORT         0x1
#define BIND_SYMBOL_FLAGS_NON_WEAK_DEFINITION 0x8
#define BIND_OPCODE_MASK                    0xF0
#define BIND_IMMEDIATE_MASK                 0x0F
#define BIND_OPCODE_DONE                    0x00
#define BIND_OPCODE_SET_DYLIB_ORDINAL_IMM           0x10
#define BIND_OPCODE_SET_DYLIB_ORDINAL_ULEB          0x20
#define BIND_OPCODE_SET_DYLIB_SPECIAL_IMM           0x30
#define BIND_OPCODE_SET_SYMBOL_TRAILING_FLAGS_IMM   0x40
#define BIND_OPCODE_SET_TYPE_IMM                0x50
#define BIND_OPCODE_SET_ADDEND_SLEB             0x60
#define BIND_OPCODE_SET_SEGMENT_AND_OFFSET_ULEB 0x70
#define BIND_OPCODE_ADD_ADDR_ULEB               0x80
#define BIND_OPCODE_DO_BIND                     0x90
#define BIND_OPCODE_DO_BIND_ADD_ADDR_ULEB       0xA0
#define BIND_OPCODE_DO_BIND_ADD_ADDR_IMM_SCALED 0xB0
#define BIND_OPCODE_DO_BIND_ULEB_TIMES_SKIPPING_ULEB 0xC0

#define EXPORT_SYMBOL_FLAGS_KIND_MASK           0x03
#define EXPORT_SYMBOL_FLAGS_KIND_REGULAR        0x00
#define EXPORT_SYMBOL_FLAGS_KIND_THREAD_LOCAL   0x01
#define EXPORT_SYMBOL_FLAGS_WEAK_DEFINITION     0x04
#define EXPORT_SYMBOL_FLAGS_INDIRECT_DEFINITION 0x08
#define EXPORT_SYMBOL_FLAGS_HAS_SPECIALIZATIONS 0x10


struct symseg_command {
    uint32_t    cmd;     /* LC_SYMSEG */
    uint32_t    cmdsize; /* sizeof(struct symseg_command) */
    uint32_t    offset;  /* symbol segment offset */
    uint32_t    size;    /* symbol segment size in bytes */
};

struct ident_command {
    uint32_t cmd;     /* LC_IDENT */
    uint32_t cmdsize; /* strings that follow this command */
};

struct fvmfile_command {
    uint32_t cmd;         /* LC_FVMFILE */
    uint32_t cmdsize;     /* includes pathname string */
    union lc_str name;    /* files pathname */
    uint32_t header_addr; /* files virtual address */
};

#define FAT_MAGIC   0xcafebabe
#define FAT_CIGAM   0xbebafeca  /* NXSwapLong(FAT_MAGIC) */

struct fat_header {
    uint32_t magic;      /* FAT_MAGIC */
    uint32_t nfat_arch;  /* number of structs that follow */
};

struct fat_arch {
    uint32_t cputype;    /* cpu specifier (int) */
    uint32_t cpusubtype; /* machine specifier (int) */
    uint32_t offset;     /* file offset to this object file */
    uint32_t size;       /* size of this object file */
    uint32_t align;      /* alignment as a power of 2 */
};

#define VM_PROT_NONE       0x00
#define VM_PROT_READ       0x01
#define VM_PROT_WRITE      0x02
#define VM_PROT_EXECUTE    0x04
#define VM_PROT_DEFAULT    (VM_PROT_READ|VM_PROT_WRITE)
#define VM_PROT_ALL        (VM_PROT_READ | VM_PROT_WRITE | VM_PROT_EXECUTE)
#define VM_PROT_NO_CHANGE  0x08
#define VM_PROT_COPY       0x10
#define VM_PROT_WANTS_COPY 0x10