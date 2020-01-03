# divisao tarefas

* **bia:** client simulator (testbench)

* **costa:** filas & client handler

* **diogo:** criação da estrutura base dos servidores

# objetivo
* usar multi core e comparar arquitetura thread based, com uma arquitetura hibrida (só com 1 thread pool)

**NOTA:** ha varios tipos de arquiteturas baseadas em eventos, ver no seda esses tipos e escolher 1 (ou tentar testar mais? prob not) 

[eventos só faz sentido com 1 core, como pc's hoje em dia sao multi core, fazemos arquitetura hibrida para fazer sentidos comparar threads]

* em relção à hibrida, ha um nr ideal de threads a usar na event pool (é 8 ou qql coisa assim) [fazer um teste com isso] 
 
* em thread based, as threads sao apagadas dps de usadas; em event driven, as threas estão smp na thread pool, mas sao usadas ou nao

(ver se api em event-driven é blocking ou non-blocking, for some reason; thread based nao temos de nos preocupar com bloquei idk why)

* na SEDA só usam dados que estão em cache; tentar testar dados em cache e no disco

* testar em hdd vs. ssd

* usar timestamps para tempo inicial e final e fazer o calculo à pata

* testar com pedidos na cache e com pedidos ao disco (ver se dá para limpar a cache)
