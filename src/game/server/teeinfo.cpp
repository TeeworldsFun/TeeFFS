#include <base/color.h>
#include <base/system.h>

#include "teeinfo.h"

struct StdSkin
{
	char m_SkinName[64];
	char m_apSkinPartNames[6][24];
	bool m_aUseCustomColors[6];
	int m_aSkinPartColors[6];
};

static StdSkin g_StdSkins[] = {
	{"default", {"standard", "", "", "standard", "standard", "standard"}, {true, false, false, true, true, false}, {1798004, 0, 0, 1799582, 1869630, 0}},
	{"bluekitty", {"kitty", "whisker", "", "standard", "standard", "standard"}, {true, true, false, true, true, false}, {8681144, -8229413, 0, 7885547, 7885547, 0}},
	{"bluestripe", {"standard", "stripes", "", "standard", "standard", "standard"}, {true, false, false, true, true, false}, {10187898, 0, 0, 750848, 1944919, 0}},
	{"brownbear", {"bear", "bear", "hair", "standard", "standard", "standard"}, {true, true, false, true, true, false}, {1082745, -15634776, 0, 1082745, 1147174, 0}},
	{"cammo", {"standard", "cammo2", "", "standard", "standard", "standard"}, {true, true, false, true, true, false}, {5334342, -11771603, 0, 750848, 1944919, 0}},
	{"cammostripes", {"standard", "cammostripes", "", "standard", "standard", "standard"}, {true, true, false, true, true, false}, {5334342, -14840320, 0, 750848, 1944919, 0}},
	{"coala", {"koala", "twinbelly", "", "standard", "standard", "standard"}, {true, true, false, true, true, false}, {184, -15397662, 0, 184, 9765959, 0}},
	{"limekitty", {"kitty", "whisker", "", "standard", "standard", "standard"}, {true, true, false, true, true, false}, {4612803, -12229920, 0, 3827951, 3827951, 0}},
	{"pinky", {"standard", "whisker", "", "standard", "standard", "standard"}, {true, true, false, true, true, false}, {15911355, -801066, 0, 15043034, 15043034, 0}},
	{"redbopp", {"standard", "donny", "unibop", "standard", "standard", "standard"}, {true, true, true, true, true, false}, {16177260, -16590390, 16177260, 16177260, 7624169, 0}},
	{"redstripe", {"standard", "stripe", "", "standard", "standard", "standard"}, {true, false, false, true, true, false}, {16307835, 0, 0, 184, 9765959, 0}},
	{"saddo", {"standard", "saddo", "", "standard", "standard", "standard"}, {true, true, false, true, true, false}, {7171455, -9685436, 0, 3640746, 5792119, 0}},
	{"toptri", {"standard", "toptri", "", "standard", "standard", "standard"}, {true, false, false, true, true, false}, {6119331, 0, 0, 3640746, 5792119, 0}},
	{"twinbop", {"standard", "duodonny", "twinbopp", "standard", "standard", "standard"}, {true, true, true, true, true, false}, {15310519, -1600806, 15310519, 15310519, 37600, 0}},
	{"twintri", {"standard", "twintri", "", "standard", "standard", "standard"}, {true, true, false, true, true, false}, {3447932, -14098717, 0, 185, 9634888, 0}},
	{"warpaint", {"standard", "warpaint", "", "standard", "standard", "standard"}, {true, false, false, true, true, false}, {1944919, 0, 0, 750337, 1944919, 0}}};

CTeeInfo::CTeeInfo(const char *pSkinName, int UseCustomColor, int ColorBody, int ColorFeet)
{
	str_copy(m_SkinName, pSkinName, sizeof(m_SkinName));
	m_UseCustomColor = UseCustomColor;
	m_ColorBody = ColorBody;
	m_ColorFeet = ColorFeet;
}

CTeeInfo::CTeeInfo(const char *pSkinPartNames[6], int *pUseCustomColors, int *pSkinPartColors)
{
	for(int i = 0; i < 6; i++)
	{
		str_copy(m_apSkinPartNames[i], pSkinPartNames[i], sizeof(m_apSkinPartNames[i]));
		m_aUseCustomColors[i] = pUseCustomColors[i];
		m_aSkinPartColors[i] = pSkinPartColors[i];
	}
}

void CTeeInfo::ToSixup()
{
	SkinToSixup();
	ColorToSixup();
}

void CTeeInfo::FromSixup()
{
	SkinFromSixup();
	ColorFromSixup();
}

void CTeeInfo::SkinToSixup()
{
	// reset to default skin
	for(int p = 0; p < 6; p++)
	{
		str_copy(m_apSkinPartNames[p], g_StdSkins[0].m_apSkinPartNames[p], 24);
		m_aUseCustomColors[p] = g_StdSkins[0].m_aUseCustomColors[p];
		m_aSkinPartColors[p] = g_StdSkins[0].m_aSkinPartColors[p];
	}

	// check for std skin
	for(auto &StdSkin : g_StdSkins)
	{
		if(!str_comp(m_SkinName, StdSkin.m_SkinName))
		{
			for(int p = 0; p < 6; p++)
			{
				str_copy(m_apSkinPartNames[p], StdSkin.m_apSkinPartNames[p], 24);
				m_aUseCustomColors[p] = StdSkin.m_aUseCustomColors[p];
				m_aSkinPartColors[p] = StdSkin.m_aSkinPartColors[p];
			}
			break;
		}
	}
}

void CTeeInfo::SkinFromSixup()
{
	// reset to default skin
	str_copy(m_SkinName, "default", sizeof(m_SkinName));
	m_UseCustomColor = false;
	m_ColorBody = 0;
	m_ColorFeet = 0;

	// check for std skin
	for(auto &StdSkin : g_StdSkins)
	{
		bool match = true;
		for(int p = 0; p < 6; p++)
		{
			if(str_comp(m_apSkinPartNames[p], StdSkin.m_apSkinPartNames[p]) || m_aUseCustomColors[p] != StdSkin.m_aUseCustomColors[p] || (m_aUseCustomColors[p] && m_aSkinPartColors[p] != StdSkin.m_aSkinPartColors[p]))
			{
				match = false;
				break;
			}
		}
		if(match)
		{
			str_copy(m_SkinName, StdSkin.m_SkinName, sizeof(m_SkinName));
			return;
		}
	}

	// find closest match
	int best_skin = 0;
	int best_matches = -1;
	for(int s = 0; s < 16; s++)
	{
		int matches = 0;
		for(int p = 0; p < 3; p++)
			if(str_comp(m_apSkinPartNames[p], g_StdSkins[s].m_apSkinPartNames[p]) == 0)
				matches++;

		if(matches > best_matches)
		{
			best_matches = matches;
			best_skin = s;
		}
	}

	str_copy(m_SkinName, g_StdSkins[best_skin].m_SkinName, sizeof(m_SkinName));
}

void CTeeInfo::ColorToSixup()
{
	if(m_UseCustomColor)
	{
		ColorRGBA ColorBody = color_cast<ColorRGBA>(ColorHSLA(m_ColorBody).UnclampLighting());
		ColorRGBA ColorFeet = color_cast<ColorRGBA>(ColorHSLA(m_ColorFeet).UnclampLighting());

		ColorRGBA BodyPartGrey = color_cast<ColorRGBA>(ColorHSLA(m_aUseCustomColors[0] ? m_aSkinPartColors[0] : 255)).Greyscale();
		ColorRGBA FeetPartGrey = color_cast<ColorRGBA>(ColorHSLA(m_aUseCustomColors[4] ? m_aSkinPartColors[4] : 255)).Greyscale();

		m_aSkinPartColors[0] = color_cast<ColorHSLA>(BodyPartGrey.Blend(ColorBody)).Pack(DARKEST_LGT_7);
		m_aSkinPartColors[1] = color_cast<ColorHSLA>(color_cast<ColorRGBA>(ColorHSLA(m_aUseCustomColors[1] ? m_aSkinPartColors[1] : 255)).Greyscale(BodyPartGrey.r).Blend(ColorBody)).Pack(DARKEST_LGT_7, true);
		m_aSkinPartColors[2] = color_cast<ColorHSLA>(color_cast<ColorRGBA>(ColorHSLA(m_aUseCustomColors[2] ? m_aSkinPartColors[2] : 255)).Greyscale(BodyPartGrey.r).Blend(ColorBody)).Pack(DARKEST_LGT_7);
		m_aSkinPartColors[3] = color_cast<ColorHSLA>(color_cast<ColorRGBA>(ColorHSLA(m_aUseCustomColors[3] ? m_aSkinPartColors[3] : 255)).Greyscale(BodyPartGrey.r).Blend(ColorBody)).Pack(DARKEST_LGT_7);
		m_aSkinPartColors[4] = color_cast<ColorHSLA>(FeetPartGrey.Blend(ColorFeet)).Pack(DARKEST_LGT_7);
		m_aUseCustomColors[0] = true;
		m_aUseCustomColors[1] = true;
		m_aUseCustomColors[2] = true;
		m_aUseCustomColors[3] = true;
		m_aUseCustomColors[4] = true;
	}
}

void CTeeInfo::ColorFromSixup()
{
	m_UseCustomColor = true;
	m_ColorBody = ColorHSLA(m_aUseCustomColors[0] ? m_aSkinPartColors[0] : 255).UnclampLighting(DARKEST_LGT_7).Pack(ColorHSLA::DARKEST_LGT);
	m_ColorFeet = ColorHSLA(m_aUseCustomColors[4] ? m_aSkinPartColors[4] : 255).UnclampLighting(DARKEST_LGT_7).Pack(ColorHSLA::DARKEST_LGT);
}
