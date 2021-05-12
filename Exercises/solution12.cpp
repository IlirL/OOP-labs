
#include<iostream>
#include<cstring>
using namespace std;

//your code here


class InvestmentPlan{
    protected:

    char name[80];
    float sum;
    float shares;
    bool current_day;


    public:
    //constructors
    InvestmentPlan(char *name = "", float sum = 0, float shares = 0, bool current_day = 0)
    {
        this->sum = sum;
        this->shares = shares;
        this->current_day = current_day;
        strcpy(this->name, name);
    }

    //operator=
    InvestmentPlan& operator=(InvestmentPlan &i)
    {
         this->sum = i.sum;
        this->shares = i.shares;
        this->current_day = i.current_day;
        strcpy(this->name, i.name);
    }
    ~InvestmentPlan(){}

    float getSum(){
        return sum;
    }

    bool getCurrentDay()
    {
        return current_day;
    }

    float getShares()
    {
        return shares;
    }
};

class InvestmentFund{
    protected:
    char name[50];
    InvestmentPlan *plans;
    int n;
    float price_of_share;

    public:
    InvestmentFund(){
        this->plans = new InvestmentPlan[0];
        this->n = 0;
    }

    InvestmentFund(char *name, InvestmentPlan ip[], int n, float price_of_share )
    {
        strcpy(this->name, name);
        this->n = n;
        this->price_of_share = price_of_share;

        plans = new InvestmentPlan [n];

        for(int i = 0; i<n; i++)
        {
            plans[i] = ip[i];
        }

        // cout<<"price_of_share = "<<price_of_share<<endl;
    }
    ~InvestmentFund(){
        delete [] plans;
    }

    float total_sum_investments(){

        float sum = 0;

        for(int i = 0; i<n; i++)
        {
            sum += plans[i].getSum() * price_of_share;
        }

        return sum;

    }

    float value_of_new_plans(){
        float sum = 0;
        for(int i = 0; i<n; i++)
        {
            if(plans[i].getCurrentDay())
                sum+=plans[i].getSum();
        }
    }

    virtual float dailyProfit() = 0;
};

class MoneyFund : public InvestmentFund{
    private:
    const static float provision;
    public:
    MoneyFund(char *name, InvestmentPlan ip[], int n, float price_of_share ) : InvestmentFund(name, ip, n, price_of_share){
        // cout<<"provision in MoneyFund = "<<provision;
    }

    float dailyProfit() override{
        // cout<<"We are in DailyProfit for fund in MoneyFund: "<<name<<" "<<(total_sum_investments() * provision / 100) / 365<<endl;
        return (total_sum_investments() * provision / 100) / 365;
    }



};

const float MoneyFund::provision = 1;

class ActionFund : public InvestmentFund{
    private:
    const static float provision;
    const static float entry_provision;

    public:
     ActionFund(char *name, InvestmentPlan ip[], int n, float price_of_share ) : InvestmentFund(name, ip, n, price_of_share){
                // cout<<"provision in ActionFund = "<<provision;

    }


    float dailyProfit() override{
        //  cout<<"We are in DailyProfit for fund in ActionFund: "<<name<<" "<<(total_sum_investments() * provision / 100) / 365 + value_of_new_plans() * entry_provision / 100 <<endl;
        return (total_sum_investments() * provision / 100) / 365 + (value_of_new_plans() * entry_provision / 100) ;
    }

};

const float ActionFund::provision = 1.5;
const float ActionFund::entry_provision = 3;


double totalProfit(InvestmentFund** funds, int n){

    double total = 0;

    for(int i = 0; i<n; i++)
    {
        total +=funds[i]->dailyProfit();
    }

    return total;
}
int main(){

    char investitor[80], ime[50];
    double plan, brUdeli, udel;
    bool flag = false;
    int n, m;
    cin >> n;
    InvestmentFund **fondovi = new InvestmentFund*[n];

    for(int i = 0; i < n; i++){
        cin >> ime;
        cin >> m;
        InvestmentPlan *ip = new InvestmentPlan[m];

        for(int j = 0; j < m; j++){
            cin >> investitor >> plan >> brUdeli;
            if(j % 2) flag = true;
            else flag = false;
            InvestmentPlan IP(investitor, plan, brUdeli, flag);
            ip[j] = IP;
    //   cout<<"1";
        }
    //   cout<<"1";
        cin >> udel;
        if(i % 2){
            fondovi[i] = new ActionFund(ime, ip, m, udel);

        }
        else{
            fondovi[i] = new MoneyFund(ime, ip, m, udel);
        }
    }
    cout << totalProfit(fondovi, n);
    return 0;
}
