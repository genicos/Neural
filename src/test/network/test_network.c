#include "../../project.h"
#include "../../network/network.h"
#include "../../network/pderivative.h"
#include <stdio.h>

int main(){

  printf("\nTesting network\n");
  printf("NOTE: some tests require tensors, those are marked as TENSOR DEPENDENT\n");
  printf("  To test tensors, run test_tensor\n");
  
  
  //Creating 4 pairs of identical nodes, to test node equal
  
  node *NE_1a = node_create(NULL, 0, 2, 4);
  node *NE_1b = node_create(NULL, 0, 2, 4);

  node *NE_2a = node_create(NULL, 52, 84, 61);
  node *NE_2b = node_create(NULL, 52, 84, 61);

  node *NE_3a = node_create(NULL, 75, 20, 7);
  node *NE_3b = node_create(NULL, 75, 20, 7);

  node *NE_4a = node_create(NULL, 66, 21, 1);
  node *NE_4b = node_create(NULL, 66, 21, 1);
  
  bool NE1 = node_equal(NE_1a, NE_1b);
  bool NE2 = node_equal(NE_2a, NE_2b);
  bool NE3 = node_equal(NE_3a, NE_3b);
  bool NE4 = node_equal(NE_4a, NE_4b);
  
  if(!NE1 || !NE2 || !NE3 || !NE4) {
    printf("node_equal failed to call equal nodes equal ! ! ! ! ! ! !\n");
    printf("FAIL\n");
    return 1;
  }

  NE_1a->t++;
  NE_2a->function++;
  NE_3a->parent_1++;
  NE_4a->parent_2++;
  
  bool nNE1 = node_equal(NE_1a, NE_1b);
  bool nNE2 = node_equal(NE_2a, NE_2b);
  bool nNE3 = node_equal(NE_3a, NE_3b);
  bool nNE4 = node_equal(NE_4a, NE_4b);
  
  if(nNE1 || nNE2 || nNE3 || nNE4) {
    printf("node_equal failed to call unequal nodes unequal ! ! ! ! ! ! !\n");
    printf("FAIL\n");
    return 1;
  }
  
  if(!node_equal(NULL, NULL) || node_equal(NE_1a, NULL) || node_equal(NULL, NE_1a)){
    printf("node_equal failed to account for NULL pointers ! ! ! ! ! ! !\n");
    printf("FAIL\n");
    return 1;
  }
  
  node_delete(NE_1a);
  node_delete(NE_1b);
  node_delete(NE_2a);
  node_delete(NE_2b);
  node_delete(NE_3a);
  node_delete(NE_3b);
  node_delete(NE_4a);
  node_delete(NE_4b);

  printf("node_equal passed.\n");
  
  
  //Creating 4 identical pairs of networks, to test network_equal 
  
  NODES_LENGTH WE_1a_nl = 6;
  node        *WE_1a_n[6]  = {(node *)0,(node *)1,(node *)2,(node *)3,(node *)4,(node *)5}; 
  NODES_LENGTH WE_1a_e  = 78;
  network     *WE_1a    = network_create(WE_1a_nl, WE_1a_n);
  WE_1a->root = WE_1a_e;
  
  NODES_LENGTH WE_1b_nl = 6;
  node        *WE_1b_n[6]  = {(node *)0,(node *)1,(node *)2,(node *)3,(node *)4,(node *)5}; 
  NODES_LENGTH WE_1b_e  = 78;
  network     *WE_1b    = network_create(WE_1b_nl, WE_1b_n);
  WE_1b->root = WE_1b_e;
  
  
  NODES_LENGTH WE_2a_nl = 4;
  node        *WE_2a_n[4]  = {(node *)0,(node *)1,(node *)2,(node *)3}; 
  NODES_LENGTH WE_2a_e  = 16;
  network     *WE_2a    = network_create(WE_2a_nl, WE_2a_n);
  WE_2a->root = WE_2a_e;
  
  NODES_LENGTH WE_2b_nl = 4;
  node        *WE_2b_n[4]  = {(node *)0,(node *)1,(node *)2,(node *)3}; 
  NODES_LENGTH WE_2b_e  = 16;
  network     *WE_2b    = network_create(WE_2b_nl, WE_2b_n);
  WE_2b->root = WE_2b_e;
  
  
  NODES_LENGTH WE_3a_nl = 7;
  node        *WE_3a_n[7]  = {(node *)0,(node *)1,(node *)2,(node *)3,(node *)4,(node *)5,(node *)6}; 
  NODES_LENGTH WE_3a_e  = 13;
  network     *WE_3a    = network_create(WE_3a_nl, WE_3a_n);
  WE_3a->root = WE_3a_e;
  
  NODES_LENGTH WE_3b_nl = 7;
  node        *WE_3b_n[7]  = {(node *)0,(node *)1,(node *)2,(node *)3,(node *)4,(node *)5,(node *)6}; 
  NODES_LENGTH WE_3b_e  = 13;
  network     *WE_3b    = network_create(WE_3b_nl, WE_3b_n);
  WE_3b->root = WE_3b_e;
  
  
  NODES_LENGTH WE_4a_nl = 2;
  node        *WE_4a_n[2]  = {(node *)0,(node *)1}; 
  NODES_LENGTH WE_4a_e  = 65;
  network     *WE_4a    = network_create(WE_4a_nl, WE_4a_n);
  WE_4a->root = WE_4a_e;
  
  NODES_LENGTH WE_4b_nl = 2;
  node        *WE_4b_n[2]  = {(node *)0,(node *)1}; 
  NODES_LENGTH WE_4b_e  = 65;
  network     *WE_4b    = network_create(WE_4b_nl, WE_4b_n);
  WE_4b->root = WE_4b_e;
  
  
  bool WE1 = network_equal(WE_1a,WE_1b);
  bool WE2 = network_equal(WE_2a,WE_2b);
  bool WE3 = network_equal(WE_3a,WE_3b);
  bool WE4 = network_equal(WE_4a,WE_4b);
   
  if(!WE1 || !WE2 || !WE3 || !WE4){
    printf("network_equal failed to call equal networks equal ! ! ! ! ! !\n");
    printf("FAIL\n");
    return 1;
  }


  WE_1a->nodes_length--;
  WE_2a->nodes[0]++;
  WE_3a->root++;
  WE_4a->root++;

 
  bool nWE1 = network_equal(WE_1a, WE_1b);
  bool nWE2 = network_equal(WE_2a, WE_2b);
  bool nWE3 = network_equal(WE_3a, WE_3b);
  bool nWE4 = network_equal(WE_4a, WE_4b);
  
  if(nWE1 || nWE2 || nWE3 || nWE4) {
    printf("network_equal failed to call unequal networks unequal ! ! ! ! ! ! !\n");
    printf("FAIL\n");
    return 1;
  }
  
  if(!network_equal(NULL, NULL) || network_equal(WE_1a, NULL) || network_equal(NULL, WE_1a)){
    printf("network_equal failed to account for NULL pointers ! ! ! ! ! ! !\n");
    printf("FAIL\n");
    return 1;
  }
  
  network_delete(WE_1a);
  network_delete(WE_1b);
  network_delete(WE_2a);
  network_delete(WE_2b);
  network_delete(WE_3a);
  network_delete(WE_3b);
  network_delete(WE_4a);
  network_delete(WE_4b);

  printf("network_equal passed.\n");
  
  
  
  
  //Creating the following network, Z
  //
  //
  //      F
  //      ^
  //      E     tensor_amass
  //     / \
  //    C *.D   tensor_scale
  //   / \
  //  A + B     tensor_add 
  //
  FORM_ELEMENT shared_form[2] = {2,2};
  
  tensor *A_tensor = tensor_create(2,shared_form);
  
  if(!A_tensor){
    printf("Failed to create tensors\n");
    printf("FAIL\n");
    return 1;
  }
   
  ELEMENT shared_data[4] = {3,4,5,6};
  
  A_tensor->data = shared_data;
  
  tensor *B_tensor = tensor_copy(A_tensor);
  tensor *D_tensor = tensor_copy(A_tensor);
  
  
  
  node *A = node_create(A_tensor, 0,  0,0);
  node *B = node_create(B_tensor, 0,  1,0);
  node *D = node_create(D_tensor, 0,  3,0);

  node *C = node_create(NULL, 0,  0,1);
  node *E = node_create(NULL, 2,  2,3);
  node *F = node_create(NULL, 4,  4,0);

  if(!A || !B || !C || !D || !E || !F){
    printf("Failed to create nodes\n");
    return 1;
  }
  
  node *Z_nodes[6] = {A, B, C, D, E, F};

  network *Z = network_create(6, Z_nodes);

  if(!Z){
    printf("Failed to create network\n");
    return 1;
  }
  
  
  if(!network_save("NETWORK_TEST_SAVE", Z)){
    printf("network_save failed ! ! ! ! ! ! ! ! \n");
    printf("FAIL\n");
    return 1;
  }
  
  network *Z_recovered = network_read("NETWORK_TEST_SAVE");
  
  if(!network_equal(Z, Z_recovered)){
    printf("network_save or network_read failed, recovered network is altered ! ! ! ! ! ! ! !\n");
    printf("FAIL\n");
    return 1;
  }
  
  network_save("NETWORK_TEST_SAVE2", Z_recovered);
  
  network_delete(Z_recovered);
  
  printf("network_save and network_read passed\n");
  
  
  
  
  
  
  if(!node_solve(Z, 5)){
    printf("Failed to solve node F in Z\n");
  }
  printf("Successfully solved node F in Z\n\n");

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
  Z->root = 5;
  node_solve(Z,Z->root);
  
  propogate_error(Z, 3, params);
  for(int i = 0; i < 3; i++){
    printf("Node %d\n", params[i]);
    tensor_print(Z->derivatives[params[i]] , "f");
  }
  
  printf("\nApplying gradient decent\n");
  
  for(int i = 0; i < 30; i++){ 
    if(!gradient_decent(Z, 0.002908, 0.01)){   //bad things happen when scale is >=0.01
      printf("GRADIENT DECENT FAILED ! ! ! ! ! ! ! ! ! \n");
    }
    
    printf("Error:    %f\n", Z->nodes[Z->root]->t->data[0]);
    network_clean(Z);
    node_solve(Z, Z->root);
    propogate_error(Z, 3, params);
  }
  printf("Gradient decent has been applied\n");
  
  network_clean(Z);
  node_solve(Z, Z->root);
  
  for(int i = 0; i < Z->nodes_length; i++){
    printf("Node %c in Z:\n", 'A' + i);
    tensor_print(Z->nodes[i]->t, "f");
  }
  
  
  /*       
           
                    I: input, {28,28}
           H        P: parameters, {784, 10}
          / \       D: intuitions, {10}
         R   T      R: beliefs, {10}
         |          T: Ground Truth, {10}
         D          H: distance {1}
        / \
       I   P
  */ 
  
  //I should actually not have all these tensors pre-made
   
  //FORM_ELEMENT input_form[2] = {28,28};
  FORM_ELEMENT param_form[2] = {28*28, 10};
  //FORM_ELEMENT digit_form[1] = {10};
  //FORM_ELEMENT scalr_form[1] = {1}; 
  
  //tensor *input     = tensor_create(2, input_form);
  tensor *param     = tensor_create(2, param_form);
  //tensor *intuition = tensor_create(1, digit_form);
  //tensor *beliefs   = tensor_create(1, digit_form);
  //tensor *truth     = tensor_create(1, digit_form);
  //tensor *distance  = tensor_create(1, scalr_form);
  
  node *L_i = node_create(NULL     , 0, 0,0);//0
  node *L_p = node_create(param    , 0, 1,0);//1
  node *L_d = node_create(NULL     , 3, 0,1);//2
  node *L_r = node_create(NULL     , 5, 2,0);//3
  node *L_t = node_create(NULL     , 0, 4,0);//4
  node *L_h = node_create(NULL     , 6, 3,4);//5
  
  node *L_nodes[6] = {L_i, L_p, L_d, L_r, L_t, L_h};
 
  network *L = network_create(6, L_nodes);
  L->root = 5;

  //network_save("MNIST-trainer", L); 
  
  network_delete(L); 
  node_delete(L_h);
  node_delete(L_t);
  node_delete(L_r);
  node_delete(L_d);
  node_delete(L_p);
  node_delete(L_i);
  //tensor_delete(distance);
  //tensor_delete(truth);
  //tensor_delete(beliefs);
  //tensor_delete(intuition);
  tensor_delete(param);
  //tensor_delete(input);
  //
  
  
   
  network_delete(Z);
  node_delete(F);
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
