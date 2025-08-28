# Sistema de Estacionamento em C

Este projeto implementa um **sistema de gerenciamento de estacionamento** em linguagem **C**, utilizando as estruturas de dados **pilha, fila e lista encadeada**.  
O objetivo é simular o funcionamento de um estacionamento com vagas limitadas, controlando a entrada, saída e espera de veículos.

---

## Estruturas Utilizadas
- **Pilha (Estacionamento)** → armazena os carros estacionados, simulando a ordem de entrada/saída (LIFO).  
- **Fila (Espera)** → guarda os carros que aguardam vaga disponível (FIFO).  
- **Lista (Cadastros)** → mantém o histórico de veículos que passaram pelo sistema.  

---

## Funcionalidades
- Estacionar carro → coloca o veículo na pilha ou, caso cheia, na fila de espera.  
- Retirar carro → remove um carro específico, contabilizando manobras necessárias.  
- Buscar carro → pesquisa por placa dentro do estacionamento.  
- Listar → exibe carros no estacionamento, cadastrados ou em espera.  
- Relatórios → mostram a ocupação, top 5 permanências e total de manobras.  

---

## Fluxo Resumido
1. O carro chega → tenta estacionar.  
2. Se há vaga → vai para o estacionamento.  
3. Se não há vaga → entra na fila de espera.  
4. Ao sair um carro → o primeiro da fila ocupa a vaga.  
