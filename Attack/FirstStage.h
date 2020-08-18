#pragma once

#include <SFML\Graphics.hpp>

using namespace sf;

const int H = 119;	// 34(screen height) * 3 = 102 + 17 (half-screen height) = 119
const int W = 61;

String FirstStage[H] = 
{
	"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
	"BFFFFFFWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWFFFFFFB",
	"BFFFFFWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWFFFFFB",
	"BFFFF                                                   FFFFB",
	"BFFF                                                     FFFB",
	"BFF                                                       FFB",
	"BF                                                         FB",
	"B                                                           B",
	"B                                                           B",
	"B                                                           B",
	"B                                                           B",
	"B                                                           B",
	"B                                                           B",
	"B                                                           B",
	"B                                                           B",
	"B        WWWWWWWWW                        WWWWWWWWWW        B",
	"B        WWWWWWWWW                        WWWWWWWWWW        B",
	"B        WWWWWWWWW                        WWWWWWWWWW        B",
	"B        WWWWWWWWW                        WWWWWWWWWW        B",
	"B          bbbb                              bbbb           B",
	"B        bbbbbbbb                          bbbbbbbb         B",
	"BbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbB",
	"B      bbbbbbbbbbbb       WWWWWWWWW      bbbbbbbbbbbb       B",
	"B        bbbbbbbb         WWWWWWWWW        bbbbbbbb         B",
	"B          bbbb                              bbbb           B",
	"B                                                           B",
	"B                                                           B",
	"B       BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB       B",
	"B       RBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB        B",
	"B               BB            B           BB                B",
	"B               BB                        BB                B",
	"B               BB                                          B",
	"BWWWWWWWW                BB       BB                WWWWWWWWB",
	"BWWWWWWWW                BB       BB                WWWWWWWWB",
	"BBBBBBBBBBBBBBBBBBBBBBBBBBB       BBBBBBBBBBBBBBBBBBBBWWWWWWB",
	"BBBBBBBBBBBBBBBBBBBBBBBBBBB       BBBBBBBBBBBBBBBBBBBBWWWWWWB",
	"BFFFFFFFFFFFFFFFFFFFFFFFF           bb      bb     bb      UB",
	"BFFFFFFFFFFFFFFFFFFFFFFF            bb      bb     bb       B",
	"BFFFFFFFFFFFFFFFFFFFFFF             bb      bb     bb       B",
	"BFFFFFFFFFFFFFFFFFFFFF              bb      bb     bb       B",
	"BFFFFFFFFFFFFFFFFFWWWbbbbbbbbbBBBBBBBBBBBBBBBBBBBBBBBBWWWWWWB",
	"BFFFFFFFFFFFFFFFFFWWW           bb      bb      bb          B",
	"BFFFFFFFFFFFFFFFFFWWW           bb      bb      bb          B",
	"BFFFFFFFFFFFFFFFFFWWW           bb      bb      bb          B",
	"BWWWWWFFFFFFBWWWWWWW            bb      bb      bb       R  B",
	"BWWWWWFFFFFFBWW          BBBBBBBBBBBBBBBBBBBBBBBBBbbbbbbbbbbB",
	"BWWWWWFFFFFFBWW         WWWWWWBbbbbbbbbbbbFFFFFFFFbbbbbbbbbbB",
	"BWWWWWFFFFFFBWW        WWWWWWWBbbbbbbbbbbbFFFFFFFFbbbbbbbbbbB",
	"BWWWWWFFFFFFBWW       WWWBBBBBBbbbbbbbbbbbFFFFFFFFbbbbbbbbbbB",
	"BbbbbbFFFFFFBWW      WWWWBBBBBBRbbbbbbbbbbBBBBBBBBBBBBBBBBBBB",
	"BUbbbbFFFFFFBWW     WWWWWBBBBBBbbbbbbbbbbb                  B",
	"BWWWWWFFFFFFBWW     WWWWWBBBBBBbbbbbbbbbbb                  B",
	"BWWWWWFFFFFFBWW     WWWWWBBBBBBbbbbbbbbbbb                  B",
	"BFFFFFFFFFFFBWW     WBBBBBBBBBBBBBBBBBBBBBBBBBBB            B",
	"BFFFFFFFFFFFBFFFFFFFFFFFFFFFFFFWWWWWWFFFFFFFBBFFFFFFbbbbbbbbB",
	"BFFFFFFFFFFFBFFFFFFFFFFFFFFFFFFWWWWWWFFFFFFFBBFFFFFFbbbbbbbbB",
	"BFFFFFWWWWBBBBBB               WWW          BB              B",
	"BFFFFFWWWW                     WWW          BB              B",
	"BFFFFFBBBB                     WWW          BB              B",
	"BFFFFFBBBB        R            BWB                  bbbbbbbbB",
	"BFFFFFBBBB                  bbBBBBBbb            R  bbbbbbbbB",
	"BFFFFFBBBB                  bBBBBBBBb                       B",
	"BFFFFFFFFFFFFFFFFFFFFFFFFFFFBBBBBBBBB                       B",
	"BFFFFFFFFFFFFFFFFFFFFFFFFFFFBB     BB                       B",
	"BFFFFFFFFFFFFFFFFFFFFFFFFFFFBB  U  BBFFFFFFFFFFFFFFFFFFFFFFFB",
	"BBBBWWWWWWWWWWWWBBBBBBFFFFFFBB     BBFFFFFFFFFFFFFFFFFFFFFFFB",
	"BBBBWWWWWWWWWWWWBBBBBBFFFFFFBB     BB      A                B",
	"BBBBBBBBBBBBBBBBBBBBBBFFFFFFBB     BB                       B",
	"BBBBBBBBBBBBBBBBBBBBBBFFFFFFBB     BB      BBBBBBBBbbbbbbbbbB",
	"BBBBBBBBBBBBBBBBBBBBBBFFFFFFBB     BB      BBBBBBBBbbbbbbbbbB",
	"Bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb              bbbbbbbbbB",
	"Bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb              bbbbbbbbbB",
	"B                                                  bbbbbbbbbB",
	"B                                                  bbbbbbbbbB",
	"B                                                  bbbbbbbbbB",
	"BFFFF                 BBBB         BBBB            bbbbbbbbbB",
	"BFFFFFFFF    bbbb     BBBB         BBBB            bbbbbbbbbB",
	"BFFFFFFFFFFFFbbbb     bbbb         bbbb                 bbbbB",
	"BFFFFFFFFFFFFbbbbFFFFFFFFFFFFFFFFFFFFFFFFFFbbbb      U  bbbbB",
	"BFFFFFFFFFFFFbbbbFFFFFFFFFFFFFFFFFFFFFFFFFFbbbb         bbbbB",
	"BFFFFFFFFFFFFWWWWWW   BBBB         BBBB                 bbbbB",
	"BFFFFFFFF    WWWWWW   BBBB    R    BBBB                 WWWWB",
	"BFFFF                     BB     BB                     WWWWB",
	"B                         BBBBBBBBBbbbbbbbbbbbbbbbbbWWWWWWWWB",
	"B     bbbbFFFFbbbbbbb     bbbbbbbbb                 WWWWWWWWB",
	"B     bbbbFFFFbbbbbbb      bbbbbbb                  FFFFFWWWB",
	"B     bbbb      WWWW        bbbbb                   FFFFFFFFB",
	"B     bbbb      WWWW         bbb                            B",
	"B     bbbb      WWWW          b       bbbbbbbbbbbbbb        B",
	"B     bbbb                            bbbbbbbbbbbbbb        B",
	"B     bbbb                                                  B",
	"B                                                           B",
	"B   BBBBBBBBBB     WWWWWWWWWWWWWWWWWWWWWWW     BBBBBBBBBB   B",
	"BbbbWWWWFFFFFF     WWWWWWWWWWWWWWWWWWWWWWW     FFFFFFWWWWbbbB",
	"BbbbWWWWFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFWWWWbbbB",
	"BbbbWWWWbbbbFFFFFF        bbbbbbb          FFFFFFbbbbWWWWbbbB",
	"BbbbWWWWbbbbFFFFFF   R    bbbUbbb    R     FFFFFFbbbbWWWWbbbB",
	"BbbbWWWWbbbWWWWWWWbb      bbbbbbb        bbWWWWWWWbbbWWWWbbbB",
	"BbbbWWWWbUbWWWWWWWbb      bbbbbbb        bbWWWWWWWbUbWWWWbbbB",
	"B                            B                              B",
	"B                            B                              B",
	"B            BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB             B",
	"B                                                           B",
	"B                            C                              B",
	"B                                                           B",
	"BWWWWWWWWWWWWWWWWWWWWWWWWWWFFFFFFWWWWWWWWWWWWWWWWWWWWWWWWWWWB",
	"BWWWWWWWWWWWWWWWWWWWWWWWWWWFFFFFFWWWWWWWWWWWWWWWWWWWWWWWWWWWB",
	"BBBBBBBBBBBBBBBBBBBBBBBBBBBFFFFFFBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
	"BBBBBBBBBBBWWWWWWWWWWWWWWWWFFFFFFWWWWWWWWWWWWWWWWWBBBBBBBBBBB",
	"BBBBBBBBBBWWWWWWWWWWWWWWWWWFFFFFFWWWWWWWWWWWWWWWWWWBBBBBBBBBB",
	"BBBBBBBBBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBBBBBBBBB",
	"BBBBBBBBFFFFFFFFFbbbbbbbbbbbbbbbbbbbbbbbbbbbFFFFFFFFFBBBBBBBB",
	"BBBBBBBFFFFFFFFbbbbb                     bbbbbFFFFFFFFBBBBBBB",
	"BBBBBBFFFFFFFbbbbbbb                     bbbbbbbFFFFFFFBBBBBB",
	"BBBBBFFFFFFFbbbbbb                         bbbbbbFFFFFFFBBBBB",
	"BBBBFFFFFFFbbbbbbb                         bbbbbbbFFFFFFFBBBB",
	"BBBFFFFFFFbbbbbb                             bbbbbAFFFFFFFBBB",
	"BBFFFFFFFbbbbbbb                             bbbbbbbFFFFFFFBB",
	"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"
};

RectangleShape rectangle(Vector2f(32, 32));

void drawMap(String map[H], RenderWindow &app, Animation &a, double time)
{
	a.update(time, true, 1);

	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
		{
			if (map[i][j] == 'W')
				a.sprite.setTextureRect(a.frames[(int)a.frame]);
			else if (map[i][j] == 'B')
				a.sprite.setTextureRect(IntRect(0, 32, 32, 32));
			else if (map[i][j] == 'b')
				a.sprite.setTextureRect(IntRect(96, 32, 32, 32));
			else
				continue;

			a.sprite.setPosition(float(j * 32), float(i * 32));
			app.draw(a.sprite);
		}
}

void drawForestAndIcons(String map[H], RenderWindow &app, Animation &a, Animation icons[], double time)
{
	for (int i = 0; i < sizeof(icons); i++)
		icons[i].update(time, true, 1);

	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
		{
			if (map[i][j] == 'F')
			{
				a.sprite.setTextureRect(IntRect(32, 32, 32, 32));
				a.sprite.setPosition(float(j * 32), float(i * 32));
				app.draw(a.sprite);
			}

			if (map[i][j] == 'R')
			{
				icons[0].sprite.setTextureRect(icons[0].frames[(int)icons[0].frame]);
				icons[0].sprite.setPosition(float(j * 32), float(i * 32));
				app.draw(icons[0].sprite);
			}

			if (map[i][j] == 'U')
			{
				icons[1].sprite.setTextureRect(icons[1].frames[(int)icons[1].frame]);
				icons[1].sprite.setPosition(float(j * 32), float(i * 32));
				app.draw(icons[1].sprite);
			}

			if (map[i][j] == 'C')
			{
				icons[2].sprite.setTextureRect(icons[2].frames[(int)icons[2].frame]);
				icons[2].sprite.setPosition(float(j * 32), float(i * 32));
				app.draw(icons[2].sprite);
			}

			if (map[i][j] == 'A')
			{
				icons[3].sprite.setTextureRect(icons[3].frames[(int)icons[3].frame]);
				icons[3].sprite.setPosition(float(j * 32), float(i * 32));
				app.draw(icons[3].sprite);
			}
		}
}