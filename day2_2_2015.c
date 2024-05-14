/*
--- Day 2: I Was Told There Would Be No Math ---
The elves are running low on wrapping paper, and so they need to submit an order for more. They have a list of the dimensions (length l, width w, and height h) of each present, and only want to order exactly as much as they need.
Os elfos estão ficando sem papel de embrulho, então precisam enviar um pedido para mais. Eles têm uma lista das dimensões (comprimento l, largura w e altura h) de cada presente e só querem encomendar exatamente o que precisam. 

Fortunately, every present is a box (a perfect right rectangular prism), which makes calculating the required wrapping paper for each gift a little easier: find the surface area of the box, which is 2*l*w + 2*w*h + 2*h*l. The elves also need a little extra paper for each present: the area of the smallest side. 
Por sorte, cada presente é uma caixa (um prisma retangular perfeito), o que facilita um pouco o cálculo do papel de embrulho necessário para cada presente: encontrar a área da superfície da caixa, que é 2*l*w + 2*w*h + 2*h*l. Os elfos também precisam de um pouco de papel extra para cada presente: a área do lado mais pequeno.

For example:
Por exemplo:

A present with dimensions 2x3x4 requires 2*6 + 2*12 + 2*8 = 52 square feet of wrapping paper plus 6 square feet of slack, for a total of 58 square feet.
Um presente com dimensões 2x3x4 requer 2*6 + 2*12 + 2*8 = 52 pés quadrados de papel de embrulho mais 6 pés quadrados de folga, totalizando 58 pés quadrados.

A present with dimensions 1x1x10 requires 2*1 + 2*10 + 2*10 = 42 square feet of wrapping paper plus 1 square foot of slack, for a total of 43 square feet.
Um presente com dimensões 1x1x10 requer 2*1 + 2*10 + 2*10 = 42 pés quadrados de papel de embrulho mais 1 pé quadrado de folga, totalizando 43 pés quadrados.

All numbers in the elves' list are in feet. How many total square feet of wrapping paper should they order?
Todos os números na lista dos elfos estão em pés. Quantos pés quadrados totais de papel de embrulho eles devem encomendar?

Your puzzle answer was 1598415.
Sua resposta para o puzzle foi 1598415.

--- Part Two ---
--- Parte Dois ---

The elves are also running low on ribbon. Ribbon is all the same width, so they only have to worry about the length they need to order, which they would again like to be exact.
Os elfos também estão ficando sem fita. A fita tem sempre a mesma largura, então eles só precisam se preocupar com o comprimento que precisam encomendar, que novamente gostariam que fosse exato.

The ribbon required to wrap a present is the shortest distance around its sides, or the smallest perimeter of any one face. Each present also requires a bow made out of ribbon as well; the feet of ribbon required for the perfect bow is equal to the cubic feet of volume of the present. Don't ask how they tie the bow, though; they'll never tell.
A fita necessária para embrulhar um presente é a menor distância ao redor dos seus lados, ou o menor perímetro de qualquer uma das faces. Cada presente também requer um laço feito de fita; os pés de fita necessários para o laço perfeito são iguais aos pés cúbicos de volume do presente. Não pergunte como eles dão o nó no laço, no entanto; eles nunca vão contar.

For example:
Por exemplo:

A present with dimensions 2x3x4 requires 2+2+3+3 = 10 feet of ribbon to wrap the present plus 2*3*4 = 24 feet of ribbon for the bow, for a total of 34 feet.
Um presente com dimensões 2x3x4 requer 2+2+3+3 = 10 pés de fita para embrulhar o presente mais 2*3*4 = 24 pés de fita para o laço, totalizando 34 pés.

A present with dimensions 1x1x10 requires 1+1+1+1 = 4 feet of ribbon to wrap the present plus 1*1*10 = 10 feet of ribbon for the bow, for a total of 14 feet.
Um presente com dimensões 1x1x10 requer 1+1+1+1 = 4 pés de fita para embrulhar o presente mais 1*1*10 = 10 pés de fita para o laço, totalizando 14 pés.

How many total feet of ribbon should they order?
Quantos pés totais de fita eles deveriam encomendar?

Your puzzle answer was 3812909.
Sua resposta para o puzzle foi 3812909.

Both parts of this puzzle are complete! They provide two gold stars: **
*/

#include <stdio.h>
#include <stdlib.h>

void editFile (FILE *baseFile, FILE *nMeasureFile);
int wrappingPaperOrder (FILE *nMeasureFile);
int ribbonOrder (FILE *ribbonMeasureFile);
void printResult (int wrappingPaperMeasurement, int ribbonMeasurement);

int main (){
    //variáveis utilizados, sendo duas para arquivo, pois reescrevi o arquivo de medição, por causa de um caracter x no arquivo original. Dessa forma resolvi manter só números, as duas variáveis result é pra armazenar os resultado de cada parte.
    FILE *measurementList, *measurementList1;
    int result, result1;

    //abertura do arquivo original contendo as medições.
    measurementList = fopen ("b2015.txt", "r");

    //criação do arquivo onde foi reescrito as medições.
    measurementList1 = fopen ("listofmeasurements.txt", "w+");

    //procedimento para a transcrição do arquivo original excluindo o caracter x para o outro arquivo.
    editFile (measurementList, measurementList1);

    //fecho o arquivo original, poiis não há mais necessidade de uso dele
    fclose (measurementList);

    //reposicionamento do arquivo que irei ler para o início
    rewind (measurementList1);

    //função wrappingPaperOrder que retorna o valor total de pés quadrados de papel de embrulho que será necessário pedir.
    result = wrappingPaperOrder (measurementList1);

    //reposicionamento do ponteiro para o início do arquivo
    rewind (measurementList1);

    //chamada da função para o cálculo de fita necessária
    result1 = ribbonOrder (measurementList1);

    //depois do uso do arquivo temos o fechamento do mesmo
    fclose (measurementList1);

    //chamada para o procedimento para printar os resultados coletados
    printResult (result, result1);

    exit (0);
}

void editFile (FILE *baseFile, FILE *nMeasureFile){
    //variável buffer que irá conter o caracter a ser preenchido no arquivo.
    char compare;

    //laço para leitura de um arquivo e reescrita no outro.
    while (fread(&compare, sizeof(char), 1, baseFile) == 1) {
        
        //aqui se ve se o caracter encontrado é o x e se foi, colocamos um espaço em branco pra delimitar um espaço entre os números. Isso irá facilitar na leitura do arquivo e saber corretamente as medidas.
        if (compare == 'x'){
            fputs (" ", nMeasureFile);
        }

        //caso contrário, atribuo o valor contido no buffer no novo arquivo.
        else
            fprintf (nMeasureFile, "%c", compare);
    }

    return;
}

int wrappingPaperOrder (FILE *nMeasureFile){
    //variáveis utilizadas nessa função. wrappingPaperMeasurement que vai armazenar o total de papel de embrulho necessário, rowRead para guardar os valores de length, width e height. Sabendo que cada linha representa um presente.
    int wrappingPaperMeasurement = 0;
    char rowRead[20];
    int length, width, height;

    //laço que tem como parâmetro existir caracter no arquivo com as medidas, lendo de linha a linha. E atribuindo a rowRead a linha lida
    while (fgets (rowRead, sizeof (rowRead), nMeasureFile) != NULL){
        //sscanf para processar a linha lida por fgets, o 3 é para específicar que estou pegando 3 valores
        if (sscanf(rowRead, "%d %d %d", &length, &width, &height) == 3) {
            //comparações para achar a menor área e efetuar o cálculo
            if ((length * width <= width * height) && (length * width <= length * height))
                wrappingPaperMeasurement += (length * width) + ((2 * length * width) + (2 * width * height) + (2 * height * length));
            else if ((length * height <= width * height) && (length * height <= length * width))
                wrappingPaperMeasurement += (length * height) + ((2 * length * width) + (2 * width * height) + (2 * height * length));
            else
                wrappingPaperMeasurement += (width * height) + ((2 * length * width) + (2 * width * height) + (2 * height * length));
        }
    }

    return wrappingPaperMeasurement;
}

int ribbonOrder (FILE *ribbonMeasureFile){
    //variáveis utilizadas nessa função. ribbonMeasurement que vai armazenar o total de papel de embrulho necessário, rowRead para guardar os valores de length, width e height. Sabendo que cada linha representa um presente.
    int ribbonMeasurement = 0;
    char rowRead[20];
    int length, width, height;

    ////laço que tem como parâmetro existir caracter no arquivo com as medidas, lendo de linha a linha. E atribuindo a rowRead a linha lida
    while (fgets (rowRead, sizeof (rowRead), ribbonMeasureFile) != NULL){
        // sscanf para processar a linha lida por fgets, o 3 é para específicar que estou pegando 3 valores
        if (sscanf(rowRead, "%d %d %d", &length, &width, &height) == 3) {
            //comparações para achar o menor perímetro e efetuar o cálculo
            if ((length + width <= width + height) && (length + width <= length + height))
                ribbonMeasurement += (2 * length) + (2 * width) + (length * width * height);
    
            else if ((length + height <= width + height) && (length + height <= length + width))
                ribbonMeasurement += (2 * length) + (2 * height) + (length * width * height);

            else
                ribbonMeasurement += (2 * width) + (2 * height) + (length * width * height);            
        }
    }

    return ribbonMeasurement;
}

void printResult (int wrappingPaperMeasurement, int ribbonMeasurement){
    //procedimento para printar os resultados encontrados.
    printf ("Santa's needs a total of %d square feet wrapping paper.\n\n", wrappingPaperMeasurement);

    printf ("Santa's needs a total of %d square feet of ribbon.\n\n", ribbonMeasurement);

    return;
}
