#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <vector>
#include <string>

using namespace sf;


class Game {
public:
    int x, y, h;
    float dx, dy;
    Game() {
        x = 100; 
        y = 100;
        h = 200;
        dx = 0;
        dy = 0;

    }
    void TurnDown()
    {
        dy += 0.2;
        y += dy;
    }
};

class Platform {
public:
    virtual void createPlatform(int count) {
        for (int i = 0; i < count; ++i) {
            Vector2f p;
            p.x = rand() % 400;
            p.y = rand() % 533;
            plat.push_back(p);
        }
    }


    virtual void movePlatforms(float dy, int& y, int& h, Sprite score[], int fs[], int& sc) {
        for (size_t i = 0; i < plat.size(); ++i) {
            y = h;
            plat[i].y = plat[i].y + dy;
            if (plat[i].y > 533) {
                plat[i].y = 0;
                plat[i].x = rand() % 400;
                ++sc;

                            fs[4]++;
                            if (fs[4] > 9) {
                                fs[4] -= 10;

                                fs[3]++;
                                if (fs[3] > 9) {
                                    fs[3] -= 10;

                                    fs[2]++;
                                    if (fs[2] > 9) {
                                        fs[2] -= 10;

                                        fs[1]++;
                                        if (fs[1] > 9) {
                                            fs[1] -= 10;

                                            fs[0]++;
                                            if (fs[0] > 9)
                                                fs[0] -= 10;
                                            score[0].setTextureRect(IntRect(30 * fs[0], 0, 30, 47));
                                        }
                                        score[1].setTextureRect(IntRect(30 * fs[1], 0, 30, 47));
                                    }
                                    score[2].setTextureRect(IntRect(30 * fs[2], 0, 30, 47));
                                }
                                score[3].setTextureRect(IntRect(30 * fs[3], 0, 30, 47));
                            }
                            score[4].setTextureRect(IntRect(30 * fs[4], 0, 30, 47));
                        }
                    }   
    }

    void drawPlatforms(RenderWindow& app, Sprite& sPlat) {
        for (size_t i = 0; i < plat.size(); ++i) {
            sPlat.setPosition(plat[i]);
            app.draw(sPlat);
        }
    }

    float getPlatformX(int index) {
        if (index >= 0 && index < plat.size()) {
            return plat[index].x;
        }
        return 0.0f;
    }

    float getPlatformY(int index) {
        if (index >= 0 && index < plat.size()) {
            return plat[index].y;
        }
        return 0.0f;
    }

    void setPlatformX(int index, float x) {
        if (index >= 0 && index < plat.size()) {
            plat[index].x = x;
        }
    }

    void setPlatformY(int index, float y) {
        if (index >= 0 && index < plat.size()) {
            plat[index].y = y;
        }
    }

    void TouchToGreenPlatform(int x, int y, float& dy, int index)
    {
        if ((x + 50 > getPlatformX(index)) && (x + 20 < getPlatformX(index) + 68) && (y + 70 > getPlatformY(index)) && (y + 70 < getPlatformY(index) + 14) && (dy > 0))
        {
            dy = -10;
        }
    }
    int Size()
    {
        return plat.size();
    }



protected:
    std::vector<Vector2f> plat;

};

class WhitePlatform : virtual public Platform {
public:

    void settakenWhitePlatforms(int index, bool boolean) {
        if (index >= 0 && index < plat.size()) {
            takenWhitePlatforms[index] = boolean;
        }
    }
    bool gettakenWhitePlatforms(int index) {
        if (index >= 0 && index < plat.size()) {
            return takenWhitePlatforms[index];
        }
        return false;
    }




     void movePlatforms(float dy, int& y, int& h, Sprite score[], int fs[], int& sc) override {
        for (size_t i = 0; i < plat.size(); ++i) {
            y = h;
            plat[i].y = plat[i].y + dy;
            if (plat[i].y > 533) {
                if (gettakenWhitePlatforms(i))
                    settakenWhitePlatforms(i, false);
                sc++;
                plat[i].y = 0;
                plat[i].x = rand() % 400;

                fs[4]++;
                if (fs[4] > 9) {
                    fs[4] -= 10;

                    fs[3]++;
                    if (fs[3] > 9) {
                        fs[3] -= 10;

                        fs[2]++;
                        if (fs[2] > 9) {
                            fs[2] -= 10;

                            fs[1]++;
                            if (fs[1] > 9) {
                                fs[1] -= 10;

                                fs[0]++;
                                if (fs[0] > 9)
                                    fs[0] -= 10;
                                score[0].setTextureRect(IntRect(30 * fs[0], 0, 30, 47));
                            }
                            score[1].setTextureRect(IntRect(30 * fs[1], 0, 30, 47));
                        }
                        score[2].setTextureRect(IntRect(30 * fs[2], 0, 30, 47));
                    }
                    score[3].setTextureRect(IntRect(30 * fs[3], 0, 30, 47));
                }
                score[4].setTextureRect(IntRect(30 * fs[4], 0, 30, 47));
            }
        }
    }
    

    void TouchToWhitePlatform(int x, int y, float& dy, int index)
    {
        if ((x + 50 > getPlatformX(index)) && (x + 20 < getPlatformX(index) + 68) && (y + 70 > getPlatformY(index)) && (y + 70 < getPlatformY(index) + 14) && (dy > 0) && !gettakenWhitePlatforms(index))
        {

            dy = -10;

            settakenWhitePlatforms(index, true);
        }
    }


protected:
    bool takenWhitePlatforms[5] = { false, false, false, false, false };
};






class TextureManager {
public:
    TextureManager() {
        LoadTextures();
    }

    Texture& getTexture(int index) {
        return textures[index];
    }

private:
    Texture textures[9];

    void LoadTextures() {
        if (!textures[0].loadFromFile("C:/Users/artur/OneDrive/Рабочий стол/дудл/background.png"))
            std::cerr << "Failed to load background.png" << std::endl;

        if (!textures[1].loadFromFile("C:/Users/artur/OneDrive/Рабочий стол/дудл/platform.png"))
            std::cerr << "Failed to load platform.png" << std::endl;

        if (!textures[2].loadFromFile("C:/Users/artur/OneDrive/Рабочий стол/дудл/doodle.png"))
            std::cerr << "Failed to load doodle.png" << std::endl;

        if (!textures[3].loadFromFile("C:/Users/artur/OneDrive/Рабочий стол/дудл/WhitePlatform.png"))
            std::cerr << "Failed to load WhitePlatform.png" << std::endl;

        if (!textures[4].loadFromFile("C:/Users/artur/OneDrive/Рабочий стол/дудл/BluePlatfrom.png"))
            std::cerr << "Failed to load BluePlatfrom.png" << std::endl;

        if (!textures[5].loadFromFile("C:/Users/artur/OneDrive/Рабочий стол/дудл/score.png"))
            std::cerr << "Failed to load score.png" << std::endl;

        if (!textures[6].loadFromFile("C:/Users/artur/OneDrive/Рабочий стол/дудл/gameover.png"))
            std::cerr << "Failed to load score.png" << std::endl;
        if (!textures[7].loadFromFile("C:/Users/artur/OneDrive/Рабочий стол/дудл/boom.png"))
            std::cerr << "Failed to load score.png" << std::endl;
        if (!textures[8].loadFromFile("C:/Users/artur/OneDrive/Рабочий стол/дудл/yellow.png"))
            std::cerr << "Failed to load score.png" << std::endl;
    }
};


class MovingPlatform : virtual public Platform {
public:

    void createPlatform(int count) override {
        for (int i = 0; i < count; ++i) {
            Vector2f p;
            p.x = rand() % 400;
            p.y = rand() % 533;
            int move;
            move = rand() % 2 == 0 ? -1 : 1;
            direction.push_back(move);
            plat.push_back(p);
        }
    }



  void update() {
        for (size_t i = 0; i < plat.size(); ++i) {
            plat[i].x += direction[i] * 5;
            if (plat[i].x > 366)
                direction[i] = -1; // Если платформа достигла правой границы, изменяем направление на лево
            if (plat[i].x < 0)
                direction[i] = 1; // Если платформа достигла левой границы, изменяем направление на право
        }
    }
protected:
    std::vector<int> direction;
};


class ExtremePlatform :  public WhitePlatform, public MovingPlatform
{
public:


    void drawplatforms(RenderWindow& app, Sprite& sPlat) {
        WhitePlatform::drawPlatforms(app, sPlat);
    }

    void createplatform(int count)  {
        MovingPlatform::createPlatform(count);
    }

    void moveplatforms(float dy, int& y, int& h, Sprite score[], int fs[], int& sc) {
        WhitePlatform::movePlatforms(dy,y,h,score,fs,sc);
    }

    

private:

};


class Level
{
public:
    void SetLevel()
    {
        std::cout << "Виберіть рівень гри (easy, medium або hard): ";
        std::cin >> level;
    }

    std::string GetLevel()
    {
        return level;
    }




private:
    std::string level;
};
class EasyLevel
{
public:
    void playLevel(RenderWindow& app, Game& game, Platform& Green_Platform)
    {
        Green_Platform.createPlatform(10);
    }
};

class MediumLevel
{
public:
    void playLevel(RenderWindow& app, Game& game, Platform& Green_Platform, WhitePlatform& White_Platform)
    {
        Green_Platform.createPlatform(5);
        White_Platform.createPlatform(5);
    }
};

class HardLevel
{
public:
    void playLevel(RenderWindow& app, Game& game, MovingPlatform& Blue_Platform, WhitePlatform& White_Platform, Platform& Green_Platform, ExtremePlatform& Yellow_Platfrom)
    {
        Green_Platform.createPlatform(2);
        White_Platform.createPlatform(2);
        Blue_Platform.createPlatform(2);
        Yellow_Platfrom.createplatform(2);
    }
};



class Score
{
public:
    Score()
    {
        the_best_score = 0;
        current_score = 0; 
    }
    void SetFS(int index, int number)
    {
        fs[index] = number;
    }
    int* GetFS()
    {   
        return fs;
    }
    void SetScore(int number)
    {
        if( number > the_best_score)
        the_best_score = number;
    }
    int& GetCurrentScore()
    {
        return current_score;
    }
    int GetTheBestScore()
    {
        return the_best_score;
    }
private:
    int fs[5];
    int the_best_score;
    int current_score;
};

class traps : public Game
{
public:
    traps(Sprite& b) : sBomb(b) // Передача по ссылке
    {
        i = 1;
        x = 200; 
        y = -1;
        dy = 2.5;
        sBomb.setPosition(-100, -100);
    }

    void createBomb(int number)
    {
        if (number > 50 * i)
        {
            
            ++i;
            sBomb.setPosition(200, 0);// Изменение объекта Sprite через ссылку
            y = 0;
            std::cout << i << std::endl;
        }
    }

    void down()
    {
        if (y >= 0)
        {
            y += dy;
            sBomb.setPosition(200, y);
        }
        if (y > 533)
        {
            sBomb.setPosition(-100, -100);
            y = -1;
        }
    }

private:
    int i;
    Sprite& sBomb; // Ссылка на объект Sprite
};


int main() {


    srand(time(0));

    RenderWindow app(VideoMode(400, 533), "MyDoodleGame");

    app.setFramerateLimit(60);
    Level level;

    level.SetLevel();

    TextureManager textureManager;


    Sprite sBackground(textureManager.getTexture(0)),
        sPlat(textureManager.getTexture(1)),
        sPers(textureManager.getTexture(2)),
        sWhitePlat(textureManager.getTexture(3)),
        sBluePlatfrom(textureManager.getTexture(4)),
        sGameOver(textureManager.getTexture(6)),
        sBomb(textureManager.getTexture(7)),
        sYellowPlatform(textureManager.getTexture(8));

    sGameOver.setPosition(0, 150);

    bool gameover = true;
       
    Game game;

    traps bomb(sBomb);
    

    EasyLevel easyLevel;
    MediumLevel mediumLevel;
    HardLevel hardLevel;

    WhitePlatform White_Platform;
    Platform Green_Platform;
    MovingPlatform Blue_Platform;
    ExtremePlatform YellowPlatform;

    
    Score sc;
    Sprite score[5];
    for (int i = 0; i < 5; i++) {
        score[i].setTexture(textureManager.getTexture(5));
        score[i].setTextureRect(IntRect(0, 0, 30, 47));
        score[i].setPosition(35 * i, 0);
        sc.SetFS(i,0);
    }

    if (level.GetLevel() == "e") {
        easyLevel.playLevel(app, game, Green_Platform);
    }
    else if (level.GetLevel() == "m") {
        mediumLevel.playLevel(app, game, Green_Platform, White_Platform);
    }
    else if (level.GetLevel() == "ha") {
        hardLevel.playLevel(app, game, Blue_Platform, White_Platform, Green_Platform, YellowPlatform);
    }

    int Size = Green_Platform.Size();


    while (app.isOpen()) {
        Event e;
        while (app.pollEvent(e)) {
            if (e.type == Event::Closed)
                app.close();
        }

        app.clear();

        if (Keyboard::isKeyPressed(Keyboard::Right)) game.x += 4;
        if (Keyboard::isKeyPressed(Keyboard::Left)) game.x -= 4;

        Blue_Platform.update();
        YellowPlatform.update();
        game.TurnDown();


        if (game.x > 400)
            game.x = -40;
        if (game.x < -40)
            game.x = 400;

        bomb.createBomb(sc.GetCurrentScore());
        bomb.down();

        if (game.y > 520) gameover = false;

        if (game.y < game.h)
        {
            Green_Platform.movePlatforms(-game.dy, game.y, game.h, score, sc.GetFS(), sc.GetCurrentScore());
            if (level.GetLevel() == "m" or level.GetLevel() == "ha")
                White_Platform.movePlatforms(-game.dy, game.y, game.h, score, sc.GetFS(), sc.GetCurrentScore());
            if (level.GetLevel() == "ha")
            {
                Blue_Platform.movePlatforms(-game.dy, game.y, game.h, score, sc.GetFS(), sc.GetCurrentScore());
                YellowPlatform.moveplatforms(-game.dy, game.y, game.h, score, sc.GetFS(), sc.GetCurrentScore());
            }


        }

        for (int i = 0; i < Size; ++i)
        {
            Green_Platform.TouchToGreenPlatform(game.x, game.y, game.dy, i);
            if (level.GetLevel() == "m" or level.GetLevel() == "ha")
                White_Platform.TouchToWhitePlatform(game.x, game.y, game.dy, i);
            if (level.GetLevel() == "ha")
            {
                Blue_Platform.TouchToGreenPlatform(game.x, game.y, game.dy, i);
                YellowPlatform.TouchToWhitePlatform(game.x, game.y, game.dy, i);
            }
        }
  
        
        sPers.setPosition(game.x, game.y);

        app.draw(sBackground);
        app.draw(sPers);

        Green_Platform.drawPlatforms(app, sPlat);
        White_Platform.drawPlatforms(app, sWhitePlat);
        Blue_Platform.drawPlatforms(app, sBluePlatfrom);
        YellowPlatform.drawplatforms(app, sYellowPlatform);

        app.draw(sBomb);

        for (int i = 0; i < 5; ++i)
            app.draw(score[i]);

        if (!gameover)
        {
            app.draw(sGameOver);
            sc.SetScore(sc.GetCurrentScore());
            std::cout << sc.GetTheBestScore() << std::endl;
            level.SetLevel();
        }

        app.display();
    }

    return 0;
}