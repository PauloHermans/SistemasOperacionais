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

void calculo (int vetA[TAM],int vetB[TAM],int vetC[TAM])
{
    for (int i=0; i<TAM; i++)
    {
        vetC[i]=vetA[i]-vetB[i];
    }
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int vetA[TAM],vetB[TAM],vetC[TAM];
    cout << "Vetor A." << endl;
    leitura(vetA);
    cout << "Vetor B." << endl;
    leitura(vetB);
    calculo(vetA,vetB,vetC);
    cout << "Vetor C." << endl;
    for (int i=0; i<TAM; i++)
    {
        cout << "O valor da " << i+1 << "ª posição é " << vetC[i] << "." << endl;
    }
    return 0;
}
