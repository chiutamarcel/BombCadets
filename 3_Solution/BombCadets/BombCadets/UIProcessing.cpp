#include "UIProcessing.h"
#include "GameConfig.h"

using namespace GameConfig;

UIProcessing* UIProcessing::instance = nullptr;

UIProcessing& UIProcessing::get() {
    if (nullptr == instance)
    {
        instance = new UIProcessing();
    }
    return *instance;
}

void UIProcessing::destruct() {
    delete instance;
    instance = nullptr;
}

void UIProcessing::draw(RenderWindow* window)
{
    curUI->draw(window);
}


void UIProcessing::switchMenu(MENUTYPE curMenu)
{
    delete curUI;

    switch (curMenu)
    {
    case MENUTYPE::MAINMENU:
        curUI = new MainMenu(GameConfig::WINDOWXSIZE, GameConfig::WINDOWYSIZE);
        break;
    case MENUTYPE::PLAY:
        curUI = new PlayMode(GameConfig::WINDOWXSIZE, GameConfig::WINDOWYSIZE);
        break;
    case MENUTYPE::ABOUT:
        curUI = new AboutMode(GameConfig::WINDOWXSIZE, GameConfig::WINDOWYSIZE);
        break;
    case MENUTYPE::HIGHSCORES:
        curUI = new HighScore(GameConfig::WINDOWXSIZE, GameConfig::WINDOWYSIZE);
        break;
    case MENUTYPE::OPTIONS:
        curUI = new Options(GameConfig::WINDOWXSIZE, GameConfig::WINDOWYSIZE);
        break;
    case MENUTYPE::JOINLOBBY:
        curUI = new JoinLobby(GameConfig::WINDOWXSIZE, GameConfig::WINDOWYSIZE);
        break;
    case MENUTYPE::CREATELOBBY:
        curUI = new CreateLobby(GameConfig::WINDOWXSIZE, GameConfig::WINDOWYSIZE);
        break;
    }
}

void UIProcessing::processEvents(Event event, RenderWindow* window, MENUTYPE &curMenu, GAMESTATE &curGameState, ENTRYTYPE &curEntryType)
{
    // << "Processing events\n";
    /*if (curEntryType == ENTRYTYPE::LOGIN && logUsername.getSelection()==true)
        {
            if (event.type == sf::Event::TextEntered)
            {
                logUsername.char_entered(event);
            }
        }
        else if (curEntryType == ENTRYTYPE::LOGIN && logUsername.getSelection() == false && logPassword.getSelection()==true)
        {
            if (event.type == sf::Event::TextEntered)
            {
                logPassword.char_entered(event);
                logPassword.setAsPass();
            }
        }
        else if (curEntryType == ENTRYTYPE::LOGIN && logUsername.getSelection() == false && logPassword.getSelection() == false)
        {
            curGameState = GAMESTATE::MAINMENU;
            curEntryType = ENTRYTYPE::CHOOSE;
            event.key.code = Keyboard::F;
        }

        if (curEntryType == ENTRYTYPE::CREATE && createUsername.getSelection() == true)
        {
            if (event.type == sf::Event::TextEntered)
            {
                createUsername.char_entered(event);
            }
        }
        else if (curEntryType == ENTRYTYPE::CREATE && createUsername.getSelection() == false && createPassword.getSelection() == true)
        {
            if (event.type == sf::Event::TextEntered)
            {
                createPassword.char_entered(event);
                createPassword.setAsPass();
            }
        }
        else if (curEntryType == ENTRYTYPE::CREATE && createUsername.getSelection() == false && createPassword.getSelection() == false)
        {
            curGameState = GAMESTATE::MAINMENU;
            curEntryType = ENTRYTYPE::CHOOSE;
            event.key.code = Keyboard::F;
        }*/

    /*if (curEntryType == ENTRYTYPE::IN && userTextBox.getSelection() == true)
    {
        if (event.type == sf::Event::TextEntered)
        {
            userTextBox.char_entered(event);
        }
        event.key.code = Keyboard::Escape;
    }

    if (curGameState == GAMESTATE::LOGIN && curEntryType == ENTRYTYPE::IN && userTextBox.getSelection() == false)
    {
        curGameState = GAMESTATE::MAINMENU;
        event.key.code = Keyboard::Escape;
    }

    if (createPass.getSelection() == false && createLobb.getSelection() == false && curGameState == GAMESTATE::MAINMENU)
    {
        music.stop();
        if (!gameMusic.openFromFile("Media\\game.wav"))
            exit(1); // eroare
        gameMusic.play();
        gameMusic.setLoop(true);
        gameMusic.setVolume(musicVolume);
        Game::startSinglePlayer();
        curGameState = GAMESTATE::INGAME;
    }

    if (event.type == sf::Event::TextEntered && createPass.getSelection() == true && createLobb.getSelection() == false && curMenu == MENUTYPE::CREATELOBBY)
    {
        createPass.char_entered(event);
        lobbyPass = createPass.getText();
        createPass.setAsPass();
    }

    if (event.type == sf::Event::TextEntered && createLobb.getSelection() == true && curMenu == MENUTYPE::CREATELOBBY)
    {
        createLobb.char_entered(event);
        lobbyName = createLobb.getText();
    }

    if (event.type == sf::Event::TextEntered && joinLobb.getSelection() == true && curMenu == MENUTYPE::JOINLOBBY)
    {
        joinLobb.char_entered(event);
    }*/

    if (event.type == Event::Closed) {
            delete curUI;
            exit(1);
    }

    curUI->pollEvents(event, curMenu, curGameState, curEntryType);
    

    //    if (event.type == Event::KeyPressed) {
    //        if (event.key.code == Keyboard::Escape) {
    //            window->close();
    //            return;
    //        }
    //    }
    //}
    //else if (curGameState == GAMESTATE::MAINMENU) {
    //    switch (curMenu) {
    //    case MENUTYPE::MAINMENU:
    //        if (event.type == Event::Closed) {
    //            window->close();
    //        }
    //        if (event.type == Event::KeyReleased) {

    //            if (event.key.code == Keyboard::Up) {
    //                curUI->up();
    //                break;
    //            }

    //            if (event.key.code == Keyboard::Down) {
    //                curUI->down();
    //                break;
    //            }

    //            if (event.key.code == Keyboard::Return) {

    //                int x = curUI->buttonPressed();
    //                switch (x) {
    //                case 0:
    //                    curUI = new PlayMode(WINDOWXSIZE, WINDOWYSIZE);
    //                    curMenu = MENUTYPE::PLAY;
    //                    break;
    //                case 1:
    //                    curUI = new Options(WINDOWXSIZE, WINDOWYSIZE);
    //                    curMenu = MENUTYPE::OPTIONS;
    //                    break;
    //                case 2:
    //                    curUI = new HighScore(WINDOWXSIZE, WINDOWYSIZE);
    //                    curMenu = MENUTYPE::HIGHSCORES;
    //                    break;
    //                case 3:
    //                    curUI = new AboutMode(WINDOWXSIZE, WINDOWYSIZE);
    //                    curMenu = MENUTYPE::ABOUT;
    //                    break;
    //                case 4:
    //                    exit(0);
    //                    break;
    //                }
    //            }
    //        }
    //        break;
    //    case MENUTYPE::PLAY:
    //        if (event.type == Event::Closed) {
    //            curMenu = MENUTYPE::MAINMENU;
    //            delete curUI;
    //            break;
    //        }

    //        if (event.type == Event::KeyPressed) {
    //            if (event.key.code == Keyboard::Escape) {
    //                curMenu = MENUTYPE::MAINMENU;
    //                switchMenu(curMenu);
    //                //delete curUI;
    //                break;
    //            }
    //        }

    //        if (event.type == Event::KeyReleased) {
    //            cout << curUI->buttonPressed();
    //            if (event.key.code == Keyboard::Left) {
    //                curUI->left();
    //                break;
    //            }

    //            if (event.key.code == Keyboard::Right) {
    //                curUI->right();
    //                break;
    //            }

    //            if (event.key.code == Keyboard::Return) {

    //                int y = curUI->buttonPressed();

    //                if (y == 1)
    //                {
    //                    //create lobby
    //                    curUI = new CreateLobby(WINDOWXSIZE, WINDOWYSIZE);
    //                    /*createLobb = TextBox(50, sf::Color::White, true);
    //                    createPass = TextBox(50, sf::Color::White, true);
    //                    createLobb.setFont();
    //                    createLobb.setPosition({ 110, 280 });
    //                    createPass.setFont();
    //                    createPass.setPosition({ 130, 630 });*/
    //                    curMenu = MENUTYPE::CREATELOBBY;
    //                    break;
    //                }

    //                if (y == 0)
    //                {
    //                    //join lobby
    //                    //curUI = new JoinLobby(WINDOWXSIZE, WINDOWYSIZE);
    //                    ///*joinLobb = TextBox(25, sf::Color::White, true);
    //                    //joinLobb.setFont();
    //                    //joinLobb.setPosition({ 820, 85 });*/
    //                    //curMenu = MENUTYPE::JOINLOBBY;

    //                    music.stop();
    //                    if (!gameMusic.openFromFile("Media\\game.wav"))
    //                        exit(1); // eroare
    //                    gameMusic.play();
    //                    gameMusic.setLoop(true);
    //                    gameMusic.setVolume(50.f);

    //                    Game::startSinglePlayer();
    //                    curGameState = GAMESTATE::INGAME;
    //                    break;
    //                }
    //            }
    //        }
    //        break;

    //    case MENUTYPE::ABOUT:

    //        if (event.type == Event::Closed) {
    //            curMenu = MENUTYPE::MAINMENU;
    //            delete curUI;
    //            break;
    //        }

    //        if (event.type == Event::KeyPressed) {
    //            if (event.key.code == Keyboard::Escape) {
    //                curMenu = MENUTYPE::MAINMENU;
    //                switchMenu(curMenu);
    //                break;
    //            }
    //        }

    //        if (event.type == Event::KeyReleased) {
    //            if (event.key.code == Keyboard::Up) {
    //                curUI->up();
    //                break;
    //            }

    //            if (event.key.code == Keyboard::Down) {
    //                curUI->down();
    //                break;
    //            }

    //            if (event.key.code == Keyboard::Return) {

    //                int y = curUI->buttonPressed();

    //                if (y == 0)
    //                {
    //                    //how to play
    //                }

    //                if (y == 1)
    //                {
    //                    //controls
    //                }
    //            }

    //        }

    //        break;
    //    case MENUTYPE::HIGHSCORES:

    //        if (event.type == Event::Closed) {
    //            curMenu = MENUTYPE::MAINMENU;
    //            delete curUI;
    //            break;
    //        }

    //        if (event.type == Event::KeyPressed) {
    //            if (event.key.code == Keyboard::Escape) {
    //                curMenu = MENUTYPE::MAINMENU;
    //                switchMenu(curMenu);
    //                break;
    //            }
    //        }

    //        if (event.type == Event::KeyReleased) {
    //            if (event.key.code == Keyboard::Up) {
    //                curUI->up();
    //                break;
    //            }

    //            if (event.key.code == Keyboard::Down) {
    //                curUI->down();
    //                break;
    //            }

    //            if (event.key.code == Keyboard::Return) {

    //                int y = curUI->buttonPressed();

    //                if (y == 0)
    //                {
    //                    //local
    //                }

    //                if (y == 1)
    //                {
    //                    //regional
    //                }
    //            }

    //        }

    //        break;
    //    case MENUTYPE::OPTIONS:

    //        if (event.type == Event::Closed) {
    //            curMenu = MENUTYPE::MAINMENU;
    //            delete curUI;
    //            break;
    //        }

    //        if (event.type == Event::KeyPressed) {
    //            if (event.key.code == Keyboard::Escape) {
    //                curMenu = MENUTYPE::MAINMENU;
    //                switchMenu(curMenu);
    //                break;
    //            }
    //        }

    //        if (event.type == Event::KeyReleased) {
    //            if (event.key.code == Keyboard::Up) {
    //                curUI->up();
    //                break;
    //            }

    //            if (event.key.code == Keyboard::Down) {
    //                curUI->down();
    //                break;
    //            }

    //            if (event.key.code == Keyboard::Return) {

    //                int y = curUI->buttonPressed();

    //                if (y == 0)
    //                {
    //                    //player skin
    //                }

    //                if (y == 1)
    //                {
    //                    //bomb skin
    //                }

    //                if (y == 2)
    //                {
    //                    //sound
    //                }
    //            }

    //        }

    //        break;
    //    default:

    //        if (event.type == Event::Closed) {
    //            curMenu = MENUTYPE::MAINMENU;
    //            delete curUI;
    //            break;
    //        }

    //        if (event.type == Event::KeyPressed) {
    //            if (event.key.code == Keyboard::Escape) {
    //                curMenu = MENUTYPE::MAINMENU;
    //                switchMenu(curMenu);
    //                break;
    //            }
    //        }

    //        break;

    //    }
    //}
    //else if (curGameState == GAMESTATE::LOGIN)
    //{
    //    switch (curEntryType)
    //    {
    //    case ENTRYTYPE::CHOOSE:
    //        if (event.type == Event::Closed) {
    //            window->close();
    //        }
    //        //if (event.type == Event::KeyReleased) {
    //        //    if (event.key.code == Keyboard::Up) {
    //        //        logCreate->up();
    //        //        break;
    //        //    }

    //        //    if (event.key.code == Keyboard::Down) {
    //        //        logCreate->down();
    //        //        break;
    //        //    }

    //        //    if (event.key.code == Keyboard::Return) {

    //        //        int y = logCreate->buttonPressed();

    //        //        if (y == 0)
    //        //        {
    //        //            //create
    //        //            createAcc = new CreateAcc(WINDOWXSIZE, WINDOWYSIZE);
    //        //            createUsername = TextBox(50, sf::Color::White, true);
    //        //            createUsername.setFont();
    //        //            createUsername.setPosition({ 330, 130 });
    //        //            createPassword = TextBox(50, sf::Color::White, true);
    //        //            createPassword.setFont();
    //        //            createPassword.setPosition({ 330, 290 });
    //        //            curEntryType = ENTRYTYPE::CREATE;
    //        //            break;
    //        //        }

    //        //        if (y == 1)
    //        //        {
    //        //            //login
    //        //            Login = new LogIn(WINDOWXSIZE, WINDOWYSIZE);
    //        //            logUsername = TextBox(50, sf::Color::Black, true);
    //        //            logPassword = TextBox(50, sf::Color::Black, true);
    //        //            logUsername.setFont();
    //        //            logUsername.setPosition({ 530, 60 });
    //        //            logPassword.setFont();
    //        //            logPassword.setPosition({ 530, 200 });
    //        //            curEntryType = ENTRYTYPE::LOGIN;
    //        //            break;
    //        //        }
    //        //    }
    //        //}
    //        //break;

    //        /*userTextBox = TextBox(60, sf::Color::Black, true);
    //        userTextBox.setFont();
    //        userTextBox.setPosition({ 530, 60 });*/
    //        curEntryType = ENTRYTYPE::IN;
    //        break;
    //    default:

    //        if (event.type == Event::Closed) {
    //            exit(1);
    //            break;
    //        }

    //        break;
    //    }
    //}

}

