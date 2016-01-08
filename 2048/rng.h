/************ RNJezus */
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
static inline unsigned unifRandom(unsigned n) {
    static int seeded = 0;

    if(!seeded) {
        int fd = open("/dev/urandom", O_RDONLY);
        unsigned short seed[3];
        if(fd < 0 || read(fd, seed, sizeof(seed)) < (int)sizeof(seed)) {
            srand48(time(NULL));
        } else {
            seed48(seed);
        }
        if(fd >= 0)
            close(fd);

        seeded = 1;
    }
    
    return (int)(drand48() * n);
}
