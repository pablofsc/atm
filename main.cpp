// 27/05/2019 - 31/05/2019
// Necess�rio usar o seguinte comando nas op��es de compilador: -std=c++11

#include "header.hpp"
#include "declarations.cpp"

int main() {
	system("TITLE PVR");
	setlocale(LC_ALL, "portuguese");
	srand(time(0)*time(0)*time(0));
	
	bool logado = false;
	int user, op, destino;
	string pass, straux;
	long double flaux;
	char chop, opaux;
	
	while(true) {
		rdata();
		
		if (logado == false) {
			printlogo(true, "LOGIN");
			cout << "\t1. Acessar conta\n\t2. Criar conta\n\n>>> ";
			chop = getch();
			cout << chop;
			
			switch(chop) {
				case '1':
					cout << "\n\nConta: ";
					cin >> user;
					
					cout << "Senha: ";
					cin >> pass;
					
					if (user < 99999) {
						if (conta[user].getinfo(false, pass) == false) {
							cout << "\nConta inexistente ou senha incorreta.\n\n";
							system("PAUSE");
						}
						else {
							cout << endl;
							logado = true;
						}
					}
					else {
						cout << "\nConta inv�lida!\n";
						system("PAUSE");
					}
					break;
					
				case '2':
					criarconta();
					system("PAUSE");
					break;
					
			}
		}
		else if (logado == true) {
			printlogo(true, "Conta #" + to_string(conta[user].getcc()));
			cout << "Bem vind" << conta[user].getart() << ", " << conta[user].getnome() << ".\n\nSaldo em conta corrente: R$ " << fixed << setprecision(2) << conta[user].getsaldo();
			cout << "\n\n\t1. Dep�sito\n\t2. Saque\n\t3. Transfer�ncia\n\t4. Extrato\n\t5. Alterar informa��es\n\t6. Sair\n\n>>> ";
			chop = getch();
			
			switch(chop) {
				case '1':
					printlogo(true, "DEP�SITO");
					cout << "Quantia: R$ ";
					cin >> flaux;
					
					if (flaux > 0) {
						if (flaux <= 1000000000) {
							if (conta[user].depsaq(true, flaux) == 1) {
								wextr(false, to_string(user), flaux, "Dep�sito", "R$ +");
								cout << "\nDep�sito realizado com sucesso.\n\n";
							}
						}
						else {
							cout << "\nN�meros maiores de um bilh�o n�o s�o aceitos.\n\n";
						}
					}
					else {
						cout << "\nDep�sito cancelado.\n\n";
					}
					system("PAUSE");
					break;
					
				case '2':
					printlogo(true, "SAQUE");
					cout << "Quantia: R$ ";
					cin >> flaux;
					
					if (flaux > 0 && flaux <= 1000000000) {
						if (flaux <= 1000000000) {
							if (conta[user].depsaq(false, flaux) == 1) {
								wextr(false, to_string(user), flaux, "Saque", "R$ -");
								cout << "\nSaque realizado com sucesso.\n\n";
							}
						}
						else {
							cout << "\nN�meros maiores de um bilh�o n�o s�o aceitos.\n\n";
						}
					}
					else {
						cout << "\nSaque cancelado.\n\n";
					}
					system("PAUSE");
					break;
					
				case '3':
					printlogo(true, "TRANSFER�NCIA");
					
					cout << "Conta destino: ";
					cin >> destino;
					
					if (destino == 0) {
						cout << "\nTransfer�ncia cancelada.\n\n";
						system("PAUSE");
						break;
					}
					
					cout << "Quantia: R$ ";
					cin >> flaux;
					
					if (flaux <= 0) {
						cout << "\nSomente valores positivos s�o permitidos para transfer�ncias.\n\n" ;
					}
					else {
						if (chkcnt(destino) == false) {
							cout << "\nA conta destino n�o existe.\n";
						}
						else {
							if (conta[user].getsaldo() < flaux) {
								cout << "\nN�o h� saldo suficiente para esta transa��o.";
							}
							else {
								if (conta[user].depsaq(false, flaux) == 1) {
									if (conta[destino].depsaq(true, flaux) == 1) {
										wextr(false, to_string(user), flaux, "Transfer�ncia para a conta #" + to_string(destino), "R$ -");
										wextr(false, to_string(destino), flaux, "Transfer�ncia da conta #" + to_string(user), "R$ +");
										cout << "\nTransa��o realizada com sucesso.\n";
									}
								}
								else {
									cout << "\nHouve um erro na transa��o.";
								}
							}
						}
					}
					system("PAUSE");
					break;
				
				case '4':
					printlogo(true, "EXTRATO");
					conta[user].rextr();
					system("PAUSE");
					break;
					
				case '5':
					printlogo(true, "ALTERA��O DE INFORMA��ES");
					conta[user].getinfo(true, pass);
					cout << "\t1. Alterar nome\n\t2. Alterar CPF\n\t3. Alterar data de nascimento\n\t4. Alterar sexo\n\t5. Alterar senha\n\t6. Excluir conta\n\t7. Voltar\n\n>>> ";
					opaux = getch();
					printlogo(true, "ALTERA��O DE INFORMA��ES");
					
					switch(opaux) {
						case '1':
							conta[user].getinfo(true, pass);
							cout << "Para cancelar, insira 0.\n\n";
							cout << "Novo nome: ";
							cin >> straux;
							
							if (straux == "0") { 
								cout << "\nAltera��o cancelada.\n\n";
							}
							else {
								updata(false, "NOM", to_string(user), 0.0, straux);
							}
							
							system("PAUSE");
							break;
							
						case '2':
							conta[user].getinfo(true, pass);
							cout << "Para cancelar, insira 0.\n\n";
							cout << "Novo CPF: ";
							cin >> straux;
							
							if (straux == "0") { 
								cout << "\nAltera��o cancelada.\n\n";
							}
							else {							
								updata(false, "CPF", to_string(user), 0.0, straux);
							}
							
							system("PAUSE");
							break;
							
						case '3':
							conta[user].getinfo(true, pass);
							cout << "Para cancelar, insira 0.\n\n";
							cout << "Nova data de nascimento: ";
							cin >> straux;
							
							if (straux == "0") { 
								cout << "\nAltera��o cancelada.\n\n";
							}
							else {
								updata(false, "DAT", to_string(user), 0.0, straux);
							}
							
							system("PAUSE");
							break;
							
						case '4':
							conta[user].getinfo(true, pass);
							cout << "Novo sexo (F/M): ";
							cin >> straux;
							
							if (straux == "f" || straux == "F" || straux == "m" || straux == "M") {
								updata(false, "SEX", to_string(user), 0.0, straux);
								cout << "\nAltera��o conclu�da.\n\n";
							}
							else {
								cout << "\nAltera��o cancelada.\n\n";
							}
							
							system("PAUSE");
							break;
							
						case '5':
							conta[user].getinfo(true, pass);
							cout << "Para cancelar, insira 0.\n\n";
							cout << "Senha antiga: ";
							cin >> straux;
							
							if (straux == "0") { 
								cout << "\nAltera��o cancelada.\n\n";
								break;
							}
							else if (straux == pass) {
								cout << "Nova senha: ";
								cin >> straux;
								
								updata(false, "SEN", to_string(user), 0.0, straux);
								break;
							}
							else {
								cout << "\nSenha incorreta.\n";
							}
							
							system("PAUSE");
							break;
							
						case '6':
							conta[user].getinfo(true, pass);
							cout << "Tem certeza? S/N: ";
							cin >> straux;
							
							if (straux == "S" || straux == "s") {
								cout << "Insira sua senha: ";
								cin >> straux;
								
								if (straux == pass) {
									deletarconta(to_string(user));
									logado = false;
								}
								else {
									cout << "\n\nSenha incorreta. Exclus�o cancelada.\n\n";
								}
							}
							else {
								cout << "\nExclus�o cancelada.\n\n";
							}
							system("PAUSE");
							break;
							
						case '7':
							break;
					}
					
					break;
					
				case '6':
					logado = false;
					break;
					
			}
		}
	}
	
	return 0;
}
