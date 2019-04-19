#ifndef SORT_VIEW_HPP
#define SORT_VIEW_HPP

#include "base_view.hpp"

using namespace std;
using namespace sf;

class SortView{
private:
    int _begin;
    int _end;
    enum ViewOption{BAR, DOT};
    ViewOption _voption;
    float _thick{9.0};
    float _delta{11.0};
    float xbegin{20};
    float ybegin{600};
    RenderTexture painel;
public:
    SortView()
    {
        _begin = 0;
        _end = 0;
        _voption = BAR;
        painel.create(800, 600);
    }

    void set_faixa(int begin, int end){
        _begin = begin;
        _end = end;
    }

    void set_thick(int size){
        int size_default = 70;
        _thick = size_default*_thick/size;
        _delta = size_default*_delta/size;
    }

    void set_bar_view(){
        _voption = BAR;
    }

    void set_dot_view(){
        _voption = DOT;
    }

    void plot(float x, float size, Color cor_linha){
        float ydown = 0;
        if(_voption == DOT)
            ydown = -size + 5;

        painel.draw(dsLine(Vector2f(_delta * x + xbegin, ybegin + ydown),
                           Vector2f(_delta * x + xbegin, ybegin - size),
                           _thick, cor_linha));
    }

    void show(const vector<int> &vet, vector<int> pos = {}, string cores = ""){
        if(my_window->isOpen() == false)
            return;

        painel.clear();
        ColorMap * cmap = ColorMap::get_instance();
        int tam = vet.size();
        for(int x = 0; x < tam; x++){
            Color cor_linha = Color::White;
            for(int k = 0; k < (int)pos.size(); k++){
                if(x == pos[k]){
                    cor_linha = cmap->get(cores[k]);
                }
            }
            plot(x, vet[x], cor_linha);
        }

        painel.display();
        my_player->_push(painel.getTexture());
    }
};

static SortView sortview;

void view_lock(){
    my_player->wait();
}

#endif