#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>

// ################# Carregar Livros 

// struct do livro com os dados
struct livro {
	int id;
	char* titulo; 
	char* status;
 	struct livro *prox;
};

typedef livro livro;


// aloca uma memória
livro * alocar() {
	livro *novo= (livro*)malloc(sizeof(livro));
	return novo;
}


livro* insere (int id, char* titulo, char* status,  livro *p) {
   livro *novo = alocar();
   novo->titulo = titulo;
   novo->status = status;
   novo->id = id;
	 novo->prox = p;
   
	 return novo;
}

//imprime a lista de livros
void imprimirLivros(livro* lista) {
	if(lista==NULL)
		return; 
	
	imprimirLivros(lista->prox);
		printf("ID:%d  -   Título: %s  -   Status: %s\n",lista->id,lista->titulo,lista->status);
}

//Carregar os livros da biblioteca
livro* carregarBiblioteca(livro* lista) { 
	lista = insere(1,"Star Wars", "Disponível", lista);
	lista = insere(2,"Harry", "Disponível", lista);
	lista = insere(3,"50 tons de cinza", "Disponível", lista);
	lista = insere(4,"A elite", "Disponível", lista);
	lista = insere(5,"Para todos os garotos que amei", "Disponível", lista);
}


//Buscar livro desejado pelo id
livro* buscaLivroId(livro *lista, int id){
	livro *p, *numero =NULL;
  p = lista;
 
   while (p != NULL && p->id != id) {
   		p = p->prox; 
	 }
	   
	 if(p) {
	 		numero = p;
	 }
      
   return numero;
}



///////////////////////////////////////////// Emprestimo
void emprestarLivro (livro *livroParaEmprestar, livro *tp) { 
	
	livroParaEmprestar->status = "Indisponível";
   livro *novaPilha = alocar();
   novaPilha->id = livroParaEmprestar->id;
   novaPilha->titulo = livroParaEmprestar->titulo;
   novaPilha->status = livroParaEmprestar->status;
 
   
   novaPilha->prox  = tp->prox;
   tp->prox = novaPilha;
//      printf("ID:%d  -   Título: %s  -   Status: %s\n",novaPilha->id,novaPilha->titulo,novaPilha->status);

}

void imprimirLivrosEmprestados(livro *pilha) {
	livro *aux2= pilha;
	while(aux2->prox!= NULL)
	{
		printf(" %d   %s \n", aux2->prox->id, aux2->prox->titulo);
		aux2=aux2->prox;
	}
}
//////

//################################## fila de usuário

struct usuario{
	char* nome;
	struct usuario *prox;
};

typedef usuario usuario;

usuario* criarUsuario (char *nomeUsuario ,usuario* pessoas)
{
	usuario *novo;
	novo= (usuario*) malloc(sizeof(usuario));
	novo->prox = pessoas->prox;
	pessoas->prox = novo;
	pessoas->nome= nomeUsuario;
	return novo;
}

void listaDePessoas (usuario *pessoas){
		pessoas = criarUsuario("Daniel",pessoas);
		pessoas = criarUsuario("Danillo",pessoas);
		pessoas = criarUsuario("Gabriel",pessoas);
		pessoas = criarUsuario("Lucas",pessoas);
}

void imprimir(usuario *pessoas){
	usuario *aux2= pessoas;
//	while(aux2!= NULL)
//	{
//		printf("%s\n",aux2->nome);
//		aux2=aux2->prox;
//	}
 usuario* u;
 for(u = pessoas; u->prox != NULL; u= u->prox) {
 		printf("%s\n",u->nome);
 }
	
}



int main ()

{
	setlocale(LC_ALL,"portuguese");
	livro *lista = NULL;
	livro* livroEscolhido;
	lista = carregarBiblioteca(lista);
	
	usuario *pessoas = NULL;
//	usuario* pessoas;
	pessoas = (usuario*)malloc(sizeof(usuario));
	pessoas->prox = pessoas;
	
		
	livro cabeca;
	livro *tp;
	tp = &cabeca;
	tp->prox = NULL;
	
	pessoas = criarUsuario("Daniel",pessoas);
		pessoas = criarUsuario("Danillo",pessoas);
//	listaDePessoas(pessoas);
//	imprimir(pessoas);
	
	
	int escolha, id;
	
	
	do
	{
		system("cls");
		printf(" -------------> M E N U P R I N C I P A L <---------------\n");
		printf("|\n");
		printf("|(1)Alugar livros disponíveis \n");
		printf("|(2)Mostrar Livros Alugados\n");
		printf("|(3)Sair\n");
		printf("|Escolha a opção desejada:\n");
		printf("|_________________________________________________________");
		scanf("%i",&escolha);
		system("cls");
		switch(escolha)
		{
			case 1: 
				imprimirLivros(lista);
				printf("Digite o número do ID do livro desejado: ");
				scanf("%d",&id);
				livroEscolhido = buscaLivroId(lista, id);
//				imprimirLivros(lista);
				livroEscolhido->status = "Indisponível";
				emprestarLivro(livroEscolhido,  tp);
				break;
			case 2:
				imprimirLivrosEmprestados(tp);
				break;
				
		}
		system("pause");
	}while(escolha != 3);

	
	return 0;
}





