#include "project.h"
#include "network/.h"
#include "network/pderivative.h"
#include <stdio.h>

int main(){
  printf("Creating the following network Z, consisting of nodes A B C D E\n\n");
  
  printf("    E\n");
  printf("   / \\\n");
  printf("  C   D\n");
  printf(" / \\\n");
  printf("A   B\n\n");
  
  FORM_ELEMENT shared_form[2] = {2,2};
  
  tensor *A_tensor = tensor_create(shared_form, 2);
  tensor *B_tensor = tensor_create(shared_form, 2);
  tensor *D_tensor = tensor_create(shared_form, 2);
  
  if(!A_tensor || !B_tensor || !D_tensor){
    printf("Failed to create tensors\n");
    return 1;
  }
  
  ELEMENT shared_data[4] = {2,3,4,5};

  A_tensor->data = shared_data;
  B_tensor->data = shared_data;
  D_tensor->data = shared_data;

  printf("Creating nodes A B D\n");
  
  node *A = node_create(A_tensor, 0,0,0);
  node *B = node_create(B_tensor, 0,1,0);
  node *D = node_create(D_tensor, 0,3,0);

  node *C = node_create(NULL, 0, 0, 1);
  node *E = node_create(NULL, 2, 2, 3);
 

  if(!A || !B || !C || !D || !E){
    printf("Failed to create nodes\n");
    return 1;
  }
  printf("Successfully created nodes\n");
  
  node *Z_nodes[5] = {A, B, C, D, E};

  network *Z = network_create(5, Z_nodes);

  if(!Z){
    printf("Failed to create network\n");
    return 1;
  }
  printf("Successfully created network Z\n\n");

  printf("Applying node_solve to node E in Z\n\n");

  if(!node_solve(Z, 4)){
    printf("Failed to solve node E in Z\n");
  }
  printf("Successfully solved node E in Z\n\n");

  for(int i = 0; i < Z->nodes_length; i++){
    printf("Node %c in Z:\n", 'A' + i);
    tensor_print(Z->nodes[i]->t, "f");
  }
  
  printf("\nClearing dependent nodes\n\n");
  network_clean(Z);
   
  for(int i = 0; i < Z->nodes_length; i++){
    printf("Node %c in Z:\n", 'A' + i);
    tensor_print(Z->nodes[i]->t, "f");
  }
  
  printf("\n\nTesting Partial Derivative\n\n");
  
  printf("Test 1/2 pderivative_tree\n");
  printf("Creating the following network:\n\n");
  
  printf("Y------N1--X \n");    
  printf("|      |     \n");
  printf("N2     N3--X \n");
  printf("|      |     \n");
  printf("N7--X  N4--N6\n");
  printf("|      |     \n");
  printf("X      N5    \n");
  
  node *Y  = node_create(NULL, 0, 2, 1);
  node *N1 = node_create(NULL, 0, 3, 8); 
  node *N2 = node_create(NULL, 0, 7, 2); 
  node *N3 = node_create(NULL, 0, 4, 8); 
  node *N4 = node_create(NULL, 0, 5, 6); 
  node *N5 = node_create(NULL, 0, 5, 5); 
  node *N6 = node_create(NULL, 0, 6, 6); 
  node *N7 = node_create(NULL, 0, 8, 8); 
  node *X  = node_create(NULL, 0, 8, 8);
  
  printf("Nodes created \n");
  
  node *P_nodes[9] = {Y,N1,N2,N3,N4,N5,N6,N7,X};
  
  network *P = network_create(9, P_nodes);
  
  if(P){
    printf("P made successfully\n");
  }
  
  pderivative_tree *T = partial_derivative(P,0, 8, 0, 0);
  
  if(!T){
    printf("Failed to create T");
    return 1;
  }
  
  printf("lineage_count: %d\n", T->lineage_count);
  
  for(NODES_LENGTH i = 0; i < T->lineage_count; i++){
    printf("\n\nlineage %d\n", i);
    NODES_LENGTH j = 0;
    do{
      printf("%u\n", T->lineages[i][j]);
      j++;
    }while(T->lineages[i][j] != 0);
  }
  
  delete_pdtree(T);
  network_delete(P);
  node_delete(Y);
  node_delete(N1);
  node_delete(N2);
  node_delete(N3);
  node_delete(N4);
  node_delete(N5);
  node_delete(N6);
  node_delete(N7);
  node_delete(X);
  network_delete(Z);
  node_delete(E);
  node_delete(D);
  node_delete(C);
  node_delete(B);
  node_delete(A);
  tensor_delete(D_tensor);
  tensor_delete(B_tensor);
  tensor_delete(A_tensor);
  return 0;
}
