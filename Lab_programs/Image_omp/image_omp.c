// We need to write a program to convert a RGB image to a B/W image using OpenMP.
// We need to demonstrate the performance of different scheduling policies for various chunk sizes.
// We also need to analyse the scheduling patterns by assigning a single color value for an image for each thread.
// Tabulate the following
// Image sizes (Width x Height): 512 x 512, 1024 x 1024, 2048 x 2048, 4096 x 4096
// Schedule types: default, static, dynamic, guided

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <gd.h>
#include <error.h>
#include <string.h>

void process_pixels(gdImagePtr img, int x, int h)
{
    int y, color, red, green, blue, tmp, tid;
    for (y = 0; y < h; y++)
    {
        tid = omp_get_thread_num();
        color = gdImageGetPixel(img, x, y);
        red = gdImageRed(img, color);
        green = gdImageGreen(img, color);
        blue = gdImageBlue(img, color);
        tmp = (red + green + blue) / 3;

        switch (tid)
        {
        case 0:
            color = gdImageColorAllocate(img, tmp, 0, 0);
            break;
        case 1:
            color = gdImageColorAllocate(img, 0, tmp, 0);
            break;
        case 2:
            color = gdImageColorAllocate(img, 0, 0, tmp);
            break;
        default:
            color = gdImageColorAllocate(img, tmp, tmp, tmp);
        }
        gdImageSetPixel(img, x, y, color);
    }
}

double process_image(char *iname, char *oname, int num_threads, const char *schedule_type, int chunk_size)
{
    FILE *fp = NULL;
    gdImagePtr img;
    int tid, tmp, red, green, blue, color, x, y, h, w;

    if ((fp = fopen(iname, "r")) == NULL)
    {
        error(1, 0, "Error: %s not found", iname);
    }
    img = gdImageCreateFromPng(fp);
    fclose(fp);

    w = gdImageSX(img);
    h = gdImageSY(img);

    double start = omp_get_wtime();
    omp_set_num_threads(num_threads);

    if (strcmp(schedule_type, "static") == 0)
    {
#pragma omp parallel for private(x, y, color, red, green, blue, tid) schedule(static, chunk_size)
        for (x = 0; x < w; x++)
        {
            process_pixels(img, x, h);
        }
    }
    else if (strcmp(schedule_type, "dynamic") == 0)
    {
#pragma omp parallel for private(x, y, color, red, green, blue, tid) schedule(dynamic, chunk_size)
        for (x = 0; x < w; x++)
        {
            process_pixels(img, x, h);
        }
    }
    else if (strcmp(schedule_type, "guided") == 0)
    {
#pragma omp parallel for private(x, y, color, red, green, blue, tid) schedule(guided, chunk_size)
        for (x = 0; x < w; x++)
        {
            process_pixels(img, x, h);
        }
    }

    double end = omp_get_wtime();

    if ((fp = fopen(oname, "w")) == NULL)
    {
        error(1, 0, "Error: %s not found", oname);
    }
    gdImagePng(img, fp);
    fclose(fp);
    gdImageDestroy(img);

    return end - start;
}

int main(int argc, char *argv[])
{
    const int sizes[] = {512};
    const char *schedules[] = {"static", "dynamic", "guided"};
    const int chunk_sizes[] = {1, 10, 50, 100};
    const int num_threads = 4;

    printf("\nPerformance Results (Time in seconds)\n");
    printf("=====================================\n");
    printf("Size\tSchedule\tChunk\tTime\n");

    char input_file[256], output_file[256];

    for (int i = 0; i < sizeof(sizes) / sizeof(sizes[0]); i++)
    {
        sprintf(input_file, "input_%dx%d.png", sizes[i], sizes[i]);

        for (int j = 0; j < sizeof(schedules) / sizeof(schedules[0]); j++)
        {
            for (int k = 0; k < sizeof(chunk_sizes) / sizeof(chunk_sizes[0]); k++)
            {
                sprintf(output_file, "output/output_%dx%d_%s_%d.png", sizes[i], sizes[i], schedules[j], chunk_sizes[k]);

                double time = process_image(input_file, output_file, num_threads, schedules[j], chunk_sizes[k]);

                printf("%dx%d\t%s\t\t%d\t%.4f\n", sizes[i], sizes[i], schedules[j], chunk_sizes[k], time);
            }
        }
    }

    return 0;
}