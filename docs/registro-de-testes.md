# Registro de testes

O programa foi compilado com GCC usando `-std=c99 -Wall -Wextra -pedantic`. Foram verificados estes cenários:

1. Cadastrar e listar uma ação válida — aprovado.
2. Tentar cadastrar um código repetido — aprovado.
3. Pesquisar um código que não existe — aprovado.
4. Informar campo vazio e quantidade negativa — aprovado.
5. Pesquisar por escola e por tema — aprovado.
6. Atualizar a situação e gerar o resumo — aprovado.
7. Escolher uma opção inválida no menu — aprovado.
8. Rejeitar 31/02/2026 e aceitar uma data válida — aprovado.
9. Aceitar 29/02/2028 — aprovado.
10. Rejeitar 29/02/2027 e aceitar 28/02/2027 — aprovado.
11. Impedir cadastro acima do limite de 100 ações — aprovado.

Resultado: 11 de 11 cenários aprovados.
