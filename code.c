#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 20
#define COLS 40

char canvas[ROWS][COLS];

void initializeCanvas()
{
    int i, j;

    for(i = 0; i < ROWS; i++)
    {
        for(j = 0; j < COLS; j++)
        {
            canvas[i][j] = '_';
        }
    }
}

void displayCanvas()
{
    int i, j;

    for(i = 0; i < ROWS; i++)
    {
        for(j = 0; j < COLS; j++)
        {
            printf("%c", canvas[i][j]);
        }
        printf("\n");
    }
}

void drawRectangle(int row, int col, int width, int height)
{
    int i, j;

    for(i = row; i < row + height; i++)
    {
        for(j = col; j < col + width; j++)
        {
            if(i >= 0 && i < ROWS && j >= 0 && j < COLS)
            {
                if(i == row || i == row + height - 1 ||
                   j == col || j == col + width - 1)
                {
                    canvas[i][j] = '*';
                }
            }
        }
    }
}

void drawLine(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps;
    int i;

    if(dx < 0) dx = -dx;
    if(dy < 0) dy = -dy;

    steps = (dx > dy) ? dx : dy;

    if(steps == 0)
    {
        canvas[x1][y1] = '*';
        return;
    }

    float xInc = (float)(x2 - x1) / steps;
    float yInc = (float)(y2 - y1) / steps;

    float x = x1;
    float y = y1;

    for(i = 0; i <= steps; i++)
    {
        if((int)x >= 0 && (int)x < ROWS &&
           (int)y >= 0 && (int)y < COLS)
        {
            canvas[(int)x][(int)y] = '*';
        }

        x += xInc;
        y += yInc;
    }
}

void drawTriangle(int row, int col, int height)
{
    int i, j;

    for(i = 0; i < height; i++)
    {
        if(row + i < ROWS)
        {
            if(col - i >= 0)
                canvas[row + i][col - i] = '*';

            if(col + i < COLS)
                canvas[row + i][col + i] = '*';
        }
    }

    for(j = col - height + 1; j <= col + height - 1; j++)
    {
        if(row + height - 1 < ROWS &&
           j >= 0 && j < COLS)
        {
            canvas[row + height - 1][j] = '*';
        }
    }
}

void drawCircle(int cx, int cy, int radius)
{
    int x, y;

    for(x = 0; x < ROWS; x++)
    {
        for(y = 0; y < COLS; y++)
        {
            int d = (x - cx) * (x - cx) +
                    (y - cy) * (y - cy);

            int r2 = radius * radius;

            if(d >= r2 - radius &&
               d <= r2 + radius)
            {
                canvas[x][y] = '*';
            }
        }
    }
}

void deleteArea(int row, int col, int width, int height)
{
    int i, j;

    for(i = row; i < row + height; i++)
    {
        for(j = col; j < col + width; j++)
        {
            if(i >= 0 && i < ROWS &&
               j >= 0 && j < COLS)
            {
                canvas[i][j] = '_';
            }
        }
    }
}

int main()
{
    int choice;

    initializeCanvas();

    while(1)
    {
        printf("\n===== 2D GRAPHICS EDITOR =====\n");
        printf("1. Draw Rectangle\n");
        printf("2. Draw Line\n");
        printf("3. Draw Triangle\n");
        printf("4. Draw Circle\n");
        printf("5. Delete Area\n");
        printf("6. Display Canvas\n");
        printf("7. Exit\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        if(choice == 1)
        {
            int r, c, w, h;

            printf("Row Col Width Height: ");
            scanf("%d%d%d%d", &r, &c, &w, &h);

            drawRectangle(r, c, w, h);
        }
        else if(choice == 2)
        {
            int x1, y1, x2, y2;

            printf("x1 y1 x2 y2: ");
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);

            drawLine(x1, y1, x2, y2);
        }
        else if(choice == 3)
        {
            int r, c, h;

            printf("Row Col Height: ");
            scanf("%d%d%d", &r, &c, &h);

            drawTriangle(r, c, h);
        }
        else if(choice == 4)
        {
            int x, y, r;

            printf("CenterRow CenterCol Radius: ");
            scanf("%d%d%d", &x, &y, &r);

            drawCircle(x, y, r);
        }
        else if(choice == 5)
        {
            int r, c, w, h;

            printf("Row Col Width Height: ");
            scanf("%d%d%d%d", &r, &c, &w, &h);

            deleteArea(r, c, w, h);
        }
        else if(choice == 6)
        {
            displayCanvas();
        }
        else if(choice == 7)
        {
            break;
        }
        else
        {
            printf("Invalid Choice!\n");
        }
    }

    return 0;
}
