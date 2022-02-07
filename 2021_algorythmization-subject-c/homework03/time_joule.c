#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#endif /* __PROGTEST__ */

int is_leap(int yr) {

  // IMPORTANCE OF THE ORDER!
  if (yr % 4000 == 0)
    return 0; 
  else if (yr % 400 == 0) 
    return 1;
  else if (yr % 100 == 0)
    return 0;
  else if (yr % 4 == 0)
    return 1;
  else
    return 0;
}

int th_day(int leap, int m, int d) { // returns order of day in year (5th, 11th -> therefore thDay()) OR 0 if day is higher than max day in month
  int daysInMonths[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  daysInMonths[1] = leap ? 29 : 28;

  if (d > daysInMonths[m - 1])
    return 0;

  int daysTotal = d;
  for (int i = 1; i < m; i++) {
    daysTotal += daysInMonths[i - 1];
  }

  return daysTotal;
}

int is_interval_valid(int y1, int m1, int d1, int h1, int i1,
                  int y2, int m2, int d2, int h2, int i2) {
  if (y1 < 1600 || y2 < 1600 ||
      m1 < 1 || m1 > 12 || m2 < 1 || m2 > 12 ||
      th_day(is_leap(y1), m1, d1) == 0 ||
      th_day(is_leap(y2), m2, d2) == 0 ||
      h1 < 0 || h1 > 23 || h2 < 0 || h2 > 23 ||
      i1 < 0 || i1 > 59 || i2 < 0 || i2 > 59 ||
      d1 < 1 || d2 < 1)
        return 0;

  int start[5] = {y1, m1, d1, h1, i1};
  int end[5] = {y2, m2, d2, h2, i2};
  
  for (int i = 0; i < 5; i++) {
    if (start[i] > end[i])
      return 0;
    
    if (start[i] < end[i])
      return 1;
  }
  return 1; // if minutes same
}

int is_day_whole(int h, int i) {
  if (h == 0 && i == 0) 
      return 1;
  return 0;
}

int is_same_date(int y1, int m1, int d1, int y2, int m2, int d2) {
  if (y1 == y2 && m1 == m2 && d1 == d2)
    return 1;
  return 0;
}

int joules_in_interval(int h1, int i1, int h2, int i2) {
  const int increments_decimal[10] = {4, 5, 2, 3, 3, 1, 5, 4, 1, 2};
  const int increments_sextary[6] = {4, 5, 2, 3, 3, 3,};
  const int increments_trinary[3] = {4, 5, 3,};
  const int min_increment = 200;

  int hour_cnt = 0;

  int joules = 0;
  
  // h2 = (h2 == 0 && i2 == 0) ? 24 : h2;
  for (int h = h1; h < h2; ++h) {
    hour_cnt++;
    joules += increments_decimal[h % 10] + ((h+1) % 10 == 0 ? increments_trinary[(h / 10) % 6] : 0);
  }
  int total_minutes = (hour_cnt-1) * 60 + (60-i1) + i2;
  
  // i < last_minute ... inc[0] = transition 0->1
  for (int i = i1; i < i1 + total_minutes; ++i) {
    
    joules += min_increment + increments_decimal[i % 10] + ((i+1) % 10 == 0 ? increments_sextary[(i / 10) % 6] : 0);
    // ~= joules_per_second * 60 + joules_per_minute_digit0(0-9) + joules_per_minute_digit1(0-6)
        // (i+1) ... if we start on 10 we'd add 0->1 change
        // (i / 10) % 6 ... on 9th min add increment[0], on 19th add increment[1]
  }
    
  return joules;
  // POSSIBLE BUG IF I2 == 00:00 : h2 = (h2 == 0 && i2 == 0) ? 24 : h2; ... WHAT IF 00:01 - 00:05
}

int energyConsumption ( int y1, int m1, int d1, int h1, int i1,
                        int y2, int m2, int d2, int h2, int i2, long long int * consumption )
{
    if (!is_interval_valid(y1, m1, d1, h1, i1, y2, m2, d2, h2, i2))
      return 0;

  // joules per whole day
  long long daily = 86 + 200 * 24 + 24 * 60 * 200;

  // calc. whole days total + leap "days"
  long long total_days = 365LL * (y2 - y1 + 1); // later we'll subtract
  long long leaps = (y2 / 4 - y2 / 100 + y2 / 400 - y2 / 4000) - 
                ((y1 - 1) / 4 - (y1 - 1) / 100 + (y1 - 1) / 400 - (y1 - 1) / 4000);
  total_days += leaps;

  // subtract days from whole years
  long long minus_days_start = 0, minus_days_end = 0;
  minus_days_start = th_day(is_leap(y1), m1, d1);
  minus_days_end = (is_leap(y2) ? 366 : 365) - th_day(is_leap(y2), m2, d2) + 1;
  total_days -= (minus_days_end + minus_days_start);

  // ADD rest day joules
  long long rest_joules = joules_in_interval(h1, i1, 24, 0) + joules_in_interval(0, 0, h2, i2) + 3; // POSSIBLE BUG NOTE: + to00:00 -- will I2 ever be 00:00?
  

  *consumption = daily * total_days + rest_joules;
  // printf("%lld\n", *consumption);
  
  // TODO: write down whole alg. functionality, check it again + create limit asserts

  return 1;
}


#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  long long int consumption;

 assert ( energyConsumption ( 2021, 10,  1, 0, 0,
                               2021, 10,  1, 0, 0, &consumption ) == 1
           && consumption == 0LL );

assert ( energyConsumption ( 2021, 12,  31, 23, 59,
                    2022, 1,  1, 0, 0, &consumption ) == 1
&& consumption == 211LL );

  assert ( energyConsumption ( 2021, 10,  1, 13, 15,
                               2021, 10,  1, 18, 45, &consumption ) == 1
           && consumption == 67116LL );
  assert ( energyConsumption ( 2021, 10,  1, 13, 15,
                               2021, 10,  2, 11, 20, &consumption ) == 1
           && consumption == 269497LL );
  assert ( energyConsumption ( 2021,  1,  1, 13, 15,
                               2021, 10,  5, 11, 20, &consumption ) == 1
           && consumption == 81106033LL );
  assert ( energyConsumption ( 2024,  1,  1, 13, 15,
                               2024, 10,  5, 11, 20, &consumption ) == 1
           && consumption == 81398919LL );
  assert ( energyConsumption ( 1900,  1,  1, 13, 15,
                               1900, 10,  5, 11, 20, &consumption ) == 1
           && consumption == 81106033LL );
  assert ( energyConsumption ( 2021, 10,  1,  0,  0,
                               2021, 10,  1, 12,  0, &consumption ) == 1
           && consumption == 146443LL );
  assert ( energyConsumption ( 2021, 10,  1,  0, 15,
                               2021, 10,  1,  0, 25, &consumption ) == 1
           && consumption == 2035LL );
  assert ( energyConsumption ( 2021, 10,  1, 12,  0,
                               2021, 10,  1, 12,  0, &consumption ) == 1
           && consumption == 0LL );
  assert ( energyConsumption ( 2021, 10,  1, 12,  0,
                               2021, 10,  1, 12,  1, &consumption ) == 1
           && consumption == 204LL );
  assert ( energyConsumption ( 2021, 11,  1, 12,  0,
                               2021, 10,  1, 12,  0, &consumption ) == 0 );
  assert ( energyConsumption ( 2021, 10, 32, 12,  0,
                               2021, 11, 10, 12,  0, &consumption ) == 0 );
  assert ( energyConsumption ( 2100,  2, 29, 12,  0,
                               2100,  2, 29, 12,  0, &consumption ) == 0 );
  assert ( energyConsumption ( 2400,  2, 29, 12,  0,
                               2400,  2, 29, 12,  0, &consumption ) == 1
           && consumption == 0LL );


  return 0;
}
#endif /* __PROGTEST__ */
