#include <pocketsphinx.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#define FALSE 0
#define TRUE  1
 
int main(int argc, char** argv)
{
    ps_decoder_t *ps;
    cmd_ln_t *config;

    config = cmd_ln_init(NULL, ps_args(), TRUE,
                         "-hmm", MODELDIR "/hmm/en_US/hub4wsj_sc_8k",
                         "-lm", MODELDIR "/lm/en/turtle.DMP",
                         "-dict", MODELDIR "/lm/en/turtle.dic",
                         NULL);

    if(NULL == config)
        return 1;

    // initialize the decoder
    ps = ps_init(config);
    if(NULL == ps)
        return 1;

    // open audio file
    FILE *fh;
    fh = fopen("../resources/goforward.raw", "rb");
    if(NULL == fh)
    {
        perror("Failed to open goforward.raw");
        return 1;
    }

    // decode the audio file
    int rv = ps_decode_raw(ps, fh, "goforward", -1);
    if(rv < 0)
        return 1;

    // get the hypothesis
    char const *hyp, *uttid;
    int32_t score;

    hyp = ps_get_hyp(ps, &score, &uttid);
    if(NULL == hyp)
        return 1;
    printf("Recognized: %s\n", hyp);

    // start the utterance
    fseek(fh, 0, SEEK_SET);
    rv = ps_start_utt(ps, "goforward");
    if(rv < 0)
        return 1;

    // read 512 samples at a time from the file
    // and feed them to the decoder
    int16_t buf[512];
    while(!feof(fh))
    {
        size_t nsamp;
        nsamp = fread(buf, 2, 512, fh);
        rv = ps_process_raw(ps, buf, nsamp, FALSE, FALSE);
    }

    // mark end of utterance
    rv = ps_end_utt(ps);
    if(rv < 0)
        return 1;

    // get hypothesis string
    hyp = ps_get_hyp(ps, &score, &uttid);
    if(NULL == hyp)
        return 1;
    printf("Recognized: %s\n", hyp);

    // clean up
    fclose(fh);
    ps_free(ps);

    return 0;



}
