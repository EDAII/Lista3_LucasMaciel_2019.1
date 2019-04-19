#ifndef COLORMAP_H
#define COLORMAP_H
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <cmath>
#include <string>

#include <map>
#define my_colormap (ColorMap::get_instance())

class ColorMap
{
private:
    std::map<char, sf::Color> mapa;

    ColorMap()
    {
        mapa['r'] = sf::Color::Red;
        mapa['g'] = sf::Color::Green;
        mapa['b'] = sf::Color::Blue;
        mapa['y'] = sf::Color::Yellow;
        mapa['c'] = sf::Color::Cyan;
        mapa['m'] = sf::Color::Magenta;
        mapa['w'] = sf::Color::White;
        mapa['k'] = sf::Color::Black;
    }

public:
    static ColorMap *get_instance()
    {
        static ColorMap map;
        return &map;
    }

    std::string color_list()
    {
        std::string colors;
        char c[2];
        c[1] = '\0';
        for (const std::pair<char, sf::Color> &p : mapa)
        {
            c[0] = p.first;
            colors.append(c);
        }
        return colors;
    }

    void set(char color, int R, int G, int B)
    {
        mapa[color] = sf::Color(R, G, B);
    }

    sf::Color get(char color)
    {
        auto it = mapa.find(color);
        if (it == mapa.end())
            return sf::Color::White;
        return it->second;
    }

    bool exists(char color)
    {
        return (mapa.find(color) != mapa.end());
    }

    //void update(const sf::Keyboard::Key key, char *cor);
    char sf2char(sf::Keyboard::Key key)
    {
        if (key >= sf::Keyboard::A and key <= sf::Keyboard::Z)
            return key - sf::Keyboard::A + 'a';
        if (key >= sf::Keyboard::Num0 and key <= sf::Keyboard::Num9)
            return key - sf::Keyboard::Num0 + '0';
        if (key >= sf::Keyboard::Numpad0 and key <= sf::Keyboard::Num9)
            return key - sf::Keyboard::Numpad0 + '0';
        return '0';
    }
};
#endif // COLORMAP_H

//#############################################################################

#ifndef SFLINE_H
#define SFLINE_H

#include <SFML/Graphics.hpp>

class dsLine : public sf::Drawable
{
public:
    dsLine(const sf::Vector2f &point1, const sf::Vector2f &point2,
           float thickness = 1.0, sf::Color color = sf::Color::Red) : _begin(point1), _end(point2), _color(color), _thickness(thickness)
    {
        update_vertices();
    }

    sf::Vector2f get_begin()
    {
        return _begin;
    }

    sf::Vector2f get_end()
    {
        return _end;
    }

    float get_thickness()
    {
        return _thickness;
    }

    sf::Color get_color()
    {
        return _color;
    }

    void set_color(sf::Color color)
    {
        this->_color = color;
        update_vertices();
    }

    void set_end(sf::Vector2f end)
    {
        this->_end = end;
        update_vertices();
    }

    void set_begin(sf::Vector2f begin)
    {
        this->_begin = begin;
        update_vertices();
    }

    void set_thickness(float thickness)
    {
        _thickness = thickness;
        update_vertices();
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        (void)states;
        target.draw(_vertices, 4, sf::Quads);
    }

private:
    sf::Vector2f _begin;
    sf::Vector2f _end;
    sf::Vertex _vertices[4];
    sf::Color _color;
    float _thickness;

    void update_vertices()
    {
        sf::Vector2f direction = _end - _begin;
        sf::Vector2f unitDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
        sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

        sf::Vector2f offset = (_thickness / 2.f) * unitPerpendicular;

        _vertices[0].position = _begin + offset;
        _vertices[1].position = _end + offset;
        _vertices[2].position = _end - offset;
        _vertices[3].position = _begin - offset;

        for (int i = 0; i < 4; ++i)
            _vertices[i].color = _color;
    }
};

#endif // SFLINE_H

//####################################################################################

#ifndef SFTEXT_H
#define SFTEXT_H

#include <SFML/Graphics.hpp>
#include <iostream>

class sfText : public sf::Text
{
public:
    sfText(sf::Vector2f pos, std::string texto, sf::Color color = sf::Color::White, int size = 16)
    {
        this->setFont(*this->get_default_font());
        this->setFillColor(color);
        this->setOutlineColor(color);
        this->setPosition(pos);
        this->setString(texto);
        this->setCharacterSize(size);
    }

private:
    static sf::Font *get_default_font()
    {
        const std::string _path = "font.ttf";
        static sf::Font font;
        static bool init = true;
        if (init)
        {
            init = false;
            if (!font.loadFromFile(_path))
                std::cerr << "Font " << _path << " nao encontrada." << std::endl;
        }
        return &font;
    }
};

#endif // SFTEXT_H

#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <vector>
#include <SFML/Graphics.hpp>

class MyWindow : public sf::RenderWindow
{

private:
    static const int altura = 600;
    static const int largura = 800;

public:
    MyWindow() : sf::RenderWindow(sf::VideoMode(largura, altura), "QXCODE ED")
    {
        this->setFramerateLimit(30);
    }

    void processar_close_resize(const sf::Event &evt)
    {
        if (evt.type == sf::Event::Closed)
            this->close();
        if (evt.type == sf::Event::Resized)
            this->setView(sf::View(sf::FloatRect(0, 0, evt.size.width, evt.size.height)));
    }
};

#endif // MYWINDOW_H

//################################################################################

#ifndef MBUFFER_H
#define MBUFFER_H

#include <list>
#include <iostream>

using namespace std;

template <typename T>
class MBuffer
{
private:
    uint _indice;
    uint _first;
    uint _max_size; //maximo a frente ou atras
    int _count_swap;
    char *_name_method;
    typename std::list<T>::iterator _it;
    std::list<T> _list;

public:
    MBuffer(uint max_size, T first)
    {
        //inserindo uma funcao vazia que nao faz nada so pra inicializar
        //os indices e o vetor
        _list.push_back(first);
        _it = _list.begin();
        _indice = 0;
        _first = 0;
        _max_size = max_size;
        _count_swap = 0;
        _name_method = (char *)"";
    }

    void set_max_size(uint size)
    {
        _max_size = size;
    }

    bool exists(uint indice)
    {
        if (indice >= _first)
            if (indice < _first + _list.size())
                return true;
        return false;
    }

    bool go_to(uint indice)
    {
        if (exists(indice))
        {
            if (indice > pos_actual())
            {
                go_foward(indice - pos_actual());
            }
            if (indice < pos_actual())
            {
                go_back(pos_actual() - indice);
                return true;
            }
            return true;
        }
        return false;
    }

    void push(const T &t)
    {
        _list.push_back(t);
        if (size() > (int)_max_size)
        {
            _list.pop_front();
            _first++;
            if (_indice > 0)
                _indice--;
            else
                _indice = 0;
        }
    }

    bool is_full()
    {
        return _list.size() >= _max_size;
    }

    int size()
    {
        return _list.size();
    }

    const T &get_it()
    {
        return *_it;
    }

    // uint pos_first(){
    //     return _first;
    // }

    uint pos_actual()
    {
        return _first + _indice;
    }

    int get_count_swap()
    {
        return _count_swap;
    }

    char *get_name_method()
    {
        return _name_method;
    }

    uint pos_last()
    {
        return _first + _list.size() - 1;
    }

    //se nao conseguiu andar pra frente eh porque nao conseguiu dar todos
    //os passos por falta de estados
    bool go_foward(uint steps, int count_swap = 0, char *name = (char *)"")
    {
        if (_indice + steps < _list.size())
        {
            _indice += steps;
            if (count_swap != 0)
                _count_swap = count_swap;
            if (name != "")
                _name_method = name;
            std::advance(_it, steps);
            return true;
        }
        return false;
    }

    void go_last()
    {
        _indice = _list.size() - 1;
        _it = std::prev(_list.end());
    }

    bool go_back(uint steps)
    {
        if (_indice >= steps)
        {
            _indice -= steps;
            while (steps--)
                _it = std::prev(_it);
            return true;
        }
        return false;
    }
    void go_first()
    {
        _indice = 0;
        _it = _list.begin();
    }
};

#endif // MBUFFER_H

//#####################################################################

#ifndef MPLAYER_H
#define MPLAYER_H

#include <iostream>
#include <string>
#include <cmath>
#include <list>
#include <queue>

#include <SFML/Graphics.hpp>

using namespace std;

// #define my_player (MPlayer::get_instance())

class MPlayer
{
private:
    sf::Clock _clock;
    MBuffer<sf::Texture> _buffer;
    bool _return_to_main{false};
    bool _finished{false};
    int _destiny{0}; //proximo estado a ser mostrado
    MyWindow *_mywindow;

public:
    sf::Color color_back{sf::Color::Black};
    sf::Color color_front{sf::Color::White};
    const uint offset_up = 40;
    bool autoplay{false};
    int jump{1}; //define o tamanho do salto

    MPlayer(MyWindow *mywindow) : _buffer(100, sf::Texture())
    {
        _mywindow = mywindow;
    }
    //Retorna o player
    // static MPlayer *get_instance()
    // {
    //     static MPlayer _player;
    //     return &_player;
    // }

    //Espera a janela ser fechada
    //se estava esperando um salto de varios estados,
    //volta a mostrar o estado atual
    virtual void wait()
    {
        _finished = true;
        show();
    }

    //Altera o tamanho do buffer
    virtual void set_buffer_size(uint size)
    {
        _buffer.set_max_size(size);
    }

    //Funcao utilizada pelo pintor para salvar os estado
    virtual void _push(const sf::Texture &texture, int count_swap = 0, char *name = (char *)"")
    {
        if (_mywindow->isOpen())
        {
            _buffer.push(texture);
            _buffer.go_foward(1, count_swap, name);
            show();
        }
    }

    virtual void show()
    {
        if (!_finished)
        {
            if (!_buffer.go_to(_destiny))
                return;
        }
        else
        {
            if (_destiny > (int)_buffer.pos_last())
            {
                _destiny = _buffer.pos_last();
                _buffer.go_last();
                autoplay = false;
            }
        }

        _return_to_main = false;
        while (_mywindow->isOpen())
        {
            if (!_finished)
                if (_return_to_main)
                    return;
            if (autoplay)
                walk(jump);
            process_input();
            _mywindow->clear(color_back);
            auto sprite = sf::Sprite(_buffer.get_it());
            auto wsize = _mywindow->getSize();
            auto ssizex = sprite.getLocalBounds().width;
            auto ssizey = sprite.getLocalBounds().height;
            sprite.setScale(sf::Vector2f(wsize.x / (float)ssizex, wsize.y / (float)ssizey));
            _mywindow->draw(sprite);
            print_label();
            _mywindow->display();
        }
    }

private:
    //processa a entrada do usuario
    void process_input()
    {
        sf::Event evt;

        while (_mywindow->pollEvent(evt))
        {
            _mywindow->processar_close_resize(evt);
            if (evt.type == sf::Event::KeyPressed)
            {
                if (evt.key.code == sf::Keyboard::Right)
                {
                    walk(jump);
                }
                else if (evt.key.code == sf::Keyboard::Left)
                {
                    walk(-jump);
                }
                else if (evt.key.code == sf::Keyboard::Return)
                {
                    autoplay = !autoplay;
                }
                else if (evt.key.code == sf::Keyboard::Up)
                {
                    jump *= 2;
                }
                else if (evt.key.code == sf::Keyboard::Down)
                {
                    if (jump > 1)
                        jump /= 2;
                }
            }
        }
        //        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){walk(jump * jump);}
        //        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){walk(-(jump * jump));}
    }

    //mostra os comandos na parte superior da tela
    void print_label()
    {

        std::string title_left = " Method\t\t|Jump|Swaps|Atual ";

        char estado[200];
        sprintf(estado, " %s\t|%4d|%4d |%4d ",
                _buffer.get_name_method(), jump, _buffer.get_count_swap(), _buffer.pos_actual());

        _mywindow->draw(sfText(sf::Vector2f(0, 0), title_left, color_front));
        std::string state = estado;
        if (_finished)
            state += "(Finalizado!)";
        else
            state += "(Processando)";
        _mywindow->draw(sfText(sf::Vector2f(0, 20), state, color_front));

        std::string title_right = " Step  Move |  Speed  | Autoplay";
        std::string teclas = " Left/Right | Up/Down | Enter   ";

        std::string autoOp = "                             ###";

        auto dim = _mywindow->getSize();
        float width = sfText(sf::Vector2f(0, 0), title_right).getLocalBounds().width;

        _mywindow->draw(sfText(sf::Vector2f(dim.x - width - 10, 0), title_right, color_front));
        _mywindow->draw(sfText(sf::Vector2f(dim.x - width - 10, 15), teclas, color_front));

        sf::Color colorAuto = sf::Color::Red;
        if (autoplay)
            colorAuto = sf::Color::Green;
        _mywindow->draw(sfText(sf::Vector2f(dim.x - width - 10, 15), autoOp, colorAuto));
        _mywindow->draw(dsLine(sf::Vector2f(0, 40), sf::Vector2f(dim.x, 40), 1, color_front));
    }

    //anda nos estados para frente e para trás chamando métodos do buffer
    void walk(int step)
    {
        int atual = _buffer.pos_actual();
        _destiny = atual + step;
        if (_destiny > (int)_buffer.pos_last())
            if (_finished)
                _destiny = _buffer.pos_last();
        if (step > 0)
        {
            if (!_buffer.go_to(_destiny))
            {
                _return_to_main = true;
                return;
            }
        }
        else
        {
            if (!_buffer.go_to(_destiny))
            {
                _buffer.go_first();
            }
        }
    }
};

#endif //MPLAYER_H