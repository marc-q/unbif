/*
 * unbif.c
 * Copyright (C) 2017  Marc Volker Dickmann
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include "llist.h"

#include "format/aurora_types.h"
#include "format/bif_file.h"
#include "format/key_file.h"

static bool
read_and_check_ftype (FILE           *f,
                      const uint32_t  type)
{
	// Read the type
	uint32_t data = 0;
	if (fread (&data, 4, 1, f) != 1)
		return false;
	
	// Skip the version since it is not used
	fseek (f, 4, SEEK_CUR);
	
	// Compare
	return (data == type);
}

static void
load_and_run (const char *filename_key,
              const char *filename_bif,
              void        func (FILE  *f,
                                LList *keys))
{
	FILE *f_key = fopen (filename_key, "rb");
	if (f_key == NULL)
	{
		perror (NULL);
		return;
	}
	
	FILE *f_bif = fopen (filename_bif, "rb");
	if (f_bif == NULL)
	{
		fclose (f_key);
		perror (NULL);
		return;
	}
	
	if (read_and_check_ftype (f_key, 542721355) &&
	    read_and_check_ftype (f_bif, 1179011394))
	{
		KeyFile key;
		key_file_init (&key);
		key_file_read (f_key, &key);
		
		func (f_bif, key.resources);
		
		key_file_free (&key);
	}
	fclose (f_key);
	fclose (f_bif);
}

//
// Commands
//

static void
cmd_unpack (FILE  *f_bif,
            LList *keys)
{
	BifFile bif;
	bif_file_init (&bif);
	bif_file_read (f_bif, &bif);
	
	char filename[FILENAME_MAX];
	char *buf = NULL;
	FILE *f_out;
	
	LList *pos;
	BifResource *res;
	KeyResource *fname;
	LLIST_FOR_EACH (pos, bif.resources)
	{
		res = pos->data;
		
		// Get the filename from the key file
		fname = llist_find_custom (keys,
		                           key_resource_cmp_by_id,
		                           &res->id);
		
		if (fname == NULL)
			continue;
		
		// Build the filename
		strncpy (filename, fname->name, 16);
		strncat (filename, ".", 1);
		strncat (filename, aurora_type_to_str (res->type), 3);
		
		// Read the content
		fseek (f_bif, res->offset, SEEK_SET);
		buf = realloc (buf, res->file_size);
		if (fread (buf, 1, res->file_size, f_bif) != res->file_size)
			continue;
		
		// Write the content
		if (aurora_type_to_format (res->type) == FILE_FORMAT_BINARY)
			f_out = fopen (filename, "wb");
		else
			f_out = fopen (filename, "w");
		
		if (f_out != NULL)
			fwrite (buf, 1, res->file_size, f_out);
		
		fclose (f_out);
	}
	free (buf);
	bif_file_free (&bif);
}

static void
cmd_list (FILE  *f_bif,
          LList *keys)
{
	BifFile bif;
	bif_file_init (&bif);
	bif_file_read (f_bif, &bif);
	
	// Print table header in bold
	int len = printf ("\033[1m%-16s %-6s %-10s %-10s\033[0m\n",
	                  "Name",
	                  "Type",
	                  "Offset",
	                  "Size");
	
	// Print a solid line
	for (; len != 0; --len)
	{
		printf ("\u2500");
	}
	printf ("\n");
	
	// Print table entries
	LList *pos;
	BifResource *res;
	KeyResource *filename;
	LLIST_FOR_EACH (pos, bif.resources)
	{
		res = pos->data;
		
		filename = llist_find_custom (keys,
		                              key_resource_cmp_by_id,
		                              &res->id);
		
		if (filename == NULL)
			continue;
		
		printf ("%-16.16s %-6.3s %-10u %-10u\n",
		        filename->name,
		        aurora_type_to_str (res->type),
		        res->offset,
		        res->file_size);
	}
	bif_file_free (&bif);
}

//
// Menu
//

static void
version (void)
{
	printf ("unbif version 0.0.1\n");
}

static _Noreturn void
usage (const int status)
{
	printf ("Usage: unbif [OPTIONS] <key_file> <bif_file>\n");
	
	printf ("\nOptions:\n");
	printf ("%-25s %s\n", "-h", "Show this help");
	printf ("%-25s %s\n", "-V", "Display version number");
	printf ("%-25s %s\n", "-l", "Lists the files");
	printf ("%-25s %s\n", "-x", "Extract files from an archive");
	
	exit (status);
}

int
main (int argc, char **argv)
{
	if (argc == 1)
		usage (EXIT_FAILURE);
	
	// Parse options
	int opt = 0;
	bool cmd_list_a = false, cmd_unpack_a = false;
	do
	{
		opt = getopt (argc, argv, "hVlx");
		switch (opt)
		{
		case 'h':
			usage (EXIT_SUCCESS);
		case 'V':
			version ();
			exit (EXIT_SUCCESS);
		case 'l':
			cmd_list_a = true;
			break;
		case 'x':
			cmd_unpack_a = true;
			break;
		case -1:
			break;
		default:
			usage (EXIT_FAILURE);
		}
	} while (opt != -1);
	
	// Check for errors
	if (optind >= argc)
	{
		perror ("Expected argument after options");
		exit (EXIT_FAILURE);
	}
	else if ((argc - optind) < 2 ||
	         optind == 1)
	{
		usage (EXIT_FAILURE);
	}
	
	// Extract the filenames from args
	const char *filename_key = argv[optind];
	const char *filename_bif = argv[optind + 1];
	
	// Parse commands
	if (cmd_list_a)
		load_and_run (filename_key, filename_bif, cmd_list);
	
	if (cmd_unpack_a)
		load_and_run (filename_key, filename_bif, cmd_unpack);
	return 0;
}
