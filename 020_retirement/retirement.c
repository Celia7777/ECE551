#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

double balance_calculate(int age, double principal, retire_info status) {
  double current_balance = principal;
  for (int i = age; i < age + status.months; i++) {
    printf("Age %3d month %2d you have $%.2lf\n", i / 12, i % 12, current_balance);
    current_balance += current_balance * status.rate_of_return + status.contribution;
  }
  return current_balance;
}

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  double working_balance = balance_calculate(startAge, initial, working);
  balance_calculate(startAge + working.months, working_balance, retired);
}

int main(void) {
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;

  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;

  retirement(327, 21345, working, retired);

  return 0;
}
