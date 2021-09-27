#include "pandemic.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//use to check the population part is a pure number or not later
//start and end point to the start and end bits of population
void check_purenumber(char * start, char * end) {
  if (start == end) {
    fprintf(stderr, "The population format is wrong.");
    exit(EXIT_FAILURE);
  }
  while (start != end) {
    if (isdigit(*start) == 0) {
      fprintf(stderr, "The population is not a pure number.");
      exit(EXIT_FAILURE);
    }
    start++;
  }
}

country_t parseLine(char * line) {
  country_t ans;
  ans.name[0] = '\0';
  ans.population = 0;

  char * comma_ptr;    //a pointer to the comma
  char * newline_ptr;  //a pointer to the newline
  size_t length;       //size of line
  size_t name_length = 0;
  char *
      popul_valid_num_end;  //point to the first element which is not valid number, in population part
  uint64_t popul_num;

  //check if there is a line or not
  if (line == NULL) {
    fprintf(stderr, "There is no line array.");
    exit(EXIT_FAILURE);
  }

  comma_ptr = strchr(line, ',');
  newline_ptr = strchr(line, '\n');
  // check if there is a comma or not
  if (comma_ptr == NULL) {
    fprintf(stderr, "The input has no comma.");
    exit(EXIT_FAILURE);
  }
  //check if the population if a pure number or not
  check_purenumber(comma_ptr + 1, newline_ptr);

  //compute the length of the string of the country name
  length = strlen(line);
  for (size_t i = 0; i < length; i++) {
    if (line[i] != ',') {
      name_length++;
    }
    if (line[i] == ',') {
      break;
    }
  }

  //check the size of the country name string
  if (name_length > MAX_NAME_LEN) {
    fprintf(stderr, "There is no country name, or the name is too long");
    exit(EXIT_FAILURE);
  }

  //Extract the country name
  //and check if it contains other char except alphabet
  for (size_t j = 0; j < name_length; j++) {
    ans.name[j] = line[j];
  }
  ans.name[name_length] = '\0';

  //convert the string of population to 64 int
  //comma_ptr+1 point to the first element of population string
  //popul_valid_num_end point to the last element of valid population number part
  //base 10, decimal
  popul_num = strtoll((comma_ptr + 1), &popul_valid_num_end, 10);
  ans.population = popul_num;
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  double first_7d_sum = 0;  //initialize the sum of first 7 days

  //some testcases
  //check if there is data array or not
  if (data == NULL) {
    fprintf(stderr, "There is no data array.");
    exit(EXIT_FAILURE);
  }
  //check if there is result array or not
  if (avg == NULL) {
    fprintf(stderr, "There is no where to store the results.");
    exit(EXIT_FAILURE);
  }
  //check if there is enough 7 days
  if (n_days < 7) {
    fprintf(stderr, "The number of days is not enough.");
    exit(EXIT_FAILURE);
  }
  //compute the the seven-day running average
  else {
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
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  double cum_allpeople = 0;
  double per_people = 100000;
  double population = (double)pop;

  //some testcases
  //check if there is data array or not
  if (data == NULL) {
    fprintf(stderr, "There is no data array.");
    exit(EXIT_FAILURE);
  }
  //check if there is result array or not
  if (cum == NULL) {
    fprintf(stderr, "There is no where to store the results.");
    exit(EXIT_FAILURE);
  }
  //check if the population is zero or not
  if (pop == 0) {
    fprintf(stderr, "The population cannot be zero.");
    exit(EXIT_FAILURE);
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

  //testcases
  //check if there is data array or not
  if (data == NULL) {
    fprintf(stderr, "There is no data array.");
    exit(EXIT_FAILURE);
  }
  //check if there is country info or not
  if (countries == NULL) {
    fprintf(stderr, "There is no country info.");
    exit(EXIT_FAILURE);
  }
  //check if there are enough days
  if (n_days <= 0) {
    fprintf(stderr, "There is not enough days data.");
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
  printf("%s has the most daily cases with %u\n", country_name, number_cases);

  //check if there is a tie situation
  if (tie != 0) {
    printf("There is a tie between at least two countries\n");
  }
}
