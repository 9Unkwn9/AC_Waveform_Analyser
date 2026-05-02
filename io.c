#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M_length 512
/*Filename: AC_Waveform_Analyser
Description: AC Waveform Analyser
Author: Adam Rychlinski - 23024670
Date: 02/05/2026
Version 2.0
Log: Creating Mathmatical solutions required for waveform
*/

static int c_rows(FILE *fp) {//Number of rows within CSV file
    char line[M_length];
    int rows = 0;

    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp)!=NULL) {
        rows++;
    }

    rewind(fp);//Restart file pointer to the start
    return rows;
}

int loaded_csv(const char *filename, Waveform **waveform, size_t *count) {
    FILE *file = fopen(filename, "r");//r means read in C so it makes the file open in read mode

    if (file == NULL) {
        printf("File Invalid\n");
        return 0;
    }

    int rows = c_rows(file);//Amount of rows

    if (rows <=0) {
        printf("Error no data found\n");
        fclose(file);
        return 0;
    }

    *waveform = malloc (rows * sizeof(Waveform));//Allocated memory

    if (*waveform == NULL) {
        printf("Memory Inaccessable\n");
        free(*waveform);
        fclose(file);
        return 0;
    }

    size_t i = 0;
    char line[M_length];
    fgets(line, sizeof(line), file);
    while (i < (size_t)rows &&
        fscanf(file, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
            &((*waveform + i)->timestamp),//Scans for each title within CSV file
            &((*waveform + i)->phase_A_Voltage),
            &((*waveform + i)->phase_B_Voltage),
            &((*waveform + i)->phase_C_Voltage),
            &((*waveform + i)->line_current),
            &((*waveform + i)->frequency),
            &((*waveform + i)->power_factor),
            &((*waveform + i)->thd_percentage)) == 8) {
        i++;
            }

    if (i==0) {
        printf("Error no data can be found\n");
        free(*waveform);
        fclose(file);
        return 0;
    }

    *count = i;
    fclose(file);
    return 1;
}

static void w_phase(FILE *file, const char *phase_name, const PhaseR *phase) {//Write results for individal phase
    fprintf(file, "%s\n", phase_name);
    fprintf(file, "\n");
    fprintf(file, "RMS Voltage:     %.3f V\n", phase->rms);
    fprintf(file, "Peak to peak Voltage:     %.3f V\n", phase->ptp);
    fprintf(file, "DC Offset:    %.3f V\n", phase->dc_offset);
    fprintf(file, "Clipped Samples:     %d\n", phase->c_count);

    if (phase->w_tolerance == 1) {
        fprintf(file,"Within Tolerance\n\n");
    }else {
        fprintf(file,"Outside of Tolerance\n");
    }

}

int results(
    const char *filename,//Output of all results are how they're going to be outputted in the Text file
    const PhaseR *PhaseA,
    const PhaseR *PhaseB,
    const PhaseR *PhaseC,
    size_t sample_count
) {
    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        printf("Could not create output file\n");
        return 0;
    }

    fprintf(file, "AC Waveform Analysis Report");
    fprintf(file, "\n\n\n");
    fprintf(file, "Samples Analyised: %zu\n\n",sample_count);

    w_phase(file, "Phase A:", PhaseA);
    w_phase(file, "Phase B:", PhaseB);
    w_phase(file, "Phase C:", PhaseC);

    fclose(file);

    return 1;
}