#include<stdio.h>
#include<stdlib.h>
#include<string.h>
const int ALL=13;
struct salelist
{
    int volum;
    int month;
    float disc;
    float prc;
};
struct product
{
    int prono;
    char fullname[20];
    float price,sum;
    struct salelist sale[10];
}prdt[20],prdts[20]={0};
float rank[15][2];

void Q1_initialize();
void Q1_read();
void Q2_sort();
void Q2_print();
int Q3_month_to_num(char *m);
void Q3_read();
void Q3_print(int m,int i,int j);
void Q3_sort();
void Q4_calc_print();
void Q5_function();
void Q6_msort(int s,int t);
void Q6_calc();

int main()
{
    Q1_read();
    Q2_sort();
    Q2_print();
    Q3_read();
    Q3_sort();
    Q4_calc_print();
    Q5_function();
    Q6_calc();
    return 0;
}
/*
@function Q1_initialize
@This function is used to initialize the structer members.
*/
void Q1_initialize()
{
    for(int i=1;i<=20;i++)
    {
        prdt[i].prono=0;
        prdt[i].price=0;
        for(int k=0;k<20;k++)
            prdt[i].fullname[k]=0;
        for(int j=1;j<=10;j++)
        {
            prdt[i].sale[j].disc=0;
            prdt[i].sale[j].month=0;
            prdt[i].sale[j].volum=0;
            prdt[i].sale[j].prc=0;
        }
    }
}
/*
@function Q1_read()
@This function is used to read the statistics from the product.txt and restore them in the structure arry.
*/
void Q1_read()
{
    FILE *fp=fopen("product.txt","r");
    for(int i=1;i<=ALL;i++)
    {
        fscanf(fp,"%d",&prdt[i].prono); 
        prdts[i].prono=prdt[i].prono;
        fscanf(fp,"%s",&prdt[i].fullname); 
        for(int j=0;j<strlen(prdt[i].fullname);j++)
            prdts[i].fullname[j]=prdt[i].fullname[j];
        fscanf(fp,"%f",&prdt[i].price); 
        prdts[i].price=prdt[i].price;
    }
    fclose(fp);
}
/*
@function Q2_swap
@These functions are used to swap the numbers
*/
void Q2_swap_int(int *a, int *b)
{
    int c;
    c=*a;
    *a=*b;
    *b=c;
}
void Q2_swap_float(float *a, float *b)
{
    float c;
    c=*a;
    *a=*b;
    *b=c;
}
/*
@function Q2_sort
@This function is used to sort all the products by price from small to big,mainly use the selection sort algorithem
*/
void Q2_sort()
{
    for(int i=1;i<=ALL;i++)
        for(int j=i+1;j<=ALL;j++)
        {
            if(prdts[i].price>prdts[j].price) 
            {
                char str[20];
                strcpy(str,prdts[j].fullname);
                strcpy(prdts[j].fullname,prdts[i].fullname);
                strcpy(prdts[i].fullname,str);
                Q2_swap_int(&prdts[j].prono,&prdts[i].prono);
                Q2_swap_float(&prdts[j].price,&prdts[i].price);
            }
        }
}
/*
@function Q2_print
@This function is used to print the result processed by function Q2_sort
*/
void Q2_print()
{
    printf("This is the original product list which has been sorted by price\n");
    printf("Prono\tFullname\tPrice\t\n");
    for(int i=1;i<=ALL;i++)
    {
        printf("%d\t%s\t%.1f\n",prdts[i].prono,prdts[i].fullname,prdts[i].price);
    }
    printf("--------------------------------------------------------------------\n");
}
/*
@function Q3_read
This function is used to access the salelist.txt 
*/
void Q3_read()
{
    FILE *fp=fopen("salelist.txt","r");
    int prono=0,month=0,volum=0,pre=0,cnt=0;
    float disc=0;
    for(int i=1;i<=32;i++)
    {
        char s[30];
        fgets(s,sizeof(s),fp);
        prono=(s[0]-'0')*100+(s[1]-'0')*10+s[2]-'0';
        if(prono!=pre)
        {
            cnt=1;
            pre=prono;
        }
        else cnt++;
        if(s[4]=='A') month=8;
        if(s[4]=='S') month=9;
        if(s[4]=='O') month=10;
        if(s[4]=='N') month=11;
        if(s[4]=='D') month=12;
        volum=(s[9]-'0')*10+s[10]-'0';
        if(s[12]=='n')disc=0;
        else disc=(s[12]-'0')/10.0;
        prdt[prono-100].sale[cnt].month=month;
        prdt[prono-100].sale[cnt].volum=volum;
        prdt[prono-100].sale[cnt].disc=disc;
        prdt[prono-100].sale[cnt].prc=prdt[prono-100].price*(1-prdt[prono-100].sale[cnt].disc);
    }
}
/*
@function Q3_print
@This function is used to print the records by month
*/
void Q3_print(int m,int i,int j)
{
    printf("%d\t",prdt[i].prono);
    if(m==8)printf("Aug.\t");
    if(m==9)printf("Sep.\t");
    if(m==10)printf("Oct.\t");
    if(m==11)printf("Nov.\t");
    if(m==12)printf("Dec.\t");
    printf("%d\t",prdt[i].sale[j].volum);
    if(prdt[i].sale[j].disc==0) printf("none\n");
    else 
    {
        int d=(int)(prdt[i].sale[j].disc*100.0);
        printf("%d",d);
        printf("%% ");
        printf("off\n");
    }
}
/*
@function Q3_sort
@This function is used to sort the records by month
*/
void Q3_sort()
{
    printf("This is the sale list information sorted by month.\n");
    printf("Prono\tMonth\tVolum\tDiscount\t\n");
    for(int k=8;k<=12;k++)
        for(int i=1;i<=ALL;i++)
            for(int j=1;;j++)
            {
                if(prdt[i].sale[j].month==0)break;
                else if(prdt[i].sale[j].month==k)Q3_print(k,i,j);
            }
        
    printf("--------------------------------------------------------------------\n");
}
/*
@function Q4_calc_print
@This function is used to calculate the total sale volume of each product respectively
*/
void Q4_calc_print()
{
    printf("This is the total sale volum and average sale volume of each product.\n");
    printf("Prono\tVolum\tAverage\t\n");
    for(int i=1;i<=ALL;i++)
    {
        int sum=0,cnt=1;
        float avg=0.0;
        for(int j=1;prdt[i].sale[j].volum!=0;j++)
        {
            sum+=prdt[i].sale[j].volum;
            cnt=j;
        }
        avg=(sum*1.0)/(cnt*1.0);
        printf("%d\t%d\t%.2f\n",prdt[i].prono,sum,avg);

    }
    printf("--------------------------------------------------------------------\n");
}
/*
@function Q5_function
@This function is used to output all sales data of September with product information
*/
void Q5_function()
{
    FILE *fp=fopen("2279371.txt","w");
    fprintf(fp,"This is the sales data with product information on September.\n");
    fprintf(fp,"Prono\tFullname\tPrice\tVolum\t\n");
    for(int i=1;i<=ALL;i++)
        for(int j=1;prdt[i].sale[j].month!=0;j++)
        {
            if(prdt[i].sale[j].month==9)
            {
                fprintf(fp,"%d\t%s\t%.2f\t%d\t",prdt[i].prono,prdt[i].fullname,prdt[i].price,prdt[i].sale[j].volum);
                if(prdt[i].sale[j].disc==0)fprintf(fp,"none\n");
                else fprintf(fp,"%d%% off\n",(int)(prdt[i].sale[j].disc*100.0));
            }
        }
    fclose(fp);  
}
/*
@function Q6()
*/
void Q6_msort(int s,int t)
{
    if(s==t) return;
    int mid=(s+t)/2;
    Q6_msort(s,mid);
    Q6_msort(mid+1,t);
    int i=s,j=mid+1,k=s;
    while(i<=mid&&j<=t)
    {
        if(prdt[i].sum<=prdt[j].sum)
        {
            rank[k][1]=i+100;
            rank[k][2]=prdt[i].sum;
            k++;
            i++;
        }
        else
        {
            rank[k][1]=j+100;
            rank[k][2]=prdt[j].sum;
            k++;
            j++;
        }
    }
    while(i<=mid)
    {
        rank[k][1]=i+100;
        rank[k][2]=prdt[i].sum;
        k++;
        i++;
    }
    while(j<=t)
    {
        rank[k][1]=j+100;
        rank[k][2]=prdt[j].sum;
        k++;
        j++;
    }
}
void Q6_calc()
{
    float calc=0;
    for(int i=1;i<=ALL;i++)
    {
        for(int j=1;prdt[i].sale[j].month!=0;j++)
        {
            calc+=prdt[i].sale[j].prc*prdt[i].sale[j].volum;
        }
        prdt[i].sum+=calc;
    }
    Q6_msort(1,13);
    printf("This is the top three products ranked by total sales\n");
    printf("Prono\tFullname\tTotal Volum\t\n");
    for(int i=13;i>=11;i--)
    {
        int m=(int)rank[i][1];
        printf("%d\t%s\t%.2f\t\n",m,prdt[m-100].fullname,rank[i][2]);
    }
}
