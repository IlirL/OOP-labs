
#include<stdio.h>
#include<stdbool.h>


struct Prod{
    char name[100];
    float price;
    int amount;
};


int main(){
    int n;
    scanf("%d", &n);
    struct Prod products[n];
    float total = 0;
    for(int i = 0; i<n; i++){
    scanf("%s %f %d", products[i].name, &products[i].price, &products[i].amount);

    float result =  products[i].price * products[i].amount;
    printf("%d. %s\t%.2f x %d = %.2f \n", i+1, products[i].name, products[i].price, products[i].amount, result);
    total+=result;
    }
    printf("Total: %.2f", total);

}
