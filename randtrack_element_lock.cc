#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "defs.h"
#include "hash.h"

#define SAMPLES_TO_COLLECT 10000000
#define RAND_NUM_UPPER_BOUND 100000
#define NUM_SEED_STREAMS 4

/* 
 * ECE454 Students: 
 * Please fill in the following team struct 
 */
team_t team = {
    "miniscule", /* Team name */
    "Yupeng Wang",                  /* Member full name */
    "1003272521",                   /* Member student number */
    "yupeng.wang@mail.utoronto.ca", /* Member email address */
};

unsigned num_threads;
unsigned samples_to_skip;

class sample;

class sample {
    unsigned my_key;
    pthread_mutex_t lock;

    public:
        sample *next;
        unsigned count;

        sample(unsigned the_key)
        {
            my_key = the_key;
            count = 0;
            lock = PTHREAD_MUTEX_INITIALIZER;
        };
        unsigned key() { return my_key; }
        void print(FILE *f) { printf("%d %d\n", my_key, count);}
        void atomic_incre() {
            pthread_mutex_lock(&lock);
            count++;
            pthread_mutex_unlock(&lock);
        }
};

// This instantiates an empty hash table
// it is a C++ template, which means we define the types for
// the element and key value here: element is "class sample" and
// key value is "unsigned".
hash<sample, unsigned> h;

void *random_generator(void *arg) {
    int rnum;
    int i, j, k;
    sample *s;
    unsigned key;

    // process streams starting with different initial numbers
    for (i = 0; i < NUM_SEED_STREAMS / num_threads; i++) {
        rnum = *((int *) (arg)) + i;

        for (j = 0; j < SAMPLES_TO_COLLECT; j++) {

            // skip a number of samples
            for (k = 0; k < samples_to_skip; k++) {
                rnum = rand_r((unsigned int *)&rnum);
            }

            // force the sample to be within the range of 0..RAND_NUM_UPPER_BOUND-1
            key = rnum % RAND_NUM_UPPER_BOUND;
            
            // if this sample has not been counted before
            h.lock(key);
            if (!(s = h.lookup(key))) {

                // insert a new element for it into the hash table
                s = new sample(key);
                h.insert(s);
                h.unlock(key);
            }
            h.unlock(key);

            // increment the count for the sample
            s->atomic_incre();
        }
    }
}



int main(int argc, char *argv[]) {
    int rnum;
    //pthread_mutex_init(&global_lock, NULL);
    pthread_t tid[NUM_SEED_STREAMS];
    int args[NUM_SEED_STREAMS];

    // Print out team information
    printf("Team Name: %s\n", team.team);
    printf("\n");
    printf("Student 1 Name: %s\n", team.name1);
    printf("Student 1 Student Number: %s\n", team.number1);
    printf("Student 1 Email: %s\n", team.email1);
    printf("\n");

    // Parse program arguments
    if (argc != 3) {
        printf("Usage: %s <num_threads> <samples_to_skip>\n", argv[0]);
        exit(1);
    }

    sscanf(argv[1], " %d", &num_threads); // not used in this single-threaded version
    sscanf(argv[2], " %d", &samples_to_skip);

    // initialize a 16K-entry (2**14) hash of empty lists
    h.setup(14);

    int i;

    for (i = 0; i < num_threads; i++) {
        args[i] = i * NUM_SEED_STREAMS / num_threads;
        pthread_create(&tid[i], NULL, random_generator, &args[i]);
    }

    for (i = 0; i < num_threads; i++) {
        pthread_join(tid[i], NULL);
    }

    // print a list of the frequency of all samples
    h.print();
}