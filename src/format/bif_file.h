#ifndef __BIF_FILE_H__
#define __BIF_FILE_H__

typedef struct BifResource
{
	uint32_t id;
	uint32_t offset;
	
	uint32_t file_size;
	uint32_t type;
} BifResource;

typedef struct BifFile
{
	// Counts
	uint32_t  cnt_var_res; // Number of variable resources
	uint32_t  cnt_fix_res; // Number of fixed resources
	
	// Offsets
	uint32_t  pos_var_res; // Byte position of the variable resource table
	
	// Data
	LList    *resources;
} BifFile;

void           bif_file_init                     (BifFile    *bif);
void           bif_file_free                     (BifFile    *bif);
bool           bif_file_read                     (FILE       *f,
                                                  BifFile    *bif);

#endif /* __BIF_FILE_H__ */
