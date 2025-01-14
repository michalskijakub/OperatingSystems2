#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <ncurses.h>
#include <signal.h>

#ifndef SERWER_FUNCTION_H
#define SERWER_FUNCTION_H


struct create_player
{
    char* name1;
    char* name2;
};
struct bestia_info
{
    int x;
    int y;

    int x_ostatnie;
    int y_ostatnie;

    int x_nowe;
    int y_nowe;

    int pom;

    int alive;
};

struct player_info
{
    int PID;
    int PID_serwer;
    int numer;
    int x_current;
    int y_current;
    int x_start;
    int y_start;
    int deaths;
    int coins_carried;
    int coins_brought;
    char request;
    char typ[10];
    char area[150][150];
    int runda;
    sem_t *sem_p1_pom;
    sem_t *sem_p1;
};

struct skarb_info
{
    int one_coin[1000][2];
    int count_one_coin;
    int treasure_coin[1000][2];
    int count_treasure_coin;
    int large_treasure_coin[1000][2];
    int count_large_treasure_coin;
    int count_drop_coin;
    int dropped_coin[1000][2];
    int value_all_dropped_coin[1000];
};

struct serwer_info
{
    int PID;

    int x_camp;
    int y_camp;

    int runda;
    char** mapa;
    int pom;

    struct player_info *player1;
    struct player_info *player2;

    struct skarb_info skarb;

    struct bestia_info bestia;
};

struct user_info
{
    struct serwer_info *serwer;
    int user;
};

struct pid_info
{
    int pid1;
    int pid2;
};

char* plansza();
char** pobierz_plansze();
void drukuj_plansze(char** tab);
void druk_info_plansza_s(struct serwer_info *serwer);
void druk_info_gracz_s();

void* bestia(void* pom);

void* quit_quit(void* pom);

void* serwer_serwer(void* pom);

void* gracz_fun(void* pom);

int random_return(int low, int upp);

struct player_info* player_set(char* pom);

int step1_krzak(struct serwer_info *serwer);
int step2_krzak(struct serwer_info *serwer);

int step1(struct serwer_info *serwer);
int step2(struct serwer_info *serwer);
void bestia_move_random(struct serwer_info *serwer);

int wizja1(struct user_info *user);
int wizja2(struct user_info *user);
int druk_wizja(struct user_info *user);
void oboz_start(struct serwer_info *serwer);
void* bestia_move(struct serwer_info *serwer, char direction);
void* collect_skarb(struct serwer_info *serwer);
void oboz_random(struct serwer_info *serwer);
void oboz_coins(struct serwer_info *serwer_s);
void player_position_random(struct serwer_info *serwer);
void bestia_kolizja(struct serwer_info *serwer);
void player_kolizja(struct serwer_info *serwer);

void skarbunio(void *pom);

#endif //SERWER_FUNCTION_H
