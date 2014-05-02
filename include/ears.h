//ears.h
#ifndef _EARS_H_
#define _EARS_H_

#include <pocketsphinx.h>
#include <cstdlib>
#include <string>
#include <cstring>

#define WNF "wnf" //word not found flag

class Ears
{
	public:
		Ears();
		~Ears();
		
		int init(); 
		int setLMdir(std::string _lmDir);
		int setDICdir(std::string _dicDir);
		std::string rawToString(const char * pathToraw);
	
	
	private:
		
		int updateModel();
		
		
		
		std::string lmDir, dicDir;
		
		ps_decoder_t *ps;
		cmd_ln_t *config;
		FILE *fh;
		char const *hyp, *uttid;
		int16 buf[512];
		int rv;
		int32 score;	
		
};

#endif
