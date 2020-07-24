#include "TicTacToeScene.hpp"
#include "MinigameSelectScene.hpp"

#define t(x) AddCommand(x)
#define func(a) [&]() { t(a); }
#define PAIR(name, command) { name, [&]() { t(command); }}
#define NULLPartialPAIR(name) { name, nullptr }
#define NULLPAIR PAIR("", nullptr)
#define COLORPAIR(name, r, g, b) PAIR(name, new ColorCommand(name, m3d::Color(r,g,b,255)))


TicTacToeScene::TicTacToeScene() 
{
	commandLister->OverrideTabCommandListObjects(
		{
			PAIR("Naught", new TTT_O_Command()),
			PAIR("Cross",  new TTT_X_Command())
		}, 0
	);
	for (int i = 1; i < NUM_TABS; i++)
	{
		commandLister->OverrideTabCommandListObjects({}, i);
		commandLister->SetTabState(i, false);
	}
}

TicTacToeScene::~TicTacToeScene() 
{
    
}

/**
 *  @brief
 * 
 * 
 */
void TicTacToeScene::initialize() {
    Minigame::initialize();

    colorRec = new m3d::Color(150,150,150);
	colorText = new m3d::Color(0,0,0);

    //  Initialize Detectors
    for (int i = 0; i < TTT_NUM_CELLS; i++)
    {
        int row = (i % TTT_NUM_ROWS);
        int col = (i / TTT_NUM_ROWS);
        m_detectors[i] = new BoundingBox(
                                            TTT_X + (TTT_CELL_SIZE * row), 
                                            TTT_Y + (TTT_CELL_SIZE * col), 
                                            TTT_DETECTOR_SIZE, 
                                            TTT_DETECTOR_SIZE
                                        );
        m_board[i] = BoardState::VACANT;
    }
     
    wallpaper= new SpriteMenuItem(*(ResourceManager::getSprite("TTT_BG.png")));
    menu->AddItem(wallpaper);

	wallpaper->setCenter(0,0);
	wallpaper->setScale(1,1);
       
    tutorial[0] = new SpriteMenuItem(*(ResourceManager::getSprite("TTT_Tutorial1.png")));
    menu->AddItem(tutorial[0]);
    tutorial[1] = new SpriteMenuItem(*(ResourceManager::getSprite("TTT_Tutorial2.png")));
    menu->AddItem(tutorial[1]);
    tutorial[2] = new SpriteMenuItem(*(ResourceManager::getSprite("TTT_Tutorial3.png")));
    menu->AddItem(tutorial[2]);
    tutCount = 0;

    popup = tutorial[tutCount];
    popup->setPosition(80,20);

	currentState = TTTState::TutorialMessage;
}

void TicTacToeScene::draw() {

    m3d::Screen *screen = GameManager::getScreen();

    screen->drawTop(*wallpaper);

    if(currentState == TTTState::TutorialMessage)
    {
        screen->drawTop(*popup,m3d::RenderContext::Mode::Flat,2);
    }
    Minigame::draw();
    
}

void TicTacToeScene::load(){Minigame::load();};

void TicTacToeScene::unload(){Minigame::unload();};

void TicTacToeScene::update()
{
    Minigame::update();
    switch (currentState)
    {
        case TutorialMessage:

            AddButton->SetActive(false);
            RemoveButton->SetActive(false);
            EditButton->SetActive(false);
            submitButton->SetActive(false);

            if (m3d::buttons::buttonPressed(m3d::buttons::A))
            {
                if (tutCount < 3)
                {
                    tutCount++;
                }

                if (tutCount < 3)
                {
                    popup = tutorial[tutCount];
                    popup->setPosition(80,20);
                }    
            }

            if (m3d::buttons::buttonDown(m3d::buttons::Start) || tutCount >= 3)
            {
                tutCount = 0;

                currentState = TTTState::Requesting;
                SceneManager::RequestUserCode( {
                                                    new TTT_O_Command("1","1")
                                                }, [&](std::vector<CommandObject*> list){ this->SubmitTTTCode(list);} 
                                            );
                codeEditor->SetActive(true);
            }

            break;
        case Requesting: // Resting state
            
            break;
        case PlayerTurn:
            currentState = TTTState::Requesting;
            SceneManager::RequestUserCode( {}, [&](std::vector<CommandObject*> list){ this->SubmitTTTCode(list);} );            
            break;
        case Execute:
            submitButton->SetActive(false);
			AddButton->SetActive(false);
			RemoveButton->SetActive(false);
			EditButton->SetActive(false);            
            break;
        case EnemyTurn:
            runEnemyAI();
            updateBoard();
            SceneManager::RequestUserCode( {}, [&](std::vector<CommandObject*> list){ this->SubmitTTTCode(list);} );
            currentState = TTTState::PlayerTurn; 
            break; 
        case Win:
            break;
        case Lose:
            break;
        default:
            break;
    }
};

void TicTacToeScene::updateBoard()
{
    for (int i = 0; i < TTT_NUM_CELLS; i++)
    {
        m3d::BoundingBox *d = m_detectors[i];
        GameObject* g = nullptr;

        for (auto objPair : m_hashmap)
		{
			g = objPair.second;
            if(g->getAABB().intersects(*d))
            {
                if(g->getName() == "X" || g->getName() == "O" )
                {
                    m_board[i] = (g->getName() == "X") ? BoardState::ENEMY : BoardState::PLAYER;
                }
            }
		}
    }

    #ifdef DEBUG_MINIGAME 
    for (int i = 0; i < TTT_NUM_CELLS; i++)
    {
        if(i%3 == 0)
            Util::PrintLine("");
        Util::Print(std::to_string(m_board[i]) + " ");
    }
    Util::PrintLine("");
    #endif
    
    if(checkWinCond(BoardState::PLAYER))
    {
        currentState = TTTState::Win;
        submitButton->SetActive(false);
        AddButton->SetActive(false);
        RemoveButton->SetActive(false);
        EditButton->SetActive(false); 
        #ifdef DEBUG_MINIGAME
        Util::PrintLine("You Win!");
        #endif
    } else if(checkWinCond(BoardState::ENEMY))
    {
        currentState = TTTState::Lose;
        submitButton->SetActive(false);
        AddButton->SetActive(false);
        RemoveButton->SetActive(false);
        EditButton->SetActive(false);
        #ifdef DEBUG_MINIGAME
        Util::PrintLine("You Lose!"); 
        #endif
    }
    
    
}

void TicTacToeScene::SubmitTTTCode(std::vector<CommandObject*> luaCode)
{
    #ifdef DEBUG_MINIGAME
    Util::PrintLine("TTT: queue commands");
    #endif
    std::string str = CommandObject::ConvertBulk(luaCode);

    /*
        Encapsulate code into a function. then call the function.
    */
    stringstream fn;
    fn << "userCode = function()" << str << " end\n" << "\n";
    m_sandbox->executeString(fn.str()); // if this returns false theres an error in the usercode
    m_sandbox->executeStringQueued("userCode()\n");

	currentState = TTTState::Execute;
}

void TicTacToeScene::onEnter(){Minigame::onEnter();};
void TicTacToeScene::onExit(){Minigame::onExit();};

bool TicTacToeScene::checkWinCond(TicTacToeScene::BoardState id)
{
    //  Diagonals
    if  ( 
            (m_board[0] == id && m_board[4] == id && m_board[8] == id ) || 
            (m_board[2] == id && m_board[4] == id && m_board[6] == id ) 
        )
        { 
            return true;
        }

    //  Horizontal
    for (int i = 0; i < TTT_NUM_COLS; i++)
    {
        int shift = i * TTT_NUM_ROWS;
        if (m_board[ (shift+0) % TTT_NUM_CELLS ] == id && 
            m_board[ (shift+1) % TTT_NUM_CELLS ] == id && 
            m_board[ (shift+2) % TTT_NUM_CELLS ] == id )
        {
            return true;
        } 
    }

    //  Vertical
    for (int i = 0; i < TTT_NUM_ROWS; i++)
    {
        int shift = i;
        if (m_board[ (shift+0) % TTT_NUM_CELLS ] == id && 
            m_board[ (shift+3) % TTT_NUM_CELLS ] == id && 
            m_board[ (shift+6) % TTT_NUM_CELLS ] == id )
        {
            return true;
        } 
    }
    
    return false;
}

void TicTacToeScene::loadScene() { Minigame::loadScene(); };
void TicTacToeScene::loadWinScr() { Minigame::loadWinScr(); };
void TicTacToeScene::loadLoseScr() { Minigame::loadLoseScr(); };
void TicTacToeScene::requestUI() { Minigame::requestUI(); };
void TicTacToeScene::closeGame() { Minigame::closeGame(); };

void TicTacToeScene::runEnemyAI()
{
    int n;
    do{
        n =  rand() % (TTT_NUM_CELLS);
    }while(m_board[n] != BoardState::VACANT);
    
    int row = (n % TTT_NUM_ROWS) + 1;
    int col = (n / TTT_NUM_ROWS) + 1;
    addObject(new TTT_Token(true,row,col));
    #ifdef DEBUG_MINIGAME 
    Util::PrintLine("Enemy rand:" + std::to_string(n) + " ,row:" + std::to_string(row) + ",col:" + std::to_string(col) );
    #endif
}

void TicTacToeScene::onExecutionEnd()
{
    updateBoard();
    this->isExecuting = false;
    this->currentState = TTTState::EnemyTurn;
}
