//ears.cpp

#include "ears.h"
//create a handler that will loop and listen for commands
//passing the recognized words to the logic node for processing

Ears::Ears()
{
	//this is a very basic langauge model that comes with pocketsphinx
	//use the setLMdir and setDICdir to set your own language models
    std::string temp = MODELDIR;
    _lang_model_dir = temp  +"/lm/en/turtle.DMP";
    _dictionary_dir = temp +"/lm/en/turtle.dic";
}

Ears::~Ears()
{
    fclose(_fh);
    ps_free(_ps);
}

//this will give us access to pocket sphinx's cmd_ln.c interpreter
int Ears::Init()
{
	//create a config object
    _config = cmd_ln_init(NULL, ps_args(), TRUE,
			     "-hmm", MODELDIR "/hmm/en_US/hub4wsj_sc_8k",
                 "-lm", _lang_model_dir.c_str(),
                 "-dict", _dictionary_dir.c_str(),
			     NULL);
    if (_config == NULL)
		return 1;
		
	//initialize the decoder	
    _ps = ps_init(_config);
    if (_ps == NULL)
		return 1;
	
	return 0;
}

//the ability to set the location for the models will allow new models to be composed and replaced with ease
int Ears::SetLanguageModelDir(std::string lang_model_dir)
{
    std::string temp = MODELDIR;
	
    _lang_model_dir = temp + lang_model_dir;
    if(_lang_model_dir.c_str() == NULL)
		return -1;
		
    UpdateModel(); //update the LM if config already exists
	return 1;
}

int Ears::SetDictionaryDir(std::string dictionary_dir)
{
	std::string temp = MODELDIR;
	
    _dictionary_dir = temp+ dictionary_dir;
    if(_dictionary_dir.c_str() == NULL)
		return -1;
	
    UpdateModel(); //update Dictionary if config object already exists
	return 1;
}


int Ears::UpdateModel()
{
	//if init has not been called we don't need to restart pocketSphinx
    if(_config == NULL)
		return 1;
	
    ps_free(_ps); //free the decoder
	
    Init(); //call init to load the decoder with the new language model.
	
}



//enter the location of the file to be interpreted. 
//returns the string that was recognized by the decoder
std::string Ears::RawToString(const char * pathToraw)
{
	std::string er = "error";
	//open the file stream for reading in binary mode
    _fh = fopen(pathToraw, "rb");
    if (_fh == NULL) {
		perror("Failed to open raw file");
		return er;
	}
	
	//decode the binary audio files and return the number of samples recovered
    _rv = ps_decode_raw(_ps, _fh, "myUttId", -1);//decoder,file handler, utterance ID, -1 = read to end of file
    if (_rv < 0)
		return er;
		
	//get the hypothesis on the output 	
    _hyp = ps_get_hyp(_ps, &_score, &_uttid);
	
    if (_hyp == NULL)//if none of our known words match what was said send a flag for the handler to pick up
		{
			return WNF;
		}
	
    return _hyp;
}

//use this for real time decoding via a microphone. Hardware settings are handled in the hardware node 
//and assigned through the logic node

