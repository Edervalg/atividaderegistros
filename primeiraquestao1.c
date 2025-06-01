#include <stdio.h>
#include <string.h>

#define NUM_ESTADOS 26
#define TAM_NOME 50

typedef struct {
    char nome[TAM_NOME];
    int num_veiculos;
    int num_acidentes;
} Estado;

void coletarDados(Estado estados[]) {
    printf("Coletando dados dos 26 estados:\n");
    for (int i = 0; i < NUM_ESTADOS; i++) {
        printf("\nEstado %d:\n", i + 1);
        printf("Nome do estado: ");
        scanf(" %[^\n]", estados[i].nome);
        printf("Numero de veiculos (2007): ");
        scanf("%d", &estados[i].num_veiculos);
        printf("Numero de acidentes (2007): ");
        scanf("%d", &estados[i].num_acidentes);
    }
}

void encontrarExtremos(Estado estados[], int *maior_idx, int *menor_idx) {
    *maior_idx = 0;
    *menor_idx = 0;
    
    for (int i = 1; i < NUM_ESTADOS; i++) {
        if (estados[i].num_acidentes > estados[*maior_idx].num_acidentes) {
            *maior_idx = i;
        }
        if (estados[i].num_acidentes < estados[*menor_idx].num_acidentes) {
            *menor_idx = i;
        }
    }
}

float calcularPercentual(Estado estados[], int estado_idx) {
    if (estados[estado_idx].num_veiculos == 0) {
        return 0.0f;
    }
    return ((float)estados[estado_idx].num_acidentes / estados[estado_idx].num_veiculos) * 100;
}

float calcularMediaAcidentes(Estado estados[]) {
    int total = 0;
    for (int i = 0; i < NUM_ESTADOS; i++) {
        total += estados[i].num_acidentes;
    }
    return (float)total / NUM_ESTADOS;
}

void estadosAcimaMedia(Estado estados[], float media) {
    printf("\nEstados com numero de acidentes acima da media (%.2f):\n", media);
    for (int i = 0; i < NUM_ESTADOS; i++) {
        if (estados[i].num_acidentes > media) {
            printf("- %s\n", estados[i].nome);
        }
    }
}

int main() {
    Estado estados[NUM_ESTADOS];
    int maior_idx, menor_idx;
    
    // (a) Coletar dados dos estados
    coletarDados(estados);
    
    // (b) Encontrar estados com maior e menor número de acidentes
    encontrarExtremos(estados, &maior_idx, &menor_idx);
    printf("\nEstado com MAIOR numero de acidentes: %s (%d acidentes)\n", 
           estados[maior_idx].nome, estados[maior_idx].num_acidentes);
    printf("Estado com MENOR numero de acidentes: %s (%d acidentes)\n", 
           estados[menor_idx].nome, estados[menor_idx].num_acidentes);
    
    // (c) Calcular e mostrar percentual de veículos envolvidos em acidentes para cada estado
    printf("\nPercentual de veiculos envolvidos em acidentes por estado:\n");
    for (int i = 0; i < NUM_ESTADOS; i++) {
        float percentual = calcularPercentual(estados, i);
        printf("%s: %.2f%%\n", estados[i].nome, percentual);
    }
    
    // (d) Calcular e mostrar média de acidentes no país
    float media_acidentes = calcularMediaAcidentes(estados);
    printf("\nMedia de acidentes no pais: %.2f\n", media_acidentes);
    
    // (e) Mostrar estados acima da média de acidentes
    estadosAcimaMedia(estados, media_acidentes);
    
    return 0;
}