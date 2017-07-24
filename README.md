# unbif

## About unbif
Unbif is a small tool that can be used to extract files from *BIFF* archives.
BIFF files can be found in games that use BioWare's Aurora engine and contain
other files like scripts etc.

A list of files used by the Aurora engine can be found inside *src/format/aurora_types.h*.

## How to compile unbif
1. Download this repository (If you don't like to use git, make use of GitHubs zip file)
2. Open a terminal and navigate into the repository folder.
3. Run `$ make` (Without `$ `).

## How to use unbif

### Print the help
`$ unbif -h`

### Print the version
`$ unbif -V`

### List files
`$ unbif -l keyfile.key biffile.bif`

### Extract files
`$ unbif -x keyfile.key biffile.bif`
