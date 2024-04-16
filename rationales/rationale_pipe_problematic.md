# Local do benchmark

Foi calculado o tempo que leva para:

1.  Transmitir o dado via dprintf;

Isto foi feito na função `task_conveyorN()`.

# Resultados

O resultado desta versão de pipe é interessante. Primeiramente vale
mencionar que o fato da leitura dos pipes bloquearem a execução, e
o valor de ambas as tasks serem lidas de forma sequencial faz com que
as mesmas sejam sincronizadas ao timing da task mais lenta. Isto faz 
com que a task controle somente leita o valor da task dois uma somente
vez, enquanto a mesma manda dois valores por segundo.

Note que a task dois em sí não é bloqueada pois o pipe() do Linux 
implementa um cache de 64KiB; ela somente perde autonomia quando este
cache é esgotado.

Por disto, é possivel ver nos dados brutos a task dois "mandar" seu
valor ao controle.

O pipe é definitivamente mais lerdo do que a thread: a média é de 23µs,
mediana de 16.4µs, moda de 16.3µs, desvio padrão de 11µs, máximo de 67µs,
minimo de 6µs.

### Histograma

Por mais de haver somente uma moda, ainda há uma bipartição dos timings.
É, no geral, de se esperar que a cada duas instâncias de '16µs', o 
sistema leve também uma instância de '37µs'.

### Diagrama de Impulsos

Em geral, o sistema alterna entre 16µs e 37µs, com algumas ilhas de
estabilidade. Tais ilhas aparentam ser periódicas.

# Método

O benchmark foi realizado em um computador de 8GiB RAM DDR3, processador
Pentium G3220 (2 núcleos) @ 2.9GHz, em sistema nativo Debian 12 Bookworm,
Linux 6.6.13, GCC 12.2.0, glibc 2.36. O benchmark for rodado por dez
minutos. Foi utilizado o `clock_gettime()`, 900 pontos foram gerados.


O programa foi compilado da seguinte forma:

```
$ gcc -std=c11 -Wall -Wextra -DTIMING -o conveyor_pipe_problematic conveyor_pipe_problematic.c conveyor_shared.c -lpthread -lrt
```


# Dados Brutos

```
1: 0.000054473
2: 0.000046898
2: 0.000038845
1: 0.000018655
2: 0.000014236
2: 0.000042118
1: 0.000023910
2: 0.000018077
2: 0.000015390
1: 0.000013658
2: 0.000009943
2: 0.000014583
1: 0.000016240
2: 0.000006884
2: 0.000023947
1: 0.000016590
2: 0.000006871
2: 0.000014872
1: 0.000015947
2: 0.000009626
2: 0.000016752
1: 0.000016119
2: 0.000007265
2: 0.000038759
1: 0.000016426
2: 0.000007401
2: 0.000014906
1: 0.000016527
2: 0.000009649
2: 0.000014970
1: 0.000016515
2: 0.000009612
2: 0.000038489
1: 0.000016232
2: 0.000009516
2: 0.000015355
1: 0.000016639
2: 0.000009586
2: 0.000038604
1: 0.000016560
2: 0.000009652
2: 0.000038735
1: 0.000016769
2: 0.000009580
2: 0.000036164
1: 0.000016086
2: 0.000009477
2: 0.000038669
1: 0.000016139
2: 0.000009657
2: 0.000038864
1: 0.000038404
2: 0.000030365
2: 0.000015002
1: 0.000038449
2: 0.000030426
2: 0.000040383
1: 0.000015992
2: 0.000009534
2: 0.000039646
1: 0.000016208
2: 0.000009598
2: 0.000039652
1: 0.000017009
2: 0.000009820
2: 0.000039727
1: 0.000016604
2: 0.000009536
2: 0.000038704
1: 0.000016468
2: 0.000030445
2: 0.000038709
1: 0.000016318
2: 0.000009602
2: 0.000039547
1: 0.000016128
2: 0.000009693
2: 0.000014664
1: 0.000016323
2: 0.000010589
2: 0.000016439
1: 0.000016013
2: 0.000034661
2: 0.000016514
1: 0.000015696
2: 0.000010453
2: 0.000016578
1: 0.000037426
2: 0.000009856
2: 0.000016227
1: 0.000036044
2: 0.000010143
2: 0.000015550
1: 0.000017107
2: 0.000010611
2: 0.000016465
1: 0.000016044
2: 0.000010434
2: 0.000016045
1: 0.000015537
2: 0.000010168
2: 0.000037893
1: 0.000015932
2: 0.000017417
2: 0.000017522
1: 0.000015640
2: 0.000010046
2: 0.000037647
1: 0.000015492
2: 0.000010293
2: 0.000037802
1: 0.000016037
2: 0.000009476
2: 0.000037733
1: 0.000015947
2: 0.000010273
2: 0.000038644
1: 0.000016028
2: 0.000031834
2: 0.000038213
1: 0.000015627
2: 0.000010187
2: 0.000038148
1: 0.000015850
2: 0.000031774
2: 0.000016269
1: 0.000037186
2: 0.000032831
2: 0.000038358
1: 0.000040053
2: 0.000028330
2: 0.000038299
1: 0.000037707
2: 0.000038725
2: 0.000038479
1: 0.000039281
2: 0.000027173
2: 0.000039110
1: 0.000037386
2: 0.000032676
2: 0.000038344
1: 0.000037597
2: 0.000009458
2: 0.000016797
1: 0.000037767
2: 0.000009913
2: 0.000016278
1: 0.000037432
2: 0.000010288
2: 0.000016375
1: 0.000037486
2: 0.000010380
2: 0.000016191
1: 0.000037642
2: 0.000009877
2: 0.000015769
1: 0.000037717
2: 0.000010434
2: 0.000015939
1: 0.000037612
2: 0.000009767
2: 0.000015861
1: 0.000037241
2: 0.000010124
2: 0.000016497
1: 0.000038995
2: 0.000010442
2: 0.000015988
1: 0.000038955
2: 0.000010387
2: 0.000038083
1: 0.000016396
2: 0.000031909
2: 0.000037748
1: 0.000015847
2: 0.000032941
2: 0.000042042
1: 0.000015552
2: 0.000031498
2: 0.000039546
1: 0.000013971
2: 0.000033393
2: 0.000038549
1: 0.000015593
2: 0.000031688
2: 0.000038253
1: 0.000037497
2: 0.000033111
2: 0.000037682
1: 0.000015942
2: 0.000031828
2: 0.000038409
1: 0.000015340
2: 0.000032991
2: 0.000038013
1: 0.000015614
2: 0.000031543
2: 0.000040243
1: 0.000015060
2: 0.000032886
2: 0.000038494
1: 0.000015744
2: 0.000027097
2: 0.000038173
1: 0.000016565
2: 0.000010301
2: 0.000040159
1: 0.000037561
2: 0.000009970
2: 0.000016328
1: 0.000036940
2: 0.000010149
2: 0.000016089
1: 0.000036610
2: 0.000010102
2: 0.000016435
1: 0.000037316
2: 0.000010398
2: 0.000016251
1: 0.000037406
2: 0.000010159
2: 0.000016033
1: 0.000037421
2: 0.000009772
2: 0.000015677
1: 0.000037286
2: 0.000010071
2: 0.000017412
1: 0.000038198
2: 0.000010420
2: 0.000016175
1: 0.000039236
2: 0.000010323
2: 0.000016472
1: 0.000015291
2: 0.000032820
2: 0.000037186
1: 0.000015489
2: 0.000028431
2: 0.000016036
1: 0.000037602
2: 0.000010068
2: 0.000016303
1: 0.000037973
2: 0.000032029
2: 0.000015830
1: 0.000038163
2: 0.000033002
2: 0.000037642
1: 0.000037427
2: 0.000026171
2: 0.000037647
1: 0.000015817
2: 0.000032590
2: 0.000036960
1: 0.000016238
2: 0.000027173
2: 0.000014551
1: 0.000015170
2: 0.000009826
2: 0.000037792
1: 0.000015597
2: 0.000027518
2: 0.000016007
1: 0.000015412
2: 0.000032666
2: 0.000016128
1: 0.000015252
2: 0.000030852
2: 0.000016392
1: 0.000016041
2: 0.000032986
2: 0.000038484
1: 0.000015174
2: 0.000031293
2: 0.000017258
1: 0.000015965
2: 0.000010278
2: 0.000016676
1: 0.000015836
2: 0.000026892
2: 0.000016105
1: 0.000015812
2: 0.000009792
2: 0.000016059
1: 0.000015705
2: 0.000032525
2: 0.000017212
1: 0.000037517
2: 0.000009784
2: 0.000015846
1: 0.000036925
2: 0.000009744
2: 0.000015634
1: 0.000037557
2: 0.000010412
2: 0.000016145
1: 0.000037196
2: 0.000009867
2: 0.000015476
1: 0.000037442
2: 0.000010279
2: 0.000015760
1: 0.000037432
2: 0.000031663
2: 0.000037717
1: 0.000015523
2: 0.000033417
2: 0.000037095
1: 0.000015739
2: 0.000031407
2: 0.000063141
1: 0.000037251
2: 0.000033101
2: 0.000038629
1: 0.000015612
2: 0.000031418
2: 0.000040223
1: 0.000037487
2: 0.000034169
2: 0.000037597
1: 0.000037833
2: 0.000010141
2: 0.000037402
1: 0.000037577
2: 0.000032720
2: 0.000038138
1: 0.000037728
2: 0.000031317
2: 0.000037963
1: 0.000037386
2: 0.000033202
2: 0.000038022
1: 0.000016311
2: 0.000031513
2: 0.000015637
1: 0.000015160
2: 0.000033262
2: 0.000015992
1: 0.000015525
2: 0.000009842
2: 0.000016243
1: 0.000015951
2: 0.000010158
2: 0.000015947
1: 0.000015647
2: 0.000009798
2: 0.000016488
1: 0.000015997
2: 0.000009883
2: 0.000015797
1: 0.000015889
2: 0.000010423
2: 0.000016571
1: 0.000015922
2: 0.000011307
2: 0.000016129
1: 0.000015988
2: 0.000031638
2: 0.000016176
1: 0.000013640
2: 0.000010129
2: 0.000016143
1: 0.000015863
2: 0.000028497
2: 0.000038118
1: 0.000037402
2: 0.000010372
2: 0.000016585
1: 0.000037432
2: 0.000022692
2: 0.000017231
1: 0.000037000
2: 0.000010260
2: 0.000016187
1: 0.000037922
2: 0.000009962
2: 0.000016429
1: 0.000037121
2: 0.000010150
2: 0.000041115
1: 0.000037892
2: 0.000032500
2: 0.000016198
1: 0.000037226
2: 0.000010286
2: 0.000016769
1: 0.000015974
2: 0.000032306
2: 0.000015878
1: 0.000037932
2: 0.000010334
2: 0.000016181
1: 0.000037697
2: 0.000009964
2: 0.000015940
1: 0.000037371
2: 0.000010223
2: 0.000016438
1: 0.000037742
2: 0.000010257
2: 0.000017266
1: 0.000037928
2: 0.000009831
2: 0.000016705
1: 0.000037331
2: 0.000027644
2: 0.000016068
1: 0.000037381
2: 0.000009952
2: 0.000016562
1: 0.000015704
2: 0.000009892
2: 0.000015959
1: 0.000016169
2: 0.000010114
2: 0.000016396
1: 0.000015636
2: 0.000009777
2: 0.000017160
1: 0.000016039
2: 0.000010327
2: 0.000016242
1: 0.000015271
2: 0.000010020
2: 0.000016089
1: 0.000016219
2: 0.000010417
2: 0.000017174
1: 0.000016379
2: 0.000009796
2: 0.000016478
1: 0.000015907
2: 0.000010183
2: 0.000015954
1: 0.000015894
2: 0.000010028
2: 0.000016151
1: 0.000015563
2: 0.000010182
2: 0.000016025
1: 0.000015562
2: 0.000009806
2: 0.000017006
1: 0.000037447
2: 0.000033237
2: 0.000040033
1: 0.000015461
2: 0.000027078
2: 0.000037802
1: 0.000035327
2: 0.000033597
2: 0.000016752
1: 0.000015945
2: 0.000032685
2: 0.000016111
1: 0.000037812
2: 0.000032425
2: 0.000015909
1: 0.000037783
2: 0.000030411
2: 0.000016382
1: 0.000037557
2: 0.000033227
2: 0.000038469
1: 0.000037221
2: 0.000031497
2: 0.000016388
1: 0.000037267
2: 0.000010489
2: 0.000037897
1: 0.000037637
2: 0.000031818
2: 0.000038298
1: 0.000037301
2: 0.000009785
2: 0.000016592
1: 0.000015755
2: 0.000034538
2: 0.000016431
1: 0.000037452
2: 0.000010514
2: 0.000016230
1: 0.000037170
2: 0.000009988
2: 0.000016191
1: 0.000037762
2: 0.000010413
2: 0.000016204
1: 0.000037852
2: 0.000026391
2: 0.000038569
1: 0.000016201
2: 0.000009974
2: 0.000016506
1: 0.000015844
2: 0.000010227
2: 0.000038299
1: 0.000015310
2: 0.000010200
2: 0.000016248
1: 0.000016003
2: 0.000009957
2: 0.000016013
1: 0.000015732
2: 0.000033167
2: 0.000038524
1: 0.000015857
2: 0.000010216
2: 0.000038068
1: 0.000015645
2: 0.000033132
2: 0.000038298
1: 0.000015969
2: 0.000028361
2: 0.000016802
1: 0.000015981
2: 0.000032365
2: 0.000016491
1: 0.000015929
2: 0.000032324
2: 0.000016448
1: 0.000015577
2: 0.000026186
2: 0.000038750
1: 0.000037366
2: 0.000031994
2: 0.000040719
1: 0.000015975
2: 0.000031448
2: 0.000016763
1: 0.000037251
2: 0.000032781
2: 0.000067340
1: 0.000037467
2: 0.000030631
2: 0.000037998
1: 0.000037216
2: 0.000032926
2: 0.000037877
1: 0.000036314
2: 0.000028306
2: 0.000016354
1: 0.000037176
2: 0.000010447
2: 0.000016374
1: 0.000037853
2: 0.000009785
2: 0.000016374
1: 0.000037737
2: 0.000010328
2: 0.000016442
1: 0.000038103
2: 0.000009624
2: 0.000015968
1: 0.000037893
2: 0.000010277
2: 0.000016178
1: 0.000037687
2: 0.000009958
2: 0.000016158
1: 0.000037477
2: 0.000010132
2: 0.000015932
1: 0.000037507
2: 0.000010067
2: 0.000016580
1: 0.000037431
2: 0.000033006
2: 0.000016178
1: 0.000016156
2: 0.000031568
2: 0.000038168
1: 0.000015787
2: 0.000033487
2: 0.000038800
1: 0.000015609
2: 0.000026913
2: 0.000038268
1: 0.000016146
2: 0.000032525
2: 0.000038709
1: 0.000015993
2: 0.000028140
2: 0.000038188
1: 0.000016278
2: 0.000032620
2: 0.000038053
1: 0.000016121
2: 0.000027689
2: 0.000038649
1: 0.000015549
2: 0.000032460
2: 0.000038879
1: 0.000015926
2: 0.000028186
2: 0.000037632
1: 0.000016025
2: 0.000032004
2: 0.000038905
1: 0.000015747
2: 0.000027413
2: 0.000038133
1: 0.000015415
2: 0.000032530
2: 0.000038238
1: 0.000015692
2: 0.000009836
2: 0.000016378
1: 0.000015831
2: 0.000010348
2: 0.000016764
1: 0.000015483
2: 0.000032956
2: 0.000016547
1: 0.000015648
2: 0.000010240
2: 0.000016257
1: 0.000015963
2: 0.000032039
2: 0.000016462
1: 0.000037467
2: 0.000010327
2: 0.000016396
1: 0.000015921
2: 0.000009862
2: 0.000016356
1: 0.000037256
2: 0.000010045
2: 0.000016576
1: 0.000034956
2: 0.000029011
2: 0.000037727
1: 0.000037912
2: 0.000033107
2: 0.000038193
1: 0.000015398
2: 0.000028842
2: 0.000038143
1: 0.000015661
2: 0.000032064
2: 0.000038038
1: 0.000037131
2: 0.000027478
2: 0.000037892
1: 0.000037311
2: 0.000032971
2: 0.000038569
1: 0.000015923
2: 0.000028130
2: 0.000037362
1: 0.000037868
2: 0.000035482
2: 0.000038213
1: 0.000015894
2: 0.000026261
2: 0.000038614
1: 0.000015719
2: 0.000032691
2: 0.000038163
1: 0.000015943
2: 0.000028315
2: 0.000037872
1: 0.000015863
2: 0.000032295
2: 0.000037131
1: 0.000015574
2: 0.000026551
2: 0.000037752
1: 0.000016070
2: 0.000032430
2: 0.000016358
1: 0.000015561
2: 0.000009968
2: 0.000016204
1: 0.000015469
2: 0.000040081
2: 0.000016496
1: 0.000015777
2: 0.000010264
2: 0.000016391
1: 0.000015185
2: 0.000032770
2: 0.000019936
1: 0.000015540
2: 0.000010460
2: 0.000016975
1: 0.000015506
2: 0.000010150
2: 0.000016491
1: 0.000015853
2: 0.000047209
2: 0.000016323
1: 0.000016457
2: 0.000010137
2: 0.000037917
1: 0.000015871
2: 0.000010230
2: 0.000016310
1: 0.000016318
2: 0.000031493
2: 0.000016279
1: 0.000016496
2: 0.000010114
2: 0.000016928
1: 0.000016059
2: 0.000028381
2: 0.000016202
1: 0.000016161
2: 0.000010011
2: 0.000015943
1: 0.000015750
2: 0.000009997
2: 0.000016285
1: 0.000033938
2: 0.000010111
2: 0.000015749
1: 0.000038424
2: 0.000010054
2: 0.000037963
1: 0.000013940
2: 0.000010209
2: 0.000015589
1: 0.000016322
2: 0.000025990
2: 0.000038018
1: 0.000016657
2: 0.000032430
2: 0.000037783
1: 0.000017137
2: 0.000026817
2: 0.000037862
1: 0.000015990
2: 0.000009824
2: 0.000016116
1: 0.000016809
2: 0.000027123
2: 0.000038544
1: 0.000016293
2: 0.000009933
2: 0.000016715
1: 0.000015533
2: 0.000033142
2: 0.000015617
1: 0.000017010
2: 0.000010382
2: 0.000016441
1: 0.000016398
2: 0.000032646
2: 0.000015877
1: 0.000015861
2: 0.000009840
2: 0.000016055
1: 0.000015965
2: 0.000009767
2: 0.000016088
1: 0.000015883
2: 0.000010086
2: 0.000015299
1: 0.000016358
2: 0.000009716
2: 0.000015925
1: 0.000016148
2: 0.000010154
2: 0.000016156
1: 0.000016127
2: 0.000027438
2: 0.000037897
1: 0.000037807
2: 0.000032084
2: 0.000038363
1: 0.000015763
2: 0.000028105
2: 0.000039326
1: 0.000016562
2: 0.000031989
2: 0.000038579
1: 0.000016132
2: 0.000009859
2: 0.000015988
1: 0.000015719
2: 0.000033728
2: 0.000037491
1: 0.000016396
2: 0.000027593
2: 0.000038579
1: 0.000016303
2: 0.000032244
2: 0.000038554
1: 0.000015737
2: 0.000028140
2: 0.000040578
1: 0.000016184
2: 0.000033397
2: 0.000038123
1: 0.000016368
2: 0.000028722
2: 0.000016055
1: 0.000015523
2: 0.000032776
2: 0.000038779
1: 0.000015977
2: 0.000028185
2: 0.000016553
1: 0.000015683
2: 0.000010380
2: 0.000015511
1: 0.000016220
2: 0.000009822
2: 0.000016128
1: 0.000014783
2: 0.000010293
2: 0.000016267
1: 0.000016064
2: 0.000009807
2: 0.000016378
1: 0.000015687
2: 0.000010119
2: 0.000016501
1: 0.000015849
2: 0.000033000
2: 0.000019509
1: 0.000016318
2: 0.000010092
2: 0.000016242
1: 0.000015879
2: 0.000010101
2: 0.000016123
1: 0.000015596
2: 0.000010156
2: 0.000038403
1: 0.000016201
2: 0.000031643
2: 0.000016025
1: 0.000015708
2: 0.000033196
2: 0.000037311
1: 0.000015887
2: 0.000032585
2: 0.000038163
1: 0.000015929
2: 0.000032971
2: 0.000015752
1: 0.000016255
2: 0.000030526
2: 0.000038174
1: 0.000016478
2: 0.000033181
2: 0.000038669
1: 0.000016449
2: 0.000029202
2: 0.000038313
1: 0.000016295
2: 0.000032174
2: 0.000037707
1: 0.000015955
2: 0.000028145
2: 0.000038374
1: 0.000016541
2: 0.000032706
2: 0.000038639
1: 0.000016529
2: 0.000027062
2: 0.000038459
1: 0.000016586
2: 0.000032100
2: 0.000038589
1: 0.000016222
2: 0.000012447
2: 0.000016439
1: 0.000016676
2: 0.000021698
2: 0.000016324
1: 0.000016182
2: 0.000010277
2: 0.000016039
1: 0.000015997
2: 0.000031057
2: 0.000014387
1: 0.000015905
2: 0.000010416
2: 0.000015869
1: 0.000020522
2: 0.000010196
2: 0.000016359
1: 0.000015877
2: 0.000010121
2: 0.000016406
1: 0.000016716
2: 0.000009846
2: 0.000038294
1: 0.000016340
2: 0.000010223
2: 0.000016302
1: 0.000016393
2: 0.000010274
2: 0.000015881
1: 0.000016274
2: 0.000010381
2: 0.000016771
1: 0.000015001
2: 0.000026677
```