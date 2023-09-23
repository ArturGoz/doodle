#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <vector>

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
    void createPlatform(int count) {
        for (int i = 0; i < count; ++i) {
            Vector2f p;
            p.x = rand() % 400;
            p.y = rand() % 533;
            plat.push_back(p);
        }
    }

    virtual void movePlatforms(float dy, int& y, int& h) {
        for (size_t i = 0; i < plat.size(); ++i) {
            y = h;
            plat[i].y = plat[i].y + dy;
            if (plat[i].y > 533) {
                plat[i].y = 0;
                plat[i].x = rand() % 400;
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

    void TouchToGreenPlatform(int x, int y, float& dy, int index)
    {
        if ((x + 50 > getPlatformX(index)) && (x + 20 < getPlatformX(index) + 68) && (y + 70 > getPlatformY(index)) && (y + 70 < getPlatformY(index) + 14) && (dy > 0))
        {
            dy = -10;
        }
    }


protected:
    std::vector<Vector2f> plat;
};

class WhitePlatform : public Platform {
public:

    //поліморфізм
    void drawPlatforms(RenderWindow& app, Sprite& sWhitePlat) {
        for (int i = 0; i < plat.size(); ++i) {
          //  sPlat.setPosition(getPlatformX(i), getPlatformY(i));
            sWhitePlat.setPosition(getPlatformX(i), getPlatformY(i));
        //    app.draw(sPlat);
            app.draw(sWhitePlat);
        }
    }
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
    void movePlatforms(float dy, int& y, int& h) override {
        for (size_t i = 0; i < plat.size(); ++i) {
            y = h;
            plat[i].y = plat[i].y + dy;
            if (plat[i].y > 533) {
                if(gettakenWhitePlatforms(i))
                settakenWhitePlatforms(i, false);
                plat[i].y = 0;
                plat[i].x = rand() % 400;
            }
        }
    }

    void TouchToWhitePlatform(int x, int y, float& dy, int index)
    {
        if ((x + 50 > getPlatformX(index)) && (x + 20 < getPlatformX(index) + 68) && (y + 70 > getPlatformY(index)) && (y + 70 < getPlatformY(index) + 14) && (dy > 0) && !gettakenWhitePlatforms(index))
        {

            dy = -10;

            settakenWhitePlatforms(index , true);
        }
    }


private:
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
    Texture textures[5]; 

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
    }
};

class MovingPlatform : public Platform
{

};


int main() {


    srand(time(0));

    RenderWindow app(VideoMode(400, 533), "MyDoodleGame");

    app.setFramerateLimit(60);

    TextureManager textureManager;

    Sprite sBackground(textureManager.getTexture(0)),
        sPlat(textureManager.getTexture(1)),
        sPers(textureManager.getTexture(2)), 
        sWhitePlat(textureManager.getTexture(3)), 
        sBluePlatfrom(textureManager.getTexture(4));
    
    Game game;


    WhitePlatform White_Platform;
    Platform Green_Platform;

    Green_Platform.createPlatform(5);
    White_Platform.createPlatform(5);

    while (app.isOpen()) {
        Event e;
        while (app.pollEvent(e)) {
            if (e.type == Event::Closed)
                app.close();
        }

        app.clear();

        if (Keyboard::isKeyPressed(Keyboard::Right)) game.x += 4;
        if (Keyboard::isKeyPressed(Keyboard::Left)) game.x -= 4;

        game.TurnDown();

        if (game.x > 400)
            game.x = -40;
        if (game.x < -40)
            game.x = 400;

        if (game.y > 500) game.dy = -10;
        if (game.y < game.h)
        {
            Green_Platform.movePlatforms(-game.dy, game.y, game.h);
            White_Platform.movePlatforms(-game.dy, game.y, game.h);
        }

        for (int i = 0; i < 5; ++i)
        {
                Green_Platform.TouchToGreenPlatform(game.x, game.y, game.dy, i);
                White_Platform.TouchToWhitePlatform(game.x, game.y, game.dy, i);
        }

        sPers.setPosition(game.x, game.y);

        app.draw(sBackground);
        app.draw(sPers);
        Green_Platform.drawPlatforms(app, sPlat);
        White_Platform.drawPlatforms(app,sWhitePlat);

        app.display();
    }

    return 0;
}
