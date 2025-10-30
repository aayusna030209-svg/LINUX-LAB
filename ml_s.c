#include <stdio.h>

struct Process {
    int id, at, bt, ct, tat, wt, remaining;
    int type; 
};

int main() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter AT, BT and Type (0=system, 1=user) for P%d: ", i + 1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].type);
        p[i].remaining = p[i].bt;
    }

    printf("Enter Time Quantum for User processes: ");
    scanf("%d", &tq);

    int time = 0, done = 0;

    printf("\n--- Multilevel Scheduling Execution ---\n");

    while (done < n) {
        int idx = -1;

        int minAT = 1e9;
        for (int i = 0; i < n; i++) {
            if (p[i].remaining > 0 && p[i].type == 0 && p[i].at <= time) {
                if (p[i].at < minAT) {
                    minAT = p[i].at;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            printf("Time %d: System Process P%d is running (BT=%d)\n", time, p[idx].id, p[idx].remaining);
            time += p[idx].remaining;
            p[idx].remaining = 0;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            done++;
            continue;
        }

        // Else: user processes (Round Robin)
        int executed = 0;
        for (int i = 0; i < n; i++) {
            if (p[i].remaining > 0 && p[i].type == 1 && p[i].at <= time) {
                int runTime = (p[i].remaining > tq) ? tq : p[i].remaining;
                printf("Time %d: User Process P%d is running for %d units\n", time, p[i].id, runTime);

                time += runTime;
                p[i].remaining -= runTime;

                if (p[i].remaining == 0) {
                    p[i].ct = time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    done++;
                }
                executed = 1;
            }
        }

        if (!executed) {
            time++;  // CPU idle if nothing is ready
        }
    }

    printf("\n--- Final Process Table ---\n");
    printf("PID\tType\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%s\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, (p[i].type==0 ? "system" : "user"),
               p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    return 0;
}
