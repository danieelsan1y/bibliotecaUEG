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


//################### Início da Fila de Usuários
//struct fila do usuário
struct filaUsuario {
	char nome[50]; 
 	struct filaUsuario *prox;
};

typedef filaUsuario usuario;

usuario *inserirUsuario (char nomeUsuario[], filaUsuario *pessoa) {
	filaUsuario *nova;
	nova = (filaUsuario*)malloc(sizeof(filaUsuario));
	nova->prox = pessoa->prox;
	pessoa->prox = nova;
	strcpy(pessoa->nome, nomeUsuario);	
	
  return nova;
}
								
void  mostrarFilaDeUsuarios (filaUsuario *pessoa) {
   filaUsuario *p;
   int cont=0;
   p = pessoa;
   while(p->prox != pessoa){
	 printf("    Nome: %s\n", p->prox->nome);
	 cont++;
	 p = p->prox;
  }
}

filaUsuario *buscarPrimenroDaFilaDeUsuarios (filaUsuario *pessoa) {
	printf("Primeiro %s", pessoa->prox->nome);
  return pessoa->prox;
}

char* removeUsuarioDaFila (filaUsuario *pessoa) {
 char *nome;
 filaUsuario *p, *t;

 t = pessoa; 
 p = pessoa->prox; // p aponta primeiro da fila
 nome = p->nome;
 pessoa->prox = p->prox;
 
 pessoa = p;
 pessoa->prox = t;

 free (p);
 return nome;
}


//###################### Início da Lista de Livros da Biblioteca

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
//###################### Início da Lista de Livros da Biblioteca
criaPilhaLivros(pilhaDeLivros *pilha) {
	
}


//###################### Início das funções para empréstimo de livros
void emprestarLivro (livro *livroParaEmprestar, pilhaDeLivros *tp) { 	
   livroParaEmprestar->status = "Indisponível";

   pilhaDeLivros *novaPilha = (pilhaDeLivros*)malloc(sizeof(pilhaDeLivros));
   novaPilha->id = livroParaEmprestar->id;
   novaPilha->titulo = livroParaEmprestar->titulo;

   novaPilha->prox  = tp->prox;
   tp->prox = novaPilha;
}

void imprimirLivrosEmprestados(pilhaDeLivros *pilha) {
 pilhaDeLivros *aux2= pilha; 
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
	
	cadUsuario *usuarioEncontrado;
	
	cadUsuario *listaUsuarioCadastro = NULL;
	listaUsuarioCadastro = carregarCadUsuario(listaUsuarioCadastro);


	filaUsuario *filaUsuarios;
	filaUsuarios = (filaUsuario*)malloc(sizeof(filaUsuario));
	filaUsuarios->prox = filaUsuarios;
	
	pilhaDeLivros cabeca;
	pilhaDeLivros *tp;
	tp = &cabeca;
	tp->prox = NULL;
	
	
	int escolha, id;
	char nomeCadastro[30];
	char *usuarioRemovido;
	int cpf;
	
	
	lista = carregarBiblioteca(lista);	
			
	do
	{
		system("cls");
		
//		printf("Fila de usuários para Solicitar Livros\n");
//		mostrarFilaDeUsuarios(filaUsuarios);
//		printf("\n\n");
		
		
		printf(" -------------> M E N U P R I N C I P A L <---------------\n");
		printf("|\n");
		printf("|(1)Escolher livro para empréstimo\n");
		printf("|(2)Mostrar pilha de livos emprestados\n");
		printf("|(3)Mostrar fila de espera \n");
		printf("|(4)Sair\n");
		printf("|Escolha a opção desejada:\n");
		printf("|_________________________________________________________\n");
		printf("Digite a opção: ");
		scanf("%i",&escolha);
		system("cls");
		switch(escolha)
		{
				
				case 1:
//					imprimirCadastroUsuarios(listaUsuarioCadastro);
//					
//					char novoUsuario[50];
//					printf("\nInforme Usuário? ");
//					scanf("%s", novoUsuario);
//						
//					filaUsuarios = inserirUsuario(novoUsuario, filaUsuarios);

					imprimirCadastroUsuarios(listaUsuarioCadastro);
				
						char usuarioEscolhido[50];
						printf("\nInforme Usuário? ");
						scanf("%s", usuarioEscolhido);
						
						imprimirLivros(lista);
						int idEscolhido;
						
						do {		
						    printf("\n %s informe Id do Livro ou 0 para sair? ", usuarioEscolhido);
							scanf("%d", &idEscolhido);
							
							if (idEscolhido > 0) {
								livro *livroEscolhido;
								livroEscolhido  = buscaLivroId(lista, idEscolhido);
								
//								char primeiroFila[50]; 
//								strcpy(primeiroFila, filaUsuarios->prox->nome);
							
								usuarioEncontrado = buscarUsuarioPorNome(usuarioEscolhido, listaUsuarioCadastro);												
								emprestarLivro(livroEscolhido, usuarioEncontrado->pilha);
							}
						
						} while (idEscolhido > 0);
						 

//						removeUsuarioDaFila(filaUsuarios);	
					
					break;
					
					case 2:
					    imprimirCadastroUsuarios(listaUsuarioCadastro);
						char usuario[50];
						
						printf("\nInforme Usuário que? ");
						scanf("%s", usuario);
						
		
						usuarioEncontrado = buscarUsuarioPorNome(usuario, listaUsuarioCadastro);
						imprimirLivrosEmprestados(usuarioEncontrado->pilha);						
					break;
			case 3: 

				
				break;
				
		}
		system("pause");
	}while(escolha != 5);

	
	return 0;
}
