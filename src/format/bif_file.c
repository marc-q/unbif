/*
 * bif_file.c
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

#include "bif_file.h"

//
// BifResource
//

static LList *
bif_resource_list_add (LList       *list,
                       BifResource *data)
{
	BifResource *new = malloc (sizeof (BifResource));
	
	*new = *data;
	
	return llist_append (list, new);
}

//
// BifFile
//

static bool
bif_file_read_header (FILE    *f,
                      BifFile *bif)
{
	if (fread (&bif->cnt_var_res, 4, 1, f) != 1 ||
	    fread (&bif->cnt_fix_res, 4, 1, f) != 1 ||
	    
	    fread (&bif->pos_var_res, 4, 1, f) != 1)
	{
		return false;
	}
	return true;
}

void
bif_file_init (BifFile *bif)
{
	bif->resources = NULL;
}

void
bif_file_free (BifFile *bif)
{
	if (bif->resources != NULL)
		llist_free_full (bif->resources, free);
}

bool
bif_file_read (FILE    *f,
               BifFile *bif)
{
	const size_t offset = ftell (f) - 8;
	
	if (!bif_file_read_header (f, bif))
		return false;
	
	// Variable resource table
	fseek (f, bif->pos_var_res + offset, SEEK_SET);
	
	BifResource res;
	for (uint32_t i = 0; i < bif->cnt_var_res; i++)
	{
		if (fread (&res.id, 4, 1, f) != 1 ||
		    fread (&res.offset, 4, 1, f) != 1 ||
		    
		    fread (&res.file_size, 4, 1, f) != 1 ||
		    fread (&res.type, 4, 1, f) != 1)
		{
			return false;
		}
		
		res.offset += offset;
		
		bif->resources = bif_resource_list_add (bif->resources, &res);
	}
	return true;
}
