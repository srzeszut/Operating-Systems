#include "grid.h"
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "pthread.h"
#include <unistd.h>
#include "signal.h"

#define GRID_WIDTH 30
#define GRID_HEIGHT 30
const int grid_width = 30;
const int grid_height = 30;

char *create_grid()
{
    return malloc(sizeof(char) * grid_width * grid_height);
}

void destroy_grid(char *grid)
{
    free(grid);
}

void draw_grid(char *grid)
{
    for (int i = 0; i < grid_height; ++i)
    {
        // Two characters for more uniform spaces (vertical vs horizontal)
        for (int j = 0; j < grid_width; ++j)
        {
            if (grid[i * grid_width + j])
            {
                mvprintw(i, j * 2, "■");
                mvprintw(i, j * 2 + 1, " ");
            }
            else
            {
                mvprintw(i, j * 2, " ");
                mvprintw(i, j * 2 + 1, " ");
            }
        }
    }

    refresh();
}

void init_grid(char *grid)
{
    for (int i = 0; i < grid_width * grid_height; ++i)
        grid[i] = rand() % 2 == 0;
}

bool is_alive(int row, int col, char *grid)
{

    int count = 0;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
            {
                continue;
            }
            int r = row + i;
            int c = col + j;
            if (r < 0 || r >= grid_height || c < 0 || c >= grid_width)
            {
                continue;
            }
            if (grid[grid_width * r + c])
            {
                count++;
            }
        }
    }

    if (grid[row * grid_width + col])
    {
        if (count == 2 || count == 3)
            return true;
        else
            return false;
    }
    else
    {
        if (count == 3)
            return true;
        else
            return false;
    }
}

void update_grid(char *src, char *dst)
{
    for (int i = 0; i < grid_height; ++i)
    {
        for (int j = 0; j < grid_width; ++j)
        {
            dst[i * grid_width + j] = is_alive(i, j, src);
        }
    }
}
typedef struct
{
    char *src;
    char *dst;
    int row;
    int col;
} thread_args;

void handler(int signo, siginfo_t* info, void* context) {}

void *worker(void *arg)

{
    thread_args *data = (thread_args *)arg;
    while (true){

        int row = data->row;
        int col = data->col;
        char *src = data->src;
        data->dst[row * grid_width + col] = is_alive(row, col, src);

        pause();

        data->src = data->dst;
        data->dst = src;
    }

    return NULL;
}
void update_grid_multi(char *src, char *dst)
{
    static pthread_t threads[GRID_WIDTH * GRID_HEIGHT];
    static thread_args thread_data[GRID_WIDTH * GRID_HEIGHT];
    static int thread_count = 0;
    static bool threads_created = false;

    struct sigaction action;
    sigemptyset(&action.sa_mask);
    action.sa_sigaction = handler;
    sigaction(SIGUSR1, &action, NULL);


    if(!threads_created){
        printf("%d",threads_created);

    for (int i = 0; i < grid_height; ++i)
    {
        for (int j = 0; j < grid_width; ++j)
        {
            // Create a new thread for each cell
            thread_data[thread_count].src = src;
            thread_data[thread_count].dst = dst;
            thread_data[thread_count].row = i;
            thread_data[thread_count].col = j;
            pthread_create(&threads[thread_count], NULL, worker, (void *)&thread_data[thread_count]);
            thread_count++;
        }

    }
    threads_created=true;
    }

    for (int i = 0; i < thread_count; ++i)
    {
        pthread_kill(threads[i],SIGUSR1);
    }
}