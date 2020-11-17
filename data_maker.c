#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define DATA_MIN 0
#define DATA_MAX 1024
#define DATA_LENGTH 1000
typedef enum { false, true } bool;

int get_random_bool() {
    return random() % 2;
}

int get_random_number(int min, int max) {
    return min + rand() % ( max - min + 1 );
}

void print_high_timelocality(FILE *fp) {
    const int FREQUENTLY_USED_VALUE = 0;
    const int MIN_GAP = 1;
    const int MAX_GAP = 10;
    int gap_between_fuv = 0;
    int current_gap_idx = 0;
    int i; // used in for loop
    
    for (i = 0;i < DATA_LENGTH;i++) {
        if(current_gap_idx == gap_between_fuv) {
            gap_between_fuv = get_random_number(MIN_GAP, MAX_GAP);
            current_gap_idx = 0;
            fprintf(fp, "%d\n", FREQUENTLY_USED_VALUE);
        } else {
            fprintf(fp, "%d\n", get_random_number(DATA_MIN, DATA_MAX));
            current_gap_idx++;
        }
    }
}

void print_high_spacelocality(FILE* fp) {
    const int MIN_SECTOR_LENGTH = 3;
    const int MAX_SECTOR_LENGTH = 10;
    int sector_length = 0;
    int sector_idx = 0;
    int center_value;
    bool direction_up = false;
    int i;
    
    for(i=0;i<DATA_LENGTH;i++) {
        if(sector_idx == sector_length) {
            sector_length = get_random_number(MIN_SECTOR_LENGTH, MAX_SECTOR_LENGTH);
            sector_idx = 0;
            center_value = get_random_number(DATA_MIN, DATA_MAX);
        }
        else {
            // get random direction
            if(center_value <= DATA_MIN) {
                direction_up = true;
            }
            else if(center_value >= DATA_MAX) {
                direction_up = false;
            }
            else {
                direction_up = get_random_bool();
            }
            
            if(direction_up) {
                // center value go up
                center_value++;
            }
            else {
                // center value go down
                center_value--;
            }
            sector_idx++;
        }
        fprintf(fp, "%d\n", center_value);
    }
}

void print_pseudorandom(FILE *fp) {
    int i;
    for(i=0;i<DATA_LENGTH;i++) {
        fprintf(fp, "%d\n", get_random_number(DATA_MIN, DATA_MAX));
    }
}

int main(int argc, char *argv[]) {
    FILE* output;
    // Set seed
    srand(time(NULL));
    
    // Make sure there are 4 arguments given on command line.
	if (argc != 3) {
		perror("Error: Invalid Number of Arguments!");
		return EXIT_FAILURE;
	}
    
    // Open file and check to see if it's opened correctly.
	if ( (output = fopen(argv[2], "w")) == NULL ) {
		perror("Error: Inavlid File!\n");
		return EXIT_FAILURE;
	}
    
    char mod = argv[1][0];
    switch(mod) {
        case 't':
            print_high_timelocality(output);
            break;
        case 's':
            print_high_spacelocality(output);
            break;
        case 'r':
            print_pseudorandom(output);
            break;
        default:
            perror("Error: Invalid Argument!");
            fclose(output);
		    return EXIT_FAILURE;
    }
    
    fclose(output);
    return EXIT_SUCCESS;
}