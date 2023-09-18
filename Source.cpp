#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

class Platform {
public:
    Platform() {
        for (int i = 0; i < 10; ++i) {
            plat[i].x = rand() % 400;
            plat[i].y = rand() % 533;
        }
    }

    void movePlatforms(float dy, int& y, int& h) {
        for (int i = 0; i < 10; ++i)
        {
            y = h;
            y = h;
            plat[i].y = plat[i].y + dy; // Додати dy до платформи
            if (plat[i].y > 533)
            {
                plat[i].y = 0;
                plat[i].x = rand() % 400;
            }
        }
    }

    void drawPlatforms(RenderWindow& app, Sprite& sPlat) {
        for (int i = 0; i < 10; ++i) {
            sPlat.setPosition(getPlatformX(i), getPlatformY(i));
            app.draw(sPlat);
        }
    }

    float getPlatformX(int index) {
        if (index >= 0 && index < 10) {
            return plat[index].x;
        }
        return 0.0f; // Return 0 if index is out of bounds
    }

    float getPlatformY(int index) {
        if (index >= 0 && index < 10) {
            return plat[index].y;
        }
        return 0.0f; // Return 0 if index is out of bounds
    }

private:
    Vector2f plat[20];
};


class WhitePlatform
{
public:

private:


};

class MovingPlatform
{
public:

private:


};

class Level
{

};

class HardLewvel
{

};

class EasyLevel
{
    
};

class NormalLevel
{

};

class Rune
{

};

int main() {
    srand(time(0));
    RenderWindow app(VideoMode(400, 533), "MyDoodleGame");
    app.setFramerateLimit(60);

    Texture t1, t2, t3;
    t1.loadFromFile("C:/Users/artur/OneDrive/Рабочий стол/дудл/background.png");
    t2.loadFromFile("C:/Users/artur/OneDrive/Рабочий стол/дудл/platform.png");
    t3.loadFromFile("C:/Users/artur/OneDrive/Рабочий стол/дудл/doodle.png");

    Sprite sBackground(t1), sPlat(t2), sPers(t3);

    int x = 100, y = 100, h = 200;
    float dx = 0, dy = 0;

    Platform platform;

    while (app.isOpen()) {
        Event e;
        while (app.pollEvent(e)) {
            if (e.type == Event::Closed)
                app.close();
        }

        app.clear();

        if (Keyboard::isKeyPressed(Keyboard::Right)) x += 3;
        if (Keyboard::isKeyPressed(Keyboard::Left)) x -= 3;

        dy += 0.2;
        y += dy;

        if (y > 400) dy = -10;

        if (y < h)
            platform.movePlatforms(-dy, y, h);

        for (int i = 0; i < 10; ++i)
            if ((x + 50 > platform.getPlatformX(i)) && (x + 20 < platform.getPlatformX(i) + 68) && (y + 70 > platform.getPlatformY(i)) && (y + 70 < platform.getPlatformY(i) + 14) && (dy > 0))
                dy = -10;

        sPers.setPosition(x, y);

        app.draw(sBackground);
        app.draw(sPers);
        platform.drawPlatforms(app, sPlat);

        app.display();
    }

    return 0;
}