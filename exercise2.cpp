#include <iostream>
using namespace std;
#include <locale.h>
#define TAM 10

void leitura (int vet[TAM])
{
    for (int i=0; i<TAM; i++)
    {
        cout << "Digite a nota do " << i+1 << "º aluno." << endl;
        cin >> vet[i];
    }
}

float media (int vet[TAM])
{
    float med=0;
    for (int i=0; i<TAM; i++)
    {
        med += vet[i];
    }
    med /= TAM;
    return med;
}

int maiores (int vet[TAM], float med)
{
    int mai=0;
    for (int i=0; i<TAM; i++)
    {
        if (vet[i] > med)
        mai++;
    }
    return mai;
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int vet[TAM];
    leitura(vet);
    cout << "A média das notas foi " << media(vet) << "." << endl;
    cout << maiores(vet, media(vet)) << " alunos receberam nota acima da média." << endl;
    return 0;
}
