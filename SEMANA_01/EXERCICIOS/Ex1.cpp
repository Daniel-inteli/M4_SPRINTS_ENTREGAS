#include <iostream>
#include <string>


using namespace std;

char *direcao[4] = {(char *)"Direita",(char*)"Esquerda",(char*)"Frente",(char*)"Tr�s"}; //guardando as direcoes em uma variavel ponteiro
// 1 -  Fa�a uma fun��o que recebe uma certa medida e ajusta ela percentualmente 
// entre dois valores m�nimo e m�ximo e retorna esse valor
int ajuste(int medida, int minimo, int maximo) {
	int resultado = ((medida - minimo)*100)/(maximo - minimo); //formula que reajusta a medida 
	return resultado;  
}
// 2 - Fa�a uma fun��o que simule a leitura de um sensor lendo o 
// valor do teclado ao final a fun��o retorna este valor
int recebeDistancia(int lado ) { 
	int valor; 
	cout << "Digite a distancia(em metros) para "<< direcao[lado]; // Faz um pedido ao usuario e utiliza variavel direcao para futuramente em um for repetir as perguntas alterando os valores dessa variavel pelo indice
	cout << ":" ;
	cin >> valor; // guarda a resposta do usuario na variavel valor
	return valor;
};
// 3 - Fa�a uma fun��o que armazena uma medida inteira qualquer 
// em um vetor fornecido. Note que como C n�o possui vetores 
// nativos da linguagem, lembre-se que voc� precisa passar o 
// valor m�ximo do vetor assim como a �ltima posi��o preenchida
// Evite tamb�m que, por acidente, um valor seja escrito em 
// uma �rea de mem�ria fora do vetor
int armazena(int medida, int *vetor, int tamanhoVetor, int posicao){ 
	/*no if abaixo a gente faz um armazenamento do valor das medidas nas posicoes do indice dos vetores,
	 ou seja, vai verificar a direcao e guardar o valor da medida, ate o tamanho maximo do vetor,
	e feito esse processo de verificacao pois conforme diz o enunciado da questao a linguagem nao
	possui vetores nativos, podendo ocasionar no aparecimento de bugs devido 
	a lixos de memoria que o computador pode buscar para preencher o espaco 
	do vetor caso seja desrespeitado esse limite*/ 
	if (posicao < tamanhoVetor){ 
		vetor[posicao] = medida;
		posicao += 1;
	return posicao;
	}
		

}


// 4 - Fa�a uma fun��o que recebe um vetor com 4 posi��es que cont�m 
// o valor da dist�ncia de um pequeno rob� at� cada um dos seus 4 lados.
// A fun��o deve retornar duas informa��es: A primeira � a dire��o 
// de maior dist�ncia ("Direita", "Esquerda", "Frente", "Tras") e a 
// segunda � esta maior dist�ncia.

// Esta presente na questao 2 e na funcao dirige


// 5 - Fa�a uma fun��o que pergunta ao usu�rio se ele deseja continuar o mapeamento e 
// retorna verdadeiro ou falso
int confirmacao(){
	char confirma;
	cout<<"Voc� deseja continuar?(s/n)"; // Expoe ao usuario uma pergunta
	cin>> confirma; // Guarda a resposta do usuario na variavel confirma
	if (confirma == 's'){ 
		return 1; // Quando o usuario apertar s a funcao retornara 1
	}
	else{
		return 0; // caso o primeiro if nao seja verdadeiro a funcao retornara 0
	}
}

// 6 - A fun��o abaixo (que est� incompleta) vai "dirigindo" virtualmente um rob� 
// e atrav�s de 4 sensores em cada um dos 4 pontos do robo ("Direita", "Esquerda", 
// "Frente", "Tras"). 
//      A cada passo, ele verifica as dist�ncias aos objetos e vai mapeando o terreno 
// para uma movimenta��o futura. 
//      Ele vai armazenando estas distancias em um vetor fornecido como par�metro 
// e retorna a ultima posicao preenchida do vetor.
//      Esta fun��o deve ir lendo os 4 sensores at� que um comando de pare seja enviado 
//
//      Para simular os sensores e os comandos de pare, use as fun��es j� constru�das 
// nos �tens anteriores e em um looping cont�nuo at� que um pedido de parada seja 
// enviado pelo usu�rio. 
//
//      Complete a fun��o com a chamada das fun��es j� criadas
int dirige(int *v,int maxv){
	int maxVetor = maxv;
	int *vetorMov = v;
	int posAtualVetor = 0;
	int dirigindo = 1;		
	while(dirigindo){ // Funcao abaixo ira ocorrer enquanto o usuario na funcao confirmacao pressionar a tecla s 
		for  (int i = 0; i < 4;i++){ // Vai repetir o processo de perguntas da funcao recebeDistancia pelo tamanho do vetor, que no caso sao as 4 direcoes
			int medida = recebeDistancia(i); // Variavel medida vai receber o retorno da funcao recebeDistancia nas 4 direcoes
			posAtualVetor = armazena(medida,vetorMov,maxVetor,posAtualVetor); 
		}
		dirigindo = confirmacao();	// dirigindo recebe o retorno da funcao confirmacao que vai determinar o continuamento ou nao do while	
	}
	return posAtualVetor;
}
char *direcaoMaiorCaminho(int *vetorMov, int *maiorDir){ //Funcao que guarda a direcao da maior distancia
	int maiorDistancia = vetorMov[0];
	int indice = 0;
	for (int i =0; i< 4;i++){ // vai verificar cada indice do vetor e guardar o indice com a maior distancia
		if (vetorMov[i] >maiorDistancia){ // verifica se o valor do indice e maior que o anterior  
			maiorDistancia = vetorMov[i]; // guarda a 'direcao' que tem a maior distancia
			indice = i;
		}
	
	}
	
	*maiorDir = maiorDistancia;
	return direcao[indice]; // Retorna o valor do indice que contem a maior distancia
}
	


// O trecho abaixo ir� utilizar as fun��es acima para ler os sensores e o movimento
// do rob� e no final percorrer o vetor e mostrar o movimento a cada dire��o baseado 
// na maior dist�ncia a cada movimento
void percorre(int *v,int tamPercorrido){	 // Funcao que informa ao usuario a direcao e o valor da maior distancia	
	int *vetorMov = v;
	int maiorDir = 0;
	
	for(int i = 0; i< tamPercorrido; i+=4){ // Vai passar em todos os indices e informar ao usuario a direcao e distancia percorrida  
		char *dir = direcaoMaiorCaminho(&(vetorMov[i]),&maiorDir);
		printf("Movimentando para %s distancia = %i metros\n",dir,maiorDir);
	}
}

int main(int argc, char** argv) { // funcao inicial do sistema que chamara as outras funcoes 
	int maxVetor = 100;
	int vetorMov[maxVetor*4];
	int posAtualVet = 0;
	
	posAtualVet = dirige(vetorMov,maxVetor);
	percorre(vetorMov,posAtualVet);
	
	return 0;
}
