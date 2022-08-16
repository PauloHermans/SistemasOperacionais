#include <iostream>
using namespace std;
#include <locale.h>
#define TAM 10

void leitura (int vet[TAM])
{
    cout << "Digite " << TAM << " valores." << endl;
    for (int i=0; i<TAM; i++)
    {
        cin >> vet[i];
    }
}

void exibicao (int vet[TAM])
{
    cout << "Invertidos ficam:" << endl;
    for (int i=TAM-1; i>=0; i--)
    {
        cout << vet[i] << endl;
    }
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int vet[TAM];
    leitura(vet);
    exibicao(vet);
    return 0;
}
