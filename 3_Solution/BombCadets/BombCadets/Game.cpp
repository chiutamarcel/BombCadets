#include "Game.h"
#include "Map.h"
#include "Client.h"
#include "GameConfig.h"
#include "UIProcessing.h"
#include "Logger.h"
#include <utility>
#include <fstream>

using namespace GameConfig;

//UIProcessing& UI=UI.get();

static MENUTYPE curMenu;
static GAMESTATE curGameState;
static ENTRYTYPE curEntryType;

Game::Game() {
    focus = true;
}

void Game::pollEvents()
{
    Client::getInstance().pollEvents();

    if (curGameState == GAMESTATE::INGAME) {
        if (focus == true) {
            Entities::getInstance().getPlayer().pollEvents();
        }
    }


    // Process events
    sf::Event event;

    while (window->pollEvent(event))
    {


        if (curGameState != GAMESTATE::INGAME)
            UIProcessing::get().processEvents(event, window, curMenu, curGameState, curEntryType);

        if (event.type == sf::Event::LostFocus) {
            focus = false;
        }

        if (event.type == sf::Event::GainedFocus) {
            focus = true;
        }
    }
}


Game::~Game()
{
	if (window != nullptr)
		delete window;
}

void Game::start()
{

	// Make Main window
    window = new sf::RenderWindow(sf::VideoMode(WINDOWXSIZE, WINDOWYSIZE), "Bomberman");
    //logCreate = new LogCreate(WINDOWXSIZE, WINDOWYSIZE);
    //mainMenu = new MainMenu(WINDOWXSIZE, WINDOWYSIZE);

    ////logCreate bacc
    //logCreateBackground.setSize(Vector2f(WINDOWXSIZE, WINDOWYSIZE));
    //logCreate_texture.loadFromFile("Textures\\logsig1.jpg");
    //logCreateBackground.setTexture(&logCreate_texture);

    ////login bacc
    //logBackground.setSize(Vector2f(WINDOWXSIZE, WINDOWYSIZE));
    //log_texture.loadFromFile("Textures\\log.png");
    //logBackground.setTexture(&log_texture);

    ////createAcc bacc
    //createAccBackground.setSize(Vector2f(WINDOWXSIZE, WINDOWYSIZE));
    //createAcc_texture.loadFromFile("Textures\\create.png");
    //createAccBackground.setTexture(&createAcc_texture);

    //create sky bacc
    skyBacc.setSize(sf::Vector2f(1344, 136));
    sky_texture.loadFromFile("Textures\\sky.png");
    skyBacc.setTexture(&sky_texture);


    curMenu = MENUTYPE::MAINMENU;
    curGameState = GAMESTATE::LOGIN;
    curEntryType = ENTRYTYPE::CHOOSE;
}

void Game::update()
{
	if (curGameState == GAMESTATE::INGAME) {
		for (auto entity : Entities::getInstance().getCharacters())
			entity->update(deltaTime.asSeconds());
		for (auto entity : Entities::getInstance().getBreakableBlocks())
			entity->update(deltaTime.asSeconds());
		for (auto entity : Entities::getInstance().getBombs())
			entity->update(deltaTime.asSeconds());

		std::vector<Explosion*>& explosions = Entities::getInstance().getExplosions();

		for (int i = 0; i < explosions.size(); i++)
		(explosions[i])->update(deltaTime.asSeconds());
		
		deltaTime = deltaClock.restart();;
  }
}

void Game::startSinglePlayer() {
    curGameState = GAMESTATE::INGAME;
    MapText mapText(BLOCKSONSCREENX, BLOCKSONSCREENY);
    mapText.readFromFile(mapFile);
    mapText.putBreakableBlocks(NRBREAKABLEWALLS);
    Map::spawnMap(mapText);
    Map::spawnCharacter(Map::CharacterType::PLAYER);
    Map::spawnCharacter(Map::CharacterType::BOT);
}

void Game::startMultiPlayer(std::string ip, unsigned short port) {
    curGameState = GAMESTATE::INGAME;
    Client::getInstance().start(ip, port);

    // TODO: change later after adding a proper Bot class
    for (int i = 0; i < Map::maxPlayers; i++) {
        if (i == Client::getInstance().getId()) {
            Map::spawnCharacter(Map::CharacterType::PLAYER);
        }
        else {
            Map::spawnCharacter(Map::CharacterType::BASE);
        }
    }
}

void Game::draw()
{
	// Clear screen
	window->clear();

	// Draw
    if (curGameState == GAMESTATE::MAINMENU || curGameState == GAMESTATE::LOGIN) {
        /*switch (curMenu) {
        case MENUTYPE::MAINMENU:
            window->draw(background);
            mainMenu->draw(window);
            break;
        case MENUTYPE::PLAY:
            window->draw(playBackground);
             playMode->draw(window);
            break;
        case MENUTYPE::ABOUT:
            window->draw(aboutBackground);
            about->draw(window);
            break;
        case MENUTYPE::HIGHSCORES:
            window->draw(highBackground);
            highScore->draw(window);
            break;
        case MENUTYPE::OPTIONS:
            window->draw(optionsBackground);
            options->draw(window);
            break;
        case MENUTYPE::JOINLOBBY:
			window->draw(joinBackground);
			joinLobby->draw(window);
            joinLobb.draw(window);
			break;
        case MENUTYPE::CREATELOBBY:
            window->draw(createBackground);
			createLobby->draw(window);
            createLobb.draw(window);
            createPass.draw(window);
            break;
        }*/

        UIProcessing::get().draw(window);
    } else if (curGameState == GAMESTATE::INGAME) {
        for (auto entity : Entities::getInstance().getCharacters())
		    window->draw(entity->getShape());
	    for (auto entity : Entities::getInstance().getBreakableBlocks())
		    window->draw(entity->getShape());
	    for (auto entity : Entities::getInstance().getBombs())
		    window->draw(entity->getShape());
	    for (auto entity : Entities::getInstance().getWalls())
		    window->draw(entity->getShape());
	    for (auto entity : Entities::getInstance().getExplosions())
		    window->draw(entity->getShape());
        window->draw(skyBacc);
    }
  //  else if (curGameState == GAMESTATE::LOGIN) {
  //      switch (curEntryType) {
		//case ENTRYTYPE::IN:
		//	window->draw(inUsernameBackground);
		//	inUsername->draw(window);
  //          userTextBox.draw(window);
		//	break;
		//case ENTRYTYPE::CHOOSE:
  //          window->draw(inUsernameBackground);
  //          inUsername->draw(window);
  //          break;
		////case ENTRYTYPE::CREATE:
  //        // window->draw(createAccBackground);
  //         // createAcc->draw(window);
  //         // createUsername.draw(window);
  //         // createPassword.draw(window);
		//   // break;
		//}
	//}

	// Display what has been drawn
	window->display();
}

const sf::RenderWindow& Game::getWindow() const
{
	return *window;
}
