//Node *makeNode( double x, double y, int level );
//void makeChildren( Node *parent );
//void writeTree( Node *head );
//void writeNode( FILE *fp, Node *node );
//void printOut( FILE *fp, Node *node );
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "treeStructure.h"
#include "buildTree.h"
#include "newfunction.h"
extern void writeTree();
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
