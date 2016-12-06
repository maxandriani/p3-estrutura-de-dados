#include <iostream>
#include <stdlib.h>
#include <time.h> 

using namespace std;

#define TREE_LMR 'lmr'
#define TREE_RML 'rml'
#define TREE_LRM 'lrm'

struct Tree {
	int key;
	struct Tree *left;
	struct Tree *right;
};

// create_tree_node
Tree*	create_tree_node( int key );
// Insersão
Tree*	add_tree_node( Tree *root, Tree *node );
// Busca
Tree*	search_tree_node( Tree *root, int key);
// Altura de arvore
int 	get_tree_height( Tree *root );
// Profundidade do nó
int 	get_tree_node_level( Tree *root, int key );
// Impressão genérica
Tree*	print_tree( Tree *root, char nav[3] );
// Remoção
Tree* delete_tree_node( Tree *root, int key );

int main(){

	Tree *t = create_tree_node(50);
	Tree *n;
	int k;

	cout << "Populando arvore randomicamente" << endl;

	srand (time(NULL));

	for(int x=0; x<100; x++){
		k = rand() % 100;
		n = create_tree_node(k);
		t = add_tree_node(t, n);
	}

	cout << "Inserindo nos conhecidos (2, 89, 30)" << endl;

	// Insert known nodes for tests
	n = create_tree_node(2);
	t = add_tree_node(t, n);

	n = create_tree_node(89);
	t = add_tree_node(t, n);

	n = create_tree_node(30);
	t = add_tree_node(t, n);

	cout << "Imprimindo arvore: " << endl;
	char l[3];
	l[0] = 'l';
	l[1] = 'r';
	l[2] = 'm';
	print_tree(t, l);
	cout << endl << endl;

	cout << "Teste 01: Pesquisar no 89 -> ";
	n = search_tree_node(t, 89);
	cout << n->key << endl;

	cout << "Teste 02: Altura da arvore: ";
	cout << get_tree_height(t) << endl;

	cout << "Teste 03: Profundidade do no (2): ";
	cout << get_tree_node_level(t, 2) << endl;

	cout << "Teste 03: Profundidade do no (30): ";
	cout << get_tree_node_level(t, 30) << endl;

	cout << endl;
	cout << "Impressao RML:" << endl;
	l[0] = 'r';
	l[1] = 'm';
	l[2] = 'l';
	print_tree(t, l);

	cout << endl;
	cout << "Impressao MLR:" << endl;
	l[0] = 'm';
	l[1] = 'l';
	l[2] = 'r';
	print_tree(t, l);

	system("pause");

	return 0;
}

Tree*	create_tree_node( int key ){
	Tree *t = (Tree*) malloc(sizeof(Tree));
	t->left = NULL;
	t->right = NULL;
	t->key = key;
}

Tree*	add_tree_node( Tree *root, Tree *node ){
	if (root == NULL){
		return node;
	}

	if (root->key < node->key){
		root->left = add_tree_node(root->left, node); // Add on left side
	} else {
		root->right = add_tree_node(root->right, node); // Add on right side
	}

	return root; // Return updadted node
}

// Busca
Tree*	search_tree_node( Tree *root, int key){
	if (root == NULL){
		return NULL;
	}

	if (root->key == key){
		return root;
	}

	if (root->key < key){
		return search_tree_node(root->left, key);
	} else {
		return search_tree_node(root->right, key);
	}
}

// Altura de arvore
int 	get_tree_height( Tree *root ){
	int l, r;

	// Verifica se é uma folha, se sim, retorna 0 pois a contagem é feita de baixo para cima
	if (root == NULL){
		return 0;
	}

	// Compara o valor da direita com o da esquerda
	l = get_tree_height( root->left );
	r = get_tree_height( root->right );

	// Retorna o maior valor acrescido de um
	if (l < r){
		return ++r;
	} else {
		return ++l;
	}
}

// Profundidade do nó
int 	get_tree_node_level( Tree *root, int key ){
	int t;

	if (root == NULL){
		return 0;
	}

	if (root->key == key){
		// Achei o nó... taca-le o pau
		return 1;
	}

	// cheka direção do resultado
	if (root->key < key){
		t = get_tree_node_level( root->left, key );
	} else {
		t = get_tree_node_level( root->right, key );
	}

	// verifica se encontrou resultado
	if (t > 0){
		return ++t;
	} else {
		return 0;
	}
}
// Impressão genérica
Tree*	print_tree( Tree *root, char nav[3] ){
	Tree *t;

	if (root == NULL){
		cout << "<>";
		return NULL;
	}

	cout << "<";

	// generic magic
	for (int x=0; x<3; x++){
		switch(nav[x]){
			case 'l': // left
				t = print_tree( root->left, nav );
				break;
			case 'r': // right
				t = print_tree( root->right, nav );
				break;
			case 'm': // main: root
				t = root;
				break;
		}

		if (t != NULL){
			cout << '[' << t->key << ']';
		}
	}

	cout << ">";

	return root;
}