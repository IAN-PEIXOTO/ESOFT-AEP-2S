# PSE em Ação

Sistema de Planejamento e Acompanhamento de Ações de Saúde na Escola.

## Integrantes

- Ian Victor Scodro Peixoto — RA: 26008088-2
- João Paulo Ribeiro Felix — RA: 26007923-2
- Pedro — RA: a definir

## Sobre o projeto

Este projeto está sendo desenvolvido como parte da AEP do 2º semestre de 2026.

A proposta consiste na criação de um programa em linguagem C para auxiliar no planejamento, registro e acompanhamento de ações coletivas do Programa Saúde na Escola (PSE).

Como estudantes, somos responsáveis por planejar e desenvolver uma aplicação executada em terminal, capaz de cadastrar ações, consultar informações, atualizar registros e gerar um resumo geral das atividades realizadas.

O sistema será desenvolvido de forma simples, utilizando os conteúdos estudados durante o semestre e respeitando os limites definidos na proposta da atividade.

## Escopo mínimo do sistema

O sistema deverá permitir:

1. Cadastrar uma ação do PSE, informando:
   - código;
   - escola;
   - tema;
   - data prevista;
   - público-alvo;
   - responsável;
   - quantidade prevista de participantes;
   - situação inicial.

2. Listar todas as ações cadastradas, apresentando as informações de forma organizada e compreensível.

3. Pesquisar ações por código, escola ou tema.

4. Atualizar a situação de uma ação para:
   - planejada;
   - realizada;
   - cancelada.

   Quando a ação for realizada, também deverá ser registrada a quantidade efetiva de participantes.

5. Gerar um resumo geral contendo:
   - quantidade de ações planejadas;
   - quantidade de ações realizadas;
   - quantidade de ações canceladas;
   - total de participantes;
   - percentual de participação em relação à quantidade prevista.

6. Validar entradas importantes, evitando:
   - códigos repetidos;
   - quantidades negativas;
   - campos obrigatórios vazios;
   - opções inexistentes no menu.

## Requisitos técnicos mínimos

- Menu principal controlado por uma estrutura de repetição, permitindo a execução de várias operações até que o usuário escolha encerrar o programa.
- Uso de estruturas condicionais.
- Uso de laços de repetição.
- Uso de vetores.
- Uso de funções.
- Separação da solução em funções com responsabilidades claras, evitando concentrar toda a lógica na função `main`.
- Apresentação de mensagens claras para confirmar operações e informar erros de entrada.
- Armazenamento dos dados em memória durante a execução.
- O uso de arquivos será opcional e poderá ser considerado como melhoria adicional, caso esse conteúdo tenha sido trabalhado em aula.

## Limites e cuidados obrigatórios

- O sistema utilizará somente dados fictícios e informações coletivas sobre as ações.
- Não deverão ser cadastrados nomes, diagnósticos, prontuários, condições clínicas ou qualquer outro dado sensível individual de estudantes.
- O programa não realizará diagnóstico, triagem médica, prescrição ou recomendação de tratamento.
- Banco de dados, interface gráfica, aplicação web e bibliotecas avançadas não serão exigidos.
