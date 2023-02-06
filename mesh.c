/* Efficient Parallel Numerical Integration Program on a 2-D mesh */
#include <stdlib.h>
#include <math.h>
#define numproc 40
#define numpoints 30
float a, b, w, globalsum, answer;
int i;
spinlock L;
float f(float t)
{
	return( sqrt(4 - t*t) ); 
}
void Integrate(int myindex)
{
	float localsum = 0;
	float t;
	int j;
	t = a + myindex*(b-a)/numproc;
	for (j = 1; j <= numpoints; j++) {
		localsum = localsum + f(t);
		t = t + w;
		}
		localsum = w * localsum;
		Lock(L);
		globalsum = globalsum+localsum;
		Unlock(L);
}
		main( )
		{
			a=0;
			b=2;
			w = (b-a)/(numproc*numpoints);
			forall i = 0 to numproc-1 do 
			Integrate(i);
			answer = globalsum + w/2*(f(b)-f(a));
			cout << answer << endl;
		}