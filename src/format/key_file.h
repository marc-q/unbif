#ifndef __KEY_FILE_H__
#define __KEY_FILE_H__

typedef struct KeyResource
{
	char     name[17];
	uint16_t type;
	uint32_t id;
} KeyResource;

typedef struct KeyFile
{
	// Counts
	uint32_t cnt_bif;     // Number of BIF files
	uint32_t cnt_res;     // Number of Resources
	
	// Offsets
	uint32_t pos_filetbl; // Byte position of the file table
	uint32_t pos_restbl;  // Byte position of the resource table
	
	// Date this file was build
	uint32_t build_year;
	uint32_t build_day;
	
	// Data
	LList     *resources;
} KeyFile;

int            key_resource_cmp_by_id            (const void *data,
                                                  const void *udata);

void           key_file_init                     (KeyFile    *key);
void           key_file_free                     (KeyFile    *key);
bool           key_file_read                     (FILE       *f,
                                                  KeyFile    *key);

#endif /* __KEY_FILE_H__ */
