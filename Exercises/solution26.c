#include<stdio.h>
    #include<string.h>
    #include<stdbool.h>


    typedef struct Transaction{
      char date_transaction[11];
      int amount;
      char currency[4];
    } T;

    int char_int(char c)
    {
        return (int)c-(int)'0';
    }

    bool print_transaction(T t)
    {
        // printf("%s %d %s\n", t.date_transaction, t.amount, t.currency);
        if(strcmp(t.currency, "USD") != 0)
            return false;
        if(t.amount>=5000)
            return false;

        // int year = 0;
        // year+=char_int(t.date_transaction[9]);
        // year += char_int(t.date_transaction[8]) * 10;
        // year += char_int(t.date_transaction[7]) * 100;
        // year+=char_int(t.date_transaction[6]) * 1000;

        int month = 0;
        month += char_int(t.date_transaction[4]);
        month+=char_int(t.date_transaction[3]) * 10;
        if(month>=1 && month<=3)
            return true;

        return false;

    }

    int main()
    {
        int n;
        scanf("%d", &n);
        int current_transaction = 1;
        int total = 0;
        for(int i = 0; i<n; i++)
        {
            char date[11];
            int amount;
            char currency[4];
            T t;
            scanf("%s %d %s",  &t.currency, &t.amount, &t.date_transaction);

            // strcpy(t.date_transaction, date);
            // strcpy(t.currency, currency);
            // t.amount = amount;
            // printf("%d\n", t.amount);
            // print_transaction(t);
            if(print_transaction(t))
            {
                total+=t.amount;
                printf("%d. %s %d %s\n", current_transaction++, t.date_transaction,t.amount, t.currency);
            }

        }
        printf("Total: %d USD", total);
    }
