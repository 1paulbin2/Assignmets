#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    char pid[20];
    int at, bt, pr;
    int rt;   
    int ct;   
    int tat;  
    int wt;   
    int index; 
} Process;

int main() {
    int n;
    Process p[MAX];

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%s %d %d %d", p[i].pid, &p[i].at, &p[i].bt, &p[i].pr);
        p[i].rt = p[i].bt;
        p[i].ct = p[i].tat = p[i].wt = 0;
        p[i].index = i;
    }

    int completed = 0, time = 0;


    int minAT = p[0].at;
    for (int i = 1; i < n; i++) {
        if (p[i].at < minAT) minAT = p[i].at;
    }
    time = minAT;

    while (completed < n) {
        int idx = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0) {
                if (idx == -1 ||
                    p[i].pr < p[idx].pr ||
                    (p[i].pr == p[idx].pr && p[i].at < p[idx].at) ||
                    (p[i].pr == p[idx].pr && p[i].at == p[idx].at && p[i].index < p[idx].index)) {
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        p[idx].rt--;
        time++;

        if (p[idx].rt == 0) {
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            completed++;
        }
    }

    double totalWT = 0, totalTAT = 0;

    printf("Waiting Time:\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", p[i].pid, p[i].wt);
        totalWT += p[i].wt;
    }

    printf("Turnaround Time:\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", p[i].pid, p[i].tat);
        totalTAT += p[i].tat;
    }

    printf("Average Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}
