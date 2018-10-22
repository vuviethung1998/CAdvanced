#include "3way.h"
#include <sys/time.h>
int main()
{
	struct timeval start, stop;

	double elapsed;
	int *a1 , *a2;
	int i;
	srand(time(0));
	a1= createArray(SMALL_NUMBER);
	a2 = dumpArray(a1, SMALL_NUMBER);

	gettimeofday(&start, NULL);
	sort3way(a2, 0, SMALL_NUMBER -1);//sort
	gettimeofday(&stop, NULL);
	elapsed = (double)(stop.tv_usec -start.tv_usec)/1000000 +(double)(stop.tv_usec -start.tv_usec);
	printf("sort3way: %f\n" , elapsed);	
	
	gettimeofday(&start, NULL);
	sort2way(a2, 0, SMALL_NUMBER -1);//sort
	gettimeofday(&stop, NULL);
	elapsed = (double)(stop.tv_usec -start.tv_usec)/1000000 +(double)(stop.tv_usec -start.tv_usec);
	printf("sort2way: %f\n" , elapsed);	
	return 0;
}