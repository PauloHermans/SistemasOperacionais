#include <iostream>
using namespace std;
#include <locale.h>
#define TAM 5

void leitura (int vet[TAM])
{
    for (int i=0; i<TAM; i++)
    {
        cout << "Digite o valor da " << i+1 << "ª posição." << endl;
        cin >> vet[i];
    }
}

int igual (int vet[TAM])
{
    int ig=0;
    for (int i=1; i<TAM; i++)
    {
        if (vet[0]==vet[i])
        ig++;
    }
    return ig;
}

int maior (int vet[TAM])
{
    int mai=0;
    for (int i=1; i<TAM; i++)
    {
        if (vet[0]<vet[i])
        mai++;
    }
    return mai;
}

int menor (int vet[TAM])
{
    int men=0;
    for (int i=1; i<TAM; i++)
    {
        if (vet[0]>vet[i])
        men++;
    }
    return men;
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int vet[TAM];
    leitura(vet);
    cout << igual(vet) << " valores são iguais ao primeiro valor." << endl;
    cout << maior(vet) << " valores são maiores que o primeiro valor." << endl;
    cout << menor(vet) << " valores são menores que o primeiro valor." << endl;
    return 0;
}
