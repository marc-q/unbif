#ifndef __AURORA_TYPES_H__
#define __AURORA_TYPES_H__

typedef enum AuroraFileType
{
	FILE_TYPE_RES = 0,    // gff, Generic gff
	FILE_TYPE_BMP = 1,    // binary, Windows BMP file
	FILE_TYPE_TGA = 3,    // binary, TGA image format
	FILE_TYPE_WAV = 4,    // binary, WAV sound file
	FILE_TYPE_PLT = 6,    // binary, Bioware Packed Layered Texture
	FILE_TYPE_INI = 7,    // text (ini), Windows INI file format
	FILE_TYPE_TXT = 10,   // text, Text file
	FILE_TYPE_MDL = 2002, // mdl, Aurora model
	FILE_TYPE_NSS = 2009, // text, NWScript source
	FILE_TYPE_NCS = 2010, // binary, NWScript Compiled Script
	FILE_TYPE_ARE = 2012, // gff, BioWare Aurora Engine Area file
	FILE_TYPE_SET = 2013, // text (ini), BioWare Aurora Engine Tileset
	FILE_TYPE_IFO = 2014, // gff, Module Info File
	FILE_TYPE_BIC = 2015, // gff, Character/Creature
	FILE_TYPE_WOK = 2016, // mdl, Walkmesh
	FILE_TYPE_2DA = 2017, // text, 2-D Array
	FILE_TYPE_TXI = 2022, // text, Extra Texture Info
	FILE_TYPE_GIT = 2023, // gff, Game Instance File
	FILE_TYPE_UTI = 2025, // gff, Item Blueprint
	FILE_TYPE_UTC = 2027, // gff, Creature Blueprint
	FILE_TYPE_DLG = 2029, // gff, Conversation File
	FILE_TYPE_ITP = 2030, // gff, Tile/Blueprint Palette File
	FILE_TYPE_UTT = 2032, // gff, Trigger Blueprint
	FILE_TYPE_DDS = 2033, // binary, Compressed texture file
	FILE_TYPE_UTS = 2035, // gff, Sound Blueprint
	FILE_TYPE_LTR = 2036, // binary, Letter-combo probability info
	FILE_TYPE_GFF = 2037, // gff, Generic File Format
	FILE_TYPE_FAC = 2038, // gff, Faction File
	FILE_TYPE_UTE = 2040, // gff, Encounter Blueprint
	FILE_TYPE_UTD = 2042, // gff, Door Blueprint
	FILE_TYPE_UTP = 2044, // gff, Placeable Object Blueprint
	FILE_TYPE_DFT = 2045, // text (ini), Default Values file
	FILE_TYPE_GIC = 2046, // gff, Game Instance Comments
	FILE_TYPE_GUI = 2047, // gff, Graphical User Interface layout
	FILE_TYPE_UTM = 2051, // gff, Store/Merchant Blueprint
	FILE_TYPE_DWK = 2052, // mdl, Door walkmesh
	FILE_TYPE_PWK = 2053, // mdl, Placeable Object walkmesh
	FILE_TYPE_JRL = 2056, // gff, Journal File
	FILE_TYPE_SAV = 2057, // erf, Game save
	FILE_TYPE_UTW = 2058, // gff, Waypoint Blueprint
	FILE_TYPE_SSF = 2060, // binary, Sound Set File
	FILE_TYPE_NDB = 2064, // binary, Script Debugger File
	FILE_TYPE_PTM = 2065, // gff, Plot Manager file, Plot Instance
	FILE_TYPE_PTT = 2066, // gff, Plot Wizard Blueprint
	FILE_TYPE_INVALID = 0xFFFF // Invalid resource type
} AuroraFileType;

typedef enum AuroraFileFormat
{
	FILE_FORMAT_BINARY,
	FILE_FORMAT_TEXT,
	FILE_FORMAT_TEXT_INI,
	FILE_FORMAT_GFF,
	FILE_FORMAT_MDL,
	FILE_FORMAT_ERF,
	FILE_FORMAT_INVALID
} AuroraFileFormat;

const char *            aurora_type_to_str         (const AuroraFileType type);
AuroraFileFormat        aurora_type_to_format      (const AuroraFileType type);

#endif /* __AURORA_TYPES_H__ */
