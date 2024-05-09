/*
--- Day 1: Not Quite Lisp ---
Santa was hoping for a white Christmas, but his weather machine's "snow" function is powered by stars, and he's fresh out! To save Christmas, he needs you to collect fifty stars by December 25th.
O Papai Noel estava esperando por um "Natal branco" (Natal com neve), mas a função de "neve" da sua máquina climática é alimentada por estrelas, e ele está sem! Para salvar o Natal, ele precisa que você colete cinquenta estrelas até 25 de dezembro.

Collect stars by helping Santa solve puzzles. Two puzzles will be made available on each day in the Advent calendar; the second puzzle is unlocked when you complete the first. Each puzzle grants one star. Good luck!
Colete estrelas ajudando o Papai Noel a resolver puzzles. Dois puzzles serão disponibilizados a cada dia no calendário do Advento; o segundo puzzle é desbloqueado quando você completa o primeiro. Cada puzzle concede uma estrela. Boa sorte!

Here's an easy puzzle to warm you up.
Aqui está um puzzle fácil para te aquecer.

Santa is trying to deliver presents in a large apartment building, but he can't find the right floor - the directions he got are a little confusing. He starts on the ground floor (floor 0) and then follows the instructions one character at a time.
O Papai Noel está tentando entregar presentes em um grande prédio de apartamentos, mas ele não consegue encontrar o andar certo - as direções que ele recebeu estão um pouco confusas. Ele começa no térreo (andar 0) e então segue as instruções um caractere de cada vez.

An opening parenthesis, (, means he should go up one floor, and a closing parenthesis, ), means he should go down one floor.
Um parêntese de abertura, (, significa que ele deve subir um andar, e um parêntese de fechamento, ), significa que ele deve descer um andar.

The apartment building is very tall, and the basement is very deep; he will never find the top or bottom floors.
O prédio de apartamentos é muito alto, e o subsolo é muito profundo; ele nunca encontrará os andares mais altos ou mais baixos.

For example:
Por exemplo:

(()) and ()() both result in floor 0.
(()) e ()() resultam ambos no andar 0.

((( and (()(()( both result in floor 3.
((( e (()(()( resultam ambos no andar 3.

))((((( also results in floor 3.
))((((( também resulta no andar 3.

()) and ))( both result in floor -1 (the first basement level).
()) e ))( resultam ambos no andar -1 (o primeiro andar do subsolo). 

))) and )())()) both result in floor -3.
))) e )())()) resultam ambos no andar -3.

To what floor do the instructions take Santa?
A que andar as instruções levam o Papai Noel?

Your puzzle answer was 138.
Sua resposta para o puzzle foi 138.

--- Part Two ---
--- Parte Dois ---

Now, given the same instructions, find the position of the first character that causes him to enter the basement (floor -1). The first character in the instructions has position 1, the second character has position 2, and so on.
Agora, dadas as mesmas instruções, encontre a posição do primeiro caractere que o faz entrar no subsolo (andar -1). O primeiro caractere nas instruções tem posição 1, o segundo caractere tem posição 2, e assim por diante.

For example:
Por exemplo:

) causes him to enter the basement at character position 1.
) faz com que ele entre no subsolo na posição do caractere 1.

()()) causes him to enter the basement at character position 5.
()()) faz com que ele entre no subsolo na posição do caractere 5.

What is the position of the character that causes Santa to first enter the basement?
Qual é a posição do caractere que faz o Papai Noel entrar no subsolo pela primeira vez?

Your puzzle answer was 1771.
Sua resposta para o puzzle foi 1771.

Both parts of this puzzle are complete! They provide two gold stars: **
*/

//este código mostra em qual andar se encontra o Papai Noel após seguir uma lista de instruções.

#include <stdio.h>
#include <stdlib.h>

int floorIndicator (FILE *instructionFile);
int basementIndicator (FILE *instructionFile);
void printResult (int resultCurrentFloor, int resultNumberInstructionEnterTheBasement);

int main (){
    //variáveis que serão utilizadas Instruction é o arquivo contendo os comandos que o Papai Noel seguirá, result receberá o resultado do primeiro puzzle e result1 do segundo puzzle
    FILE *instructions;
    int result, result1;

    //abertura do arquivo e setagem de leitura, esse arquivo contém as instruções para se locomover no prédio.
    instructions = fopen ("a2015.txt", "r");

    //aqui chamamos a função floorIndicator com o arquivo de instrução como parâmetro, isso irá retornar a resposta para o primeiro puzzle na variável result
    result = floorIndicator (instructions);

    //recolocando o ponteiro do arquivo no começo novamente para a resolução do segundo puzzle.
    rewind (instructions);

    //aqui há a chamada da função basementIndicator com o arquivo de instrução como parâmetro, isso irá retornar a resposta para o segundo puzzle na variável result1
    result1 = basementIndicator (instructions);

    //fecha o arquivo de intrução
    fclose (instructions);

    //chama o procedimento para printar os resultados em tela
    printResult (result, result1);

    //após a execução estou saindo do programa com sucesso
    exit (0);
}

int floorIndicator (FILE *instructionFile){
    //a variável currentFloor, irá servir como um contador do andar atual que o Papai Noel está e a variável compare serve pra ser um buffer para guardar o caracter lido do arquivo de intruções e é utilizado posteriormente no loop para comparar com o caracter que serve para indicar uma locomoção do Papai Noel no prédio.
    int currentFloor = 0;
    char compare;

    //este laço durará enquanto tiver um caracter a ser lido no arquivo de instrução
    while (fread(&compare, sizeof(char), 1, instructionFile) == 1) {

        //comparações para definir se o Papai Noel sobe ou desce um andar no prédio
        if (compare == '(')
            currentFloor += 1;
        else if (compare == ')')
            currentFloor -= 1;
    }

    //retorna o andar que o Papai Noel atualmente se encontra
    return currentFloor;
}

int basementIndicator (FILE *instructionFile){
    // variável currentFloor, irá servir como um contador do andar atual que o Papai Noel está e a variável compare serve pra ser um buffer para guardar o caracter lido do arquivo de intruções e é utilizado posteriormente no loop para comparar com o caracter que serve para indicar uma locomoção do Papai Noel no prédio.
    int currentFloor = 0;
    char compare;

    //variável utilizada para contar a posição do caracter que irá levar o Papai Noel para o subsolo
    int instructionForTheBasement = 1;

    //este laço durará enquanto tiver um caracter a ser lido no arquivo de instrução
    while (fread(&compare, sizeof(char), 1, instructionFile) == 1) {

        //comparações para definir se o Papai Noel sobe ou desce um andar no prédio
        if (compare == '(')
            currentFloor += 1;
        else if (compare == ')')
            currentFloor -= 1;

        //aqui se nota que se alcançou o subsolo pela primeira vez com base nas instruções, deste modo há um break e a saída do loop
        if (currentFloor == -1)
            break;
        
        //somando um no contador de posição da instrução que levará o Papai Noel ao subsolo, como a variável se iniciou 1 a soma deve ser após a realização da comparação que sai do loop
        instructionForTheBasement += 1;
    }

    //checagem se o Papai Noel nunca atingiu o subsolo com base nas instruções
    if (currentFloor != -1)
        return 0;

    //retorna a posição do caracter que levou o Papai Noel pela primeira vez ao subsolo.
    return instructionForTheBasement;
}

void printResult (int resultCurrentFloor, int resultNumberInstructionEnterTheBasement){
    printf ("Santas is on the floor %d\n\n", resultCurrentFloor);

    printf ("And Santas enters the basement in instruction %d\n", resultNumberInstructionEnterTheBasement);

    return;
}
