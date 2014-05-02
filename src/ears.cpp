//ears.cpp

#include "ears.h"
//create a handler that will loop and listen for commands
//passing the recognized words to the logic node for processing

Ears::Ears()
{
	//this is a very basic langauge model that comes with pocketsphinx
	//use the setLMdir and setDICdir to set your own language models
    std::string temp = MODELDIR;
    lmDir = temp  +"/lm/en/turtle.DMP";
	dicDir = temp +"/lm/en/turtle.dic";	
}

Ears::~Ears()
{
	fclose(fh);
    ps_free(ps);
}

//this will give us access to pocket sphinx's cmd_ln.c interpreter
int Ears::init()
{
	//create a config object
	config = cmd_ln_init(NULL, ps_args(), TRUE,
			     "-hmm", MODELDIR "/hmm/en_US/hub4wsj_sc_8k",
			     "-lm", lmDir.c_str(),
			     "-dict", dicDir.c_str(),
			     NULL);
	if (config == NULL)
		return 1;
		
	//initialize the decoder	
	ps = ps_init(config);
	if (ps == NULL)
		return 1;
	
	return 0;
}

//the ability to set the location for the models will allow new models to be composed and replaced with ease
int Ears::setLMdir(std::string _lmDir)
{
    std::string temp = MODELDIR;
	
	lmDir = temp+ _lmDir;
	if(lmDir.c_str()==NULL)
		return -1;
		
	updateModel();//update the LM if config already exists
	return 1;
}

int Ears::setDICdir(std::string _dicDir)
{
	std::string temp = MODELDIR;
	
	dicDir = temp+ _dicDir;
	if(dicDir.c_str() ==NULL)
		return -1;
	
	updateModel(); //update Dictionary if config object already exists 
	return 1;
}


int Ears::updateModel()
{
	//if init has not been called we don't need to restart pocketSphinx
	if(config == NULL)
		return 1;
	
	ps_free(ps); //free the decoder
	
	init(); //call init to load the decoder with the new language model.
	
}



//enter the location of the file to be interpreted. 
//returns the string that was recognized by the decoder
std::string Ears::rawToString(const char * pathToraw)
{
	std::string er = "error";
	//open the file stream for reading in binary mode
	fh = fopen(pathToraw, "rb");
	if (fh == NULL) {
		perror("Failed to open raw file");
		return er;
	}
	
	//decode the binary audio files and return the number of samples recovered
	rv = ps_decode_raw(ps, fh, "myUttId", -1);//decoder,file handler, utterance ID, -1 = read to end of file
	if (rv < 0)
		return er;
		
	//get the hypothesis on the output 	
	hyp = ps_get_hyp(ps, &score, &uttid);
	
	if (hyp == NULL)//if none of our known words match what was said send a flag for the handler to pick up
		{
			return WNF;
		}
	
	return hyp;	
}




//use this for real time decoding via a microphone. Hardware settings are handled in the hardware node 
//and assigned through the logic node

