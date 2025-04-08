#include <stdio.h>

struct router {
    unsigned cost[20];
    unsigned from[20];
} routingtable[10];

int main() {
    int costmat[20][20];
    int routers, i, j, k, count = 0;

    printf("Enter number of routers: ");
    scanf("%d", &routers);

    printf("Enter the cost matrix:\n");
    for(i = 0; i < routers; i++) {
        for(j = 0; j < routers; j++) {
            scanf("%d", &costmat[i][j]);
            if(i == j) {
                costmat[i][j] = 0;  // Cost to itself is always 0
            }
        }
    }

    // Initialize routing table
    for(i = 0; i < routers; i++) {
        for(j = 0; j < routers; j++) {
            routingtable[i].cost[j] = costmat[i][j];
            routingtable[i].from[j] = j;
        }
    }

    int othershortpathexists;
    do {
        othershortpathexists = 0;
        for(i = 0; i < routers; i++) {
            for(j = 0; j < routers; j++) {
                for(k = 0; k < routers; k++) {
                    if(routingtable[i].cost[j] > costmat[i][k] + routingtable[k].cost[j]) {
                        routingtable[i].cost[j] = costmat[i][k] + routingtable[k].cost[j];
                        routingtable[i].from[j] = k;
                        othershortpathexists = 1;
                    }
                }
            }
        }
    } while(othershortpathexists != 0);

    // Print routing table
    for(i = 0; i < routers; i++) {
        printf("Router %d\n", i + 1);
        for(j = 0; j < routers; j++) {
            printf("Cost to Router %d = %d, Next hop = Router %d\n", j + 1, routingtable[i].cost[j], routingtable[i].from[j] + 1);
        }
        printf("\n");
    }

    return 0;
}

