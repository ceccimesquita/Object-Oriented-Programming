#include <SFML/Graphics.hpp>
#include <iostream>

void setSize(sf::Sprite& sprite, int width, int height){
    auto dim = sprite.getLocalBounds();
    sprite.setScale((float) width / dim.width, (float) height / dim.height);
}

struct Entity{
    int x{0};
    int y{0};
    int step{0};
    sf::Sprite sprite;

    Entity(int x, int y, int step, sf::Texture& texture): x{x}, y{y}, step{step}, sprite{texture}{
        this->sprite.setTexture(texture);
    }

    void draw(sf::RenderWindow& window){
        this->sprite.setPosition(x * step, y * step);
        setSize(this->sprite,  step, step);
        window.draw(this->sprite);
    }
};

struct Board
{
    int nc{0};
    int nl{0};
    int step{0};
    sf::Sprite sprite;
    sf::RectangleShape rect;

    Board(int nc, int nl, int step, sf::Texture& texture): nc{nc}, nl{nl}, step{step}, sprite{texture}{
        this->sprite.setTexture(texture);
        setSize(this->sprite,  nc * step,nl * step);
        this->sprite.setPosition(0, 0);
        this->rect.setSize(sf::Vector2f(step, step));
        this->rect.setFillColor(sf::Color::Transparent);
        this->rect.setOutlineColor(sf::Color::Black);
        this->rect.setOutlineThickness(2);
    }

    void draw(sf::RenderWindow& window){
        window.draw(this->sprite);
        for(int i = 0; i < nl; i++){
            for(int j = 0; j < nc; j++){
                rect.setPosition(j * step, i * step);
                window.draw(rect);
            }
        }

    }
};




void movEntity(sf::Keyboard::Key key, Entity& entity, std::vector<sf::Keyboard::Key> move_keys){
    if(key == move_keys[0]){
        entity.y -= 1;
    }else if(key == move_keys[1]){
        entity.y += 1;
    }else if(key == move_keys[2]){
        entity.x -= 1;
    }else if(key == move_keys[3]){
        entity.x += 1;
    }
}

sf::Texture loadTexture(std::string path){
    sf::Texture texture;
    if(! texture.loadFromFile(path)){
        std::cout << "Error loading texture" << std::endl;
        exit(1);
    }
    return texture;
}

int main(){
    

    sf::Texture wolf_tex {loadTexture("lobol.png")};
    sf::Texture rebbit_tex {loadTexture("coelho.png")};
    sf::Texture grass_tex {loadTexture("grama.png")};

    const int STEP{100};

    Entity wolf(1, 1, STEP, wolf_tex);
    Entity rebbit(3, 3, STEP, rebbit_tex);
    Board board(7, 5, STEP, grass_tex);

    sf::RenderWindow window(sf::VideoMode(board.nc * STEP, board.nl * STEP), "SFML works!");


    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }else if(event.type == sf::Event::KeyPressed){
                movEntity(event.key.code, wolf, {sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right});
                movEntity(event.key.code, rebbit, {sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D});
            
            }
        }
    


        window.clear();
        board.draw(window);
        wolf.draw(window);
        rebbit.draw(window);
        window.display();
    }
    return 0;
}