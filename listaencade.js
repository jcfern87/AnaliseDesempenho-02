const fs = require("fs");

class No {
  constructor(data) {
    this.data = data;
    this.prox = null;
  }
}

class ListaEncade {
  constructor() {
    this.head = null;
  }

  // Aqui jaz a função de inserir um nó em qualquer posição desejada na lista.
  inserir(data, posicao) {
    const novoNo = new No(data);

    // Caso a posição ser a primeira ou não existir cabeça, o novo nó será a cabeça.
    if (posicao === 0 || !this.head) {
      novoNo.prox = this.head;
      this.head = novoNo;
      return;
    }

    let atual = this.head;
    for (let index = 0; index < posicao - 1 && atual.prox; index++) {
      atual = atual.prox;
    }
    novoNo.prox = atual.prox;
    atual.prox = novoNo;
  }

  remover(data) {
    // Se não houver cabeça, não há nada a ser removido.
    if (!this.head) {
      console.error("Não há nada na lista a ser removido");
      return;
    }

    if (this.head.data === data) {
      this.head = this.head.prox;
      return;
    }

    let atual = this.head;
    while (atual.prox && atual.prox.data !== data) {
      atual = atual.prox;
    }

    if (atual.prox) {
      atual.prox = atual.prox.prox;
    }
    console.error("O nó que está tentando remover não existe.");
  }

  imprimir() {
    let atual = this.head;
    let resultado = "";
    while (atual) {
      resultado += atual.data + " ";
      atual = atual.prox;
    }
    console.log(resultado.trim());
  }
}

class leitorTxt {
  constructor() {
    this.lista = new ListaEncade();
  }

  lerArquivo(nomeArq) {
    fs.readFile(nomeArq, "utf8", (err, data) => {
      if (err) {
        console.error("Erro ao ler o arquivo:", err);
        return;
      }

      const linhas = data
        .split("\n")
        .map((linha) => linha.trim())
        .filter((linha) => linha);

      // A partir daqui, incializa-se a lista com a primeira linha
      const valoresIniciais = linhas[0].split(" ").map(Number);
      valoresIniciais
        .reverse()
        .forEach((valor) => this.lista.inserir(valor, 0));

      // número de ações
      const numAcoes = parseInt(linhas[1]);

      // Processar cada ação
      for (let index = 0; index < 2 + numAcoes; index++) {
        const [acao, num, pos] = linhas[index].split(" ");

        if (acao === "A") {
          this.lista.inserir(parseInt(num), parseInt(pos));
        } else if (acao === "R") {
          this.lista.remover(parseInt(num));
        } else if (acao === "P") {
          this.lista.imprimir();
        }
      }
    });
  }
}

const leitor = new leitorTxt();
leitor.lerArquivo("arq-novo.txt");
