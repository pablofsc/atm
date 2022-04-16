int wdata(bool rewr, string entr) {
	ofstream dados;
	
	if (rewr == false) {
		dados.open("dados.txt", fstream::app);
	}
	else {
		dados.open("dados.txt");
	}
	
	if (dados.is_open()) {
		dados << entr;
		dados.close();
	}
	else {
		cout << "Houve um erro na função wdata.";
		system("PAUSE");
	}
}

int wextr(bool novo, string nconta, float valor, string detalhes, string pos) {
	ofstream extrato;
	extrato.open(nconta + ".txt", fstream::app);
	
	if (extrato.is_open()) {
		if (novo == false) {
			detalhes.resize(35, ' ');
			time_t timenow = time(NULL);
			extrato << ctime(&timenow) << detalhes << " | " << pos << fixed << setprecision(2) << valor << endl;
			extrato.close();
		}
	}
	else {
		cout << "Houve um erro na função wextr.\n";
		system("PAUSE");
	}

	return 1;
}

int updata(bool isflo, string dtipo, string nconta, float nvflo, string nvstr) {
	ifstream dados;
	dados.open("dados.txt") ;
	string linha, towrite;
	
	if (dados.is_open()) {
		bool lendotipo = true, contacerta = false, primlinh = true;
		string tipo;
		
		while(getline(dados, linha)) {
			if (lendotipo == true) {
				tipo = linha;
				lendotipo = false;
			}
			else if (lendotipo == false) {
				if (tipo == "") {
					if (linha == nconta) {
						contacerta = true;
					}
					else {
						contacerta = false;
					}
				}
				else if (tipo == dtipo && contacerta == true) {
					if (isflo == true) {
						linha = to_string(nvflo);
					}
					else {
						linha = nvstr;
					}
				}
				
				lendotipo = true;
			}
			
			towrite += linha + "\n";
		}
		
		dados.close();
		
		wdata(true, towrite);
	}
	else {
		cout << "Houve um erro na função updata.";
		system("PAUSE");
	}
}

struct cliente {
	private:
		int linhatxt;
		string lnconta, lcpf, lnome, ldnasc, lsenha, lsexo;
		long double lsaldo;
	public:
		bool usado = false;
		
		void setinfo(bool escrever, int inlinha, int n, string incpf, string innome, string indnasc, string insexo, string insenha, float insaldo) {
			lnconta = to_string(n);
			lcpf = incpf;
			lnome = innome;
			ldnasc = indnasc;
			lsenha = insenha;
			lsaldo = insaldo;
			lsexo = insexo;
			linhatxt = inlinha;
			
			if (escrever == true) {
				wdata(false, "\n" + lnconta + "\nNOM\n" + lnome + "\nCPF\n" + lcpf + "\nDAT\n" + ldnasc + "\nSEX\n" + lsexo + "\nSAL\n" + to_string(lsaldo) + "\nSEN\n" + lsenha + "\n");
				wextr(true, lnconta, 0.0, "", "");
			}
			
			usado = true;
		}
		
		bool getinfo(bool mostrar, string pass) {
			if (usado == true && pass == lsenha) {
				if (mostrar == true) {
					cout << "Nome: " << lnome;
					cout << "\nCPF: " << lcpf;
					cout << "\nData de nascimento: " << ldnasc;
					cout << "\nSexo: ";
					if (lsexo == "f" || lsexo == "F") {
						cout << "Feminino";
					}
					else {
						cout << "Masculino";
					}
					cout << endl << endl;
				}
				return true;
			}
			else {
				return false;
			}
		}
		
		float getsaldo() {
			return lsaldo;
		}
		
		string getnome() {
			return lnome;
		}
		
		char getart() {
			if (lsexo == "F" || lsexo == "f") {
				return 'a';
			}
			else {
				return 'o';
			}
		}
		
		int depsaq(bool dep, float quantia) {
			if (dep == true) {
				lsaldo += quantia;
			}
			else if (dep == false) {
				if (quantia <= lsaldo) {
					lsaldo -= quantia;
				}
				else {
					cout << "\nNão há fundos suficientes para esta operação.\n";
					return 0;
				}
			}
			
			updata(true, "SAL", lnconta, lsaldo, "NULL");
			return 1;
		}
		
		int getcc() {
			return stoi(lnconta);
		}
		
		int rextr() {
			ifstream extrato;
			extrato.open(lnconta + ".txt");
			
			if (extrato.is_open()) {
				bool lendodata = true;
				string linha;
				
				cout << " DATA                     | DETALHES                            | VALOR\n";
				
				while (getline(extrato, linha)) {
					if (lendodata == true) {
						cout << " " << linha << " | ";
						lendodata = false;
					}
					else {
						cout << linha << endl;
						lendodata = true;
					}
				}
				
				cout << "\n                          | SALDO ATUAL                         | R$ " << lsaldo << "\n\n";
				extrato.close();
			}
			else {
				cout << "Houve um erro na função rextr. Criando novo arquivo de histórico...\n";
				wextr(true, lnconta, 0.0, "", "");
			}
		}		
};

cliente conta[99999];


int deletarconta(string nconta) {
	ifstream dados;
	dados.open("dados.txt") ;
	string linha, towrite, extr;
	
	if (dados.is_open()) {
		conta[stoi(nconta)].usado = false;
		
		extr = nconta + ".txt";
		bool lendotipo = true, contacerta = false, primlinh = true;
		string tipo;
		
		while(getline(dados, linha)) {
			if (lendotipo == true) {
				tipo = linha;
				lendotipo = false;
				
				if (contacerta == false && linha != "") {
					towrite += linha + "\n";
				}
			}
			else if (lendotipo == false) {
				if (tipo == "") {
					if (linha == nconta) {
						contacerta = true;
					}
					else {
						towrite += "\n";
						contacerta = false;
					}
				}
				
				if (contacerta == false) {
					towrite += linha + "\n";
				}
				
				lendotipo = true;
			}
		}
		
		dados.close();
		
		wdata(true, towrite);
		
		if (remove(extr.c_str()) != 0) {
    		cout << "Houve um erro na função deletarconta, remove(). O arquivo de extrato não foi removido."; 
    		system("PAUSE");
		}
		else {
			cout << "Conta excluída.\n\n";
		}	
	}
	else {
		cout << "Houve um erro na função deletarconta.";
		system("PAUSE");
	}
}

int rdata() {
	ifstream dados;
	string linha;
	
	//cout << "Lendo dados...\n\n";
	dados.open("dados.txt");
	
	if (dados.is_open()) {
		int nca, linhatxt, linhas = 0;
		string tipo, nconta, nome, cpf, dnasc, senha, sexo;
		float saldo;
		bool lendotipo;
		
		lendotipo = true;
		while(getline(dados, linha)) {
			linhas += 1;
			if (lendotipo == true) {
				tipo = linha;
				lendotipo = false;
			}
			else {
				if (tipo == "") {
					nca = stoi(linha);
					nconta = linha;
					linhatxt = linhas;
				}
				else if (tipo == "NOM") {
					nome = linha;
				}
				else if (tipo == "CPF") {
					cpf = linha;
				}
				else if (tipo == "DAT") {
					dnasc = linha;
				}
				else if (tipo == "SEX") {
					sexo = linha;
				}
				else if (tipo == "SAL") {
					saldo = stof(linha, NULL);
				}
				else if (tipo == "SEN") {
					senha = linha;
					conta[nca].setinfo(false, linhatxt, nca, cpf, nome, dnasc, sexo, senha, saldo);
					//cout << "Lida conta #" << nconta << endl;
				}
				
				lendotipo = true;
			}
		}
		
		dados.close();
	}
	else {
		//cout << "Houve um erro na função rdata. Criando novo dados.txt\n\n";
		wdata(false, "");
		system("PAUSE");
	}
}

void criarconta() {
	string cpf, nome, dnasc, senha, aux, sexo;
	int nconta;
	
	while(true) {
		nconta = rand() % 99999 + 9999;
		if (conta[nconta].usado == false) {
			break;
		}
	}
	
	cout << "\n\nCPF (Somente números): ";
	cin >> cpf;
	
	cout << "Nome: ";	
	cin.ignore();
	getline(std::cin, nome);
	
	cout << "Data de nascimento (DD/MM/AAAA): ";
	cin >> dnasc;
	
	cout << "Sexo (F/M): ";
	cin >> sexo;
	
	cout << "Crie uma senha: ";
	cin >> senha;
	
	conta[nconta].setinfo(true, 0, nconta, cpf, nome, dnasc, sexo, senha, 0.0);
	
	if (conta[nconta].usado == true) {
		cout << "\nO número da nova conta é " << nconta << "\n\n";
	}
}

bool chkcnt(int nconta) {
	if (nconta < 99999 && nconta >= 10000 && conta[nconta].usado == true) {
		return true;
	}
	else {
		return false;
	}
}

void printlogo(bool limpar, string subt) {
	if (limpar == true) {
		system("CLS");
	}
	cout << " ---------------------------------\n";
	cout << " | $$$$$$$   $$     $$  $$$$$$$  |\n";
	cout << " | $$    $$  $$     $$  $$    $$ |\n";
	cout << " | $$    $$  $$     $$  $$    $$ |\n";
	cout << " | $$$$$$$    $$   $$   $$$$$$$  |\n";
	cout << " | $$          $$ $$    $$    $$ |\n";
	cout << " | $$           $$$     $$    $$ |\n";
	cout << " | $$            $      $$    $$ |\n";
	cout << " ---------------------------------\n";
	cout << setw((34/2) + subt.length()/2) << right << subt << "\n\n";
}

