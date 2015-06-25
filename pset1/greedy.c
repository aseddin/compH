#include <stdio.h>
#include <cs50.h>
#include <math.h>
 
/* Compute the optimal number of coins for a particular change*/

//define available coin values
#define QUARTER  25
#define DIME  10
#define NICKEL  5
#define PENNY  1

    
int get_change();
     
int main(void)
{   
    int change; // change in cents
    printf("O hai");
    change = get_change();

    int num_q, num_d, num_n, num_p;

    //compute number of quarters
    num_q= change / QUARTER;

    change -= num_q * QUARTER;

    //compute number of dimes
    num_d= change / DIME;

    change -= num_d* DIME;

    //computer number of nickels
    num_n = change / NICKEL;

    change -= num_n * NICKEL;

    //computer number of pennies
    num_p = change / PENNY;

    change -= num_p * PENNY;

    if(change != 0)
        printf("Error: change left is %d cents\n", change);
    else
        printf("%d\n", num_q + num_d + num_n + num_p);

    return 0;
}   

//get change from the user in the following format 9.45 for $9.45
//return the change in cents
int get_change(void)
{
    float change;

    //Keep asking for a positive money change
    do
    {
        printf("How much change is owed?\n");
        change = GetFloat();
    }
    while (change < 0);

    return (round(change * 100));
}
