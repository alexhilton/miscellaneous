/* final standing */
#include <stdio.h>
#include <stdlib.h>

typedef struct Team Team;
struct Team {
    int id;
    int score;
};

void merge(Team a[], int start, int end, int middle) {
    int size1 = middle - start + 1;
    Team *low = (Team *) calloc(size1, sizeof(Team));
    int size2 = end - middle;
    Team *high = (Team *) calloc(size2, sizeof(Team));
    int i, j, k;
    for (i = 0; i < size1; i++) {
        low[i] = a[start + i];
    }
    for (j = 0; j < size2; j++) {
        high[j] = a[middle + 1 + j];
    }
    // now low takes first half sorted, and high takes second half sorted
    i = 0;
    j = 0;
    k = 0;
    while (i < size1 && j < size2) {
        if (low[i].score < high[j].score) {
            a[start + k] = high[j];
            j++;
        } else {
            a[start + k] = low[i];
            i++;
        }
        k++;
    }
    while (i < size1) {
        a[start + k] = low[i];
        i++;
        k++;
    }
    while (j < size2) {
        a[start + k] = high[j];
        j++;
        k++;
    }
    free(low);
    free(high);
}

void merge_sort(Team a[], int start, int end) {
    if (start >= end) {
        return;
    }
    int middle = (start + end) / 2;
    merge_sort(a, start, middle);
    merge_sort(a, middle + 1, end);
    merge(a, start, end, middle);
}

int main() {
    int count;
    Team team[150000];
    scanf("%d", &count);
    int i;
    for (i = 0; i < count; i++) {
        scanf("%d%d", &team[i].id, &team[i].score);
    }
    merge_sort(team, 0, count - 1);
    for (i = 0; i < count; i++) {
        printf("%d %d\n", team[i].id, team[i].score);
    }

    return 0;
}
