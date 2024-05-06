#include "display_utils.h"
unsigned char* init_mem_base(){
  unsigned char *mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
  if (mem_base == NULL)
    fprintf(stderr, "Error: Unable to map physical address\n");
    exit(1);
  return mem_base;
}
unsigned char* init_parlcd_mem_base(){
  unsigned char *parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
  if (parlcd_mem_base == NULL)
    fprintf(stderr, "Error: Unable to map physical address\n");
    exit(1);
  return parlcd_mem_base;
}