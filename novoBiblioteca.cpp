#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>

// ################# Cadastro de Usuário da Biblioteca
// Pilha do usuário
struct pilhaDeLivros {
	int id;
	char* titulo; 
 	struct pilhaDeLivros *prox;
 	struct pilhaDeLivros *tp;
};

typedef pilhaDeLivros pilhaDeLivros;


//struct do cadastro de usuário
struct cadUsuario {
	char nome[50]; 
	struct pilhaDeLivros *pilha;
 	struct cadUsuario *prox;
};

typedef cadUsuario cadUsuario;


cadUsuario *inicializarCadUsuario (char nomeUsuario[], cadUsuario *lista) {
   cadUsuario *novo =(cadUsuario*)malloc(sizeof(cadUsuario));
   
   pilhaDeLivros cabeca;
   pilhaDeLivros *tp;
   tp = &cabeca;
   tp->prox = NULL;
   
   pilhaDeLivros *novaPilha = (pilhaDeLivros*)malloc(sizeof(pilhaDeLivros));   
   novaPilha->prox  = tp->prox;
   tp->prox = novaPilha;
   
	
   novo->pilha = novaPilha;
   strcpy(novo->nome, nomeUsuario);
   
	if(lista == NULL){
		novo->prox = NULL;
		lista =novo;
	}else{
		cadUsuario *aux = lista;
		while (aux->prox!=NULL)
		{
			aux=aux->prox;
		}
		aux->prox=novo;
		novo->prox = NULL;
	}
	
	return lista;
}

// Carrega lista de usuário cadastrados
cadUsuario *carregarCadUsuario (cadUsuario* usuario) {
 	usuario = inicializarCadUsuario("Daniel", usuario);
	usuario = inicializarCadUsuario("Danillo", usuario);
	usuario = inicializarCadUsuario("Gabriel", usuario);
	usuario = inicializarCadUsuario("Fernando", usuario);
	
	return usuario;
}

cadUsuario *buscarUsuarioPorNome(char nome[] , cadUsuario* lista) {
	cadUsuario *aux2= lista;
	cadUsuario *usuarioEncontrado= NULL;
	while(aux2!= NULL) {
		if (strcmp(aux2->nome, nome) == 0) {
			usuarioEncontrado = aux2;
			break ;	
		}
		
		aux2=aux2->prox;
	}
	
	return usuarioEncontrado;
}

//imprime a lista de livros
void imprimirCadastroUsuarios(cadUsuario* lista) {
	cadUsuario *aux2= lista;
	while(aux2!= NULL)
	{
   		printf("Nome: %s\n",aux2->nome);
		aux2=aux2->prox;
	}
}


//################### Fim do Cadastro de Usuários da Biblioteca



//###################### Início da Lista de Livros da Biblioteca

// struct do livro com os dados
struct livro {
	int id;
	char* titulo; 
	char* status;
	struct filaDeEmprestimo *fila;
 	struct livro *prox;
};

typedef livro livro;

struct filaDeEmprestimo {
	char nomeUsuario[50];
 	struct filaDeEmprestimo *prox;
};

typedef filaDeEmprestimo filaDeEmprestimo;

// aloca uma memória do livro
livro * alocar() {
	livro *novo= (livro*)malloc(sizeof(livro));
	return novo;
}

//insere livros
livro* inicializarCadastroDeLivro (int id, char* titulo, char* status,  livro *lista) {
	
	filaDeEmprestimo *filaEmprestimo = (filaDeEmprestimo*) malloc(sizeof(filaDeEmprestimo));
	filaEmprestimo->prox = filaEmprestimo;
	
	livro *novo =(livro*)malloc(sizeof(livro));
   novo->titulo = titulo;
   novo->status = status;
   novo->id = id;
   novo->fila = filaEmprestimo;
	
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
	lista = inicializarCadastroDeLivro(1,"Star Wars", "Disponível", lista);
	lista = inicializarCadastroDeLivro(2,"Harry", "Disponível", lista);
	lista = inicializarCadastroDeLivro(3,"50 tons de cinza", "Disponível", lista);
	lista = inicializarCadastroDeLivro(4,"A elite", "Disponível", lista);
	lista = inicializarCadastroDeLivro(5,"Para todos os garotos que amei", "Disponível", lista);
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

filaDeEmprestimo *inserirNaFilaDeEmprestimo (char nomeUsuario[], filaDeEmprestimo* fila){
	filaDeEmprestimo *nova;
	nova = (filaDeEmprestimo*)malloc(sizeof(filaDeEmprestimo));
	nova->prox = fila->prox;
	fila->prox = nova;
	strcpy(nova->nomeUsuario, nomeUsuario);
	
	return nova;
}

void  mostrarFilaDeEmprestimo (filaDeEmprestimo *fila) {
   filaDeEmprestimo *p;
   int cont=0;
   p = fila;
   while(p->prox != fila){
	 printf("    Usuário : %s\n", p->prox->nomeUsuario);
	 cont++;
	 p = p->prox;
  }
}

void tirarDaFilaDeEspera ( filaDeEmprestimo *fila) {
 filaDeEmprestimo *ponteiro;
 ponteiro = fila->prox;
 fila->prox = ponteiro->prox;
 free (ponteiro);
}





//###################### Início das funções para empréstimo de livros
void emprestarLivro (livro *livroParaEmprestar, pilhaDeLivros *tp) { 	

	pilhaDeLivros *novaPilha = (pilhaDeLivros*)malloc(sizeof(pilhaDeLivros));
	novaPilha->id = livroParaEmprestar->id;
	novaPilha->titulo = livroParaEmprestar->titulo;
	novaPilha->prox  = tp->prox;
	tp->prox = novaPilha;   	 	
	livroParaEmprestar->status = "Indisponível";

 }

void imprimirLivrosEmprestados(pilhaDeLivros *pilha) {
 pilhaDeLivros *aux2= pilha; 
 while(aux2->prox!= NULL)
 {
	printf(" %d   %s \n", aux2->prox->id, aux2->prox->titulo);
	aux2=aux2->prox;
 }
}

int devolverLivro (pilhaDeLivros *pilha) {
   int idLivro;
   pilhaDeLivros *ponteiro;
   ponteiro = pilha->prox;
   idLivro = ponteiro->id;
   pilha->prox = ponteiro->prox;
   free (ponteiro);
   return idLivro; 
}




int main ()

{
	setlocale(LC_ALL,"portuguese");
	livro *lista = NULL;
	
	cadUsuario *usuarioEncontrado;
	
	cadUsuario *listaUsuarioCadastro = NULL;
	listaUsuarioCadastro = carregarCadUsuario(listaUsuarioCadastro);


	livro *livroEscolhido;
	char usuarioEscolhido[50];
	int escolha, id;
	char nomeCadastro[30];
	char *usuarioRemovido;
	int cpf;
	
	
	lista = carregarBiblioteca(lista);	
			
	do
	{
		system("cls");
		

		
		
		printf(" -------------> M E N U P R I N C I P A L <---------------\n");
		printf("|\n");
		printf("|(1)Escolher livro para empréstimo\n");
		printf("|(2)Mostrar pilha de livos emprestados\n");
		printf("|(3)Mostrar fila de espera \n");
		printf("|(4)Devolver livro\n");
		printf("|(5)Sair\n");
		printf("|Escolha a opção desejada:\n");
		printf("|_________________________________________________________\n");
		printf("Digite a opção: ");
		scanf("%i",&escolha);
		system("cls");
		switch(escolha)
		{
				
				case 1:

					imprimirCadastroUsuarios(listaUsuarioCadastro);
				
						printf("\nInforme Usuário? ");
						scanf("%s", usuarioEscolhido);
						
						imprimirLivros(lista);
						int idEscolhido;
						
						do {		
						    printf("\n %s informe Id do Livro ou 0 para sair? ", usuarioEscolhido);
							scanf("%d", &idEscolhido);
							
							if (idEscolhido > 0) {
						
								livroEscolhido  = buscaLivroId(lista, idEscolhido);
								
							
								usuarioEncontrado = buscarUsuarioPorNome(usuarioEscolhido, listaUsuarioCadastro);												
								   if (livroEscolhido->status == "Disponível"){
									 		emprestarLivro(livroEscolhido, usuarioEncontrado->pilha);
									 }else {
									 		inserirNaFilaDeEmprestimo(usuarioEncontrado->nome,livroEscolhido->fila);
									  }
					
							}
						
						} while (idEscolhido > 0);
						 
					
					break;
					
					case 2:
					    imprimirCadastroUsuarios(listaUsuarioCadastro);
						char usuario[50];
						
						printf("\nInforme Usuário que? ");
						scanf("%s",&usuario);
						
		
						usuarioEncontrado = buscarUsuarioPorNome(usuario, listaUsuarioCadastro);
						imprimirLivrosEmprestados(usuarioEncontrado->pilha);						
					break;
			case 3: 
				imprimirLivros(lista);
				printf("\nInforme o id do livro? ");
				scanf("%d", &idEscolhido);	
				livroEscolhido  = buscaLivroId(lista, idEscolhido);
				
				printf("*** Depois livro escolhido \n");
				mostrarFilaDeEmprestimo(livroEscolhido->fila);
				break;
			case 4:
				int livroDevolvido;
				imprimirCadastroUsuarios(listaUsuarioCadastro);
				printf("\nInforme Usuário? ");
						scanf("%s", usuarioEscolhido);
						usuarioEncontrado = buscarUsuarioPorNome(usuarioEscolhido, listaUsuarioCadastro);
						livroDevolvido= devolverLivro(usuarioEncontrado->pilha);
						livroEscolhido  = buscaLivroId(lista, livroDevolvido);
						
						printf("Livro devolvido\n");
						printf("Id: %d  -  Título: %s\n",livroEscolhido->id, livroEscolhido->titulo);
														
						if(livroEscolhido->fila == livroEscolhido->fila->prox) {
							printf("passei if");
							livroEscolhido->status = "Disponível";
						} else {
							printf("passei else \n");
							
							usuarioEncontrado = buscarUsuarioPorNome(livroEscolhido->fila->prox->nomeUsuario, listaUsuarioCadastro);
							emprestarLivro(livroEscolhido, usuarioEncontrado->pilha);
							tirarDaFilaDeEspera(livroEscolhido->fila);
						}
				break;
				
		}
		system("pause");
	}while(escolha != 5);

	
	return 0;
}
