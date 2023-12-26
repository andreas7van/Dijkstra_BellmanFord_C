#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#define INFINITY 9999
#define MAX 10
 

void dijkstra(int myarr[MAX][MAX],int n,int startnode);
int Bellman_Ford(int myarr[MAX][MAX] ,int a, int V, int E, int edge[20][2]);



int main(){
	
	
	int V,edge[20][2],myarr[MAX][MAX],i,j,k=0;
	int n,u,a;

	printf("Enter the number of vertices:");
	scanf("%d",&n);


//Validation check for vertices
	while(n!=6){
	printf("Number of vertices should be 6...Please try again\n");
	printf("Enter no. of vertices:");
	scanf("%d",&n);
	}
	V=n;//save the variable in V for bellman-ford
	
	//We take the adjacency matrix from file
	
	printf("\nTake  the adjacency matrix from file:\n");

 	
    FILE *file = fopen("costs.txt", "r");

 for(i=0; i<V; i++)
    {
        for(j=0; j<V; j++)
        {
            fscanf(file, "%d" , &myarr[i][j]);
             if(myarr[i][j]!=0)
                edge[k][0]=i,edge[k++][1]=j;
        }
        fscanf(file,"\n");
    }

    fclose(file);

    for(i=0; i<V; i++)
    {
        for(j=0; j<V; j++)
        {
            printf("%d ",myarr[i][j]);
        }
        printf("\n");
    }
	
	
	
	printf("\nEnter the starting node:");
	scanf("%d",&u);
	//validation check for starting node
	while(u<1 || u>6){
	printf("\nPlease try again");	
	printf("\nEnter the starting node:");
	scanf("%d",&u);
}
	
	a=u;//save the variable for bellman-ford function
	u--;//decrease the source for dijsktra algorithm
	
	
	int choice1;
	
	//Menu
	printf("0.Dijkstra Algorithm\n");
	printf("1.Bellman Ford Algorithm\n");
	printf("2.Dijkstra Algorithm and Bellman Ford Algorithm\n");
	printf("What is your choice 0,1 or 2:");
	scanf("%d",&choice1);
	
	//Validation check for choices
	while (choice1!=0 && choice1!=1 && choice1!=2 ){
				
		printf("Select a number between 0,1 and 2:\n");
		printf("0.Dijkstra Algorithm\n");
		printf("1.Bellman Ford Algorithm\n");
		printf("2.Dijkstra Algorithm and Bellman Ford Algorithm\n");
		scanf("%d",&choice1);
	}
	//Clear the screen
	system("cls");
	
	//if choice is 0 programm will execute only dijkstra algorithm
	if (choice1==0){
	printf("You select Dijsktra Algorithm\n");
	dijkstra(myarr,n,u);
	printf("\nPress any button to close the programm");
	getch();
}

	//if choice is 1 programm will execute only bellman-ford algorithm 
 	else if(choice1==1){
		
		printf("You select Bellmand Ford Algorithm\n");
		if(Bellman_Ford(myarr,a,V,k,edge))
        printf("\nNo negative weight cycle\n");
    	else 
		printf("\nNegative weight cycle exists\n");
    	
    	printf("\nPress any button to close the programm");
		getch();
		}
		
		
		//if choice is 2 programm will execute both of two algorithms
	else{
		
		printf("You select both of two Algorithms\n");
		//We run both of two algorithms and we start from dijsktra
		printf("Print first the Dijsktra Algorithm\n");
		dijkstra(myarr,n,u);
		printf("--------------------------------------------------\n");
		printf("Press any button to continue\n");
		getch();
	
		printf("Print at last Bellman-Ford Algorithm\n");
		//check if there are a negative cost in matrix
		if(Bellman_Ford(myarr,a,V,k,edge))
    	printf("\nNo negative weight cycle\n");
    	else 
		printf("\nNegative weight cycle exists\n");
    	
		printf("\nPress any button to close the programm\n");
		getch();		
}

}




//Bellman-Ford Algorithm
int Bellman_Ford(int myarr[MAX][MAX], int a, int V, int E, int edge[20][2]){

	int nexthop[99];
    int i,j,u,v,k,distance[20],parent[20],S,flag=1;
    for(i=0;i<V;i++)
        distance[i] = 1000 , parent[i] = -1 ;
        S=a;
  	    distance[S-1]=0 ;
    for(i=0;i<V-1;i++)
    {
        for(k=0;k<E;k++)
        {
            u = edge[k][0] , v = edge[k][1] ;
            if(distance[u]+myarr[u][v] < distance[v])
                distance[v] = distance[u] + myarr[u][v] , parent[v]=u ;
        }
    }
    for(k=0;k<E;k++)
        {
            u = edge[k][0] , v = edge[k][1] ;
            if(distance[u]+myarr[u][v] < distance[v])
                flag = 0 ;
        }
        
         for(i=0;i<V;i++){
    	if (parent[i]==-1)
    	parent[i]=0;
	}

//find shortest paths (paths for dijkstra and bellman-ford are the same) 
printf("\nPrint the shortest paths and distance for Bellman-Ford Algorithm\n");
for(i=0;i<V;i++)
if(i!=S-1)
{
printf("\nDistance of node%d=%d",i+1,distance[i]);
printf("\nPath=%d",i+1);
j=i;
do
{
	if (parent[i]==-1)
    parent[i]=0;
    
j=parent[j];
printf("<-%d",j+1);
}while(j!=S-1);
}
else if (i==S-1){
	printf("\nDistance of node%d=%d",i+1,distance[i]);
	printf("\nPath=%d",i+1);
	printf("<-%d",i+1);
}
        
        
    //initialize nexthop
	for(i=0;i<V;i++){
	nexthop[i]=0;
	}


	//find nexthop
	for(i=0;i<V;i++)
	if(i!=S-1)
	{
	j=i;
	do
	{
	if (parent[i]==-1)
	parent[i]=0;
	j=parent[j];
	if(j==S-1){
	break;
	}
	nexthop[i]=j+1;
	}while(j!=S-1);
	}



	
			for(i=0;i<V;i++){
				
   			 	if (i==S-1){
   			 		nexthop[i]=S;
					}
   			 	else if(nexthop[i]==0){
   			 		nexthop[i]=i+1;
					}		
					
				}
    
        //print the routing table 
        if(flag)
        	printf("\n\n-----------------Bellman-Ford Algorithm-----------------\n");
			printf("\n\t\tRouting Table(%d)",S);
			printf("\nDestination Node\tNext-Hop\tCost\n");
   			 for(i=0;i<V;i++)
   			 {
   		
        printf("%d\t\t\t%d\t\t%d\n", i+1 , nexthop[i] ,distance[i]);
  				  }		
        return flag;
}



//Dijkstra Algorithm
void dijkstra(int myarr[MAX][MAX],int n,int startnode)
{
int nexthop[99];
int cost[MAX][MAX],distance[MAX],pred[MAX];
int visited[MAX],count,mindistance,nextnode,i,j;
//pred[] stores the predecessor of each node
//count gives the number of nodes seen so far
//create the cost matrix
for(i=0;i<n;i++)
for(j=0;j<n;j++)
if(myarr[i][j]==0)
cost[i][j]=INFINITY;
else
cost[i][j]=myarr[i][j];
//initialize pred[],distance[] and visited[]
for(i=0;i<n;i++)
{
distance[i]=cost[startnode][i];
pred[i]=startnode;
visited[i]=0;
}
distance[startnode]=0;
visited[startnode]=1;
count=1;
while(count<n-1)
{
mindistance=INFINITY;
//nextnode gives the node at minimum distance
for(i=0;i<n;i++)
if(distance[i]<mindistance&&!visited[i])
{
mindistance=distance[i];
nextnode=i;
}
//check if a better path exists through nextnode
visited[nextnode]=1;
for(i=0;i<n;i++)
if(!visited[i])
if(mindistance+cost[nextnode][i]<distance[i])
{
distance[i]=mindistance+cost[nextnode][i];
pred[i]=nextnode;
}
count++;
}
//print the path and distance of each node
printf("\nPrint the shortest paths and distance for Dijkstra Algorithm\n");
for(i=0;i<n;i++)
if(i!=startnode)
{
printf("\nDistance of node%d=%d",i+1,distance[i]);
printf("\nPath=%d",i+1);
j=i;
do
{
j=pred[j];
printf("<-%d",j+1);
}while(j!=startnode);
}
else if (i==startnode){
	printf("\nDistance of node%d=%d",i+1,distance[i]);
	printf("\nPath=%d",i+1);
	printf("<-%d",i+1);
}


//we do again this process to find nexthop
for(i=0;i<n;i++)
for(j=0;j<n;j++)
if(myarr[i][j]==0)
cost[i][j]=INFINITY;
else
cost[i][j]=myarr[i][j];
//initialize pred[],distance[] and visited[]
for(i=0;i<n;i++)
{
nexthop[i]=0;
distance[i]=cost[startnode][i];
pred[i]=startnode;
visited[i]=0;
}
distance[startnode]=0;
visited[startnode]=1;
count=1;
while(count<n-1)
{
mindistance=INFINITY;
//nextnode gives the node at minimum distance
for(i=0;i<n;i++)
if(distance[i]<mindistance&&!visited[i])
{
mindistance=distance[i];
nextnode=i;
}
//check if a better path exists through nextnode
visited[nextnode]=1;
for(i=0;i<n;i++)
if(!visited[i])
if(mindistance+cost[nextnode][i]<distance[i])
{
distance[i]=mindistance+cost[nextnode][i];
pred[i]=nextnode;
}
count++;
}
for(i=0;i<n;i++)
if(i!=startnode)
{
j=i;
do
{
j=pred[j];
if(j==startnode)
	break;
else
nexthop[i]=j+1;
}while(j!=startnode);
}






//find the next hop
  for(i=0;i<n;i++){
    
    	if(i==startnode){
    		nexthop[i]=startnode+1;
		}
        else if (nexthop[i]==0)
        nexthop[i]=i+1;
        
    
}
//print the routing table//
	printf("\n\n------------Dijsktra Algorithm---------------\n");
	printf("\n\t\tRouting Table(%d)",++startnode);
	printf("\nDestination Node\tNext-Hop\tCost\n");
    for(i=0;i<n;i++)
    {
        printf("%d\t\t\t%d\t\t%d\n", i+1 , nexthop[i] ,distance[i]);
    }
}




