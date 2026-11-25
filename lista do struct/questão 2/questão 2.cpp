#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Produto {
    int codigo;
    char nome[50];
    float preco;
    int qtd;
};

struct Produto prod[15];
int cont = 0; 


int buscar(int cod) {
    int i;
    for (i = 0; i < cont; i++) {
        if (prod[i].codigo == cod) {
            return i;
        }
    }
    return -1;
}

void cadastrar() {
    int cod;

    if (cont == 15) {
        printf("\nO estoque esta cheio! (maximo 15 produtos)\n");
        return;
    }

    printf("\n--- CADASTRAR PRODUTO ---\n");
    printf("Codigo: ");
    scanf("%d", &cod);

    if (buscar(cod) != -1) {
        printf("\nJa existe um produto com esse codigo!\n");
        return;
    }

    prod[cont].codigo = cod;

    printf("Nome: ");
    fflush(stdin);
    gets(prod[cont].nome);

    printf("Preco: ");
    scanf("%f", &prod[cont].preco);

    printf("Quantidade em estoque: ");
    scanf("%d", &prod[cont].qtd);

    cont++;
    printf("\nProduto cadastrado!\n");
}

void listar() {
    int i;

    if (cont == 0) {
        printf("\nNenhum produto cadastrado ainda.\n");
        return;
    }

    printf("\n--- LISTA DE PRODUTOS ---\n");
    for (i = 0; i < cont; i++) {
        printf("\nCodigo: %d\n", prod[i].codigo);
        printf("Nome: %s\n", prod[i].nome);
        printf("Preco: R$ %.2f\n", prod[i].preco);
        printf("Estoque: %d\n", prod[i].qtd);
    }
}

void reposicao() {
    int cod, pos, q;

    printf("\n--- REPOR ESTOQUE ---\n");
    printf("Codigo do produto: ");
    scanf("%d", &cod);

    pos = buscar(cod);

    if (pos == -1) {
        printf("\nProduto nao encontrado!\n");
    } else {
        printf("Quanto vai repor? ");
        scanf("%d", &q);

        if (q <= 0) {
            printf("\nValor invalido!\n");
        } else {
            prod[pos].qtd = prod[pos].qtd + q;
            printf("\nEstoque atualizado! Agora tem %d unidades.\n", prod[pos].qtd);
        }
    }
}

void venda() {
    int cod, pos, q;

    printf("\n--- REGISTRAR VENDA ---\n");
    printf("Codigo do produto: ");
    scanf("%d", &cod);

    pos = buscar(cod);

    if (pos == -1) {
        printf("\nProduto nao encontrado!\n");
    } else {
        printf("Quantidade vendida: ");
        scanf("%d", &q);

        if (q <= 0) {
            printf("\nValor invalido!\n");
        } else if (q > prod[pos].qtd) {
            printf("\nNao tem estoque suficiente! So tem %d unidades.\n", prod[pos].qtd);
        } else {
            prod[pos].qtd = prod[pos].qtd - q;
            printf("\nVenda registrada! Total: R$ %.2f\n", q * prod[pos].preco);
            printf("Sobraram %d unidades.\n", prod[pos].qtd);
        }
    }
}

void consultar() {
    int cod, pos;

    printf("\n--- CONSULTAR PRODUTO ---\n");
    printf("Codigo do produto: ");
    scanf("%d", &cod);

    pos = buscar(cod);

    if (pos == -1) {
        printf("\nProduto nao encontrado!\n");
    } else {
        printf("\nCodigo: %d\n", prod[pos].codigo);
        printf("Nome: %s\n", prod[pos].nome);
        printf("Preco: R$ %.2f\n", prod[pos].preco);
        printf("Estoque: %d\n", prod[pos].qtd);
    }
}

void relatorio() {
    int i, posMaior = 0;
    float total = 0, valor, maior = 0;

    if (cont == 0) {
        printf("\nNenhum produto cadastrado ainda.\n");
        return;
    }

    for (i = 0; i < cont; i++) {
        valor = prod[i].preco * prod[i].qtd;
        total = total + valor;

        if (valor > maior) {
            maior = valor;
            posMaior = i;
        }
    }

    printf("\n--- RELATORIO ---\n");
    printf("Valor total em estoque: R$ %.2f\n", total);
    printf("\nProduto com maior valor em estoque:\n");
    printf("Codigo: %d\n", prod[posMaior].codigo);
    printf("Nome: %s\n", prod[posMaior].nome);
    printf("Valor: R$ %.2f\n", maior);
}

int main() {
    int op;

    do {
        system("cls");
        printf("===== PAPELARIA =====\n");
        printf("1 - Cadastrar produto\n");
        printf("2 - Listar produtos\n");
        printf("3 - Repor estoque\n");
        printf("4 - Registrar venda\n");
        printf("5 - Consultar produto\n");
        printf("6 - Relatorio do estoque\n");
        printf("0 - Sair\n");
        printf("\nEscolha: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                cadastrar();
                break;
            case 2:
                listar();
                break;
            case 3:
                reposicao();
                break;
            case 4:
                venda();
                break;
            case 5:
                consultar();
                break;
            case 6:
                relatorio();
                break;
            case 0:
                printf("\nSaindo...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }

        printf("\nPressione ENTER para continuar...");
        getchar(); 
        getchar();

    } while (op != 0);

    return 0;
}
