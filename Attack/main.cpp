#include "Animation.h"
#include "maps.h"

#include "View.h"
#include "Entity.h"

#include "Player.h"
#include "Shell.h"

#include "Smoke.h"
#include "Rank.h"

#include "Air.h"
#include "Plane.h"

#include "Bomb.h"
#include "Enemy.h"

#include "DrowningModel.h"
#include "AchievementModel.h"


//.:: temp code :::
bool isUpd = false;	//.:: for double click protection
//:::::::::::::::::

enum AppMode { OPTIONS, GAME, SCORING, ENDGAME };
AppMode mode = OPTIONS;
bool transition = false; //.:: Game -> Scoring

vector<Entity*> entities;
vector<Air*> airEntities;
vector<Player*> team;
vector<Enemy*> squad;

int getEnemyPositionYOffset(int, int, string*);

template <typename T>
bool findAliveFrom(vector<T> team)
{
	for (auto t : team)
		if (t->status != DEAD) return true;

	return false;
}

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

	Image iMap, iIcon, iBurgundyTank, iYellowTank, iPurpleTank, iCyanTank, iHemoTank, iFighter, iAirBomb, iBombExplosion,
		iEnemy_1, iEnemy_2, iEnemy_3, iEnemy_4, iEnemy_5, iEnemy_6, iEnemy_7, iEnemy_8, iCommunication_truck, iDrowning,
		iSpeedUpAchiev, iRepair, iSniper;

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
	iFighter.loadFromFile("source/images/sprites/models/planes/fighter.png");
	iFighter.createMaskFromColor(Color::White);
	iAirBomb.loadFromFile("source/images/sprites/models/other/air_bomb.png");
	iAirBomb.createMaskFromColor(Color::White);
	iBombExplosion.loadFromFile("source/images/sprites/explosions/bomb_explosion.png");
	iBombExplosion.createMaskFromColor(Color::White);

	iEnemy_1.loadFromFile("source/images/sprites/models/tanks/enemies/enemy_1.png");
	iEnemy_1.createMaskFromColor(Color::White);
	iEnemy_2.loadFromFile("source/images/sprites/models/tanks/enemies/enemy_2.png");
	iEnemy_2.createMaskFromColor(Color::White);
	iEnemy_3.loadFromFile("source/images/sprites/models/tanks/enemies/enemy_3.png");
	iEnemy_3.createMaskFromColor(Color::White);
	iEnemy_4.loadFromFile("source/images/sprites/models/tanks/enemies/enemy_4.png");
	iEnemy_4.createMaskFromColor(Color::White);
	iEnemy_5.loadFromFile("source/images/sprites/models/tanks/enemies/enemy_5.png");
	iEnemy_5.createMaskFromColor(Color::White);
	iEnemy_6.loadFromFile("source/images/sprites/models/tanks/enemies/enemy_6.png");
	iEnemy_6.createMaskFromColor(Color::White);
	iEnemy_7.loadFromFile("source/images/sprites/models/tanks/enemies/enemy_7.png");
	iEnemy_7.createMaskFromColor(Color::White);
	iEnemy_8.loadFromFile("source/images/sprites/models/tanks/enemies/enemy_8.png");
	iEnemy_8.createMaskFromColor(Color::White);
	iCommunication_truck.loadFromFile("source/images/sprites/models/special_transport/communication_truck.png");
	iCommunication_truck.createMaskFromColor(Color::White);

	iDrowning.loadFromFile("source/images/sprites/other/drowning.png");
	iDrowning.createMaskFromColor(Color::White);
	iSpeedUpAchiev.loadFromFile("source/images/sprites/other/speed_up_achievement.png");
	iRepair.loadFromFile("source/images/sprites/other/repair.png");
	iSniper.loadFromFile("source/images/sprites/other/sniper_achievement.png");

#pragma endregion

#pragma region Textures

	Texture tMap, tIcon, bTank, yTank, pTank, cTank, hTank, tTankRound, tShell, tShellExp,
		tSmoke, tRank, tTarget, tAirStrikeZone, tFighter, tFighterTrace, tAirJetsFlame, tAirBomb, tBombExplosion,
		tEnemy_1, tEnemy_2, tEnemy_3, tEnemy_4, tEnemy_5, tEnemy_6, tEnemy_7, tEnemy_8, tCommunication_truck, tDrowning,
		tSpeedUpAchiev, tRepair, tSniper;

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
	tRank.loadFromFile("source/images/sprites/attributes/ranks.png");
	tTarget.loadFromFile("source/images/sprites/attributes/target.png");
	tAirStrikeZone.loadFromFile("source/images/sprites/attributes/airstrike_zone.png");
	tFighter.loadFromImage(iFighter);
	tFighterTrace.loadFromFile("source/images/sprites/models/planes/fighterTrace.png");
	tAirJetsFlame.loadFromFile("source/images/sprites/models/planes/air_jets_flame.png");
	tAirBomb.loadFromImage(iAirBomb);
	tBombExplosion.loadFromImage(iBombExplosion);

	tEnemy_1.loadFromImage(iEnemy_1);
	tEnemy_2.loadFromImage(iEnemy_2);
	tEnemy_3.loadFromImage(iEnemy_3);
	tEnemy_4.loadFromImage(iEnemy_4);
	tEnemy_5.loadFromImage(iEnemy_5);
	tEnemy_6.loadFromImage(iEnemy_6);
	tEnemy_7.loadFromImage(iEnemy_7);
	tEnemy_8.loadFromImage(iEnemy_8);
	tCommunication_truck.loadFromImage(iCommunication_truck);

	tDrowning.loadFromImage(iDrowning);
	tSpeedUpAchiev.loadFromImage(iSpeedUpAchiev);
	tRepair.loadFromImage(iRepair);
	tSniper.loadFromImage(iSniper);

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

	SoundBuffer bTankBuf, yTankBuf, pTankBuf, tankExpBuf, autoExpBuf, burgTankRoundBuf, yelTankRoundBuf, purpTankRoundBuf, 
		shellExpBuf, takingIconBuf, prefermentBuf, airstrikeQueryBuf, airstrikeConfirmBuf, fighterFlightBuf, bombWhistleBuf, bombExplosionBuf,
		enemy_1Buf, enemy_1RoundBuf, armorBuf, laughBuf, drowningBuf, speedUpBuf, repairBuf, sniperBuf;

	bTankBuf.loadFromFile("source/sounds/tank/movement/move_1.flac");
	yTankBuf.loadFromFile("source/sounds/tank/movement/move_2.flac");
	pTankBuf.loadFromFile("source/sounds/tank/movement/move_3.flac");
	tankExpBuf.loadFromFile("source/sounds/tank/explosion/tank_explosion.flac");
	burgTankRoundBuf.loadFromFile("source/sounds/tank/round/burgundy_tank_round.flac");
	purpTankRoundBuf.loadFromFile("source/sounds/tank/round/purple_tank_round.flac");
	yelTankRoundBuf.loadFromFile("source/sounds/tank/round/yellow_tank_round.flac");
	shellExpBuf.loadFromFile("source/sounds/explosion/shell_explosion.flac");
	takingIconBuf.loadFromFile("source/sounds/effects/icons/take_icon.flac");
	prefermentBuf.loadFromFile("source/sounds/effects/icons/preferment.flac");
	airstrikeQueryBuf.loadFromFile("source/sounds/effects/icons/airstrike_query.flac");
	airstrikeConfirmBuf.loadFromFile("source/sounds/effects/airstrike_confirmation.flac");
	fighterFlightBuf.loadFromFile("source/sounds/effects/fighterFlight.flac");
	bombWhistleBuf.loadFromFile("source/sounds/effects/bombWhistle.flac");
	bombExplosionBuf.loadFromFile("source/sounds/explosion/bomb_explosion.flac");
	enemy_1Buf.loadFromFile("source/sounds/tank/movement/move_5.flac");
	enemy_1RoundBuf.loadFromFile("source/sounds/tank/round/enemy1_round.flac");
	armorBuf.loadFromFile("source/sounds/tank/armor.flac");
	autoExpBuf.loadFromFile("source/sounds/explosion/auto_explosion.flac");
	laughBuf.loadFromFile("source/sounds/effects/laugh.flac");
	drowningBuf.loadFromFile("source/sounds/effects/drowning.flac");
	speedUpBuf.loadFromFile("source/sounds/effects/speed_up.flac");
	repairBuf.loadFromFile("source/sounds/effects/icons/repair.flac");
	sniperBuf.loadFromFile("source/sounds/effects/sniper.flac");

	Sound enemy_move, sTakingIcon, sPreferment, sAirStrikeQuery(airstrikeQueryBuf), sAirStrikeConfirm, sArmor, sLaugh(laughBuf);

	enemy_move.setBuffer(enemy_1Buf);			enemy_move.setLoop(true);
	sTakingIcon.setBuffer(takingIconBuf);		sTakingIcon.setLoop(false);
	sPreferment.setBuffer(prefermentBuf);		sPreferment.setLoop(false);		sPreferment.setVolume(32.f);
	sAirStrikeConfirm.setBuffer(airstrikeConfirmBuf); sAirStrikeConfirm.setLoop(false); sAirStrikeConfirm.setVolume(50.f);
	sArmor.setBuffer(armorBuf);					sArmor.setLoop(false);

	Music chapter_finale_theme;
	chapter_finale_theme.openFromFile("source/sounds/music/chapter_finale_theme.flac");

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
	Animation aRank(tRank, 0, 0, 200, 200, 1, 18);

	Animation aTarget(tTarget, 0, 0, 400, 400, 0.007, 6);
	Animation aAirStrikeZone(tAirStrikeZone, 0, 0, 400, 400, 0.005, 4);
	Animation aFighter(tFighter, fighterFlightBuf, 0, 0, 120, 165, 0.01, 1);
	Animation aFighterTrace(tFighterTrace, 0, 0, 120, 165, 0.1, 21);
	Animation aAirJetsFlame(tAirJetsFlame, 0, 0, 120, 165, 0.1, 21);
	Animation aDroppingBomb(tAirBomb, bombWhistleBuf, 0, 0, 200, 200, 0.015, 50);
	Animation aBombExplosion(tBombExplosion, bombExplosionBuf, 0, 0, 400, 400, 0.012, 19);

	Animation enemy_1(tEnemy_1, 0, 0, 64, 64, 0.016, 2);
	Animation explosion_enemy_1(tEnemy_1, tankExpBuf, 0, 64, 64, 64, 0.01, 12);
	Animation aEnemy1Round(tTankRound, enemy_1RoundBuf, 0, 0, 40, 36, 0.015, 8);
	Animation enemy_2(tEnemy_2, 0, 0, 64, 64, 0.016, 2);
	Animation explosion_enemy_2(tEnemy_2, tankExpBuf, 0, 64, 64, 64, 0.01, 12);
	Animation enemy_3(tEnemy_3, 0, 0, 64, 64, 0.016, 2);
	Animation explosion_enemy_3(tEnemy_3, tankExpBuf, 0, 64, 64, 64, 0.01, 12);
	Animation enemy_4(tEnemy_4, 0, 0, 64, 64, 0.016, 2);
	Animation explosion_enemy_4(tEnemy_4, tankExpBuf, 0, 64, 64, 64, 0.01, 12);
	Animation enemy_5(tEnemy_5, 0, 0, 64, 64, 0.016, 2);
	Animation explosion_enemy_5(tEnemy_5, tankExpBuf, 0, 64, 64, 64, 0.01, 12);
	Animation enemy_6(tEnemy_6, 0, 0, 64, 64, 0.016, 2);
	Animation explosion_enemy_6(tEnemy_6, tankExpBuf, 0, 64, 64, 64, 0.01, 12);
	Animation enemy_7(tEnemy_7, 0, 0, 64, 64, 0.016, 2);
	Animation explosion_enemy_7(tEnemy_7, tankExpBuf, 0, 64, 64, 64, 0.01, 12);
	Animation enemy_8(tEnemy_8, 0, 0, 64, 64, 0.016, 2);
	Animation explosion_enemy_8(tEnemy_8, tankExpBuf, 0, 64, 64, 64, 0.01, 12);

	Animation communication_truck(tCommunication_truck, 0, 0, 64, 64, 0.016, 1);
	Animation explosion_communication_truck(tCommunication_truck, autoExpBuf, 0, 64, 64, 64, 0.01, 14);

	Animation enemyAnim_1[] = { enemy_1, enemy_2, enemy_3, enemy_4, enemy_5, enemy_6, enemy_7, enemy_8, communication_truck };
	Animation explosionEnemyAnim_1[] = { explosion_enemy_1, explosion_enemy_2, explosion_enemy_3, explosion_enemy_4,
										 explosion_enemy_5, explosion_enemy_6, explosion_enemy_7, explosion_enemy_8,
										 explosion_communication_truck };

	Animation aDrowning(tDrowning, drowningBuf, 0, 0, 64, 64, 0.02, 14);
	Animation aSpeedUp(tSpeedUpAchiev, speedUpBuf, 0, 0, 128, 128, 0.009, 24);
	Animation aRepair(tRepair, repairBuf, 0, 0, 128, 128, 0.009, 21);
	Animation aSniper(tSniper, sniperBuf, 0, 0, 128, 128, 0.017, 50);

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
	float viewPosX = sizeX / 2, viewPosY = mapsHeight[0] * 32 - sizeY / 2;
	//.::::::::::::::::::::

	float zoomViewX = (float)sizeX / 2, zoomViewY = (float)sizeY / 2;

	//.:: Players tanks start position variables :::
	int a1, a2, b1, b2, c1, c2, d1, d2, e1, e2;
	a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = 0;

	Clock clock;

	Clock gameTimeClock;
	int gameTime = 0;
	double time = 0.0;

	//.:: Current message for players :::
	int endDisplayMessage = 0;

	Text report;
	Color reportColor;
	report.setFillColor(Color::Cyan);
	double mX = view.getCenter().x - 200;
	double mY = view.getCenter().y - 200;
	report.setPosition(mX, mY);
	//.::::::::::::::::::::::::::::::::::

#pragma region Functions
	
	void createEnemies(vector<Entity*>&, vector<Enemy*>&, Animation[], Animation[], string*);
	void createSmoke(Tank*, Animation&);
	void createShot(Tank*, Animation&, Animation&, Animation&);
	void createBomberLink(Player*, Sound&, Sound&, int, Animation&, Animation&, Animation&);
	void dropBombs(Animation&, Animation&);

#pragma endregion

	if (isGamePlay)
	{
		while (app.isOpen())
		{
			time = clock.getElapsedTime().asMicroseconds();
			clock.restart();

			time /= 1700;
			gameTime = (int)(gameTimeClock.getElapsedTime().asSeconds());

#pragma region Fade out time of main_theme music

			if (mode == GAME && main_theme->getStatus() == SoundStream::Playing)
			{
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
						main_theme->stop();				}
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

				//createEnemies(entities, squad, enemyAnim_1, explosionEnemyAnim_1);
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
									case 0: player = new Player(aBurgTank, a1, a2, "tank", 1, true, aExpBurgTank, "player", 1); break;
									case 1: player = new Player(aYellowTank, b1, b2, "tank", 1, true, aExpYellowTank, "player", 1); break;
									case 2: player = new Player(aPurpTank, c1, c2, "tank", 1, true, aExpPurpTank, "player", 1); break;
									case 3: player = new Player(aCyanTank, d1, d2, "tank", 1, true, aExpCyanTank, "player", 1); break;
									case 4: player = new Player(aHemoTank, e1, e2, "tank", 1, true, aExpHemoTank, "player", 1); break;
									}

									team.push_back(player);
									entities.push_back(player);
								}

								mode = GAME;
								start.play();
							}

							isStartGame = false;
							choice->play();
							createEnemies(entities, squad, enemyAnim_1, explosionEnemyAnim_1, maps[index]);
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
					if (enemy_move.getStatus() == SoundStream::Stopped && !battleIsOver)
						enemy_move.play();
					else if (enemy_move.getStatus() == SoundStream::Playing && battleIsOver)
						enemy_move.stop();

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
								enemy_move.stop();
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
							//.:: Air Spotter Mode
							if (Player::airSpotter.isAirSpotter && Player::airSpotter.currentPlayer == currentPlayer)
								createBomberLink(currentPlayer, sAirStrikeQuery, sAirStrikeConfirm, index, aFighter, aFighterTrace, aAirJetsFlame);
							else
								if (currentPlayer->isShot)
									createShot(currentPlayer, roundAnimation, aShell, aShellExp);
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
						Tank::camera = Camera::StartGame;
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
								if (team[0]->status != DEAD)
								{
									//.:: Air Spotter mode :::
									if(Player::airSpotter.isAirSpotter && Player::airSpotter.currentPlayer == team[0])
										createBomberLink(team[0], sAirStrikeQuery, sAirStrikeConfirm, index, aFighter, aFighterTrace, aAirJetsFlame);
									else
										if (team[0]->isShot)
											createShot(team[0], aBurgTankRound, aShell, aShellExp);
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
									if (team[1]->status != DEAD)
										createBomberLink(team[1], sAirStrikeQuery, sAirStrikeConfirm, index, aFighter, aFighterTrace, aAirJetsFlame);
									else
										if (team[1]->isShot)
											createShot(team[1], aYelTankRound, aShell, aShellExp);
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
									if (team[2]->status != DEAD)
										createBomberLink(team[2], sAirStrikeQuery, sAirStrikeConfirm, index, aFighter, aFighterTrace, aAirJetsFlame);
									else
										if (team[2]->isShot)
											createShot(team[2], aPurpTankRound, aShell, aShellExp);
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
									if (team[3]->status != DEAD)
										createBomberLink(team[3], sAirStrikeQuery, sAirStrikeConfirm, index, aFighter, aFighterTrace, aAirJetsFlame);
									else
										if (team[3]->isShot)
											createShot(team[3], aYelTankRound, aShell, aShellExp);
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
									if (team[4]->status != DEAD)
										createBomberLink(team[4], sAirStrikeQuery, sAirStrikeConfirm, index, aFighter, aFighterTrace, aAirJetsFlame);
									else
										if (team[4]->isShot)
											createShot(team[4], aBurgTankRound, aShell, aShellExp);
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
						p->checkMapCollision(maps[index]);

						//.:: Get Rank :::::::::::::::
						if (p->isPreferment)
						{
							p->isPreferment = false;
							sPreferment.play();
							if (!p->hasRank)
							{
								p->hasRank = true;
								Rank *rank = new Rank(aRank, p, "rank");
								entities.push_back(rank);
							}
						}

						//.:: Appoint a Commander :::
						if (p->isCommander && Tank::camera == Camera::Commander)
							setViewCoordinates(sizeX, sizeY, p->getCoordX(false), p->getCoordY(false), index);

						//.:: Air spotter mode :::
						if (Player::airSpotter.isAirSpotter && Player::airSpotter.currentPlayer == p)
						{
							if (Player::airSpotter.isTargetCreated)
							{
								Player::airSpotter.isTargetCreated = false;
								sAirStrikeQuery.play();

								Air *targetBomb = new Air(aTarget, aAirStrikeZone, p, "target");
								airEntities.push_back(targetBomb);

								Tank::camera = Camera::Target;

								reportColor = p->number == 1 ? Color::Red : p->number == 2 ? Color::Yellow :
									p->number == 3 ? Color::Magenta : p->number == 4 ? Color::Cyan : Color::Green;
							}

							if (Tank::camera == Camera::Target)
								setViewCoordinates(sizeX, sizeY, Player::airSpotter.xTargetPosition, Player::airSpotter.yTargetPosition, index);
							
							//.:: A death in spotter mode :::
							if (p->hitPoints <= 0)
							{
								Player::airSpotter.isAirSpotter = false;
								Player::airSpotter.currentPlayer = NULL;
								Player::airSpotter.xTargetPosition = 0.0;
								Player::airSpotter.yTargetPosition = 0.0;

								Tank::camera = Camera::NotDefined;
								if (sAirStrikeQuery.getStatus() == SoundStream::Playing)
									sAirStrikeQuery.stop();

								for (auto a : airEntities)
								{
									if (a->name == "target" && static_cast<Air*>(a)->getOwn() == p)
									{
										a->isExist = false;
										break;
									}
								}
							}
						}

						//::::::::::::::::::::::::::::::::::::::::::::::::::
						if (fadeOutTime != 0 && Tank::camera == Camera::StartGameSetted || Tank::camera == Camera::Commander)
							p->checkIconCollision(maps[index], sTakingIcon);
					}
					else
					{
						if (p->isCommander)
						{
							p->isCommander = false;
							Player::defineNewCommander(team);
						}
					}
				}

				for (auto e : squad)
				{
					if (e->status != DEAD)
					{
						e->checkMapCollision(maps[index]);
						e->checkIconCollision(maps[index], sTakingIcon);

						if (!e->round && e->isShot) e->destroyBrickWalls(maps[index]);
						if (!e->round && e->isShot)
							for (auto p : team)
								e->destroyPlayersTanks(p);

						if (e->round && e->isShot)
							createShot(e, aEnemy1Round, aShell, aShellExp);
					}
					else
						if (Enemy::evilTank.tank == e)
						{
							Enemy::evilTank.tank = NULL;
							if (sLaugh.getStatus() == SoundStream::Playing)
								sLaugh.stop();

							resetVillainView(sizeX, sizeY, zoomViewX, zoomViewY, index);
						}
				}

				//.:: Bomb dropping :::::::::::::::::::
				if (Plane::leader.bombStatus == BombStatus::DROPPED)
					dropBombs(aDroppingBomb, aBombExplosion);

				for (auto a : airEntities)
				{
					//.:: Air bomb destruction zone :::
					if (a->name == "bombExplosion" && !static_cast<Bomb*>(a)->coordsTransmitted)
					{
						static_cast<Bomb*>(a)->coordsTransmitted = true;

						double x = a->getCoordX(false);
						double y = a->getCoordY(false);

						Area *area = new Area(x, y, (float)180, a, "destructionZone");
						entities.push_back(area);
					}
				}

				for (auto a : entities)
				{
					//.:: Smoking :::::::::::::::::::::
					if (a->name == "tank" || a->name == "destroyed")
						if (static_cast<Tank*>(a)->status == WOUNDED 
							|| static_cast<Tank*>(a)->status == DEAD && static_cast<Tank*>(a)->makeSureDestroyed())
							if (!static_cast<Tank*>(a)->isSmoking)
								createSmoke((Tank*)a, aSmoke);

					//.:: Map collision :::::::::::::::
					if (a->name == "shell")
						static_cast<Shell*>(a)->checkMapCollision(maps[index]);

					//.:: Drowning ::::::::::::::::::::
					if (a->name == "destroyed" && !static_cast<Tank*>(a)->isDrowned)
						static_cast<Tank*>(a)->sinkTheTankCarcass(maps[index]);
					if (a->name == "destroyed" && static_cast<Tank*>(a)->isDrowned && !static_cast<Tank*>(a)->drowning)
					{
						static_cast<Tank*>(a)->drowning = true;
						DrowningModel *drowning = new DrowningModel(aDrowning, (Tank*)a, "drowning");
						entities.push_back(drowning);
					}

				
					//.:: Collide entities ::::::::::::
					for (auto b : entities)
					{
						if (a->name == "shell" && b->name == "tank")
							if (static_cast<Shell*>(a)->number != static_cast<Tank*>(b)->number)
								static_cast<Shell*>(a)->damageEntity((Tank*)(b), sArmor);
						
						if (a->name == "tank" && b->name == "tank" && static_cast<Tank*>(a)->number != static_cast<Tank*>(b)->number)
							static_cast<Tank*>(a)->checkVehiclesCollision((Tank*)b);

						if (a->name == "tank" && b->name == "destroyed" && static_cast<Tank*>(a)->makeSureVehicleCollision((Tank*)b))
							static_cast<Tank*>(a)->shoveOffTankCarcass((Tank*)b);

						if (a->name == "tank" && b->name == "destructionZone")
							static_cast<Tank*>(a)->getAreaDamage((Area*)b, maps[index]);
					}

					//.:: Achievements and effects ::::::::::::::::
					if (a->name == "tank" && static_cast<Tank*>(a)->isShowSpeedBonusAchiev)
					{
						static_cast<Tank*>(a)->isShowSpeedBonusAchiev = false;
						AchievementModel *achievement = new AchievementModel(aSpeedUp, (Tank*)a, "achievement");
						airEntities.push_back((Air*)achievement);
					}

					if (a->name == "tank" && static_cast<Tank*>(a)->isShowRepair)
					{
						static_cast<Tank*>(a)->isShowRepair = false;
						AchievementModel *repairEffect = new AchievementModel(aRepair, (Tank*)a, "effect");
						airEntities.push_back((Air*)repairEffect);
					}

					if (a->name == "tank" && static_cast<Tank*>(a)->isShowSniperAchiev)
					{
						static_cast<Tank*>(a)->isShowSniperAchiev = false;
						AchievementModel *achievement = new AchievementModel(aSniper, (Tank*)a, "achievement");
						airEntities.push_back((Air*)achievement);
					}

					//.:: Report about air strike victims :::::::::::::::::::::
					if (a->name == "destructionZone" && a->status == WOUNDED)
					{
						string message_ = (Area::victims == 0) ? "No destroyed enemy tanks"
							: (Area::victims == 1) ? "1 enemy tank was destroyed"
							: to_string(Area::victims) + " enemy tanks were destroyed";

						report = Text(message_, font_1, 50);
						report.setFillColor(reportColor);

						endDisplayMessage = gameTime + 5;
						
						if (reportColor == Color::Red) team[0]->nickDown(Area::totalExperience);
						else if (reportColor == Color::Yellow) team[1]->nickDown(Area::totalExperience);
						else if (reportColor == Color::Magenta) team[2]->nickDown(Area::totalExperience);
						else if (reportColor == Color::Cyan) team[3]->nickDown(Area::totalExperience);
						else if (reportColor == Color::Green) team[4]->nickDown(Area::totalExperience);
					}
				}

#pragma region Camera settings

				if (Tank::camera == Camera::NotDefined)
				{
					if (!Player::checkTeamForCommander(team))
						Tank::camera = Camera::StartGame;
					else
						Tank::camera = Camera::Commander;
				}

				if (Tank::camera == Camera::StartGame)
				{
					Tank::camera = Camera::StartGameSetted;
					setViewCoordinates(sizeX, sizeY, viewPosX, viewPosY, index);
				}

				if (Tank::camera == Camera::FirstPlane)
				{
					Plane *plane = static_cast<Plane*>(Plane::leader.plane);
					if (Plane::leader.openPosition)
						if (plane->leader.bombStatus == ABOARD)
							setViewCoordinates(sizeX, sizeY, plane->getCoordX(false), plane->getCoordY(false), index);

					//.:: Focus the camera on the first bomb :::
					if (Bomb::firstBomb.isOpenPosition)
					{
						Bomb *bomb = static_cast<Bomb*>(Bomb::firstBomb.bomb);

						if (bomb == NULL)
						{
							Tank::camera = Camera::NotDefined;
							Bomb::firstBomb.isOpenPosition = false;

							view.reset(FloatRect(0, 0, (float)sizeX, (float)sizeY));

							if (!Player::checkTeamForCommander(team))
								view.setCenter(mapsWidth[index] * 32 / 2 - 16, mapsHeight[index] * 32 - sizeY / 2 - 32);

							zoomViewX = (float)sizeX / 2;
							zoomViewY = (float)sizeY / 2;
						}
						else
						{
							zoomViewX -= zoomViewX / 200;
							zoomViewY -= zoomViewY / 200;

							view.reset(FloatRect(0, 0, zoomViewX, zoomViewY));
							setViewCoordinates(zoomViewX, zoomViewY, bomb->getCoordX(false), bomb->getCoordY(false), index);
						}
					}

				}

				if (Tank::camera == Camera::MalevolentTank && Enemy::evilTank.isVillain)
				{
					if (Enemy::evilTank.tank != NULL)
					{
						if (Enemy::evilTank.finishVillainTime == 0)
						{
							sLaugh.play();
							view.reset(FloatRect(0, 0, zoomViewX, zoomViewY));
							Enemy::evilTank.finishVillainTime = gameTime + 5;
						}

						zoomViewX -= zoomViewX / 1000;
						zoomViewY -= zoomViewY / 1000;

						view.reset(FloatRect(0, 0, zoomViewX, zoomViewY));
						setViewCoordinates((int)zoomViewX, (int)zoomViewY, Enemy::evilTank.tank->getCoordX(false), Enemy::evilTank.tank->getCoordY(false), index);

						if (gameTime >= Enemy::evilTank.finishVillainTime)
							resetVillainView(sizeX, sizeY, zoomViewX, zoomViewY, index);
					}
				}

#pragma endregion

				//.:: Clearing the list of enemies
				for (auto j = squad.begin(); j != squad.end();)
				{
					Entity *enemy = *j;
					if (static_cast<Enemy*>(enemy)->drowning)
					{
						j = squad.erase(j);
					}
					else j++;
				}

				//.:: update entities :::
				for (auto i = entities.begin(); i != entities.end();)
				{
					Entity* e = *i;
					e->update(time);
					e->anim.update(time, e->isPlayAnimation, e->dir);

					if (!e->isExist)
					{
						i = entities.erase(i);
						delete e;
					}
					else i++;
				}

				//.:: update air entities :::
				for (auto i = airEntities.begin(); i != airEntities.end();)
				{
					Entity* e = *i;
					e->update(time);
					e->anim.update(time, e->isPlayAnimation, e->dir);

					if (!e->isExist)
					{
						i = airEntities.erase(i);
						delete e;
					}
					else i++;
				}

				app.setView(view);

#pragma region Battle is over

				if (!battleIsOver && !transition && (!findAliveFrom(team) || !findAliveFrom(squad)))
				{
					chapter_finale_theme.play();
					lastSecondsOfChapter = gameTime + 7;
					transition = true;
				}

				if (!battleIsOver && transition)
				{
					if (gameTime >= lastSecondsOfChapter)
					{
						transition = false;
						battleIsOver = true;

						if (index + 1 != maps.size())
						{
							view.setCenter(float(sizeX / 2), float(sizeY / 2));
							mode = SCORING;
							++index;
						}
					}
				}

#pragma endregion
			}

			if (mode == SCORING)
			{
				app.setView(view);
			}
			
			if (mode == OPTIONS)
				star->update(1, true, 0);

			app.clear();
#pragma region GAME mode

			if (mode == GAME)
			{
				//.:: display zones :::
				for (auto e : airEntities)
					if (e->name == "zone")
						e->draw(app);

				//.:: map rendering :::
				renderMap(maps[index], app, map, time, index);
				//.:: display entities :::
				for (auto e : entities)
					e->draw(app);
				drawForestAndIcons(maps[index], app, map, icons, time, index);

				//.:: display all air entities except zones :::
				for (auto e : airEntities)
					if (e->name != "zone")
						e->draw(app);

				if (endDisplayMessage >= gameTime)
				{
					mX = view.getCenter().x - 250;
					mY = view.getCenter().y - 250;
					report.setPosition(mX, mY);
					app.draw(report);
				}
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

void createEnemies(vector<Entity*> &entities, vector<Enemy*> &squad, Animation anim[], Animation explosionAnim[], string *map)
{
	const int eTanks = 72;
	double enemyPositionX = 70;
	double enemyPositionY = 100;
	int mX = 0, mY = 0;
	int addValue = 0;

	for (int i = 0; i < eTanks; i++)
	{
		mX = (int)(ceil(enemyPositionX / 32));
		mY = (int)(ceil(enemyPositionY / 32));

		addValue = getEnemyPositionYOffset(mX, mY, map);

		Enemy *enemy;
		if (i <= 9)
			enemy = new Enemy(anim[7], enemyPositionX, enemyPositionY + addValue, "tank", 3, true, explosionAnim[7], "enemy", 8);
		else if (i > 9 && i <= 18)
			enemy = new Enemy(anim[6], enemyPositionX, enemyPositionY + addValue, "tank", 3, true, explosionAnim[6], "enemy", 7);
		else if (i > 18 && i <= 27)
			enemy = new Enemy(anim[5], enemyPositionX, enemyPositionY + addValue, "tank", 3, true, explosionAnim[5], "enemy", 6);
		else if (i > 27 && i <= 36)
			enemy = new Enemy(anim[4], enemyPositionX, enemyPositionY + addValue, "tank", 3, true, explosionAnim[4], "enemy", 5);
		else if (i > 36 && i <= 45)
			enemy = new Enemy(anim[3], enemyPositionX, enemyPositionY + addValue, "tank", 3, true, explosionAnim[3], "enemy", 4);
		else if (i > 45 && i <= 54)
			enemy = new Enemy(anim[2], enemyPositionX, enemyPositionY + addValue, "tank", 3, true, explosionAnim[2], "enemy", 3);
		else if (i > 54 && i <= 63)
			enemy = new Enemy(anim[1], enemyPositionX, enemyPositionY + addValue, "tank", 3, true, explosionAnim[1], "enemy", 2);
		else
			enemy = new Enemy(anim[0], enemyPositionX, enemyPositionY + addValue, "tank", 3, true, explosionAnim[0], "enemy", 1);

		entities.push_back(enemy);
		squad.push_back(enemy);

		enemyPositionX += 200;
		if (i != 0 && i % 9 == 0)
		{
			enemyPositionX = 100;
			enemyPositionY += 400;
		}
	}
}

int getEnemyPositionYOffset(int x, int y, string *map)
{
	int value = 0;

	while (true)
	{
		if (map[y][x] == ' ' || map[y][x] == 'F')
		{
			if (value > 0 || value == 0 && map[y-1][x] == 'B' || value == 0 && map[y-1][x] == 'b' || value == 0 && map[y-1][x] == 'W')
				value += 32;
			break;
		}
		else
		{
			value += 32;
			y++;
		}
	}

	return value;
}

void createBomberLink(Player *player, Sound &sQuery, Sound &sConfirm, int index, Animation &a, Animation &b, Animation &c)
{
	for (auto e : airEntities)
	{
		if (e->name == "target" && e->number == player->number)
		{
			e->status = WOUNDED;
			if (sQuery.getStatus() == SoundStream::Playing)
				sQuery.stop();
			sConfirm.play();

			int x = 0, y = 0;
			for (int i = 0; i < 3; i++)
			{
				x = i == 0 ? e->getCoordX(false) : i == 1 ? e->getCoordX(false) - 150 : e->getCoordX(false) + 150;
				y = i == 0 ? mapsHeight[index] * 32 + 800 : mapsHeight[index] * 32 + 900;

				Plane *fighter = new Plane(a, b, c, x, y, "fighter", e);
				airEntities.push_back(fighter);
			}

			Tank::camera = Camera::FirstPlane;
			break;
		}
	}
}

void createShot(Tank *tank, Animation &a, Animation &b, Animation &c)
{
	tank->isShot = false;
	if (tank->army == "enemy") static_cast<Enemy*>(tank)->round = false;

	Smoke *round = new Smoke(a, tank, "explosion");
	Shell *shell = new Shell(b, c, tank);
	entities.push_back(round);
	entities.push_back(shell);
}

void dropBombs(Animation &a, Animation &b)
{
	Plane::leader.bombStatus = BombStatus::DESCENT;
	Entity *e = Plane::leader.plane;

	int x = 0, y = 0;
	for (int i = 0; i < 3; i++)
	{
		x = i == 0 ? e->getCoordX(false) : i == 1 ? e->getCoordX(false) - 150 : e->getCoordX(false) + 150;
		y = i == 0 ? e->getCoordY(false) : e->getCoordY(false) + 70;

		Bomb *bomb = new Bomb(a, b, x, y, "bomb");
		airEntities.push_back(bomb);
	}
}

void createSmoke(Tank * p, Animation &a)
{
	p->isSmoking = true;
	Smoke *smoke = new Smoke(a, p, "smoke");
	airEntities.push_back((Air*)smoke);
}
