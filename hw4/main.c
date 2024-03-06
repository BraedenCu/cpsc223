
/**
 * Name: Braeden Cullen
 * Assignment: Blotto
 * Class: CPSC223 Spring 2024
 * Date: March 5th
 * Purpose: driver for blotto
 *
 */

#include "gmap.h"
#include "entry.h"
#include "string_key.h"
#include "blotto.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

/*================== BLOTTO DRIVER ==================*/

int main(int argc, char *argv[])
{
    int max_id = 32;
    int num_bf = argc - 1;
    int bf_weights[num_bf];

    FILE *in = entry_parse_args(argc, argv, &max_id, &num_bf);
    
    gmap *map = populate_gmap(in, max_id, num_bf, duplicate, compare_keys, hash29, free);
    
    find_weights(map, in, bf_weights, num_bf, argc, argv);
    
    play_matches(map, in, bf_weights, num_bf, max_id);

    blotto_cleanup(map, in);

    return 0;
}
