#include <stdio.h>
#include <string.h>

#define MAX 100

struct Acao {
    int codigo;
    char escola[50];
    char tema[50];
    char data[11];
    char publico[50];
    char responsavel[50];
    int previstos;
    int efetivos;
    int situacao; // 1 = planejada, 2 = realizada, 3 = cancelada
};

struct Acao acoes[MAX];
int total = 0;

void limparTela() {
    printf("\033[2J\033[H");
}

void limparBuffer() {
    int c;
    c = getchar();
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

void esperar() {
    printf("\nPressione ENTER para voltar ao menu...");
    getchar();
    limparTela();
}

int lerNumero() {
    int n, ok;
    ok = scanf("%d", &n);
    limparBuffer();
    while (ok != 1) {
        if (ok == EOF) {
            return 0;
        }
        printf("Valor invalido, digite um numero: ");
        ok = scanf("%d", &n);
        limparBuffer();
    }
    return n;
}

void lerTexto(char mensagem[], char texto[]) {
    int ok;
    printf("%s", mensagem);
    ok = scanf("%49[^\n]", texto);
    limparBuffer();
    while (ok != 1) {
        printf("Este campo e obrigatorio. Digite novamente: ");
        ok = scanf("%49[^\n]", texto);
        limparBuffer();
    }
}

int dataValida(char data[]) {
    int i, dia, mes, ano, dias;

    if (strlen(data) != 10) {
        return 0;
    }
    if (data[2] != '/' || data[5] != '/') {
        return 0;
    }
    for (i = 0; i < 10; i++) {
        if (i != 2 && i != 5) {
            if (data[i] < '0' || data[i] > '9') {
                return 0;
            }
        }
    }

    dia = (data[0] - '0') * 10 + (data[1] - '0');
    mes = (data[3] - '0') * 10 + (data[4] - '0');
    ano = (data[6] - '0') * 1000 + (data[7] - '0') * 100 + (data[8] - '0') * 10 + (data[9] - '0');

    if (ano < 1 || mes < 1 || mes > 12 || dia < 1) {
        return 0;
    }

    if (mes == 2) {
        if ((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0) {
            dias = 29;
        } else {
            dias = 28;
        }
    } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        dias = 30;
    } else {
        dias = 31;
    }

    if (dia > dias) {
        return 0;
    }
    return 1;
}

int buscarCodigo(int codigo) {
    int i;
    for (i = 0; i < total; i++) {
        if (acoes[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void mostrarAcao(int i) {
    printf("\nCodigo: %d\n", acoes[i].codigo);
    printf("Escola: %s\n", acoes[i].escola);
    printf("Tema: %s\n", acoes[i].tema);
    printf("Data prevista: %s\n", acoes[i].data);
    printf("Publico-alvo: %s\n", acoes[i].publico);
    printf("Responsavel: %s\n", acoes[i].responsavel);
    printf("Participantes previstos: %d\n", acoes[i].previstos);
    printf("Participantes efetivos: %d\n", acoes[i].efetivos);
    if (acoes[i].situacao == 1) {
        printf("Situacao: Planejada\n");
    } else if (acoes[i].situacao == 2) {
        printf("Situacao: Realizada\n");
    } else {
        printf("Situacao: Cancelada\n");
    }
}

void cadastrar() {
    struct Acao nova;
    char data[50];
    int ok;

    printf("=== CADASTRAR ACAO ===\n\n");

    if (total >= MAX) {
        printf("Limite de acoes atingido.\n");
        esperar();
        return;
    }

    printf("Codigo da acao: ");
    nova.codigo = lerNumero();
    while (nova.codigo <= 0 || buscarCodigo(nova.codigo) != -1) {
        if (nova.codigo <= 0) {
            printf("O codigo deve ser maior que zero. Digite de novo: ");
        } else {
            printf("Esse codigo ja esta cadastrado. Digite outro: ");
        }
        nova.codigo = lerNumero();
    }

    lerTexto("Escola: ", nova.escola);
    lerTexto("Tema: ", nova.tema);

    ok = 0;
    while (ok == 0) {
        lerTexto("Data prevista (DD/MM/AAAA): ", data);
        ok = dataValida(data);
        if (ok == 0) {
            printf("Data invalida!\n");
        }
    }
    strcpy(nova.data, data);

    lerTexto("Publico-alvo: ", nova.publico);
    lerTexto("Responsavel: ", nova.responsavel);

    printf("Quantidade prevista de participantes: ");
    nova.previstos = lerNumero();
    while (nova.previstos < 0) {
        printf("A quantidade nao pode ser negativa. Digite de novo: ");
        nova.previstos = lerNumero();
    }

    nova.efetivos = 0;
    nova.situacao = 1;
    acoes[total] = nova;
    total++;

    printf("\nAcao cadastrada com sucesso!\n");
    esperar();
}

void listar() {
    int i;

    printf("=== LISTA DE ACOES ===\n");

    if (total == 0) {
        printf("\nNenhuma acao cadastrada.\n");
    }
    for (i = 0; i < total; i++) {
        mostrarAcao(i);
    }
    esperar();
}

void pesquisar() {
    int opcao, codigo, i, achou;
    char busca[50];

    printf("=== PESQUISAR ACAO ===\n\n");

    if (total == 0) {
        printf("Nenhuma acao cadastrada.\n");
        esperar();
        return;
    }

    printf("1 - Por codigo\n");
    printf("2 - Por escola\n");
    printf("3 - Por tema\n");
    printf("Opcao: ");
    opcao = lerNumero();

    achou = 0;
    if (opcao == 1) {
        printf("Codigo: ");
        codigo = lerNumero();
        i = buscarCodigo(codigo);
        if (i != -1) {
            mostrarAcao(i);
            achou = 1;
        }
    } else if (opcao == 2) {
        lerTexto("Nome exato da escola: ", busca);
        for (i = 0; i < total; i++) {
            if (strcmp(acoes[i].escola, busca) == 0) {
                mostrarAcao(i);
                achou = 1;
            }
        }
    } else if (opcao == 3) {
        lerTexto("Tema exato: ", busca);
        for (i = 0; i < total; i++) {
            if (strcmp(acoes[i].tema, busca) == 0) {
                mostrarAcao(i);
                achou = 1;
            }
        }
    } else {
        printf("\nOpcao invalida!\n");
        esperar();
        return;
    }

    if (achou == 0) {
        printf("\nNenhuma acao encontrada.\n");
    }
    esperar();
}

void atualizar() {
    int codigo, i, opcao, qtd;

    printf("=== ATUALIZAR SITUACAO ===\n\n");

    if (total == 0) {
        printf("Nenhuma acao cadastrada.\n");
        esperar();
        return;
    }

    printf("Codigo da acao: ");
    codigo = lerNumero();
    i = buscarCodigo(codigo);

    if (i == -1) {
        printf("\nAcao nao encontrada.\n");
        esperar();
        return;
    }

    printf("\n1 - Planejada\n");
    printf("2 - Realizada\n");
    printf("3 - Cancelada\n");
    printf("Nova situacao: ");
    opcao = lerNumero();

    if (opcao == 1 || opcao == 3) {
        acoes[i].situacao = opcao;
        acoes[i].efetivos = 0;
        printf("\nSituacao atualizada com sucesso!\n");
    } else if (opcao == 2) {
        printf("Quantidade efetiva de participantes: ");
        qtd = lerNumero();
        while (qtd < 0) {
            printf("A quantidade nao pode ser negativa. Digite de novo: ");
            qtd = lerNumero();
        }
        acoes[i].situacao = 2;
        acoes[i].efetivos = qtd;
        printf("\nSituacao atualizada com sucesso!\n");
    } else {
        printf("\nSituacao invalida, nada foi alterado.\n");
    }
    esperar();
}

void resumo() {
    int i, planejadas = 0, realizadas = 0, canceladas = 0;
    int efetivos = 0, previstos = 0;
    float percentual = 0;

    printf("=== RESUMO ===\n\n");

    for (i = 0; i < total; i++) {
        if (acoes[i].situacao == 1) {
            planejadas++;
        } else if (acoes[i].situacao == 2) {
            realizadas++;
            efetivos = efetivos + acoes[i].efetivos;
            previstos = previstos + acoes[i].previstos;
        } else {
            canceladas++;
        }
    }

    if (previstos > 0) {
        percentual = (float) efetivos * 100 / previstos;
    }

    printf("Acoes planejadas: %d\n", planejadas);
    printf("Acoes realizadas: %d\n", realizadas);
    printf("Acoes canceladas: %d\n", canceladas);
    printf("Participantes efetivos (acoes realizadas): %d\n", efetivos);
    printf("Percentual em relacao ao previsto: %.1f%%\n", percentual);
    esperar();
}

int main() {
    int opcao;

    limparTela();
    do {
        printf("=== PSE EM ACAO ===\n\n");
        printf("1 - Cadastrar acao\n");
        printf("2 - Listar acoes\n");
        printf("3 - Pesquisar acoes\n");
        printf("4 - Atualizar situacao\n");
        printf("5 - Gerar resumo\n");
        printf("0 - Sair\n\n");
        printf("Escolha: ");
        opcao = lerNumero();
        limparTela();

        if (opcao == 1) {
            cadastrar();
        } else if (opcao == 2) {
            listar();
        } else if (opcao == 3) {
            pesquisar();
        } else if (opcao == 4) {
            atualizar();
        } else if (opcao == 5) {
            resumo();
        } else if (opcao == 0) {
            printf("Programa encerrado.\n");
        } else {
            printf("Opcao invalida!\n");
            esperar();
        }
    } while (opcao != 0);

    return 0;
}
