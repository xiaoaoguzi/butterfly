
#include <stdio.h>
#include <stdlib.h>

int temp_focus = 331330;

#define  MAX(x, y)   ((x) > (y) ?  (x) : (y))

unsigned char  is_focus_valid(long focus);

int main(void)
{
	int ret;

	ret = is_focus_valid(59879);
	printf("ret: %d\n", ret);

	return 0;

}


// 331330  59879
unsigned char  is_focus_valid(long int focus)
{
	long  temp;
	if(temp_focus){
		temp = MAX(temp_focus * 0.20,80000);
		if(focus > temp_focus){
			if(temp < abs(focus - temp_focus))
			{
				printf("temp:%ld temp_focus: %d focus:%ld\n", temp, temp_focus,focus);

				temp_focus = focus;
				return 1;
			}
			else{
				printf("temp:%ld temp_focus: %d focus:%ld\n", temp, temp_focus,focus);
				temp_focus = focus;
				return 0;
			}
		}
	}
	temp_focus = focus;
	return 0;
}
