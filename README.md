# PSE em Ação

Sistema de Planejamento e Acompanhamento de Ações de Saúde na Escola.

# Integrantes

### Ian Victor Scodro Peixoto RA: 26008088-2
### João Paulo Ribeiro Felix RA: 26007923-2
### Pedro Henrique De Lima Lopes RA: 26009522-2

# Sobre o projeto

Este projeto foi desenvolvido como parte da AEP do 2º semestre de 2026.

A proposta consiste em um programa em linguagem C para auxiliar no planejamento, registro e acompanhamento de ações coletivas do Programa Saúde na Escola (PSE).

O programa é executado no terminal e permite cadastrar ações, consultar informações, atualizar registros e gerar um resumo das atividades.

O sistema foi escrito de forma simples, utilizando estruturas básicas da linguagem C e respeitando os limites definidos na proposta da atividade.

# Escopo mínimo do sistema

## O sistema permite:

1. Cadastrar uma ação do PSE, informando o código, a escola, o tema, a data prevista, o público-alvo, o responsável e a quantidade prevista de participantes.

2. Listar as ações cadastradas com suas informações e situação.

3. Pesquisar ações por código, escola ou tema. A pesquisa por escola e tema compara o texto exato informado.

4. Atualizar a situação de uma ação para planejada, realizada ou cancelada.

5. Informar a quantidade efetiva de participantes quando uma ação for marcada como realizada.

6. Gerar um resumo com a quantidade de ações planejadas, realizadas e canceladas, o total de participantes efetivos nas ações realizadas e o percentual em relação ao total previsto nessas ações.

7. Validar entradas importantes, como códigos repetidos ou não positivos, quantidades negativas, campos obrigatórios vazios, datas que não existem no calendário e opções inválidas no menu.

# Arquivos do projeto

O código principal está em `src/pse.c`. A pasta `docs/` reúne os fluxogramas, o diagrama de casos de uso, as capturas do programa e o registro de testes.

# Requisitos técnicos mínimos

Menu principal controlado por uma estrutura de repetição, permitindo a execução de várias operações até que o usuário escolha encerrar o programa
Uso de estruturas condicionais
Uso de laços de repetição
Uso de vetores
Uso de funções
Uso de uma estrutura `struct` para organizar os dados de cada ação
Separação da solução em funções com responsabilidades claras, evitando concentrar toda a lógica na função `main`
Apresentação de mensagens claras para confirmar operações e informar erros de entrada
Armazenamento dos dados em memória durante a execução, com limite de 100 ações; os dados são perdidos ao encerrar o programa

Para compilar e executar em um terminal com GCC:

```sh
gcc -std=c99 -Wall -Wextra -pedantic src/pse.c -o pse
./pse
```

## Limites e cuidados obrigatórios

O sistema utilizará somente dados fictícios e informações coletivas sobre as ações
Não deverão ser cadastrados nomes, diagnósticos, prontuários, condições clínicas ou qualquer outro dado sensível individual de estudantes
O programa não realizará diagnóstico, triagem médica, prescrição ou recomendação de tratamento
Banco de dados, interface gráfica, aplicação web e bibliotecas avançadas não serão exigidos
A data é validada no formato DD/MM/AAAA, considerando os dias de cada mês e anos bissextos
