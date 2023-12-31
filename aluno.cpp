#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream> 
#include <iomanip>

#define TRACO "---------------------------------------------------------------------------------------------------"
using namespace std;

class Aluno {
    private:
        string nome;
        string email;
        int nota1;
        int nota2;
    public:
    ~Aluno(){

    }
    Aluno(){
        nome = "";
        email = "";
        nota1 = 0;
        nota2 = 0;
    }
    Aluno(string _nome, string _email, int _nota1, int _nota2){
        nome = _nome;
        email = _email;
        nota1 = _nota1;
        nota2 = _nota2;
    }
    string getNome();
    string getEmail();
    int getNota1();
    int getNota2();

    void setNome(string _nome);
    void setEmail(string _email);
    void setNota1(int _nota1);
    void setNota2(int _nota2);
};
string Aluno :: getNome(){
    return nome;
}
string Aluno :: getEmail(){
    return email;
}
int Aluno :: getNota1(){
    return nota1;
}
int Aluno :: getNota2(){
    return nota2;
}
void Aluno :: setNome(string _nome){
    nome = _nome;
}
void Aluno :: setEmail(string _email){
    email = _email;
}
void Aluno :: setNota1(int _nota1){
    nota1 = _nota1;
}
void Aluno :: setNota2(int _nota2){
    nota2 = _nota2;
}

class BancoDeDados {
public:
    static vector<Aluno> recuperarDados(string nomeArquivo) {
        ifstream entrada;

        entrada.open(nomeArquivo, ios_base::in);
        
        vector<Aluno> alunos;
        string nome, email, nota;
        int nota1, nota2;
        if (entrada.is_open()) {
            string linha;

            while (getline(entrada, linha)) {
                istringstream ss(linha);
                
                getline(ss, nome, ',');
                getline(ss, email, ',');
                
                getline(ss, nota, ',');
                nota1 = stoi(nota);
                
                getline(ss, nota, ',');
                nota2 = stoi(nota);

                Aluno novoAluno(nome, email, nota1, nota2);
                alunos.push_back(novoAluno);        
            }
        
            entrada.close(); // Close the input file here
        } else {
            cout << "Erro ao abrir o arquivo" << endl;
        }
        return alunos;
    }

    static void salvarDadosAluno(Aluno& aluno, string nomeArquivo){
        ofstream saida;
        saida.open(nomeArquivo, ios_base::app);
        
        if (saida.is_open()) {
            
            saida << aluno.getNome() << "," << aluno.getEmail()  << "," << aluno.getNota1()  << "," << aluno.getNota2() << endl;
            
            saida.close();
        } else {
            cout << "Erro ao abrir o arquivo" << endl;
        }
    }
    static void salvarDadosTudo(vector<Aluno>& dados, string nomeArquivo){
        ofstream saida;
        saida.open(nomeArquivo, ios_base::out);
        
        if (saida.is_open()) {
            for (Aluno& aluno: dados) {
                saida << aluno.getNome() << "," << aluno.getEmail()  << "," << aluno.getNota1()  << "," << aluno.getNota2() << endl;
            }
            saida.close();
        } else {
            cout << "Erro ao abrir o arquivo" << endl;
        }
    }
};

//Prototipos funções
void inserir(vector<Aluno>& alunos, string nomeArquivo);
int buscarAluno(vector<Aluno>& alunos, string nome_aluno);
void alterarAluno(vector<Aluno>& alunos, string nomeArquivo);
void excluirAluno(vector<Aluno>& alunos, string nomeArquivo);
void listarAlunos(vector<Aluno>& alunos);
//Prototipos funções

int main(){
    bool continuar = true;
    int op;
    string nomeArquivo = "alunos.txt";

    vector<Aluno> alunos = BancoDeDados :: recuperarDados(nomeArquivo);
    do
    {
        cout << "Cadastro de aluno" << endl;
        cout << "1. Incluir aluno"<< endl;
        cout << "2. Alterar aluno"<< endl; 
        cout << "3. Excluir aluno"<< endl; 
        cout << "4. Listar " << endl; 
        cout << "0. Sair" <<endl;
        cin>>op;
        switch (op)
        {
        case 1:
            inserir(alunos, nomeArquivo);
            break;
        case 2:
            alterarAluno(alunos, nomeArquivo);
            break;
        case 3:
            excluirAluno(alunos, nomeArquivo);
            break;
        case 4:
            listarAlunos(alunos);
            break;
        case 0:
            continuar=false;
            break;
        default:
            break;
        }
    } while (continuar);
    
}
void inserir(vector<Aluno>& alunos, string nomeArquivo){
    string nome;
    string email;
    int nota1;
    int nota2;
    int index;
    do
    {
        cout << "Digite o nome do aluno: " << endl;
        cin>>nome;
        index = buscarAluno(alunos, nome);
        if(index != -1){
            cout << "Ops! Aluno já existe no banco de dados." << endl;
            nome = "";
        }
    } while (nome == "");
    
    cout << "Digite o email do aluno: " << endl;
    cin >> email;
    do
    {
        cout << "Digite a nota 1: [0-100]" << endl;
        cin >> nota1;
    } while (nota1 < 0 || nota1 > 100);
    
    do
    {
        cout << "Digite a nota 2: [0-100]" << endl;
        cin >> nota2;
    } while (nota2 < 0 || nota2 > 100);
    
    Aluno novoAluno(nome, email, nota1, nota2);
    alunos.push_back(novoAluno);
    BancoDeDados :: salvarDadosAluno(novoAluno, nomeArquivo);
}

void alterarAluno(vector<Aluno>& alunos, string nomeArquivo)
{
    bool sair = true;
    char opcao;
    string nome;
    Aluno aluno;
    int index;

    cout << "Insira o nome do aluno que deseja alterar: " << endl;
    cin>>nome;
    index = buscarAluno(alunos, nome);
    if (index >= 0){
        aluno = alunos[index];
        cout  << endl ;
        cout << "Aluno: " << aluno.getNome() << endl;
        cout << "Email: " << aluno.getEmail() << endl;
        cout << "Nota 1: " << aluno.getNota1() << endl;
        cout << "Nota 2: " << aluno.getNota2() << endl;

        string email;
        int nota;

        cout << "Deseja alterar o email? (s/n) ";
        cin >> opcao;
        if (opcao == 's'){
            cout << "Digite o email: " << endl;
            cin >> email;
            alunos[index].setEmail(email);
        }
            
        cout << "Deseja alterar a nota 1? (s/n) ";
        cin >> opcao;
        if (opcao == 's'){
            do{
                cout << "Digite a nota 1: [0-100]" << endl;
                cin >> nota;
            } while (nota < 0 || nota > 100);
            alunos[index].setNota1(nota);
        }
            
        cout << "Deseja alterar a nota 2? (s/n) ";
        cin >> opcao;
        if (opcao == 's'){
            do{
                cout << "Digite a nota 1: [0-100]" << endl;
                cin >> nota;
            } while (nota < 0 || nota > 100);
            alunos[index].setNota2(nota);
        }
        BancoDeDados :: salvarDadosTudo(alunos, nomeArquivo);
    }
    else
    {
        cout << "Aluno não encontrado." << endl;
    }
}
int buscarAluno(vector<Aluno>& alunos, string nome_aluno)
{
    int qtd_alunos = alunos.size();
    for (int i = 0; i < qtd_alunos; i++)
    {
        if (nome_aluno == alunos[i].getNome())
            return i;
        
    }
    return -1;
}
void excluirAluno(vector<Aluno>& alunos, string nomeArquivo){
        string nome;
        cout << "Insira o nome do aluno que deseja excluir: ";
        cin>>nome;
        int indice = buscarAluno(alunos, nome);

        if (indice != -1){
            alunos.erase(alunos.begin() + indice);
            cout << "Aluno removido com sucesso!" << endl;

            BancoDeDados :: salvarDadosTudo(alunos, nomeArquivo);
        }
        else{
            cout << "Aluno não encontrado, portanto nenhum aluno foi removido." << endl;
        }
}
void listarAlunos(vector<Aluno>& alunos){
    cout << TRACO << endl;
    cout << left << setw(40) << "NOME" << setw(16) << "NOTA 1" << setw(16) << "NOTA 2"  << endl;
    cout << TRACO << endl;

    for (Aluno &aluno : alunos)
        cout << left << setw(40) << aluno.getNome() << setw(16) << setprecision(2) << aluno.getNota1() << setw(16) << setprecision(2) << aluno.getNota2() << endl;
    
    cout << TRACO << endl;

}