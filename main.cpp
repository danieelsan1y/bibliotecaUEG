#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>

// ################# Carregar Livros 

//struct do usuário
struct usuario {
	char* nome; 
	struct pilhaDeLivros *usuarioPilha;
 	struct usuario *prox;
};

// Pilha do usuário
struct pilhaDeLivros {
	int idLivro;
	char* tituloLivro; 
 	struct pilhaUsuario *prox;
};


typedef pilhaDeLivros pilhaDeLivros;
typedef usuario usuario;



usuario *inserirUsuario (char *nomeUsuario, usuario *pessoa) {
	usuario *nova;
	nova = (usuario*)malloc(sizeof(usuario));
	nova->prox = pessoa->prox;
	pessoa->prox = nova;
	pessoa->nome = nomeUsuario;
	return nova;

}

//Carregar as pessoas
void carregarUsuario (usuario* pessoa) {
 	pessoa = inserirUsuario("Daniel", pessoa);
	pessoa = inserirUsuario("Danillo", pessoa);
	pessoa = inserirUsuario("Gabriel", pessoa);
	pessoa = inserirUsuario("Fernando", pessoa);
}
								
void  mostrarUsuario (usuario *pessoa) {
   usuario *p;
   int cont=0;
   p = pessoa;
   while(p->prox != pessoa){
   	if(cont==1)
   	{
   		printf("--->Nome: %s\n", p->nome);
		}else{
			printf("    Nome: %s\n", p->nome);
		}
		cont++;
		p = p->prox; 
	 }    
}

char* removeUsuario (usuario *pessoa) {
 char *nome;
 usuario *p, *t;

 t = pessoa; 
 p = pessoa->prox; // p aponta primeiro da fila
 nome = p->nome;
 pessoa->prox = p->prox;
 
 pessoa = p;
 pessoa->prox = t;

// free (p);
 return nome;
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
livro* insere (int id, char* titulo, char* status,  livro *lista) {
	livro *novo =(livro*)malloc(sizeof(livro));
   novo->titulo = titulo;
   novo->status = status;
   novo->id = id;
	
	if(lista == NULL)
	{
		novo->prox = NULL;
		lista =novo;
	}else{
		livro *aux = lista;
		while (aux->prox!=NULL)
		{
			aux=aux->prox;
		}
		aux->prox=novo;
		novo->prox = NULL;
	}
	return lista;
}


//imprime a lista de livros
void imprimirLivros(livro* lista) {
	livro *aux2= lista;
	while(aux2!= NULL)
	{
   	printf(" Id:%d\n Título:%s\n Status:%s\n",aux2->id,aux2->titulo, aux2->status);
   	printf("\n");
		aux2=aux2->prox;
	}
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

	usuario *pessoa;
	pessoa = (usuario*)malloc(sizeof(usuario));
	pessoa->prox = pessoa;

		
	/*livro cabeca;
	livro *tp;
	tp = &cabeca;
	tp->prox = NULL;
	*/
	
	pilhaDeLivros cabeca;
	pilhaDeLivros *tp;
	tp = &cabeca;
	tp->prox = NULL;
	
	
	int escolha, id;
	char nomeCadastro[30];
	char *usuarioRemovido;
	int cpf;
	
	
	carregarUsuario(pessoa);		
	lista = carregarBiblioteca(lista);	
	printf("Fila de usuários");
	mostrarUsuario(pessoa);
			
	do
	{
		system("cls");
		printf("Fila de usuários\n");
		if (pessoa->prox == pessoa) {
			pessoa = (usuario*)malloc(sizeof(usuario));
			pessoa->prox = pessoa;
			carregarUsuario(pessoa);
			mostrarUsuario(pessoa);
		} else {
			mostrarUsuario(pessoa);
		}
		
		
		printf(" -------------> M E N U P R I N C I P A L <---------------\n");
		printf("|\n");
		printf("|(1)Mostrar pessoas cadastradas\n");
		printf("|(2)Mostrar livros\n");
		printf("|(3)Sair\n");
		printf("|Escolha a opção desejada:\n");
		printf("|_________________________________________________________\n");
		printf("Digite a opção: ");
		scanf("%i",&escolha);
		system("cls");
		switch(escolha)
		{
				
				case 1:
					usuarioRemovido = removeUsuario(pessoa);
					break;
					
					case 2:
						printf("             Livros\n");
						imprimirLivros(lista);
				break;
			case 3: 
				/*printf("             Livros\n");
				imprimirLivros(lista);
				printf("Digite o número do ID do livro desejado: ");
				scanf("%d",&id);
				livroEscolhido = buscaLivroId(lista, id);
				emprestarLivro(livroEscolhido,  tp);
				break;
			case 4:
				imprimirLivrosEmprestados(tp);
				*/
				break;
				
		}
		system("pause");
	}while(escolha != 5);

	
	return 0;
}





