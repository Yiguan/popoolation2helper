# popoolation2helper
calculate allele frequency and allele frequency difference using sync data format generated by popoolation2

popoolation2 <https://sourceforge.net/p/popoolation2/wiki/Tutorial/> is a very useful tool for Pool_seq data, and can generate sync format file which contains the allele count for each population and each polymorphic site. But unfortuately, it can't output allele frequency for specific population. Although it can produce allele frequency difference, it calculates across all pairwise populations, and generate very large files with some data your don't want to use.

This tool exploits the sync data, but it allows you to specify the populations you want to calculate allele frequency, and allows you to specify the population pairs you want to compare allele frequency difference without necessary to output  difference across all populations.

## input data format

sync data (refer to popoolation2 tutorial) format as following:

```
2L	1524	T	0:200:0:2:0:0	0:202:0:0:0:0	0:202:0:0:0:0	0:202:0:0:0:0	0:202:0:0:0:0
2L	1669	G	2:0:0:200:0:0	3:0:0:199:0:0	31:0:0:171:0:0	23:0:0:179:0:0	15:0:0:187:0:0
2L	1675	A	200:0:0:2:0:0	202:0:0:0:0:0	202:0:0:0:0:0	202:0:0:0:0:0	202:0:0:0:0:0
2L	2821	C	0:2:200:0:0:0	0:0:202:0:0:0	0:0:202:0:0:0	0:0:202:0:0:0	0:0:202:0:0:0
2L	2965	T	0:200:0:2:0:0	0:202:0:0:0:0	0:202:0:0:0:0	0:202:0:0:0:0	0:202:0:0:0:0
2L	2980	G	2:0:0:200:0:0	0:0:0:202:0:0	0:0:0:202:0:0	0:0:0:202:0:0	0:0:0:202:0:0
2L	3066	T	0:200:0:2:0:0	0:197:0:5:0:0	0:202:0:0:0:0	0:202:0:0:0:0	0:202:0:0:0:0
2L	3067	T	0:200:2:0:0:0	0:197:5:0:0:0	0:202:0:0:0:0	0:202:0:0:0:0	0:202:0:0:0:0
2L	3068	C	2:0:200:0:0:0	5:0:197:0:0:0	0:0:202:0:0:0	0:0:202:0:0:0	0:0:202:0:0:0
2L	3069	A	200:2:0:0:0:0	197:5:0:0:0:0	202:0:0:0:0:0	202:0:0:0:0:0	202:0:0:0:0:0
```

Making sure you have valid reference allele in column 3, and remove indels(only include SNPs)

## Install

Compile the source code directly, or using:

```bash
chmod 777 install.sh
./install.sh
```
It will generate two executable object: `calfreq` and `caldiff`.

## Usage

1. calculate allele frequency

```bash
./calfreq -i test.sync -f 1,3,2,5
```

`-i` specify input sync file;

`-f` specify the poplation you want to calculate allele frequency, `0` indicate all populations;

2. calculate allele frequency difference

```bash
./caldiff -i test.sync -p 1-2,4-3,2-5
```
`-i` specify input sync file;

`-p` specify the population pairs you want to compare allele frequency difference, each pair separated by ","

