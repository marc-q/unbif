/*
 * aurora_types.c
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

#include "aurora_types.h"

const char *
aurora_type_to_str (const AuroraFileType type)
{
	switch (type)
	{
	case FILE_TYPE_RES:
		return "res";
	case FILE_TYPE_BMP:
		return "bmp";
	case FILE_TYPE_TGA:
		return "tga";
	case FILE_TYPE_WAV:
		return "wav";
	case FILE_TYPE_PLT:
		return "plt";
	case FILE_TYPE_INI:
		return "ini";
	case FILE_TYPE_TXT:
		return "txt";
	case FILE_TYPE_MDL:
		return "mdl";
	case FILE_TYPE_NSS:
		return "nss";
	case FILE_TYPE_NCS:
		return "ncs";
	case FILE_TYPE_ARE:
		return "are";
	case FILE_TYPE_SET:
		return "set";
	case FILE_TYPE_IFO:
		return "ifo";
	case FILE_TYPE_BIC:
		return "bic";
	case FILE_TYPE_WOK:
		return "wok";
	case FILE_TYPE_2DA:
		return "2da";
	case FILE_TYPE_TXI:
		return "txi";
	case FILE_TYPE_GIT:
		return "git";
	case FILE_TYPE_UTI:
		return "uti";
	case FILE_TYPE_UTC:
		return "utc";
	case FILE_TYPE_DLG:
		return "dlg";
	case FILE_TYPE_ITP:
		return "itp";
	case FILE_TYPE_UTT:
		return "utt";
	case FILE_TYPE_DDS:
		return "dds";
	case FILE_TYPE_UTS:
		return "uts";
	case FILE_TYPE_LTR:
		return "ltr";
	case FILE_TYPE_GFF:
		return "gff";
	case FILE_TYPE_FAC:
		return "fac";
	case FILE_TYPE_UTE:
		return "ute";
	case FILE_TYPE_UTD:
		return "utd";
	case FILE_TYPE_UTP:
		return "utp";
	case FILE_TYPE_DFT:
		return "dft";
	case FILE_TYPE_GIC:
		return "gic";
	case FILE_TYPE_GUI:
		return "gui";
	case FILE_TYPE_UTM:
		return "utm";
	case FILE_TYPE_DWK:
		return "dwk";
	case FILE_TYPE_PWK:
		return "pwk";
	case FILE_TYPE_JRL:
		return "jrl";
	case FILE_TYPE_SAV:
		return "sav";
	case FILE_TYPE_UTW:
		return "utw";
	case FILE_TYPE_SSF:
		return "ssf";
	case FILE_TYPE_NDB:
		return "ndb";
	case FILE_TYPE_PTM:
		return "ptm";
	case FILE_TYPE_PTT:
		return "ptt";
	default:
		return "err";
	}
}

AuroraFileFormat
aurora_type_to_format (const AuroraFileType type)
{
	switch (type)
	{
	case FILE_TYPE_BMP:
	case FILE_TYPE_TGA:
	case FILE_TYPE_WAV:
	case FILE_TYPE_PLT:
	case FILE_TYPE_NCS:
	case FILE_TYPE_DDS:
	case FILE_TYPE_LTR:
	case FILE_TYPE_SSF:
	case FILE_TYPE_NDB:
		return FILE_FORMAT_BINARY;
	case FILE_TYPE_TXT:
	case FILE_TYPE_NSS:
	case FILE_TYPE_2DA:
	case FILE_TYPE_TXI:
		return FILE_FORMAT_TEXT;
	case FILE_TYPE_INI:
	case FILE_TYPE_SET:
	case FILE_TYPE_DFT:
		return FILE_FORMAT_TEXT_INI;
	case FILE_TYPE_RES:
	case FILE_TYPE_ARE:
	case FILE_TYPE_IFO:
	case FILE_TYPE_BIC:
	case FILE_TYPE_GIT:
	case FILE_TYPE_UTI:
	case FILE_TYPE_UTC:
	case FILE_TYPE_DLG:
	case FILE_TYPE_ITP:
	case FILE_TYPE_UTT:
	case FILE_TYPE_UTS:
	case FILE_TYPE_GFF:
	case FILE_TYPE_FAC:
	case FILE_TYPE_UTE:
	case FILE_TYPE_UTD:
	case FILE_TYPE_UTP:
	case FILE_TYPE_GIC:
	case FILE_TYPE_GUI:
	case FILE_TYPE_UTM:
	case FILE_TYPE_JRL:
	case FILE_TYPE_UTW:
	case FILE_TYPE_PTM:
	case FILE_TYPE_PTT:
		return FILE_FORMAT_GFF;
	case FILE_TYPE_MDL:
	case FILE_TYPE_WOK:
	case FILE_TYPE_DWK:
	case FILE_TYPE_PWK:
		return FILE_FORMAT_MDL;
	case FILE_TYPE_SAV:
		return FILE_FORMAT_ERF;
	default:
		return FILE_FORMAT_INVALID;
	}
}
