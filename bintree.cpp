// Henrique Machado
// 2022


#include <stdio.h>
#include <iostream>

using namespace std;

struct Knot {
    int info;
    Knot *left, *right;
};


struct BinTree{
    Knot *root;
    void Create();
    //Função recursiva de inserir (precisa retornar um nó)
    Knot * Insert(Knot *current, int value);
    Knot * Wipe (Knot *current, int value);
    Knot * Search(int value);
    void Print(Knot *current);
    void PreOrder(Knot *current);
    void InOrder(Knot *current);
    void PostOrder(Knot *current);
};

void BinTree::Create(){
    root = NULL;
}

Knot* BinTree::Insert(Knot *current, int value){
    
    //caso base - nó atual == NULL
    if (current == NULL){
        current = new Knot; //se o nó atual é nulo, faz-se a alocaççao de um elemento
        current->info = value;
        current->left = NULL;
        current->right = NULL;
        
        return current;
    }
    //caso recursivo
    else {
        //fazer uma chamada recursiva a partir da ramificação esquerda
        if (value < current->info){
            current->left = Insert(current->left, value); //faz a ligação entre o novo nó e o nó pai
        }
        //fazer uma chamada recursiva a partir da ramificação direita 
        else if (value > current->info){
            current->right = Insert(current->right, value); //faz a ligação entre o novo nó e o nó pai
        }
    }
    return current;
}

Knot * BinTree::Wipe (Knot *current, int value){
    
    Knot* knot_temp;
    int temp; 
    
    //Caso base: Tem ou não o elemento
    //Caso tenha e o elemento foi encontrado (está no nó current)
        if (current->info == value){
            
            //Caso 1 - Nó folha
            if (current->left == NULL && current->right == NULL){
                delete current;
                return NULL;
            }
            
            //Caso 2 - Nó possui apenas um filho (à esquerda ou à direita)
            
            //Subcaso (2.1) - O filho está à esquerda
            else if (current->right == NULL){
                knot_temp = current->left;
                delete current;
                return knot_temp;
            }
            
            //Subcaso (2.2) - O filho está à direita
            else if (current->left == NULL){
                knot_temp = current->right;
                delete current;
                return knot_temp;
            }
            
            
            //Caso 3 -  Nó possui dois filhos (à esquerda e à direita)
            else if (current->left != NULL && current->right!=NULL){
             
             
            //Encontra aquele que irá substituir o nó removido (usa-se o maior, ou seja, à direita)
            knot_temp = current->right; 
             
            
            //Encontra o nó de menor valor ao considerar a subárvore à direita

            while (knot_temp->left != NULL) {
                knot_temp = knot_temp->left;
            }

            temp = current->info;
            current->info = knot_temp->info;
            knot_temp->info = temp;

            current->right = Wipe(current->right, knot_temp->info);   
            }
            
        }
        
     
    //Caso não tenha o elemento 
        else if (current == NULL){
            return current;
        }
    
        else if(value < current->info){
            current->left = Wipe(current->left, value);
        } 
        
        else if (value > current->info){
            current->right = Wipe(current->right, value);
        }
    
    
    return current;
}

Knot * BinTree::Search(int value){
    
    if (root == NULL){
        return NULL;
    }
    
    Knot *current = root;
    
    while (current->info != value){
        if (value < current->info){
            current = current->left;
        }
        
        else if (value > current->info){
            current = current->right;
        }
        
        if (current == NULL){
            return NULL;
        }
    }
    
    return current;
}


void BinTree::PreOrder(Knot* current){

//Caso base -> se o nó atual é nulo. Nesse sentido, se faz a função pensando caso ele não seja nulo. 
//O primeiro valor a ser apresentado é a raiz
    if (current != NULL){
        cout << current->info << " ";
        PreOrder(current->left);
        PreOrder(current->right);
    }

}

//Primeiro ele entra à esquerda, mostra o valor e depois entra à direita
void BinTree::InOrder(Knot *current){
     if (current != NULL){
        InOrder(current->left); 
        cout << current->info << " ";
        InOrder(current->right);
     }
 }

//Visita primeiro à esquerda, depois à direita e por fim apresenta o elemento visitado
//O ultimo elemento a ser apresentado é a raiz
void BinTree::PostOrder(Knot *current){
       if (current != NULL){
           PostOrder(current->left);
           PostOrder(current->right);
           cout << current->info << " ";
       }
 }

void BinTree::Print(Knot *current){
    
        cout << "\n\nTraversal: Pre-Order\n";
        PreOrder(current);

        cout << "\n\nTraversal: In-Order\n";
        InOrder(current);

        cout << "\n\nTraversal: Post-Order\n";
        PostOrder(current);

}



int main()
{
   
    BinTree my_tree;
    my_tree.Create();
    int option, value;
    
    do{
        cout << "\n------------------------------------------" <<
                "\n------------BINARY SEARCH TREE------------\n" <<
                "------------------------------------------\n" <<
                "What would you like to do?\n" <<
                "[1] Add a value\n" << "[2] Delete a value\n"<<
                "[3] Search for a value\n" << "[4] Print the tree\n" <<
                "[5] Close this program\n";
        cout << "Enter your command: "; cin >> option;
        
        switch(option){
            case 1: {
                cout << "\nType in the value you would like add: ";
                cin >> value;
                my_tree.root = my_tree.Insert(my_tree.root, value);
                break;
            }
            
            case 2: {
                cout << "\nType in the value wou want to delete: ";
                cin >> value;
                my_tree.root = my_tree.Wipe(my_tree.root, value);
                break;
            }
            
            case 3:{
                cout << "\nType in the value would like to search: ";
                cin >> value;
                if (my_tree.Search(value)!= NULL){
                    cout << "\nThe value was found and it is part of this tree.";
                }
                else {
                    cout << "\nThe chosen value is either not part of this tree.\nYou can add it using the option [1]";
                }
                break;
            }
            case 4: {
                my_tree.Print(my_tree.root);
                break;
            }
        }
        
    } while (option != 5);
    
    
    return 0;
}