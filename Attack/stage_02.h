#pragma once

const int secondHeight = 119;
const int secondWidth = 61;

string SecondStage[] =
{
	"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
	"BFFFFFFSSSSSSSSFFFFFSSSSSSFFFSSSSSSSSSSSSSFFFFFFFFFFFFFFFFFFB",
	"BSSSFFFFFSSSFFFFSSSSSSSSSFFFFFFFSSSSSFFFFFFSSFFWWWWWFFFFFFFFB",
	"BSSSSSSFFFFFFFSSSSSSFFFFFFSSSSFFFFFFFFFFSSSSSSFFWWWWWFFFFFFFB",
	"BSSSSSFFFFFFSSSSSSSSSSSSSSSSSSSSSSSFFFFSSSSSSSSFFWWWFFFFFFFFB",
	"BSSSSSSFFFSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSFFFFFFFFWB",
	"BFSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSFFFFFFWWB",
	"BFFSSSSSSSSSSSSSSSFFFFSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSFFFFWWWB",
	"BFFFSSSSSSSSSSSSSSFFSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSFFFWWWB",
	"BFFSSSSSSSSSSSSFFFFSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSWWWSB",
	"BFSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSWWWWSB",
	"BFSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSWWWWB",
	"BSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSWWWB",
	"BSSSSSSSSFFSSSSSSBBBBSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSWB",
	"BSSSSSSFFFFFSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSB",
	"BSSSSFFFWWWFFFSSSSSSSSSSSSSSSSSSSSFFFFFFFFFFFFFFFFFFFSSSSSSSB",
	"BSSSFFFWWWWWWFFFSSSSSSSSSSSSSSSFFFFFFFFFFFFFFFFFFFFFFFSSSSSSB",
	"BSSSSFFFWWWFFFSSSSSSSSSSFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFSSSSB",
	"BSSSSSFFFFFFFSSFFFFFFFFFFFFFFSSWWWWWWWWWWWWWSSSSFFFFFFFFFSSSB",
	"BSSSSFFFFFFFFFFFFFFFFFFFFFFFSSWWWWWWWWWWWWWWWWWWWWWFFFFFFFFSB",
	"BFFFFFFFFFFFFFFFFFFFFFFFFSSSWWWWWWWWWWWWWWWWWWWWWWWWWWFFFFFFB",
	"BSSSFFFFFFFFFFFFFFSSSSWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWFFFFFFFB",
	"BSSSSSFFFFFFFFFFFFFFWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWFFFFFFFFB",
	"BSSSSSSFFFFFFFFFFFSSSSSSSWWWWWWWWWWWWWWWWWWWWWWWWSSSSSSFFFFFB",
	"BSSSSSSFFFFFFFFFFFFFFSSSSSSSSSWWWWWWWWWWWSSSSSSSSSSSSSSSSSSSB",
	"BSSSSSSSSSSSSFFFFFFFFFFSSSSSSSSWWWWWWWSSSSSSSSSSSSSSSSSSSSSSB",
	"BSSSSSSSSSSSSFFFFFFFFFFFSSSSSSWWWWWSSSSSSSSSSSSSSWwWWWWSSSSSB",
	"BSSSSSSSSSSSSSSSFFFFFFFSSSSSSSSSSSSSSSSSSSSSSSWWWWWWWWWWWSSSB",
	"BSSSSSSFFFFFFFFFFFSSSSSSSSSSSSSSSSSSSSSSSSSSSWWWWWWWWWWSSSSSB",
	"BFFFFFFFFFFFFFFSSSSSSSSSSSSSSSSSBBSSSSSSSSSSSSSSWWWWWWSSSSSSB",
	"BFFFFFFFFSSSSSSSSSSSSSSSSSSSSSSSBBSSSSSSWWWWWWWWWWWSSSSSSSSSB",
	"BFFFFFFSSSSSSSSSSSSSSSSSSSSSSSSSBBSSSSFFFWWWWWWWWWWSSSSSSBBBB",
	"BSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSFFFFFFFFFWWWWWWWWWWWSSSBWWWB",
	"BSSSSSSSSSSSSSSSFFFSSSSSSSSSSSSSSSFFFFFFFFWWWWWWWWSSSSSSBWWWB",
	"BSSSSSSSSSSSSSFFFFFFFSSSBBBBBBBSSSSSFFFFFFFFFFFFBBSSSSSBWWSSB",
	"BSSSSSSSSSSFFFFFWWWWFFSSSSSSSSSSSSSSSSSSSSFFFFFFFBSSSSSBWSSSB",
	"BSSSSFFFFFFFFFFFWWWWWWFFSSSSSSSSSSSSSSSSSSSSSSSSSBSSSSBWSSSSB",
	"BSSSSSSSSFFFFFFFWWWWFFFFFFSSSSSSSSSSSSSSSSSSSSSSSSSSSSBSSSSSB",
	"BSSSSSSSSSFFFFFFFWWWFFFFFFFFFSSSSSSSSSSSSSSSSSSSSSSSSBSSSSSSB",
	"BSSSSSSSSSSSFFFFWWWFFFFFFFFSSSSSSSSSSSBBBBBSSSSSSSSSSBSSSSSSB",
	"BSSSSSSSSSSSSSFFFFFFFFFSSSSSSSSSSSSSSSSSSSSSSSSSSSSSBSSSSSSSB",
	"BSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSBSSSSSSSB",
	"BSSSSSSFFFFFFFFFFFFFSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSFBSSSSSSFFB",
	"BSSSFFFFFFFFBBBBBBBBBBBBBSSSSSSSSSSSSSSSSSSSSFFFFFFBSSSSSFFFB",
	"BSSSSSSFFFFFFFBBBBBBBBSSSSSSSSSSSSSSSSSSSSSSFFFFFFBWSSSSFFFFB",
	"BSSSSFFFFFFFFSSSSBBSSSSSSSSSSSSSSSSSSSSSSFFFFFFSSSBWSSSFFFFFB",
	"BSSSSSSFFFFSSSSSSBSSSSSSSSSSSSSSSSSSSSFFFFFFFSSSSBWWSSFFFFFFB",
	"BSSSSSSSSFFFSSSSSSSSSSSSSSSSSSSSSSSSSSSFFFFSSSSSSBWWSFFFFFFFB",
	"BSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSBWWWFFFFFFFFB",
	"BSSSSSSSSSSSSSSSSSFFSSSSSSSSSSSSSSSSSSSSSSSSSSSSBWWWFFFFFFFFB",
	"BFFSSSSSSSSSSSSFFFFFSSSSSSSSFFSSSSSSSSSSSSWWWSSSFBWWSFFFFFFFB",
	"BFFFSSSSSSSSSSSSFFSSSSSSSSSFFFFSSSSSSSSSSSWWWWWFFBWWSSFFFFFFB",
	"BFSSSSSSSSSSSSSSSSSSSSSSSFFFBSSSSSSSSSSSWWWWWWWWWWBWSSSFFFFFB",
	"BSSSSSSSSSSSFFFFFFSSSSSSFFFFBSSSSSSSSSSWWWWWWWWWWWBWSSSSFFFSB",
	"BFSSSSSSSSSSSSFFWWWWWSSFFSSSBBSSSSSSSSSSSSWWWWWWWWFBSSSFFFFSB",
	"BFFSSSSSSSSSSSSFFWWWWWWFFSSSSSSSSSSSSSSSSSSSSSSSSFFBSFFFFSSSB",
	"BFFFSSSSSSSSSSSFFFWWWWWWFFFSSSSSSSSSSSFFFFSSSSSSSSSFBSFFFSSSB",
	"BFFFFSSSSSSSSSSSFFWWWWWWWFFFFSSSSSSSSSSSFFFFFSSSSSSSBSSFFFSSB",
	"BFFFFFSSSSSSSFFFFWWWWWWWWWWFSSSSSSSSSSFFFFFFSSSSSSSSSBSSFFFFB",
	"BWWFFFSSSSSSSSFFWWWWWWWWWWFSSSSSSSSSSSSFFFSSSSFFFSSSSBSSSFFFB",
	"BWWWFFFFSSFFFFWWWWWWWWWWWWFFSSSSSSSSSSSFFSSSSFWWFFFSSBBSSSFFB",
	"BWWWWFFFSSSSFFFWWWWWWWWFFFFSSSSSSSSSSSSSSSSFFFWWWWFFFSBSSSSSB",
	"BWWWWFFFFSSSSSFFFFFFFSSSSSSSSSSSSSSSSSSSSSFFWWWWWWWFFFFBSSSSB",
	"BWWWWWFFFFSSSSSSSSSFFFFSSSSSSSFFFFSSSSSSSSSSFFWWWWFFFSSBSSSSB",
	"BWWWFFFFFFSSSSSSSSSSSSSFFSSSSFFFFFFFSSSSSSSSSFFFFFFFSSSSSSSSB",
	"BWWFFFFFSSSSSSSSSSSSSSFFFFFFFFFFFFFFFFSSSSSSSSSSSSSSSSSSSSSSB",
	"BFFFSSSSSSSSBBBSSSSSSFFFSSFFFFFFFFFSSSSSSSSSSSSSSSSSSSSSSBBBB",
	"BFFSSSSSSSBBBSSSSSSSSSSSSSSSSSSSSSSSSSSSSFFFFFSSSSSSSSSSSSSSB",
	"BSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSFFFFFFFFFFSSSSSSSSSSSSSB",
	"BSSSWWWWSSSSSSSSSSSBSSSSSSSSSSSSSFFFFFFFFFFFSSSSSSSSSSSSSSSSB",
	"BSSSWWWSSSSSSSBBBBBBSSSSSSSSSFFFFFFWWWWWWWFFFFFFSSSSSSSSSSSSB",
	"BSSSSSSSSSSSSSSSSSSSSSSSSSFFFFFFFFWWWWWWWWWWWWWFFFFSSSSSSFFFB",
	"BSSSSSSSSSSSSSSSSSSSSSSFFFFFFFWWWWWWWWWWWWWWWWWWWWWWWSSSWWWWB",
	"BWWWWWWWWWSSSSSSSSSFFFFFFFFWWWWWWWWWWWWWWWWWWWWWWWWSSSSSFFWWB",
	"BWWWWWWWWWWWSSSSSFFFFFFFFWWWWWWWWWWWWWWWWWWWWWWWWFFSSSSSFFFFB",
	"BWWWWWWWWWSSSSFFFFFFFWWWWWWWWWWWWWWWWWWWWWWWWFFFFFSSSSSSSFFFB",
	"BWWWSSSSSSFFFFFFFFFWWWWWWWWWWWWWWWWWWWWWWWWWFFFFSSSSSSSSSFFFB",
	"BSSSSSFFFFFFFFFFFFWWWWWWWWWWWWWFFFFFFFFFFFFFFFSSSSSSSSSWWFFFB",
	"BFFFFFFFFFFFFFFFFWWWWWWWWWWWWFFFFFFFFFFFFFFFSSSSSSSSSWWWWWFFB",
	"BFFFFFFFFFFFFFFWWWWWWWWWWWFFFFFFFSSSSSSSSSSSSSSSWWWWWWWWWWFFB",
	"BSSSFFFFFFFFFFFFWWWWWWWWWWWWFFFSSSSSSSSSSSSSSWWWWWWWWWWWWWFFB",
	"BSSSSFFFFSSSSSFFFFFFWWWWWWWWWFFFFSSSSSSSSWWWWWWWWWWWWWWWWWFFB",
	"BSSSSSFFSSSSSSSFFFFFFWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWFFFFFFFB",
	"BSSBBSSSSSSSSSSSSSFFFFFFFFWWWWWWWWWWWWWWWWWWWWWBBBBBBFFFSSSSB",
	"BSSSSSSSSSSSSSSSSSSSSSSSSFFFFFFFFFFWWWWWWWWWFFFFFFFFSSSSSSSSB",
	"BSSSSSSFFSSSSSSSSSSSSSSSSSSSFFFFFFFFFFFFFFFFFFFFSSSSSSSSSSSSB",
	"BSSSSSFFFFSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSB",
	"BSSSFFFFFFFFSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSBBBBBB",
	"BSSSFFFFFFFFSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSB",
	"BSSFFFFFFFSSSSSSSSWWWWWSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSB",
	"BSSSSSFFSSSSSSSWWWWWWWWWSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSB",
	"BSSSSSSSSSSSSSSSSSWWWWWWFFSSSSSSSSSSSSSSSSSFFFSSSSSSSSSSSSSSB",
	"BSSSSSSSSSSSSSSSSSSFFFFFFFFFFFFSSSSSSSSSSFFFSSSSSSSSSSSSSSSSB",
	"BSSBBSSSSSSSSSSSSSSFFFFFFFFFFFFFFFSSSSSSFFFSSSSFFFFFFFFFFSSSB",
	"BSSSSSSSSSSSFFFFFFFFFSSSSSSSSSFFFFFFFFFFFFFFFFFFFFFFSSSSSSSSB",
	"BSSSSSFFFFFSSSSSSSSSSSSSSSSSSSSSSSSSFFBBBBBBBBSSSSSSSSSSSSSSB",
	"BSSFFFFFFFFFFFSSSSSSSSSSSSSSSSSSSSSSSFBSSSSSSSSSSSSSWWWSSSSSB",
	"BFFFFFFFFFFFFSSSSSSSSSSSSSSSSSSSSSBBBBBSSSSSSSSSWWWWWWWWSSSSB",
	"BSSFFFFWWWFFSSSSSSSSSFFFFFFFSSSSSSSSSSSSSSSSSFFFFFWWWSSSSSSSB",
	"BSSSSWWWWWWSSSSSSFFFFFFFFSSSSSSSSSSSSSSSSSSSFFFFFFFFSSSSSSSSB",
	"BSSSSSSWWWSSSSSFFFFFFSSSSSSSSSSSSSSSSSSSSSSFFFFFFFFSSSSSSSSSB",
	"BSSSSSSSSSSSSSSSFFSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSB",
	"BSSSSBBBBSSSSSSSFFSSSSSSFFFFFFFFFFFFFSSSSSSSSSSSSSSSSSSSSSSFB",
	"BSSSSBSSSSSSSSFFFFFSSSFFFFFFFFFFFFFFFFFSSSSSSSSSSSSSSSSSSFFFB",
	"BSSSSBSSSSSSSFFFFSSSSSFFFFWWWWWWWWWWWFFFSSSSSSSSSSSSSSFFFFFFB",
	"BSSSSBSSSSSFFFFFSSSSSSFFFFWWWWWWWWWWWFFFFFBBBBBBBBBFFFFFFFFFB",
	"BSSSSBSSSSFFFFSSSSSSFFFFWWWWWWWWWWWWWWWFFFFSSSSSSSSFFFFFFFWWB",
	"BSSSSSSSSSSSSSSSSSSSSFFFWWWWWWWWWWWWWWWFFFFSSSSSSSFFFWWWWWWWB",
	"BSSSSSSSSSCSSSSSSSSSSSFFWWWWWWWWWWWWWWWFFFFFSSSSFFFFWWWWWWWWB",
	"BSSSSSSSSSSSSSSSSSSSSSFFFFWWWWWWWWWWWFFFFFSSSSSSSSFFFFWWWWWWB",
	"BSSSSSSFFFFSSSSSSSSSSSSFFFWWWWWWWWWWWFFFFSSSSSSSSSFFFFWWWWWWB",
	"BSSSSFFFFFFFFSSSSSSSSSSSFFFFFFFFFFFFFFFFFFSSSSSSSSSSFFFFFWWWB",
	"BSSSFFFFFFFFFFSSSSSSSSSSSSFFFFFFFFFFFFFFSSSSSSSSSSSSSFFFFFFFB",
	"BFFFFFFSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSASSSSSSSSSFFFFFFFFFFFB",
	"BFFFFWWWWWSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSBBBBFFFFFFFFFFB",
	"BFFFFWWWWWWWSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSBFFFFFFFFFFFFFFB",
	"BFFFFFFFSSSSSSSBBBSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSFFFFFFFFFFFB",
	"BFFFFFFFFSSSSBBBBBBBBSSSSSSSSSSSSSSSSSSSSSSSSFFFFFFFFFFFFFFFB",
	"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"
};
