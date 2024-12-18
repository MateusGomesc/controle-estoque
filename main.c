#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int codigo;
    char *nome;
    char *categoria;
    int quantidadeEstoque;
    float preco;
} Produto;

void verifyFile(FILE *f) {
    if (f == NULL) {
        perror("Arquivo nao pode ser aberto\n");
        exit(1);
    }
}

int countLines(FILE *f) {
    int count = 0;
    char c;

    while ((c = fgetc(f)) != EOF) {
        if (c == '\n') {
            count++;
        }
    }

    return count;
}

void read() {
    FILE *f = fopen("C:\\Users\\Mateus\\CLionProjects\\controleEstoque\\produtos.txt", "r");
    verifyFile(f);

    Produto produto;
    produto.nome = (char *) malloc(20 * sizeof(char));
    produto.categoria = (char *) malloc(20 * sizeof(char));

    printf("Codigo\tNome\t\tTipo\t\tQuantidade\tPreco\n");
    while (1) {
        const int result = fscanf(f, "%d %s %s %d %f", &produto.codigo, produto.nome, produto.categoria, &produto.quantidadeEstoque, &produto.preco);

        if (result != 5) {
            break;
        }

        if (strcmp(produto.categoria, "Bebidas") != 0) {
            printf("%d\t%s\t\t%s\t%d\t\tR$%.2f\n", produto.codigo, produto.nome, produto.categoria, produto.quantidadeEstoque, produto.preco);
        }
        else {
            printf("%d\t%s\t\t%s\t\t%d\t\tR$%.2f\n", produto.codigo, produto.nome, produto.categoria, produto.quantidadeEstoque, produto.preco);
        }
    }
    printf("\n");

    fclose(f);
}

void create() {
    FILE *f = fopen("C:\\Users\\Mateus\\CLionProjects\\controleEstoque\\produtos.txt", "a");
    verifyFile(f);

    Produto produto;
    produto.nome = (char *) malloc(20 * sizeof(char));
    produto.categoria = (char *) malloc(20 * sizeof(char));

    printf("\nCadastro de produto:\n\n");

    printf("Codigo:");
    scanf("%d", &produto.codigo);
    while (produto.codigo < 0) {
        printf("Codigo invalido! Tente novamente...\n");
        printf("Codigo:");
        scanf("%d", &produto.codigo);
    }

    printf("Nome:");
    scanf("%s", produto.nome);

    printf("Categoria:");
    scanf("%s", produto.categoria);

    printf("Quantidade em estoque:");
    scanf("%d", &produto.quantidadeEstoque);
    while (produto.quantidadeEstoque < 0) {
        printf("Quantidade invalida! Tente novamente...\n");
        printf("Quantidade em estoque:");
        scanf("%d", &produto.quantidadeEstoque);
    }

    printf("Preco:");
    scanf("%f", &produto.preco);
    while (produto.preco < 0) {
        printf("Preco invalido! Tente novamente...\n");
        printf("Preco: ");
        scanf("%f", &produto.preco);
    }

    fprintf(f, "%d %s %s %d %.2f\n", produto.codigo, produto.nome, produto.categoria, produto.quantidadeEstoque, produto.preco);
    printf("\nProduto cadastrado com sucesso!\n");

    fclose(f);
}

int findId() {
    int codigo;

    printf("Codigo:");
    scanf("%d", &codigo);
    while (codigo < 0) {
        printf("Codigo invalido! Tente novamente...\n");
        printf("Codigo:");
        scanf("%d", &codigo);
    }

    FILE *f;
    f = fopen("C:\\Users\\Mateus\\CLionProjects\\controleEstoque\\produtos.txt", "r");
    verifyFile(f);

    Produto produto;
    produto.nome = (char *) malloc(20 * sizeof(char));
    produto.categoria = (char *) malloc(20 * sizeof(char));

    printf("\nBuscando...\n\n");
    while (!feof(f)) {
        fscanf(f, "%d %s %s %d %f", &produto.codigo, produto.nome, produto.categoria, &produto.quantidadeEstoque, &produto.preco);
        if (produto.codigo == codigo) {
            printf("Codigo\tNome\t\tTipo\t\tQuantidade\tPreco\n");
            if (strcmp(produto.categoria, "Bebidas") != 0) {
                printf("%d\t%s\t\t%s\t%d\t\tR$%.2f\n", produto.codigo, produto.nome, produto.categoria, produto.quantidadeEstoque, produto.preco);
            }
            else {
                printf("%d\t%s\t\t%s\t\t%d\t\tR$%.2f\n", produto.codigo, produto.nome, produto.categoria, produto.quantidadeEstoque, produto.preco);
            }
            printf("\n");
            return 0;
        }
    }

    printf("\nNao foi encontrado nenhum produto com o codigo %d...\n", codigo);
    fclose(f);
}

void stockReport() {
    FILE *f = fopen("C:\\Users\\Mateus\\CLionProjects\\controleEstoque\\produtos.txt", "r");
    verifyFile(f);

    Produto produto;
    produto.nome = (char *) malloc(20 * sizeof(char));
    produto.categoria = (char *) malloc(20 * sizeof(char));

    printf("Codigo\tNome\t\tTipo\t\tQuantidade\tPreco\n");
    while (1) {
        const int result = fscanf(f, "%d %s %s %d %f", &produto.codigo, produto.nome, produto.categoria, &produto.quantidadeEstoque, &produto.preco);

        if (result != 5) {
            break;
        }

        if (!produto.quantidadeEstoque) {
            printf("%d\t%s\t\t%s\t\t%d\t\t%.2f\n", produto.codigo, produto.nome, produto.categoria, produto.quantidadeEstoque, produto.preco);
        }
    }

    printf("\n");
    fclose(f);
}

void updateStock() {
    int codigo, value;

    printf("Codigo:");
    scanf("%d", &codigo);
    while (codigo < 0) {
        printf("Codigo invalido! Tente novamente...\n");
        printf("Codigo:");
        scanf("%d", &codigo);
    }

    printf("Novo estoque:");
    scanf("%d", &value);
    while (value < 0) {
        printf("Estoque invalido! Tente novamente...\n");
        printf("Novo estoque:");
        scanf("%d", &value);
    }

    FILE *fOriginal = fopen("C:\\Users\\Mateus\\CLionProjects\\controleEstoque\\produtos.txt", "r");
    FILE *fTemp = fopen("C:\\Users\\Mateus\\CLionProjects\\controleEstoque\\temp.txt", "w");

    verifyFile(fOriginal);
    verifyFile(fTemp);

    Produto produto;
    produto.nome = (char *) malloc(20 * sizeof(char));
    produto.categoria = (char *) malloc(20 * sizeof(char));

    while (1) {
        const int result = fscanf(fOriginal, "%d %s %s %d %f", &produto.codigo, produto.nome, produto.categoria, &produto.quantidadeEstoque, &produto.preco);

        if (result != 5) {
            break;
        }

        if (produto.codigo == codigo) {
            produto.quantidadeEstoque = value;
            fprintf(fTemp, "%d %s %s %d %.2f\n", produto.codigo, produto.nome, produto.categoria, produto.quantidadeEstoque, produto.preco);
        }
        else {
            fprintf(fTemp, "%d %s %s %d %.2f\n", produto.codigo, produto.nome, produto.categoria, produto.quantidadeEstoque, produto.preco);
        }
    }

    printf("Estoque do produto com codigo %d atualizado para %d!\n", codigo, value);

    fclose(fOriginal);
    fclose(fTemp);

    remove("C:\\Users\\Mateus\\CLionProjects\\controleEstoque\\produtos.txt");
    rename("C:\\Users\\Mateus\\CLionProjects\\controleEstoque\\temp.txt", "C:\\Users\\Mateus\\CLionProjects\\controleEstoque\\produtos.txt");
}

void deleteId() {
    int codigo;

    printf("Codigo:");
    scanf("%d", &codigo);
    while (codigo < 0) {
        printf("Codigo invalido! Tente novamente...\n");
        printf("Codigo:");
        scanf("%d", &codigo);
    }

    FILE *fOriginal = fopen("C:\\Users\\Mateus\\CLionProjects\\controleEstoque\\produtos.txt", "r");
    FILE *fTemp = fopen("C:\\Users\\Mateus\\CLionProjects\\controleEstoque\\temp.txt", "w");

    verifyFile(fOriginal);
    verifyFile(fTemp);

    Produto produto;
    produto.nome = (char *) malloc(20 * sizeof(char));
    produto.categoria = (char *) malloc(20 * sizeof(char));

    while (1) {
        const int result = fscanf(fOriginal, "%d %s %s %d %f", &produto.codigo, produto.nome, produto.categoria, &produto.quantidadeEstoque, &produto.preco);

        if (result != 5) {
            break;
        }

        if (produto.codigo != codigo) {
            fprintf(fTemp, "%d %s %s %d %.2f\n", produto.codigo, produto.nome, produto.categoria, produto.quantidadeEstoque, produto.preco);
        }
    }

    printf("Produto excluido com sucesso!\n");

    fclose(fOriginal);
    fclose(fTemp);

    remove("C:\\Users\\Mateus\\CLionProjects\\controleEstoque\\produtos.txt");
    rename("C:\\Users\\Mateus\\CLionProjects\\controleEstoque\\temp.txt", "C:\\Users\\Mateus\\CLionProjects\\controleEstoque\\produtos.txt");
}

void menu() {
    printf("\nGerenciamento de produtos:\n\n");
    printf("1. Inserir produto\n");
    printf("2. Atualizar estoque de produto\n");
    printf("3. Remover produto\n");
    printf("4. Mostrar todos os produtos\n");
    printf("5. Mostrar produto pelo codigo\n");
    printf("6. Relatorio de estoque\n");
    printf("0. Sair\n\n");
}

int main(void) {
    int opc;

    do {
        system("cls");
        menu();
        printf("Selecione uma opcao deseja:");
        scanf("%d", &opc);

        switch (opc) {
            case 0:
                break;
            case 1:
                system("cls");
                create();
                system("pause");
                break;
            case 2:
                system("cls");
                updateStock();
                system("pause");
                break;
            case 3:
                system("cls");
                deleteId();
                system("pause");
                break;
            case 4:
                system("cls");
                read();
                system("pause");
                break;
            case 5:
                system("cls");
                findId();
                system("pause");
                break;
            case 6:
                system("cls");
                stockReport();
                system("pause");
                break;
            default:
                printf("Opcao invalida! Tente novamente...");
        }
    }while (opc != 0);

    return 0;
}