/*
 * user.cpp
 *
 *  Created on: 29/05/2013
 *      Author: lucas
 */
#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include "CCL.h"


void * user_foo(void * arg){
	int * n = (int*) arg;
	while(1){
		std::cout << "Call done. N value = " << *n << std::endl;
		sleep(2);
	}
	return NULL;
}
int user_foo_void (){
	while(1){
		std::cout << "Void function call." << std::endl;
		sleep(2);
	}
	return 1;
}
int main(){

 	CCL ccl;
	int n =10;
	ccl.execute(user_foo, n);
	ccl.execute(user_foo_void);
	int o = 20;
	ccl.execute(user_foo, o);
	ccl.global_join();
	return 0;
}
