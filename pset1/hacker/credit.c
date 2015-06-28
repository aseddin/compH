#include <stdio.h>
#include <cs50.h>

/*Check the validity and type of a credit card
 * use the following paypal recommended numbers to test the code:
 * https://www.paypalobjects.com/en_US/vhelp/paypalmanager_help/credit_card_numbers.htm
 * */


long long get_credit_num();
bool check_credit_validity(long long credit_number);
string determine_card_brand(long long credit_number);

int main(void)
{

    //get credit card number
    long long credit_card_number = get_credit_num();
    
    if (!check_credit_validity(credit_card_number))
        printf("INVALID\n");
    else //decide the credit card number
        printf("%s\n", determine_card_brand(credit_card_number));

    return 0;
}

/*get credit card number*/
long long get_credit_num(void)
{
    long long credit_number;

    //solicit a positive credit card number from the user
    do
    {
        printf("Enter credit card number: ");
        credit_number = GetLongLong();
    }
    while(credit_number <=0);

    return credit_number;
}

/*check the validity of a credit card number*/
bool check_credit_validity(long long credit_number)
{
    int accumulator = 0, first = 0, second = 0;

    while (credit_number > 0)
    {
        first = credit_number % 10;
        credit_number /= 10;
        second = (credit_number % 10) * 2;
        credit_number /= 10;

        accumulator += first;

        //if second is greater than 9, then sum its digits separately
        //second cannot exceed 9*2=18;
        if (second < 9)
            accumulator += second;
        else
            accumulator += second /10 + second %10;

    }

    //if the accumulator's value is modulo 10 the credit card number is valid
    if (accumulator % 10 == 0)
        return true;
    else
        return false;
}

//determine the credit card brand
string determine_card_brand(long long credit_number)
{
    //get the 2 most significant credit card digits
    while (credit_number > 99)
    {
        credit_number /= 10;
    }

    switch(credit_number)
    {
        case 34 ... 37:
            return "AMEX";
            break;
        case 51 ... 55: 
            return "MASTERCARD";
            break;
        case 40 ... 49:
            return "VISA";
            break;
        default:
            return "INVALID";

    }
}
