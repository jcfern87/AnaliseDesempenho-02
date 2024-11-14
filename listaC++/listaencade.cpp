#include <iostream>
#include <locale.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class No
{
private:
public:
    int data; // Dado do nó
    No *prox;

    No(int data)
    {
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
    listaEnc()
    {
        this->head = nullptr;
    };

    // Função que adiciona os Nós a partir do final
    void addFim(int data)
    {
        No *novoNo = new No(data);
        if (head == nullptr)
        {
            head = novoNo;
            return;
        }
        No *temp = head;
        while (temp->prox != nullptr)
        {
            temp = temp->prox;
        }
        temp->prox = novoNo;
    }

    // Função inserir em posição
    void inserir(int data, int posicao)
    {
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
    void remove(int data)
    {
        No *temp = head;
        while (temp != nullptr)
        {
            if (temp->prox == nullptr)
            {
                break;
            }
            if (temp->prox->data == data)
            {
                temp->prox = temp->prox->prox;
                return;
            }
            temp = temp->prox;
        }
        cout << "O nó que você está tentando remover não existe." << endl;
    }

    void printList()
    {
        No *temp = head;
        cout << "{ ";
        while (temp != nullptr)
        {
            cout << temp->data << ", ";
            temp = temp->prox;
        }
        cout << "}" << endl;
    }
};

class leitorTxt
{
public:
    listaEnc lista;

    void lerArq(const std::string &arquivo)
    {
        std::ifstream file(arquivo);
        if (!file.is_open())
        {
            std::cerr << "Houve um erro ao abrir o arquivo." << std::endl;
            return;
        }

        std::string linha;
        std::getline(file, linha); // Lista inicial

        std::istringstream initialStream(linha);
        int valor;
        while (initialStream >> valor)
        {
            lista.addFim(valor);
        }

        std::getline(file, linha); // Segunda linha, número de ações
        int numAcoes = std::stoi(linha);

        for (int i = 0; i < numAcoes; ++i)
        {
            std::getline(file, linha);
            std::istringstream actionStream(linha);

            std::string acao;
            int num, pos;
            actionStream >> acao;

            if (acao == "A")
            {
                actionStream >> num >> pos;
                lista.inserir(num, pos);
            }
            else if (acao == "R")
            {
                actionStream >> num;
                lista.remove(num);
            }
            else if (acao == "P")
            {
                lista.printList();
            }
        }

        file.close();
    }
};

int main()
{

    leitorTxt leitor;
    leitor.lerArq("arq-novo.txt");
    return 0;
}