#include<stdio.h> 
#include<stdlib.h>
#include<limits.h>

#define LOCKED 1
#define UNLOCKED 0

struct Node{
	int gain;
	int nodeid;
};

int matrix[100][100];
int partition[100],optimal_partition_set[100],node_status[100];
int curr_part[2];
int vertex, net, limit_max, limit_min;
char filename[128];
int optimal_partition;
int gain_till_now;
int move_id;

struct Node node[100];

int compare(const void * a, const void * b) {
    if( ((struct Node *)a)->gain == ((struct Node *)b)->gain )
        return ((struct Node *)a)->nodeid - ((struct Node *)b)->nodeid;
    return ((struct Node *)b)->gain - ((struct Node *)a)->gain;
}

int compare2(const void * a, const void * b) {
        return ((struct Node *)a)->nodeid - ((struct Node *)b)->nodeid;
}

void init(){
	for(int i=0;i<100;i++)
	for(int j=0;j<100;j++)
		matrix[i][j]=0;
	for(int i=0;i<100;i++)
	{	partition[i]=0;
		node[i].nodeid=i;
		node[i].gain=0;
        node_status[i]=UNLOCKED;
        optimal_partition_set[i]=-1;
	}
    curr_part[0]=curr_part[1]=0;
    optimal_partition=INT_MIN;
    gain_till_now=0;
}

int FS(int nodeid){
	int fs=0;
	int flag;
	for(int i=0;i<net;i++)
	{
	    if(matrix[i][nodeid] == 1)
	    {
			flag=1;
		    for(int j=0; j<vertex; j++)
				if(matrix[i][j]==1 && j!=nodeid)
					if(partition[j]==partition[nodeid])
			    		{flag=0;break;}
			fs+=flag;
		}	
	}	
	//printf("fs(%d)=%d\t",nodeid,fs);	
    return fs;
}

int TE(int nodeid){
	int te=0;
        int flag;
        for(int i=0;i<net;i++)
        {
           if(matrix[i][nodeid] == 1)
			{
				flag=1;
				for(int j=0; j<vertex; j++)
					if(matrix[i][j]==1 && j!=nodeid)
						if(partition[j]!=partition[nodeid])
							{flag=0;break;}
				te+=flag;
			}   
        }
		//printf("fs(%d)=%d\n",nodeid,te);
    return te;
}

int validSwap(int nodeid){
    if(node_status[nodeid]==LOCKED)
        return 0;

    if(curr_part[partition[nodeid]]==limit_min)
        return 0;

    return 1;    
}

void printCurrentPartition(){
    printf("P1 = {");
    for(int i=0;i<vertex;i++)
        if(partition[i]==0) printf("%c ",i+'a');
    printf("}\nP2 = {");
    for(int i=0;i<vertex;i++)
        if(partition[i]==1) printf("%c ",i+'a');
    printf("}\n\n"); 
}

void printOptimalPartition(){
    printf("\nOptimal Gain = %d",optimal_partition);
    printf("\nP1 = {");
    for(int i=0;i<vertex;i++)
        if(optimal_partition_set[i]==0) printf("%c ",i+'a');
    printf("}\nP2 = {");
    for(int i=0;i<vertex;i++)
        if(optimal_partition_set[i]==1) printf("%c ",i+'a');
    printf("}\n"); 
}

void moveNode(int nodeid){
    curr_part[partition[nodeid]]--;
    partition[nodeid] = 1-partition[nodeid];
    curr_part[partition[nodeid]]++;
    node_status[nodeid]=LOCKED;
}

void input_from_file(char file_name[]){
    int temp1,temp2;
    FILE* file = fopen (file_name, "r");
    fscanf (file, "%d", &vertex);
    fscanf (file, "%d", &net);
    for(int i=0;i<net;i++)
	{
        fscanf (file, "%d", &temp1);
        for(int j=0;j<temp1;j++)
        {
            fscanf (file, "%d", &temp2);
            matrix[i][temp2]=1;
        }
    }
    fscanf (file, "%d", &limit_min);
    fscanf (file, "%d", &limit_max);
    fclose (file);
}

void input_cli(){
    int temp1,temp2;		
	//read_file();

	printf("# of Nodes:\t");
	scanf("%d",&vertex);
	printf("# of Nets:\t");
	scanf("%d",&net);
	
	for(int i=0;i<net;i++)
	{
		printf("Net %d\t # of nodes :",i+1);
		scanf("%d",&temp1);
		for(int j=0;j<temp1;j++)
			{scanf("%d",&temp2);
				matrix[i][temp2]=1;
			}
	}

	printf("constraint (min,max) : ");
	scanf("%d %d", &limit_min,&limit_max);
}

void init_random_partition(){
    for(int i=0;i<vertex;i++)
		partition[i]=i%2;
    
    //partition[0]=partition[2]=partition[3]=partition[6]=0;
    //partition[1]=partition[4]=partition[5]=partition[7]=1;
    
    for(int i=0;i<vertex;i++)
	    if(partition[i]==0) curr_part[0]++;
        else    curr_part[1]++;
}

void display(){

    for(int i=0;i<vertex;i++)
    printf("%c\t",'a'+i);
    printf("\n");
    for(int i=0;i<net;i++)
	{
		for(int j=0;j<vertex;j++)
		printf("%d\t",matrix[i][j]);
		printf("\n");
	}
}

void calulate_gain_all(){
    for(int i=0;i<vertex;i++)
        node[i].gain=FS(i)-TE(i);
}

void calulate_gain(int t){
    
    /*
    printf("V=%c Neighbour=",'a'+t);
    for(int i=0;i<net;i++)
        for(int j=0;j<vertex;j++)
            if(matrix[i][t]==1 && matrix[i][j]==1 && j!=t)
                printf("%c ",'a'+j);
    
    printf("\n");
    */
    for(int i=0;i<net;i++)
    {
        if(matrix[i][t]==1)
            for(int j=0;j<vertex;j++)
                if(matrix[i][j]==1 && j!=t)
                    node[j].gain=FS(j)-TE(j);
    }      
}

void print_gain(){
    printf("Gain :\t");
    for(int i=0;i<vertex;i++)
		printf("%d\t",node[i].gain);
    printf("\n");    
    //for(int i=0;i<vertex;i++)
	//	printf("%d\t",node[i].nodeid);
    //printf("\n");
    printf("Node :\t");    
    for(int i=0;i<vertex;i++)
		printf("%c\t",'a'+node[i].nodeid);    
    printf("\n");    
    //for(int i=0;i<vertex;i++)
	//	printf("%d\t",partition[node[i].nodeid]);    
    //printf("\n");    
}

void printPartion(){
    for(int i=0;i<vertex;i++) 
        printf("%d ",partition[i]);
    printf("\n");
}

void update_optimal_partition()
{
    //rintf("gain till now %d\n",gain_till_now);
    if(gain_till_now > optimal_partition)
    {
        optimal_partition=gain_till_now; 
        for(int j=0;j<vertex;j++)
            optimal_partition_set[j]=partition[j];
    }
}

void moveToPartition(){
    for(int i=0;i<vertex;i++) 
    {
        move_id=node[i].nodeid;
        if(validSwap(move_id))
        {
            gain_till_now += node[i].gain;
            moveNode(move_id);
            printf("move '%c' from partition %d to partition %d\n",'a'+move_id,partition[move_id]+1,2-partition[move_id]);
            printf("gain = %d\n",node[i].gain);
            update_optimal_partition(); 
            break;
        }
    }

}

int main(int argc, char *argv[])
{
    init();
    
    if(argc>=2)
    input_from_file(argv[1]);
    else
    input_cli();
    init_random_partition();
    //display();

    printf("Initial Random Partition : \n");
    printCurrentPartition();

    calulate_gain_all();
    qsort(node, vertex, sizeof(struct Node), compare);
    print_gain();
    moveToPartition();
    
    //printf("-----------------\n");
    qsort(node, vertex, sizeof(struct Node), compare2);
    //print_gain();
    printCurrentPartition();

    for(int i=1;i<vertex;i++)
    {
        calulate_gain(move_id);
        qsort(node, vertex, sizeof(struct Node), compare);
        print_gain();
        moveToPartition();
        qsort(node, vertex, sizeof(struct Node), compare2);
        printCurrentPartition();
    }


    printOptimalPartition();
    return 0;
}
