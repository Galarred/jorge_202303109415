#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Fruta
{
    int codigo;
    char nome[50];
    int quantidade;
    float preco;
    struct Fruta *proximo;
} Fruta;

Fruta *criarFruta(int codigo, char *nome, int quantidade, float preco)
{
    Fruta *novaFruta = (Fruta *)malloc(sizeof(Fruta));
    novaFruta->codigo = codigo;
    strcpy(novaFruta->nome, nome);
    novaFruta->quantidade = quantidade;
    novaFruta->preco = preco;
    novaFruta->proximo = NULL;
    return novaFruta;
}

void inserirFruta(Fruta **cabeca, Fruta *novaFruta)
{
    novaFruta->proximo = *cabeca;
    *cabeca = novaFruta;
}

void listarFrutas(Fruta *cabeca)
{
    if (cabeca == NULL)
    {
        printf("Lista de frutas vazia.\n");
        return;
    }
    printf("Lista de Frutas:\n");
    while (cabeca != NULL)
    {
        printf("Código: %d, Nome: %s, Quantidade: %d, Preço: %.2f\n", cabeca->codigo, cabeca->nome, cabeca->quantidade, cabeca->preco);
        cabeca = cabeca->proximo;
    }
}

Fruta *buscarFruta(Fruta *cabeca, int codigo)
{
    while (cabeca != NULL)
    {
        if (cabeca->codigo == codigo)
        {
            return cabeca;
        }
        cabeca = cabeca->proximo;
    }
    return NULL;
}

void alterarFruta(Fruta *cabeca, int codigo)
{
    Fruta *fruta = buscarFruta(cabeca, codigo);
    if (fruta == NULL)
    {
        printf("Fruta não encontrada.\n");
        return;
    }
    printf("Digite o novo nome da fruta: ");
    scanf("%s", fruta->nome);
    printf("Digite a nova quantidade da fruta: ");
    scanf("%d", &fruta->quantidade);
    printf("Digite o novo preço da fruta: ");
    scanf("%f", &fruta->preco);
}

void excluirFruta(Fruta **cabeca, int codigo)
{
    Fruta *anterior = NULL;
    Fruta *atual = *cabeca;

    while (atual != NULL && atual->codigo != codigo)
    {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL)
    {
        printf("Fruta não encontrada.\n");
        return;
    }

    if (anterior == NULL)
    {
        *cabeca = atual->proximo;
    }
    else
    {
        anterior->proximo = atual->proximo;
    }

    free(atual);
}

void venderFruta(Fruta **cabeca, int codigo, int quantidade)
{
    Fruta *fruta = buscarFruta(*cabeca, codigo);
    if (fruta == NULL)
    {
        printf("Fruta não encontrada.\n");
        return;
    }
    if (fruta->quantidade < quantidade)
    {
        printf("Quantidade em estoque insuficiente.\n");
        return;
    }
    fruta->quantidade -= quantidade;
}

void salvarVendas(Fruta *cabeca)
{
    FILE *arquivo = fopen("vendas.txt", "a");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (cabeca != NULL)
    {
        fprintf(arquivo, "Código: %d, Nome: %s, Quantidade Vendida: %d, Preço: %.2f\n", cabeca->codigo, cabeca->nome, cabeca->quantidade, cabeca->preco);
        cabeca = cabeca->proximo;
    }

    fclose(arquivo);
}

int main()
{
    Fruta *cabeca = NULL;

    while (1)
    {
        int opcao;
        printf("\n////////////////// Mercadinho do seu Zé ////////////////////\n");
        printf("\n1. Cadastrar Fruta\n");
        printf("2. Listar Frutas\n");
        printf("3. Buscar Fruta\n");
        printf("4. Alterar Fruta\n");
        printf("5. Excluir Fruta\n");
        printf("6. Vender Fruta\n");
        printf("7. Sair\n");
        printf("\nDigite a opção desejada: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
        {
            int codigo, quantidade;
            char nome[50];
            float preco;
            printf("Digite o código da fruta: ");
            scanf("%d", &codigo);
            printf("Digite o nome da fruta: ");
            scanf("%s", nome);
            printf("Digite a quantidade da fruta: ");
            scanf("%d", &quantidade);
            printf("Digite o preço da fruta: ");
            scanf("%f", &preco);
            Fruta *novaFruta = criarFruta(codigo, nome, quantidade, preco);
            inserirFruta(&cabeca, novaFruta);
            printf("Fruta cadastrada com sucesso!\n");
            break;
        }
        case 2:
            listarFrutas(cabeca);
            break;
        case 3:
        {
            int codigo;
            printf("Digite o código da fruta: ");
            scanf("%d", &codigo);
            Fruta *fruta = buscarFruta(cabeca, codigo);
            if (fruta == NULL)
            {
                printf("Fruta não encontrada.\n");
            }
            else
            {
                printf("Código: %d, Nome: %s, Quantidade: %d, Preço: %.2f\n", fruta->codigo, fruta->nome, fruta->quantidade, fruta->preco);
            }
            break;
        }
        case 4:
        {
            int codigo;
            printf("Código da fruta para alteração: ");
            scanf("%d", &codigo);
            alterarFruta(cabeca, codigo);
            break;
        }
        case 5:
        {
            int codigo;
            printf("Código da fruta para ser excluída: ");
            scanf("%d", &codigo);
            excluirFruta(&cabeca, codigo);
            break;
        }
        case 6:
        {
            int codigo, quantidade;
            printf("Código da fruta para venda: ");
            scanf("%d", &codigo);
            printf("Quantidade a ser vendida: ");
            scanf("%d", &quantidade);
            venderFruta(&cabeca, codigo, quantidade);
            break;
        }
        case 7:
            printf("Programa encerrado.... Tchau!\n");
            exit(0);
        default:
            printf("Opção inválida.\n");
        }
    }

    return 0;
}