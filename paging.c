#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int frameNo;
int *frame;
int *clockFrame;
int fault = 0;
char policy[8];
int *pageSequence;
int*lruFrame;
int count = 0;
int*optFrame;


int compare(int pageNo)
{
    int i;
    int hit = -1;
    for(i=0; i<frameNo; i++)
    {
        if(frame[i] == pageNo)
        {
            hit = i;
            break;
        }

    }
    return hit;
}

void display()
{
    int counter=0;
    while(counter < frameNo)
    {
        if(frame[counter] > -1)
            printf("%02d ",frame[counter]);
        counter = counter+1;
    }
    printf("\n");
}


void fifo()
{
    int j=0;
    int i;
    int index = 0;
    printf("Replacement Policy = FIFO\n");
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");
    for(i = 0; i < count; i++)
    {
        if(compare(pageSequence[i])!= -1)
        {
            printf("%02d     ",pageSequence[i]);
        }
        else
        {
            if(frame[index % frameNo] != -1000)
            {
                printf("%02d F   ",pageSequence[i]);
                fault++;
            }
            else
                printf("%02d     ",pageSequence[i]);
            frame[index++ % frameNo] = pageSequence[i];
        }
        display();

    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n",fault);
}

void opt(){

    optFrame = (int*)malloc(frameNo*sizeof(int));
    int nextFrame = 0;
    int number = 0;
    int i;

    printf("Replacement Policy = OPTIMAL\n");
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");


    for(i = 0; i < count; i++)
    {

        if(compare(pageSequence[i])!= -1)
        {
             optFrame[compare(pageSequence[i])] = number++;
            printf("%02d     ",pageSequence[i]);
        }
        else
        {
            if(nextFrame < frameNo)
            {
                frame[nextFrame] = pageSequence[i];
                 
                optFrame[nextFrame++] = number++;

                printf("%02d     ",pageSequence[i]);
            }
            else
            {
                int max = -9999;
                int maxIndex;
                for(int i = 0; i< frameNo; i++)
                {
                    if(optFrame[i]>max)
                    {
                        max = optFrame[i];
                        maxIndex = i;
                    }
                }
                frame[maxIndex] = pageSequence[i];
                optFrame[maxIndex] = number++;
                fault++;
                printf("%02d F   ",pageSequence[i]);
            }

        }
        display();
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n",fault);




}





void lru()
{
    lruFrame = (int*)malloc(frameNo*sizeof(int));
    int nextFrame = 0;
    int number = 0;
    int i;

    printf("Replacement Policy = LRU\n");
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");


    for(i = 0; i < count; i++)
    {

        if(compare(pageSequence[i])!= -1)
        {
            lruFrame[compare(pageSequence[i])] = number++;
            printf("%02d     ",pageSequence[i]);
        }
        else
        {
            if(nextFrame < frameNo)
            {
                frame[nextFrame] = pageSequence[i];
                lruFrame[nextFrame++] = number++;

                printf("%02d     ",pageSequence[i]);
            }
            else
            {
                int min = 9999;
                int minIndex;
                for(int i = 0; i< frameNo; i++)
                {
                    if(lruFrame[i] < min)
                    {
                        min = lruFrame[i];
                        minIndex = i;
                    }
                }
                frame[minIndex] = pageSequence[i];
                lruFrame[minIndex] = number++;
                fault++;
                printf("%02d F   ",pageSequence[i]);
            }

        }
        display();
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n",fault);
}


void clock()
{
    clockFrame = (int*) malloc(frameNo*sizeof(int));
    printf("Replacement Policy = CLOCK\n");
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");
    int index = 0;
    for(int i = 0; i < count; i++)
    {

        if(compare(pageSequence[i]) != -1)
        {
            clockFrame[compare(pageSequence[i])] = 1;

            printf("%02d     ",pageSequence[i]);
        }
        else
        {

            while(clockFrame[index % frameNo] != 0)
            {
                clockFrame[index % frameNo] = 0;
                index++;
            }
            frame[index % frameNo] = pageSequence[i];
            clockFrame[index% frameNo] = 1;
            index++;
            if(index > frameNo)
            {
                printf("%02d F   ",pageSequence[i]);
                fault++;
            }
            else printf("%02d     ",pageSequence[i]);

        }
        display;
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n",fault);
}


int main()
{
    int pageNo;
    int i;
    frame = (int*) malloc(frameNo*sizeof(int));
    pageSequence = (int*) malloc(100*sizeof(int));

    scanf("%d",&frameNo);
    scanf("%s", policy);

    for(i = 0; i < frameNo; i++)
    {
        frame[i] = -1000;
    }

    for(i=0; i<100; i++)
    {
        scanf("%d",&pageNo);
        if (pageNo == -1) break;
        pageSequence[i] = pageNo;
        count++;

    }

    if(strcmp(policy,"FIFO")==0)
        fifo();
    else if(strcmp(policy,"LRU")==0)
        lru();
    else if(strcmp(policy,"CLOCK")==0)
        clock();
     else if(strcmp(policy,"OPTIMAL")==0)
         opt();
    return 0;
}

