#include"game.h"

using namespace std;
using namespace sf;

#define WIDTH 1024
#define HEIGHT 768

int cnt = 0;

struct ArrowShape
{
    int direction;
    int x;
    int y;
};

class Arrow
{
private:
    enum Dir
    {
        UP = 0,
        DOWN,
        LEFT,
        RIGHT,
    };

    Texture t;
    Sprite s;
    deque<ArrowShape> questions;

    float frame;
    float frameSpeed;
    int frameLimit;
    int dir[4] = { -90, 90, 180, 0 };
private:
    bool CheckArrow(int idx)
    {
        if (questions.empty()) return false;
        if (idx == questions[0].direction)
        {
            cout << "correct" << endl;
            return true;
        }
        return false;
    }

public:
    Arrow()
    {
        srand(static_cast<unsigned int>(time(nullptr)));

        t.loadFromFile("img/game5/kwarrow.png");
        s = Sprite(t);
        Rect<float> rect = s.getGlobalBounds();
        s.setOrigin(Vector2f(rect.width / 2, rect.height / 2));
        frame = 20.f;
        frameSpeed = 0.6f;
        frameLimit = 20;
    }
    ~Arrow() {}

    void Init()
    {
        questions.clear();
    }

    bool CheckKey()
    {
        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            cout << "UP" << endl;
            return CheckArrow(Dir::UP);
        }
        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            cout << "DOWN" << endl;
            return CheckArrow(Dir::DOWN);
        }
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            cout << "LEFT" << endl;
            return CheckArrow(Dir::LEFT);
        }
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            cout << "RIGHT" << endl;
            return CheckArrow(Dir::RIGHT);
        }
        return false;
    }

    void ArrowSetting()
    {
        //check frame
        frame += frameSpeed;
        if (frame <= frameLimit) return;
        frame -= frameLimit;

        //check arrow number
        if (questions.size() > 10) return;
        ArrowShape as;

        int dirIdx = rand() % 4;
        as.direction = dirIdx;
        as.x = WIDTH;
        as.y = 100;
        s.setPosition(as.x, as.y);
        questions.push_back(as);
    }

    void Move(const int& speed, bool& isGameOver)
    {
        deque<ArrowShape>::iterator iter;
        for (iter = questions.begin(); iter != questions.end(); ++iter)
        {
            iter->x -= speed;
            if (iter->x <= 0)
            {
                //gameover;
                isGameOver = true;
                break;
            }
        }
    }

    void Draw(RenderWindow& _window)
    {
        for (auto iter = questions.begin(); iter != questions.end(); ++iter)
        {
            s.setRotation(dir[iter->direction]);
            s.setPosition(iter->x, iter->y);
            _window.draw(s);
        }
    }

    ArrowShape GetFirstArrowPos()
    {
        return questions[0];
    }

    void RemoveFirstArrow()
    {
        if (questions.empty()) return;
        questions.pop_front();
    }

    bool IsEmpty() const
    {
        return questions.empty();
    }
};
class GameManager
{
private:
    enum GameState
    {
        NONE,
        CORRECT,
        WRONG,
    };
    int arrowSpeed;
    bool isGameOver;
    Arrow* pArrow;

    Texture tw;
    Texture tl;
    Texture correct;
    Sprite imgWrong;
    Sprite imgDeadLine;
    GameState state;
    ArrowShape firstArrowPos;
public:
    GameManager()
    {
        arrowSpeed = 10;
        isGameOver = false;
        pArrow = new Arrow();
        state = NONE;

        tw.loadFromFile("img/game5/wrong.png");
        tl.loadFromFile("img/game5/line.png");
        correct.loadFromFile("img/game5/correct.png");
        imgWrong = Sprite(tw);
        imgDeadLine = Sprite(tl);
        imgDeadLine.setPosition(0, 45);

        Rect<float> rect = imgWrong.getGlobalBounds();
        imgWrong.setOrigin(Vector2f(rect.width / 2, rect.height / 2));
    }

    void Init()
    {
        pArrow->Init();
    }

    void CheckKey()
    {
        if (pArrow->IsEmpty()) return;

        if (pArrow->CheckKey())
        {
            //correct
            firstArrowPos = pArrow->GetFirstArrowPos();
            pArrow->RemoveFirstArrow();
            state = CORRECT;
        }
        else
        {
            //wrong
            firstArrowPos = pArrow->GetFirstArrowPos();
            pArrow->RemoveFirstArrow();
            state = WRONG;
        }
    }

    void Move()
    {
        pArrow->ArrowSetting();
        pArrow->Move(arrowSpeed, isGameOver);
    }

    void Draw(RenderWindow& window)
    {
        switch (state)
        {
        case WRONG:
            //game over.
            state = NONE;
            imgWrong.setPosition(firstArrowPos.x, firstArrowPos.y);
            window.draw(imgWrong);
            isGameOver = true;
            break;
        case CORRECT:
            //score up.
            cnt++;
            state = NONE;
            break;
        }
        pArrow->Draw(window);

        window.draw(imgDeadLine);
    }
    void CheckGameOver()
    {
        if (isGameOver)
        {
            sleep(seconds(3));
            isGameOver = false;
            Init();
            //to game_6;
        }
    }
};

void main_game_5(int dif){
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "Stage 5");
    window.setFramerateLimit(40*dif);

    GameManager* pGameMgr = new GameManager();
    pGameMgr->Init();
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) { // 스크린의 X버튼을 누르거나, 혹은 키보드의 ESC를 누르면 메인화면으로 돌아가도록 수정
                window.close(); // 게임창 닫고
                main(1); // 메인화면 창을 다시 열기
            }
            if (event.type == Event::KeyPressed)
            {
                pGameMgr->CheckKey();
            }
        }
        //logic.
        pGameMgr->Move();

        //draw.
        window.clear(Color::Black);
        pGameMgr->Draw(window);
        window.display();

        pGameMgr->CheckGameOver();
        if (cnt == 30) {
            window.close();
            //goto game_6;
        }
    }
    delete(pGameMgr);
}