#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODUTOS 40
#define TAM_DESCRICAO 50

typedef struct {
    int codigo;
    char descricao[TAM_DESCRICAO];
    float valor_unitario;
    int quantidade_estoque;
} Produto;

int total_produtos = 0;

void cadastrar_produto(Produto produtos[]) {
    if (total_produtos >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido!\n");
        return;
    }

    printf("\n--- Cadastro de Produto ---\n");
    
    printf("Codigo: ");
    scanf("%d", &produtos[total_produtos].codigo);
    
    printf("Descricao: ");
    scanf(" %[^\n]", produtos[total_produtos].descricao);
    
    printf("Valor unitario: ");
    scanf("%f", &produtos[total_produtos].valor_unitario);
    
    printf("Quantidade em estoque: ");
    scanf("%d", &produtos[total_produtos].quantidade_estoque);
    
    total_produtos++;
    printf("Produto cadastrado com sucesso!\n");
}

void alterar_valor(Produto produtos[]) {
    int codigo, encontrado = 0;
    float novo_valor;
    
    printf("\n--- Alterar Valor ---\n");
    printf("Digite o codigo do produto: ");
    scanf("%d", &codigo);
    
    for (int i = 0; i < total_produtos; i++) {
        if (produtos[i].codigo == codigo) {
            printf("Produto encontrado: %s\n", produtos[i].descricao);
            printf("Valor atual: R$ %.2f\n", produtos[i].valor_unitario);
            printf("Novo valor: ");
            scanf("%f", &novo_valor);
            
            produtos[i].valor_unitario = novo_valor;
            printf("Valor atualizado com sucesso!\n");
            encontrado = 1;
            break;
        }
    }
    
    if (!encontrado) {
        printf("Produto nao encontrado!\n");
    }
}

float informar_valor(Produto produtos[], int codigo) {
    for (int i = 0; i < total_produtos; i++) {
        if (produtos[i].codigo == codigo) {
            return produtos[i].valor_unitario;
        }
    }
    return -1; // Código inválido
}

int informar_estoque(Produto produtos[], int codigo) {
    for (int i = 0; i < total_produtos; i++) {
        if (produtos[i].codigo == codigo) {
            return produtos[i].quantidade_estoque;
        }
    }
    return -1; // Código inválido
}

void vender_produto(Produto produtos[]) {
    int codigo, quantidade, estoque;
    char resposta;
    
    printf("\n--- Venda de Produto ---\n");
    printf("Codigo do produto: ");
    scanf("%d", &codigo);
    
    for (int i = 0; i < total_produtos; i++) {
        if (produtos[i].codigo == codigo) {
            estoque = produtos[i].quantidade_estoque;
            
            if (estoque == 0) {
                printf("Produto esgotado!\n");
                return;
            }
            
            printf("Produto: %s\n", produtos[i].descricao);
            printf("Estoque atual: %d\n", estoque);
            printf("Quantidade desejada: ");
            scanf("%d", &quantidade);
            
            if (quantidade <= estoque) {
                produtos[i].quantidade_estoque -= quantidade;
                printf("Venda realizada! Total: R$ %.2f\n", quantidade * produtos[i].valor_unitario);
            } else {
                printf("Quantidade insuficiente em estoque!\n");
                printf("Deseja comprar todo o estoque disponivel (%d unidades)? (S/N): ", estoque);
                scanf(" %c", &resposta);
                
                if (toupper(resposta) == 'S') {
                    float total = estoque * produtos[i].valor_unitario;
                    produtos[i].quantidade_estoque = 0;
                    printf("Venda realizada! Total: R$ %.2f\n", total);
                } else {
                    printf("Venda cancelada.\n");
                }
            }
            return;
        }
    }
    
    printf("Produto nao encontrado!\n");
}

void atualizar_estoque(Produto produtos[]) {
    int codigo, quantidade, encontrado = 0;
    
    printf("\n--- Atualizar Estoque ---\n");
    printf("Digite o codigo do produto: ");
    scanf("%d", &codigo);
    
    for (int i = 0; i < total_produtos; i++) {
        if (produtos[i].codigo == codigo) {
            printf("Produto encontrado: %s\n", produtos[i].descricao);
            printf("Estoque atual: %d\n", produtos[i].quantidade_estoque);
            printf("Nova quantidade: ");
            scanf("%d", &quantidade);
            
            produtos[i].quantidade_estoque = quantidade;
            printf("Estoque atualizado com sucesso!\n");
            encontrado = 1;
            break;
        }
    }
    
    if (!encontrado) {
        printf("Produto nao encontrado!\n");
    }
}

void listar_produtos(Produto produtos[]) {
    printf("\n--- Lista de Produtos ---\n");
    for (int i = 0; i < total_produtos; i++) {
        printf("%d - %s\n", produtos[i].codigo, produtos[i].descricao);
    }
}

void listar_estoque_zero(Produto produtos[]) {
    printf("\n--- Produtos com Estoque Zero ---\n");
    int tem_zero = 0;
    
    for (int i = 0; i < total_produtos; i++) {
        if (produtos[i].quantidade_estoque == 0) {
            printf("%d - %s\n", produtos[i].codigo, produtos[i].descricao);
            tem_zero = 1;
        }
    }
    
    if (!tem_zero) {
        printf("Nenhum produto com estoque zero!\n");
    }
}

int main() {
    Produto produtos[MAX_PRODUTOS];
    int opcao, codigo;
    
    do {
        printf("\n=== PAPELARIA ESCOLAR ===\n");
        printf("1. Cadastrar novo produto\n");
        printf("2. Alterar valor unitario\n");
        printf("3. Consultar valor unitario\n");
        printf("4. Consultar estoque\n");
        printf("5. Realizar venda\n");
        printf("6. Atualizar estoque\n");
        printf("7. Listar todos os produtos\n");
        printf("8. Listar produtos com estoque zero\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                cadastrar_produto(produtos);
                break;
            case 2:
                alterar_valor(produtos);
                break;
            case 3:
                printf("\nDigite o codigo do produto: ");
                scanf("%d", &codigo);
                float valor = informar_valor(produtos, codigo);
                if (valor >= 0) {
                    printf("Valor unitario: R$ %.2f\n", valor);
                } else {
                    printf("Produto nao encontrado!\n");
                }
                break;
            case 4:
                printf("\nDigite o codigo do produto: ");
                scanf("%d", &codigo);
                int estoque = informar_estoque(produtos, codigo);
                if (estoque >= 0) {
                    printf("Quantidade em estoque: %d\n", estoque);
                } else {
                    printf("Produto nao encontrado!\n");
                }
                break;
            case 5:
                vender_produto(produtos);
                break;
            case 6:
                atualizar_estoque(produtos);
                break;
            case 7:
                listar_produtos(produtos);
                break;
            case 8:
                listar_estoque_zero(produtos);
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);
    
    return 0;
}