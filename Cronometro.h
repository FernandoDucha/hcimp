/*
 * Cronometro.h
 *
 *  Created on: 30/07/2009
 *      Author: fordem
 */

#ifndef CRONOMETRO_H_
#define CRONOMETRO_H_
#include <unistd.h>
#include <time.h>
#include <iostream>
#include <string>
#include <math.h>
using namespace std;
class Cronometro {
	typedef short time_res_t;
	timespec t_start, t_end;
	double res_factor;
	bool stoped;
	time_res_t actual_res;
	static string ResolutionNames[4];//{"nanosegundos","microsegundos","milisegundos","segundos"};
	static string ResolutionSigs[4];
public:
        static Cronometro cr;
	static const time_res_t NANO_S=0;
	static const time_res_t MICRO_S=1;
	static const time_res_t MILI_S=2;
	static const time_res_t SEGUNDOS=3;
    time_res_t getActual_res() const
    {
        return actual_res;
    }
    bool getStoped() const
    {
        return stoped;
    }

    void setStoped(bool stoped)
    {
        this->stoped = stoped;
    }

    const char * getSig() const;
	void start();
	void end();
	double elapsed()const;
	void set_resolution(time_res_t Wich);
	double time()const;
	const char * getResName();
	Cronometro();
        Cronometro(time_res_t Wich);
        static void startIntern();
        static double elapsedIntern();
	virtual ~Cronometro();

};
inline double Cronometro::elapsed() const
{
	long long tempo_start=t_start.tv_sec*pow(1000.,3.)+t_start.tv_nsec;
	timespec t_end_temp;
	clock_gettime(CLOCK_REALTIME,&t_end_temp);
	long long tempo_end= t_end_temp.tv_sec*pow(1000.,3.)+t_end_temp.tv_nsec;
	return (tempo_end-tempo_start)/res_factor;
}
inline double Cronometro::time() const
{
	long long tempo_start=t_start.tv_sec*pow(1000.,3.)+t_start.tv_nsec;
	long long tempo_end= t_end.tv_sec*pow(1000.,3.)+t_end.tv_nsec;
	return (tempo_end-tempo_start)/res_factor;
}
inline ostream & operator <<(ostream & os, const Cronometro & s)
{
	if(s.getStoped()){
		os<<"finalizado "<<s.time()<<" "<<s.getSig()<<".";
	}else{
		os<<"passados "<<s.elapsed()<<" "<<s.getSig()<<".";
	}
	return os;
}

#endif /* CRONOMETRO_H_ */
