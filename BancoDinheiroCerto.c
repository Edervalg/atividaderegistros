#include <stdio.h>
#include <string.h>

#define MAX_CONTAS 100

typedef struct {
    int numeroConta;
    char nome[100];
    char cpf[15];
    char telefone[20];
    float saldo;
} Conta;

// Função de busca
int buscarConta(Conta cadastro[], int totalContas, int numeroConta) {
    if (totalContas == 0)
        return -1;

    for (int i = 0; i < totalContas; i++) {
        if (cadastro[i].numeroConta == numeroConta)
            return i;
    }

    return -2;
}

// Procedimento para cadastrar nova conta
void cadastrarConta(Conta cadastro[], int *totalContas, int numeroConta) {
    if (*totalContas >= MAX_CONTAS) {
        printf("Cadastro cheio. Não é possível adicionar mais contas.\n");
        return;
    }

    int pos = buscarConta(cadastro, *totalContas, numeroConta);
    if (pos >= 0) {
        printf("Número de conta já cadastrado. Cadastro não realizado.\n");
        return;
    }

    Conta novaConta;
    novaConta.numeroConta = numeroConta;

    printf("Informe o nome do cliente: ");
    scanf(" %[^\n]", novaConta.nome);

    printf("Informe o CPF: ");
    scanf(" %[^\n]", novaConta.cpf);

    printf("Informe o telefone: ");
    scanf(" %[^\n]", novaConta.telefone);

    printf("Informe o saldo inicial: ");
    scanf("%f", &novaConta.saldo);

    cadastro[*totalContas] = novaConta;
    (*totalContas)++;

    printf("Conta cadastrada com sucesso!\n");
}

// Procedimento para consultar saldo
void consultarSaldo(Conta cadastro[], int totalContas, int numeroConta) {
    int pos = buscarConta(cadastro, totalContas, numeroConta);
    if (pos == -1 || pos == -2) {
        printf("Conta não encontrada.\n");
    } else {
        printf("Saldo da conta %d: R$ %.2f\n", numeroConta, cadastro[pos].saldo);
    }
}

// Procedimento para depósito
void fazerDeposito(Conta cadastro[], int totalContas, int numeroConta) {
    int pos = buscarConta(cadastro, totalContas, numeroConta);
    if (pos == -1 || pos == -2) {
        printf("Conta não cadastrada.\n");
        return;
    }

    float valor;
    printf("Informe o valor a depositar: ");
    scanf("%f", &valor);
    cadastro[pos].saldo += valor;
    printf("Depósito realizado com sucesso. Novo saldo: R$ %.2f\n", cadastro[pos].saldo);
}

// Procedimento para saque
void fazerSaque(Conta cadastro[], int totalContas, int numeroConta) {
    int pos = buscarConta(cadastro, totalContas, numeroConta);
    if (pos == -1 || pos == -2) {
        printf("Conta não cadastrada.\n");
        return;
    }

    float valor;
    printf("Informe o valor a sacar: ");
    scanf("%f", &valor);

    if (cadastro[pos].saldo >= valor) {
        cadastro[pos].saldo -= valor;
        printf("Saque realizado com sucesso. Novo saldo: R$ %.2f\n", cadastro[pos].saldo);
    } else {
        printf("Saldo insuficiente para saque.\n");
    }
}

// Procedimento para exibir todas as contas
void exibirContas(Conta cadastro[], int totalContas) {
    if (totalContas == 0) {
        printf("Nenhuma conta cadastrada.\n");
        return;
    }

    for (int i = 0; i < totalContas; i++) {
        printf("\nConta %d\n", i + 1);
        printf("Número da conta: %d\n", cadastro[i].numeroConta);
        printf("Nome do titular: %s\n", cadastro[i].nome);
        printf("Telefone: %s\n", cadastro[i].telefone);
    }
}

int main() {
    Conta contaCorrente[MAX_CONTAS];
    Conta contaPoupanca[MAX_CONTAS];
    int totalCorrente = 0;
    int totalPoupanca = 0;

    int opcao, tipoConta, numeroConta;

    while (1) {
        printf("\n--- MENU ---\n");
        printf("1. Cadastrar nova conta\n");
        printf("2. Consultar saldo\n");
        printf("3. Fazer depósito\n");
        printf("4. Fazer saque\n");
        printf("5. Exibir todas as contas\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        if (opcao == 0) break;

        if (opcao >= 1 && opcao <= 5) {
            printf("Tipo de conta (1 - Corrente, 2 - Poupança): ");
            scanf("%d", &tipoConta);
        }

        switch (opcao) {
            case 1:
                printf("Informe o número da nova conta: ");
                scanf("%d", &numeroConta);
                if (tipoConta == 1)
                    cadastrarConta(contaCorrente, &totalCorrente, numeroConta);
                else
                    cadastrarConta(contaPoupanca, &totalPoupanca, numeroConta);
                break;
            case 2:
                printf("Informe o número da conta: ");
                scanf("%d", &numeroConta);
                if (tipoConta == 1)
                    consultarSaldo(contaCorrente, totalCorrente, numeroConta);
                else
                    consultarSaldo(contaPoupanca, totalPoupanca, numeroConta);
                break;
            case 3:
                printf("Informe o número da conta: ");
                scanf("%d", &numeroConta);
                if (tipoConta == 1)
                    fazerDeposito(contaCorrente, totalCorrente, numeroConta);
                else
                    fazerDeposito(contaPoupanca, totalPoupanca, numeroConta);
                break;
            case 4:
                printf("Informe o número da conta: ");
                scanf("%d", &numeroConta);
                if (tipoConta == 1)
                    fazerSaque(contaCorrente, totalCorrente, numeroConta);
                else
                    fazerSaque(contaPoupanca, totalPoupanca, numeroConta);
                break;
            case 5:
                if (tipoConta == 1)
                    exibirContas(contaCorrente, totalCorrente);
                else
                    exibirContas(contaPoupanca, totalPoupanca);
                break;
            default:
                printf("Opção inválida.\n");
        }
    }

    return 0;
}
