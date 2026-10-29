#include <stdio.h>
#include <string.h>

#define MAX_ACOES 100
#define PLANEJADA 1
#define REALIZADA 2
#define CANCELADA 3

typedef struct {
    int codigo;
    char escola[100];
    char tema[100];
    char data[100];
    char publicoAlvo[100];
    char responsavel[100];
    int participantesPrevistos;
    int participantesEfetivos;
    int situacao;
} Acao;

void limparEntrada(void) {
    int caractere;

    while ((caractere = getchar()) != '\n' && caractere != EOF) {
    }
}

int lerInteiro(char mensagem[]) {
    int valor;
    int leitura;

    do {
        printf("%s", mensagem);
        leitura = scanf("%d", &valor);

        if (leitura != 1) {
            printf("Digite um número inteiro válido.\n");
            limparEntrada();
        } else {
            limparEntrada();
        }
    } while (leitura != 1);

    return valor;
}

void lerTexto(char mensagem[], char texto[], int tamanho) {
    int i;

    do {
        printf("%s", mensagem);

        if (fgets(texto, tamanho, stdin) == NULL) {
            texto[0] = '\0';
        } else {
            i = 0;
            while (texto[i] != '\0' && texto[i] != '\n') {
                i++;
            }

            if (texto[i] == '\n') {
                texto[i] = '\0';
            } else {
                limparEntrada();
            }
        }

        if (texto[0] == '\0') {
            printf("Este campo é obrigatório. Tente novamente.\n");
        }
    } while (texto[0] == '\0');
}

int dataValida(char data[]) {
    int dia;
    int mes;
    int ano;
    int i;

    if (strlen(data) != 10 || data[2] != '/' || data[5] != '/') {
        return 0;
    }

    for (i = 0; i < 10; i++) {
        if (i != 2 && i != 5 && (data[i] < '0' || data[i] > '9')) {
            return 0;
        }
    }

    dia = (data[0] - '0') * 10 + (data[1] - '0');
    mes = (data[3] - '0') * 10 + (data[4] - '0');
    ano = (data[6] - '0') * 1000 + (data[7] - '0') * 100 +
          (data[8] - '0') * 10 + (data[9] - '0');

    return dia >= 1 && dia <= 31 && mes >= 1 && mes <= 12 && ano >= 1;
}

int buscarIndicePorCodigo(Acao acoes[], int total, int codigo) {
    int i;

    for (i = 0; i < total; i++) {
        if (acoes[i].codigo == codigo) {
            return i;
        }
    }

    return -1;
}

void mostrarSituacao(int situacao) {
    if (situacao == PLANEJADA) {
        printf("Planejada");
    } else if (situacao == REALIZADA) {
        printf("Realizada");
    } else {
        printf("Cancelada");
    }
}

void mostrarAcao(Acao acao) {
    printf("\nCódigo: %d\n", acao.codigo);
    printf("Escola: %s\n", acao.escola);
    printf("Tema: %s\n", acao.tema);
    printf("Data prevista: %s\n", acao.data);
    printf("Público-alvo: %s\n", acao.publicoAlvo);
    printf("Responsável: %s\n", acao.responsavel);
    printf("Participantes previstos: %d\n", acao.participantesPrevistos);
    printf("Participantes efetivos: %d\n", acao.participantesEfetivos);
    printf("Situação: ");
    mostrarSituacao(acao.situacao);
    printf("\n");
}

int cadastrarAcao(Acao acoes[], int total) {
    Acao novaAcao;
    int codigoRepetido;

    if (total >= MAX_ACOES) {
        printf("Limite de ações atingido.\n");
        return total;
    }

    do {
        novaAcao.codigo = lerInteiro("Código da ação: ");
        codigoRepetido = buscarIndicePorCodigo(acoes, total, novaAcao.codigo) != -1;

        if (novaAcao.codigo <= 0) {
            printf("O código deve ser maior que zero.\n");
        } else if (codigoRepetido) {
            printf("Esse código já está cadastrado. Digite outro.\n");
        }
    } while (novaAcao.codigo <= 0 || codigoRepetido);

    lerTexto("Escola: ", novaAcao.escola, 100);
    lerTexto("Tema: ", novaAcao.tema, 100);

    do {
        lerTexto("Data prevista (DD/MM/AAAA): ", novaAcao.data, 100);
        if (!dataValida(novaAcao.data)) {
            printf("Data inválida. Use o formato DD/MM/AAAA.\n");
        }
    } while (!dataValida(novaAcao.data));

    lerTexto("Público-alvo: ", novaAcao.publicoAlvo, 100);
    lerTexto("Responsável: ", novaAcao.responsavel, 100);

    do {
        novaAcao.participantesPrevistos = lerInteiro("Quantidade prevista: ");
        if (novaAcao.participantesPrevistos < 0) {
            printf("A quantidade não pode ser negativa.\n");
        }
    } while (novaAcao.participantesPrevistos < 0);

    novaAcao.participantesEfetivos = 0;
    novaAcao.situacao = PLANEJADA;
    acoes[total] = novaAcao;
    total++;

    printf("Ação cadastrada com sucesso.\n");
    return total;
}

void listarAcoes(Acao acoes[], int total) {
    int i;

    if (total == 0) {
        printf("Ainda não há ações cadastradas.\n");
        return;
    }

    for (i = 0; i < total; i++) {
        mostrarAcao(acoes[i]);
    }
}

void pesquisarAcoes(Acao acoes[], int total) {
    int opcao;
    int codigo;
    int i;
    int encontradas = 0;
    char termo[100];

    if (total == 0) {
        printf("Ainda não há ações cadastradas.\n");
        return;
    }

    printf("\nPesquisar por:\n");
    printf("1 - Código\n");
    printf("2 - Escola\n");
    printf("3 - Tema\n");
    opcao = lerInteiro("Opção: ");

    if (opcao == 1) {
        codigo = lerInteiro("Código: ");
        i = buscarIndicePorCodigo(acoes, total, codigo);

        if (i == -1) {
            printf("Ação não encontrada.\n");
        } else {
            mostrarAcao(acoes[i]);
        }
    } else if (opcao == 2 || opcao == 3) {
        lerTexto(opcao == 2 ? "Nome exato da escola: " : "Tema exato: ", termo, 100);

        for (i = 0; i < total; i++) {
            if ((opcao == 2 && strcmp(acoes[i].escola, termo) == 0) ||
                (opcao == 3 && strcmp(acoes[i].tema, termo) == 0)) {
                mostrarAcao(acoes[i]);
                encontradas++;
            }
        }

        if (encontradas == 0) {
            printf("Nenhuma ação encontrada com esse termo.\n");
        }
    } else {
        printf("Opção de pesquisa inválida.\n");
    }
}

void atualizarSituacao(Acao acoes[], int total) {
    int codigo;
    int indice;
    int novaSituacao;
    int participantes;

    if (total == 0) {
        printf("Ainda não há ações cadastradas.\n");
        return;
    }

    codigo = lerInteiro("Código da ação: ");
    indice = buscarIndicePorCodigo(acoes, total, codigo);

    if (indice == -1) {
        printf("Ação não encontrada.\n");
        return;
    }

    printf("Nova situação:\n");
    printf("1 - Planejada\n");
    printf("2 - Realizada\n");
    printf("3 - Cancelada\n");
    novaSituacao = lerInteiro("Opção: ");

    if (novaSituacao == PLANEJADA) {
        acoes[indice].situacao = PLANEJADA;
        acoes[indice].participantesEfetivos = 0;
    } else if (novaSituacao == CANCELADA) {
        acoes[indice].situacao = CANCELADA;
        acoes[indice].participantesEfetivos = 0;
    } else if (novaSituacao == REALIZADA) {
        do {
            participantes = lerInteiro("Quantidade efetiva de participantes: ");
            if (participantes < 0) {
                printf("A quantidade não pode ser negativa.\n");
            }
        } while (participantes < 0);

        acoes[indice].situacao = REALIZADA;
        acoes[indice].participantesEfetivos = participantes;
    } else {
        printf("Situação inválida. Nenhuma alteração foi feita.\n");
        return;
    }

    printf("Situação atualizada com sucesso.\n");
}

void gerarResumo(Acao acoes[], int total) {
    int i;
    int planejadas = 0;
    int realizadas = 0;
    int canceladas = 0;
    int participantesEfetivos = 0;
    int previstosNasRealizadas = 0;
    double percentual = 0.0;

    for (i = 0; i < total; i++) {
        if (acoes[i].situacao == PLANEJADA) {
            planejadas++;
        } else if (acoes[i].situacao == REALIZADA) {
            realizadas++;
            participantesEfetivos += acoes[i].participantesEfetivos;
            previstosNasRealizadas += acoes[i].participantesPrevistos;
        } else {
            canceladas++;
        }
    }

    if (previstosNasRealizadas > 0) {
        percentual = (double) participantesEfetivos * 100 / previstosNasRealizadas;
    }

    printf("\nResumo geral\n");
    printf("Ações planejadas: %d\n", planejadas);
    printf("Ações realizadas: %d\n", realizadas);
    printf("Ações canceladas: %d\n", canceladas);
    printf("Participantes efetivos nas ações realizadas: %d\n", participantesEfetivos);
    printf("Participação em relação ao previsto nas ações realizadas: %.1f%%\n", percentual);
}

void exibirMenu(void) {
    printf("\n=== PSE em Ação ===\n");
    printf("1 - Cadastrar ação\n");
    printf("2 - Listar ações\n");
    printf("3 - Pesquisar ações\n");
    printf("4 - Atualizar situação\n");
    printf("5 - Gerar resumo\n");
    printf("0 - Encerrar\n");
}

int main(void) {
    Acao acoes[MAX_ACOES];
    int total = 0;
    int opcao;

    do {
        exibirMenu();
        opcao = lerInteiro("Escolha uma opção: ");

        switch (opcao) {
            case 1:
                total = cadastrarAcao(acoes, total);
                break;
            case 2:
                listarAcoes(acoes, total);
                break;
            case 3:
                pesquisarAcoes(acoes, total);
                break;
            case 4:
                atualizarSituacao(acoes, total);
                break;
            case 5:
                gerarResumo(acoes, total);
                break;
            case 0:
                printf("Programa encerrado.\n");
                break;
            default:
                printf("Opção inválida. Escolha uma opção do menu.\n");
        }
    } while (opcao != 0);

    return 0;
}
