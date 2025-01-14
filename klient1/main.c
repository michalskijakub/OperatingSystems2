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

// gcc main.c function.c -lncurses -pthread -lrt

int SERWER = 0;

int main() {

    // initscr();  // od terminala
    // noecho();   // brak echa
    // //nonl();
    // cbreak();   // cos do initscr
    (void) initscr();      /* initialize the curses library */
//    keypad(stdscr, TRUE);  /* enable keyboard mapping */
    (void) nonl();         /* tell curses not to do NL->CR/NL on output */
    (void) cbreak();       /* take input chars one at a time, no wait for \n */
    (void) noecho();       /* don't echo input */
    keypad(stdscr, TRUE); // make keys work
    start_color();

    sem_t *sem = sem_open("start_serwer",O_CREAT,0777,0);
    sem_t *sem2 = sem_open("start_serwer2",O_CREAT,0777,0);

    int fd = shm_open("shm_pid",O_CREAT | O_RDWR,0777);
    if(fd == -1)
    {
        printf("Shm open filed!!!");
        return 1;
    }

    struct pid_info *pidinfo = mmap(NULL,sizeof(struct pid_info),PROT_READ | PROT_WRITE,MAP_SHARED, fd, 0);
    ftruncate(fd,sizeof(struct pid_info));
    if(pidinfo == MAP_FAILED)
    {
        printf("mmap failed");
        return 1;
    }

    pidinfo->pid2 = getpid();
    sem_post(sem2);
    sem_wait(sem);

    if(pidinfo->pid1 < pidinfo->pid2)
    {
        SERWER = 1;
    }
    sem_post(sem2);
    sem_wait(sem);
    //sem_unlink("start_serwer");
    //sem_unlink("start_serwer2");
    munmap(pidinfo,sizeof(struct pid_info));
    shm_unlink("shm_pid");

    struct create_player player_create;
    if(SERWER == 1)
    {
        char n1[] = "shm_p1";
        char n2[] = "shm_p1_pom";
        player_create.name1 = n1;
        player_create.name2 = n2;


        int fd2 = shm_open("shm_p1",O_CREAT | O_RDWR, 0777);

        struct player_info *playerinfo = mmap(NULL,sizeof(struct player_info),PROT_READ | PROT_WRITE,MAP_SHARED, fd2,0);
        ftruncate(fd2,sizeof(struct player_info));
        playerinfo->PID = getpid();
        playerinfo->numer = 1;
        memcpy(playerinfo->typ,"HUMAN",5);

        pthread_t serw, gracz1, gracz2, bestiunia, quit;

        pthread_create(&quit,NULL,quit_quit,"shm_p1");
        pthread_create(&gracz1,NULL,gracz_fun,&player_create.name1);
        pthread_create(&serw,NULL,serwer_serwer,&player_create);
        pthread_join(quit, NULL);
        pthread_join(gracz1, NULL);
        pthread_join(serw, NULL);
        shm_unlink("shm_p1");
        shm_unlink("shm_p2");
    }
    else
    {
        char n1[] = "shm_p2";
        char n2[] = "shm_p2_pom";
        player_create.name1 = n1;
        player_create.name2 = n2;


        int fd2 = shm_open("shm_p2",O_CREAT | O_RDWR, 0777);

        struct player_info *playerinfo2 = mmap(NULL,sizeof(struct player_info),PROT_READ | PROT_WRITE,MAP_SHARED, fd2,0);
        ftruncate(fd2,sizeof(struct player_info));
        playerinfo2->PID = getpid();
        playerinfo2->numer = 2;
        memcpy(playerinfo2->typ,"HUMAN",5);


        pthread_t  gracz1, gracz2, quit;

        pthread_create(&quit, NULL,quit_quit ,"shm_p2");
        pthread_create(&gracz1, NULL, gracz_fun, &player_create);
        pthread_join(quit, NULL);
        pthread_join(gracz1, NULL);

    }
    clear();    //czyszcenie okna
    refresh();  // odswiezenie okna
    endwin();   // przywrocenie terminalu
    return 0;
}
