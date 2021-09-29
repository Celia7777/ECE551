#include "pandemic.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//compute the length of first part before comma in any string in this format:"   ,   "
size_t compute_firstlen(char * array, size_t size) {
  size_t first_length = 0;
  for (size_t i = 0; i < size; i++) {
    if (array[i] != ',') {
      first_length++;
    }
    if (array[i] == ',') {
      break;
    }
  }
  return first_length;
}

country_t parseLine(char * line) {
  country_t ans;
  ans.name[0] = '\0';
  ans.population = 0;
  char * comma_ptr;    //a pointer to the comma
  char * popul_ptr;    //a pointer to the first of population
  size_t line_length;  //size of line
  size_t name_length;  //size of the country name in line
  char *
      popul_valid_num_end;  //point to the first element which is not valid number, in population part

  uint64_t popul_num;

  //check if there is a line array or not
  if (line == NULL) {
    fprintf(stderr, "There is no line array.");
    exit(EXIT_FAILURE);
  }

  comma_ptr = strchr(line, ',');
  popul_ptr = comma_ptr + 1;
  // check if there is a comma or not
  if (comma_ptr == NULL) {
    fprintf(stderr, "The input has no comma.");
    exit(EXIT_FAILURE);
  }

  line_length = strlen(line);
  name_length = compute_firstlen(line, line_length);
  //check the size of the country name string
  if (name_length > MAX_NAME_LEN) {
    fprintf(stderr, "The length of name is too long");
    exit(EXIT_FAILURE);
  }

  //Extract the country name
  for (size_t j = 0; j < name_length; j++) {
    ans.name[j] = line[j];
  }
  ans.name[name_length] = '\0';

  //convert the string of population to 64 int, base 10
  //and check if the population is valid or not, popul_valid_num_end pointing the same
  //thing as popul_ptr means popul_ptr points to nonvalid number
  popul_num = strtoll(popul_ptr, &popul_valid_num_end, 10);
  if (popul_valid_num_end == popul_ptr) {
    fprintf(stderr, "The first part of population is not an number.");
    exit(EXIT_FAILURE);
  }
  ans.population = popul_num;
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  double first_7d_sum = 0;

  //Some Testcases//
  //check if there is data array or not
  if (data == NULL) {
    return;
  }
  //check if there is result array or not
  if (avg == NULL) {
    return;
  }
  //check if there is enough 7 days
  if (n_days < 7) {
    return;
  }

  //compute the the seven-day running average
  for (size_t i = 0; i < 7; i++) {
    first_7d_sum += data[i];
  }
  double current_sum = first_7d_sum;
  avg[0] = first_7d_sum / 7;
  for (size_t j = 7; j < n_days; j++) {
    current_sum = current_sum - data[j - 7] + data[j];
    avg[j - 6] = current_sum / 7;
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  double cum_allpeople = 0;
  double per_people = 100000;
  double population = (double)pop;

  //Some Testcases//
  //check if there is data array or not
  if (data == NULL) {
    return;
  }
  //check if there is result array or not
  if (cum == NULL) {
    return;
  }

  //compute the cumulative number of cases that day per 100,000 people
  for (size_t i = 0; i < n_days; i++) {
    cum_allpeople += data[i];
    cum[i] = (cum_allpeople * per_people) / population;
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  unsigned number_cases = 0;
  unsigned max_index = 0;
  unsigned tie = 0;  //to check if there is a tie
  char * country_name;

  //Some Testcases//
  //check if there is data array or not
  if (data == NULL) {
    return;
  }
  //check if there is country info or not
  if (countries == NULL) {
    return;
  }
  //check if there are enough days
  if (n_days == 0) {
    return;
  }

  //find the maximum case data
  for (size_t i = 0; i < n_countries; i++) {
    for (size_t j = 0; j < n_days; j++) {
      if (data[i][j] == number_cases) {
        tie++;
      }
      if (data[i][j] > number_cases) {
        number_cases = data[i][j];
        max_index = i;
        tie = 0;
      }
    }
  }
  country_name = countries[max_index].name;

  //check if there is a tie situation
  if (tie == 0) {
    printf("%s has the most daily cases with %u\n", country_name, number_cases);
  }
  else {
    printf("There is a tie between at least two countries\n");
  }
}
