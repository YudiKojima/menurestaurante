//Alunos: Rhafael Da Cruz Starke e Roger Hideki Fujii Contato e Marcos Yudi Kojima Silva

#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <cstring>
#include <unistd.h>

using namespace std;

class NoCard {
    public:
    int IDProduto;
    char nome[20];
    float valor;
    NoCard* prox;
    
};

void inserirNoCard (NoCard* &lista, int &contadorProduto, char nom[20], float vlr) {
    NoCard* no = new NoCard();
    contadorProduto++;
    
    no->IDProduto = contadorProduto;
    strcpy(no->nome, nom);
    no->valor = vlr;
    no->prox = lista;
    lista = no;
}

void exibirCard (NoCard* lista) {
    
    cout << fixed << setprecision(2);
    while (lista != NULL) {
        cout << lista->IDProduto << ": " << lista->nome << "..................................R$ " << lista->valor << " \n";
        lista = lista->prox;
    }
    
    cout << endl;
}

class NoListaCliente {
    public:
        int IDCliente;
        NoListaCliente* prox;
};

void exibirListaCliente( NoListaCliente* lista) {
    
    cout << "\nLISTA DE CLIENTES: " << endl;
    while (lista != NULL) {
        cout << lista->IDCliente << endl;
        lista = lista->prox;
    }
}

void inserirCliente (NoListaCliente* &lista, int contadorCliente) {
    NoListaCliente* no = new NoListaCliente();
    
    no->IDCliente = contadorCliente;
    no->prox = lista;
    lista = no;
    
}

void removerCliente(NoListaCliente* &lista, int remover) {
    NoListaCliente* no1 = lista;
    NoListaCliente* no2 = NULL;
    
    if (no1 != NULL && no1->IDCliente == remover) {
        lista = no1->prox;
        delete no1;
        return;
    } else {
        while (no1 != NULL && no1->IDCliente != remover) {
            no2 = no1;
            no1 = no2->prox;
        }
        
        if (no1 == NULL) {
            return;
        }
        
        no2->prox = no1->prox;
        delete no1;
    }
}


class NoListaConsumo {
    public:
        int IDCliente;
        int IDProduto;
        NoListaConsumo* prox;
};

void inserirConsumo (NoListaConsumo* &lista, int value1, int value2) {
    NoListaConsumo* no = new NoListaConsumo();
    
    no->IDCliente = value1;
    no->IDProduto = value2;
    no->prox = lista;
    lista = no;
}

NoListaConsumo* buscaConsumo (NoListaConsumo* no, int id) {
    while (no != NULL && no->IDCliente != id) {
        no = no->prox;
    }
    
    return no;
}

float buscarSubconsumo (NoCard* no, int chave) {
    while (no != NULL && no->IDProduto != chave) {
        no = no->prox;
    }

    return no->valor;
}

float buscarConsumo (NoListaConsumo* no, int chave, NoCard* noCardapio) {
    float valorTotal = 0;
    while (no != NULL) {
        if (no->IDCliente == chave){
            valorTotal += buscarSubconsumo(noCardapio, no->IDProduto);
        }
        no = no->prox;
    }

    return valorTotal;
}

/*void removerConsumo (NoListaConsumo* &lista, int chave) {
    NoListaConsumo* no1 = lista;
    NoListaConsumo* no2 = NULL;
    
    if (no1 != NULL && n1->IDCliente == chave) {
        lista = no1->prox;
        delete no1;
        return;
    } else {
        while (no1 != NULL && no1->IDCliente != chave) {
            no2 = no1
            return;
        }
    }
}*/

class NoFilaPagar {
    public:
        int IDCliente;
        NoFilaPagar* prox;
        
        NoFilaPagar(int c) {
            IDCliente = c;
            prox = NULL;
        }
};

class FilaPagar {
    public:
        NoFilaPagar* inicio, *fim;
        int tamanho;
        
        FilaPagar() {
            inicio = fim = NULL;
            tamanho = 0;
        }
    
    void push(int id) {
        NoFilaPagar* no = new NoFilaPagar(id);
        tamanho++;
        
        if (fim == NULL) {
            inicio = fim = no;
            return;
        }
        
        fim->prox = no;
        fim = no;
    }
    
    void pop() {
        if (inicio == NULL) {
            return;
        }
        
        NoFilaPagar* no = inicio;
        inicio = inicio->prox;
        
        if (inicio == NULL) {
            fim = NULL;
        }
        
        delete no;
    }
    
    int front() {
        if (inicio != NULL) {
            return inicio->IDCliente;
        } else {
            cout << "ERROR: ";
            return 0;
        }
    }
};

int main(){
    
    NoCard* cardapio = NULL;
    NoListaCliente* listaCliente = NULL;
    NoListaConsumo* listaConsumoG = NULL;
    NoListaConsumo* listaConsumoP = NULL;
    FilaPagar fila;
    
    int opcao, pause;
    char name[20];
    float value;
    int contadorProduto = 0;
    int contadorCliente = 0;
    int idCliente;
    int idProduto;
    
    do{
        system("cls");
        cout << "\n\nCONTROLE DO RESTAURANTE\n" << endl;
        cout << "[1] Adicionar Item ao Cardápio." << endl;
        cout << "[2] Exibir Itens do Cardápio." << endl;
        cout << "[3] Adicionar Cliente." << endl;
        cout << "[4] Adicionar Item à Conta de Cliente." << endl;
        cout << "[5] Fechar Conta." << endl;
        cout << "[6] Atender Cliente." << endl;
        cout << "[0] EXIT." << endl;
        cout << "Opcao: ";
        cin >> opcao;
        cin.ignore();
        
        switch (opcao){
            case 1:
                system("cls");
                cout << "ADICIONAR ITEM AO CARDÁPIO\n" << endl;
                cout << "Nome do novo item: ";
                cin.get(name, 20);
                cin.ignore();
                cout << "Valor do novo item: ";
                cin >> value;
                cin.ignore();
                
                inserirNoCard(cardapio, contadorProduto, name, value);
                
                cout << "\nProduto Adicionado com Sucesso!" << endl;
                cout << "\n\nAperte [ENTER] para continuar..." << endl;
                pause = getc(stdin);
                break;
            case 2:
                system("cls");
                cout << "ITENS NO CARDÁPIO\n" << endl;
                
                exibirCard(cardapio);
                
                cout << "\nAperte [ENTER] para continuar..." << endl;
                pause = getc(stdin);
                break;
            case 3:
                system("cls");
                cout << "ADICIONAR CLIENTE\n" << endl;
                
                contadorCliente++;
                
                cout << "Adicionando Cliente..." << endl;
                inserirCliente(listaCliente, contadorCliente);
                sleep(1);
                
                cout << "\nCliente adicionado, id: " << contadorCliente << endl;
                
                exibirListaCliente(listaCliente);
                
                cout << "\n\nAperte [ENTER] para continuar..." << endl;
                pause = getc(stdin);
                break;
            case 4:
                system("cls");
                cout << "ADICIONAR ITEM À CONTA DE CLIENTE\n" << endl;
                
                cout << "ID do Cliente: ";
                cin >> idCliente;
                cin.ignore();
                
                cout << "ID do Produto: ";
                cin >> idProduto;
                cin.ignore();
                
                inserirConsumo(listaConsumoG, idCliente, idProduto);
                
                cout << "\nItem Adicionado com Sucesso!" << endl;
                cout << "\n\nAperte [ENTER] para continuar..." << endl;
                pause = getc(stdin);
                break;
            case 5:
                system("cls");
                cout << "FECHAR CONTA DO CLIENTE\n" << endl;
                
                cout << "ID do Cliente: ";
                cin >> idCliente;
                cin.ignore();
                
                fila.push(idCliente);
                
                removerCliente(listaCliente, idCliente);
                
                cout << "\n\nCliente Adicionado na Fila do Caixa Com Sucesso!" << endl;
                cout << "Aperte [ENTER] Para Continuar..." << endl;
                pause = getc(stdin);
                break;
            case 6:
                system("cls");
                cout << "CAIXA\n" << endl;

                cout << "Cliente a ser atendido: " << fila.front() << endl;
                idCliente = fila.front();
                fila.pop();

                cout << "Valor total: R$ " << buscarConsumo(listaConsumoG, idCliente, cardapio);


                pause = getc(stdin);
                break;
            case 0:
                system("cls");
                cout << "PROGRAMA ENCERRADO!" << endl;
                sleep(1);
                return 0;
                break;
            default:
                system("cls");
                cout << "\nComando Inválido!" << endl;
                sleep(2);
                break;
        }   
    }while(1);
}