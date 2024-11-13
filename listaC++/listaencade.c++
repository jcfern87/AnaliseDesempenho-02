#include <iostream> 
using namespace std;

class No
{
private:
public:
    int data; //Dado do nó
    No *prox;

    No(int data) {
        this->data = data;
        this->prox = nullptr;
    }
};

class listaEnc 
{
private:
    No *head;
public:
    // Construtor da classe
    listaEnc () {
        this->head = nullptr;
    };

    // Função que adiciona os Nós a partir do final
    void addFim(int data) {
        No *novoNo = new No(data);
        if (head == nullptr) {
            head = novoNo;
            return;
        }
        No *temp = head;
        while (temp->prox != nullptr) {
            temp = temp->prox;
        }
        temp->prox = novoNo;
    }
    
    // Função inserir em posição
    void inserir(int data, int posicao) {
        No *novoNo = new No(data);
        No *temp = head;
        int cont = 0;
        while (temp != nullptr)
        {
            if (cont == posicao - 1)
            {
                novoNo->prox = temp->prox;
                temp->prox = novoNo;
                return;
            }
            cont++;
            temp = temp->prox;
        }
        string msg = "A posição que está tentando inserir o dado não existe.";
        cout << msg << endl;
    }

    // Função que remove um nó a partir de seus dados
    void remove(int data) {
        No *temp = head;
        while (temp != nullptr) {
            if (temp->prox->data == data)
            {
                temp->prox = temp->prox->prox;
                return;
            }
            temp = temp->prox;
        } 
        cout << "O nó que você está tentando remover não existe." << endl;
    }

    void printList() {
        No *temp = head;
        while (temp != nullptr)
        {
            cout << temp->data << "";
            temp = temp->prox;
        }
        cout << endl;
    }

};

int main() {
    listaEnc lista;

    lista.addFim(1);
    lista.addFim(2);
    lista.addFim(3);
    lista.addFim(4);
    lista.addFim(5);

    cout << "Lista original: "; 
    lista.printList();

    lista.remove(2);
    lista.remove(4);

    cout << "Lista sem os números ímpares: ";
    lista.printList();

    lista.inserir(2, 1);
    lista.inserir(4, 3);

    cout << "Lista de volta ao normal: ";

}



