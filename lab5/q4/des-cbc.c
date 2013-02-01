#include <mcrypt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

main() {

    MCRYPT td;
    int i;
    char *key; 
    char *block_buffer;
    char *IV;
    int blocksize;
    int keysize = 7; /* 56 bits == 7 bytes */


    key = calloc(1, keysize);
    strcpy(key, "prakash");

    td = mcrypt_module_open("des", NULL, "cbc", NULL);

    blocksize = mcrypt_enc_get_block_size(td);
    block_buffer = malloc(blocksize);

    IV=malloc(mcrypt_enc_get_iv_size(td));

    for (i=0; i < mcrypt_enc_get_iv_size(td); i++) {
        IV[i]=rand();
    }

    mcrypt_generic_init( td, key, keysize, IV);

    /* Encryption in CBC is performed in blocks */
    while ( fread (block_buffer, 1, blocksize, stdin) == blocksize ) {
        //mcrypt_generic (td, block_buffer, blocksize);
        mdecrypt_generic (td, block_buffer, blocksize); 
        fwrite ( block_buffer, 1, blocksize, stdout);
    }

    /* deinitialize the encryption thread */
    mcrypt_generic_deinit (td);

    /* Unload the loaded module */
    mcrypt_module_close(td);

    return 0;

}
