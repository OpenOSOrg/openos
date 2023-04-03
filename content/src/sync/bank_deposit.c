#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define money_t double
#define MAX_ACCOUNTS 1000

struct deposit_s {
    int account_num;
    money_t amount;
};

money_t accounts[MAX_ACCOUNTS];

/* This function is intended so simulate the work of retrieving the current balance
 * for a given account number. It just spins and yields a random number of times.
 */
static money_t get_balance(int account_num)
{
    long dummy = 0;
    int nyield = rand() % 10;
    int nspin = rand() % 1000;


    for (int i = 0; i < nyield; i++) {
        sched_yield();
        for (int j = 0; j < nspin; j++) {
            dummy += rand();
        }
    }

    return accounts[account_num];
}

/* This function is intended so simulate the work of saving the current balance
 * back to a given account number. It just spins and yields a random number of times.
 */
static void put_balance(int account_num, money_t balance)
{
    long dummy = 0;
    int nyield = rand() % 10;
    int nspin = rand() % 1000;


    for (int i = 0; i < nyield; i++) {
        sched_yield();
        for (int j = 0; j < nspin; j++) {
            dummy += rand();
        }
    }

    accounts[account_num] = balance;
    return;
}

/* Start of deposit function */
static void deposit(int account, money_t amount)
{
    money_t balance = get_balance(account);
    balance += amount;
    put_balance(account, balance);

    return;        
}
/* End of deposit function */

static void *deposit_thread(void *arg)
{
    struct deposit_s *my_deposit = (struct deposit_s *)arg;
    deposit(my_deposit->account_num, my_deposit->amount);

    return (void *)0;
}

int main(int argc, char **argv)
{
    pthread_t tid1, tid2;
    int account_num = 100;
    money_t amt1 = 50.00;
    money_t amt2 = 100.00; 

    struct deposit_s dep1 = {account_num, amt1};
    struct deposit_s dep2 = {account_num, amt2}; 

    /* Normally we'd want to test the return value of pthread_create. */

    (void)pthread_create(&tid1, NULL, deposit_thread, (void *)&dep1 );
    (void)pthread_create(&tid2, NULL, deposit_thread, (void *)&dep2 );

    /* Wait for child threads to finish */
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("Final balance of account #%d after depositing $%.2lf and $%.2lf is $%.2lf\n",
           account_num, amt1, amt2, accounts[account_num] );
    return 0;
}