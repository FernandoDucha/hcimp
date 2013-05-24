/*
 * Cronometro.cpp
 *
 *  Created on: 30/07/2009
 *      Author: fordem
 */

#include "Cronometro.h"
string Cronometro::ResolutionNames[4]={"nanosegundos","microsegundos","milisegundos","segundos"};
string Cronometro::ResolutionSigs[4]={"ns","\u03BCs","ms","s"};
Cronometro Cronometro::cr;
Cronometro::Cronometro() {
	// TODO Auto-generated constructor stub
	set_resolution(NANO_S);
	actual_res=NANO_S;
}
Cronometro::Cronometro(time_res_t Wich){
    set_resolution(Wich);
    actual_res=Wich;
}
void Cronometro::start()
{
	stoped=false;
	clock_gettime(CLOCK_REALTIME,&t_start);
//	t_start=clock();
	//	clock_gettime(CLOCK_REALTIME,&start);
}

void Cronometro::end()
{
	stoped=true;
	clock_gettime(CLOCK_REALTIME,&t_end);
}


void Cronometro::set_resolution(time_res_t Wich)
{
	actual_res=Wich;
	res_factor=pow(1000,Wich);
}

const char *Cronometro::getResName()
{
	return ResolutionNames[actual_res].c_str();
}


const char *Cronometro::getSig()  const
{
	return ResolutionSigs[actual_res].c_str();
}

Cronometro::~Cronometro() {
	// TODO Auto-generated destructor stub
}

double Cronometro::elapsedIntern(){
    return cr.elapsed();
}
void Cronometro::startIntern(){
    cr.start();
}

