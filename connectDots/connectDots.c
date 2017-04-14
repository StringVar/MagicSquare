

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#define STROKEWIDTH_RATIO 0.1
// flags:
/* pure data for me to just not care
one for a file
-i for pure input [FileOutName][space][size][iii ii i ii i]
-f for file [fileformat
output flags
-s svg file
-p svg and a cario render
*//*
file fomat:
size: squares so just square that
===
size\n
123
456
789
*/

typedef struct triple
{
    int i;
    int x;
    int y;
}triple;
void printTriple(int size, triple t[])
{
    int i;
    for( i = 0; i < size; i++ )
    {
    // <line x1="0" y1="0" x2="200" y2="200" style="stroke:rgb(255,0,0);stroke-width:2" />
        printf("<%d,%d,%d>\n", t[i].i, t[i].x, t[i].y);
    }
}
compTriple_i(const void *a, const void *b)
{
    triple * u = (triple*)a;
    triple * v = (triple*)b;

    if( u->i == v->i )
        return 0;
    else if( u->i > v->i )
        return 1;
    else return -1;
}


void svgTripleConnectDots(FILE *fp, int size, int squSize, triple t[])
{
    int i;
    int multi = 100;
    /*fprintf(fp, "<!DOCTYPE html>\n<html>\n<body>");*/
    fprintf(fp, "<svg width=\"%d\" height=\"%d\">\n", (size + 1)*multi, (size + 1)*multi);

    fprintf(fp, "<g stroke=\"black\" stroke-width=\"3\" fill=\"black\"/>\n<path pathLength = \"%i\" d=\"",squSize);

    fprintf(fp, " M %d %d", t[0].x*multi, t[0].y*multi);
    for( i = 1; i < squSize; i += 1 )
    {
        //fprintf(fp, " l %F %F",((double)t[i].x)*fract*multi, ((double)t[i].y)*fract)*multi;
        fprintf(fp, " L %d %d", t[i].x*multi, t[i].y*multi);
    }
    fprintf(fp, "\"   >");
    fprintf(fp, "</g></svg>");


    /*fprintf(fp, "\n<body>\n</html>");*/
}




int mainf(char* argv)
{
    char fileName[80];
    strcpy(fileName, argv);
    FILE *fp, *svgfp;
    fp = fopen(strcat(fileName, ".txt\0"), "r");
    svgfp = fopen(strcat(fileName, ".svg\0"), "w");
    if( fp == NULL || svgfp == NULL )
    {
        printf("ERROR cannot open file");
        return 0;
    }
    int size;
    int squSize;
    int x, y;//incremeting opperator
    int i;//sub
    int count;
    fscanf(fp, "%d\n", &size);

    squSize = size*size;
    triple(*tri);
    tri = malloc(sizeof(triple)*squSize);
    count = 0;
    i = 0;
    for( x = 0; x < size; x++ )
    {
        for( y = 0; y < size; y++ )
        {
            fscanf(fp, "%d", &i);
            tri[count].i = i;
            tri[count].x = x + 1;
            tri[count].y = y + 1;
            count++;

        }
    }
    qsort(tri, squSize, sizeof(triple), compTriple_i);
    printf("=====\n");
    printTriple(squSize, tri, squSize);
    printf("=====\n");
    //getchar();

    svgTripleConnectDots(svgfp, size, squSize, tri);

    fclose(fp);
    fclose(svgfp);
    getchar();
    return 0;
}
int main()
{
    //mainf("3x3 - Saturn=15\0");
    //mainf("4x4 - Jupiter=34\0");
    //mainf("5x5 - Mars=65\0");
    //mainf("6x6 - Sol=111\0");
    //mainf("7x7 - Venus=175\0");
    //mainf("8x8 - Mercury=260\0");
    //mainf("9x9 - Luna=369\0");
    /*mainf("4x4 pandiagonal magic square A");
    mainf("4x4 pandiagonal magic square B");
    mainf("4x4 pandiagonal magic square C");*/
    //mainf("12x12 Most Perfect n2");
    //mainf("12x12 Most Perfect n2");
    mainf("12x12 panmagic=870");
}