#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <random>
#include <chrono>
#include <fstream>

int rand_uns(int min, int max) {
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    static std::default_random_engine e(seed);
    static std::uniform_int_distribution<int> d(min, max);
    return d(e);
}

int main()
{
    std::ofstream op("out2.csv", std::ios::binary);
    std::list<sf::CircleShape> trgls;
    for(int j = 1000; j < 7000; j += 1000) {
        for(int i = 0; i < j; ++i) {
            sf::CircleShape trgl(14, 3);
            trgl.setFillColor(sf::Color(rand_uns(0, 255), rand_uns(0, 255), rand_uns(0, 255)));
            trgl.setPosition(rand_uns(0, 966), 0);
            trgls.push_back(trgl);
        }
        int c = 0;
        int c1 = 0;
        sf::RenderWindow window(sf::VideoMode(980, 1000), "Lecon");
        auto begin = std::chrono::high_resolution_clock::now();
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            window.clear();
            for(auto & item : trgls) {
                item.move(0, rand_uns(1, 4));
                window.draw(item);
            }
            window.display();
            c++;
            if(c == 100) {
                c = 0;
                c1++;
                if(c1 == 2) {
                op << 100000./std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - begin).count() << " " << j << std::endl;
                std::cout << 100000./std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - begin).count() << " " << j << std::endl;
                c1 = 0;
                trgls.clear();
                break;
                }
                begin = std::chrono::high_resolution_clock::now();
            }
            for(auto it = trgls.begin(); it != trgls.end(); it++)
            if(it->getPosition().y > 1000) {
                it = trgls.erase(it);
                sf::CircleShape trgl(14, 3);
                trgl.setFillColor(sf::Color(rand_uns(0, 255), rand_uns(0, 255), rand_uns(0, 255)));
                trgl.setPosition(rand_uns(0, 966), 0);
                trgls.push_back(trgl);
            }

        }
    }
    return 0;
}
