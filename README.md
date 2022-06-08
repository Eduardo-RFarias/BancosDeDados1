# Atividade 1

Análise o problema abaixo e elabore um programa em C que atenda as exigências para o armazenamento dos registros que serão cadastrados pelo usuário de seu programa. Respeite o padrão de entrega de seu programa fonte na Linguagem C usando struct para elaborar a estrutura heterogênea de um ou mais registros que deverão ser armazenados por seu programa e os armazene organizadamente em arquivo de dados (em binário) e NÃO em texto, pois será somente o programa que irá manipular os dados guardados no arquivo (ou arquivos).

# ENUNCIADO

Crie uma representação do que seria um projeto de banco de dados eficiente para controlar o conjunto de dados necessários ao exercício de programação (Proprietário de Automóveis). Suponha que seu usuário deseje gerenciar estes cadastrados. Assim,você deverá implementar as estruturas que serão capazes de armazenar os registros previstos em seu programa em C utilizando struct.

Aqueles que estiverem com dificuldade para lembrar de struct (ou Estrutura de Dados Heterogêna) e de Arquivo na Linguagem C é sugerida a leitura/estudo do conteúdo disponível no CAE (ver ligação virtual no ambiente MOODLE da disciplina), em que se deve navegar para a disciplina Computação Básica (equivalente a Algoritmo - APC), ao invés de Sistemas Banco Dados 1, no menu superior e depois clicar nas opções do menu lateral à esquerda Estr. de Dados Hete e depois em Arquivos.

Respeitando o padrão de entrega no MOODLE, você deverá colocar o nome de seu arquivo (programa fonte em C) com a expressão inicial aula1exer1, seguida de seus dados pessoais de primeiro e último nome somente e sua matrícula. Por exemplo, suponha que a aluna Ana Maria Braga, com matrícula 13-1223222, fosse entregar a solução que ela elaborou. O nome do arquivo único que ela entregaria em C (que NÃO é em C++) seria:

aula1exer1_AnaBraga_131223222.c
Arquivos fontes que tiverem extensão .cpp não são soluções em C e por isso NÃO serão considerados entregues a contento desta primeira atividade da disciplina.

Para quem tiver necessidade de explicar como qualquer pessoa que baixar sua solução precisa fazer para executá-la corretamente deverá então criar um arquivo LEIA-ME.txt e este outro arquivo deverá ser compactado junto com a solução entregue com o código fonte. No LEIA-ME.txt deverão existir as instruções de como o usuário interessado deverá proceder para colocar sua solução para executar corretamente.

Ressalta-se que a entrega então deverá acontecer de um único arquivo compactado somente no formato ZIP (só serão aceitos arquivos compactados no formato ZIP) contendo o código fonte com um ou mais arquivos necessários para execução e avaliação da entrega, além do arquivo LEIA-ME.txt, por exemplo:

aula1exer1_AnaBraga_13-1223222.zip

Arquivos compactados com extensão .rar, .arj, .cab ou qualquer outra NÃO serão nem consideradas entregues a contento da primeira atividade prática da disciplina, demonstrando a falta de conhecimento prático do estudante que está cursando esta importante disciplina que é oferecida depois da metade do curso.

Atente também que só serão entregues os arquivos fontes do projeto que o professor estará abrindo em um IDE (Integrated Development Environment) e colocando em execução em C, devendo o programa INTERAGIR com o usuário, pois no mundo real não existe Judge que analisa solução que confere saída de dados, a partir de uma entrada. Caso a entrega não seja dos fontes para avaliação e execução pelo professor com a turma a atividade NÃO será reconhecida como realizada a contento também, além de demonstrar a falta de conhecimento básico do estudante de Engenharia de Software.

# PROBLEMA PROPOSTO

Observe a realidade que envolve uma única pessoa a ser proprietária de um automóvel no Brasil. Assim, verifique quais dados seriam necessários armazenar e registrar uma pessoa que possa ser identificada no país, além da identificação de um ou mais automóveis (carro somente) que sejam de sua propriedade (é o usuário que sabe quantos carros e proprietários ele deseja cadastrar e não o seu programa que deve guardar todos corretamente e para quantos o usuário quiser). É importante também destacar que o usuário de seu programa poderá cadastrar quantas pessoas e seus respectivos carros ela desejar (solução não pode só fazer o registro de uma pessoa e um carro para atender a esta demanda).
