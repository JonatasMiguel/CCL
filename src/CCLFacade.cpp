/*
 * CCLFacade.cpp *
 *  Created on: 29/05/2013
 *      Author: lucas
 */
#include <cstdio>
#include<stdio.h>
#include<iostream>
#include"CCL.h"
CCL::CCL() {
	available_threads = 64;
	ccl_thread = new pthread_t[available_threads];
	current_thread = 0;
	user_function = new void*[64];
	function_counter = 0;
	function_arguments = new void*[64];
}

template <class F>
void * call (void * c){
	printf("NORMAL_CALL");
	Carrier * carrier = (Carrier*)c;
	CCL * context = (CCL*) carrier->context;
	std::cout << "Function_pos: " << carrier->function_pos << std::endl;
	F* call_routine = (F*) context->user_function[carrier->function_pos];
	call_routine(context->function_arguments[carrier->function_pos]);
	std::cout << "Call complete" << std::endl;
	return NULL;
}

template <typename F>
void * call_void (void * c){
	std::cout << "Call_void__ " << std::endl;
	Carrier * carrier = (Carrier*) c;
	CCL * context = (CCL*) carrier->context;
	F * call_routine = (F*) context->user_function[carrier->function_pos];
	std::cout << "Call_routine: " << context->user_function[carrier->function_pos] << std::endl;
	call_routine();
	std::cout << "Call complete" << std::endl;
	return NULL;
}

template <class F>
void CCL::execute(F &function){
	Carrier * carrier = new Carrier;
	carrier->context = this;
	carrier->function_pos = this->function_counter;
	user_function[function_counter++] = (void*) &function;
	pthread_create(&ccl_thread[current_thread++],NULL,(call_void<F>),(void*) carrier);
}

template <class F,class A >
void CCL::execute(F &function, A &arg){
	Carrier * carrier = new Carrier;
	carrier->context = this;
	carrier->function_pos = this->function_counter;
	user_function[function_counter] = (void*) &function;
	function_arguments[function_counter++] = (void*) &arg;
	pthread_create(&ccl_thread[current_thread++],NULL,(call<F>),(void*) carrier);
}
void CCL::Register(){

}
void CCL::global_join(){
	pthread_exit(NULL);
	std::cout << "Exiting joins" << std::endl;
}
CCL::~CCL() {
	// TODO !CodeTemplates.destructorstub.tododesc!
}

