# unbif

## About
Unbif is a small tool that can be used to extract files from *BIFF* archives.
BIFF archives can be found in games that use BioWare’s Aurora engine and contain
other files like scripts and images.

A list of files used by the Aurora engine can be found inside *src/format/aurora_types.h*.

## How to compile
1. Make shure you have `make` and `gcc` installed.
2. Download this repository (If you don’t like to use git, make use of GitHub’s [zip](https://github.com/marc-q/unbif/archive/master.zip) file).
3. Open a terminal and navigate into the repository folder.
4. Run `$ make` (Without `$ `).

## How to use

### Print the help
`$ unbif -h`

### List files
`$ unbif -l keyfile.key biffile.bif`

### Extract files
`$ unbif -x keyfile.key biffile.bif`
