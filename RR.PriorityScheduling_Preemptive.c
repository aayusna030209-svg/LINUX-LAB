#include <stdio.h>
struct Process {
int id, at, bt, rt, prio, ct, tat, wt, done;
};
int main() {
int n, time = 0, completed = 0; 
printf("Enter number of processes: "); 
scanf("%d", &n);
struct Process p[n];
for (int i = 0; i < n; i++) {
p[i].id = i + 1;
printf("Enter AT, BT, Priority of P%d: ", p[i].id);
 scanf("%d %d %d", &p[i].at, &p[i].bt,
&p[i].prio);
p[i].rt = p[i].bt;
p[i].done = 0; }
while (completed < n) {
int idx = -1, minPrio = 999; for (int i = 0; i < n; i++) {
if (!p[i].done && p[i].at <= time && p[i].prio < minPrio && p[i].rt > 0) {
minPrio = p[i].prio;
idx = i;
 }
}
if (idx != -1) {
p[idx].rt--;
 time++;
if (p[idx].rt == 0) {
p[idx].ct = time;
 p[idx].done = 1; 
 completed++;
}
} else {
time++; }
}
float totalTAT = 0, totalWT = 0;
 printf("\nP\tAT\tBT\tPrio\tCT\tTAT\tWT\n");
  for (int i = 0; i < n; i++) {
p[i].tat = p[i].ct - p[i].at;
p[i].wt = p[i].tat - p[i].bt;
totalTAT += p[i].tat;
totalWT += p[i].wt;
 printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
p[i].id, p[i].at, p[i].bt, p[i].prio, p[i].ct, p[i].tat, p[i].wt); }
printf("\nAvg TAT = %.2f, Avg WT = %.2f\n", totalTAT / n, totalWT / n);
return 0; 
}