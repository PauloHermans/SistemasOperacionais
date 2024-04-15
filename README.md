# Abstrato

Trabalhos apresentados como requisitos avaliativos para a disciplina de Sistemas Operacionais.

Trabalho M1 - Processos, Threads, Concorrência e Paralelismo: Alunos: Larissa de Souza, Paulo Hermans e Vinicius Schütz Piva . Data: 16/04.

Link para acesso ao relatório: https://univali-my.sharepoint.com/:w:/r/personal/phermans_edu_univali_br/Documents/SO_M1.docx?d=w786df790a93f431cb7b904af3f01f4dd&csf=1&web=1&e=WUIgh4

# Instruções de compilação

### Linux

Para os códigos de plataforma Linux, clone este repo em uma maquina com
tal sistema operacional, que tenha GCC 11+, GNU Make, e rode:
```
$ make conveyor_thread           TIMING=1
$ make conveyor_pipe_problematic TIMING=1
$ make conveyor_pipe_threaded    TIMING=1
```
para compilar.

Para rodar os programas e realizar os benchmarks, rode:
```
$ ./conveyor_{thread,pipe_problematic,pipe_threaded} 2> timing.txt
Contagem:     .... Peso Acumulado     ....^C
$ cat timing.txt
1: 0.00001234
2: 0.00004123
...
```

Para não emitir informações de profiling, compile novamente sem `TIMING=1`.

### Windows

O código foi feito para ser compilado via o crosscompilador do MinGW do Linux para rodar no Windows.
Por favor tenha certeza que o MinGW está instalado.

```
$ make windows_conveyor_thread        TIMING=1
$ make windows_conveyor_pipe_threaded TIMING=1
```

Note que não há uma versão `pipe_problematic`. Também note que a precisão do timer provido no Windows é pior do que
a oferecida no Linux (100ns vs 1ns).

Para windows, há uma terceira implementação de pipe que usa uma arquitetura cliente servidor:
```
$ make windows_pipe_server TIMING=1
```
Isto gerará três executaveis. Execute o servidor primeiro.

# Guia Documentação

A documentação se trata de comentários escritos no próprio código, e devem ser lidos na seguinte ordem: `conveyor_shared.h → conveyor_shared.c → conveyor_thread.c → conveyor_pipe_problematic.c → conveyor_pipe_threaded.c`.

Os arquivos `rationale_xyz.md` contém as observações e resultados estatísticos.
