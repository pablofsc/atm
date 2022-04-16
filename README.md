# Caixa Eletrônico em C++
Simula um caixa eletrônico.

Trabalho de Linguagens e Técnicas de Programação II. Feito em maio de 2019.

Só funciona no Windows devido à biblioteca conio.h e requer C++ 11. (inserir -std=c++11 nas opções do compilador)

## Descrição das funções:
```c
wdata(bool rewr, string entr): escreve o conteúdo de entr no arquivo dados.txt
	rewr: caso a função esteja sendo chamada para uma atualização completa do arquivo
	entr: conteúdo a ser escrito no arquivo

wextr(bool novo, string nconta, float valor, string detalhes, string pos): cria e adiciona infomações ao arquivo de extrato da conta nconta
	novo: se a conta acabou de ser criada (true) ou não (false). neste caso o arquivo de extrato é vazio
	nconta: número da conta a qual o extrato se refere
	valor: valor da movimentação a ser registrada
	detalhes: descrição da movimentação
	pos: se a transação colocou ou tirou dinheiro, "prefixo" do valor ("R$ +" ou "R$ -")

updata(bool isflo, string dtipo, string nconta, float nvflo, string nvstr): atualiza informações no arquivo dados.txt
	isflo: se o dado a ser atualizado é float (true) ou string (false)
	dtipo: tipo da informação a ser alterada
	nvflo: novo valor float (caso o valor a ser alterado não seja float, esse argumento é ignorado)
	nvstr: novo valor string (caso o valor a ser alterado não seja string, esse argumento é ignorado)

struct cliente: estrutura/classe de cliente. as variáveis aqui começam com l de loaded.
	setinfo(bool escrever, int inlinha, int n, string incpf, string innome, string indnasc, string insexo, string insenha, float insaldo): configura uma nova conta ou carrega conta do dados.txt
		escrever: escreve os conteúdos no dados.txt - true quando uma conta acabou de ser criada, false quando a conta está sendo carregada do dados.txt
		inlinha: linha na qual as informações dessa conta começam dentro do dados.txt - eu acho que acabei não usando isso em nada
		n: numero da conta
		o resto dos argumentos sao auto-explicativos

	getinfo(bool mostrar, string pass): imprime informações sobre a conta na tela.
		mostrar: mostra ou nao as informações na tela. no inicio era util, agora nao serve pra nada
		pass: senha, se estiver errada a funcao retorna false. tambem nao serve pra muita coisa agora, mas antes servia, foi uma das primeiras funcoes que fiz

	getsaldo(): retorna o saldo da conta

	getnome(): retorna o nome do cliente

	getart(): retorna o artigo a ser usado em palavras não-neutras (bem vindo, bem vinda)

	depsaq(bool dep, float quantia): funcao de depositos e saques
		dep: se true, performa um deposito, se false, performa um saque
		quantia: quantia a ser depositada ou sacada

	getcc(): retorna o numero da conta corrente

	rextr(): lê o extrato (lnconta.txt), faz as formatações e imprime na tela 

cliente conta[99999]: declara 100.000 contas. por conta da função que cria contas, somente numeros entre 9999 e 99999 são usados, portanto a quantidade máxima de contas no programa é 10.000.

deletarconta(string nconta): deleta a conta #nconta, excluindo as informações do dados.txt e o arquivo de extrato nconta.txt. baseada na função updata.
	nconta: numero da conta a ser deletada

rdata(): lê e interpreta o arquivo dados.txt, carregando as informações na memória. chamado sempre que o usuário volta para o menu principal, para garantir que os dados estejam sempre atualizados

criarconta(): cria uma conta com número pseudoaleatório, gerado pela função rand()

chkcnt(int nconta): checa de nconta existe
	nconta: conta a ser checada

printlogo(bool limpar, string subt): imprime o logotipo do banco na tela e um subtítulo centralizado
	limpar: se true, limpa a tela antes de imprimir
	subt: subtítulo 

main(): quase todo código relacionado à interface está aqui
```