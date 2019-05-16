//
// Created by gabriele on 17/12/18.
//

#ifndef P_STAT_H
#define P_STAT_H

typedef struct stat_t* stat_p;

stat_p initStat();
void setHP(stat_p stat, int hp);
void setMP(stat_p stat, int mp);
void setATK(stat_p stat, int atk);
void setDEF(stat_p stat, int def);
void setMAG(stat_p stat, int mag);
void setSPR(stat_p stat, int spr);
int getHP(stat_p stat);
int getMP(stat_p stat);
int getATK(stat_p stat);
int getDEF(stat_p stat);
int getMAG(stat_p stat);
int getSPR(stat_p stat);
void stampaStatistiche(stat_p stat);
void controlloStatisticheMinoriDiZero(stat_p stat);



#endif //P_STAT_H
