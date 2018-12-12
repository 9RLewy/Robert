
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

// tree data structure

struct qnode {
  int level;
  double xy[2];
  struct qnode *child[4];
  int flag;
};
typedef struct qnode Node;

// function definitions

Node *makeNode( double x, double y, int level );
void makeChildren( Node *parent );
void writeTree( Node *head );
void writeNode( FILE *fp, Node *node );
void printOut( FILE *fp, Node *node );


void growTree(Node *node);
void destoryTree(Node*node);
void removeChildren(Node*parent);
double nodeValue( Node *node, double time );
double value( double x, double y, double time );
void set(Node*node);
void complate(Node*head);
void add(Node*head);
void adapt( Node *head );
void plus(Node*node);
// main
int j=0;
int k=0;
int maxLEVEL=6;
int m=0;
int n=0;
int main( int argc, char **argv ) {

  Node *head;
  // make the head node
  head = makeNode( 0.0,0.0, 0 );
  head->flag=0;
  // make a tree
  makeChildren( head );
  growTree(head);
  growTree(head);

  adapt( head );
  printf("The number of nodes added is: \n");
  printf("%d\n",m);
  printf("The number of deleted nodes is: \n");
  printf("%d\n",n);

  // print the tree for Gnuplot
  writeTree( head );


  return 0;
}

// make a node at given location (x,y) and level

Node *makeNode( double x, double y, int level ) {

  int i;

  Node *node = (Node *)malloc(sizeof(Node));

  node->level = level;

  node->xy[0] = x;
  node->xy[1] = y;

  for( i=0;i<4;++i )
    node->child[i] = NULL;

  return node;
}
void adapt( Node *head ){
    do{ j=0;
        k=0;
        set(head);
        complate(head);
        add(head);
    }
    while(j+k>0);


}

void add(Node*node){
int i;
if(node->child[0]==NULL){
    if(node->flag==1&&node->level<maxLEVEL){
        makeChildren(node);
        j=j+4;
        m=m+4;}
}
else{
    if(node->child[0]->flag==-1&&node->child[1]->flag==-1&&node->child[2]->flag==-1&&node->child[3]->flag==-1){
        removeChildren(node);
        k=k+4;
        n=n+4;}
    else{
        for(i=0;i<4;++i){
        add(node->child[i]);
    }
    }

return;
}
}

void complate(Node*node){
int i;
double t;
if(node->child[0]==NULL){
   t=nodeValue( node, 0.0 );
   if (t>0.5){
    node->flag=1;
   }
   else if(t<-0.5){
    node->flag=-1;
   }
}
else{
    for(i=0;i<4;++i){
        complate(node->child[i]);
    }

}
return;
}
// split a leaf nodes into 4 children

void makeChildren( Node *parent ) {

  double x = parent->xy[0];
  double y = parent->xy[1];

  int level = parent->level;

  double hChild = pow(2.0,-(level+1));

  parent->child[0] = makeNode( x,y, level+1 );
  parent->child[1] = makeNode( x+hChild,y, level+1 );
  parent->child[2] = makeNode( x+hChild,y+hChild, level+1 );
  parent->child[3] = makeNode( x,y+hChild, level+1 );

  return;
}

// write out the tree to file 'quad.out'

void writeTree( Node *head ) {

  FILE *fp = fopen("quad.out","w");

  writeNode(fp,head);

  fclose(fp);

  return;
}

// recursively visit the leaf nodes

void writeNode( FILE *fp, Node *node ) {
  int i;
  if( node->child[0] == NULL )
    printOut( fp, node );
  else {
    for ( i=0; i<4; ++i ) {
      writeNode( fp, node->child[i] );
    }
  }
  return;
}
//grow tree
void growTree(Node *node){
  int i;
  if( node->child[0] == NULL )
    makeChildren(node);
  else {
    for ( i=0; i<4; ++i ) {
      growTree(node->child[i]);
    }

  }
  return;
}



void set(Node*node){
    int i;
    int j;
    node->flag=0;
    if(node->child[0] == NULL)
        node->flag=0;
    else{
        for(j=0;j<4;++j){
            set(node->child[j]);
        }
    }
    return;
}


void destoryTree(Node*node){
int i;
if(node->child[0]==NULL)
{
 free(node);
}
else{
    for ( i=0; i<4; ++i ) {
      destoryTree(node->child[i]);
      node->child[i]=NULL;
    }
    free(node);
    node=NULL;
}
return;
}
void removeChildren(Node*parent){
    int i;
    for (i=0;i<4;++i){
        free(parent->child[i]);
        parent->child[i]=NULL;
    }
    return;
}

double nodeValue( Node *node, double time ) {

  int level = node->level;
  double x = node->xy[0];
  double y = node->xy[1];

  double h = pow(2.0,-level);

  return( value( x+0.5*h, y+0.5*h, time ) );
}

// Data function

double value( double x, double y, double time ) {

  return( 2.0*exp(-8.0*(x-time)*(x-time)) - 1.0 ) ;
}
// write out the (x,y) corners of the node

void printOut( FILE *fp, Node *node ) {
  double x = node->xy[0];
  double y = node->xy[1];
  int level = node->level;
  double h = pow(2.0,-level);

  fprintf(fp, " %g %g\n",x,y);
  fprintf(fp, " %g %g\n",x+h,y);
  fprintf(fp, " %g %g\n",x+h,y+h);
  fprintf(fp, " %g %g\n",x,y+h);
  fprintf(fp, " %g %g\n\n",x,y);

  return;
}

