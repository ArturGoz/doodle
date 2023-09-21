#include <SFML/Graphics.hpp>
#include <time.h>
#include <vector>

using namespace sf;

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


protected:
    std::vector<Vector2f> plat;
};

class WhitePlatform : public Platform {
public:
    //поліморфізм
    void drawPlatforms(RenderWindow& app, Sprite& sPlat, Sprite& sWhitePlat) {
        for (int i = 0; i < 5; ++i) {
            sPlat.setPosition(getPlatformX(i), getPlatformY(i));
            sWhitePlat.setPosition(getPlatformX(i + 5), getPlatformY(i + 5));
            app.draw(sPlat);
            app.draw(sWhitePlat);
        }
    }
    void settakenWhitePlatforms(int index, bool boolean) {
        if (index >= 0 && index < 5) {
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
                settakenWhitePlatforms(i, false);
                plat[i].y = 0;
                plat[i].x = rand() % 400;
            }
        }
    }
protected:
    bool takenWhitePlatforms[5] = { false, false, false, false, false };
};

void LoadTextures(Texture& t1, Texture& t2, Texture& t3, Texture& t4, Texture& t5) {

    t1.loadFromFile("C:/Users/artur/OneDrive/Рабочий стол/дудл/background.png");
    t2.loadFromFile("C:/Users/artur/OneDrive/Рабочий стол/дудл/platform.png");
    t3.loadFromFile("C:/Users/artur/OneDrive/Рабочий стол/дудл/doodle.png");
    t4.loadFromFile("C:/Users/artur/OneDrive/Рабочий стол/дудл/WhitePlatform.png");
    t5.loadFromFile("C:/Users/artur/OneDrive/Рабочий стол/дудл/BluePlatfrom.png");

}

// Other classes remain the same

int main() {
    int WX = -1;
    srand(time(0));
    RenderWindow app(VideoMode(400, 533), "MyDoodleGame");
    app.setFramerateLimit(60);

    Texture t1, t2, t3, t4, t5;
    LoadTextures(t1, t2, t3, t4, t5);
    Sprite sBackground(t1), sPlat(t2), sPers(t3), sWhitePlat(t4), sBluePlatfrom(t5);

    int x = 100, y = 100, h = 200;
    float dx = 0, dy = 0;

    WhitePlatform platform;
    platform.createPlatform(10);
    while (app.isOpen()) {
        Event e;
        while (app.pollEvent(e)) {
            if (e.type == Event::Closed)
                app.close();
        }

        app.clear();

        if (Keyboard::isKeyPressed(Keyboard::Right)) x += 4;
        if (Keyboard::isKeyPressed(Keyboard::Left)) x -= 4;

        dy += 0.2;
        y += dy;

        if (y > 500) dy = -10;
      //  for (int i = 5; i < 10; ++i)
    //    {
      //      if (platform.getPlatformY(i)> 533)
       //         if(platform.gettakenWhitePlatforms(i - 5))
        //            platform.settakenWhitePlatforms(i - 5, false);
     //   }
        if (y < h)
            platform.movePlatforms(-dy, y, h);

        for (int i = 0; i < 10; ++i)
        {
            if (i < 5)
            {
                if ((x + 50 > platform.getPlatformX(i)) && (x + 20 < platform.getPlatformX(i) + 68) && (y + 70 > platform.getPlatformY(i)) && (y + 70 < platform.getPlatformY(i) + 14) && (dy > 0))
                {
                    dy = -10;
                }
            }
            else
            {
                if ((x + 50 > platform.getPlatformX(i)) && (x + 20 < platform.getPlatformX(i) + 68) && (y + 70 > platform.getPlatformY(i)) && (y + 70 < platform.getPlatformY(i) + 14) && (dy > 0)&& !platform.gettakenWhitePlatforms(i-5))
                {

                    dy = -10;
                    platform.settakenWhitePlatforms(i-5, true);
                    WX = i;
                }
            }
            
        }

        sPers.setPosition(x, y);

        app.draw(sBackground);
        app.draw(sPers);
        platform.drawPlatforms(app, sPlat, sWhitePlat);

        app.display();
    }

    return 0;
}
