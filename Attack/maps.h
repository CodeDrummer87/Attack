#pragma once

#include "stage_01.h"
#include "stage_02.h"
#include "stage_03.h"
#include "stage_04.h"
#include "stage_05.h"
#include "stage_06.h"
#include "stage_07.h"
#include "stage_08.h"
#include "stage_09.h"
#include "stage_10.h"
#include "stage_11.h"
#include "stage_12.h"
#include "stage_13.h"
#include "stage_14.h"
#include "stage_15.h"
#include "stage_16.h"
#include "stage_17.h"
#include "stage_18.h"
#include "stage_19.h"
#include "stage_20.h"

vector<string*> maps {	FirstStage, SecondStage, ThirdStage, ForthStage, FifthStage,
						SixthStage, SeventhStage, EigthStage, NinthStage, TenthStage,
						EleventhStage, TwelfthStage, ThirteenthStage, FourteenthStage, FifteenthStage,
						SixteenthStage, SeventeenthStage, EighteenthStage, NineteenthStage, TwentiethStage  };

vector<int> mapsHeight = {  firstHeight, secondHeight, thirdHeight, forthHeight, fifthHeight,
							sixthHeight, seventhHeight, eigthHeight, ninthHeight, tenthHeight,
							eleventhHeight, twelfthHeight, thirteenthHeight, fourteenthHeight, fifteenthHeight,
							sixteenthHeight, seventeenthHeight, eighteenthHeight, nineteenthHeight, twentiethHeight  };

vector<int> mapsWidth = {	firstWidth, secondWidth, thirdWidth, forthWidth, fifthWidth,
							sixthWidth, seventhWidth, eigthWidth, ninthWidth, tenthWidth,
							eleventhWidth, twelfthWidth, thirteenthWidth, fourteenthWidth, fifteenthWidth,
							sixteenthWidth, seventeenthWidth, eighteenthWidth, nineteenthWidth, twentiethWidth  };

RectangleShape rectangle(Vector2f(32, 32));

void renderMap(string* map, RenderWindow &app, Animation &a, double time, int index)
{
	a.update(time, true, 1);

	for (int i = 0; i < mapsHeight[index]; i++)
		for (int j = 0; j < mapsWidth[index]; j++)
		{
			if (map[i][j] == 'W')
				a.sprite.setTextureRect(a.frames[(int)a.frame]);
			else if (map[i][j] == 'B')
				a.sprite.setTextureRect(IntRect(0, 32, 32, 32));
			else if (map[i][j] == 'b')
				a.sprite.setTextureRect(IntRect(96, 32, 32, 32));
			else if (map[i][j] == 'I')
				a.sprite.setTextureRect(IntRect(64, 0, 32, 32));
			else if (map[i][j] == 'S')
				a.sprite.setTextureRect(IntRect(0, 0, 32, 32));
			else if (map[i][j] == 's')
				a.sprite.setTextureRect(IntRect(32, 0, 32, 32));
			else
				continue;

			a.sprite.setPosition(float(j * 32), float(i * 32));
			app.draw(a.sprite);
		}
}

void drawForest(string* map, RenderWindow &app, Animation &a, int index)
{
	for (int i = 0; i < mapsHeight[index]; i++)
		for (int j = 0; j < mapsWidth[index]; j++)
		{
			if (map[i][j] == 'F')
			{
				a.sprite.setTextureRect(IntRect(32, 32, 32, 32));
				a.sprite.setPosition(float(j * 32), float(i * 32));
				app.draw(a.sprite);
			}
		}
}
