/*
 * key_file.c
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

#include "llist.h"

#include "key_file.h"

//
// KeyResource
//

static LList *
key_resource_list_add (LList       *list,
                       KeyResource *data)
{
	KeyResource *new = malloc (sizeof (KeyResource));
	
	*new = *data;
	
	return llist_append (list, new);
}

int
key_resource_cmp_by_id (const void *data,
                        const void *udata)
{
	const KeyResource *a = data;
	const uint32_t *b = udata;
	
	return (a->id == *b);
}

//
// KeyFile
//

static bool
key_file_read_header (FILE    *f,
                      KeyFile *key)
{
	if (fread (&key->cnt_bif, 4, 1, f) != 1 ||
	    fread (&key->cnt_res, 4, 1, f) != 1 ||
	    
	    fread (&key->pos_filetbl, 4, 1, f) != 1 ||
	    fread (&key->pos_restbl, 4, 1, f) != 1 ||
	    
	    fread (&key->build_year, 4, 1, f) != 1 ||
	    fread (&key->build_day, 4, 1, f) != 1)
	{
		return false;
	}
	
	// The build_year has been saved as an offset from 1900
	key->build_year += 1900;
	
	// Skip the reserved part
	fseek (f, 32, SEEK_CUR);
	return true;
}

void
key_file_init (KeyFile *key)
{
	key->resources = NULL;
}

void
key_file_free (KeyFile *key)
{
	if (key->resources != NULL)
		llist_free_full (key->resources, free);
}

bool
key_file_read (FILE    *f,
               KeyFile *key)
{
	const size_t offset = ftell (f) - 8;
	
	if (!key_file_read_header (f, key))
		return false;
	
	// Resource table
	fseek (f, key->pos_restbl + offset, SEEK_SET);
	
	KeyResource res;
	for (uint32_t i = 0; i < key->cnt_res; i++)
	{
		if (fread (res.name, 1, 16, f) != 16 ||
		    fread (&res.type, 2, 1, f) != 1 ||
		    fread (&res.id, 4, 1, f) != 1)
		{
			return false;
		}
		
		res.name[16] = '\0';
		
		key->resources = key_resource_list_add (key->resources, &res);
	}
	return true;
}
