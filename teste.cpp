#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#define tam 2

struct usuario {
	char* nome; 
	struct pilhaDeLivros *usuarioPilha;
 	struct usuario *prox;
};

typedef struct usuario usuario;


usuario *criarUsuario(usuario *pessoa, char *nomeUsuario){
	usuario *novoUsuario =(usuario*)malloc(sizeof(usuario));
	novoUsuario->nome = nomeUsuario;
	
	if(pessoa == NULL)
	{
		novoUsuario->prox = NULL;
		pessoa =novoUsuario;
	}else{
		usuario *aux = pessoa;
		while (aux->prox!=NULL)
		{
			aux=aux->prox;
		}
		aux->prox=novoUsuario;
		novoUsuario->prox = NULL;
	}
	
	return pessoa;	
}

usuario* inserirNoInicio (usuario *pessoa, char *nomeUsuario)
{
	usuario *novoNo= (usuario*)malloc(sizeof(usuario));
	novoNo->nome = nomeUsuario; 
	if(pessoa == NULL){
		pessoa = novoNo;
		novoNo->prox=NULL;
	} else{
		novoNo->prox = pessoa;
		pessoa = novoNo;
	}
	return pessoa;
}


void imprimir(usuario *pessoa){
	usuario *aux2= pessoa;
	int cont=0;
	while(aux2!= NULL)
	{
		if(cont==1)
   	{
   		printf("--->Nome: %s\n", aux2->nome);
		}else{
			printf("    Nome: %s\n", aux2->nome);
		}
		cont ++;
		aux2=aux2->prox;
	}
	
}
 void removerUsuario (usuario *pessoa)
{
	usuario* aux;
	aux = pessoa;
	pessoa = aux->prox;
	free(aux);
	printf("passei\n");
	
}

usuario* carregarUsuario(usuario* pessoa){
	pessoa =criarUsuario(pessoa,"Lucas");
	pessoa= criarUsuario(pessoa,"Pedro");
	pessoa= criarUsuario(pessoa, "Daniel");
 	
 	return pessoa;
 }


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct livro{
	int id;
	char* titulo; 
	char* status;
 	struct livro *prox;
};
typedef livro livro;

livro *criarLivro(int id, char* titulo, char* status,  livro *lista){
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

void imprimirLivros(livro* lista){
	livro *aux2= lista;
	while(aux2!= NULL)
	{
   	printf(" Id:%d\n Título:%s\n Status:%s\n",aux2->id,aux2->titulo, aux2->status);
		aux2=aux2->prox;
	}
	
}

livro* carregarBiblioteca(livro* lista) { 
printf("passei aqui\n");
	lista = criarLivro(1,"Star Wars", "Disponível", lista);
	lista = criarLivro(2,"Harry", "Disponível", lista);
	lista = criarLivro(3,"50 tons de cinza", "Disponível", lista);
	lista = criarLivro(4,"A elite", "Disponível", lista);
	lista = criarLivro(5,"Para todos os garotos que amei", "Disponível", lista);
	
	return lista;
}
int main()
{
	setlocale(LC_ALL, "Portuguese");
	livro* lista= NULL;
	usuario *pessoa = NULL;
	char *usuarioRemovido;
	
 	
	
	

	
 	lista  = carregarBiblioteca(lista);
 	pessoa = carregarUsuario(pessoa);
 	
	imprimir(pessoa);
	imprimirLivros(lista);
	


	

	
	system("pause");
	return 0;
}
