
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "macho_spec.h"
#include "macho_field_string.h"

struct _buf {
    size_t size;
    uint8_t * buf;
};


struct fat_header * mach_fat_header           (struct _buf * buf);
struct fat_arch *   mach_fat_arch             (struct _buf * buf, size_t i);
uint32_t            mach_fat_header_endian_32 (struct fat_header * fh, uint32_t v);
uint32_t            mach_endian_32            (struct mach_header * mh, uint32_t v);


struct fat_header * mach_fat_header (struct _buf * buf)
{
    return (struct fat_header *) buf->buf;
}


struct fat_arch * mach_fat_arch (struct _buf * buf, size_t i)
{
    size_t offset = sizeof(struct fat_header) + (sizeof(struct fat_arch) * i);
    return (struct fat_arch *) &(buf->buf[offset]);
}

struct mach_header * mach_mach_header (struct _buf * buf)
{
    return (struct mach_header *) buf->buf;
}

struct load_command * mach_load_command (struct _buf * buf, size_t i)
{
    struct mach_header * mh = mach_mach_header(buf);
    size_t offset           = sizeof(struct mach_header);
    size_t j = 0;
    for (j = 0; j < i; j++) {
        struct load_command * lc = (struct load_command *) &(buf->buf[offset]);
        offset += mach_endian_32(mh, lc->cmdsize);
    }
    return (struct load_command *) &(buf->buf[offset]);
}


uint32_t mach_fat_header_endian_32 (struct fat_header * fh, uint32_t v)
{
    if (fh->magic == FAT_CIGAM)
        return (v >> 24)
               | ((v >> 8) & 0xff00)
               | ((v << 8) & 0xff0000)
               | ((v << 24));
    return v;
}

uint32_t mach_endian_32 (struct mach_header * mh, uint32_t v)
{
    if (mh->magic == MH_CIGAM)
        return (v >> 24)
               | ((v >> 8) & 0xff00)
               | ((v << 8) & 0xff0000)
               | ((v << 24));
    return v;
}

/*
* MACH FAT HEADER FIELDS
*/


uint32_t mach_fat_header_nfat_arch (struct _buf * buf)
{
    struct fat_header * fh = mach_fat_header(buf);

    return mach_fat_header_endian_32(fh, fh->nfat_arch);
}

/*
* STRUCT FIELD GETTERS
*/

#define MACH_FAT_ARCH_FIELD(XX) \
uint32_t mach_fat_arch_##XX (struct _buf * buf, size_t i) \
{ \
    struct fat_header * fh = mach_fat_header(buf); \
    struct fat_arch * fa = mach_fat_arch(buf, i); \
    return mach_fat_header_endian_32(fh, fa->XX); \
}

MACH_FAT_ARCH_FIELD(cputype)
MACH_FAT_ARCH_FIELD(cpusubtype)
MACH_FAT_ARCH_FIELD(offset)
MACH_FAT_ARCH_FIELD(size)
MACH_FAT_ARCH_FIELD(align)

#define MACH_MACH_HEADER_FIELD(XX) \
uint32_t mach_mach_header_##XX (struct _buf * buf) \
{ \
    struct mach_header * mh = mach_mach_header(buf); \
    return mach_endian_32(mh, mh->XX); \
}

MACH_MACH_HEADER_FIELD(cputype)
MACH_MACH_HEADER_FIELD(cpusubtype)
MACH_MACH_HEADER_FIELD(filetype)
MACH_MACH_HEADER_FIELD(ncmds)
MACH_MACH_HEADER_FIELD(sizeofcmds)
MACH_MACH_HEADER_FIELD(flags)

#define MACH_LOAD_COMMAND_FIELD(XX) \
uint32_t mach_load_command_##XX (struct mach_header * mh, struct load_command * lc) \
{ \
    return mach_endian_32(mh, lc->XX); \
}

MACH_LOAD_COMMAND_FIELD(cmd)
MACH_LOAD_COMMAND_FIELD(cmdsize)

/*
* PARSERS
*/

void mach_mach_header_parse (struct _buf * buf)
{
    struct mach_header * mh = mach_mach_header(buf);

    if (mh->magic == MH_MAGIC)
        printf(" MACH HEADER\n");
    else if (mh->magic == MH_CIGAM)
        printf(" MACH HEADER REVERSE\n");
    else
        return;

    printf("  cputype    %s\n", string_search_cputype(mach_mach_header_cputype(buf)));
    printf("  cpusubtype %s\n", 
           string_search_cpusubtype(mach_mach_header_cputype(buf), mach_mach_header_cpusubtype(buf)));
    printf("  filetype   %s\n", string_search_filetype(mach_mach_header_filetype(buf)));
    printf("  ncmds      %x\n", mach_mach_header_ncmds(buf));
    printf("  sizeofcmds %x\n", mach_mach_header_sizeofcmds(buf));
    printf("  flags      %s\n", string_search_mach_header_flags(mach_mach_header_flags(buf)));

    size_t i;
    for (i = 0; i < mach_mach_header_ncmds(buf); i++) {
        struct load_command * lc = mach_load_command(buf, i);
        printf("   load_command %s\n", string_search_load_command_cmd(mach_load_command_cmd(mh, lc)));
    }
}

void mach_fat_parse (struct _buf * buf)
{
    struct fat_header * fh = mach_fat_header(buf);

    if (fh->magic == FAT_MAGIC)
        printf("MACH FAT\n");
    else if (fh->magic == FAT_CIGAM)
        printf("MACH FAT REVERSE ENDIAN\n");
    else
        return;

    printf("nfat_arch: %d\n", mach_fat_header_nfat_arch(buf));

    size_t i;
    for (i = 0; i < mach_fat_header_nfat_arch(buf); i++) {
        printf("-------------------------------------------------\n");
        printf("fat_arch cputype    %s\n", string_search_cputype(mach_fat_arch_cputype(buf, i)));
        printf("fat_arch cpusubtype %s\n",
               string_search_cpusubtype(mach_fat_arch_cputype(buf, i), mach_fat_arch_cpusubtype(buf, i)));
        printf("fat_arch offset     %x\n", mach_fat_arch_offset(buf, i));
        printf("fat_arch size       %x\n", mach_fat_arch_size(buf, i));
        printf("fat_arch align      %x\n", mach_fat_arch_align(buf, i));

        struct _buf buf2;
        buf2.size = mach_fat_arch_size(buf, i);
        buf2.buf  = &(buf->buf[mach_fat_arch_offset(buf, i)]);

        mach_mach_header_parse(&buf2);
    }
}


int main (int argc, char * argv[])
{
    size_t filesize;

    FILE * fh = fopen(argv[1], "rb");

    fseek(fh, 0, SEEK_END);
    filesize = ftell(fh);
    fseek(fh, 0, SEEK_SET);

    struct _buf buf;
    buf.buf = (uint8_t *) malloc(filesize);
    buf.size = filesize;
    fread(buf.buf, 1, filesize, fh);

    fclose(fh);

    printf("parsing\n");

    mach_fat_parse(&buf);

    free(buf.buf);

    return 0;
}