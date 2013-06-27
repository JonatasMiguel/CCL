#ifndef CCL_H_
#define CCL_H_

#include <pthread.h>
#include "CCLFacade.cpp"
/*!
 * \class CCL
 * Principal classe do C++ca&&la.
 * Nela acontece todo o controle das threads a serem executadas.
 * Utilizando a biblioteca <pthread.h> para execução de funções simultaneamente.
 * O controle de semaforos tambem é feito utilizando objetos da biblioteca <pthread.h>
 * Apartir dos metodos desta classe, o usuário poderá criar e executar funções de modo simultaneo e distribuído de forma muito mais simples e facil dp que apartir de metodos tradicionais.
 * O controle das partes criticas das funções do usuario vai ficar a cargo do C++ca&la.
 */
class CCL {
	public:
		CCL();
		template<class F> void execute(F&) ;
		template<class F,class A> void execute(F&,A&) ;
		template<class F> friend void * call (void * context);
		template<class F> friend void * call_void (void * context);
		void Register();
		void global_join();
		virtual ~CCL();
	private:
		pthread_mutex_t mutex;//!<Atributo responsavel pela sinalização de partes criticas na execução de uma função. Quando tal variavel é setada a execução volta a ficar sequencial.
		pthread_cond_t flag;//!<Atributo que quando setada apartir de funções da biblioteca <pthread.h> deixa as threads em estado de espera ate que alguma ação às acorde e termine sua execução
		void ** user_function;//!<Vetor de ponteiros (void), onde cada posição do vetor contem o endereço das funções do usuario.
		void ** function_arguments;//!<Vetor de ponteiros (void), onde cada posição do vetor contem o endereço dos parametros das funções do usuario.
		pthread_t * ccl_thread;//!<Vetor de threads que serão executadas simultaneamente.
		int available_threads;//!<Atributo utilizado para a contagem de thread disponiveis a serem executadas
		unsigned current_thread;//!<Controle da thread que está atualmente  executada.
		unsigned function_counter;//!<Contador de funções para serem executadas.
};
class Carrier{
	public:
		CCL * context;
		int function_pos;
};



#endif /* CCL_H_ */
