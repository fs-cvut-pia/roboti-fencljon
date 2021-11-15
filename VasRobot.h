#ifndef VASROBOT_H_INCLUDED
#define VASROBOT_H_INCLUDED

#include "Bludiste.h"
#include "StavUzlu.h"

#include <string>
#include <iostream>

// Tuto tridu nemente
// Obsahuje abstraktni tridu - interface, ktery musi trida vaseho robota implementovat

class VasRobot : public Prohledavac {
public:
    StavUzlu stav[100][100];
    bool start(Bludiste & map) {
        for(int i = 0; i<100; i++) {
            for(int j = 0; j<100; j++) {
                stav[i][j].navstiven = false;
            }
        }
        stav[0][0].navstiven = true;
        return true;
    }
    bool start(BludisteOdkryte & map) {
        return true;
    }
    bool stop() {
        return true;
    }
    void krok(Bludiste & map) {
        // std::cout << map.pocet_kroku() << " kroku, poloha [" << map.poloha().x << ";" << map.poloha().y << "]\n";
        int poloha_x = map.poloha().x;
        int poloha_y = map.poloha().y;
        if(map.cil()) return;
        bool pohyb = false;
        if(poloha_x > 0 && !stav[poloha_x-1][poloha_y].navstiven) {
            stav[poloha_x-1][poloha_y].navstiven = true;
            if (map.vlevo()) {
                pohyb = true;
            }
        }
        if(!pohyb && !stav[poloha_x][poloha_y+1].navstiven) {
            stav[poloha_x][poloha_y+1].navstiven = true;
            if (map.nahoru()) {
                pohyb = true;
            }
        }
        if(!pohyb && !stav[poloha_x+1][poloha_y].navstiven) {
            stav[poloha_x+1][poloha_y].navstiven = true;
            if (map.vpravo()) {
                pohyb = true;
            }
        }
        if(!pohyb && poloha_y > 0 && !stav[poloha_x][poloha_y-1].navstiven) {
            stav[poloha_x][poloha_y-1].navstiven = true;
            if (map.dolu()) {
                pohyb = true;
            }
        }
        if(pohyb) {
            stav[map.poloha().x][map.poloha().y].predchudce_x = poloha_x;
            stav[map.poloha().x][map.poloha().y].predchudce_y = poloha_y;
        } else {
            int predchudce_x = stav[poloha_x][poloha_y].predchudce_x;
            int predchudce_y = stav[poloha_x][poloha_y].predchudce_y;
            std::cout << "Zpet na [" << predchudce_x << ";" << predchudce_y << "]\n";
            if(predchudce_x != poloha_x) {
                if(predchudce_x > poloha_x) {
                    map.vpravo();
                } else {
                    map.vlevo();
                }
            } else {
                if(predchudce_y > poloha_y) {
                    map.nahoru();
                } else {
                    map.dolu();
                }
            }
        }
    }
    void krok(BludisteOdkryte & map) {
    }
    std::string jmeno() {
        return "MujRobot";
    }
};


#endif // VASROBOT_H_INCLUDED
