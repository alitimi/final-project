#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


//variables

    char Name[50],findName[50]="",mentionedword[50],currentwordshown[50],topic,harf,checkexit;
    int maintopicchoise,score,num=0,x,k,j,misses=0,randomnum,mentionedwordlengh,gamerun=1,saveexplore=0,letssave;
    long int Point,pointnew;
    static int checkiftrue=0;
    FILE *availabletopics;
    FILE *themaintopicfound;
    FILE *SAVELOG;
    time_t seconds,seconds2;
//functions

    void showtopics(FILE *availabletopicsin);
    char *findtopic(char index,FILE *availabletopicsin);
    int  countwords(FILE *maintopic ,int number);

//structure

    struct wordsstruct{
    char word[50];
    int wordlengh;
    int id;
    };

//main

int main()
{
    SAVELOG = fopen("SAVELOG.txt","r+");
    availabletopics = fopen("TOPICS/AVAILABLE_TOPICS.txt","r");
    printf("Enter your name:\n");
    scanf("%s",Name);
    printf("Welcome %s!\n",Name);
    printf("[1] New Game\n[2] Resume Game\n");
    scanf("%d",&maintopicchoise);

    switch(maintopicchoise){

        case 1:
        showtopics(availabletopics);
        scanf("\n%c",&topic);
        topic=topic-97;
        fseek(availabletopics,0,SEEK_SET);
        themaintopicfound = fopen(findtopic(topic,availabletopics),"r");
        num=countwords(themaintopicfound ,num)-1;
        //making structure and allocating memory
        struct wordsstruct *ptr;
        ptr = (struct wordsstruct*) malloc(num * sizeof(struct wordsstruct));
        fseek(themaintopicfound,0,SEEK_SET);
        int i=0;
        while(!feof(themaintopicfound)){
            fscanf(themaintopicfound,"%s",(ptr+i)->word);
            (ptr+i)->wordlengh=strlen((ptr+i)->word);
            (ptr+i)->id=1;
            i++;
        }
        //
        printf("GAME STARTED!\n");
        seconds = time(NULL);
        srand(time(NULL));


        while (gamerun){
            randomnum=(rand())%(num);
        if((ptr+randomnum)->id!=0){

        mentionedwordlengh=(ptr+randomnum)->wordlengh;
        strcpy(mentionedword,(ptr+randomnum)->word);

        for(j=0;j<mentionedwordlengh;++j){
            currentwordshown[j]='-';
            printf("%c",currentwordshown[j]);
        }
        currentwordshown[j]='\0';
        printf("\n");



        k=1;
        while(k){
            scanf("\n%c",&harf);
            //KHOROJ
            if(harf=='Q'){
                printf("\nAre you sure? [y/n]");
                scanf("\n%c",&checkexit);
                if(checkexit=='y'){
                    printf("Do you want to save? [y/n]");
                    scanf("\n%c",&checkexit);
                    if(checkexit=='y'){
                        fseek(SAVELOG,0,SEEK_END);
                        fprintf(SAVELOG,"%s %ld ",Name,Point);
                        return 0;
                    }
                    else if(checkexit=='n'){
                        return 0;
                    }
                }
                else if(checkexit=='n'){
                    scanf("\n%c",&harf);
                }
            }
            //
            int c;
            for(c=0;c<mentionedwordlengh;++c){
            if(mentionedword[c]==harf){
                currentwordshown[c]=harf;
                checkiftrue=1;
            }
        }
            if(checkiftrue==1){
                printf("\nCorrect! (%d/5)",5-misses);
                checkiftrue=0;
            }
            else if (checkiftrue==0){
                misses++;
                printf("\nWrong! (%d/5)",5-misses);
            }
                    switch(misses){
                        case 0:
                            printf("\n       +-----+\n       | . . |\n       |  |  |\n       | --- |\n       +-----+\n         | |\n    +-----------+\n   /|           |\\ \n  / /           \\ \\ \n / /|           |\\ \\ \n    |           |\n    |           |\n    |           |\n    +-+-+---+-+-+\n      | |   | |\n      | |   | |\n      | |   | |\n      | |   | |\n/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\ \n///////////////////////\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \n");
                    break;
                        case 1:
                            printf("\n       +-----+\n       | o o |\n       |  |  |\n       | --- |\n       +-----+\n         | |\n    +-----------+\n   /|           |\\ \n  / /           \\ \\ \n / /|           |\\ \\ \n    |           |\n    |           |\n    |           |\n    +-+-+---+-+-+\n/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\ \n///////////////////////\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \n");
                    break;
                        case 2:
                            printf("\n       +-----+\n       | o o |\n       |  |  |\n       | --- |\n       +-----+\n         | |\n    +-----------+\n   /|           |\\ \n  / /           \\ \\ \n / /|           |\\ \\ \n/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\ \n///////////////////////\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \n");
                    break;
                        case 3:
                            printf("\n       +-----+\n       | o o |\n       |  |  |\n       | --- |\n       +-----+\n         | |\n/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\ \n///////////////////////\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \n");
                    break;
                        case 4:
                            printf("\n       +-----+\n       | * * |\n       |  |  |\n/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\ \n///////////////////////\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \n");
                    break;
                        case 5:
                            printf("\n        Bye Bye!!!\n/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\ \n///////////////////////\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \n");
                            printf("\nyou lost. The word was %s.\n",mentionedword);
                            (ptr+randomnum)->id=0;
                            misses=0;
                            randomnum=(rand())%(num);
                            k=0;
                    break;
                }
        printf("\n");
        if(k!=0){
        for(x=0;x<mentionedwordlengh;++x){
            printf("%c",currentwordshown[x]);
        }
        }
        printf("\n");
        if(!strcmp(mentionedword,currentwordshown)){
                printf("Correct! The word was %s.\n",mentionedword);
                Point=Point+(3*mentionedwordlengh-misses);
                (ptr+randomnum)->id=0;
                misses=0;
                randomnum=(rand())%(num);
                k=0;
        }
        }
        }
        else{
        int m,ch=0;
            for(m=0;m<num;++m){
               ch=ch+(ptr+m)->id;
            }
            if(ch==0)
            {
              seconds2 = time(NULL);
              printf("\nYour Total Points Are %ld\n",Point+Point/(seconds2-seconds));
              printf("\nDo you want to continue? [y,n]\n");
              scanf("%c",&harf);
              if(harf=='n'){
                printf("Do you want to save? [y/n]");
                    scanf("\n%c",&harf);
                    if(harf=='y'){
                        fseek(SAVELOG,0,SEEK_END);
                        fprintf(SAVELOG,"%s %ld ",Name,Point+Point/(seconds2-seconds));
                        return 0;
                    }
                    else if(harf=='n'){
                        return 0;
                    }
              }
              else if(harf=='y'){
                showtopics(availabletopics);
                scanf("\n%c",&topic);
                topic=topic-97;
                fseek(availabletopics,0,SEEK_SET);
                themaintopicfound = fopen(findtopic(topic,availabletopics),"r");
                num=countwords(themaintopicfound ,num);
                //making structure and allocating memory
                ptr = (struct wordsstruct*) malloc(num * sizeof(struct wordsstruct));
                int i=0;
                fseek(themaintopicfound,0,SEEK_SET);
                while(!feof(themaintopicfound)){
                fscanf(themaintopicfound,"%s",(ptr+i)->word);
                (ptr+i)->wordlengh=strlen((ptr+i)->word);
                (ptr+i)->id=1;
                i++;
                }
                //
                printf("GAME STARTED!\n");
              }
            }
            else{
                randomnum=(rand())%(num);
            }
        }
        }

     break;

        case 2:
        //open save
        while(strcmp(Name,findName)){
            fscanf(SAVELOG,"%s",findName);
                if(!strcmp(Name,findName)){
                    fscanf(SAVELOG,"%ld",&pointnew);
                }
        }
        /*
        //test////
        printf("%d",saveexplore1);
        SAVELOG = fopen("SAVELOG.txt","+");
        fseek(SAVELOG,0,SEEK_SET);
        while(saveexplore1){
        fscanf(SAVELOG,"%s",findName);
        saveexplore1--;
        }
        fprintf(SAVELOG,"*");
        //*/
        showtopics(availabletopics);
        scanf("\n%c",&topic);
        topic=topic-97;
        fseek(availabletopics,0,SEEK_SET);
        themaintopicfound = fopen(findtopic(topic,availabletopics),"r");

        num=countwords(themaintopicfound ,num)-1;
        //making structure and allocating memory
        struct wordsstruct *ptrn;
        ptrn = (struct wordsstruct*) malloc(num * sizeof(struct wordsstruct));
        i=0;
        fseek(themaintopicfound,0,SEEK_SET);
        while(!feof(themaintopicfound)){
            fscanf(themaintopicfound,"%s",(ptrn+i)->word);
            (ptrn+i)->wordlengh=strlen((ptrn+i)->word);
            (ptrn+i)->id=1;
            i++;
        }
        //
        printf("GAME STARTED!\n");
        seconds = time(NULL);
        srand(time(NULL));


        while (gamerun){
        randomnum=(rand())%(num);
        if((ptrn+randomnum)->id!=0){
        mentionedwordlengh=(ptrn+randomnum)->wordlengh;
        strcpy(mentionedword,(ptrn+randomnum)->word);

        for(j=0;j<mentionedwordlengh;++j){
            currentwordshown[j]='-';
            printf("%c",currentwordshown[j]);
        }
        currentwordshown[j]='\0';
        printf("\n");

        k=1;
        while(k){
            scanf("\n%c",&harf);
            //KHOROJ
            if(harf=='Q'){
                printf("\nAre you sure? [y/n]");
                scanf("\n%c",&checkexit);
                if(checkexit=='y'){
                    printf("Do you want to save? [y/n]");
                    scanf("\n%c",&checkexit);
                    if(checkexit=='y'){
                            letssave=pointnew;
                            while(letssave/10!=0){
                                saveexplore++;
                                letssave=letssave/10;
                            }
                    fseek(SAVELOG,-(saveexplore+1),SEEK_CUR);
                           fprintf(SAVELOG,"%ld",pointnew+Point);
                           return 0;
                    }
                    else if(checkexit=='n'){
                        return 0;
                    }
                }
                else if(checkexit=='n'){
                    scanf("\n%c",&harf);
                }
            }
            //
            int c;


            for(c=0;c<mentionedwordlengh;++c){
            if(mentionedword[c]==harf){
                currentwordshown[c]=harf;
                checkiftrue=1;
            }
        }
            if(checkiftrue==1){
                printf("\nCorrect! (%d/5)",5-misses);
                checkiftrue=0;
            }
            else if (checkiftrue==0){
                misses++;
                printf("\nWrong! (%d/5)",5-misses);
            }
                    switch(misses){
                        case 0:
                            printf("\n       +-----+\n       | . . |\n       |  |  |\n       | --- |\n       +-----+\n         | |\n    +-----------+\n   /|           |\\ \n  / /           \\ \\ \n / /|           |\\ \\ \n    |           |\n    |           |\n    |           |\n    +-+-+---+-+-+\n      | |   | |\n      | |   | |\n      | |   | |\n      | |   | |\n/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\ \n///////////////////////\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \n");
                    break;
                        case 1:
                            printf("\n       +-----+\n       | o o |\n       |  |  |\n       | --- |\n       +-----+\n         | |\n    +-----------+\n   /|           |\\ \n  / /           \\ \\ \n / /|           |\\ \\ \n    |           |\n    |           |\n    |           |\n    +-+-+---+-+-+\n/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\ \n///////////////////////\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \n");
                    break;
                        case 2:
                            printf("\n       +-----+\n       | o o |\n       |  |  |\n       | --- |\n       +-----+\n         | |\n    +-----------+\n   /|           |\\ \n  / /           \\ \\ \n / /|           |\\ \\ \n/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\ \n///////////////////////\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \n");
                    break;
                        case 3:
                            printf("\n       +-----+\n       | o o |\n       |  |  |\n       | --- |\n       +-----+\n         | |\n/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\ \n///////////////////////\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \n");
                    break;
                        case 4:
                            printf("\n       +-----+\n       | * * |\n       |  |  |\n/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\ \n///////////////////////\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \n");
                    break;
                        case 5:
                            printf("\n        Bye Bye!!!\n/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\ \n///////////////////////\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \n");
                            printf("\nyou lost. The word was %s.\n",mentionedword);
                            (ptrn+randomnum)->id=0;
                            misses=0;
                            randomnum=(rand())%(num);
                            k=0;
                    break;
                }
        printf("\n");
        if(k!=0){
        for(x=0;x<mentionedwordlengh;++x){
            printf("%c",currentwordshown[x]);
        }
        }
        printf("\n");
        if(!strcmp(mentionedword,currentwordshown)){
                printf("Correct! The word was %s.\n",mentionedword);
                Point=Point+(3*mentionedwordlengh-misses);
                (ptrn+randomnum)->id=0;
                misses=0;
                randomnum=(rand())%(num);
                k=0;

        }
        }
        }
        else{
        int m,ch=0;
            for(m=0;m<num;++m){
               ch=ch+(ptrn+m)->id;
            }
            if(ch==0)
            {
              seconds2=time(NULL);
              printf("\nYour Total Points Are %ld\n",pointnew+Point+Point/(seconds2-seconds));
              printf("\nDo you want to continue? [y,n]\n");
              scanf("%c",&harf);
              if(harf=='n'){
                printf("Do you want to save? [y/n]");
                    scanf("\n%c",&harf);
                    if(harf=='y'){
                            letssave=pointnew;
                            while(letssave/10!=0){
                                saveexplore++;
                                letssave=letssave/10;
                            }
                        fseek(SAVELOG,-(saveexplore+1),SEEK_CUR);
                        fprintf(SAVELOG,"%ld",pointnew+Point+Point/(seconds2-seconds));
                    }
                    else if(harf=='n'){
                        return 0;
                    }
              }
              else if(harf=='y'){
                showtopics(availabletopics);
                scanf("\n%c",&topic);
                topic=topic-97;
                fseek(availabletopics,0,SEEK_SET);
                themaintopicfound = fopen(findtopic(topic,availabletopics),"r");
                num=countwords(themaintopicfound ,num);
                //making structure and allocating memory
                ptrn = (struct wordsstruct*) malloc(num * sizeof(struct wordsstruct));
                int i=0;
                fseek(themaintopicfound,0,SEEK_SET);
                while(!feof(themaintopicfound)){
                fscanf(themaintopicfound,"%s",(ptrn+i)->word);
                (ptrn+i)->wordlengh=strlen((ptrn+i)->word);
                (ptrn+i)->id=1;
                i++;
                }
                //
                printf("GAME STARTED!\n");
              }
              }
            else{
                randomnum=(rand())%(num);
            }
        }
        }
     break;
    }
    return 0;
}

    int countwords(FILE *maintopic ,int number){
            while(!feof(maintopic)){
            char x;
            fscanf(maintopic,"%c",&x);
            if(x==' '){
                number++;
            }
        }
        return number;
    }

    void showtopics(FILE *availabletopicsin){
    char test[50],index='a';
    printf("Choose one topic:\n");
    fseek(availabletopicsin,0,SEEK_SET);
    while (!feof(availabletopicsin)){
        fscanf(availabletopicsin,"%s\n",test);
        printf("(%c) %s\n",index,test);
        index++;
    }
    }

    char *findtopic(char index,FILE *availabletopicsin){
        char thetopic[50],explorer[50];
        static char thetopic1[50];
        while(index){
        fscanf(availabletopicsin,"%s",explorer);
        index--;
        }
        fscanf(availabletopicsin,"%s",thetopic);
        strcpy(thetopic1,"TOPICS/");
        strcat(thetopic1,thetopic);
        strcpy(thetopic,".txt");
        strcat(thetopic1,thetopic);
        return thetopic1;
    }



