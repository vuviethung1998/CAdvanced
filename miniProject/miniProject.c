#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSTAT 1000
#define MAXBUS  200
#include "./fields.h"
#include "./miniProject.h"

int main() {
    station *statList = (station *)malloc(sizeof(station)* MAXSTAT);
    bus *busList = (bus *)malloc(sizeof(bus)*MAXBUS);
    int countStat  = getStatNameNId("station_name.txt",statList);
    getStatBusList("station_route.txt", statList);
    int countBus = getBusStatList("route_dat.txt", busList);
    getBusDistList("out.txt", busList, countBus);
    
    // //chuc nang 1
    // int indexStat;
    // printf("Nhap mot so: \n");
    // scanf("%d", &indexStat);
    // printf("Ten cua tram la: \n");
    // displayStationByIndex(statList, countStat,indexStat);
    // //chuc nang 2
    // int indexBus;
    // printf("Nhap ma hieu cua tuyen: \n");
    // scanf("%d", &indexBus);
    // printf("Lo trinh cua tuyen %d la: ", indexBus);
    // displayBusRouteByIndex(busList, statList, countBus, indexBus);
    // //chuc nang 3    
    // int arrStat[50], count = 0;//lst cac node trong shortest path
    // int node1,node2;
    // graph *g = (graph *)malloc(sizeof(graph));
    // read_weighted_graph(g, "testdata.txt", false);
    // dijkstra(g, 1);
    // printf("Chon diem den thu nhat: \n");
    // scanf("%d", &node1);
    // printf("Chon diem den thu hai: \n");
    // scanf("%d", &node2);
    // count = find_path_dijkstra(g, node1, node2, arrStat);
    // printf("Lo trinh ngan nhat la:\n");
    // for(int j = count; j >= 0; j --) {
    //     printf("%d", arrStat[j]);
    //     printf(" - ");
    // }
    // printf("\n");
    // for(int j = count; j >= 0; j --) {
    //     displayStationByIndex(statList,countStat,arrStat[j]);
    //     printf(" - ");
    // }
    // printf("\n");
    //chuc nang 4
    // for(int i = count; i > 0; i--) {
    //     int arrBus[50];
    //     int countFT = 0;
    //     countFT = busFromTo(busList, arrStat[i], arrStat[i-1],countBus, arrBus);
    //     if(countFT == 0) {
    //         continue;
    //     } else {
    //         printf("Di xe tuyen ");
    //         for(int j = 0; j < countFT; j++) {
    //             printf("%d ", arrBus[j]);
    //         }
    //         printf("tu ");
    //         displayStationByIndex(statList,countStat,arrStat[i]);
    //         printf("den ");
    //         displayStationByIndex(statList,countStat,arrStat[i-1]);
    //         printf("\n");
    //     }    
    // }

    int choice;
    int arrStat[50], count = 0;//lst cac node trong shortest path
    int node1,node2;
    while(1)
    {   
        printf("\n");
        printf("1. Tim ten tram theo index \n");
        printf("2. Tim lo trinh theo so hieu tuyen\n");
        printf("3. Tim lo trinh ngan nhat\n");
        printf("4. Huong dan\n");
        printf("5.Exit\n");
        printf("Enter your choice :  ");
        scanf("%d",&choice);
        
        switch(choice)
        {
            case 1:{
                //chuc nang 1
                int indexStat;
                printf("Nhap mot so: \n");
                scanf("%d", &indexStat);
                printf("Ten cua tram la: \n");
                displayStationByIndex(statList, countStat,indexStat);
                printf("\n");
                break;
            }   
            case 2: {
                //chuc nang 2
                int indexBus;
                printf("Nhap ma hieu cua tuyen: \n");
                scanf("%d", &indexBus);
                printf("Lo trinh cua tuyen %d la: ", indexBus);
                displayBusRouteByIndex(busList, statList, countBus, indexBus);
                break;
            }
            case 3:{
                graph *g = (graph *)malloc(sizeof(graph));
                read_weighted_graph(g, "testdata.txt", false);
                dijkstra(g, 1);
                printf("Chon diem den thu nhat: \n");
                scanf("%d", &node1);
                printf("Chon diem den thu hai: \n");
                scanf("%d", &node2);
                count = find_path_dijkstra(g, node1, node2, arrStat);
                printf("Lo trinh ngan nhat la:\n");
                for(int j = count; j >= 0; j --) {
                    printf("%d", arrStat[j]);
                    printf(" - ");
                }
                printf("\n\n");
                for(int j = count; j >= 0; j --) {
                    displayStationByIndex(statList,countStat,arrStat[j]);
                    printf(" - ");
                }
                printf("\n");
                break;
            }
        
            case 4: {
                for(int i = count; i > 0; i--) {
                    int arrBus[50];
                    int countFT = 0;
                    countFT = busFromTo(busList, arrStat[i], arrStat[i-1],countBus, arrBus);
                    if(countFT == 0) {
                        continue;
                    } else {
                        printf("Di xe tuyen ");
                        for(int j = 0; j < countFT; j++) {
                            printf("%d ", arrBus[j]);
                        }
                        printf("tu ");
                        displayStationByIndex(statList,countStat,arrStat[i]);
                        printf("den ");
                        displayStationByIndex(statList,countStat,arrStat[i-1]);
                        printf("\n");
                    }    
                }
                break;
            }
            case 5: {
                exit(0);
            }
        }
    }
    return 0;
}