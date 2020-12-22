#include "../../project.h"
#include "../../network/network.h"
#include "../../network/pderivative.h"
#include <stdio.h>

int main(){
  printf("Creating the following network Z, consisting of nodes A B C D E\n\n");
  
  printf("    E\n");
  printf("   / \\\n");
  printf("  C   D\n");
  printf(" / \\\n");
  printf("A   B\n\n");
  
  FORM_ELEMENT shared_form[2] = {2,2};
  
  tensor *A_tensor = tensor_create(2,shared_form);
  tensor *B_tensor = tensor_create(2,shared_form);
  tensor *D_tensor = tensor_create(2,shared_form);
  
  if(!A_tensor || !B_tensor || !D_tensor){
    printf("Failed to create tensors\n");
    return 1;
  }
  
  ELEMENT shared_data[4] = {3,4,5,6};

  A_tensor->data = shared_data;
  B_tensor->data = shared_data;
  D_tensor->data = shared_data;

  printf("Creating nodes A B D\n");
  
  node *A = node_create(A_tensor, 0,  0,0);
  node *B = node_create(B_tensor, 0,  1,0);
  node *D = node_create(D_tensor, 0,  3,0);

  node *C = node_create(NULL, 0,  0,1);
  node *E = node_create(NULL, 2,  2,3);
 

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
  
  printf("\nTesting partial derivatives, by calculating partial derivatives of E with respect to A,B,D \n\n"); 
  
  NODES_LENGTH params[3] = {0,1,3};
  Z->error = 4;
  node_solve(Z,Z->error);
  
  propogate_error(Z, 3, params);
  for(int i = 0; i < 3; i++){
    printf("Node %d\n", params[i]);
    tensor_print(Z->derivatives[params[i]] , "f");
  }
   
    
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
