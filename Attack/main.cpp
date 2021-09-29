#include "Animation.h"
#include "maps.h"

#include "View.h"
#include "Entity.h"

//.:: temp code :::
bool isUpd = false;	//.:: for double click protection
//:::::::::::::::::

enum AppMode { OPTIONS, GAME, SCORING, ENDGAME };
AppMode mode = OPTIONS;

int main()
{
#pragma region Window settings

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int sizeX = GetSystemMetrics(SM_CXSCREEN);
	int sizeY = GetSystemMetrics(SM_CYSCREEN);

	if (sizeX != 1280 && sizeY != 1024)
	{
		sizeX = 1920;
		sizeY = 1080;
	}

#pragma endregion

#pragma region Texts | Images | Textures | Sounds | Animations

#pragma region Images

	Image iMap, iIcon;

	iMap.loadFromFile("source/images/map.png");
	iMap.createMaskFromColor(Color::White);
	iIcon.loadFromFile("source/images/sprites/attributes/icons/icons.png");
	iIcon.createMaskFromColor(Color::White);

#pragma endregion

#pragma region Sounds & Music

	//.:: For game start :::
	SoundBuffer startBuf;
	startBuf.loadFromFile("source/sounds/effects/start_game/start.ogg");
	Sound start(startBuf);

	SoundBuffer choiceBuf, screamBuf;
	choiceBuf.loadFromFile("source/sounds/effects/start_game/choose_number_of_players.ogg");
	screamBuf.loadFromFile("source/sounds/effects/start_game/scream.ogg");

	Sound *choice = new Sound(choiceBuf), *scream = new Sound(screamBuf);

	Music *main_theme = new Music();
	main_theme->openFromFile("source/sounds/music/main_theme.ogg");
	//::::::::::::::::::::::
	
#pragma endregion

#pragma region Textures

	Texture tMap, tIcon;

	tMap.loadFromImage(iMap);
	tIcon.loadFromImage(iIcon);

#pragma endregion

#pragma region Animations

	Animation map(tMap, 0, 64, 32, 32, 0.003, 4);
	Animation iconRepair(tIcon, 0, 0, 32, 32, 0.015, 22);
	Animation iconPreferment(tIcon, 0, 32, 32, 32, 0.015, 22);
	Animation iconCamera(tIcon, 0, 64, 32, 32, 0.015, 22);
	Animation iconAirStrike(tIcon, 0, 96, 32, 32, 0.015, 22);

	Animation icons[] = { iconRepair, iconPreferment, iconCamera, iconAirStrike };

#pragma endregion

#pragma endregion

#pragma region OPTIONS mode

	Font font_1, font_2;
	font_1.loadFromFile("source/fonts/KimberleyCYR_Black.otf");
	font_2.loadFromFile("source/fonts/lik_Ascent_2_starDom.otf");

	vector<Text*> optionsTextList;

	int attackSize, subDiv, tankFontSize;
	if (sizeX != 1280 && sizeY != 1024)
	{
		attackSize = 250;
		subDiv = 50;
		tankFontSize = 45;
	}
	else
	{
		attackSize = 200;
		subDiv = 45;
		tankFontSize = 36;
	}

	Text *attack = new Text("ATTACK", font_2, attackSize);
	attack->setFillColor(Color::Red);
	attack->setPosition((float)(sizeX / 2 - (sizeX / 2) / 1.5), (float)(sizeY / 2 - (sizeY / 2) / 1.5));
	optionsTextList.push_back(attack);

	Text *subdivision = new Text("Subdivision Formation", font_1, subDiv);
	subdivision->setFillColor(Color::Yellow);
	subdivision->setPosition((float)(sizeX / 2), (float)(sizeY / 2 - 100));
	optionsTextList.push_back(subdivision);

	Text *tank_1 = new Text("Red TANK", font_2, tankFontSize),
		*tank_2 = new Text("Yellow TANK", font_2, tankFontSize),
		*tank_3 = new Text("Magenta TANK", font_2, tankFontSize),
		*tank_4 = new Text("Cyan TANK", font_2, tankFontSize),
		*tank_5 = new Text("Hemo TANK", font_2, tankFontSize);

	tank_1->setFillColor(Color::Red);		tank_1->setPosition(sizeX / 2, sizeY / 2);			optionsTextList.push_back(tank_1);
	tank_2->setFillColor(Color::White);		tank_2->setPosition(sizeX / 2, sizeY / 2 + 70);		optionsTextList.push_back(tank_2);
	tank_3->setFillColor(Color::White);		tank_3->setPosition(sizeX / 2, sizeY / 2 + 140);	optionsTextList.push_back(tank_3);
	tank_4->setFillColor(Color::White);		tank_4->setPosition(sizeX / 2, sizeY / 2 + 210);	optionsTextList.push_back(tank_4);
	tank_5->setFillColor(Color::White);		tank_5->setPosition(sizeX / 2, sizeY / 2 + 280);	optionsTextList.push_back(tank_5);

	Text *programmer = new Text("code.drummer87@gmail.com", font_1, 17);
	programmer->setFillColor(Color::Red);
	programmer->setPosition(10, sizeY - 50);
	optionsTextList.push_back(programmer);

	Image iStar;
	iStar.loadFromFile("source/images/sprites/attributes/lighting_star.png");
	iStar.createMaskFromColor(Color::White);

	Texture tStar;
	tStar.loadFromImage(iStar);

	Animation *star = new Animation(tStar, 0, 0, 55, 45, 0.17, 9);
	star->sprite.setPosition(sizeX / 2 - 50, sizeY / 2 + 25);
	bool isVisibleStar = true;

#pragma endregion

#pragma region SCORING mode

	vector<Text*> scoringTextList;

	Text *header = new Text(" test Battle results", font_1, 50);
	header->setFillColor(Color::Yellow);
	header->setPosition(100.f, 100.f);
	scoringTextList.push_back(header);

#pragma endregion

	bool isGamePlay = true;
	int numberOfPlayers = 1;
	int index = 0;	//.:: for maps vector

	main_theme->setVolume(70.f);
	main_theme->play();

	int fadeOutTime = 0;	//.:: For foregroundTheme music
	float mainThemeVolume = 70.f;

	RenderWindow app(VideoMode(sizeX, sizeY), "Attack", Style::Fullscreen);
	app.setVerticalSyncEnabled(true);
	app.setMouseCursorVisible(false);
	app.setKeyRepeatEnabled(false);

	view.reset(FloatRect(0, 0, (float)sizeX, (float)sizeY));

	//.:: temporary code:::
	double viewPosX = sizeX / 2, viewPosY = mapsHeight[0] * 32 - sizeY / 2;
	//.::::::::::::::::::::

	Clock clock;

	Clock gameTimeClock;
	int gameTime = 0;

	if (isGamePlay)
	{
		while (app.isOpen())
		{
			double time = clock.getElapsedTime().asMicroseconds();
			clock.restart();

			time /= 1700;

#pragma region Fade out time of main_theme music

			if (mode == GAME)
			{
				gameTime = (int)(gameTimeClock.getElapsedTime().asSeconds());

				if (main_theme->getStatus() == SoundStream::Playing)
				{
					if (fadeOutTime != 0)
					{
						mainThemeVolume -= (float)gameTime;
						main_theme->setVolume(mainThemeVolume);
					}
					else
						fadeOutTime = gameTime + 5;

					if (gameTime >= fadeOutTime)
						main_theme->stop();
				}
			}

#pragma endregion

			Event event;
			while (app.pollEvent(event))
			{
				if (event.key.code == Keyboard::Escape)
				{
					isGamePlay = false;
					mode = ENDGAME;
					app.close();
					delete choice, star, scream;
				}

#pragma region OPTIONS mode

				if (mode == OPTIONS)
				{
					if (Keyboard::isKeyPressed(Keyboard::Enter))
					{
						if (numberOfPlayers >= 1)
						{
							mode = GAME;
							start.play();
						}

						choice->play();
					}

					if (Keyboard::isKeyPressed(Keyboard::Down))
					{
						if (numberOfPlayers <= 4)
						{
							choice->play();
							star->sprite.move(0, 70);
							++numberOfPlayers;

							if (numberOfPlayers >= 1)
							{
								isVisibleStar = true;
								tank_1->setFillColor(Color::Red);
							}
							if (numberOfPlayers >= 2)
								tank_2->setFillColor(Color::Yellow);
							if (numberOfPlayers >= 3)
								tank_3->setFillColor(Color::Magenta);
							if (numberOfPlayers >= 4)
								tank_4->setFillColor(Color::Cyan);
							if (numberOfPlayers == 5)
							{
								scream->play();
								tank_5->setFillColor(Color::Green);
							}
						}
					}

					if (Keyboard::isKeyPressed(Keyboard::Up))
					{
						if (numberOfPlayers >= 2)
						{
							choice->play();
							star->sprite.move(0, -70);
							--numberOfPlayers;

							if (numberOfPlayers <= 4)
								tank_5->setFillColor(Color::White);
							if (numberOfPlayers <= 3)
								tank_4->setFillColor(Color::White);
							if (numberOfPlayers <= 2)
								tank_3->setFillColor(Color::White);
							if (numberOfPlayers <= 1)
								tank_2->setFillColor(Color::White);
						}
					}
				}

#pragma endregion

#pragma region GAME mode

				if (mode == GAME)
				{
					//.:: temporary code :::
					if (Keyboard::isKeyPressed(Keyboard::N))
					{
						if (!isUpd)
						{
							isUpd = true;
							if (index + 1 != maps.size())
							{
								view.setCenter(float(sizeX / 2), float(sizeY / 2));
								mode = SCORING;
							}
						}
					}
				}

#pragma endregion

#pragma region SCORING mode

				if (mode == SCORING)
				{
					if (Keyboard::isKeyPressed(Keyboard::Space))
					{
						++index;
						isUpd = false;
						viewPosX = sizeX / 2;
						viewPosY = mapsHeight[0] * 32 - sizeY / 2;
						mode = GAME;
					}
				}

#pragma endregion

			}

			if (mode == GAME)
			{
				//.:: Temporary code: view moving :::
				if (Keyboard::isKeyPressed(Keyboard::Up))
				{
					if (viewPosY > sizeY/2)
						viewPosY -= 10;
				}

				if (Keyboard::isKeyPressed(Keyboard::Down))
				{
					if (viewPosY < mapsHeight[0]*32-sizeY/2)
						viewPosY += 10;
				}
				//:::::::::::::::::::::::

				setViewCoordinates(sizeX, sizeY, viewPosX, viewPosY, index);
				app.setView(view);
			}

			if (mode == SCORING)
				app.setView(view);
			
			if (mode == OPTIONS)
				star->update(1, true, 0);

			app.clear();
#pragma region GAME mode

			if (mode == GAME)
			{
				//.:: map rendering :::
				renderMap(maps[index], app, map, time, index);
				drawForestAndIcons(maps[index], app, map, icons, time, index);
			}

#pragma endregion

#pragma region OPTIONS mode

			if (mode == OPTIONS)
			{
				for (auto t : optionsTextList)
					app.draw(*t);
				if (isVisibleStar)
					app.draw(star->sprite);
			}

#pragma endregion

#pragma region SCORING mode

			if (mode == SCORING)
			{
				for (auto t : scoringTextList)
					app.draw(*t);
			}

#pragma endregion

			app.display();
		}
	}

	return 0;
}
