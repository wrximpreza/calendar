#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 Массив названия месяцов и количество дней в каждом месяце
*/
char *matrix[12][2] = {
		{"January", 31},
		{"February", 28},
		{"March", 31},
		{"April", 30},
		{"May", 31},
		{"June", 30},
		{"July", 31},
		{"August", 31},
		{"September", 30},
		{"October", 31},
		{"November", 30},
		{"December", 31}
	};


/*
	Функция календаря
*/
int main(int argc, char *argv[]) {
	
	int inputMonth = 1, inputYear = 0, daysOfFebruary = 0, startWeekDays = 0, days = 0, daysBefore = 0, whatShow = 0;

	printf("===========================================\n");
	printf("\nEnter year: ");
	scanf("%d", &inputYear);

	if( inputYear <= 0 ){
		
		printf("\nYear can not be less then zero: )))");
		return 0;
		
	}
	
	printf("\nShow (month - 0, all year - 1): ");
	scanf("%d", &whatShow);

	if( whatShow < 0 || whatShow > 1 ){

		printf("\nYou need enter only 0 or 1, try again");
		return 0;

	}
	
	/*
		Получаем количество дней в Феврале по заданому году
	*/
	daysOfFebruary = getNumberDaysOfFebruary(inputYear);
	
	/*
		Получаем  номера дня первой недели года
	*/
	startWeekDays = getNumberOfFirstDayOfYear(inputYear);
	matrix[1][1] = daysOfFebruary;
	

	if(whatShow == 0){
		
		printf("\nEnter number of month: ");
		scanf("%d", &inputMonth);
		
		if( inputMonth <= 0 || inputMonth > 12 ){

			printf("\nYou do not khow hove many month in the year: )))");

		}else{

			/*
				Ищем количество дней в предыдущем месяце
			*/
			days = matrix[inputMonth-1][1];

	  		if( inputMonth == 1 )
	  			daysBefore = days;
			else
				daysBefore = matrix[inputMonth-2][1];

			printf("\n===========================================\n");
			printf("<%s>            <%d>", matrix[inputMonth-1][0], inputYear, days);

			/*
				Выводим календарь на мпесяц в консоли
			*/
			drawMonthCalendar(days, startWeekDays, daysBefore, inputMonth-1);

			printf("\n===========================================\n");

		}
		
	}else{
		
		int month = 0;
		for( month; month <= 11; month++ ){
			
			printf("\n===========================================\n");
			printf("<%s>            <%d>", matrix[month][0], inputYear);

			/*
				Ищем количество дней в предыдущем месяце
			*/
			if( inputMonth == 1 )
	  			daysBefore = matrix[month-1][1];
			else
				daysBefore = matrix[month-2][1];

			/*
				Выводим календарь по заданому году в консоли
			*/
			drawMonthCalendar(matrix[month][1], startWeekDays, daysBefore, month);

		}
		
	}
	
	printf("\n===========================================");
	
	return 0;
	
}

/*
	Функция нахождения количества дней в Феврале
	int: year  текущий год
*/
int getNumberDaysOfFebruary(int year){
	
  if ( year % 400 == 0 || year % 100 == 0 || year % 4 == 0 )
   return 29;
  else
    return 28;
    
}

/*
	Функция нахождения номера дня первой недели
	int: year  текущий год
*/
int getNumberOfFirstDayOfYear(int year)
{

	return ( year + ( ( year - 1 ) / 4 ) - ( ( year - 1 ) / 100 ) + ( ( year - 1 ) / 400 ) ) % 7;

}

/*
	Фунцкия отрисовки  каледнаря на месяц
	int: days  дней в месяце
	int: startWeekDays номер дня недели с какого начинаеься месяц
	int: daysBeforeMonth количество дней в предыдущем месяце
	int: defaultMonth номер месяца
*/
int drawMonthCalendar(int days, int startWeekDays, int daysBeforeMonth, int defaultMonth){

		int k = 0, startDay = getStartDayByMonth(daysBeforeMonth, startWeekDays, defaultMonth), i = 1, numberOfWeek = getNumberWeekByMonth(startDay, defaultMonth);
		if( defaultMonth  == 0 )
			startDay = startWeekDays;

    	printf("\n___ ___ ___ ___ ___ ___ ___ ___\n");
		printf("NUM|Sun|Mon|Tue|Wed|Thu|Fri|Sat|\n");
		printf("___ ___ ___ ___ ___ ___ ___ ___\n");
		printf("%3d|", numberOfWeek);
		
  		for ( k = 1; k <= startDay; k++ )
			  printf("   |");

		for( i;  i <= days; i++ ){
			
			printf("%3d|", i);

			if ( ( i + startDay ) % 7 <= 0 ){
				
				printf("\n___ ___ ___ ___ ___ ___ ___ ___\n");
				if( days != i )
					printf("%3d|", ++numberOfWeek);
					
			}
			
		}
		
		printf("\n___ ___ ___ ___ ___ ___ ___\n");
		
}

/*
	Функция поиска номера дня недели для заданого месяца
	int: dayOfMonth
	int: startWeekDays номер дня недели
	int: defaultMonth номер месяца
*/
int getStartDayByMonth(int dayOfMonth, int startWeekDays, int defaultMonth){

	int day = startWeekDays, month = 0;

	for ( month; month <= 11; month++ ) {
		
		if( month == defaultMonth )
			return day;

		day = ( day + (int)matrix[month][1] ) % 7;

	}

	return day;
}

/*
	Фунцкия нахождения номера недели для месяца
	int: startWeekDays номер дня недели
	int: defaultMonth номер месяца
*/
int getNumberWeekByMonth(int startWeekDays, int defaultMonth){

	int days = 1, day=0, month = 0, numberWeek = 1;

	for ( month; month <= 11; month++ ) {
		
		if( month == defaultMonth )
			break;
			
		days += (int)matrix[month][1];
		
	}
	
	numberWeek = ceil( ( days - startWeekDays + 1 + 10 ) / 7 );
	return numberWeek;
	
}
