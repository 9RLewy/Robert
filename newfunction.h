extern int j;
extern int k;
extern int maxLEVEL;
extern int m;
extern int n;
extern double nodeValue( Node*, double );
void removeChildren(Node*parent){
    int i;
    for (i=0;i<4;++i){
        free(parent->child[i]);
        parent->child[i]=NULL;
    }
    return;
}

void sets(Node*node){
    int j;
    node->flag=0;
    if(node->child[0] == NULL)
        node->flag=0;
    else{
        for(j=0;j<4;++j){
            sets(node->child[j]);
        }
    }
    return;
}
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
void adapt( Node *head ){
    do{ j=0;
        k=0;
        sets(head);
        complate(head);
        add(head);
    }
    while(j+k>0);
    return;

}
