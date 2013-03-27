#ifndef macho_field_string_HEADER
#define macho_field_string_HEADER

#include <stdint.h>

const char * string_search_cputype           (uint32_t cputype);
const char * string_search_cpusubtype        (uint32_t cputype, uint32_t cpusubtype);
const char * string_search_filetype          (uint32_t filetype);
const char * string_search_mach_header_flags (uint32_t flags);
const char * string_search_load_command_cmd  (uint32_t cmd);
const char * string_search_vm_prot           (uint32_t prot);
const char * string_search_segment_flags     (uint32_t flags);

#endif