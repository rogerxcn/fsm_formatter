#include <iostream>
#include <string>
#include <cmath>
#include <map>
#include <vector>
#include <list>
#include <sstream>
using namespace std;


/* CONVINIENT CONSTANTS */

#define MAX_STATES 25


/* GLOBAL PARAMETERS */

int num_bits, num_nodes = 0;
char fsm_type;


/* Data Structure Def */

typedef struct MealyNode_Struct{

  string name;

  map<int, string> next_state;
  map<int, string> output;

}meNode;


typedef struct MooreNode_Struct{

  string name;

  map<int, string> next_state;
  string output;

}moNode;



/* CONSTRUCT ROUTINES */

void construct_mealy(){

  meNode* nodes[num_nodes];
  map<string, int> existing_nodes;
  std::vector<string> args;
  string temp;
  int locptr = 0;
  bool quit = false;

  cin.ignore();
  std::cout << "\nUsage:\n  NODE ${name} -> Create a new state\n  ARC ${from} ${to} ${input} ${output} -> define a state behavior\n  RETURN ${node} ${input} -> Check node\n  QUIT to quit." << '\n' << '\n';

  while (!quit){

    bool valid = false;

    args.clear();

    std::cout << "\nMealy> ";
    getline(cin, temp);
    istringstream input(temp);

    string word;
    while (input >> word){
      args.push_back(word);
    }

    if (args[0] == "NODE" && args.size()==2){

      valid = true;

      if (existing_nodes.find(args[1]) != existing_nodes.end()){
        std::cout << "Node already exists!" << '\n';
        continue;
      }

      if (locptr == num_nodes) {
        std::cout << "No more nodes can be created!" << '\n';
        continue;
      }

      existing_nodes[args[1]] = locptr;
      nodes[locptr++] = new meNode;

    }



    if (args[0] == "ARC" && args.size() == 5){

      valid = true;

      if (existing_nodes.find(args[1]) == existing_nodes.end() || existing_nodes.find(args[2]) == existing_nodes.end()){
        std::cout << "Node does not exist" << '\n';
        continue;
      }

      vector<int> target = {0};

      for (int i = 0; i < args[3].size(); i++){

        if (args[3][i] != 'x' && args[3][i] != 'X' ){
          for (vector<int>::iterator it = target.begin(); it < target.end(); it++){

            *it <<= 1;
            *it += (int) (args[3][i] - '0');

          }
        }else{

          vector<int> tempv = {};

          for (vector<int>::iterator it = target.begin(); it < target.end(); it++) {
            tempv.push_back(*it);
            tempv.push_back(*it);
          }

          target = tempv;

          int temp = 0;

          for (vector<int>::iterator it = target.begin(); it < target.end(); it++){

            *it <<= 1;
            *it += temp%2;
            temp++;

          }

        }

      }

      for (vector<int>::iterator it = target.begin(); it < target.end(); it++){

        (nodes[existing_nodes[args[1]]] -> next_state)[*it] = args[2];
        (nodes[existing_nodes[args[1]]] -> output)[*it] = args[4];

      }

    }


    if (args[0] == "QUIT") break;

    if (args[0] == "RETURN"){
      vector<int> target = {0};

      for (int i = 0; i < args[2].size(); i++){

        if (args[2][i] != 'x' && args[2][i] != 'X' ){
          for (vector<int>::iterator it = target.begin(); it < target.end(); it++){

            *it <<= 1;
            *it += (int) (args[2][i] - '0');

          }
        }else{

          vector<int> tempv = {};

          for (vector<int>::iterator it = target.begin(); it < target.end(); it++) {
            tempv.push_back(*it);
            tempv.push_back(*it);
          }

          target = tempv;

          int temp = 0;

          for (vector<int>::iterator it = target.begin(); it < target.end(); it++){

            *it <<= 1;
            *it += temp%2;
            temp++;

          }

        }

      }

      for (vector<int>::iterator it = target.begin(); it < target.end(); it++){

        cout << "\nInput: " << *it << '\n';
        cout << "Next State is " << (nodes[existing_nodes[args[1]]] -> next_state)[*it] << '\n' ;
        cout << "Output is " << (nodes[existing_nodes[args[1]]] -> output)[*it] << '\n';

      }
    }

  }

  /* TODO mealy_output(nodes) */;

}

void construct_moore(){

  moNode* nodes[num_nodes];
  map<string, int> existing_nodes;
  std::vector<string> args;
  string temp;
  int locptr = 0;
  bool quit = false;
  cin.ignore();
  std::cout << "\nUsage:\n  NODE ${name} -> Create a new state\n  ARC ${from} ${to} ${input} ${output} -> define a state behavior\n  RETURN ${node} ${input} -> Check node\n  QUIT to quit." << '\n' << '\n';

  while (!quit){

    bool valid = false;

    args.clear();

    std::cout << "\nMoore> ";
    getline(cin, temp);
    istringstream input(temp);

    string word;
    while (input >> word){
      args.push_back(word);
    }

    if (args[0] == "NODE" && args.size()==2){

      valid = true;

      if (existing_nodes.find(args[1]) != existing_nodes.end()){
        std::cout << "Node already exists!" << '\n';
        continue;
      }

      if (locptr == num_nodes) {
        std::cout << "No more nodes can be created!" << '\n';
        continue;
      }

      existing_nodes[args[1]] = locptr;
      nodes[locptr++] = new moNode;

    }



    if (args[0] == "ARC" && args.size() == 5){

      valid = true;

      if (existing_nodes.find(args[1]) == existing_nodes.end() || existing_nodes.find(args[2]) == existing_nodes.end()){
        std::cout << "Node does not exist" << '\n';
        continue;
      }

      vector<int> target = {0};

      for (int i = 0; i < args[3].size(); i++){

        if (args[3][i] != 'x' && args[3][i] != 'X' ){
          for (vector<int>::iterator it = target.begin(); it < target.end(); it++){

            *it <<= 1;
            *it += (int) (args[3][i] - '0');

          }
        }else{

          vector<int> tempv = {};

          for (vector<int>::iterator it = target.begin(); it < target.end(); it++) {
            tempv.push_back(*it);
            tempv.push_back(*it);
          }

          target = tempv;

          int temp = 0;

          for (vector<int>::iterator it = target.begin(); it < target.end(); it++){

            *it <<= 1;
            *it += temp%2;
            temp++;

          }

        }

      }

      for (vector<int>::iterator it = target.begin(); it < target.end(); it++){

        (nodes[existing_nodes[args[1]]] -> next_state)[*it] = args[2];
        nodes[existing_nodes[args[1]]] -> output = args[4];

      }

    }


    if (args[0] == "QUIT") break;

    if (args[0] == "RETURN"){
      vector<int> target = {0};

      for (int i = 0; i < args[2].size(); i++){

        if (args[2][i] != 'x' && args[2][i] != 'X' ){
          for (vector<int>::iterator it = target.begin(); it < target.end(); it++){

            *it <<= 1;
            *it += (int) (args[2][i] - '0');

          }
        }else{

          vector<int> tempv = {};

          for (vector<int>::iterator it = target.begin(); it < target.end(); it++) {
            tempv.push_back(*it);
            tempv.push_back(*it);
          }

          target = tempv;

          int temp = 0;

          for (vector<int>::iterator it = target.begin(); it < target.end(); it++){

            *it <<= 1;
            *it += temp%2;
            temp++;

          }

        }

      }

      for (vector<int>::iterator it = target.begin(); it < target.end(); it++){

        cout << "\nInput: " << *it << '\n';
        cout << "Next State is " << (nodes[existing_nodes[args[1]]] -> next_state)[*it] << '\n' ;
        cout << "Output is " << nodes[existing_nodes[args[1]]] -> output << '\n';

      }
    }

  }

  /* TODO mealy_output(nodes) */;

}


int main(int argc, char const *argv[]) {

  InputState:
    std::cout << "Enter the type of FSM you would like to construct > M(e)aly or M(o)ore: " << '\n';
    std::cin >> fsm_type;

    switch (fsm_type) {
      case 'e':
      case 'E':
      case 'o':
      case 'O':
        break;
      default:
        std::cout << "Invalid type." << '\n';
        goto InputState;
        break;
    }


  InputBits:
    std::cout << "Enter the number of inputs: " << '\n';
    std::cin >> num_bits;
    if (num_bits <= 0 || num_bits > 4){
      std::cout << "Invalid input bits." << '\n';
      goto InputBits;
    }

  InputNodes:
    std::cout << "Enter the number of nodes: " << '\n';
    std::cin >> num_nodes;
    if (num_nodes <= 0 || num_nodes > MAX_STATES){
      std::cout << "Invalid input nodes." << '\n';
      goto InputNodes;
    }

  switch (fsm_type) {
    case 'e':
    case 'E':
      construct_mealy();
      break;
    case 'o':
    case 'O':
      construct_moore();
      break;


  }


  return 0;


}
