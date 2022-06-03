#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUF_SIZE 16

const char path[] = "./linear_inter.txt";

struct Node
{
	float x_val;
	float y_val;
};

struct Line_coef
{
	float k_coef;
	float b_coef;
};

void piec_line(struct Node *,struct Line_coef *,int);
void linear_inter(struct Node *,
		struct Line_coef * ,float *,int,int);

int main()
{
	int node_quan,i;
	printf("\nInput quan of nodes : ");
	scanf("%d",&node_quan);
	struct Node * p_nodearr = (struct Node *)malloc
		(sizeof(struct Node)*node_quan);
	struct Line_coef * p_lcoef = (struct Line_coef *)
		malloc(sizeof(struct Line_coef*)*(node_quan-1));
	for(i=0;i<node_quan;++i)
	{
		printf("\nInput Node[%d].x_value : ",i);
		scanf("%f",&p_nodearr->x_val);
		printf("\nInput Node[%d].y_value : ",i);
                scanf("%f",&p_nodearr++->y_val);
	}
	p_nodearr-=node_quan;
	piec_line(p_nodearr,p_lcoef,node_quan);
	int quan_intrdot;
	printf("\nInput quantity of test dot : ");
	scanf("%d",&quan_intrdot);
	float * p_tdot = (float *)malloc(sizeof(float)*
			quan_intrdot);
	for(i=0;i<quan_intrdot;++i)
	{
		printf("\nInput x[%d] : ",i);
		scanf("%f",p_tdot++);
	}
	p_tdot-=quan_intrdot;
	int fd = open(path,O_TRUNC|O_WRONLY);
	char buf[BUF_SIZE];
	int len;
	for(i=0;i<node_quan;++i)
	{
		len = sprintf(buf,"%f",p_nodearr->x_val);
		write(fd,buf,len);
		write(fd," ",1);
		len = sprintf(buf,"%f",p_nodearr++->y_val);
                write(fd,buf,len);
                write(fd,"\n",1);
	}
	p_nodearr-=node_quan;
	linear_inter(p_nodearr,p_lcoef,p_tdot,
			quan_intrdot,fd);
	close(fd);
	free(p_tdot);
	free(p_lcoef);
	free(p_nodearr);



}

void 
piec_line(struct Node * p_nodearr,
		struct Line_coef * p_lcoef,int node_quan)
{
	int i;
	for(i=0;i<node_quan-1;++i)
	{
		p_lcoef->k_coef=
			((++p_nodearr)->y_val- (--p_nodearr)->y_val)/
			((++p_nodearr)->x_val - (--p_nodearr)->x_val);
		p_lcoef++->b_coef =
		       	p_nodearr->y_val - p_nodearr->x_val*
			(((++p_nodearr)->y_val- (--p_nodearr)->y_val)/
                        ((++p_nodearr)->x_val -
			 (--p_nodearr)->x_val));
	}
}

void 
linear_inter(struct Node * p_nodearr,
	struct Line_coef * p_lcoef,
       	float * p_tdot,int quan,int fd)
{
	int i,k;
	int counter=0;
	int len;
	char dig_buf[BUF_SIZE];
	p_nodearr++;
	for(i=0;i<quan;++i)
	{
		while(p_nodearr)
		{
			if(*p_tdot<=p_nodearr->x_val)
			{
				printf("\nf(%f) = %f",
				*p_tdot	,p_lcoef->k_coef*(*p_tdot)
			       	+p_lcoef->b_coef);
				len = sprintf(dig_buf,"%f",*p_tdot);
				write(fd,dig_buf,len);
                		write(fd," ",1);
				len = sprintf(dig_buf,"%f",
					p_lcoef->k_coef*(*p_tdot)
					       	+p_lcoef->b_coef);
                		write(fd,dig_buf,len);
               			if(i!=quan-1)
                        	write(fd,"\n",1);
				p_nodearr-=counter;
				p_lcoef-=counter;
				p_tdot++;
				counter=0;
				break;
			}
			else
			{
				p_lcoef++;
				p_nodearr++;
				counter++;
			}
		}
		if(counter!=(quan-1))
		
			continue;
		len = sprintf(dig_buf,"%f",*p_tdot);
		write(fd,dig_buf,len);
		write(fd," ",1);
		p_nodearr-=counter;
		--p_lcoef;
		printf("\nf(%f) = %f",
                                *p_tdot ,
			p_lcoef->k_coef*(*p_tdot)
		       	+p_lcoef->b_coef);
		len = sprintf(dig_buf,"%f",
				p_lcoef->k_coef*(*p_tdot)
			       	+p_lcoef->b_coef);
		write(fd,dig_buf,len);
		if(i!=quan-1)
			write(fd,"\n",1);
		p_lcoef-=counter;
		counter=0;
		p_tdot++;
	}
}


