#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>

// ################# Carregar Livros 

//struct do cadastro
struct cadastro {
	int cpf;
	char* nome; 
 	struct cadastro *prox;
};
typedef cadastro cadastro;

// 
cadastro* inserirPessoa (int cpf, char *nomeCadastro, cadastro *pessoa) {
   cadastro *novo = (cadastro*)malloc(sizeof(cadastro));
   novo->cpf = cpf;
   novo->nome = nomeCadastro;
	 novo->prox = pessoa;
   
	 return novo;
}
//Carregar as pessoas
cadastro* carregarPessoas(cadastro* pessoa) {
 	pessoa =inserirPessoa(11, "Daniel", pessoa);
	pessoa =inserirPessoa(12, "Danillo", pessoa);
	pessoa =inserirPessoa(13, "Gabriel", pessoa);

}
								
//Mostrar pessoas cadastradas
void mostrarPessoas(cadastro *pessoa) {
	
	if(pessoa==NULL)
		return; 
	
	mostrarPessoas(pessoa->prox);
		printf("Nome: %s\n",pessoa->nome);
		printf("Cpf: %d\n",pessoa->cpf);
		printf("\n");
}



// struct do livro com os dados
struct livro {
	int id;
	char* titulo; 
	char* status;
 	struct livro *prox;
};

typedef livro livro;


// aloca uma memória do livro
livro * alocar() {
	livro *novo= (livro*)malloc(sizeof(livro));
	return novo;
}

//insere livros
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
		printf("ID:%d \nTítulo: %s  \nStatus: %s\n",lista->id,lista->titulo,lista->status);
		printf("\n");
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

}

void imprimirLivrosEmprestados(livro *pilha) {
	livro *aux2= pilha;
	while(aux2->prox!= NULL)
	{
		printf(" %d   %s \n", aux2->prox->id, aux2->prox->titulo);
		aux2=aux2->prox;
	}
}





int main ()

{
	setlocale(LC_ALL,"portuguese");
	livro *lista = NULL;
	livro* livroEscolhido;
	lista = carregarBiblioteca(lista);
	cadastro *pessoa= NULL;
	
		
	livro cabeca;
	livro *tp;
	tp = &cabeca;
	tp->prox = NULL;
	
	
	
	int escolha, id;
	char nomeCadastro[30];
	int cpf;
						
	do
	{
		system("cls");
		printf(" -------------> M E N U P R I N C I P A L <---------------\n");
		printf("|\n");
		printf("|(1)Mostrar pessoas cadastradas\n");
		printf("|(3)Alugar Livro\n");
		printf("|(3)Sair\n");
		printf("|Escolha a opção desejada:\n");
		printf("|_________________________________________________________");
		scanf("%i",&escolha);
		system("cls");
		switch(escolha)
		{
				
				case 1:
					pessoa = carregarPessoas(pessoa);
					printf("             Usuários\n");
					mostrarPessoas(pessoa);
					break;
					
				break;
			case 2: 
				printf("             Livros\n");
				imprimirLivros(lista);
				printf("Digite o número do ID do livro desejado: ");
				scanf("%d",&id);
				livroEscolhido = buscaLivroId(lista, id);
				livroEscolhido->status = "Indisponível";
				emprestarLivro(livroEscolhido,  tp);
				break;
			case 3:
				imprimirLivrosEmprestados(tp);
				break;
				
		}
		system("pause");
	}while(escolha != 5);

	
	return 0;
}





