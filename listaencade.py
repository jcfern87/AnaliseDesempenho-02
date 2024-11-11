# Aqui é o arquivo da lista encadeada.

# Esta classe define o Nó, que é o objeto que se junta com outros nós e define uma lista encadeada. Ele contém a sua própria informação (nesse caso, o número) e o endereço do próximo nó, ou o próximo item da lista.
class No:
    def __init__(self, data):
        self.data = data
        self.next = None

# Esta classe define a Lista Encadeada, que vai conter o nó cabeça, que por sua vez contém o endereço do próximo Nó, e assim por diante. A classe contém também as funções adição, remoção, e impressão.
class ListaEncadeada:
    # Define a própria lista e o atributo cabeça, que é o nó inicial da lista.
    def __init__(self):
        self.cabeca = None

    # Define a função de adição, que checa até o último Nó vazio e insere o nó com os dados do parâmetro. Ela não será usada para ler o arquivo, no enteanto, apenas para montar o array a partir do .txt.
    def adicionar(self, data):
        novo_no = No(data)
        if not self.cabeca:
            self.cabeca = novo_no
            return
        last = self.cabeca
        while last.next:
            last = last.next
        last.next = novo_no

    # Define a função que insere um nó em uma posição especificada.
    def inserir_posicao(self, data, posicao):
        novo_no = No(data)
        # Caso o nó a ser inserido seja na pposição zero, ele troca de lugares com o nó cabeça e fecha a função.
        if posicao == 0:
            novo_no.next = self.cabeca
            self.cabeca = novo_no
            return
        # Caso não, continua daqui.
        current = self.cabeca
        contador = 0
        while current and contador < posicao - 1:
            current = current.next
            contador += 1
        if current is None:
            print("Posição fora dos limites")
            return
        novo_no.next = current.next
        current.next = novo_no

    # Define a função de remover um valor (ou a primeira instância do valor encontrada na lista, caso haja mais de uma) especificado da lista (valor dos dados, não da posição).
    def remover(self, data):
        current = self.cabeca
        previous = None
        # Checa se o valor dos dados é o valor da instância do nó sendo checado.
        while current:
            if current.data == data:
                # Se for, e a instância do nó tiver um nó precedendo ela, então o atributo próximo do nó anterior se torna o próximo do nó sendo instanciado, efetivamente removendo o nó, já que ele não possui mais nenhuma referência a ele.
                if previous:
                    previous.next = current.next
                #  Caso não seja, o atributo próximo da instância do nó sendo checado se torna a cabeça da lista.
                else:
                    self.head = current.next
                return
            previous = current
            current = current.next
        # Caso o while acabe (isso significa que a lista acabou e o valor de current é None), será imprimido uma mensagem informando que o valor não foi encontrado.
        print(f"Valor {data} não encontrado na lista")

    # Esta função vai imprimir a lista. O parâmetro "end= ' '" quer dizer que ao final de cada impressão haverá um espaço, para indicar que cada número será impresso após o outro, até a lista inteira terminar de ser impressa.
    def print_list(self):
        current = self.cabeca
        while current:
            print(current.data, end=" ")
            current = current.next
        print()

# A próxima função irá fazer o trabalho de ler o documento .txt e criar uma lista com base nele.
def lerArquivo(arquivo):
    # Abre um arquivo especificado com a intenção de ler (r = reading).
    with open(arquivo, 'r') as arquivo:
        # Lê a lista inicial.
        valores_iniciais = list(map(int, arquivo.readline().strip().split()))

        # Inicializa a lista encadeada.
        lista_ligada = ListaEncadeada()
        for valor in valores_iniciais:
            lista_ligada.adicionar(valor)
        # Lê o número de ações.
        num_acoes = int(arquivo.readline().strip())
        
        # Processa cada ação.
        for _ in range(num_acoes):
            # Divide a linha que contém a ação em 3, criando um array com o tipo, número e posição, respectivamente.
            action_line = arquivo.readline().strip().split()
            action_type = action_line[0]
            number = int(action_line[1]) if len(action_line) >1 else None
            # Caso o array tenha apenas len = 2, a posição é None.
            position = int(action_line[2]) if len(action_line) > 2 else None
            
            if action_type == 'A':
                lista_ligada.inserir_posicao(number, position)
            elif action_type == 'R':
                lista_ligada.remover(number)
            elif action_type == 'P':
                lista_ligada.print_list()
            else:
                print(f"Ação desconhecida: {action_type}")

# Chamada da função com o nome do arquivo.
lerArquivo('arq.txt')
print('')
lerArquivo('arq2.txt')