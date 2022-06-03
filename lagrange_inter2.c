#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 16

const char path[] = "./lagrange_inter.txt";

struct Node
{
	float x_val;
	float y_val;
};

int main()
{
	int quan_node,i,k,j,fd;
	int len;
	printf("\nInput quan of node : ");
	scanf("%d",&quan_node);
	struct Node * p_nodearr = (struct Node*)
		malloc(sizeof(struct Node)*quan_node);
	for(i=0;i<quan_node;++i)
	{
		printf("\nInput Node[%d].x_val :",i);
		scanf("%f",&p_nodearr->x_val);
		printf("\nInput Node[%d].y_val :",i);
                scanf("%f",&p_nodearr++->y_val);
	}
	p_nodearr-=quan_node;
	fd = open(path,O_WRONLY|O_TRUNC);
        char buf[BUF_SIZE];
        for(i=0;i<quan_node;i++)
        {
                len = sprintf(buf,"%f",p_nodearr->x_val);
                write(fd,buf,len);
                write(fd," ",1);
                len = sprintf(buf,"%f",p_nodearr++->y_val);
                write(fd,buf,len);
                write(fd,"\n",1);
        }
	p_nodearr-=quan_node;	
	int quan_tdot;
	printf("\nInput quan of test dots : ");
	scanf("%d",&quan_tdot);

	float * p_tdotarr = (float *)malloc
		(sizeof(float)*quan_tdot);
	for(i=0;i<quan_tdot;++i)
	{
		printf("\nInput x[%d] test dot : ",i);
		scanf("%f",p_tdotarr++);
	}
	p_tdotarr-=quan_tdot;
	float res;
	float cur_val;
	for(i=0;i<quan_tdot;++i)
	{
		res = 0;
		for(k=0;k<quan_node;++k)
		{
			cur_val=1.0;
			for(j=0;j<quan_node;++j)
			{
				if(k==j)
					continue;
				cur_val*=(*p_tdotarr-
					p_nodearr[j].x_val)/
					(p_nodearr[k].x_val -
					 p_nodearr[j].x_val);
			}
			res+=cur_val*p_nodearr[k].y_val;
		}
		len = sprintf(buf,"%f",*p_tdotarr);
                write(fd,buf,len);
                write(fd," ",1);
                len = sprintf(buf,"%f",res);
                write(fd,buf,len);
                if(i!=quan_tdot-1)
                {

                        write(fd,"\n",1);
                }
		printf("\nf(%f) : %f",*p_tdotarr,res);
		p_tdotarr++;
	}
	free(p_nodearr);
	p_tdotarr-=quan_tdot;
	free(p_tdotarr);
	close(fd);
}



