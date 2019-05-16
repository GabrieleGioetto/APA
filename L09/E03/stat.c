//
// Created by gabriele on 17/12/18.
//
#include <stdio.h>
#include <stdlib.h>
#include "stat.h"


struct stat_t{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
};

stat_p initStat(){
    return malloc(sizeof(struct stat_t));
}

void setHP(stat_p stat, int hp){
    stat->hp = hp;
}

void setMP(stat_p stat, int mp){
    stat->mp = mp;
}


void setATK(stat_p stat, int atk){
    stat->atk = atk;
}


void setDEF(stat_p stat, int def){
    stat->def = def;
}


void setMAG(stat_p stat, int mag){
    stat->mag = mag;
}


void setSPR(stat_p stat, int spr){
    stat->spr = spr;
}

int getHP(stat_p stat){
    return stat->hp;
}

int getMP(stat_p stat){
    return stat->mp;
}

int getATK(stat_p stat){
    return stat->atk;
}

int getDEF(stat_p stat){
    return stat->def;
}

int getMAG(stat_p stat){
    return stat->mag;
}

int getSPR(stat_p stat){
    return stat->spr;
}

void controlloStatisticheMinoriDiZero(stat_p stat) {
    if(stat->hp < 1)
        stat->hp  = 1;
    if(stat->mp  < 1)
        stat->mp  = 1;
    if(stat->atk < 1)
        stat->atk = 1;
    if(stat->def < 1)
        stat->def = 1;
    if(stat->mag < 1)
        stat->mag = 1;
    if(stat->spr < 1)
        stat->spr = 1;
}


void stampaStatistiche(stat_p stat) {
    printf("%d ", stat->hp);
    printf("%d ", stat->atk);
    printf("%d ", stat->def);
    printf("%d ", stat->mag);
    printf("%d ", stat->mp);
    printf("%d ", stat->spr);
    printf("\n");
}
