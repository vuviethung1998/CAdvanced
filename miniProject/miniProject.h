#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./Dijstra.h"
#include "./fields.h"
#define MAX 100

typedef struct station {
    int idStat;
    char name[MAX];
    int route[MAX];
    int countRoute;
}station;

typedef struct dist {
    int node1;
    int node2;
    double distance;
}dist;

typedef struct busRoute {
    int idBus;
    int routeStat[MAX + 1];
    dist distance[MAX];
    int countStat;
} bus;

int getStatNameNId(char *fn1, station statList[]) {
    FILE *f1 = fopen(fn1, "r");
    int count = 0;
    
    if(f1 == NULL ) {
        printf("fail!\n");
        return -1;
    }else {
        int i = 0;
        char *line = NULL;
        size_t len = 0;
        __ssize_t read;
        do {
            char c;
            fscanf(f1,"%d%c%[^\n]", &statList[i].idStat, &c, statList[i].name);
            i++;
            count ++;
        }while((read = getline(&line, &len, f1))!= -1);
    }
    fclose(f1);
    return count;
}

void getStatBusList(char *fn1, station statList[]) {
    IS is;
    is =new_inputstruct(fn1);
    if(is == NULL) {
        printf("fail!\n");
        return ;
    }else {
        int i;
        while(get_line(is) >= 0) {
            for(i = 1; i < is->NF; i++) {
                statList[is->line -1].route[i -1] = atoi(is->fields[i]);
            }
            statList[is->line -1].countRoute = is->NF - 1;
        }
        jettison_inputstruct(is);
    }
}

int getBusStatList(char *fn1, bus busList[]) {
    int count = 0;
    IS is;
    is = new_inputstruct(fn1);
    if(is == NULL) {
        printf ("fail\n");
        return -1;
    }else {
        int i;
        while(get_line(is) >= 0) {
            busList[is->line -1].idBus = atoi(is->fields[0]);

            for(i =1; i< is->NF; i++) {
                busList[is->line -1].routeStat[i-1] = atoi(is->fields[i]);
            }
            busList[is->line -1].countStat = is->NF - 1;
            count ++;
        }
        jettison_inputstruct(is);
    }
    return count;
}

void getBusDistList(char *fn1, bus busList[], int countBus) {
    IS is;
    is =new_inputstruct(fn1);
    if(is == NULL) {
        return ;
    }
    while(get_line(is) >= 0) {
        int x ,y;
        for(int i = 0; i < countBus; i ++) 
            for(int j = 0; j < busList[i].countStat - 1; j ++) {
                x = busList[i].routeStat[j];
                y = busList[i].routeStat[j+ 1];
                if((atoi(is->fields[0]) == x) && (atoi(is->fields[1]) == y)) {
                    busList[i].distance[j].node1 = x; 
                    busList[i].distance[j].node2 = y;
                    busList[i].distance[j].distance = atof(is->fields[2]);
                }
            }
    }
    jettison_inputstruct(is);
    return ;
}

//lay ten tram tu index
void displayStationByIndex(station statList[], int countStat,int index) {
    for(int i = 0; i < countStat; i++) {
        if(statList[i].idStat == index) {
            printf("%s", statList[i].name);
        }
    }
    return ;
}

//the hien lo trinh bang index
void displayBusRouteByIndex(bus busList[], station statList[],int countBus,int index) {
    for(int i = 0; i< countBus; i++) {
        if(busList[i].idBus == index){
            for(int j = 0; j < busList[i].countStat - 1; j++) {
                printf("%s->", statList[busList[i].routeStat[j]].name);
            }
            printf("%s\n",statList[busList[i].routeStat[busList[i].countStat - 1]].name);
        }
    }

    return ;
}

//doc graph
void read_weighted_graph(graph *g, char *fn, bool directed){

  FILE *fp = fopen(fn, "r");

  if (fp == NULL) {
    printf("Can not open file !\n");
  } else {
    initgraph(g, directed);

    int x, y;
    double weight; // vertex in edge (x, y)
    int nedges;
    fscanf(fp, "%d %d\n", &(g->nvertices), &nedges);

    for (int i = 1; i <= nedges; i++) {
      fscanf(fp, "%d %d %lf\n", &x, &y, &weight);
      insert_weighted_edge(g, x, y, weight, directed);
    }
  }

  fclose(fp);
  return;
}

//lo trinh ngan nhat
int busFromTo(bus busList[], int node1, int node2, int countBus, int arrBus[]) {
    int count = 0;
    for(int i = 0; i < countBus; i ++) {
        for(int j = 0; j < busList[i].countStat -1; j ++) {
            if((busList[i].distance[j].node1 == node1) && (busList[i].distance[j].node2 == node2)) {
                arrBus[count] = busList[i].idBus;
                count ++;
            }
            else if((busList[i].distance[j].node1 == node2) && (busList[i].distance[j].node2 == node1)) {
                arrBus[count] = busList[i].idBus;
                count ++;
            }
        }
    }
    return count;
}