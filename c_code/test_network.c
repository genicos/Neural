#include "project.h"
#include "network/.h"
#include <stdio.h>

int main(){
  printf("FFUCKED\n");
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
  node *B = node_create(B_tensor, 0,0,0);
  node *D = node_create(D_tensor, 0,0,0);

  node *C = node_create(NULL, 0, 0, 1);
  node *E = node_create(NULL, 2, 2, 3);
  
  if(!A || !B || !C || !D || !E){
    printf("Failed to create nodes\n");
    return 1;
  }
  printf("Successfully created nodes\n");
  
  node *Z_nodes[5] = {A, B, C, D, E};

  network *W = network_create(5, Z_nodes);

  if(!W){
    printf("Failed to create network\n");
    return 1;
  }
  printf("Successfully created network\n");

  

  
  network_delete(W);
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
