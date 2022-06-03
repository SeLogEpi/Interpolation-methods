#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 16

char const path[] = "./newton_inter.txt";
		
struct Node
{
	float y_val;
	float x_val;
};
float
newton_interpolation(struct Node *,int ,float);
float separ_diff(struct Node *,int,int);//separate difference
float recurs_multiplic(struct Node *,int,float);
int main()
{
	int i,nod_quan,dot_quan,fd,len;
	printf("\nInput quan of nodes : ");
	scanf("%d",&nod_quan);
	printf("\nInput quan test dots : ");
	scanf("%d",&dot_quan);
	struct Node * p_arr = (struct Node*)malloc
		(sizeof(struct Node)*nod_quan);
	float * p_valarr = (float *)malloc(sizeof(float)*dot_quan);
	for(i=0;i<nod_quan;++i)
	{
		printf("\nInput Node[%d].x_value : ",i);
		scanf("%f",&p_arr->x_val);
		printf("\nInput Node[%d].f(x)_value : ",i);
		scanf("%f",&p_arr++->y_val);
	}
	p_arr-=nod_quan;
	char buf[BUF_SIZE];
	fd = open(path,O_WRONLY|O_TRUNC);
	for(i=0;i<nod_quan;++i)
	{
		len = sprintf(buf,"%f",p_arr->x_val);
		write(fd,buf,len);
		write(fd," ",1);
		len = sprintf(buf,"%f",p_arr++->y_val);
		write(fd,buf,len);
		write(fd,"\n",1);
	}
	p_arr-=nod_quan;
	for(i=0;i<dot_quan;++i)
	{
		printf("\nInput test x coord : ");
		scanf("%f",p_valarr++);
	}
	
	p_valarr-=dot_quan;
	float cur_val;
	for(i=0;i<dot_quan;++i)
	{
		cur_val = p_arr[0].y_val+
                                newton_interpolation(p_arr,
						nod_quan-1,p_valarr[i]);

		printf("\nf(%f) : %f",p_valarr[i],cur_val);
		len = sprintf(buf,"%f",p_valarr[i]);
                write(fd,buf,len);
                write(fd," ",1);
                len = sprintf(buf,"%f",cur_val);
                write(fd,buf,len);
		if(i<dot_quan-1)
			
                	write(fd,"\n",1);
	}
	free(p_arr);
	free(p_valarr);
	close(fd);

}



//p_fval means pointer function values, 
//pcval pointer  coord values
float separ_diff(struct Node * p_arr,int lwrbrd,int uprbrd)
{
	if(uprbrd-lwrbrd==1)
	{
		return (p_arr[uprbrd].y_val-p_arr[lwrbrd].y_val)/
			(p_arr[uprbrd].x_val-p_arr[lwrbrd].x_val);
	}
	else
	{
		return (separ_diff(p_arr,lwrbrd+1,uprbrd)-
			separ_diff(p_arr,lwrbrd,uprbrd-1))/
			(p_arr[uprbrd].x_val - p_arr[lwrbrd].x_val);
	}
}

float recurs_multiplic(struct Node *p_arr,int uprbrd,float intr_val)
{
	if(!uprbrd)
	{
		return (intr_val-p_arr[uprbrd].x_val);
	}
	else
	{
		return ((intr_val-p_arr[uprbrd].x_val)*
			recurs_multiplic(p_arr,uprbrd-1,intr_val));
	}
}

float 
newton_interpolation(struct Node * p_arr,
		int uprbrd,float intr_val)//upprbrd = count-1
{
	if(!uprbrd)
	{
		return (intr_val-p_arr[uprbrd].x_val)*
			separ_diff(p_arr,0,uprbrd+1);
	}
	else
	{
		return recurs_multiplic(p_arr,uprbrd,intr_val)*
			separ_diff(p_arr,0,uprbrd+1) +
			newton_interpolation(p_arr,uprbrd-1,intr_val);
	}
}

