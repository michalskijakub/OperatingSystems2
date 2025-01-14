#include <stdio.h>

#include "function.h"

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

pthread_mutex_t mutex;
char END;
char BESTIA_ON = 0;

// char* plansza()
// {
//     FILE *fp;
//     fp = fopen("./plansza.txt", "r");
//     if(!fp)
//     {
//         return NULL;
//     }
//     char *tab = (char*)malloc(sizeof(char) * 44 * 33);
//     int licznik = 0;
//     while(1)
//     {
//         *(tab + licznik) = getc(fp);
//         if(*(tab + licznik) == EOF)
//         {
//             break;
//         }
//         licznik++;
//     }
//     char tablica[21][31];
//     for(int i=0;i<21;i++)
//     {
//         for(int j=0;j<31;j++)
//         {
//             tablica[i][j] = getc(fp);
//             licznik++;
//         }
//         licznik++;
//     }
//     printf("%d",licznik);
//     return tab;
// }
/////////////////////////////////////////////////////////////////////////////////////////////////
char** pobierz_plansze()    // correct
{
    FILE *fp;
    fp = fopen("./plansza.txt", "r");
    if(!fp)
    {
        return NULL;
    }
    char** tab = (char**)malloc(sizeof(char*) * 25);
    for(int i=0;i<21;i++)
    {
        tab[i] = (char*)malloc(sizeof(char) * 35);
    }
    for(int i=0;i<21;i++)
    {
        for(int j=0;j<31;j++)
        {
            tab[i][j] = getc(fp);
        }
        getc(fp);
    }
    tab[20][30] = 'M';
    fclose(fp);
    return tab;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void drukuj_plansze(char** tab) // correct
{
    start_color();

    init_pair(1,COLOR_WHITE, COLOR_WHITE);
    init_pair(3, COLOR_BLACK, COLOR_YELLOW);
    init_pair(11,COLOR_WHITE, COLOR_GREEN);

    for(int i=0;i<21;i++)
    {
        for(int j=0;j<31;j++)
        {
            move(i,j);
            if(tab[i][j] == 'M')
            {
                attron(COLOR_PAIR(1));
                printw(" ");
                attroff(COLOR_PAIR(1));
            }
            else if(tab[i][j] == 'c' || tab[i][j] == 't' || tab[i][j] == 'T' || tab[i][j] == 'D')
            {
                attron(COLOR_PAIR(3));
                printw("%c", tab[i][j]);
                attroff(COLOR_PAIR(3));
            }
            else if(tab[i][j] == 'A')
            {
                attron(COLOR_PAIR(3));
                printw("%c", tab[i][j]);
                attroff(COLOR_PAIR(3));
            }
            else if(tab[i][j] == '.')
            {
                printw(".");
            }
            else
            {
                printw("%c", tab[i][j]);
            }
        }
    }
    return ;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void druk_info_plansza_s(struct serwer_info *serwer) // correct
{
    start_color();
    init_pair(3, COLOR_BLACK, COLOR_YELLOW);
    init_pair(5, COLOR_WHITE, COLOR_WHITE);
    init_pair(6, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(11, COLOR_WHITE, COLOR_GREEN);
    init_pair(12, COLOR_WHITE, COLOR_RED);

    move(2,35);
    printw("Server's PID: %d", getpid());

    move(3,35);
    printw("Campsite X/Y: %d/%d", serwer->x_camp, serwer->y_camp);

    move(4,35);
    printw("Round number: %d", serwer->runda);

    move(5,35);
    printw("Parameter:   Player1  Player2  Player3  Player4");

    move(6,35);
    printw("PID         %d     %d", serwer->player1->PID, serwer->player2->PID);
    ///
    move(7,35);
    printw("Type        %d      %d", serwer->player1->typ, serwer->player2->typ);

    move(8,35);
    printw("Curr X/Y    %d/%d    %d/%d", serwer->player1->x_current, serwer->player1->y_current, serwer->player2->x_current, serwer->player2->y_current);

    move(9,35);
    printw("Deaths      %d        %d", serwer->player1->deaths, serwer->player1->deaths);

    move(11,35);
    printw("Coins");

    move(12,35);
    printw("    carried %d       %d", serwer->player1->coins_carried, serwer->player2->coins_carried);

    move(13,35);
    printw("    brought %d       %d", serwer->player1->coins_brought, serwer->player2->coins_brought);

    move(14,35);
    printw("LEGEND: ");

    move(15,35);
    attron(COLOR_PAIR(6));
    printw("1234");
    attroff(COLOR_PAIR(6));
    printw(" - players");

    move(16,35);
    attron(COLOR_PAIR(5));
    printw(" ");
    attroff(COLOR_PAIR(5));
    printw(" - wall");

    move(17,35);
    printw("# - bushes (slow down)");

    move(18,35);
    attron(COLOR_PAIR(12));
    printw("* - enemy");
    attroff(COLOR_PAIR(12));
    

    move(19,35);
    attron(COLOR_PAIR(3));
    printw("c");
    attroff(COLOR_PAIR(3));
    printw(" - one coin");
    attron(COLOR_PAIR(3));
    printw("D");
    attroff(COLOR_PAIR(3));
    printw(" - dropped treasures");

    move(20,35);
    attron(COLOR_PAIR(3));
    printw("C");
    attroff(COLOR_PAIR(3));
    printw(" - treasure (10 coins)");

    move(21,35);
    attron(COLOR_PAIR(3));
    printw("T");
    attroff(COLOR_PAIR(3));
    printw(" - large treasure (50 coins)");

    move(22,35);
    attron(COLOR_PAIR(11));
    printw("A");
    attroff(COLOR_PAIR(11));
    printw(" - campsite");

    //move(23,35);
    //printw("PID - campsite %d %d", kill(serwer->player1->PID, 0), kill(serwer->player2->PID, 0);

    return ;    
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void druk_info_gracz_s(); // ?
/////////////////////////////////////////////////////////////////////////////////////////////////
void* bestia(void* pom) // todo
{
    int x_pom = 0;
    int y_pom = 0;
    int krzak = 0;
    int found = 0;

    struct serwer_info *serwer = (struct serwer_info*)pom;
    bestia_move_random(serwer);
    sem_t *sem_bestia1 = sem_open("shm_bestia1" ,O_CREAT, 0777, 0);
    sem_t *sem_bestia2 = sem_open("shm_bestia2" ,O_CREAT, 0777, 0);

    while(1)
    {
        sem_wait(sem_bestia1); //
        x_pom = serwer->bestia.x;
        y_pom = serwer->bestia.y;

        if(found > 0)
        {
            found--;
        }

        if(serwer->bestia.x == serwer->player1->x_current && serwer->bestia.y == serwer->player1->y_current || serwer->bestia.x == serwer->player2->x_current && serwer->bestia.y == serwer->player2->y_current)
        {
            found = 1;
            krzak = 0;
        }

        // if(found > 0)
        // {
        //     found--;
        // }

        if(found == 0)
        {
            switch(krzak)
            {
                case 1:
                    bestia_move(serwer, 'd');
                    break;
                case 2:
                    bestia_move(serwer, 'a');
                    break;
                case 3:
                    bestia_move(serwer, 'w');
                    break;
                case 4:
                    bestia_move(serwer, 's');
                    break;
            }
            if(krzak != 0)
            {
                found = 1;
            }
            krzak = 0;
        }

        
    }
    return NULL;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void* quit_quit(void* pom) // correct
{
    char* q = (char*)pom;
    int fd = shm_open(q, O_CREAT | O_RDWR, 0777);
    struct player_info *playerinfo = mmap(NULL, sizeof(struct player_info),PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    //ftruncate(fd, sizeof(struct player_info));
    while(1)
    {
        END = getch();
        playerinfo->request = END;

        if(END == 'q')
        {
            return NULL;
        }
        if(END == 'b' || END == 'B')
        {
            BESTIA_ON = 1;
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void* serwer_serwer(void* pom) // correct
{
    int bestia_licznik = 0;
    int b1 = 0;
    int b2 = 0;
    int x_pom = 0;
    int y_pom = 0;
    int licznik = 0;

    pthread_t bestia1;
    pthread_t gracz1, gracz2;

    sem_t *sem_p1 = sem_open("shm_p1", O_CREAT, 0777, 0);
    sem_t *sem_p1_pom = sem_open("shm_p1_pom", O_CREAT, 0777, 0);

    sem_t *sem_p2 = sem_open("shm_p2", O_CREAT, 0777, 0);
    sem_t *sem_p2_pom = sem_open("shm_p2_pom", O_CREAT, 0777, 0);

    sem_t *sem_bestia1 = sem_open("shm_bestia1", O_CREAT, 0777, 0);
    sem_t *sem_bestia2 = sem_open("shm_bestia2", O_CREAT, 0777, 0);

    //start_color();
    init_pair(2, COLOR_WHITE, COLOR_MAGENTA);

    struct serwer_info serwerinfo;

    char *q = (char*)pom;

    if(memcmp(q, "shm_p2",6) == 0)
    {
        serwerinfo.pom = 1;
    }
    else
    {
        serwerinfo.pom = 2;
    }

    serwerinfo.PID = getpid();
    serwerinfo.runda = 0;

    serwerinfo.skarb.count_one_coin = 0;
    serwerinfo.skarb.count_treasure_coin = 0;
    serwerinfo.skarb.count_large_treasure_coin = 0;

    serwerinfo.mapa = pobierz_plansze();

    oboz_random(&serwerinfo);

    drukuj_plansze(serwerinfo.mapa);

    serwerinfo.player1 = player_set("shm_p1");
    serwerinfo.player2 = player_set("shm_p2");

    serwerinfo.player1->PID_serwer = getpid();
    serwerinfo.player2->PID_serwer = getpid();

    player_position_random(&serwerinfo);

    struct user_info userinfo;


    userinfo.serwer = &serwerinfo;

    while(1)
    {
        serwerinfo.player1->runda = serwerinfo.runda;
        serwerinfo.player2->runda = serwerinfo.runda;

        // if(BESTIA_ON && bestia_licznik == 0)
        // {
        //     serwerinfo.bestia->alive = 1;
        //     pthread_create(&bestia1, NULL, bestia, &serwerinfo);
        //     bestia_licznik = 1;
        // }

        userinfo.user = 1;

        drukuj_plansze(serwerinfo.mapa);

        //refresh();

        for(int i=0; i<serwerinfo.skarb.count_drop_coin; i++)
        {
            if(serwerinfo.skarb.value_all_dropped_coin[i] != -1)
            {
                move(serwerinfo.skarb.dropped_coin[i][0], serwerinfo.skarb.dropped_coin[i][1]);
                printw("D");
            }
        }

        // if(BESTIA_ON)
        // {
        //     move(serwerinfo.bestia->y, serwerinfo.bestia->x);
        //     printw("*");
        //     bestia_kolizja(&serwerinfo);
        // }

        skarbunio(&serwerinfo);

        move(serwerinfo.player1->y_current, serwerinfo.player1->x_current);

        attron(COLOR_PAIR(2));
        printw("1");
        attroff(COLOR_PAIR(2));

        wizja1(&userinfo);
        wizja2(&userinfo);
        if(!b1)
        {
            // move(serwerinfo.player1->y_current, serwerinfo.player1->x_current);
            // attron(COLOR_PAIR(2));
            // printw("1");
            // attroff(COLOR_PAIR(2));

            x_pom = serwerinfo.player1->x_current;
            y_pom = serwerinfo.player1->y_current;
            // wizja1(&userinfo);
            // b1 = step1(&serwerinfo);
            if(!b1)
            {
                step1_krzak(&serwerinfo);
                b1 = step1(&serwerinfo);
                move(y_pom, x_pom);
                if(serwerinfo.mapa[y_pom][x_pom] == 'M')
                {
                    printw(".");
                }
                else if(serwerinfo.mapa[y_pom][x_pom] == 'A')
                {
                    attron(COLOR_PAIR(11));
                    printw("A");
                    attroff(COLOR_PAIR(11));
                }
                else
                {
                    printw("%c", serwerinfo.mapa[y_pom][x_pom]);
                }

                move(serwerinfo.player1->y_current, serwerinfo.player1->x_current);
                attron(COLOR_PAIR(2));
                printw("1");
                attroff(COLOR_PAIR(2));

                wizja1(&userinfo);
                wizja2(&userinfo);
            }
        }
        if(b1 > 0)
        {
            b1--;
        }

        if(kill(serwerinfo.player2->PID, 0) == 0)
        {
            move(serwerinfo.player2->y_current, serwerinfo.player2->x_current);
            attron(COLOR_PAIR(2));
            printw("2");
            attroff(COLOR_PAIR(2));
        }

        move(serwerinfo.player2->y_current, serwerinfo.player2->x_current);

        wizja1(&userinfo);
        wizja2(&userinfo);

        if(!b2 && serwerinfo.player2->y_current !=0)
        {
            x_pom = serwerinfo.player2->x_current;
            y_pom = serwerinfo.player2->y_current;

            wizja1(&userinfo);
            wizja2(&userinfo);

            if(!b2)
            {
                step2_krzak(&serwerinfo);
                b2 = step2(&serwerinfo);
                move(y_pom, x_pom);
                if(serwerinfo.mapa[y_pom][x_pom] == 'M')
                {
                    printw(".");
                }
                else if(serwerinfo.mapa[y_pom][x_pom] == 'A')
                {
                    attron(COLOR_PAIR(11));
                    printw("A");
                    attroff(COLOR_PAIR(11));
                }
                else
                {
                    printw("%c", serwerinfo.mapa[y_pom][x_pom]);
                }

                move(serwerinfo.player2->y_current, serwerinfo.player2->x_current);
                attron(COLOR_PAIR(2));
                printw("2");
                attroff(COLOR_PAIR(2));

                wizja1(&userinfo);
                wizja2(&userinfo);
            }
        }
        if(b2 > 0)
        {
            b2--;
        }

        if(bestia_licznik == 0 && BESTIA_ON)
        {
            serwerinfo.bestia.alive = 1;
            pthread_create(&bestia1, NULL, bestia, &serwerinfo);
            bestia_licznik = 1;
        }

        if(BESTIA_ON)
        {
            sem_post(sem_bestia1);
            sem_wait(sem_bestia2);
            move(serwerinfo.bestia.y, serwerinfo.bestia.x);
            attron(COLOR_PAIR(12));
            printw("*");
            attroff(COLOR_PAIR(12));
            bestia_kolizja(&serwerinfo);
        }

        wizja1(&userinfo);
        wizja2(&userinfo);

        player_kolizja(&serwerinfo);

        collect_skarb(&serwerinfo);

        if(kill(serwerinfo.player1->PID, 0) == 0 )
        {
            sem_post(sem_p1);
            sem_wait(sem_p1_pom);
        }

        if(kill(serwerinfo.player2->PID, 0) == 0 )
        {
            sem_post(sem_p2);
            sem_wait(sem_p2_pom);
        }
        else
        {
            serwerinfo.player2->y_current = 0;
            serwerinfo.player2->x_current = 0;
        }

        oboz_coins(&serwerinfo);

        druk_info_plansza_s(&serwerinfo);

        refresh();

        if(END == 'q')
        {
            sem_post(sem_bestia1);

            if(BESTIA_ON)
            {
                pthread_join(bestia1, NULL);
            }
            
            munmap(serwerinfo.player1, sizeof(struct player_info));
            munmap(serwerinfo.player2, sizeof(struct player_info));
            shm_unlink("shm_p1");
            shm_unlink("shm_p1_pom");
            shm_unlink("shm_p2");
            shm_unlink("shm_p2_pom");
            shm_unlink("shm_bestia1");
            shm_unlink("shm_bestia2");
            //...11
            return NULL;
        }

        //sleep(1);
        clear();
        usleep(1000000);

        serwerinfo.runda++;
    }
    return NULL;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void* gracz_fun(void* pom) //correct
{
    struct create_player *createplayer = (struct create_player*)pom;
    int fd = shm_open(createplayer->name1, O_CREAT | O_RDWR, 0777);

    struct player_info *playerinfo = mmap(NULL, sizeof(struct player_info),PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    //ftruncate(fd, sizeof(struct player_info));

    playerinfo->request = END;

    sem_t *sem_p1 = sem_open(createplayer->name1, O_CREAT, 0777, 0);
    sem_t *sem_p1_pom = sem_open(createplayer->name2, O_CREAT, 0777, 0);

    start_color();
    init_pair(3, COLOR_BLACK, COLOR_YELLOW);
    init_pair(5, COLOR_WHITE, COLOR_WHITE);
    init_pair(6, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(11, COLOR_WHITE, COLOR_GREEN);
    init_pair(12, COLOR_WHITE, COLOR_RED);

    while(1)
    {
        //refresh();
        sem_wait(sem_p1);

        for(int i=0;i<5;i++)
        {
            for(int j=0;j<5;j++)
            {
                move(i + 25, j + 5);
                if(playerinfo->area[i][j] == 'M')
                {
                    attron(COLOR_PAIR(5));
                    printw(" ");
                    attroff(COLOR_PAIR(5));
                }
                else if(playerinfo->area[i][j] == '1' || playerinfo->area[i][j] == '2' || playerinfo->area[i][j] == '3' || playerinfo->area[i][j] == '4')
                {
                    attron(COLOR_PAIR(6));
                    printw("%c",playerinfo->area[i][j]);
                    attroff(COLOR_PAIR(6));
                }
                else if(playerinfo->area[i][j] == 'c' || playerinfo->area[i][j] == 't' || playerinfo->area[i][j] == 'T' || playerinfo->area[i][j] == 'D')
                {
                    attron(COLOR_PAIR(3));
                    printw("%c",playerinfo->area[i][j]);
                    attroff(COLOR_PAIR(3));
                }
                else if(playerinfo->area[i][j] == '*')
                {
                    attron(COLOR_PAIR(12));
                    printw("*");
                    attroff(COLOR_PAIR(12));
                }
                else if(playerinfo->area[i][j] == 'A')
                {
                    attron(COLOR_PAIR(11));
                    printw("A");
                    attroff(COLOR_PAIR(11));
                }
                else
                {
                    printw("%c",playerinfo->area[i][j]);
                }
            }
        }

        move(25,13);
        printw("Server's PID: %d", playerinfo->PID_serwer);

        move(26,13);
        printw("Campsite X/Y: unknown");

        move(27,13);
        printw("Campsite X/Y: ");

        move(28,13);
        printw("Round number: %d", playerinfo->runda);

        move(30,13);
        printw("Player: ");

        move(31,13);
        printw("Number: %d", playerinfo->numer);

        move(32,13);
        printw("Type : HUMAN");

        move(33,13);
        printw("Curr X/Y %d/%d ", playerinfo->x_current, playerinfo->y_current);

        move(34,13);
        printw("Deaths :    %d", playerinfo->deaths);

        move(36,13);
        printw("Coins found : %d", playerinfo->coins_carried);

        move(37,13);
        printw("Coins brought : %d", playerinfo->coins_brought);

        move(40,13);
        printw("LEGEND: ");

        move(41,13);
        attron(COLOR_PAIR(6));
        printw("1234");
        attroff(COLOR_PAIR(6));
        printw(" - players");

        move(42,13);
        attron(COLOR_PAIR(5));
        printw(" ");
        attroff(COLOR_PAIR(5));
        printw(" - wall");

        move(43,13);
        printw("# - bushes (slow down)");

        move(44,13);
        attron(COLOR_PAIR(12));
        printw("* - enemy");
        attroff(COLOR_PAIR(12));

        move(45,13);
        attron(COLOR_PAIR(3));
        printw("c");
        attroff(COLOR_PAIR(3));
        printw(" - one coin        ");
        attron(COLOR_PAIR(3));
        printw("D");
        attroff(COLOR_PAIR(3));
        printw(" - dropped treasures");

        move(46,13);
        attron(COLOR_PAIR(3));
        printw("C");
        attroff(COLOR_PAIR(3));
        printw(" - treasure (10 coins)");

        move(47,13);
        attron(COLOR_PAIR(3));
        printw("T");
        attroff(COLOR_PAIR(3));
        printw(" - large treasure (50 coins)");

        move(48,13);
        attron(COLOR_PAIR(11));
        printw("A");
        attroff(COLOR_PAIR(11));
        printw(" - campsite");
        refresh();
        sem_post(sem_p1_pom);
        if(END == 'q')
        {
            shm_unlink(createplayer->name1);
            return NULL;
        }
    }
    return NULL;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
int random_return(int low, int upp) // correct
{
    return (rand() % (upp - low + 1)) + low;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
struct player_info* player_set(char* pom) // correct
{
    int fd = shm_open(pom, O_CREAT | O_RDWR, 0777);
    if(fd == -1)
    {
        return NULL;
    }
    struct player_info *playerinfo = mmap(NULL, sizeof(struct player_info), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    //ftruncate(fd, sizeof(struct player_info));
    if(playerinfo == MAP_FAILED)
    {
        return NULL;
    }
    return playerinfo;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
int step1_krzak(struct serwer_info *serwer) // correct
{
    int krzok = 0;
    if(serwer->mapa[serwer->player1->y_current][serwer->player1->x_current] == '#')
    {
        krzok = 2;
    }

    return krzok;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
int step2_krzak(struct serwer_info *serwer) // correct
{
    int krzok = 0;
    if(serwer->mapa[serwer->player2->y_current][serwer->player2->x_current] == '#')
    {
        krzok = 2;
    }

    return krzok;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
int step1(struct serwer_info *serwer) // correct
{
    switch(serwer->player1->request)
    {
        case 'w':
            if(serwer->mapa[serwer->player1->y_current - 1][serwer->player1->x_current] != 'M')
            {
                serwer->player1->y_current--;
                serwer->player1->request = '0';
                END = '0';
            }
            break;
        case 'a':
            if(serwer->mapa[serwer->player1->y_current][serwer->player1->x_current - 1] != 'M')
            {
                serwer->player1->x_current--;
                serwer->player1->request = '0';
                END = '0';
            }
            break;
        case 's':
            if(serwer->mapa[serwer->player1->y_current + 1][serwer->player1->x_current] != 'M')
            {
                serwer->player1->y_current++;
                serwer->player1->request = '0';
                END = '0';
            }
            break;
        case 'd':
            if(serwer->mapa[serwer->player1->y_current][serwer->player1->x_current + 1] != 'M')
            {
                serwer->player1->x_current++;
                serwer->player1->request = '0';
                END = '0';
            }
            break;
    }
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
int step2(struct serwer_info *serwer) // correct
{
    switch(serwer->player2->request)
    {
        case 'w':
            if(serwer->mapa[serwer->player2->y_current - 1][serwer->player2->x_current] != 'M')
            {
                serwer->player2->y_current--;
                serwer->player2->request = '0';
                END = '0';
            }
            break;
        case 's':
            if(serwer->mapa[serwer->player2->y_current + 1][serwer->player2->x_current] != 'M')
            {
                serwer->player2->y_current++;
                serwer->player2->request = '0';
                END = '0';
            }
            break;
        case 'a':
            if(serwer->mapa[serwer->player2->y_current][serwer->player2->x_current - 1] != 'M')
            {
                serwer->player2->x_current--;
                serwer->player2->request = '0';
                END = '0';
            }
            break;
        case 'd':
            if(serwer->mapa[serwer->player2->y_current][serwer->player2->x_current + 1] != 'M')
            {
                serwer->player2->x_current++;
                serwer->player2->request = '0';
                END = '0';
            }
            break;
    }
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void bestia_move_random(struct serwer_info *serwer) // correct
{
    int low = 0;
    int upp = 0;
    int number = 0;
    srand(time(NULL));

    while(1)
    {
        low = 1;    upp = 29;
        serwer->bestia.x = (rand() % (upp - low + 1)) + low;

        low = 1;    upp = 19;
        serwer->bestia.y = (rand() % (upp - low + 1)) + low;

        if(serwer->mapa[serwer->bestia.y][serwer->bestia.x] == '.' && serwer->bestia.y != serwer->player1->y_current && serwer->bestia.x != serwer->player1->x_current
        && serwer->bestia.y != serwer->player2->y_current && serwer->bestia.x != serwer->player2->x_current)
        {
            break;
        }

    }
    return ;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
int wizja1(struct user_info *user) // correct
{
    int q = 0;
    int w = 0;
    int x_low = 0;
    int x_upp = 0;
    int y_low = 0;
    int y_upp = 0;
    int y = 0;
    int x = 0;

    if(user->serwer->player1->y_current - 2 < 0)
    {
        y_low = 0;
        y_upp = 5;
        y = user->serwer->player1->y_current;
    }
    else if(user->serwer->player1->y_current + 2 >= 20)
    {
        y_low = 16;
        y_upp = 20;
        if(user->serwer->player1->y_current == 18)
        {
            y = 2;
        }
        if(user->serwer->player1->y_current == 19)
        {
            y = 3;
        }
    }
    else
    {
        y_low = user->serwer->player1->y_current - 2;
        y_upp = user->serwer->player1->y_current + 2;
        y = 2;
    }

    if(user->serwer->player1->x_current - 2 < 0)
    {
        x_low = 0;
        x_upp = 5;
        x = user->serwer->player1->x_current;
    }
    else if(user->serwer->player1->x_current + 2 >= 30)
    {
        x_low = 26;
        x_upp = 30;
        if(user->serwer->player1->x_current == 28)
        {
            x = 2;
        }
        if(user->serwer->player1->x_current == 29)
        {
            x = 3;
        }
    }
    else
    {
        x_low = user->serwer->player1->x_current - 2;
        x_upp = user->serwer->player1->x_current + 2;
        x = 2;
    }

    for(int i=y_low;i<=y_upp;i++)
    {
        for(int j=x_low;j<=x_upp;j++)
        {
            user->serwer->player1->area[q][w] = user->serwer->mapa[i][j];
            if(i == user->serwer->bestia.y && j == user->serwer->bestia.x)
            {
                user->serwer->player1->area[q][w] = '*';
            }

            for(int m = 0; m<user->serwer->skarb.count_drop_coin;m++)
            {
                if(user->serwer->skarb.value_all_dropped_coin[m] >= 0 && i == user->serwer->skarb.dropped_coin[m][0] && j == user->serwer->skarb.dropped_coin[m][1])
                {
                    user->serwer->player1->area[q][w] = 'D';
                }
            }

            if(i == user->serwer->player1->y_current && j == user->serwer->player1->x_current)
            {
                user->serwer->player1->area[q][w] = '2';
            }

            w++;
        }
        q++;
        w = 0;
    }

    user->serwer->player1->area[y][x] = '1';

    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
int wizja2(struct user_info *user) // correct
{
    int q = 0;
    int w = 0;
    int x_low = 0;
    int x_upp = 0;
    int y_low = 0;
    int y_upp = 0;
    int y = 0;
    int x = 0;

    if(user->serwer->player2->y_current - 2 < 0)
    {
        y_low = 0;
        y_upp = 5;
        y = user->serwer->player2->y_current;
    }
    else if(user->serwer->player2->y_current + 2 >= 20)
    {
        y_low = 16;
        y_upp = 20;
        if(user->serwer->player2->y_current == 18)
        {
            y = 2;
        }
        if(user->serwer->player2->y_current == 19)
        {
            y = 3;
        }
    }
    else
    {
        y_low = user->serwer->player2->y_current - 2;
        y_upp = user->serwer->player2->y_current + 2;
        y = 2;
    }

    if(user->serwer->player2->x_current - 2 < 0)
    {
        x_low = 0;
        x_upp = 5;
        x = user->serwer->player2->x_current;
    }
    else if(user->serwer->player2->x_current + 2 >= 30)
    {
        x_low = 26;
        x_upp = 30;
        if(user->serwer->player2->x_current == 28)
        {
            x = 2;
        }
        if(user->serwer->player2->x_current == 29)
        {
            x = 3;
        }
    }
    else
    {
        x_low = user->serwer->player2->x_current - 2;
        x_upp = user->serwer->player2->x_current + 2;
        x = 2;
    }

    for(int i=y_low;i<=y_upp;i++)
    {
        for(int j=x_low;j<=x_upp;j++)
        {
            user->serwer->player2->area[q][w] = user->serwer->mapa[i][j];
            if(i == user->serwer->bestia.y && j == user->serwer->bestia.x)
            {
                user->serwer->player2->area[q][w] = '*';
            }

            for(int m = 0; m<user->serwer->skarb.count_drop_coin;m++)
            {
                if(user->serwer->skarb.value_all_dropped_coin[m] >= 0 && i == user->serwer->skarb.dropped_coin[m][0] && j == user->serwer->skarb.dropped_coin[m][1])
                {
                    user->serwer->player2->area[q][w] = 'D';
                }
            }

            if(i == user->serwer->player1->y_current && j == user->serwer->player1->x_current)
            {
                user->serwer->player2->area[q][w] = '1';
            }

            w++;
        }
        q++;
        w = 0;
    }

    user->serwer->player2->area[y][x] = '2';

    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
int druk_wizja(struct user_info *user) // correct
{
    init_pair(1, COLOR_WHITE, COLOR_WHITE);
    init_pair(3, COLOR_BLACK, COLOR_YELLOW);

    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            move(i,j + 100);
            if(user->serwer->player1->area[i][j] == 'M')
            {
                attron(COLOR_PAIR(1));
                printw(" ");
                attroff(COLOR_PAIR(1));
            }
            else if(user->serwer->player1->area[i][j] == '.')
            {
                printw(".");
            }
            else if(user->serwer->player1->area[i][j] == 'c' || user->serwer->player1->area[i][j] == 'D' || user->serwer->player1->area[i][j] == 't' || user->serwer->player1->area[i][j] == 'T')
            {
                attron(COLOR_PAIR(3));
                printw("%c", user->serwer->player1->area[i][j]);
                attroff(COLOR_PAIR(3));
            }
            else
            {
                printw("%c", user->serwer->player1->area[i][j]);
            }
        }
    }
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void oboz_start(struct serwer_info *serwer); // todo
/////////////////////////////////////////////////////////////////////////////////////////////////
void* bestia_move(struct serwer_info *serwer, char direction) // correct
{
    switch(direction)
    {
        case 'w':
            serwer->bestia.y_ostatnie = serwer->bestia.y;
            serwer->bestia.y--;
            break;
        case 'a':
            serwer->bestia.x_ostatnie = serwer->bestia.x;
            serwer->bestia.x--;
            break;
        case 's':
            serwer->bestia.y_ostatnie = serwer->bestia.y;
            serwer->bestia.y++;
            break;
        case 'd':
            serwer->bestia.x_ostatnie = serwer->bestia.x;
            serwer->bestia.x++;
            break;
    }

    return NULL;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void* collect_skarb(struct serwer_info *serwer) // correct
{
    int y = serwer->player1->y_current;
    int x = serwer->player1->x_current;

    for(int i=0; i <serwer->skarb.count_one_coin; i++)
    {
        if(serwer->mapa[y][x] == 'c' && y == serwer->skarb.one_coin[i][0] && x == serwer->skarb.one_coin[i][1])
        {
            serwer->player1->coins_carried++;
            serwer->mapa[y][x] = '.';
            return NULL;
        }
    }

    for(int i=0; i <serwer->skarb.count_treasure_coin; i++)
    {
        if(serwer->mapa[y][x] == 't' && y == serwer->skarb.treasure_coin[i][0] && x == serwer->skarb.treasure_coin[i][1])
        {
            serwer->player1->coins_carried = serwer->player1->coins_carried + 10;
            serwer->mapa[y][x] = '.';
            return NULL;
        }
    }

    for(int i=0; i <serwer->skarb.count_large_treasure_coin; i++)
    {
        if(serwer->mapa[y][x] == 'T' && y == serwer->skarb.large_treasure_coin[i][0] && x == serwer->skarb.large_treasure_coin[i][1])
        {
            serwer->player1->coins_carried = serwer->player1->coins_carried + 50;
            serwer->mapa[y][x] = '.';
            return NULL;
        }
    }

    for(int i=0; i <serwer->skarb.count_drop_coin; i++)
    {
        if(serwer->skarb.value_all_dropped_coin[i] >= 0 && y == serwer->skarb.dropped_coin[i][0] && x == serwer->skarb.dropped_coin[i][1])
        {
            serwer->player1->coins_carried = serwer->player1->coins_carried + serwer->skarb.value_all_dropped_coin[i];
            serwer->skarb.value_all_dropped_coin[i] = -1;
            serwer->mapa[y][x] = '.';
            return NULL;
        }
    }

    y = serwer->player2->y_current;
    x = serwer->player2->x_current;

    for(int i=0; i <serwer->skarb.count_one_coin; i++)
    {
        if(serwer->mapa[y][x] == 'c' && y == serwer->skarb.one_coin[i][0] && x == serwer->skarb.one_coin[i][1])
        {
            serwer->player2->coins_carried++;
            serwer->mapa[y][x] = '.';
            return NULL;
        }
    }

    for(int i=0; i <serwer->skarb.count_treasure_coin; i++)
    {
        if(serwer->mapa[y][x] == 't' && y == serwer->skarb.treasure_coin[i][0] && x == serwer->skarb.treasure_coin[i][1])
        {
            serwer->player2->coins_carried = serwer->player1->coins_carried + 10;
            serwer->mapa[y][x] = '.';
            return NULL;
        }
    }

    for(int i=0; i <serwer->skarb.count_large_treasure_coin; i++)
    {
        if(serwer->mapa[y][x] == 'T' && y == serwer->skarb.large_treasure_coin[i][0] && x == serwer->skarb.large_treasure_coin[i][1])
        {
            serwer->player2->coins_carried = serwer->player2->coins_carried + 50;
            serwer->mapa[y][x] = '.';
            return NULL;
        }
    }

    for(int i=0; i <serwer->skarb.count_drop_coin; i++)
    {
        if(serwer->skarb.value_all_dropped_coin[i] >= 0 && y == serwer->skarb.dropped_coin[i][0] && x == serwer->skarb.dropped_coin[i][1])
        {
            serwer->player2->coins_carried = serwer->player1->coins_carried + serwer->skarb.value_all_dropped_coin[i];
            serwer->skarb.value_all_dropped_coin[i] = -1;
            serwer->mapa[y][x] = '.';
            return NULL;
        }
    }
    return NULL;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void oboz_random(struct serwer_info *serwer) // correct
{
    srand(time(NULL));
    int low = 0;
    int upp = 0;
    int x = 0;
    int y = 0;

    while(1)
    {
        low = 1;    upp = 29;
        x = random_return(low, upp);
        
        
        low = 1;    upp = 19;
        y = random_return(low, upp);

        if(serwer->mapa[y][x] == '.')
        {
            serwer->mapa[y][x] = 'A';
            serwer->x_camp = x;
            serwer->y_camp = y;
            break;
        }
    }
    return ;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void oboz_coins(struct serwer_info *serwer) // correct
{
    if (serwer->x_camp == serwer->player1->x_current && serwer->y_camp == serwer->player1->y_current) {
        serwer->player1->coins_brought = serwer->player1->coins_brought + serwer->player1->coins_carried;
        serwer->player1->coins_carried = 0;
    }

    if (serwer->x_camp == serwer->player2->x_current && serwer->y_camp == serwer->player2->y_current) {
        serwer->player2->coins_brought = serwer->player2->coins_brought + serwer->player2->coins_carried;
        serwer->player2->coins_carried = 0;
    }
    return;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void player_position_random(struct serwer_info *serwer) // correct
{
    srand(time(NULL));
    int low = 0;
    int upp = 0;

    while(1)
    {
        low = 1;     upp = 19;
        serwer->player1->y_start = random_return(low, upp);

        low = 1;     upp = 29;
        serwer->player1->x_start = random_return(low, upp);

        if(serwer->mapa[serwer->player1->y_start][serwer->player1->x_start] == '.')
        {
            serwer->player1->x_current = serwer->player1->x_start;
            serwer->player1->y_current = serwer->player1->y_start;
            break;
        }
    }

    while(1)
    {
        low = 1;     upp = 19;
        serwer->player2->y_start = random_return(low, upp);

        low = 1;     upp = 29;
        serwer->player2->x_start = random_return(low, upp);

        if(serwer->mapa[serwer->player2->y_start][serwer->player2->x_start] == '.')
        {
            serwer->player2->x_current = serwer->player2->x_start;
            serwer->player2->y_current = serwer->player2->y_start;
            break;
        }
    }
    return ;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void bestia_kolizja(struct serwer_info *serwer) // correct
{
    if(serwer->bestia.x == serwer->player1->x_current && serwer->bestia.y == serwer->player1->y_current)
    {
        serwer->player1->deaths++;

        serwer->skarb.dropped_coin[serwer->skarb.count_drop_coin][0] = serwer->player1->y_current;
        serwer->skarb.dropped_coin[serwer->skarb.count_drop_coin][1] = serwer->player1->x_current;

        serwer->skarb.value_all_dropped_coin[serwer->skarb.count_drop_coin] = serwer->player1->coins_carried;

        serwer->player1->coins_carried = 0;

        serwer->player1->x_current = serwer->player1->x_start;
        serwer->player1->y_current = serwer->player1->y_start;

        serwer->skarb.count_drop_coin++;

        serwer->mapa[serwer->bestia.y][serwer->bestia.x] = 'D';
    }

    if(serwer->bestia.x == serwer->player2->x_current && serwer->bestia.y == serwer->player2->y_current)
    {
        serwer->player2->deaths++;

        serwer->skarb.dropped_coin[serwer->skarb.count_drop_coin][0] = serwer->player2->y_current;
        serwer->skarb.dropped_coin[serwer->skarb.count_drop_coin][1] = serwer->player2->x_current;

        serwer->skarb.value_all_dropped_coin[serwer->skarb.count_drop_coin] = serwer->player2->coins_carried;

        serwer->player2->coins_carried = 0;

        serwer->player2->x_current = serwer->player2->x_start;
        serwer->player2->y_current = serwer->player2->y_start;

        serwer->skarb.count_drop_coin++;

        serwer->mapa[serwer->bestia.y][serwer->bestia.x] = 'D';
    }
    return ;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void player_kolizja(struct serwer_info *serwer) // correct
{
    if(serwer->player1->x_current == serwer->player2->x_current && serwer->player1->y_current == serwer->player2->y_current)
    {
        serwer->player1->deaths++;
        serwer->player2->deaths++;
        
        serwer->skarb.dropped_coin[serwer->skarb.count_drop_coin][0] = serwer->player1->y_current;
        serwer->skarb.dropped_coin[serwer->skarb.count_drop_coin][1] = serwer->player1->x_current;
         serwer->skarb.value_all_dropped_coin[serwer->skarb.count_drop_coin] = serwer->player1->coins_carried + serwer->player2->coins_carried;

        serwer->player1->coins_carried = 0;
        serwer->player2->coins_carried = 0;

        serwer->player1->x_current = serwer->player1->x_start;
        serwer->player1->y_current = serwer->player1->y_start;

        serwer->player2->x_current = serwer->player2->x_start;
        serwer->player2->y_current = serwer->player2->y_start;

        serwer->skarb.count_drop_coin++;
    }

    return ;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void skarbunio(void *pom) // correct
{
    struct serwer_info * serwer = (struct serwer_info*)pom;
    srand(time(NULL));
    int x = 0;
    int y = 0;

    if(END == 'c')
    {
        END = '0';
        while(1)
        {
            y = random_return(1, 19);
            x = random_return(1, 29);
            if(serwer->mapa[y][x] == '.')
            {
                serwer->skarb.one_coin[serwer->skarb.count_one_coin][0] = y;
                serwer->skarb.one_coin[serwer->skarb.count_one_coin][1] = x;
                serwer->mapa[y][x] = 'c';
                break;
            }
        }
        serwer->skarb.count_one_coin++;
    }

    if(END == 't')
    {
        END = '0';
        while(1)
        {
            y = random_return(1, 19);
            x = random_return(1, 29);
            if(serwer->mapa[y][x] == '.')
            {
                serwer->skarb.treasure_coin[serwer->skarb.count_treasure_coin][0] = y;
                serwer->skarb.treasure_coin[serwer->skarb.count_treasure_coin][1] = x;
                serwer->mapa[y][x] = 't';
                break;
            }
        }
        serwer->skarb.count_treasure_coin++;
    }

    if(END == 'T')
    {
        END = '0';
        while(1)
        {
            y = random_return(1, 19);
            x = random_return(1, 29);
            if(serwer->mapa[y][x] == '.')
            {
                serwer->skarb.large_treasure_coin[serwer->skarb.count_large_treasure_coin][0] = y;
                serwer->skarb.large_treasure_coin[serwer->skarb.count_large_treasure_coin][1] = x;
                serwer->mapa[y][x] = 'T';
                break;
            }
        }
        serwer->skarb.count_large_treasure_coin++;
    }

    return ;
}