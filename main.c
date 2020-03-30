#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 20
#define MAXITE 1000

void addEdge(int n, int mat[n][n]);
void printMatrix(int n , int mat[n][n]);
void deleteEdge(int n, int mat[n][n]);
void IspisParticije(int vbr,int v[vbr]);
int totalCost(int v1br, int v2br, int n, int v1[v1br], int v2[v2br], int mat[n][n]);
int exinCost(int a, int vbr, int n, int v[vbr], int mat[n][n]);
void diffCost(int v1br, int v2br, int n, int v1[v1br], int v2[v2br], int mat[n][n], int diff[n]);
int gain(int v1br, int v2br, int n, int v1[v1br], int v2[v2br], int mat[n][n], int diff[n]);
void swapPlaces(int v1br, int v2br, int v1[v1br], int v2[v2br], int pmax, int qmax);
void prepisi(int v1br, int v2br, int n, int g[n][n], int v1[n], int v2[n]);
void prepisiNiz(int v1br, int v2br, int n, int g[n][n], int v1[n], int v2[n]);
void KLalgorithm(int v1br, int v2br, int n, int v1[v1br], int v2[v2br], int mat[n][n], int diff[n], int g[n][n]);
int kway(int v1br, int v2br, int n, int v1[v1br], int v2[v2br], int mat[n][n], int diff[n], int g[n][n]);

void UcitajBrNode(FILE * , int *);
void UcitajVeze(FILE *, int n, int mat[n][n]);

int main()
{
    int j=0, i=0, n = 0;
    int v1[MAX], v2[MAX];
    int k = 0, stepen = 0;
    int v1br = 0, v2br = 0;
    int cost = 0, cost1 = 0;

    FILE *f;

    f=fopen("input1.txt", "r");
    UcitajBrNode(f,&n);
    printf("Unesite kway konstantu: ");
    scanf("%d", &k);

    stepen = pow(2,k);
    int podela[stepen][(n/stepen)+1];
    printf("%d \n", stepen);

    printf("n je %d \n", n);
    int diff[n]; //lista razlike
    int p[n][n];
    int g[n][n];

    for(i = 0; i < n; i++){
        diff[i] = 0;
    }

    if (n%2 == 0){  //Inicijalna podela
        for(i = 0; i < n/2; i++){
            v1[i] = i+1;
            v2[i] = n/2+i+1;
        }
        v1br = i;
        v2br = v1br;
    } else {
         for(i = 0; i < (n-1)/2; i++){
            v1[i] = i+1;
            v2[i] = (n-1)/2+i+1;
        }
        v1br = i;
        v2br = i+1;
        v2[i]= (n-1)/2+i+1;
    }

    IspisParticije(v1br, v1);
    IspisParticije(v2br, v2);
    int matrix[n][n];

    for(i=0; i<n; i++){
       for(j=0; j<n; j++){
           matrix[i][j] = 0;
       }
    }

    for(i=0; i<n; i++){
       for(j=0; j<n; j++){
           g[i][j] = 0;
       }
    }

    UcitajVeze(f, n, matrix);
    fclose(f);
    printMatrix(n , matrix);

   /* addEdge(n, matrix);
    printMatrix(n , matrix);*/
    deleteEdge(n, matrix);
    printMatrix(n , matrix);

    cost = totalCost(v1br, v2br, n, v1, v2, matrix);

    printf("Cena je %d \n", cost);

    diffCost(v1br, v2br, n, v1, v2, matrix, diff);
    IspisParticije(n, diff);

    while(cost1<cost){
        cost = totalCost(v1br, v2br, n, v1, v2, matrix);
        KLalgorithm(v1br, v2br, n, v1, v2, matrix, diff, g);
        //printMatrix(n , g);
        cost1 = totalCost(v1br, v2br, n, v1, v2, matrix);
    }
    printf("\n");
    IspisParticije(v1br, v1);
    IspisParticije(v2br, v2);
    printf("\n");
    printf("Cena je %d \n", cost);

    return 0;
}

void addEdge(int n , int mat[n][n]){
        int i=0,j=0;
        printf("Unesite cvorove izmedju kojih postoji veza:");
        while (1>0){
            scanf("%d",&i);
            if(i==0){
                break;
            }
            scanf("%d",&j);

            mat[i-1][j-1]=1;
            mat[j-1][i-1]=1;
             }
}
void printMatrix(int n , int mat[n][n]){
        int i=0, j=0;

        for(i=0; i<n; i++){
            for(j=0; j<n; j++){
                printf("%d ", mat[i][j]);
            }
            printf("\n");
        }
}

void deleteEdge(int n, int mat[n][n]){
        int i=0, j=0;

        printf("Unesite vezu koju zelite da obrisete:");
        while(1>0){
            scanf("%d", &i);
            if(i==0){
                break;
            }
            scanf("%d", &j);

            mat[i-1][j-1]=0;
            mat[j-1][i-1]=0;
        }
}

void IspisParticije(int vbr, int v[vbr]){
    int i = 0;
    for(i = 0; i < vbr; i++){
        printf("%d ", v[i]);
    }
    printf("\n");
}

int totalCost(int v1br, int v2br, int n, int v1[v1br], int v2[v2br], int mat[n][n]){
    int i = 0, j = 0, x = 0, y =0;
    int cost = 0, elementCost = 0;

    for(i = 0; i < v1br; i++){
        x = v1[i];
        elementCost = 0;
        for(j = 0; j < v2br; j++){
            y = v2[j];
            elementCost += mat[x-1][y-1];
        }
        cost += elementCost;
    }

    return cost;
}

int exinCost(int a, int vbr, int n, int v[vbr], int mat[n][n]){
    int i = 0, y = 0;
    int exinCost = 0;

    for(i = 0; i < vbr; i++){
        y = v[i];
        exinCost += mat[a-1][y-1];
    }

    return exinCost;
}

void diffCost(int v1br, int v2br, int n, int v1[v1br], int v2[v2br], int mat[n][n], int diff[n]){
    int i = 0, rbr = 0;
    int ex = 0, in = 0;
    int a = 0;

    for(i = 0; i < v1br; i++){
        a = v1[i];
        ex = exinCost(a, v2br, n, v2, mat);
        in = exinCost(a, v1br, n, v1, mat);
        rbr = v1[i];
        diff[rbr-1] = ex-in;
    }

    for(i = 0; i < v2br; i++){
        a = v2[i];
        ex = exinCost(a, v1br, n, v1, mat);
        in = exinCost(a, v2br, n, v2, mat);
        rbr = v2[i];
        diff[rbr-1] = ex-in;
    }
}

void swapPlaces(int v1br, int v2br, int v1[v1br], int v2[v2br], int pmax, int qmax){
    int i = 0, j = 0;
    int temp = 0, podtemp = 0;
    int p = 0, q = 0;

    for(i = 0; i < v1br; i++){
        if (pmax == v1[i]){
            p = i;
        }
    }

    for(i = 0; i < v2br; i++){
        if (qmax == v2[i]){
            q = i;
        }
    }

    if(p != v1br-1){
        temp = v1[p]; //Stavi ih na poslednje mesto
        v1[p] = v1[v1br - 1];
        v1[v1br - 1] = temp;
    }

    if(q != v2br-1){
        temp = v2[q];
        v2[q] = v2[v2br - 1];
        v2[v2br - 1] = temp;
    }

    temp = v1[v1br - 1];
    v1[v1br - 1] = v2[v2br - 1];
    v2[v2br - 1] = temp;
}


int gain(int v1br, int v2br, int n, int v1[v1br], int v2[v2br], int mat[n][n], int diff[n]){
    int i = 0, j = 0;
    int q = 0, p = 0, pmax = 0, qmax = 0;
    int g = 0;
    int max = 0;

    /*printf("Drugi ispis: \n");
    IspisParticije(v1br, v1);
    IspisParticije(v2br, v2);
    printf("\n");*/

    p = v1[0];
    q = v2[0];
    pmax = p;
    qmax = q;
    //printf("P i q su: %d %d razlika diff[p] = %d , a diff[q] = %d \n", p, q, diff[p-1], diff[q-1]);
    max = diff[p-1] + diff[q-1] - 2*mat[p-1][q-1];
    //printf("Pocetni max %d \n", max);

    for(i = 0; i < v1br; i++){
        for(j = 0; j < v2br; j++){
            p = v1[i];
            q = v2[j];
            g = diff[p-1] + diff[q-1] - 2*mat[p-1][q-1];
            //printf("Gains %d\n", g);
            if (g > max){
                max = g;
                pmax = p;
                qmax = q;
            }
        }
    }

    if (max < 0){
                    return -1;
                }
    //printf("Krajnji max %d , pmax %d , qmax %d, v1br %d , v2br %d\n", max, pmax, qmax, v1br, v2br);
    //printf("Diff[%d] = %d , Diff[%d] = %d , 2*c(%d, %d) = %d\n", pmax, diff[pmax-1], qmax, diff[qmax-1], pmax, qmax, 2*mat[pmax-1][qmax-1]);
    swapPlaces(v1br, v2br, v1, v2, pmax, qmax); // Smanjiti v1br i v2br u svakoj narednoj iteraciji

    return max;
}

void KLalgorithm(int v1br, int v2br, int n, int v1[v1br], int v2[v2br], int mat[n][n], int diff[n], int g[n][n]){
    int i = 0, a = 0, x = 0, y = 0;
    int cost = 0;
    int v1org = v1br, v2org = v2br;
    int max = 0;
    int maxUk = 0;
    int brojac = 0;
    diffCost(v1br, v2br, n, v1, v2, mat, diff);

    while((v1br != 0 && v2br != 0) && brojac != n){
        max = gain(v1br, v2br, n, v1, v2, mat, diff);
        if (max == -1){
            v1br = v1org+1;
            v2br = v2org+1;
            brojac++;
        }
        //printf("Max je: %d \n", max);
        if (maxUk < maxUk+max){
            prepisi(v1org, v2org, n, g, v1, v2);
            maxUk += max;
            cost = totalCost(v1org, v2org, n, v1, v2, mat);
            //printf("MaxUk je: %d , Total cost je %d \n", maxUk, cost);
        }

        diffCost(v1org, v2org, n, v1, v2, mat, diff);

        /*for(i = 0; i < v1org; i++){
            a = v1[i];
            x = v2[v2br-1];
            y = v1[v1br-1];
            diff[a-1] = diff[a-1] - 2*mat[a-1][x-1] + 2*mat[a-1][y-1];
        }

        for(i = 0; i < v2org; i++){
            a = v2[i];
            x = v1[v1br-1];
            y = v2[v2br-1];
            diff[a-1] = diff[a-1] - 2*mat[a-1][x-1] + 2*mat[a-1][y-1];
        }*/

       /* for(i = 0; i < n; i++){
            printf("%d ", diff[i]);
        }*/
        v1br -= 1;
        v2br -= 1;
    }

    /*printf("Treci ispis: \n");
    IspisParticije(v1br, v1);
    IspisParticije(v2br, v2);
    printf("\n");*/

    prepisiNiz(v1org, v2org, n, g, v1, v2);
    cost = totalCost(v1org, v2org, n, v1, v2, mat);

    //printf("Posle algoritma cena je: %d", cost);
}

void UcitajBrNode(FILE *f, int * x){
    fscanf(f,"%d", x);
}

void UcitajVeze(FILE * f, int n, int mat[n][n]){
    int p=0,q=0;
    char s;
    while(fscanf(f, "%d ", &p)!=EOF && fscanf(f, "%d", &q)!=EOF){
         mat[p-1][q-1]=1;
         mat[q-1][p-1]=1;
    }
}

void prepisi(int v1br, int v2br, int n, int g[n][n], int v1[n], int v2[n]){
    int i = 0, j = 0;

    for(i = 0; i < v1br; i++){
        g[0][i] = v1[i];
    }

    for(i = 0; i < v2br; i++){
        g[1][i] = v2[i];
    }
}

void prepisiNiz(int v1br, int v2br, int n, int g[n][n], int v1[n], int v2[n]){
    int i = 0, j = 0;

    for(i = 0; i < v1br; i++){
        v1[i] = g[0][i];
    }

    for(i = 0; i < v2br; i++){
        v2[i] = g[1][i];
    }

}

/*int kway(int v1br, int v2br, int n, int v1[v1br], int v2[v2br], int mat[n][n], int diff[n], int g[n][n]){


    kway();
}*/
