//ears.h
#ifndef EARS_H
#define EARS_H

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

    int Init();
    int SetLanguageModelDir(std::string lang_model_dir);
    int SetDictionaryDir(std::string dictionary_dir);
    std::string RawToString(const char * path_to_raw);

private:

    int UpdateModel();

    std::string _lang_model_dir;
    std::string _dictionary_dir;

    ps_decoder_t *_ps;
    cmd_ln_t *_config;
    FILE *_fh;
    char const *_hyp, *_uttid;
    int16 _buf[512];
    int _rv;
    int32 _score;
};

#endif // EARS_H
