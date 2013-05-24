/* 
 * File:   Semaphore.h
 * Author: fernando
 *
 * Created on 9 de Dezembro de 2011, 10:01
 */

#ifndef SEMAPHORE_H
#define	SEMAPHORE_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
class Semaphore
{
private:
    key_t key;
    int nSems;
    struct sembuf sb;
    int semid;

    int initSem();

public:
    Semaphore(int);

    void getLock();

    void ReleaseLock();
};
#endif	/* SEMAPHORE_H */

