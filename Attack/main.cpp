#include "Animation.h"
#include "maps.h"

#include "View.h"
#include "Entity.h"

#include "Player.h"
#include "Shell.h"

#include "Smoke.h"

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

	Image iMap, iIcon,
		iBurgundyTank, iYellowTank, iPurpleTank, iCyanTank, iHemoTank;

	iMap.loadFromFile("source/images/map.png");
	iMap.createMaskFromColor(Color::White);
	iIcon.loadFromFile("source/images/sprites/attributes/icons/icons.png");
	iIcon.createMaskFromColor(Color::White);

	iBurgundyTank.loadFromFile("source/images/sprites/models/tanks/players/burgundyTank.png");
	iBurgundyTank.createMaskFromColor(Color::White);
	iYellowTank.loadFromFile("source/images/sprites/models/tanks/players/yellowTank.png");
	iYellowTank.createMaskFromColor(Color::White);
	iPurpleTank.loadFromFile("source/images/sprites/models/tanks/players/purpleTank.png");
	iPurpleTank.createMaskFromColor(Color::White);
	iCyanTank.loadFromFile("source/images/sprites/models/tanks/players/lightBlueTank.png");
	iCyanTank.createMaskFromColor(Color::White);
	iHemoTank.loadFromFile("source/images/sprites/models/tanks/players/hemoTank.png");
	iHemoTank.createMaskFromColor(Color::White);

#pragma endregion

#pragma region Textures

	Texture tMap, tIcon, bTank, yTank, pTank, cTank, hTank, tTankRound, tShell, tShellExp,
		tSmoke;

	tMap.loadFromImage(iMap);
	tIcon.loadFromImage(iIcon);

	bTank.loadFromImage(iBurgundyTank);
	yTank.loadFromImage(iYellowTank);
	pTank.loadFromImage(iPurpleTank);
	cTank.loadFromImage(iCyanTank);
	hTank.loadFromImage(iHemoTank);

	tTankRound.loadFromFile("source/images/sprites/explosions/round.png");
	tShell.loadFromFile("source/images/sprites/models/other/shell.png");
	tShellExp.loadFromFile("source/images/sprites/explosions/shell_explosion.png");

	tSmoke.loadFromFile("source/images/sprites/explosions/smoke.png");

#pragma endregion

#pragma region Sounds & Music

#pragma region Sounds & music for start game

	SoundBuffer startBuf;
	startBuf.loadFromFile("source/sounds/effects/start_game/start.flac");
	Sound start(startBuf);

	SoundBuffer choiceBuf, screamBuf;
	choiceBuf.loadFromFile("source/sounds/effects/start_game/choose_number_of_players.flac");
	screamBuf.loadFromFile("source/sounds/effects/start_game/scream.flac");

	Sound *choice = new Sound(choiceBuf), *scream = new Sound(screamBuf);

	Music *main_theme = new Music();
	main_theme->openFromFile("source/sounds/music/main_theme.flac");

#pragma endregion

	SoundBuffer bTankBuf, yTankBuf, pTankBuf, tankExpBuf, burgTankRoundBuf, yelTankRoundBuf, purpTankRoundBuf, shellExpBuf;

	bTankBuf.loadFromFile("source/sounds/tank/movement/move_1.flac");
	yTankBuf.loadFromFile("source/sounds/tank/movement/move_2.flac");
	pTankBuf.loadFromFile("source/sounds/tank/movement/move_3.flac");
	tankExpBuf.loadFromFile("source/sounds/tank/explosion/tank_explosion.flac");
	burgTankRoundBuf.loadFromFile("source/sounds/tank/round/burgundy_tank_round.flac");
	purpTankRoundBuf.loadFromFile("source/sounds/tank/round/purple_tank_round.flac");
	yelTankRoundBuf.loadFromFile("source/sounds/tank/round/yellow_tank_round.flac");
	shellExpBuf.loadFromFile("source/sounds/explosion/shell_explosion.flac");

#pragma endregion

#pragma region Animations

	Animation map(tMap, 0, 64, 32, 32, 0.003, 4);
	Animation iconRepair(tIcon, 0, 0, 32, 32, 0.015, 22);
	Animation iconPreferment(tIcon, 0, 32, 32, 32, 0.015, 22);
	Animation iconCamera(tIcon, 0, 64, 32, 32, 0.015, 22);
	Animation iconAirStrike(tIcon, 0, 96, 32, 32, 0.015, 22);

	Animation icons[] = { iconRepair, iconPreferment, iconCamera, iconAirStrike };

	Animation aBurgTank(bTank, bTankBuf, 0, 0, 64, 64, 0.016, 2);
	Animation aExpBurgTank(bTank, tankExpBuf, 0, 64, 64, 64, 0.01, 12);
	
	Animation aYellowTank(yTank, yTankBuf, 0, 0, 64, 64, 0.016, 2);
	Animation aExpYellowTank(yTank, tankExpBuf, 0, 64, 64, 64, 0.01, 12);

	Animation aPurpTank(pTank, pTankBuf, 0, 0, 64, 64, 0.016, 2);
	Animation aExpPurpTank(pTank, tankExpBuf, 0, 64, 64, 64, 0.01, 12);

	Animation aCyanTank(cTank, yTankBuf, 0, 0, 64, 64, 0.016, 2);
	Animation aExpCyanTank(cTank, tankExpBuf, 0, 64, 64, 64, 0.01, 12);

	Animation aHemoTank(hTank, bTankBuf, 0, 0, 64, 64, 0.016, 2);
	Animation aExpHemoTank(hTank, tankExpBuf, 0, 64, 64, 64, 0.01, 12);

	Animation aBurgTankRound(tTankRound, burgTankRoundBuf, 0, 0, 40, 36, 0.015, 8);
	Animation aYelTankRound(tTankRound, yelTankRoundBuf, 0, 0, 40, 36, 0.015, 8);
	Animation aPurpTankRound(tTankRound, purpTankRoundBuf, 0, 0, 40, 36, 0.015, 8);

	Animation aShell(tShell, 0, 0, 64, 64, 0.01, 2);
	Animation aShellExp(tShellExp, shellExpBuf, 0, 0, 64, 64, 0.017, 7);
	Animation aSmoke(tSmoke, 0, 0, 64, 64, 0.008, 5);

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
	//.:: For start and end battle :::
	bool isStartGame = true;
	bool isStartBattle = true;
	bool battleIsOver = false;
	int lastSecondsOfChapter = 0;
	//::::::::::::::::::::::

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

	vector<Entity*> entities;
	vector<Player*> team;

	//.:: Players tanks start position variables :::
	int a1, a2, b1, b2, c1, c2, d1, d2, e1, e2;
	a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = 0;

	Clock clock;

	Clock gameTimeClock;
	int gameTime = 0;
	double time = 0.0;

	if (isGamePlay)
	{
		while (app.isOpen())
		{
			time = clock.getElapsedTime().asMicroseconds();
			clock.restart();

			time /= 1700;

#pragma region Fade out time of main_theme music

			if (mode == GAME && main_theme->getStatus() == SoundStream::Playing)
			{
				gameTime = (int)(gameTimeClock.getElapsedTime().asSeconds());

				if (main_theme->getStatus() == SoundStream::Playing)
				{
					if (fadeOutTime != 0)
					{
						mainThemeVolume -= 0.2f;
						main_theme->setVolume(mainThemeVolume = mainThemeVolume > 0.f ? mainThemeVolume : 0.f);
						if (scream->getStatus() == SoundStream::Playing)
							scream->setVolume(mainThemeVolume = mainThemeVolume > 0.f ? mainThemeVolume : 0.f);
					}
					else
						fadeOutTime = gameTime + 7;

					if (gameTime >= fadeOutTime)
						main_theme->stop();
				}
			}

#pragma endregion

#pragma region Set players start position before battle

			if (mode == SCORING && index > 0 && isStartBattle)
			{
				isStartBattle = false;
				switch (numberOfPlayers)
				{
				case 1: a1 = 950; a2 = mapsHeight[index] * 32 - 126;
					team[0]->setStartPosition(a1, a2);
					break;
				case 2: a1 = 870; a2 = mapsHeight[index] * 32 - 126;
					b1 = 1030; b2 = mapsHeight[index] * 32 - 126;
					team[0]->setStartPosition(a1, a2);
					team[1]->setStartPosition(b1, b2);
					break;
				case 3: a1 = 870; a2 = mapsHeight[index] * 32 - 126;
					b1 = 950; b2 = mapsHeight[index] * 32 - 176;
					c1 = 1030; c2 = mapsHeight[index] * 32 - 126;
					team[0]->setStartPosition(a1, a2);
					team[1]->setStartPosition(b1, b2);
					team[2]->setStartPosition(c1, c2);
					break;
				case 4: a1 = 810; a2 = mapsHeight[index] * 32 - 126;
					b1 = 890; b2 = mapsHeight[index] * 32 - 176;
					c1 = 1010; c2 = mapsHeight[index] * 32 - 176;
					d1 = 1090; d2 = mapsHeight[index] * 32 - 126;
					team[0]->setStartPosition(a1, a2);
					team[1]->setStartPosition(b1, b2);
					team[2]->setStartPosition(c1, c2);
					team[3]->setStartPosition(d1, d2);
					break;
				case 5: a1 = 790; a2 = mapsHeight[index] * 32 - 76;		
					b1 = 870; b2 = mapsHeight[index] * 32 - 126;		
					c1 = 950; c2 = mapsHeight[index] * 32 - 176;
					d1 = 1030; d2 = mapsHeight[index] * 32 - 126;
					e1 = 1110; e2 = mapsHeight[index] * 32 - 76;
					team[0]->setStartPosition(a1, a2);
					team[1]->setStartPosition(b1, b2);
					team[2]->setStartPosition(c1, c2);
					team[3]->setStartPosition(d1, d2);
					team[4]->setStartPosition(e1, e2);
					break;
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
					if (isStartGame)
					{
						if (event.type == Event::KeyReleased && event.key.code == Keyboard::Enter)
						{
							if (numberOfPlayers >= 1)
							{
								switch (numberOfPlayers)
								{
								case 1: a1 = 950; a2 = mapsHeight[0] * 32 - 126;
									break;
								case 2: a1 = 870; a2 = mapsHeight[0] * 32 - 126;
									b1 = 1030; b2 = mapsHeight[0] * 32 - 126;
									break;
								case 3: a1 = 870; a2 = mapsHeight[0] * 32 - 126;
									b1 = 950; b2 = mapsHeight[0] * 32 - 176;
									c1 = 1030; c2 = mapsHeight[0] * 32 - 126;
									break;
								case 4: a1 = 810; a2 = mapsHeight[0] * 32 - 126;
									b1 = 890; b2 = mapsHeight[0] * 32 - 176;
									c1 = 1010; c2 = mapsHeight[0] * 32 - 176;
									d1 = 1090; d2 = mapsHeight[0] * 32 - 126;
									break;
								case 5: a1 = 790; a2 = mapsHeight[0] * 32 - 76;
									b1 = 870; b2 = mapsHeight[0] * 32 - 126;
									c1 = 950; c2 = mapsHeight[0] * 32 - 176;
									d1 = 1030; d2 = mapsHeight[0] * 32 - 126;
									e1 = 1110; e2 = mapsHeight[0] * 32 - 76;
									break;
								}

								for (int i = 0; i < numberOfPlayers; i++)
								{
									Player *player;
									switch (i)
									{
									case 0: player = new Player(aBurgTank, a1, a2, "player", 1, true, aExpBurgTank, "players", 1); break;
									case 1: player = new Player(aYellowTank, b1, b2, "player", 1, true, aExpYellowTank, "players", 1); break;
									case 2: player = new Player(aPurpTank, c1, c2, "player", 1, true, aExpPurpTank, "players", 1); break;
									case 3: player = new Player(aCyanTank, d1, d2, "player", 1, true, aExpCyanTank, "players", 1); break;
									case 4: player = new Player(aHemoTank, e1, e2, "player", 1, true, aExpHemoTank, "players", 1); break;
									}

									team.push_back(player);
									entities.push_back(player);
								}

								mode = GAME;
								start.play();
							}

							isStartGame = false;
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
								isStartBattle = true;
								++index;
							}
						}
					}

#pragma region Tank rounds
		
					if (event.type == Event::KeyPressed && !battleIsOver)
					{
						Player *currentPlayer = NULL;
						Animation roundAnimation;

						if (event.key.code == Keyboard::LControl)
						{
							currentPlayer = team[0];
							roundAnimation = aBurgTankRound;
						}
						
						if (numberOfPlayers > 1 && event.key.code == Keyboard::Space)
						{
							currentPlayer = team[1];
							roundAnimation = aYelTankRound;
						}
						if (numberOfPlayers > 2 && event.key.code == Keyboard::Enter)
						{
							currentPlayer = team[2];
							roundAnimation = aPurpTankRound;
						}
						if (numberOfPlayers > 3 && event.key.code == Keyboard::RControl)
						{
							currentPlayer = team[3];
							roundAnimation = aYelTankRound;
						}
						if (numberOfPlayers > 4 && event.key.code == Keyboard::Numpad7)
						{
							currentPlayer = team[4];
							roundAnimation = aBurgTankRound;
						}
						if (currentPlayer != NULL && currentPlayer->status != DEAD)
						{
							if (currentPlayer->isShot)
							{
								currentPlayer->isShot = false;

								Smoke *round = new Smoke(roundAnimation, currentPlayer, "explosion");
								Shell *shell = new Shell(aShell, aShellExp, currentPlayer);
								entities.push_back(round);
								entities.push_back(shell);
							}
						}
					}

#pragma endregion
				}

#pragma endregion

#pragma region SCORING mode

				if (mode == SCORING)
				{
					if (Keyboard::isKeyPressed(Keyboard::Space))
					{
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
#pragma region Players control

				if (!battleIsOver)
				{
#pragma region First Player control

					if (team[0]->status != DEAD)
					{
						if (Joystick::isConnected(0))
						{
							double x = Joystick::getAxisPosition(0, Joystick::X);
							double y = Joystick::getAxisPosition(0, Joystick::Y);
							if (x == -100)
							{
								team[0]->accelerate(4, -0.09 * time);
							}
							else if (x == 100)
							{
								team[0]->accelerate(2, 0.09 * time);
							}
							else if (y == -100)
							{
								team[0]->accelerate(1, -0.09 * time);
							}
							else if (y == 100)
							{
								team[0]->accelerate(3, 0.09 * time);
							}
							else
								team[0]->isPlayAnimation = false;

							if (Joystick::isButtonPressed(0, 0) || Joystick::isButtonPressed(0, 3))
							{
								if (team[0]->status != DEAD && team[0]->isShot)
								{
									team[0]->isShot = false;

									Smoke *round = new Smoke(aBurgTankRound, team[0], "explosion");
									Shell *shell = new Shell(aShell, aShellExp, team[0]);
									entities.push_back(round);
									entities.push_back(shell);
								}
							}
						}
						else
						{
							if (Keyboard::isKeyPressed(Keyboard::W))
							{
								team[0]->accelerate(1, -0.09 * time);
							}
							else if (Keyboard::isKeyPressed(Keyboard::D))
							{
								team[0]->accelerate(2, 0.09 * time);
							}
							else if (Keyboard::isKeyPressed(Keyboard::S))
							{
								team[0]->accelerate(3, 0.09 * time);
							}
							else if (Keyboard::isKeyPressed(Keyboard::A))
							{
								team[0]->accelerate(4, -0.09 * time);
							}
							else team[0]->isPlayAnimation = false;
						}
					}

#pragma endregion

#pragma region Second Player control

					if (numberOfPlayers >= 2)
					{
						if (team[1]->status != DEAD)
						{
							if (Joystick::isConnected(1))
							{
								double x = Joystick::getAxisPosition(1, Joystick::X);
								double y = Joystick::getAxisPosition(1, Joystick::Y);
								if (x == -100)
								{
									team[1]->accelerate(4, -0.09 * time);
								}
								else if (x == 100)
								{
									team[1]->accelerate(2, 0.09 * time);
								}
								else if (y == -100)
								{
									team[1]->accelerate(1, -0.09 * time);
								}
								else if (y == 100)
								{
									team[1]->accelerate(3, 0.09 * time);
								}
								else
									team[1]->isPlayAnimation = false;

								if (Joystick::isButtonPressed(1, 0) || Joystick::isButtonPressed(1, 3))
								{
									if (team[1]->status != DEAD && team[1]->isShot)
									{
										team[1]->isShot = false;

										Smoke *round = new Smoke(aYelTankRound, team[1], "explosion");
										Shell *shell = new Shell(aShell, aShellExp, team[1]);
										entities.push_back(round);
										entities.push_back(shell);
									}
								}
							}
							else
							{
								if (Keyboard::isKeyPressed(Keyboard::T))
								{
									team[1]->accelerate(1, -0.09 * time);
								}
								else if (Keyboard::isKeyPressed(Keyboard::H))
								{
									team[1]->accelerate(2, 0.09 * time);
								}
								else if (Keyboard::isKeyPressed(Keyboard::G))
								{
									team[1]->accelerate(3, 0.09 * time);
								}
								else if (Keyboard::isKeyPressed(Keyboard::F))
								{
									team[1]->accelerate(4, -0.09 * time);
								}
								else team[1]->isPlayAnimation = false;
							}
						}
					}

#pragma endregion

#pragma region Third Player control

					if (numberOfPlayers >= 3)
					{
						if (team[2]->status != DEAD)
						{
							if (Joystick::isConnected(2))
							{
								double x = Joystick::getAxisPosition(2, Joystick::X);
								double y = Joystick::getAxisPosition(2, Joystick::Y);
								if (x == -100)
								{
									team[2]->accelerate(4, -0.09 * time);
								}
								else if (x == 100)
								{
									team[2]->accelerate(2, 0.09 * time);
								}
								else if (y == -100)
								{
									team[2]->accelerate(1, -0.09 * time);
								}
								else if (y == 100)
								{
									team[2]->accelerate(3, 0.09 * time);
								}
								else
									team[2]->isPlayAnimation = false;

								if (Joystick::isButtonPressed(2, 0) || Joystick::isButtonPressed(2, 3))
								{
									if (team[2]->status != DEAD && team[2]->isShot)
									{
										team[2]->isShot = false;

										Smoke *round = new Smoke(aPurpTankRound, team[2], "explosion");
										Shell *shell = new Shell(aShell, aShellExp, team[2]);
										entities.push_back(round);
										entities.push_back(shell);
									}
								}
							}
							else
							{
								if (Keyboard::isKeyPressed(Keyboard::I))
								{
									team[2]->accelerate(1, -0.09 * time);
								}
								else if (Keyboard::isKeyPressed(Keyboard::L))
								{
									team[2]->accelerate(2, 0.09 * time);
								}
								else if (Keyboard::isKeyPressed(Keyboard::K))
								{
									team[2]->accelerate(3, 0.09 * time);
								}
								else if (Keyboard::isKeyPressed(Keyboard::J))
								{
									team[2]->accelerate(4, -0.09 * time);
								}
								else team[2]->isPlayAnimation = false;
							}
						}
					}

#pragma endregion

#pragma region Forth Player control

					if (numberOfPlayers >= 4)
					{
						if (team[3]->status != DEAD)
						{
							if (Joystick::isConnected(3))
							{
								double x = Joystick::getAxisPosition(3, Joystick::X);
								double y = Joystick::getAxisPosition(3, Joystick::Y);
								if (x == -100)
								{
									team[3]->accelerate(4, -0.09 * time);
								}
								else if (x == 100)
								{
									team[3]->accelerate(2, 0.09 * time);
								}
								else if (y == -100)
								{
									team[3]->accelerate(1, -0.09 * time);
								}
								else if (y == 100)
								{
									team[3]->accelerate(3, 0.09 * time);
								}
								else
									team[3]->isPlayAnimation = false;

								if (Joystick::isButtonPressed(3, 0) || Joystick::isButtonPressed(3, 3))
								{
									if (team[3]->status != DEAD && team[3]->isShot)
									{
										team[3]->isShot = false;

										Smoke *round = new Smoke(aYelTankRound, team[3], "explosion");
										Shell *shell = new Shell(aShell, aShellExp, team[3]);
										entities.push_back(round);
										entities.push_back(shell);
									}
								}
							}
							else
							{
								if (Keyboard::isKeyPressed(Keyboard::Up))
								{
									team[3]->accelerate(1, -0.09 * time);
								}
								else if (Keyboard::isKeyPressed(Keyboard::Right))
								{
									team[3]->accelerate(2, 0.09 * time);
								}
								else if (Keyboard::isKeyPressed(Keyboard::Down))
								{
									team[3]->accelerate(3, 0.09 * time);
								}
								else if (Keyboard::isKeyPressed(Keyboard::Left))
								{
									team[3]->accelerate(4, -0.09 * time);
								}
								else team[3]->isPlayAnimation = false;
							}
						}
					}

#pragma endregion

#pragma region Fifth Player control

					if (numberOfPlayers == 5)
					{
						if (team[4]->status != DEAD)
						{
							if (Joystick::isConnected(4))
							{
								double x = Joystick::getAxisPosition(4, Joystick::X);
								double y = Joystick::getAxisPosition(4, Joystick::Y);
								if (x == -100)
								{
									team[4]->accelerate(4, -0.09 * time);
								}
								else if (x == 100)
								{
									team[4]->accelerate(2, 0.09 * time);
								}
								else if (y == -100)
								{
									team[4]->accelerate(1, -0.09 * time);
								}
								else if (y == 100)
								{
									team[4]->accelerate(3, 0.09 * time);
								}
								else
									team[4]->isPlayAnimation = false;

								if (Joystick::isButtonPressed(4, 0) || Joystick::isButtonPressed(4, 3))
								{
									if (team[4]->status != DEAD && team[4]->isShot)
									{
										team[4]->isShot = false;

										Smoke *round = new Smoke(aBurgTankRound, team[4], "explosion");
										Shell *shell = new Shell(aShell, aShellExp, team[4]);
										entities.push_back(round);
										entities.push_back(shell);
									}
								}
							}
							else
							{
								if (Keyboard::isKeyPressed(Keyboard::Numpad8))
								{
									team[4]->accelerate(1, -0.09 * time);
								}
								else if (Keyboard::isKeyPressed(Keyboard::Numpad6))
								{
									team[4]->accelerate(2, 0.09 * time);
								}
								else if (Keyboard::isKeyPressed(Keyboard::Numpad5))
								{
									team[4]->accelerate(3, 0.09 * time);
								}
								else if (Keyboard::isKeyPressed(Keyboard::Numpad4))
								{
									team[4]->accelerate(4, -0.09 * time);
								}
								else team[4]->isPlayAnimation = false;
							}
						}
					}

#pragma endregion
				}
				else
					for (auto p : team)
						if (p->isPlayAnimation)
							p->isPlayAnimation = false;

#pragma endregion

				for (auto p : team)
				{
					if (p->status != DEAD)
					{
						//.:: Smoking :::::::::::::::
						if (p->status == WOUNDED)
						{
							if (!p->isSmoking)
							{
								p->isSmoking = true;
								Smoke * smoke = new Smoke(aSmoke, p, "smoke");
								entities.push_back(smoke);
							}
						}
					}
				}

				//.:: update entities :::
				for (auto i = entities.begin(); i != entities.end();)
				{
					Entity* e = *i;
					e->update(time);
					e->anim.update(time, e->isPlayAnimation, e->dir);

					if (e->isExist == false)
					{
						i = entities.erase(i);
						delete e;
					}
					else i++;
				}

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
				//.:: display entities :::
				for (auto e : entities)
					e->draw(app);
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
